{$DEFINE PEAKTOP:IDE/ERP/CONFIG/RPTI/E6EE37CE-3812-4D0D-AE8C-6734F1B2CCED/DEFAULT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}             {$I PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$I PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}     {$I PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}            {$I PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                      {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC}                      {$ENDIF}
const
  objname_datefrom   = 'dtpDateFrom';
  objname_dateto     = 'dtpDateTo';
  objname_firms      = 'gbFirms';
  objname_acc        = 'edtACC';
  msg_input_firms    = '�������� ����� �����';
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
  function TERPFormRpti_GetExportFilter(aOwner:TComponent):string;
  begin
    Result := 
      msg_erp_lbldatefrom+' "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+'" '+
      msg_erp_lbldateto  +' "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto))+'" '+
      '����� �����: "'+InputIntf_Ref_GetNames(aOwner.FindComponent(objname_firms))+
      '" ���� �����: "'+TxcEditCombo(aOwner.FindComponent(objname_acc)).Text+'"';
  end;
  //============================================================================
  function TERPFormRpti_OnGetSQL(aOwner:TComponent;var aSQL:string):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormRpti_OnGetSQLFileName(aOwner:TComponent;var aFileName:string);
  begin
     // do nothing, default handler
  end;
  //============================================================================
  procedure TERPFormRpti_OnProcessParams(aOwner:TComponent;aQr :TxFBQuery);
  begin
    with aQr do
      begin
      ParamByName('FIRM_IDS' ).AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_firms));
      ParamByName('DATE_FROM').AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00';
      ParamByName('DATE_TO'  ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto)+1)+' 00:00:00';
      ParamByName('ACC_ID'   ).AsString := IntToStr(aOwner.FindComponent(objname_acc).Tag);
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
  procedure TERPFormRpti_edtACC_OnButtonClick(Sender :TObject);
  var
    lkLastTop :Integer;
    lkGrb     :TxcGroupBox;
    lkEdt     :TxcEditCombo;
    lkStr     :string;
  begin
    with TxcEditCombo(Sender) do
      begin
      SetGlobalVariable('ACC_ID', IntToStr(Tag));
      call('DB:CONFIG/REF/BUHG_ACCS/DEFAULT_DLG.PS');
      lkStr := GetGlobalVariable('ACC_ID');
      if( (UpperCase(lkStr) = 'NULL') or (StrTrimAll(lkStr)='') )then exit;
      Tag := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_BUHG_ACCS', 'NAME', 'ID = '+lkStr, lkStr);
      Text := lkStr;
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_OnTerms(aOwner:TComponent;aParent:TWinControl);
  var
    lkLastTop :Integer;
    lkGrb     :TxcGroupBox;
    lkEdt     :TxcEditCombo;
    lkStr     :string;
  begin
    lkLastTop := 4;
    lkLastTop := lkLastTop + InputIntf_DatePeriod_Create(aOwner, aParent, 'gbDatePeriod', '������� ������', 4, lkLastTop, 44, 360,objname_datefrom,objname_dateto,StartOfTheMonth(Now),EndOfTheMonth(Now)).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_firms   ,msg_input_firms   ,4,lkLastTop, 0,360,'TABL$R_FIRMS',TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
    lkGrb     := CreateTxcGroupBox(aOwner, aParent, '', '�������� ���� �����',alNone,4,lkLastTop,48,360);
    lkLastTop := lkLastTop + lkGrb.Height + 4;
    lkStr     := '361'; 
    lkEdt := CreateTxcEditCombo(aOwner,lkGrb,objname_acc,TERPForm_DefaultControlIndent,20,20,lkGrb.Width-(TERPForm_DefaultControlIndent*2));
    with lkEdt do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      GlyphKind     := gkEllipsis;
      ReadOnly      := true;
      AlwaysEnable  := true;
      Font.Style    := [fsBold];
      Tag           := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_BUHG_ACCS', 'NAME', 'ID = '+lkStr, lkStr);
      Text          := lkStr;
      OnButtonClick := @TERPFormRpti_edtACC_OnButtonClick;
      end;
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
  procedure TERPFormRpti_DBGridEh_OnGetCellParams(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
    if(Column.Tag = 666)then exit;
    if(not(Column.Field.DataSet.Active))then exit;
    if(Column.Field.DataSet.RecordCount = 0)then exit;
    if(Column.Field.DataSet.FieldByName('FLAG').AsInteger = 1)then
      aFont.Style := [fsBold];
    if( (UpperCase(Column.FieldName) = 'DEBET') or (UpperCase(Column.FieldName) = 'KREDIT') or (UpperCase(Column.FieldName) = 'SALDO'))then
      begin
      aFont.Style := [fsBold];
      if(Column.Field.AsFloat = 0)then
        aFont.Color := Background
       else 
        if(Column.Field.AsFloat < 0)then
          aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Error;
      end;   
    if(Pos('J_', UpperCase(Column.FieldName)) = 1)then
      ERP_DBGridEh_OnGetCellParams_Jrnl(Sender, Column, AFont, Background, State)
  end;  
  //============================================================================
  procedure TERPFormRpti_OnColumnsCreated(aOwner:TComponent; aDBG:TDBGridEh);
  var
    i :Integer;
    lkToolBar :TxcGradientPanelVista; 
  begin
    lkToolBar := TxcGradientPanelVista(aOwner.FindComponent(obj_name_erp_toolbar_nav));
    TERPForm_CreateAction(aOwner,'actDocEdt'  ,'�������' ,'������� ��������'          ,'',0,375,@TERPFormRpti_actDocEdt_OnExecute  ,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
//    TERPForm_CreateAction(aOwner,'actJrnlGoTo','� ������','������� � ������ ���������','',0,462,@TERPFormRpti_actJrnlGoTo_OnExecute,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
    lkToolBar.Width := TWinControl_AutoWidth(lkToolBar)+2;  
    with aDBG do
      begin
      OptionsEh       := OptionsEh - [dghAutoSortMarking, dghMultiSortMarking];
      OnGetCellParams := @TERPFormRpti_DBGridEh_OnGetCellParams;
      OnDblClick      := @TERPFormRpti_actDocEdt_OnExecute;
      end;
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
