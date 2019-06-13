{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/DEFAULT_PANEL.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                       {$I PEAKTOP:GLOBAL_VARIABLES.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                         {$I PEAKTOP:GLOBAL_OBJECTS.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                             {$I PEAKTOP:OBJ/TLABEL.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TEDIT.INC}                              {$I PEAKTOP:OBJ/TEDIT.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                       {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                            {$I PEAKTOP:OBJ/TACTION.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                          {$I PEAKTOP:OBJ/TCOLUMNEH.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                          {$I PEAKTOP:OBJ/TDBGRIDEH.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}              {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}{$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                           {$I PEAKTOP:OBJ/TXCPANEL.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                   {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}                {$I ../../OBJECTNAMES.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}       {$I ../../$COMMON/FORMERP_LANG.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}      {$I ../../$COMMON/FORMERP_NAMES.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_CONST.INC}      {$I ../../$COMMON/FORMERP_CONST.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$I ../../$COMMON/FORMERP.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/GLOBALVARIABLES.INC} {$I ./GLOBALVARIABLES.INC}                {$ENDIF}
  //================ PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/DEFAULT.INC ==============
  procedure LocalizationIntf_edtLang_OnButtonClick(Sender :TObject);
  var
    lkStr :string;
  begin
    with TxcEditCombo(Sender) do
      begin
      SetGlobalVariable('COUNTRY_ID', IntToStr(Tag));
      call('PEAKTOP:IDE/ERP/CONFIG2/REF/COUNTRIES/DEFAULT_DLG.PS');
      lkStr := GetGlobalVariable('COUNTRY_ID');
      if( (UpperCase(lkStr) = 'NULL') or (StrTrimAll(lkStr)='') )then exit;
      Tag := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_COUNTRIES', 'NAME', 'ID = '+lkStr, lkStr);
      Text := lkStr;
      end;
  end;
  //============================================================================
  function LocalizationIntf_InputQueryStr(const ACaption, aPrompt:string; var aValue, aLang:string):Boolean;
  var
    lkForm :TForm;
    lkTop  :Integer;
    lkLbl  :TLabel;
    lkLang :TxcEditCombo;
    lkEdt  :TEdit;
    lkStr  :string;
  begin
    lkForm := TERPForm_Create(aCaption, '', 'PEAKTOP:IMG/CONFIG/ERP/LOCALIZATION0032X0032.BMP', true, nil);
    with lkForm do
      begin
      Width := 720;
      Height:= 120;
      end;
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      Caption := #$20#$20#$20#$20#$20#$20+aPrompt;
      lkTop   := Top + Height + 2;
      end;
    lkEdt := CreateTEdit(lkForm, lkForm, 'Edt', 4, lkTop, 20, lkForm.Width - 8);
    with lkEdt do
      begin
      Anchors   := [akLeft, akTop, akRight];
      Font.Name := 'Courier New';
      Font.Size := 8;
      Font.Style:= [fsBold];
      Text      := aValue;
      lkTop     := Top + Height + 4;
      end;
    lkLbl := CreateTLabel(lkForm,lkForm,'язык локализации',4,lkTop,20, 120,alNone,taLeftJustify);
    with lkLbl do
      begin
      Font.Name := 'Courier New';
      Font.Size := 8;
      Font.Style:= [fsBold];
      lkTop     := Top + Height + 4;
      end;
    lkLang := CreateTxcEditCombo(lkForm, lkForm, 'Lang', 128, lkLbl.Top, lkLbl.Height, lkForm.Width - 148);
    with lkLang do
      begin
      Anchors   := [akLeft, akTop, akRight];
      Font.Name := 'Courier New';
      Font.Size := 8;
      Font.Style:= [fsBold];
      GlyphKind     := gkEllipsis;
      ReadOnly      := true;
      AlwaysEnable  := true;
      Tag           := StrToInt(aLang);
      GetField(FBDataBase, 'TABL$R_COUNTRIES', 'COALESCE(LANG_NAME, NAME)', 'ID = '+aLang, lkStr);
      Text          := lkStr;
      OnButtonClick := @LocalizationIntf_edtLang_OnButtonClick;
      end;
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      aValue := lkEdt.Text;
      aLang  := IntToStr(lkLang.Tag);
      end;
    lkForm.Free;
  end;
  //============================================================================
  function LocalizationIntf_qrlocal(aOwner:TComponent):TxFBQuery;
  begin
    Result := TxFBQuery(TDBGridEh(aOwner.FindComponent(obj_name_erp_data_dbglocal)).DataSource.DataSet);
  end;
  //============================================================================
  procedure LocalizationIntf_Refresh(aOwner :TComponent);
  begin
    with LocalizationIntf_qrlocal(aOwner) do
      begin
      if Transaction.InTransaction then
        Transaction.Commit;
      try Open; except end;  
      end;
  end;
  //============================================================================
  procedure LocalizationIntf_qrlocal_AfterClose(DataSet :TDataSet);
  begin
    with TxFBQuery(DataSet).Transaction do
      if InTransaction then
        Commit;
  end;
  //============================================================================
  procedure LocalizationIntf_actIns_OnExecute(Sender :TObject);
  var 
    lkStr :string;
    lkLang:string;
  begin
    with LocalizationIntf_qrlocal(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkLang := '1000071';
      lkStr  := '';
      if(FindField('NAME') <> nil)then
        lkStr:= FieldByName('NAME').AsString;
      end;
    if LocalizationIntf_InputQueryStr(msg_erp_actlocalins_hint,msg_erp_enter_new_local, lkStr, lkLang) then
      begin
      if(Length(lkStr) > 254)then lkStr := Copy(lkStr, 1, 254);
      lkStr := StrReplaceStr(lkStr, #13#10, #$20);
      lkStr := StrReplaceStr(lkStr, '''', '''''');
      ExecSQL(LocalizationIntf_qrlocal(TComponent(Sender).Owner).DataBase, 'INSERT INTO TABL$_LOCAL(OBJ_ID, COL_ID, REC_ID, COUNTRY_ID, NAME) VALUES ('''+
        LocalizationIntf_qrlocal(TComponent(Sender).Owner).Settings[0]+''', ''NAME'', '''+
        LocalizationIntf_qrlocal(TComponent(Sender).Owner).DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+''', '''+
        lkLang+''', '''+lkStr+''')');
      LocalizationIntf_Refresh(TComponent(Sender).Owner);
      end;    
  end;
  //============================================================================
  procedure LocalizationIntf_actUpd_OnExecute(Sender :TObject);
  var 
    lkLang:string;
    lkStr :string;
    lkID  :string;
  begin
    with LocalizationIntf_qrlocal(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount > 0)then exit;
      lkStr := FieldByName('NAME').AsString;
      lkLang:= FieldByName('COUNTRY_ID').AsString;
      lkID  := FieldByName('ID').AsString;
      end;   
    if LocalizationIntf_InputQueryStr(msg_erp_actlocalupd_hint,msg_erp_enter_new_local,lkStr,lkLang) then
      begin
      if(Length(lkStr) > 254)then lkStr := Copy(lkStr, 1, 254);
      lkStr := StrReplaceStr(lkStr, #13#10, #$20);
      lkStr := StrReplaceStr(lkStr, '''', '''''');
      ExecSQL(LocalizationIntf_qrlocal(TComponent(Sender).Owner).DataBase, 
        'UPDATE TABL$_LOCAL L SET L.NAME = '''+lkStr+''', L.COUNTRY_ID = '''+lkLang+''' WHERE (L.ID = '+lkID+')');
      LocalizationIntf_Refresh(TComponent(Sender).Owner);
      end; 
  end;
  //============================================================================
  procedure LocalizationIntf_actDel_OnExecute(Sender :TObject);
  var 
    lkStr :string;
    lkLang:string;
    lkID  :string;
  begin
    with LocalizationIntf_qrlocal(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount > 0)then exit;
      lkStr := FieldByName('NAME').AsString;
      lkLang:= FieldByName('COUNTRY_NAME').AsString;
      lkID  := FieldByName('ID').AsString;
      end;       
    if Dialogs.MessageDlg(msg_erp_actlocaldel_hint+SQLCRLF+lkLang+': "'+lkStr+'" ?', mtConfirmation, [mbYes, mbNo]) = mrYes then
      begin
      ExecSQL(LocalizationIntf_qrlocal(TComponent(Sender).Owner).DataBase, 'DELETE FROM TABL$_LOCAL L WHERE (L.ID = '+lkID+')');
      LocalizationIntf_Refresh(TComponent(Sender).Owner);
      end; 
  end;
  //============================================================================
  procedure LocalizationIntf_actRefresh_OnExecute(Sender :TObject);
  begin
    LocalizationIntf_Refresh(TComponent(Sender).Owner);
  end;
  //============================================================================
  function LocalizationIntf_Create(aOwner:TComponent; aParent:TWinControl; aMasterDataSource:TDataSource; const aObjId :string):TxcPanel;
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
    Result := CreateTxcPanel(aOwner, aParent, obj_name_erp_panellocal, '', alClient,0,0,200,200,xbsNone);
    lkTopBar := CreateTxcGradientPanelVista(Result,Result,'','',alTop, 0,0,24,200,xbsRaized);
    with lkTopBar do
      begin
      Font.Size  := 7;
      Font.Style := [fsBold];
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Window;
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_REF);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_REF);
      end;
    lkLbl := CreateTLabel(lkTopBar,lkTopBar,#$20+msg_erp_localization,0,0,20,120,alLeft,taLeftJustify);
    lkLbl.Font.Color := Amunhotep.MainForm.StyleManager.Colors.Window;
    lkLbl.Font.Size  := 10;  
    lkTr := TxFBTransaction.Create(aOwner);
    with lkTr do
      begin
      Name            := obj_name_erp_data_trlocal;
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
      Name        := obj_name_erp_data_qrlocal;
      DataBase    := FBDataBase;
      Transaction := lkTr;
      DataSource  := aMasterDataSource;
      AfterClose  := @LocalizationIntf_qrlocal_AfterClose;
      SQL.Text := 
        'SELECT L.ID, L.NAME, L.FLAG_DELETE, L.OBJ_ID, L.COL_ID, L.REC_ID, L.COUNTRY_ID '+SQLCRLF+
        '      ,(SELECT FIRST 1 C.NAME      FROM TABL$R_COUNTRIES C WHERE (C.ID = L.COUNTRY_ID) )AS COUNTRY_NAME '+SQLCRLF+
        '      ,(SELECT FIRST 1 C.LANG_NAME FROM TABL$R_COUNTRIES C WHERE (C.ID = L.COUNTRY_ID) )AS LANG_NAME '+SQLCRLF+
        'FROM   TABL$_LOCAL L '+SQLCRLF+
        'WHERE  (L.OBJ_ID = '''+aObjId+''') '+SQLCRLF+
        '  AND  (L.REC_ID = ?'+ERP_DATASET_DBKEY+') '+SQLCRLF+
        'ORDER BY COUNTRY_NAME ';
      Settings.Clear;
      Settings.Add(aObjId);  
      end
    lkDS := TDataSource.Create(aOwner);
    with lkDS do
      begin
      Name    := 'DataSource'+obj_name_erp_data_qrlocal;
      DataSet := lkQr;
      end;
    lkDBG := TDBGridEh.Create(aOwner);
    with lkDBG do
      begin
      Name            := obj_name_erp_data_dbglocal;
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
      OnDblClick      := @LocalizationIntf_actUpd_OnExecute;
      end;
    lkCol := CreateTColumnEh(lkDBG,'ID'          ,'# ### ### ##0'      ,'код'                   , 60,taRightJustify);
    lkCol := CreateTColumnEh(lkDBG,'NAME'        ,''                   ,'название элемента'     ,420,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'COUNTRY_NAME',''                   ,'страна'                , 96,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'LANG_NAME'   ,''                   ,'€зык'                  ,120,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'COL_ID'      ,''                   ,'столбец'               , 80,taLeftJustify );
    lkAct := CreateTAction(aOwner,obj_name_erp_actlocalins,msg_erp_actlocalins,msg_erp_actlocalins_hint,'',0,176); lkAct.OnExecute := @LocalizationIntf_actIns_OnExecute;   
    lkTBB := CreateTxcToolBarButton2(lkTopBar,lkTopBar,'tbb'+lkAct.Name,lkLBL.Left+lkLBL.Width,1,lkTopBar.Height-2,80,alLeft,lkAct);
    with lkTBB do
      begin
      StyleManager     := nil;
      ShowCaption      := true;
      Font.Color       := lkTopBar.Font.Color;
      Colors.Border    := lkTopBar.Colors.Window;
      Colors.Window    := lkTopBar.Colors.HotTrack;
      Colors.Highlight := lkTopBar.Colors.Border;
      end;
    lkAct := CreateTAction(aOwner,obj_name_erp_actlocalupd,msg_erp_actlocalupd,msg_erp_actlocalupd_hint,'',0,175); lkAct.OnExecute := @LocalizationIntf_actUpd_OnExecute;   
    lkTBB := CreateTxcToolBarButton2(lkTopBar,lkTopBar,'tbb'+lkAct.Name,lkTBB.Left+lkTBB.Width,1,lkTopBar.Height-2,80,alLeft,lkAct);
    with lkTBB do
      begin
      StyleManager     := nil;
      ShowCaption      := true;
      Font.Color       := lkTopBar.Font.Color;
      Colors.Border    := lkTopBar.Colors.Window;
      Colors.Window    := lkTopBar.Colors.HotTrack;
      Colors.Highlight := lkTopBar.Colors.Border;
      end;
    lkAct := CreateTAction(aOwner,obj_name_erp_actlocaldel,msg_erp_actlocaldel,msg_erp_actlocaldel_hint,'',0,177); lkAct.OnExecute := @LocalizationIntf_actDel_OnExecute;   
    lkTBB := CreateTxcToolBarButton2(lkTopBar,lkTopBar,'tbb'+lkAct.Name,lkTBB.Left+lkTBB.Width,1,lkTopBar.Height-2,80,alLeft,lkAct);
    with lkTBB do
      begin
      StyleManager     := nil;
      ShowCaption      := true;
      Font.Color       := lkTopBar.Font.Color;
      Colors.Border    := lkTopBar.Colors.Window;
      Colors.Window    := lkTopBar.Colors.HotTrack;
      Colors.Highlight := lkTopBar.Colors.Border;
      end;
    lkAct := CreateTAction(aOwner,obj_name_erp_actlocalrefresh,msg_erp_actviewrefresh,msg_erp_actviewrefresh,'',0,170); lkAct.OnExecute := @LocalizationIntf_actRefresh_OnExecute;   
    lkTBB := CreateTxcToolBarButton2(lkTopBar,lkTopBar,'tbb'+lkAct.Name,lkTBB.Left+lkTBB.Width,1,lkTopBar.Height-2,80,alLeft,lkAct);
    with lkTBB do
      begin
      StyleManager     := nil;
      ShowCaption      := true;
      Font.Color       := lkTopBar.Font.Color;
      Colors.Border    := lkTopBar.Colors.Window;
      Colors.Window    := lkTopBar.Colors.HotTrack;
      Colors.Highlight := lkTopBar.Colors.Border;
      end;
  end;
