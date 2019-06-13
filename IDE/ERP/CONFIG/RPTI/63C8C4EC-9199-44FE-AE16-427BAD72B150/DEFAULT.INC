{$DEFINE PEAKTOP:IDE/ERP/CONFIG/RPTI/63C8C4EC-9199-44FE-AE16-427BAD72B150/DEFAULT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}            {$I PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}    {$I PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}           {$I PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/CHECKBOX/INTF.INC}      {$I PEAKTOP:IDE/ERP/DBO/INPUT/CHECKBOX/INTF.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REG.INC} {$I PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REG.INC} {$ENDIF}
const
  objname_datefrom   = 'dtpDateFrom';
  objname_dateto     = 'dtpDateTo';
  objname_firms      = 'gbFirms';
  objname_places     = 'gbPlaces';
  objname_checksumm  = 'cbxCheckSumm';
  objname_checkparty = 'cbxCheckParty';
  objname_checkzero  = 'cbxCheckZero';
  msg_input_firms    = 'Выберите фирмы учета';
  msg_input_places   = 'Выберите места хранения';
  msg_input_summ     = 'Показать остатки суммарно по минимальной цене';
  msg_input_party    = 'Разворачивать по партиям';
  msg_input_zero     = 'Не показывать нулевые';
  //============================================================================
  procedure TERPFormRpti_actRefEdt_OnExecute(Sender :TObject);
  begin
    with TERPForm_ActiveDataSet(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      if(FieldByName('TMC_ID').AsInteger = 0)then exit;
      SetGlobalVariable('TMC_ID', FieldByName('TMC_ID').AsString);
      call(StrAbsolutePath('../../REF/TMC/DEFAULT_ITEM.PS', ScriptName));
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_actDocEdt_OnExecute(Sender :TObject);
  begin
    with TERPForm_ActiveDataSet(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      if(FieldByName('J_ID').AsInteger = 0)then exit;
      SetGlobalVariable('J_ID', FieldByName('J_ID').AsString);
      call('DB:CONFIG/DOC/'+FieldByName('J_TYPE_ID').AsString+'/EDIT.PS');
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_actJrnlGoTo_OnExecute(Sender :TObject);
  var
    lkScript :string;
  begin
    with TERPForm_ActiveDataSet(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      if(FieldByName('J_ID').AsInteger = 0)then exit;
      SetGlobalVariable('J_ID'+ERP_SETTINGS_GOTOVAR, FieldByName('J_ID').AsString);
      call('DB:CONFIG/DOC/'+FieldByName('J_TYPE_ID').AsString+'/DEFAULT.PS');
      end;
  end;
  //============================================================================
  function TERPFormRpti_GetExportFilter(aOwner:TComponent):string;
  begin
    Result := 'Остатки на дату "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+
      '"; Фирмы учета: "'+InputIntf_Ref_GetNames(aOwner.FindComponent(objname_firms))+
      '"; Места хранения: "'+InputIntf_Ref_GetNames(aOwner.FindComponent(objname_places))+'" '+#13#10;
    if(InputIntf_CheckBox_Checked(aOwner, objname_checksumm) = '1')then
      Result := Result + 'ВНИМАНИЕ: ОСТАТКИ ПРОСУММИРОВАНЫ БЕЗ РАЗРЕЗА ПО МЕСТАМ ХРАНЕНИЯ '
    else
      begin
      if(InputIntf_CheckBox_Checked(aOwner, objname_checkparty) = '1')then
        Result := Result + 'ВНИМАНИЕ: ОСТАТКИ В РАЗРЕЗЕ ПАРТИЙ ПОСТУПЛЕНИЯ ';
      end;
  end;
  //============================================================================
  function TERPFormRpti_OnGetSQL(aOwner:TComponent;var aSQL:string):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormRpti_OnGetSQLFileName(aOwner:TComponent;var aFileName:string);
  begin
    if(InputIntf_CheckBox_Checked(aOwner, objname_checksumm) = '1')then
      aFileName := StrAbsolutePath('./DEFAULT3.SQL', ScriptName)
     else 
      if(InputIntf_CheckBox_Checked(aOwner, objname_checkparty) = '1')then
        aFileName := StrAbsolutePath('./DEFAULT2.SQL', ScriptName)
       else 
        aFileName := StrAbsolutePath('./DEFAULT.SQL', ScriptName);
  end;
  //============================================================================
  procedure TERPFormRpti_OnProcessParams(aOwner:TComponent;aQr :TxFBQuery);
  begin
    with aQr do
      begin
      ParamByName('FIRM_IDS'   ).AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_firms));
      ParamByName('PLACE_IDS'  ).AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_places));
      ParamByName('DATE_FROM'  ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00';
      ParamByName('CHECK_PARTY').AsString := InputIntf_CheckBox_Checked(aOwner, objname_checkparty);
      ParamByName('CHECK_SUMM' ).AsString := InputIntf_CheckBox_Checked(aOwner, objname_checksumm);
      ParamByName('CHECK_ZERO' ).AsString := InputIntf_CheckBox_Checked(aOwner, objname_checkzero);
      end;  
  end;
  //============================================================================
  procedure TERPFormRpti_OnChart(aOwner:TComponent; aParent:TWinControl);
  var
    lkPC :TxcPageControlEx;
    lkTS :TxcTabSheet;
  begin
    aParent.Free;
    exit;
    lkPC := CreateTxcPageControlEx(aOwner, aParent, 'PCCharts', 0,0,600,600, alClient);
    lkPC.MultiLine := false;
    TxcPageControlEx_ActivateDefaultPage(lkPC);
  end;
  //============================================================================
  procedure TERPFormRpti_OnTerms(aOwner:TComponent;aParent:TWinControl);
  var
    lkLastTop :Integer;
  begin
    lkLastTop := 4;
    lkLastTop := lkLastTop + InputIntf_DatePeriod_Create(aOwner, aParent, 'gbDatePeriod', 'Укажите период', 4, lkLastTop, 44, 360,objname_datefrom,objname_dateto,StartOfTheMonth(Now),EndOfTheMonth(Now)).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_firms   ,msg_input_firms   ,  4,lkLastTop,  0,360,'TABL$R_FIRMS' ,TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := lkLastTop + InputIntf_CheckBox_Create  (aOwner,aParent,objname_checkparty,msg_input_party,4,lkLastTop, 20,360).Height;
    lkLastTop := lkLastTop + 20;
    with InputIntf_CheckBox_Create  (aOwner,aParent,objname_checksumm,msg_input_summ,4,lkLastTop, 20,360) do
      begin
      lkLastTop := lkLastTop + Height;
      Checked   := true;
      end;
    lkLastTop := lkLastTop + 4;
    with InputIntf_CheckBox_Create  (aOwner,aParent,objname_checkzero,msg_input_zero,4,lkLastTop, 20,360) do
      begin
      lkLastTop := lkLastTop + Height;
      Checked   := true;
      end;
    lkLastTop := lkLastTop + 4;

    lkLastTop := 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_places  ,msg_input_places  ,368,lkLastTop,380,360,'TABL$R_PLACES',TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
    TDateTimePicker(aOwner.FindComponent(objname_dateto  )).Visible := false;
    TDateTimePicker(aOwner.FindComponent(objname_datefrom)).Date    := Now + 1;
  end;
  //============================================================================
  function TERPFormRpti_OnColumnsCreate(aOwner:TComponent; aDBG:TDBGridEh):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormRpti_Columns_OnEditButtonClick(Sender :TObject; var Handled :Boolean);
  var
    lkDBG    :TDBGridEh;
    lkTypes  :string;
    lkPlace  :string;
    lkScript :string;
  begin
    Handled := true;
    lkDBG   := TDBGridEh(TComponent(Sender).Owner.Owner);
    if not lkDBG.DataSource.DataSet.Active then exit;
  end;
  //============================================================================
  procedure TERPFormRpti_OnColumnsCreated(aOwner:TComponent; aDBG:TDBGridEh);
  var
    lkToolBar :TxcGradientPanelVista;
    i :Integer; 
  begin
    lkToolBar := TxcGradientPanelVista(aOwner.FindComponent(obj_name_erp_toolbar_nav));
    TERPForm_CreateAction(aOwner,'actRefEdt'   ,'Редактировать','Редактировать карточку'    ,'',0,468,@TERPFormRpti_actRefEdt_OnExecute   ,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
    TERPForm_CreateAction(aOwner,'actDocEdt'   ,'Открыть'      ,'Открыть документ'          ,'',0,375,@TERPFormRpti_actDocEdt_OnExecute   ,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
    TERPForm_CreateAction(aOwner,'actJrnlGoTo' ,'В журнал'     ,'Перейти в журнал документа','',0,462,@TERPFormRpti_actJrnlGoTo_OnExecute ,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
    lkToolBar.Width      := TWinControl_AutoWidth(lkToolBar)+2;
    for i:=0 to aDBG.Columns.Count-1 do
      if(  (Pos('FIRM_'     , aDBG.Columns[i].FieldName) = 1) 
         or(Pos('PLACE_'    , aDBG.Columns[i].FieldName) = 1) 
         or(Pos('TMC_GROUP_', aDBG.Columns[i].FieldName) = 1) 
         or(Pos('TMC_CTGR_' , aDBG.Columns[i].FieldName) = 1) 
      )then
        aDBG.Columns[i].HideDuplicates := true;  
    aDBG.OnDblClick      := @TERPFormRpti_actRefEdt_OnExecute;
    aDBG.OnGetCellParams := @ERP_DBGridEh_OnGetCellParams_Reg;
  end;
  //============================================================================
  procedure TERPFormRpti_OnColumnsLoad(aOwner:TComponent; aDBG:TDBGridEh);
  begin
    // do nothing, default handler
  end;
  //============================================================================
  function TERPFormRpti_OnPrint(aOwner:TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormRpti_BeforePreview(aOwner:TComponent; aRpt:TxReport);
  begin
    // do nothing, default handler
  end;
