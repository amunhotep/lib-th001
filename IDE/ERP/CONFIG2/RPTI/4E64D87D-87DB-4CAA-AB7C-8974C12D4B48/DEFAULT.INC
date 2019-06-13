{$DEFINE DB:CONFIG/RPTI/ENT/PS/4E64D87D-87DB-4CAA-AB7C-8974C12D4B48/DEFAULT.INC}
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
    lkSer.Name         := lkSer.ClassName+'Pie_'+aFieldName;
    lkSer.ParentChart  := lkChart;
    lkSer.ShowInLegend := true;
    lkSer.Visible      := true;
    lkSer.Circled      := true;
    lkSer.Title        := aChartTitle;
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
    lkChart := Interface_TeeChart_Create(aOwner, Result, 'DBChartBar_'+aFieldName);
    with lkChart do
      begin
      Title.Text.Text := aChartTitle;
      end;
    {$ELSE}
    lkChart := CreateTDBChart(aOwner, Result, 'DBChartBar_'+aFieldName, aChartTitle, 0,0,600,600,alClient);
    {$ENDIF}  
    lkChart.BottomAxis.LabelsAngle := 90;
    lkSer               := TBarSeries.Create(aOwner);
    lkSer.Name          := lkSer.ClassName+'Bar_'+aFieldName;
    lkSer.ParentChart   := lkChart;
    lkSer.ShowInLegend  := true;
    lkSer.Visible       := true;
    lkSer.ColorEachPoint:= true;
    lkSer.Marks.Visible := false;
    lkSer.Title         := aChartTitle;
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
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'CASH_SUM'  ,'По телу кредита', 'Долевое участие в погашении тела кредита');
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'CASH_SUMPC','По погашенным %%', 'Долевое участие в погашении процентов по кредитам');
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'ZALOG_CNT' ,'По кол-ву залогов', 'Долевое участие по количеству залогов');
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'ZALOG_CS'  ,'По кол-ву контрагентов', 'Долевое участие по количеству контрагентов, выполнивших залоги');
    lkTS := CreateChartTabSheet(aOwner, lkPC, 'ZALOG_RETSUMEND','По сумме на руках', 'Долевое участие по сумме на руках у контрагентов');

    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'CASH_SUM'  ,'По телу кредита', 'Сравнительный график в погашении тела кредита');
    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'CASH_SUMPC','По погашенным %%', 'Сравнительный график в погашении процентов по кредитам');
    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'ZALOG_CNT' ,'По кол-ву залогов', 'Сравнительный график по количеству залогов');
    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'ZALOG_CS'  ,'По кол-ву контрагентов', 'Сравнительный график по количеству контрагентов, выполнивших залоги');
    lkTS := CreateChartTabSheetBar(aOwner, lkPC, 'ZALOG_RETSUMEND','По сумме на руках', 'Сравнительный график по сумме на руках у контрагентов');

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
  procedure TERPFormRpti_OnColumnsCreated(aOwner:TComponent; aDBG:TDBGridEh);
  begin
     // do nothing, default handler
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
    if((aRpt.Tag = 1000010) or (aRpt.Tag = 1000011))then exit;
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
           if((aRpt.Tag = 1000012)or(aRpt.Tag = 1000017))then YValues.ValueSource := 'CASH_SUM'
      else if((aRpt.Tag = 1000013)or(aRpt.Tag = 1000018))then YValues.ValueSource := 'CASH_SUMPC'
      else if((aRpt.Tag = 1000014)or(aRpt.Tag = 1000019))then YValues.ValueSource := 'ZALOG_CNT'
      else if((aRpt.Tag = 1000015)or(aRpt.Tag = 1000020))then YValues.ValueSource := 'ZALOG_CS'
      else if((aRpt.Tag = 1000016)or(aRpt.Tag = 1000021))then YValues.ValueSource := 'ZALOG_RETSUMEND'
      else                                                    YValues.ValueSource := 'CASH_SUM'     
      end;
  end;
  //============================================================================ 
