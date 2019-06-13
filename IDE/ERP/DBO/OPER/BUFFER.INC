{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/BUFFER.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}            {$I PEAKTOP:GLOBAL_VARIABLES.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                 {$I PEAKTOP:OBJ/TACTION.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}              {$I PEAKTOP:OBJ/TIMAGELIST.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}               {$I PEAKTOP:OBJ/TCOLUMNEH.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}               {$I PEAKTOP:OBJ/TDBGRIDEH.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                {$I PEAKTOP:OBJ/TXCPANEL.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBAR.INC}             {$I PEAKTOP:OBJ/TXCGROUPBAR.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}        {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}            {$I PEAKTOP:OBJ/TXFBDATASETS.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC} {$I ../$COMMON/FORMERP.INC}                   {$ENDIF}
const
  msg_caption      = 'Буфер обмена базы данных';  
  msg_item_unknown = '<Неизвестно>';
  msg_actitemdel     = 'Удалить';    msg_actitemdel_hint    = 'Удалить элемент из буфера';    
  msg_actitemdelall  = 'Очистить';   msg_actitemdelall_hint = 'Очистить буфер от запоменнных элементов';    
  //============================================================================
  procedure RefreshViewItems(const aOwner:TComponent; const aTB_ID, aBUFFNAME:string); forward;
  //============================================================================
  procedure tbbObjItem_OnClick(Sender :TObject);
  var
    lkSL :TStringList;
  begin
    lkSL := TStringList.Create;
    lkSL.Text := TxcToolBarButton(Sender).HelpKeyWord;
    RefreshViewItems(TComponent(Sender).Owner.Owner, lkSL[0], lkSL[1]);
    lkSL.Free;
  end;
  //============================================================================
  procedure RefreshGroupBar(const aOwner :TComponent);
  var
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
    lkDS :TDataSource;
    lkGB :TxcGroupBar;
    lkGP :TxcGroupPanel;
    lkTBB:TxcToolBarButton;
    lkSQL:string;
    i    :Integer;
  begin
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQR, lkDS);
    lkSQL := '~'+ERP_GUID_NONE+'~';
    for i:=ERP_OBJECTTYPE_REF to ERP_OBJECTTYPE_MENU do
      lkSQL := lkSQL + ERP_ObjectGUID(i) + '~';
    lkQr.SQL.Text :=  
        'SELECT COALESCE(REF.ID,0) AS ID, COALESCE(REF.NAME,'''+msg_item_unknown+''')AS NAME '+SQLCRLF+
        '      ,COALESCE(REF.OBJ_NAME,'''') AS OBJ_NAME, REF.BUFF_NAME '+SQLCRLF+
        'FROM   (SELECT DISTINCT B.NAME AS BUFF_NAME, B.OBJ_NAME '+SQLCRLF+
        '             ,(SELECT FIRST 1 T.BASE_TYPE_ID FROM TABL$_TB T WHERE (T.ID = B.OBJ_NAME)) AS ID '+SQLCRLF+
        '             ,(SELECT FIRST 1 T.NAME         FROM TABL$_TB T WHERE (T.ID = B.OBJ_NAME)) AS NAME '+SQLCRLF+
        '        FROM   TABL$_BUFFER B '+SQLCRLF+
        '        WHERE (B.USER_ID = '''+GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''') '+SQLCRLF+
        '          AND ('''+lkSQL+''' CONTAINING ''~''||B.NAME||''~'') '+SQLCRLF+
        '        UNION ALL '+SQLCRLF+
        '        SELECT DISTINCT B.NAME AS BUFF_NAME, B.NAME AS OBJ_NAME '+SQLCRLF+
        '             ,(SELECT FIRST 1 T.BASE_TYPE_ID FROM TABL$_TB T WHERE (T.ID = B.NAME)) AS ID '+SQLCRLF+
        '             ,(SELECT FIRST 1 T.NAME         FROM TABL$_TB T WHERE (T.ID = B.NAME)) AS NAME '+SQLCRLF+
        '        FROM   TABL$_BUFFER B  '+SQLCRLF+
        '        WHERE (B.USER_ID = '''+GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''') '+SQLCRLF+
        '          AND ('''+lkSQL+''' NOT CONTAINING ''~''||B.NAME||''~'') '+SQLCRLF+
        '        )REF '+SQLCRLF+
        'ORDER BY REF.ID, REF.NAME ';  
    try
      lkQr.Open;
    except
    end;
    if not lkQr.Active then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      exit;
      end;
    lkGB := TxcGroupBar(aOwner.FindComponent('GBObjects'));
    while(lkGB.GroupPanelsCount > 0)do
      lkGB.GroupPanels[0].Free;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkGP := TxcGroupBar_AddGroupPanel(lkGB, 'gbp'+ERP_ObjectName(lkQr.FieldByName('ID').AsInteger), ERP_ObjectCaptions(lkQr.FieldByName('ID').AsInteger), lkQr.FieldByName('ID').AsInteger + 10);
      lkTBB := CreateTxcToolBarButton(lkGP,lkGP,'', lkQr.FieldByName('NAME').AsString, lkQr.FieldByName('NAME').AsString, 0,0,20,200, alTop,lkQr.FieldByName('ID').AsInteger,nil);
      lkTBB.HelpKeyWord := lkQr.FieldByName('OBJ_NAME').AsString+#13#10+StrTrimAll(lkQr.FieldByName('BUFF_NAME').AsString);                    
      lkTBB.ImagesSmall := lkGB.Images;
      lkTBB.ShowCaption := true;
      lkTBB.OnClick     := @tbbObjItem_OnClick;
      lkGP.Height := (lkGP.ControlCount * lkTBB.Height) + 4 + lkGB.ItemHeight;
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;    
  end;
  //============================================================================
  procedure RefreshViewItems(const aOwner:TComponent; const aTB_ID, aBUFFNAME:string);
  var
    lkQr  :TxFBQuery;
    lkSQL:string;
    i    :Integer;
  begin
    lkSQL := '~'+ERP_GUID_NONE+'~';
    for i:=ERP_OBJECTTYPE_REF to ERP_OBJECTTYPE_MENU do
      lkSQL := lkSQL + ERP_ObjectGUID(i) + '~';
    lkQr  := TxFBQuery(TDBGridEh(aOwner.FindComponent('dbgRef')).DataSource.DataSet);
    if lkQr.Transaction.InTransaction then
      lkQr.Transaction.Commit;
    lkQr.SQL.Text := 
      'EXECUTE BLOCK RETURNS( '+SQLCRLF+
      '   ID            TYPE OF COLUMN TABL$_BUFFER.ID '+SQLCRLF+
      '  ,NAME          TYPE OF COLUMN TABL$_BUFFER.NAME '+SQLCRLF+
      '  ,FLAG_DELETE   TYPE OF COLUMN TABL$_BUFFER.FLAG_DELETE '+SQLCRLF+
      '  ,SESSION_ID    TYPE OF COLUMN TABL$_BUFFER.SESSION_ID '+SQLCRLF+
      '  ,USER_ID       TYPE OF COLUMN TABL$_BUFFER.USER_ID '+SQLCRLF+
      '  ,OBJ_NAME      TYPE OF COLUMN TABL$_BUFFER.OBJ_NAME '+SQLCRLF+
      '  ,OBJ_ID        TYPE OF COLUMN TABL$_BUFFER.OBJ_ID '+SQLCRLF+
      '  ,OBJ_CAPT      TYPE OF COLUMN TABL$_BUFFER.OBJ_ID '+SQLCRLF+
      '  ,OBJ_TYPE_ID   TYPE OF COLUMN TABL$_TB_TYPES.ID '+SQLCRLF+
      '  ,OBJ_TYPE_NAME TYPE OF COLUMN TABL$_TB_TYPES.NAME '+SQLCRLF+
      '  ,FOREGROUND    TYPE OF COLUMN TABL$_BUFFER.FOREGROUND '+SQLCRLF+
      '  ,BACKGROUND    TYPE OF COLUMN TABL$_BUFFER.BACKGROUND '+SQLCRLF+
      ')AS '+SQLCRLF+
      '  DECLARE VARIABLE P_SQL DOMN$BLOB_SQL; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  FOR '+SQLCRLF+
      '    SELECT  B.ID, B.NAME, B.FLAG_DELETE, B.SESSION_ID, B.USER_ID, B.OBJ_NAME, B.OBJ_ID '+SQLCRLF+
      '           ,B.BACKGROUND, B.FOREGROUND '+SQLCRLF+
      '           ,(SELECT FIRST 1 T1.BASE_TYPE_ID FROM TABL$_TB T1 WHERE (T1.ID = TRIM(B.OBJ_NAME)))AS TYPE_ID '+SQLCRLF+
      '           ,(SELECT FIRST 1 T2.NAME         FROM TABL$_TB T2 WHERE (T2.ID = TRIM(B.OBJ_NAME)))AS OBJ_CAPTION '+SQLCRLF+
      '    FROM    TABL$_BUFFER  B '+SQLCRLF+
      '    WHERE   (B.USER_ID = '''+GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''') '+SQLCRLF+
      '      AND   ( (TRIM(B.NAME) = '''+aBUFFNAME+''') AND ('''+lkSQL+''' NOT CONTAINING ''~''||B.NAME||''~'') )'+SQLCRLF+
      '       OR   ((B.OBJ_NAME = '''+aTB_ID+''') AND ('''+lkSQL+''' CONTAINING ''~''||B.NAME||''~'')  )'+SQLCRLF+
      '    INTO    :ID, :NAME, :FLAG_DELETE, :SESSION_ID, :USER_ID, :OBJ_NAME, :OBJ_ID, :BACKGROUND, :FOREGROUND '+SQLCRLF+
      '           ,:OBJ_TYPE_ID, :OBJ_TYPE_NAME '+SQLCRLF+
      '  DO '+SQLCRLF+
      '    BEGIN '+SQLCRLF+
      '    OBJ_CAPT = :NAME; '+SQLCRLF+
      '    IF(EXISTS(SELECT R.RDB$RELATION_ID FROM RDB$RELATIONS R WHERE (TRIM(R.RDB$RELATION_NAME) = TRIM(:OBJ_NAME))))THEN '+SQLCRLF+
      '      BEGIN '+SQLCRLF+
      '      P_SQL = ''SELECT FIRST 1 R.NAME FROM ''||:OBJ_NAME||'' R WHERE (R.ID = ''''''||:OBJ_ID||'''''') ''; '+SQLCRLF+
      '      EXECUTE STATEMENT :P_SQL INTO :OBJ_CAPT; '+SQLCRLF+
      '      END '+SQLCRLF+
      '    SUSPEND; '+SQLCRLF+
      '    END '+SQLCRLF+
      'END';
//    Dialogs.MessageDlg(lkQr.SQL.Text, mtInformation, [mbOk]);  
    try lkQr.Open; except end;
  end;
  //============================================================================
  procedure RefreshView(aOwner :TComponent);
  var
    lkSL :TStringList;
  begin
    RefreshGroupBar(aOwner);
    with TxcGroupBar(aOwner.FindComponent('GBObjects')) do 
      if(GroupPanelsCount > 0)then
        if(GroupPanels[0].ControlCount > 0)then
          begin
          lkSL := TStringList.Create; 
          lkSL.Text := TxcToolBarButton(GroupPanels[0].Controls[GroupPanels[0].ControlCount-1]).HelpKeyWord;
          RefreshViewItems(aOwner, lkSL[0], lkSL[1]);
          lkSL.Free;
          end;
  end;
  //============================================================================
  procedure actItemDel_OnExecute(Sender :TObject);
  var
    lkSQL :string;
    lkQr  :TxFBQuery;
  begin
    lkQr  := TxFBQuery(TDBGridEh(TComponent(Sender).Owner.FindComponent('dbgRef')).DataSource.DataSet);
    if not lkQr.Active then exit;
    if not(lkQr.RecordCount>0)then exit;
    if(Dialogs.MessageDlg(msg_actitemdel_hint+' "'+lkQr.FieldByName('OBJ_CAPT').AsString+'" ?', mtConfirmation, [mbYes, mbNo]) <> mrYes)then exit;
    lkSQL := 'DELETE FROM TABL$_BUFFER B WHERE (B.ID = '''+lkQr.FieldByName('ID').AsString+''')';
    ExecSQL(FBDataBase, lkSQL);
  end;
  //============================================================================
  procedure actItemDelAll_OnExecute(Sender :TObject);
  var
    lkSQL :string;
    lkQr  :TxFBQuery;
  begin
    lkQr  := TxFBQuery(TDBGridEh(TComponent(Sender).Owner.FindComponent('dbgRef')).DataSource.DataSet);
    if not lkQr.Active then exit;
    if not(lkQr.RecordCount>0)then exit;
    if(Dialogs.MessageDlg(msg_actitemdelall_hint+' "'+lkQr.FieldByName('OBJ_TYPE_NAME').AsString+'" ?', mtConfirmation, [mbYes, mbNo]) <> mrYes)then exit;
    lkSQL := 'DELETE FROM TABL$_BUFFER B WHERE (TRIM(B.OBJ_NAME) = '''+StrTrimAll(lkQr.FieldByName('OBJ_NAME').AsString)+''') '+
      ' AND (B.NAME = '''+StrTrimAll(lkQr.FieldByName('NAME').AsString)+''')';
    ExecSQL(FBDataBase, lkSQL);
  end;
  //============================================================================
  procedure evRef_OnEventAlert(Sender :TObject; EventName: string; EventCount: LongInt; var CancelAlerts: Boolean);
  begin
    RefreshView(TComponent(Sender).Owner);
    CancelAlerts := false;
  end;
  //============================================================================
  procedure TERPFormOperBuffer_OnClose(Sender :TObject; var Action :TCloseAction);
  var
    lkEv :TxFBEvents;
  begin
    Action := caFree;
    lkEv := TxFBEvents(TComponent(Sender).FindComponent('evRef'));
    if lkEv.Registered then
      lkEv.UnRegisterEvents;
    AutoFree; 
  end; 
  //============================================================================
  function TERPFormOperBuffer_Create:TAmunhotepForm;
  var
    lkIL        :TImageList;
    lkGB        :TxcGroupBar;
    lkPnlClient :TxcPanel;
    lkToolBar   :TxcGradientPanelVista;
    lkTr        :TxFBTransaction;
    lkQr        :TxFBQuery;
    lkDS        :TDataSource;
    lkDBG       :TDBGridEh;
    lkCol       :TColumnEh;
    lkEv        :TxFBEvents;
    lkAct       :TCustomAction;
    lkTBB       :TxcToolBarButton;
  begin
    DontAutoFree;
    Result := TAmunhotepForm(TERPForm_Create(msg_caption, ERP_FILENAME_ICO_BUFFER, ERP_FILENAME_BMP_BUFFER, false, @TERPFormOperBuffer_OnClose));
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    lkIL := CreateTImageListConfiguration(Result, 'ilConfig');
    lkGB := CreateTxcGroupBar(Result, Result, 'GBObjects', 0,0,0,200, alLeft,gdLeftToRight, 24,2);
    lkGB.Images := lkIL;
    lkPnlClient := CreateTxcPanel(Result, Result, 'pnlClient','',alClient, 0,0,0,0, xbsNone);
    lkToolBar   := CreateTxcGradientPanelVistaToolBar(Result, lkPnlClient, 'ToolBar', '', alTop, 0,0,24,200, xbsRaized);
    CreateTxFBTransQuery(Result,'trRef', 'qrRef', 'DSqrRef', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQR, lkDS)  
    lkDBG := CreateTDBGridEh(Result, lkPnlClient, lkDS, 'dbgRef', 0,0,0,0, alClient);
    lkDBG.Options := [dgTitles,dgIndicator,dgColumnResize,dgColLines,dgRowLines,dgTabs,dgRowSelect,dgAlwaysShowSelection,dgConfirmDelete,dgCancelOnExit];
    lkDBG.Columns.Clear;
    lkCol := CreateTColumnEh(lkDBG,'OBJ_TYPE_ID'  ,'','Объект|Тип'          , 20,taLeftJustify);
    lkCol.KeyList.Text  := '0'+#13#10+'1'+#13#10+'2'+#13#10+'3'+#13#10+'4'+#13#10+'5'+#13#10+'6';
    lkCol.PickList.Text := lkCol.KeyList.Text;
    lkCol.ImageList     := lkIL;
    lkCol := CreateTColumnEh(lkDBG,'OBJ_TYPE_NAME','','Объект|Наименование' ,200,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'FLAG_DELETE'  ,'','Элемент|X'           , 16,taCenter);
    with lkCol do
      begin
      KeyList.Text  := '1'+#13#10+'0';
      PickList.Text := 'X'+#13#10+' ';
      CheckBoxes := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'OBJ_ID'       ,'','Элемент|Код'         , 72,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'OBJ_CAPT'     ,'','Элемент|Наименование',620,taLeftJustify);
    lkAct := CreateTAction(Result, 'actItemDel',msg_actitemdel,msg_actitemdel_hint,'Ctrl+Del',0,70); lkAct.OnExecute := @actItemDel_OnExecute;
    lkTBB := CreateTxcToolBarButton2(Result, lkToolBar, 'tbb'+lkAct.Name,lkToolBar.ControlCount*80,0,22,80,alLeft,lkAct); lkTBB.ShowCaption := true;
    lkAct := CreateTAction(Result, 'actItemDelAll',msg_actitemdelall,msg_actitemdelall_hint,'Shift+Del',0,67); lkAct.OnExecute := @actItemDelAll_OnExecute;
    lkTBB := CreateTxcToolBarButton2(Result, lkToolBar, 'tbb'+lkAct.Name,lkToolBar.ControlCount*80,0,22,80,alLeft,lkAct); lkTBB.ShowCaption := true;
    RefreshView(Result);
    lkEv := TxFBEvents.Create(Result);
    with lkEv do
      begin
      Name         := 'evRef';
      DataBase     := FBDataBase;
      OnEventAlert := @evRef_OnEventAlert;
      Events.Clear;
      Events.Add('TABL$_BUFFER');
      if not Registered then
        RegisterEvents;
      end; 
  end;
