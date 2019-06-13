{$DEFINE PEAKTOP:IDE/ERP/CONFIG/RPTI/2327EF0D-781B-42E8-A8B4-609734DABED5/DEFAULT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}             {$I PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$I PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}     {$I PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/CHECKBOX/INTF.INC}       {$I PEAKTOP:IDE/ERP/DBO/INPUT/CHECKBOX/INTF.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/COMBOBOX.INC}            {$I PEAKTOP:IDE/ERP/DBO/INPUT/COMBOBOX.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}            {$I PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                            {$I PEAKTOP:OBJ/TLABEL.INC}                            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TEDIT.INC}                             {$I PEAKTOP:OBJ/TEDIT.INC}                             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                      {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC}                      {$ENDIF}
const
  objname_datefrom   = 'dtpDateFrom';
  objname_dateto     = 'dtpDateTo';
  objname_daterpt    = 'dtpDateRpt';
  objname_firms      = 'edtFirm';
  objname_cbx_krd    = 'cmbKredit';
  objname_check_qtr  = 'cbxQuoter';
  objname_check_o11  = 'cbxO11';
  objname_check_o12  = 'cbxO12';
  objname_cbx_o2x    = 'cmbO2X';
  objname_dpa        = 'edtDPA';
  objname_filepath   = 'edtFilePath';
  objname_regnum     = 'edtRegNumber';
  msg_input_firms    = 'Выберите фирму учета';
  msg_input_dpa      = 'Укажите отделение Министерства доходов и сборов';
  msg_input_filepath = 'Укажите каталог экспорта';
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
    Result := '';
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
    if(UpperCase(aQr.Name) = 'QRMAIN')then
      with aQr do
        begin
        ParamByName('FIRM_ID'    ).AsString := IntToStr(aOwner.FindComponent(objname_firms).Tag);
        ParamByName('DATE_FROM'  ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00';
        ParamByName('DATE_TO'    ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto)  )+' 23:59:59';
        ParamByName('DATE_RPT'   ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_daterpt) )+' 00:00:00';
        if(InputIntf_ComboBox_ItemIndex(aOwner, objname_cbx_krd) = 1)then
          ParamByName('FLAG_KRD' ).AsString := '0'
         else 
          ParamByName('FLAG_KRD' ).AsString := '1';
        ParamByName('FLAG_QUOTER').AsString := InputIntf_CheckBox_Checked(aOwner, objname_check_qtr);
        ParamByName('FLAG_O11'   ).AsString := InputIntf_CheckBox_Checked(aOwner, objname_check_o11);
        ParamByName('FLAG_O12'   ).AsString := InputIntf_CheckBox_Checked(aOwner, objname_check_o12);
        ParamByName('FLAG_O2X'   ).AsString := IntToStr(InputIntf_ComboBox_ItemIndex(aOwner, objname_cbx_o2x));
        ParamByName('REGNUM'     ).AsString := TEdit(aOwner.FindComponent(objname_regnum)).Text;
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
  procedure actExport_OnExecute(Sender :TObject);
  var
    lkOwner    :TComponent;
    lkFileName :string;
    lkFileExprt:string;
    lkXML      :string;
    lkXML101, lkXML102, lkXML103, lkXML104, lkXML105, lkXML106, lkXML107, lkXML108, lkXML109, lkXML110, lkXML111, lkXML112   :string;
    lkXML201, lkXML202, lkXML203, lkXML204, lkXML205, lkXML206, lkXML207, lkXML208, lkXML209, lkXML210, lkXML211, lkXML212   :string;
    lkDPACode  :string;
    lkStr      :string;
    lkTr       :TxFBTransaction;
    lkQrEnt    :TxFBQuery;
    lkQrRpt    :TxFBQuery;
    i, k       :Integer;
  begin
    lkOwner := TComponent(Sender).Owner;
    lkTr    := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        Add('isc_tpb_read_committed');
        Add('isc_tpb_read');
        Add('isc_tpb_rec_version');
        Add('isc_tpb_nowait');
        end;
      end;
    lkQrEnt := TxFBQuery.Create(lkTr);
    with lkQrEnt do
      begin
      SQL.Text := StringsLoadFromFile('PEAKTOP:IDE/ERP/CONFIG/DOC/4/RPT_DEFAULT01.SQL');
      Prepare;
      ParamByName('FIRM_ID').AsString := IntToStr(lkOwner.FindComponent(objname_firms).Tag);
      if not Active then try Open; except end;
      end;
    lkDPACode := '';
    GetField(FBDataBase, 'TABL$R_DPA', 'CODE', 'ID = '+IntToStr(lkOwner.FindComponent(objname_dpa).Tag), lkDPACode);
    lkFileName := 
      lkDPACode + lkQrEnt.FieldByName('ENT_CS_INN').AsString+
      'F1201506'+ 
      '1' +
      FormatFloat('000000000', StrToInt(StrCiphersOnlyInt(TEdit(lkOwner.FindComponent(objname_regnum)).Text )) )+ 
      '1'+
      FormatDateTime('mmyyyy', InputIntf_DatePeriod_Date(lkOwner, objname_datefrom))+
      lkDPACode + '.xml';
    lkFileExprt := TEdit(lkOwner.FindComponent(objname_filepath)).Text;
    i := Length(lkFileExprt);
    while((i > 0) and (  (lkFileExprt[i] = #$20) 
                       or(lkFileExprt[i] = #13) 
                       or(lkFileExprt[i] = #10)
                       or(lkFileExprt[i] = '/')
                       or(lkFileExprt[i] = '\')    
    ))do 
      begin
      Delete(lkFileExprt, i, 1);
      i := Length(lkFileExprt);
      end;
    lkFileExprt := lkFileExprt + '\' + lkFileName;  
    if FileExists(lkFileExprt) then
      if(Dialogs.MessageDlg('Файл "'+lkFileExprt+'" уже существует.'+#13#10+'Перезаписать ?', mtConfirmation, [mbYes, mbNo]) <> mrYes)then 
        begin
        if lkTr.InTransaction then
          lkTr.Commit;
        lkTr.Free;  
        exit;
        end;
    lkQrRpt := TxFBQuery.Create(lkTr);
    with lkQrRpt do
      begin
      Name     := 'qrMain'; // for checking params
      SQL.Text := StringsLoadFromFile(StrAbsolutePath('./DEFAULT.SQL', ScriptName));
      Prepare;
      TERPFormRpti_OnProcessParams(lkOwner, lkQrRpt);
      ParamByName('FLAG_KRD').AsString := '1';
      if not Active then try Open; except end;
      end;
    lkQrRpt.FetchAll;
    lkQrRpt.First;
    lkXML := 
      '<?xml version="1.0" encoding="windows-1251"?>'+SQLCRLF+
      '<DECLAR xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="F1201506.xsd">'+SQLCRLF+
      '  <DECLARHEAD>'+SQLCRLF+
      '    <TIN>'+lkQrEnt.FieldByName('ENT_CS_INN').AsString+'</TIN>'+SQLCRLF+
      '    <C_DOC>F12</C_DOC>'+SQLCRLF+
      '    <C_DOC_SUB>015</C_DOC_SUB>'+SQLCRLF+
      '    <C_DOC_VER>6</C_DOC_VER>'+SQLCRLF+
      '    <C_DOC_TYPE>0</C_DOC_TYPE>'+SQLCRLF+
      '    <C_DOC_CNT>'+lkQrRpt.FieldByName('REGNUM').AsString+'</C_DOC_CNT>'+SQLCRLF+
      '    <C_REG>'+IntToStr(StrToInt(Copy(lkDPACode,1,2)))+'</C_REG>'+SQLCRLF+
      '    <C_RAJ>'+IntToStr(StrToInt(Copy(lkDPACode,3,2)))+'</C_RAJ>'+SQLCRLF+
      '    <PERIOD_MONTH>'+IntToStr(StrToInt(FormatDateTime('mm', InputIntf_DatePeriod_Date(lkOwner, objname_datefrom))))+'</PERIOD_MONTH>'+SQLCRLF+
      '    <PERIOD_TYPE>1</PERIOD_TYPE>'+SQLCRLF+
      '    <PERIOD_YEAR>'+FormatDateTime('yyyy', InputIntf_DatePeriod_Date(lkOwner, objname_datefrom))+'</PERIOD_YEAR>'+SQLCRLF+
      '    <C_STI_ORIG>'+IntToStr(StrToInt(lkDPACode))+'</C_STI_ORIG>'+SQLCRLF+
      '    <C_DOC_STAN>1</C_DOC_STAN>'+SQLCRLF+
      '    <LINKED_DOCS xsi:nil="true"></LINKED_DOCS>'+SQLCRLF+
      '    <D_FILL>'+FormatDateTime('ddmmyyyy', InputIntf_DatePeriod_Date(lkOwner, objname_daterpt))+'</D_FILL>'+SQLCRLF+
      '    <SOFTWARE>OPZ 1.30.15</SOFTWARE>'+SQLCRLF+
      '  </DECLARHEAD>'+SQLCRLF+
      '  <DECLARBODY>'+SQLCRLF+
      '    <HZ>1</HZ>'+SQLCRLF+
      '    <HNP>1</HNP>'+SQLCRLF+
      '    <HZY>'+FormatDateTime('yyyy', InputIntf_DatePeriod_Date(lkOwner, objname_datefrom))+'</HZY>'+SQLCRLF+
      '    <HZM>'+IntToStr(StrToInt(FormatDateTime('mm', InputIntf_DatePeriod_Date(lkOwner, objname_datefrom))))+'</HZM>'+SQLCRLF+
      '    <HKV xsi:nil="true"></HKV>'+SQLCRLF+
      '    <HNAME>'+lkQrEnt.FieldByName('ENT_CS_NAME').AsString+'</HNAME>'+SQLCRLF+
      '    <HNPDV>'+lkQrEnt.FieldByName('ENT_CS_INN').AsString+'</HNPDV>'+SQLCRLF+
      '    <HNSPDV>'+lkQrEnt.FieldByName('ENT_CS_CERTIFICATE').AsString+'</HNSPDV>'+SQLCRLF;
    lkXML101 := ''; lkXML201 := '';
    lkXML102 := ''; lkXML202 := '';
    lkXML103 := ''; lkXML203 := '';
    lkXML104 := ''; lkXML204 := '';
    lkXML105 := ''; lkXML205 := '';
    lkXML106 := ''; lkXML206 := '';
    lkXML107 := ''; lkXML207 := '';
    lkXML108 := ''; lkXML208 := '';
    lkXML109 := ''; lkXML209 := '';
    lkXML110 := ''; lkXML210 := '';
    lkXML111 := ''; lkXML211 := '';
    lkXML112 := ''; lkXML212 := '';
    i := 1;
    while not lkQrRpt.EOF do
      begin
      lkXML101 := lkXML101+'    <T1RXXXXG1 ROWNUM="'+IntToStr(i)+'">'+IntToStr(i)+'</T1RXXXXG1>'+SQLCRLF; 
      lkXML102 := lkXML102+'    <T1RXXXXG2D ROWNUM="'+IntToStr(i)+'">'+FormatDateTime('ddmmyyyy', lkQrRpt.FieldByName('J_DATE_COMMIT').AsDateTime)+'</T1RXXXXG2D>'+SQLCRLF; 
      lkXML103 := lkXML103+'    <T1RXXXXG3S ROWNUM="'+IntToStr(i)+'">'+lkQrRpt.FieldByName('J_DOCNUMBER').AsString+'</T1RXXXXG3S>'+SQLCRLF; 
      if(lkQrRpt.FieldByName('J_TYPE_ID').AsString = '1000131')then
        lkXML104 := lkXML104+'    <T1RXXXXG41S ROWNUM="'+IntToStr(i)+'">ПНП</T1RXXXXG41S>'+SQLCRLF
       else  
        lkXML104 := lkXML104+'    <T1RXXXXG41S ROWNUM="'+IntToStr(i)+'">РКП</T1RXXXXG41S>'+SQLCRLF;
      if(lkQrRpt.FieldByName('J_FLAG_PNP02').AsInteger = 1)then
        lkXML105 := lkXML105+'				<T1RXXXXG42S ROWNUM="'+IntToStr(i)+'">02</T1RXXXXG42S>'+SQLCRLF
      lkXML106 := lkXML106+'    <T1RXXXXG5S ROWNUM="'+IntToStr(i)+'">'+lkQrRpt.FieldByName('J_CS_NAME2').AsString+'</T1RXXXXG5S>'+SQLCRLF; 
      if(lkQrRpt.FieldByName('J_FLAG_PNP02').AsInteger <> 1)then
        lkXML107 := lkXML107+'    <T1RXXXXG6 ROWNUM="'+IntToStr(i)+'">'+lkQrRpt.FieldByName('J_CS_INN').AsString+'</T1RXXXXG6>'+SQLCRLF; 
      lkXML108 := lkXML108+'    <T1RXXXXG7 ROWNUM="'+IntToStr(i)+'">'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_SUMNDP').AsFloat),',','.')+'</T1RXXXXG7>'+SQLCRLF; 
      lkXML109 := lkXML109+'    <T1RXXXXG8 ROWNUM="'+IntToStr(i)+'">'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_SUM'   ).AsFloat),',','.')+'</T1RXXXXG8>'+SQLCRLF; 
      lkXML110 := lkXML110+'    <T1RXXXXG9 ROWNUM="'+IntToStr(i)+'">'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_NDP'   ).AsFloat),',','.')+'</T1RXXXXG9>'+SQLCRLF; 
      i := i + 1;
      lkQrRpt.Next;
      end;
    lkXML112 :=
		'    <R011G7>'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_SUMNDPS').AsFloat),',','.')+'</R011G7>'+SQLCRLF+
		'    <R011G8>'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_SUMS'   ).AsFloat),',','.')+'</R011G8>'+SQLCRLF+
		'    <R011G9>'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_NDPS'   ).AsFloat),',','.')+'</R011G9>'+SQLCRLF+
    '    <R011G10 xsi:nil="true"></R011G10>'+SQLCRLF+
    '    <R011G11 xsi:nil="true"></R011G11>'+SQLCRLF+
    '    <R011G12 xsi:nil="true"></R011G12>'+SQLCRLF+
    '    <R011G13 xsi:nil="true"></R011G13>'+SQLCRLF+
    '    <R012G7 xsi:nil="true"></R012G7>'+SQLCRLF+
    '    <R012G8 xsi:nil="true"></R012G8>'+SQLCRLF+
    '    <R012G9 xsi:nil="true"></R012G9>'+SQLCRLF+
    '    <R012G10 xsi:nil="true"></R012G10>'+SQLCRLF+
    '    <R012G11 xsi:nil="true"></R012G11>'+SQLCRLF+
    '    <R012G12 xsi:nil="true"></R012G12>'+SQLCRLF+
    '    <R012G13 xsi:nil="true"></R012G13>'+SQLCRLF;
    with lkQrRpt do
      begin
      if not Active then try Close; except end;
      SQL.Text := StringsLoadFromFile(StrAbsolutePath('./DEFAULT.SQL', ScriptName));
      Prepare;
      TERPFormRpti_OnProcessParams(lkOwner, lkQrRpt);
      ParamByName('FLAG_KRD').AsString := '0';
      if not Active then try Open; except end;
      end;
    i := 1;
    lkQrRpt.FetchAll;
    lkQrRpt.First;
    while not lkQrRpt.EOF do
      begin
      lkXML201 := lkXML201+'    <T2RXXXXG1 ROWNUM="'+IntToStr(i)+'">'+IntToStr(i)+'</T2RXXXXG1>'+SQLCRLF; 
      lkXML202 := lkXML202+'    <T2RXXXXG2D ROWNUM="'+IntToStr(i)+'">'+FormatDateTime('ddmmyyyy', lkQrRpt.FieldByName('J_DATE_COMMIT').AsDateTime)+'</T2RXXXXG2D>'+SQLCRLF; 
      lkXML203 := lkXML203+'    <T2RXXXXG3D ROWNUM="'+IntToStr(i)+'">'+FormatDateTime('ddmmyyyy', lkQrRpt.FieldByName('J_DATE_IN'    ).AsDateTime)+'</T2RXXXXG3D>'+SQLCRLF; 
      lkXML204 := lkXML204+'    <T2RXXXXG4S ROWNUM="'+IntToStr(i)+'">'+lkQrRpt.FieldByName('J_DOCNUMBERIN').AsString+'</T2RXXXXG4S>'+SQLCRLF; 
      if(lkQrRpt.FieldByName('J_TYPE_ID').AsString = '1000132')then
        lkXML205 := lkXML205+'    <T2RXXXXG51S ROWNUM="'+IntToStr(i)+'">ПНП</T2RXXXXG51S>'+SQLCRLF
       else  
        lkXML205 := lkXML205+'    <T2RXXXXG51S ROWNUM="'+IntToStr(i)+'">РКП</T2RXXXXG51S>'+SQLCRLF;
      lkXML206 := lkXML206+'    <T2RXXXXG6S ROWNUM="'+IntToStr(i)+'">'+lkQrRpt.FieldByName('J_CS_NAME2').AsString+'</T2RXXXXG6S>'+SQLCRLF; 
      lkXML207 := lkXML207+'    <T2RXXXXG7 ROWNUM="'+IntToStr(i)+'">'+lkQrRpt.FieldByName('J_CS_INN').AsString+'</T2RXXXXG7>'+SQLCRLF; 
      lkXML208 := lkXML208+'    <T2RXXXXG8 ROWNUM="'+IntToStr(i)+'">'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_SUMNDP').AsFloat),',','.')+'</T2RXXXXG8>'+SQLCRLF; 
      lkXML209 := lkXML209+'    <T2RXXXXG9 ROWNUM="'+IntToStr(i)+'">'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_SUM'   ).AsFloat),',','.')+'</T2RXXXXG9>'+SQLCRLF; 
      lkXML210 := lkXML210+'    <T2RXXXXG10 ROWNUM="'+IntToStr(i)+'">'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_NDP'   ).AsFloat),',','.')+'</T2RXXXXG10>'+SQLCRLF; 
      i := i + 1;
      lkQrRpt.Next;
      end;
    lkXML212 :=
      '    <R021G8>'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_SUMNDPS').AsFloat),',','.')+'</R021G8>'+SQLCRLF+
      '    <R021G9>'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_SUMS'   ).AsFloat),',','.')+'</R021G9>'+SQLCRLF+
      '    <R021G10>'+StrReplaceStr(FormatFloat('#0.00', lkQrRpt.FieldByName('J_P_NDPS'  ).AsFloat),',','.')+'</R021G10>'+SQLCRLF+
      '    <R021G11 xsi:nil="true"></R021G11>'+SQLCRLF+
      '    <R021G12 xsi:nil="true"></R021G12>'+SQLCRLF+
      '    <R021G13 xsi:nil="true"></R021G13>'+SQLCRLF+
      '    <R021G14 xsi:nil="true"></R021G14>'+SQLCRLF+
      '    <R021G15 xsi:nil="true"></R021G15>'+SQLCRLF+
      '    <R021G16 xsi:nil="true"></R021G16>'+SQLCRLF+
      '    <R022G8 xsi:nil="true"></R022G8>'+SQLCRLF+
      '    <R022G9 xsi:nil="true"></R022G9>'+SQLCRLF+
      '    <R022G10 xsi:nil="true"></R022G10>'+SQLCRLF+
      '    <R022G11 xsi:nil="true"></R022G11>'+SQLCRLF+
      '    <R022G12 xsi:nil="true"></R022G12>'+SQLCRLF+
      '    <R022G13 xsi:nil="true"></R022G13>'+SQLCRLF+
      '    <R022G14 xsi:nil="true"></R022G14>'+SQLCRLF+
      '    <R022G15 xsi:nil="true"></R022G15>'+SQLCRLF+
      '    <R022G16 xsi:nil="true"></R022G16>'+SQLCRLF+
      '    <HFILL>'+FormatDateTime('ddmmyyyy', InputIntf_DatePeriod_Date(lkOwner, objname_daterpt))+'</HFILL>'+SQLCRLF+
      '    <HBUH xsi:nil="true"></HBUH>'+SQLCRLF+
      '    <HKBUH xsi:nil="true"></HKBUH>'+SQLCRLF+
      '    <HBOS>'+lkQrEnt.FieldByName('ENT_CS_NAME').AsString+'</HBOS>'+SQLCRLF;

    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;  
    lkXML := lkXML + 
      lkXML101+lkXML102+lkXML103+lkXML104+lkXML105+lkXML106+lkXML107+lkXML108+lkXML109+lkXML110+lkXML111+lkXML112+
      lkXML201+lkXML202+lkXML203+lkXML204+lkXML205+lkXML206+lkXML207+lkXML208+lkXML209+lkXML210+lkXML211+lkXML212+
      '  </DECLARBODY>'+SQLCRLF+'</DECLAR>';
    
    if StringsSaveToFile(lkFileExprt, lkXML) then 
      Dialogs.MessageDlg('Выгрузка "Регистра налоговых накладных" выполнена в файл ' + SQLCRLF + lkFileExprt, mtInformation, [mbOK]);
  end;
  //============================================================================
  procedure TERPFormRpti_edtFirm_OnButtonClick(Sender :TObject);
  var
    lkLastTop :Integer;
    lkGrb     :TxcGroupBox;
    lkEdt     :TxcEditCombo;
    lkStr     :string;
  begin
    with TxcEditCombo(Sender) do
      begin
      SetGlobalVariable('FIRM_ID', IntToStr(Tag));
      call(StrAbsolutePath('../../REF/FIRMS/DEFAULT_DLG.PS', ScriptName));
      lkStr := GetGlobalVariable('FIRM_ID');
      if( (UpperCase(lkStr) = 'NULL') or (StrTrimAll(lkStr)='') )then exit;
      Tag := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_FIRMS', 'NAME', 'ID = '+lkStr, lkStr);
      Text := lkStr;
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_edtDPA_OnButtonClick(Sender :TObject);
  var
    lkLastTop :Integer;
    lkGrb     :TxcGroupBox;
    lkEdt     :TxcEditCombo;
    lkStr     :string;
  begin
    with TxcEditCombo(Sender) do
      begin
      SetGlobalVariable('DPA_ID', IntToStr(Tag));
      call(StrAbsolutePath('../../REF/DPA/DEFAULT_DLG.PS', ScriptName));
      lkStr := GetGlobalVariable('DPA_ID');
      if( (UpperCase(lkStr) = 'NULL') or (StrTrimAll(lkStr)='') )then exit;
      Tag := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_DPA', '''[''||CODE||''] ''||NAME', 'ID = '+lkStr, lkStr);
      Text := lkStr;
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_OnTerms(aOwner:TComponent;aParent:TWinControl);
  var
    lkLastTop :Integer;
    lkGrb     :TxcGroupBox;
    lkEdt     :TxcEditCombo;
    lkLbl     :TLabel;
    lkFnEdt   :TEdit;
    lkTBB     :TxcToolBarButton;
    lkStr     :string;
  begin
    lkLastTop := 4;
    lkLastTop := lkLastTop + InputIntf_DatePeriod_Create(aOwner, aParent, 'gbDatePeriod', 'Укажите период'     , 4, lkLastTop, 44, 360,objname_datefrom,objname_dateto,StartOfTheMonth(Now),EndOfTheMonth(Now)).Height;
    lkLastTop := lkLastTop + 4;

    lkGrb     := CreateTxcGroupBox(aOwner, aParent, '', msg_input_firms,alNone,4,lkLastTop,48,360);
    lkLastTop := lkLastTop + lkGrb.Height + 4;
    lkStr     := '0'; 
    lkEdt := CreateTxcEditCombo(aOwner,lkGrb,objname_firms,TERPForm_DefaultControlIndent,20,20,lkGrb.Width-(TERPForm_DefaultControlIndent*2));
    with lkEdt do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      GlyphKind     := gkEllipsis;
      ReadOnly      := true;
      AlwaysEnable  := true;
      Font.Style    := [fsBold];
      Tag           := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_FIRMS', 'NAME', 'ID = '+lkStr, lkStr);
      Text          := lkStr;
      OnButtonClick := @TERPFormRpti_edtFirm_OnButtonClick;
      end;    

    lkLastTop := lkLastTop + InputIntf_DatePeriod_Create(aOwner, aParent, 'gbDateReport', 'Укажите дату отчета', 4, lkLastTop, 44, 360,objname_daterpt ,objname_daterpt+'1',Now,EndOfTheMonth(Now)).Height;
    lkLastTop := lkLastTop + 4;
    TDateTimePicker(aOwner.FindComponent(objname_daterpt+'1')).Visible := false;

    lkGrb     := InputIntf_ComboBox_Create(aOwner, aParent, 'grb'+objname_cbx_krd, 'Укажите страницу отчета',4,lkLastTop, 48,360, objname_cbx_krd,
      'Розділ I. Видані податкові накладні'+SQLCRLF+
      'Розділ ІІ. Отримані податкові накладні', 0);
    lkLastTop := lkLastTop + lkGrb.Height + 4;
    with InputIntf_CheckBox_Create  (aOwner,aParent,objname_check_o11, 'O11 Отчетная декларация',4,lkLastTop, 20,360) do
      begin
      Checked   := true;
      lkLastTop := lkLastTop + Height;
      end;
    lkLastTop := lkLastTop + 4;
    with InputIntf_CheckBox_Create  (aOwner,aParent,objname_check_o12, 'O12 Отчетная декларация новая',4,lkLastTop, 20,360) do
      begin
      Checked   := false;
      lkLastTop := lkLastTop + Height;
      end;
    lkLastTop := lkLastTop + 4;
    
    lkGrb     := InputIntf_ComboBox_Create(aOwner, aParent, 'grbO2X', 'Отметка о декларации',4,lkLastTop, 48,360, objname_cbx_o2x,
      '(0110) загальна'+SQLCRLF+
      '(0121-0123) спеціальний режим оподаткування'+SQLCRLF+
      '(0130) сільськогосподарське підприємство'+SQLCRLF+
      '(0140) спеціальний режим оподаткування переробного підприємства', 0);
    lkLastTop := lkLastTop + lkGrb.Height + 4;
    with InputIntf_CheckBox_Create  (aOwner,aParent,objname_check_qtr, 'Квартальный отчет',4,lkLastTop, 20,360) do
      begin
      Checked   := false;
      lkLastTop := lkLastTop + Height;
      end;
    lkLastTop := lkLastTop + 4;

    lkLastTop := 4;
    lkGrb     := CreateTxcGroupBox(aOwner, aParent, '', 'Номер регистра',alNone,368,lkLastTop,44,360);
    lkLastTop := lkLastTop + lkGrb.Height + 4;
    lkFnEdt   := CreateTEdit(aOwner, lkGrb, objname_regnum, TERPForm_DefaultControlIndent, 20, 20, lkGrb.Width-(TERPForm_DefaultControlIndent*2));        
    lkFnEdt.Text := '1';
    lkGrb     := CreateTxcGroupBox(aOwner, aParent, '', msg_input_dpa,alNone,368,lkLastTop,44,360);
    lkLastTop := lkLastTop + lkGrb.Height + 4;
    lkStr     := '1000210'; 
    lkEdt := CreateTxcEditCombo(aOwner,lkGrb,objname_dpa,TERPForm_DefaultControlIndent,20,20,lkGrb.Width-(TERPForm_DefaultControlIndent*2));
    with lkEdt do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      GlyphKind     := gkEllipsis;
      ReadOnly      := true;
      AlwaysEnable  := true;
      Font.Style    := [fsBold];
      Tag           := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_DPA', '''[''||CODE||''] ''||NAME', 'ID = '+lkStr, lkStr);
      Text          := lkStr;
      OnButtonClick := @TERPFormRpti_edtDPA_OnButtonClick;
      end; 
    lkGrb     := CreateTxcGroupBox(aOwner, aParent, '', msg_input_filepath,alNone,368,lkLastTop,80,360);
    lkLastTop := lkLastTop + lkGrb.Height + 4;
    lkFnEdt   := CreateTEdit(aOwner, lkGrb, objname_filepath, TERPForm_DefaultControlIndent, 20, 20, lkGrb.Width-(TERPForm_DefaultControlIndent*2));        
    if FileExists(StrAbsolutePath('..\conf\export_best_zvit.conf', Amunhotep.ExeName))then
      lkFnEdt.Text := StringsLoadFromFile(StrAbsolutePath('..\conf\export_best_zvit.conf', Amunhotep.ExeName))
     else   
      lkFnEdt.Text := 'D:\';
    lkLbl := CreateTLabel(lkGrb, lkGrb, 'Имя каталога экспорта можно задать одной строчкой в файле '+#13#10+
      '  '+StrAbsolutePath('..\conf\export_best_zvit.conf', Amunhotep.ExeName), 
      lkFnEdt.Left, lkFnEdt.Top+lkFnEdt.Height+TERPForm_DefaultControlIndent, 24, lkFnEdt.Width, alNone, taLeftJustify);
    lkLbl.Font.Color := clBlue;
    lkLbl.Font.Style := [fsBold];      

    lkTBB := CreateTxcToolBarButton(aOwner, aParent,'tbbExport','Экcпорт отчета в XML', 'Экcпорт отчета в XML',368,lkLastTop,20,360, alNone, 288, nil);
    with lkTBB do
      begin
      ShowHint    := true;
      ShowCaption := true;
      OnClick     := @actExport_OnExecute;
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
  procedure TERPFormRpti_OnColumnsCreated(aOwner:TComponent; aDBG:TDBGridEh);
  var
    lkToolBar :TxcGradientPanelVista;
    i :Integer; 
  begin
    lkToolBar := TxcGradientPanelVista(aOwner.FindComponent(obj_name_erp_toolbar_nav));
    TERPForm_CreateAction(aOwner,'actDocEdt'   ,'Открыть'      ,'Открыть документ'          ,'',0,375,@TERPFormRpti_actDocEdt_OnExecute   ,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
    TERPForm_CreateAction(aOwner,'actJrnlGoTo' ,'В журнал'     ,'Перейти в журнал документа','',0,462,@TERPFormRpti_actJrnlGoTo_OnExecute ,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
    lkToolBar.Width      := TWinControl_AutoWidth(lkToolBar)+2;

    with aDBG do
      begin
      OnDblClick      := @TERPFormRpti_actDocEdt_OnExecute;
      for i:=0 to Columns.Count-1 do
        begin
        if(UpperCase(Columns[i].FieldName) = 'J_FLAG_LOCK')then
          begin
          with Columns[i].KeyList do
            begin
            Clear;
            Add('1');
            Add('0');
            end;
          with Columns[i].PickList do
            begin
            Clear;
            Add('БЛОК');
            Add(' ');
            end;
          Columns[i].ImageList := CreateTImageList(aDBG, 'ilLock', [224, Amunhotep.MainForm.ImageListMain.Count-1]);  
          end;
        end;
    end;  
  end;
  //============================================================================
  procedure TERPFormRpti_OnColumnsLoad(aOwner:TComponent; aDBG:TDBGridEh);
  begin
    // do nothing, default handler
  end;
  //============================================================================
  function TERPFormRpti_OnPrint(aOwner:TComponent):Boolean;
  var
    lkRptPath  :string;
    lkResource :string;
    lkRpt      :TxReport;
  begin
    Result := true;
    if(InputIntf_ComboBox_ItemIndex(aOwner, objname_cbx_krd) = 0)then
      begin
      lkRptPath := 'PEAKTOP:IDE/ERP/CONFIG/RPTI/2327EF0D-781B-42E8-A8B4-609734DABED5/RPT_DEFAULT.XFM';
      end
     else 
      begin
      lkRptPath := 'PEAKTOP:IDE/ERP/CONFIG/RPTI/2327EF0D-781B-42E8-A8B4-609734DABED5/RPT_DEFAULT2.XFM';
      end;
    lkResource := StringsLoadFromFile(lkRptPath);
    if(lkResource = '')then
      begin
      WriteLn('ERROR LOAD :'+lkRptPath);  
      exit;
      end;
    lkRpt := TxReport(StrToComponent(lkResource));
    lkRpt.DataBase := FBDataBase;
    lkRpt.Title    := '';
    if(lkRpt.DataSets.Count < 2)then
      while(lkRpt.DataSets.Count < 2)do
        lkRpt.DataSets.Add;
    with lkRpt.DataSets[0] do
      begin
      Name         := 'qrMain';
      MasterDataSet:= '';
      SQL.Text     := TERPForm_QueryMain(aOwner).SQL.Text
      Query.Prepare;
      if(Query.Params.Count > 0)then
        TERPFormRpti_OnProcessParams(aOwner, Query);
      end;  
    with lkRpt.DataSets[1] do
      begin
      Name         := 'qrEnt';
      MasterDataSet:= 'qrMain';
      SQL.Text     := StringsLoadFromFile('PEAKTOP:IDE/ERP/CONFIG/DOC/4/RPT_DEFAULT01.SQL');
      end;  
    TERPFormRpti_BeforePreview(aOwner, lkRpt);  
    lkRpt.Prepare;
    lkRpt.Preview;
  end;
  //============================================================================
  procedure TERPFormRpti_BeforePreview(aOwner:TComponent; aRpt:TxReport);
  begin
    // do nothing, default handler
  end;
