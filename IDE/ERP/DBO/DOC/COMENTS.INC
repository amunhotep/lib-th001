{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/COMENTS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                       {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                         {$I PEAKTOP:GLOBAL_OBJECTS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                             {$I PEAKTOP:OBJ/TLABEL.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMEMO.INC}                              {$I PEAKTOP:OBJ/TMEMO.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                            {$I PEAKTOP:OBJ/TACTION.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                          {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                          {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}              {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                           {$I PEAKTOP:OBJ/TXCPANEL.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                   {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}                {$I ../OBJECTNAMES.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}       {$I ../$COMMON/FORMERP_LANG.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}      {$I ../$COMMON/FORMERP_NAMES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_CONST.INC}      {$I ../$COMMON/FORMERP_CONST.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$I ../$COMMON/FORMERP.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC}  {$I ../DBGRID/GETCELLPARAMS_JRNL.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/COMENTS_GLOBALVARIABLES.INC}{$I ./COMENTS_GLOBALVARIABLES.INC}           {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/DOC/COMENTS.INC =====================
  procedure DocComentsIntf_Form_OnShow(Sender :TObject);
  begin
    TForm(Sender).BringToFront;
  end;
  //============================================================================
  function DocComentsIntf_InputQueryStr(const ACaption, aPrompt:string; var aValue:string):Boolean;
  var
    lkForm :TForm;
    lkMemo :TMemo;
  begin
    lkForm := TERPForm_Create(aCaption, '', 'PEAKTOP:IMG/CONFIG/ERP/LOG0032X0032.BMP', true, nil);
    with lkForm do
      begin
      Width  := 480;
      Height := 320;
      OnShow := @DocComentsIntf_Form_OnShow;
      end;
    TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)).Caption := #$20#$20#$20#$20#$20#$20+aPrompt;
    lkMemo := CreateTMemo(lkForm, lkForm, 'Memo', 0, 80, 200, 200, alClient);
    with lkMemo do
      begin
      Font.Name := 'Courier New';
      Font.Size := 10;
      Font.Style:= [fsBold];
      ScrollBars:= ssVertical;
      Text      := aValue;
      end;
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      aValue := lkMemo.Text;
    lkForm.Free;
  end;
  //============================================================================
  function DocComentsIntf_qrComents(aOwner:TComponent):TxFBQuery;
  begin
    Result := TxFBQuery(TDBGridEh(aOwner.FindComponent(obj_name_erp_data_dbgcoments)).DataSource.DataSet);
  end;
  //============================================================================
  procedure DocComentsIntf_Refresh(aOwner :TComponent);
  begin
    with DocComentsIntf_qrComents(aOwner) do
      begin
      if Transaction.InTransaction then
        Transaction.Commit;
      try Open; except end;  
      end;
  end;
  //============================================================================
  procedure DocComentsIntf_qrComents_AfterClose(DataSet :TDataSet);
  begin
    with TxFBQuery(DataSet).Transaction do
      if InTransaction then
        Commit;
  end;
  //============================================================================
  procedure DocComentsIntf_actIns_OnExecute(Sender :TObject);
  var 
    lkStr :string;
  begin
    lkStr := '';
    if DocComentsIntf_InputQueryStr(msg_erp_actcomentins_hint,msg_erp_enter_new_coment, lkStr) then
      begin
      if(Length(lkStr) > 254)then lkStr := Copy(lkStr, 1, 254);
      lkStr := StrReplaceStr(lkStr, #13#10, #$20);
      lkStr := StrReplaceStr(lkStr, '''', '''''');
      ExecSQL(DocComentsIntf_qrComents(TComponent(Sender).Owner).DataBase, 'INSERT INTO TABL$J_COMENTS(J_ID, NAME, USER_ID) VALUES ('+
        DocComentsIntf_qrComents(TComponent(Sender).Owner).DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+', '''+
        lkStr+''', '''+GetGlobalVariable('DATABASE_USER')+''')');
      DocComentsIntf_Refresh(TComponent(Sender).Owner);
      end;    
  end;
  //============================================================================
  procedure DocComentsIntf_actUpd_OnExecute(Sender :TObject);
  var 
    lkStr :string;
    lkID  :string;
  begin  
    with DocComentsIntf_qrComents(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount > 0)then exit;
      if(UpperCase(FieldByName('USER_ID').AsString) <> UpperCase(GetGlobalVariable('DATABASE_USER')))then
        begin
        Dialogs.MessageDlg(msg_error_coment_upd_onlyyou, mtWarning, [mbOK]);
        exit;
        end;
      lkStr := FieldByName('NAME').AsString;
      lkID  := FieldByName('ID').AsString;
      end;   
    if DocComentsIntf_InputQueryStr(msg_erp_actcomentupd_hint,msg_erp_enter_new_coment,lkStr) then
      begin
      if(Length(lkStr) > 254)then lkStr := Copy(lkStr, 1, 254);
      lkStr := StrReplaceStr(lkStr, #13#10, #$20);
      lkStr := StrReplaceStr(lkStr, '''', '''''');
      ExecSQL(DocComentsIntf_qrComents(TComponent(Sender).Owner).DataBase, 'UPDATE TABL$J_COMENTS J1 SET J1.NAME = '''+lkStr+''' WHERE (J1.ID = '+lkID+')');
      DocComentsIntf_Refresh(TComponent(Sender).Owner);
      end; 
  end;
  //============================================================================
  procedure DocComentsIntf_actDel_OnExecute(Sender :TObject);
  var 
    lkStr :string;
    lkID  :string;
  begin
    with DocComentsIntf_qrComents(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount > 0)then exit;
      if(UpperCase(FieldByName('USER_ID').AsString) <> UpperCase(GetGlobalVariable('DATABASE_USER')))then
        begin
        Dialogs.MessageDlg(msg_error_coment_del_onlyyou, mtWarning, [mbOK]);
        exit;
        end;
      lkStr := FieldByName('NAME').AsString;
      lkID  := FieldByName('ID').AsString;
      end;       
    if Dialogs.MessageDlg(msg_erp_actcomentdel_hint+' "'+lkStr+'" ?', mtConfirmation, [mbYes, mbNo]) = mrYes then
      begin
      ExecSQL(DocComentsIntf_qrComents(TComponent(Sender).Owner).DataBase, 'DELETE FROM TABL$J_COMENTS J1 WHERE (J1.ID = '+lkID+')');
      DocComentsIntf_Refresh(TComponent(Sender).Owner);
      end; 
  end;
  //============================================================================
  procedure DocComentsIntf_actRefresh_OnExecute(Sender :TObject);
  begin
    DocComentsIntf_Refresh(TComponent(Sender).Owner);
  end;
  //============================================================================
  function DocComentsIntf_Create(aOwner:TComponent; aParent:TWinControl; aMasterDataSource:TDataSource):TxcPanel;
  var
    lkTopBar :TxcGradientPanelVista;
    lkAct    :TCustomAction;
    lkTr     :TxFBTransaction;
    lkQr     :TxFBQuery;
    lkDS     :TDataSource;
    lkDBG    :TDBGridEh;
    lkCol    :TColumnEh;
    lkLbl    :TLabel;
    lkTBB    :TxcToolBarButton;
  begin
    DontAutoFree;
    Result := CreateTxcPanel(aOwner, aParent, obj_name_erp_panelcoments, '', alClient,0,0,200,200,xbsNone);
    lkTopBar := CreateTxcGradientPanelVista(Result,Result,'','',alTop, 0,0,24,200,xbsRaized);
    with lkTopBar do
      begin
      Font.Size  := 7;
      Font.Style := [fsBold];
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Window;
      end;
    lkLbl := CreateTLabel(lkTopBar,lkTopBar,#$20+msg_erp_doccoments,0,0,20,200,alLeft,taLeftJustify);
    lkLbl.Font.Color := Amunhotep.MainForm.StyleManager.Colors.Window;
    lkLbl.Font.Size  := 10;  
    lkTr := TxFBTransaction.Create(aOwner);
    with lkTr do
      begin
      Name            := obj_name_erp_data_trcoments;
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        Add('isc_tpb_read_committed');
        Add('isc_tpb_rec_version');
        Add('isc_tpb_read');
        Add('isc_tpb_nowait');
        end;
      end;
    lkQr := TxFBQuery.Create(aMasterDataSource.DataSet);
    with lkQr do
      begin
      Name        := obj_name_erp_data_qrcoments;
      DataBase    := FBDataBase;
      Transaction := lkTr;
      DataSource  := aMasterDataSource;
      AfterClose  := @DocComentsIntf_qrComents_AfterClose;
      SQL.Text := 
        'SELECT  JC.J_ID, JC.ID, JC.NAME, JC.FLAG_DELETE, JC.USER_ID, JC.DATE_CREATE '+#13#10+
        '       ,(SELECT FIRST 1 COALESCE(W.NAME, '''') FROM TABL$R_WRK W WHERE (W.USER_NAME = JC.USER_ID)) AS WRK_NAME '+#13#10+
        'FROM   TABL$J_COMENTS JC '+#13#10+
        'WHERE  (JC.J_ID = ?'+ERP_DATASET_DBKEY+') '+#13#10+
        'ORDER BY JC.ID';
      end
    lkDS := TDataSource.Create(aOwner);
    with lkDS do
      begin
      Name    := 'DataSource'+obj_name_erp_data_qrcoments;
      DataSet := lkQr;
      end;
    lkDBG := TDBGridEh.Create(aOwner);
    with lkDBG do
      begin
      Name            := obj_name_erp_data_dbgcoments;
      Parent          := Result;
      Align           := alClient;
      DataSource      := lkDS;
      Flat            := true;
      Color           := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color      := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style      := [fsBold];
      Font.Size       := 7;
      FixedColor      := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Options         := [dgTitles,dgColumnResize,dgColLines,dgRowLines,dgTabs,dgRowSelect,dgAlwaysShowSelection,dgConfirmDelete,dgCancelOnExit];
      TitleFont.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      TitleFont.Style := [fsBold];
      VTitleMargin    := 4;
      ShowHint        := true;
      UseMultiTitle   := true;
      OnGetCellParams := @ERP_DBGridEh_OnGetCellParams_JrnlComments;
      OnDblClick      := @DocComentsIntf_actUpd_OnExecute;
      end;
    lkCol := CreateTColumnEh(lkDBG,'ID'         ,'# ### ### ##0'      ,'Коментарии к документу|Код'        , 60,taRightJustify); lkCol.Title.SortMarker := smDownEh;
    lkCol := CreateTColumnEh(lkDBG,'NAME'       ,''                   ,'Коментарии к документу|Текст'      ,520,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'DATE_CREATE','dd.mm.yyyy hh:nn:ss','Коментарии к документу|Дата'       ,120,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'USER_ID'    ,''                   ,'Коментарии к документу|Пользователь|Имя'      ,126,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'WRK_NAME'   ,''                   ,'Коментарии к документу|Пользователь|Сотрудник',140,taLeftJustify );
    lkAct := CreateTAction(aOwner,obj_name_erp_actcomentins,msg_erp_actcomentins,msg_erp_actcomentins_hint,'',0,176); lkAct.OnExecute := @DocComentsIntf_actIns_OnExecute;   
    lkTBB := CreateTxcToolBarButton2(lkTopBar,lkTopBar,'tbb'+lkAct.Name,lkLBL.Left+lkLBL.Width,1,lkTopBar.Height-2,80,alLeft,lkAct);
    with lkTBB do
      begin
      StyleManager     := nil;
      ShowCaption      := true;
      Font.Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
      Colors.Border    := Amunhotep.MainForm.StyleManager.Colors.Window;
      Colors.Window    := Amunhotep.MainForm.StyleManager.Colors.HotTrack;
      Colors.Highlight := Amunhotep.MainForm.StyleManager.Colors.Border;
      end;
    lkAct := CreateTAction(aOwner,obj_name_erp_actcomentupd,msg_erp_actcomentupd,msg_erp_actcomentupd_hint,'',0,175); lkAct.OnExecute := @DocComentsIntf_actUpd_OnExecute;   
    lkTBB := CreateTxcToolBarButton2(lkTopBar,lkTopBar,'tbb'+lkAct.Name,lkTBB.Left+lkTBB.Width,1,lkTopBar.Height-2,80,alLeft,lkAct);
    with lkTBB do
      begin
      StyleManager     := nil;
      ShowCaption      := true;
      Font.Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
      Colors.Border    := Amunhotep.MainForm.StyleManager.Colors.Window;
      Colors.Window    := Amunhotep.MainForm.StyleManager.Colors.HotTrack;
      Colors.Highlight := Amunhotep.MainForm.StyleManager.Colors.Border;
      end;
    lkAct := CreateTAction(aOwner,obj_name_erp_actcomentdel,msg_erp_actcomentdel,msg_erp_actcomentdel_hint,'',0,177); lkAct.OnExecute := @DocComentsIntf_actDel_OnExecute;   
    lkTBB := CreateTxcToolBarButton2(lkTopBar,lkTopBar,'tbb'+lkAct.Name,lkTBB.Left+lkTBB.Width,1,lkTopBar.Height-2,80,alLeft,lkAct);
    with lkTBB do
      begin
      StyleManager     := nil;
      ShowCaption      := true;
      Font.Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
      Colors.Border    := Amunhotep.MainForm.StyleManager.Colors.Window;
      Colors.Window    := Amunhotep.MainForm.StyleManager.Colors.HotTrack;
      Colors.Highlight := Amunhotep.MainForm.StyleManager.Colors.Border;
      end;
    lkAct := CreateTAction(aOwner,obj_name_erp_actcomentrefresh,msg_erp_actviewrefresh,msg_erp_actviewrefresh,'',0,170); lkAct.OnExecute := @DocComentsIntf_actRefresh_OnExecute;   
    lkTBB := CreateTxcToolBarButton2(lkTopBar,lkTopBar,'tbb'+lkAct.Name,lkTBB.Left+lkTBB.Width,1,lkTopBar.Height-2,80,alLeft,lkAct);
    with lkTBB do
      begin
      StyleManager     := nil;
      ShowCaption      := true;
      Font.Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
      Colors.Border    := Amunhotep.MainForm.StyleManager.Colors.Window;
      Colors.Window    := Amunhotep.MainForm.StyleManager.Colors.HotTrack;
      Colors.Highlight := Amunhotep.MainForm.StyleManager.Colors.Border;
      end;
  end;
