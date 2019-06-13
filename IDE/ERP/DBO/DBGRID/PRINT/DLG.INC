{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/DLG.INC}
{$IFNDEF PEAKTOP:OBJ/TXCDBLABEL.INC}                    {$I PEAKTOP:OBJ/TXCDBLABEL.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                  {$I PEAKTOP:OBJ/TXFBDATASETS.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                     {$I PEAKTOP:OBJ/TCOLUMNEH.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                     {$I PEAKTOP:OBJ/TDBGRIDEH.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}              {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}       {$I ../../$COMMON/FORMERP.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC} {$I ../../USERS/GLOBALVARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/OBJNAMES.INC} {$I ./OBJNAMES.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/CONST.INC}    {$I ./CONST.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/LANG.INC}     {$I ./LANG.INC}                       {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/DLG.INC ================
  procedure TERPDialogPrint_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end;
  //============================================================================
  function TERPDialogPrint_Create(const aTypeId:Integer; const aObjId, aSubType, aUserId :string):TForm;
  var
    lkFileName :string;
    lkTr       :TxFBTransaction;
    lkQr       :TxFBQuery;
    lkDS       :TDataSource;
    lkDBG      :TDBGridEh;
    lkCol      :TColumnEh;
    lkPnl      :TxcGradientPanel;
    lkDBLbl    :TxcDBLabel;
  begin
    Result := TERPForm_Create(msg_print_dialog_doc_caption,ERP_ObjectPreviewIcon(aTypeId),ERP_ObjectPreviewBitmap(aTypeId),true,@TERPDialogPrint_OnClose);
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(aTypeId);
      Colors.HotTrackBorder := ERP_ObjectColor(aTypeId);
      end;  
    TForm_Position_Load(Result, PrepareAbsoleteFileName('TMP:'+ERP_FILENAME_CFG_DIALOGPRINT), 290, 720);
    CreateTxFBTransQuery(Result,'trDlg','qrDlg','DSqrDlg',['isc_tpb_read_committed','isc_tpb_read','isc_tpb_rec_version','isc_tpb_nowait'], lkTr, lkQr, lkDS);
    lkFileName := PrepareAbsoleteFileName(ERP_ObjectPreviewSQL(aTypeId));
    if FileExists(lkFileName)then
      with lkQr do
        begin
        SQL.Text := StringsLoadFromFile(lkFileName);
        Prepare;
        ParamByName('OBJ_ID').AsString  := aObjId;
        ParamByName('USER_ID').AsString := aUserId;
        ParamByName('SUBTYPE').AsString := aSubType;
        end;
    lkDBG   := CreateTDBGridEh(Result,Result,lkDS,'dbgDlg',0,0,200,200,alClient);
    with lkDBG do
      begin
      VTitleMargin := 4;
      Options    := Options + [dgRowSelect, dgAlwaysShowSelection] - [dgMultiSelect, dgIndicator];
      OptionsEh  := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghAutoSortMarking, dghMultiSortMarking, dghIncSearch, dghRowHighlight, dghColumnResize, dghColumnMove,dghExtendVertLines];
      OnDblClick := @TERPForm_actOk_OnExecute;
      end;    
    lkCol   := CreateTColumnEh(lkDBG,'NAME','',msg_print_dialog_report_name,440,taLeftJustify);
    lkCol   := CreateTColumnEh(lkDBG,'PATH','',msg_print_dialog_report_path,860,taLeftJustify);
    lkPnl   := CreateTxcGradientPanel(Result, Result, '', '', alBottom, 0, 0, 96, 200, xbsNone, gdTopToBottom);
    lkDBLbl := CreateTxcDBLabel(Result,lkPnl,lkDS,'DESCR',0,0,lkPnl.Height,lkPnl.Width,alClient,taLeftJustify);
    with lkDBLbl do
      begin
      Layout    := tlTop;
      TextStyle := tsRecessed;
      end;
    try
      lkQr.Open;
    finally
      lkQr.FetchAll;
      lkQr.First;
    end;  
    Result.ActiveControl := lkDBG;
  end;
  //============================================================================
  function TERPDialogPrint_Execute(const aTypeId:Integer; const aObjId, aSubType, aUserId :string; var aRptId,aRptName,aRptPath:string):Boolean;
  var
    lkForm :TForm;
  begin
    Result := false;
    if not FileExists(PrepareAbsoleteFileName(ERP_ObjectPreviewSQL(aTypeId)))then
      begin
      Dialogs.MessageDlg(msg_print_dialog_error_sql001+PrepareAbsoleteFileName(ERP_ObjectPreviewSQL(aTypeId)), mtError, [mbOk]);
      exit;   
      end;
    lkForm := TERPDialogPrint_Create(aTypeId, aObjId, aSubType, aUserId);   
    with TxFBQuery(TxFBTransaction(lkForm.FindComponent('trDlg')).FindComponent('qrDlg')) do
      begin
      if(not(RecordCount>0))then
        begin
        Result := false;
        lkForm.Free;
        exit;
        end;
      if(RecordCount = 1)then
        begin
        aRptId   := FieldByName('ID'  ).AsString;
        aRptName := FieldByName('NAME').AsString;
        aRptPath := FieldByName('PATH').AsString;
        Result   := true;
        lkForm.Free;
        exit;
        end;
      end;
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      with TxFBQuery(TxFBTransaction(lkForm.FindComponent('trDlg')).FindComponent('qrDlg'))do
        begin
        aRptId   := FieldByName('ID'  ).AsString;
        aRptName := FieldByName('NAME').AsString;
        aRptPath := FieldByName('PATH').AsString;
        end;
    TForm_Position_Save(lkForm, PrepareAbsoleteFileName('TMP:'+ERP_FILENAME_CFG_DIALOGPRINT));    
    lkForm.Free;
  end;
  //============================================================================
  function TERPDialogPrint_ExecuteDefaultItem(var aRptId,aRptName,aRptPath:string):Boolean;
  var
    lkTypeId :Integer;
  begin
    try
      lkTypeId := StrToInt(GetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_TYPE));
    except
      lkTypeId := 0;
    end;
    Result := TERPDialogPrint_Execute(lkTypeId, GetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_NAME), '0', GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT),aRptId,aRptName,aRptPath);
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_TYPE,'0');
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_NAME,'' );
  end; 
  //============================================================================
  function TERPDialogPrint_ExecuteDefault(var aRptId,aRptName,aRptPath:string):Boolean;
  var
    lkTypeId :Integer;
  begin
    try
      lkTypeId := StrToInt(GetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_TYPE));
    except
      lkTypeId := 0;
    end;
    Result := TERPDialogPrint_Execute(lkTypeId, GetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_NAME), '1', GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT),aRptId,aRptName,aRptPath);
//    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_TYPE,'0');
//    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_NAME,'' );
  end;     
