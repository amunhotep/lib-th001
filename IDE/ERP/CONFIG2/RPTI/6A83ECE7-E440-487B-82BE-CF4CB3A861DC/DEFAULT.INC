{$DEFINE DB:CONFIG/RPTI/ENT/PS/6A83ECE7-E440-487B-82BE-CF4CB3A861DC/DEFAULT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}         {$I PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC} {$I PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}        {$I PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}        {$ENDIF}
const
  objname_datefrom   = 'dtpDateFrom';
  objname_dateto     = 'dtpDateTo';
  objname_firms      = 'gbFirms';
  objname_tmcgroup   = 'gbTMCGroup';
  msg_input_firms    = 'Выберите фирмы учета';
  msg_input_tmcgroup = 'Выберите виды залогов';
  //============================================================================
  function TERPFormRpti_GetExportFilter(aOwner:TComponent):string;
  begin
    Result := 
      'С "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+
      '" ПО "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto))+
      '" Фирмы учета: "'+InputIntf_Ref_GetNames(aOwner.FindComponent(objname_firms))+
      '"  ';//Виды залогов: "'+InputIntf_Ref_GetNames(aOwner.FindComponent(objname_tmcgroup))+'"';
  end;
  //============================================================================
  function  TERPFormRpti_OnGetSQL(aOwner:TComponent;var aSQL:string):Boolean;
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
      ParamByName('FIRM_IDS'     ).AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_firms));
      ParamByName('TMC_GROUP_IDS').AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_tmcgroup));
      ParamByName('DATE_FROM'    ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00';
      ParamByName('DATE_TO'      ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto)+1)+' 00:00:00';
      end;  
  end;
  //============================================================================
  function CreateChartTabSheet(aOwner:TComponent; aPC:TxcPageControlEx; const aFieldName, aCaption, aChartTitle:string):TxcTabSheet;
  var
    lkChart :TDBChart;
    lkSer   :TPieSeries;
  begin
    Result := CreateTxcTabSheet(aPC,'ts'+aFieldName,aCaption, 371,Amunhotep.MainForm.StyleManager.Colors.Highlight);
    {$IFDEF AMUNHOTEP4512}
    lkChart := Interface_TeeChart_Create(aOwner, Result, 'DBChartPie_'+aFieldName);
    with lkChart do
      begin
      Title.Text.Text := aChartTitle;
      end;
    {$ELSE}
    lkChart := CreateTDBChart(aOwner, Result, 'DBChartPie_'+aFieldName, aChartTitle, 0,0,600,600,alClient);
    {$ENDIF}  
    lkSer              := TPieSeries.Create(aOwner);
    lkSer.Name         := lkSer.ClassName+aFieldName;
    lkSer.ParentChart  := lkChart;
    lkSer.ShowInLegend := true;
    lkSer.Visible      := true;
    lkSer.Circled      := true;
    lkSer.DataSource   := TERPForm_DBGridMain(aOwner).DataSource.DataSet;
    lkSer.PieValues.Order       := loDescending;
    lkSer.PieValues.DateTime    := false;
    lkSer.PieValues.ValueSource := aFieldName;
    lkSer.XLabelsSource         := TERPForm_DBGridMain(aOwner).Columns[1].FieldName;
  end;
  //============================================================================
  function CreateChartTabSheetBar(aOwner:TComponent; aPC:TxcPageControlEx; const aFieldName, aCaption, aChartTitle:string):TxcTabSheet;
  var
    lkChart :TDBChart;
    lkSer   :TBarSeries;
  begin
    Result := CreateTxcTabSheet(aPC,'ts'+aFieldName+'Bar',aCaption, 376,Amunhotep.MainForm.StyleManager.Colors.Highlight);
    {$IFDEF AMUNHOTEP4512}
    lkChart := Interface_TeeChart_Create(aOwner, Result, 'DBChart_Bar_'+aFieldName);
    with lkChart do
      begin
      Title.Text.Text := aChartTitle;
      end;
    {$ELSE}
    lkChart := CreateTDBChart(aOwner, Result, 'DBChart_Bar_'+aFieldName, aChartTitle, 0,0,600,600,alClient);
    {$ENDIF}  
    lkChart.BottomAxis.LabelsAngle := 90;
    lkSer               := TBarSeries.Create(aOwner);
    lkSer.Name          := lkSer.ClassName+aFieldName+'Bar';
    lkSer.ParentChart   := lkChart;
    lkSer.ShowInLegend  := true;
    lkSer.Visible       := true;
    lkSer.ColorEachPoint:= true;
    lkSer.Marks.Visible := false;
    lkSer.DataSource    := TERPForm_DBGridMain(aOwner).DataSource.DataSet;
    lkSer.YValues.Order       := loDescending;
    lkSer.YValues.DateTime    := false;
    lkSer.YValues.ValueSource := aFieldName;
    lkSer.XLabelsSource         := TERPForm_DBGridMain(aOwner).Columns[1].FieldName;
  end;
  //============================================================================
  procedure TERPFormRpti_OnChart(aOwner:TComponent; aParent:TWinControl);
  var
    lkPC :TxcPageControlEx;
    lkTS :TxcTabSheet;
  begin
    lkPC := CreateTxcPageControlEx(aOwner, aParent, 'PCCharts', 0,0,600,600, alClient);
    lkPC.MultiLine := false;
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'NEV_CNT' ,'По кол-ву залогов', 'Долевое участие по количеству залогов');
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'NEV_CS'  ,'По кол-ву контрагентов', 'Долевое участие по количеству контрагентов, выполнивших залоги');
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'NEV_SUMCALC'  ,'По сумме оценки', 'Долевое участие по сумме оценки');
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'NEV_SUMLEFT'  ,'По сумме на руках', 'Долевое участие по сумме на руках');
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'TMC_MASSA'  ,'По массе ТМЦ', 'Долевое участие по массе ТМЦ');

    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'NEV_CNT' ,'По кол-ву залогов', 'Сравнительный график по количеству залогов');
    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'NEV_CS'  ,'По кол-ву контрагентов', 'Сравнительный график по количеству контрагентов, выполнивших залоги');
    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'NEV_SUMCALC'  ,'По сумме оценки', 'Сравнительный график по сумме оценки');
    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'NEV_SUMLEFT'  ,'По сумме на руках', 'Сравнительный график по сумме на руках');
    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'TMC_MASSA'  ,'По массе ТМЦ', 'Долевое участие по массе ТМЦ');
    TxcPageControlEx_ActivateDefaultPage(lkPC);
  end;
  //============================================================================
  procedure TERPFormRpti_OnTerms(aOwner:TComponent;aParent:TWinControl);
  var
    lkLastTop :Integer;
  begin
    lkLastTop := 4;
    lkLastTop := lkLastTop + InputIntf_DatePeriod_Create(aOwner, aParent, 'gbDatePeriod', 'Укажите период', 4, lkLastTop, 44, 360,objname_datefrom,objname_dateto,Now,Now).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_firms   ,msg_input_firms   ,4,lkLastTop, 0,360,'TABL$R_FIRMS',TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_tmcgroup,msg_input_tmcgroup,4,lkLastTop,240,360,'VIEW$R_TMC_GROUP_PS001',TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
  end;
  //============================================================================
  function TERPFormRpti_OnColumnsCreate(aOwner:TComponent; aDBG:TDBGridEh):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormRpti_dbgMain_Columns_OnEditButtonClick(Sender :TObject; var Handled :Boolean);
  var
    lkDBG    :TDBGridEh;
    lkCol    :TColumnEh;
    lkScript :string;
  begin
    Handled := true;
    lkDBG   := TDBGridEh(TComponent(Sender).Owner.Owner);
    if not lkDBG.DataSource.DataSet.Active then exit;
    lkCol   := lkDBG.Columns[lkDBG.SelectedIndex];
    if(lkCol=nil)then exit;
    lkScript := 
      '{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}{$I PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}{$ENDIF} '+#13#10+
      'begin '+#13#10+
      '  TERPFormGrid_DataSetFilter_DateInit := true; '+#13#10+
      '  TERPFormGrid_DataSetFilter_DateFrom := StrToDate('''+FormatDateTime('dd.mm.yyyy',InputIntf_DatePeriod_Date(lkDBG.Owner,objname_datefrom))+'''); '+#13#10+ 
      '  TERPFormGrid_DataSetFilter_DateTo   := StrToDate('''+FormatDateTime('dd.mm.yyyy',InputIntf_DatePeriod_Date(lkDBG.Owner,objname_dateto)  )+'''); '+#13#10+
      '  TERPFormGrid_DataSetFilter_Add(''FIRM_ID''    ,'' '''''+InputIntf_Ref_GetIds(lkDBG.Owner.FindComponent(objname_firms))+''''' CONTAINING ''''~''''||FIRM_ID||''''~'''' ''); '+#13#10;
    if(lkDBG.DataSource.DataSet.FindField('FILIAL_ID') <> nil)then
      lkScript := lkScript + 
      '  TERPFormGrid_DataSetFilter_Add(''FILIAL_ID''  ,'' (FILIAL_ID = '+lkDBG.DataSource.DataSet.FieldByName('FILIAL_ID').AsString+') OR (FILIAL_ID = 0) ''); '+#13#10
     else 
      lkScript := lkScript + 
      '  TERPFormGrid_DataSetFilter_Add(''USER_ID''  ,'' USER_ID = '''''+lkDBG.DataSource.DataSet.FieldByName('USER_ID').AsString+''''' ''); '+#13#10;
    lkScript := lkScript + 
      '  TERPFormGrid_DataSetFilter_Add(''FLAG_COMMIT'',''FLAG_COMMIT = 1''); '+#13#10+
      '  Journal_Create(''1000066''); '+#13#10+
      'end.'+#13#10;
//    Dialogs.MessageDlg(lkScript, mtInformation, [mbOk]);  
    run(lkScript, 'DB:CONFIG/DOC/1000066/DEFAULT.PS');
  end;
  //============================================================================
  procedure TERPFormRpti_OnColumnsCreated(aOwner:TComponent; aDBG:TDBGridEh);
  var
    i:Integer;
  begin
    for i:=0 to aDBG.Columns.Count-1 do
      with aDBG.Columns[i] do
        if( (FieldName = 'TMC_MASSA') or (FieldName = 'TMC_MASSA_NETTO') )then
          begin
          with EditButtons.Add do
            begin
            Visible := true;
            Style   := ebsEllipsisEh;
            OnClick := @TERPFormRpti_dbgMain_Columns_OnEditButtonClick;
            end;
          AlwaysShowEditButton := true;
          Width := Width + 12;
          end;
  end;
  //============================================================================
  procedure TERPFormRpti_OnColumnsLoad(aOwner:TComponent; aDBG:TDBGridEh);
  begin
     // do nothing, default handler
  end;
  //============================================================================
  function  TERPFormRpti_OnPrint(aOwner:TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormRpti_BeforePreview(aOwner:TComponent; aRpt:TxReport);
  begin
    if((aRpt.Tag = 1000022) or (aRpt.Tag = 1000023) or (aRpt.Tag = 1000034) or (aRpt.Tag = 1000035))then exit;
    with TxrChart(aRpt.FindComponent('Chart')) do
      begin
      Chart.Title.Text.Text := '';
      Chart.BottomAxis.LabelsAngle := 90;
      end;
    with TBarSeries(aRpt.FindComponent('SeriesBar')) do
      begin
      ShowInLegend  := true;
      Visible       := true;
      ColorEachPoint:= true;
      Marks.Visible := false;
      DataSource    := aRpt.DataSets[0].Query;
      YValues.Order       := loDescending;
      YValues.DateTime    := false;
      XLabelsSource      := TERPForm_DBGridMain(aOwner).Columns[1].FieldName;
           if((aRpt.Tag = 1000024)or(aRpt.Tag = 1000029)or(aRpt.Tag = 1000036)or(aRpt.Tag = 1000041))then YValues.ValueSource := 'NEV_CNT'
      else if((aRpt.Tag = 1000025)or(aRpt.Tag = 1000030)or(aRpt.Tag = 1000037)or(aRpt.Tag = 1000042))then YValues.ValueSource := 'NEV_CS'
      else if((aRpt.Tag = 1000026)or(aRpt.Tag = 1000031)or(aRpt.Tag = 1000038)or(aRpt.Tag = 1000043))then YValues.ValueSource := 'NEV_SUMCALC'
      else if((aRpt.Tag = 1000027)or(aRpt.Tag = 1000032)or(aRpt.Tag = 1000039)or(aRpt.Tag = 1000044))then YValues.ValueSource := 'NEV_SUMLEFT'
      else if((aRpt.Tag = 1000028)or(aRpt.Tag = 1000033)or(aRpt.Tag = 1000040)or(aRpt.Tag = 1000045))then YValues.ValueSource := 'TMC_MASSA'
      else                                                    YValues.ValueSource := 'TMC_MASSA'     
      end;
  end;
  //============================================================================ 
