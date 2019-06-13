{$DEFINE DB:CONFIG/RPTI/0CB115D1-2ED0-4481-91D2-84F3409CD7D2/DEFAULT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}         {$I PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC} {$I PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}        {$I PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}        {$ENDIF}
const
  objname_datefrom   = 'dtpDateFrom';
  objname_dateto     = 'dtpDateTo';
  objname_countries  = 'gbContries';
  objname_firms      = 'gbFirms';
  objname_places     = 'gbPlaces';
  msg_input_countries= 'Выберите драгоценные металлы';
  msg_input_firms    = 'Выберите фирмы учета';
  msg_input_places   = 'Выберите места хранения';
  //============================================================================
  function TERPFormRpti_GetExportFilter(aOwner:TComponent):string;
  begin
    Result := 
      msg_erp_lbldatefrom+' "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+'" '+
      msg_erp_lbldateto  +' "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto))+'" '+
      'Фирмы учета: "'+InputIntf_Ref_GetNames(aOwner.FindComponent(objname_firms))+'" ';
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
        ParamByName('DATE_FROM'  ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00';
        ParamByName('DATE_TO'    ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto  ))+' 23:59:59';
        ParamByName('COUNTRY_IDS').AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_countries));
        ParamByName('FIRM_IDS'   ).AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_firms));
        ParamByName('PLACES_IDS' ).AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_places));
        end;  
  end;
  //============================================================================
  function TERPFormRpti_CreateTabSheetChartLine_Local(aOwner:TComponent; aPC:TxcPageControlEx; const aFieldName, aCaption, aChartTitle, aXLabelsSource:string):TxcTabSheet;
  var
    lkChart :TDBChart;
  begin
    Result := CreateTxcTabSheet(aPC,'tsChartLine_'+aFieldName,aCaption, 7,Amunhotep.MainForm.StyleManager.Colors.Highlight);
    lkChart := Interface_TeeChart_Create(aOwner, Result, 'DBChartLine_'+aFieldName);
    with lkChart do
      begin
      Title.Text.Text := aChartTitle;
      end;
    lkChart.BottomAxis.LabelsAngle := 90;
    with TLineSeries.Create(aOwner) do
      begin
      Name                := ClassName+'_'+aFieldName;
      ParentChart         := lkChart;
      ShowInLegend        := false;
      Visible             := true;
      LinePen.Width       := 2;
      Marks.Visible       := false;
      DataSource          := TERPForm_DBGridMain(aOwner).DataSource.DataSet;
      YValues.Order       := loNone;
      YValues.DateTime    := false;
      YValues.ValueSource := aFieldName;
      XLabelsSource       := aXLabelsSource;
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_OnChart(aOwner:TComponent; aParent:TWinControl);
  var
    lkPC :TxcPageControlEx;
    lkTS :TxcTabSheet;
  begin
    lkPC := CreateTxcPageControlEx(aOwner, aParent, 'PCCharts', 0,0,600,600, alClient);
    lkPC.MultiLine := false;
    lkTS := TERPFormRpti_CreateTabSheetChartBar(aOwner,lkPC,'MEND','Масса на хранении (гистограмма)','График изменения массы на хранении','DATE_COMMIT');
    TDBChart(aOwner.FindComponent('DBChartBar_MEND')).BottomAxis.DateTimeFormat := 'mmmmm yyyy';
    TDBChart(aOwner.FindComponent('DBChartBar_MEND')).BottomAxis.DateTimeFormat := 'mmmmm yyyy';
    with TBarSeries(aOwner.FindComponent('TBarSeries_MEND'))do
      begin
      Color            := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
      ColorEachPoint   := false;
      ShowInLegend     := false;
      YValues.Order    := loNone;
      YValues.DateTime := false;
      end;
    lkTS := TERPFormRpti_CreateTabSheetChartBar(aOwner,lkPC,'MDEB','Принятие/возврат (гистограмма)','График отношения принятия/возврата(невыкупов)','DATE_COMMIT');
    TDBChart(aOwner.FindComponent('DBChartBar_MDEB')).BottomAxis.DateTimeFormat := 'mmmmm yyyy';
    with TBarSeries(aOwner.FindComponent('TBarSeries_MDEB'))do
      begin
      Color            := $0080FF80;
      ColorEachPoint   := false;
      ShowInLegend     := false;
      YValues.Order    := loNone;
      YValues.DateTime := false;
      end;
    with TBarSeries.Create(aOwner) do
      begin
      Name                := ClassName+'_'+'MKRD';
      ParentChart         := TDBChart(aOwner.FindComponent('DBChartBar_MDEB'));
      Visible             := true;
      ColorEachPoint      := false;
      ShowInLegend        := false;
      Marks.Visible       := false;
      DataSource          := TERPForm_DBGridMain(aOwner).DataSource.DataSet;
      YValues.Order       := loNone;
      YValues.DateTime    := false;
      {$IFDEF DB:CONFIG/RPTI/0CB115D1-2ED0-4481-91D2-84F3409CD7D2/DEFAULT.PS}
      YValues.ValueSource := 'MKRD';
      {$ELSE}
      YValues.ValueSource := 'MKRD_';
      {$ENDIF}
      XLabelsSource       := 'DATE_COMMIT';
      Color               := $008000FF;
      end;
    lkTS := TERPFormRpti_CreateTabSheetChartBar(aOwner,lkPC,'QEND','Кол-во на хранении (гистограмма)','Кол-во изменения массы на хранении','DATE_COMMIT');
    TDBChart(aOwner.FindComponent('DBChartBar_QEND')).BottomAxis.DateTimeFormat := 'mmmmm yyyy';
    with TBarSeries(aOwner.FindComponent('TBarSeries_QEND'))do
      begin
      Color            := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
      ColorEachPoint   := false;
      ShowInLegend     := false;
      YValues.Order    := loNone;
      YValues.DateTime := false;
      end;
    
    
    lkTS := TERPFormRpti_CreateTabSheetChartLine_Local(aOwner,lkPC,'MEND','Масса на хранении (линия)','График изменения массы на хранении','DATE_COMMIT');
    with TLineSeries(aOwner.FindComponent('TLineSeries_MEND'))do
      begin
      Color            := Amunhotep.MainForm.StyleManager.Colors.Error;
      ShowInLegend     := false;
      end;
    lkTS := TERPFormRpti_CreateTabSheetChartLine_Local(aOwner,lkPC,'MDEB','Принятие/возврат (линия)','График отношения принятия/возврата(невыкупов)','DATE_COMMIT');
    with TLineSeries(aOwner.FindComponent('TLineSeries_MDEB'))do
      begin
      Color            := $00004000;
      ColorEachPoint   := false;
      ShowInLegend     := false;
      YValues.Order    := loNone;
      YValues.DateTime := false;
      end;
    with TLineSeries.Create(aOwner) do
      begin
      Name                := ClassName+'_'+'MKRD_';
      ParentChart         := TDBChart(aOwner.FindComponent('DBChartLine_MDEB'));
      Visible             := true;
      ColorEachPoint      := false;
      ShowInLegend        := false;
      Marks.Visible       := false;
      DataSource          := TERPForm_DBGridMain(aOwner).DataSource.DataSet;
      YValues.Order       := loNone;
      YValues.DateTime    := false;
      YValues.ValueSource := 'MKRD_';
      XLabelsSource       := 'DATE_COMMIT';
      LinePen.Width       := 2;
      Color               := clNavy;
      end;

    TxcPageControlEx_ActivateDefaultPage(lkPC);
  end;
  //============================================================================
  procedure TERPFormRpti_OnTerms(aOwner:TComponent;aParent:TWinControl);
  var
    lkLastTop :Integer;
  begin
    lkLastTop := 4;
    lkLastTop := lkLastTop + InputIntf_DatePeriod_Create(aOwner, aParent, 'gbDatePeriod', 'Укажите период', 4, lkLastTop, 44, 360,objname_datefrom,objname_dateto,StrToDate('01.05.2010'),EndOfTheMonth(Now)).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_countries,msg_input_countries, 4,lkLastTop,180,360,'TABL$R_COUNTRIES' ,TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_firms ,msg_input_firms ,  4,lkLastTop, 80,360,'TABL$R_FIRMS' ,TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_places,msg_input_places,368,lkLastTop,400,360,'TABL$R_PLACES',TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
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
  begin
    // do nothing, default handler
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
