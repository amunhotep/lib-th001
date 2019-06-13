{$DEFINE PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                      {$I PEAKTOP:GLOBAL_VARIABLES.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                            {$I PEAKTOP:OBJ/TLABEL.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                         {$I PEAKTOP:OBJ/TCOLUMNEH.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                         {$I PEAKTOP:OBJ/TDBGRIDEH.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}             {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                  {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                       {$I PEAKTOP:OBJ/TXCTABSHEET.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                         {$I PEAKTOP:OBJ/TSPLITTER.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSCROLLBOX.INC}                        {$I PEAKTOP:OBJ/TSCROLLBOX.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                      {$I PEAKTOP:OBJ/TXFBDATASETS.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}            {$I PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/TEECHART/DEFAULT.INC}        {$I PEAKTOP:OBJ/INTERFACE/TEECHART/DEFAULT.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}                 {$I ../SHORTCUTS.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/DIALOGCOLUMNS.INC}      {$I ../DBGRID/DIALOGCOLUMNS.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC}       {$I ../DBGRID/FOOTERS_LOAD.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/INTF.INC}        {$I ../DBGRID/EXPORT/INTF.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/DLG.INC}          {$I ../DBGRID/PRINT/DLG.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}            {$I ../DBGRID/ACTIONS.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_RPTI.INC} {$I ../DBGRID/GETCELLPARAMS_RPTI.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/LOADITEMS.INC}            {$I ../MENU/LOADITEMS.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}           {$I ../$COMMON/FORMERP.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC}      {$I ../$COMMON/FORMERP_BLOB.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}      {$I ../$COMMON/FORMERP_LANG.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC}        {$I ../$COMMON/EXTENSIONS.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/HEADER.INC}               {$I ./HEADER.INC}                               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/ACTIONS.INC}              {$I ./ACTIONS.INC}                              {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC ===================
  procedure TERPFormRpti_RefreshView(aOwner :TComponent);
  var
    lkTr       :TxFBTransaction;
    lkQr       :TxFBQuery;
    lkSQL      :string;
    lkFileName :string;
  begin
    lkTr := TERPForm_TransactionMain(aOwner);
    lkQr := TERPForm_QueryMain(aOwner);
    lkQr.DisableControls;
    if lkTr.InTransaction then 
      lkTr.Commit;
    TERPFormRpti_OnColumnsLoad(aOwner, TERPForm_DBGridMain(aOwner));  
    lkSQL := '';  
    if TERPFormRpti_OnGetSQL(aOwner, lkSQL)then
      lkQr.SQL.Text := lkSQL
     else
      begin
      GetField(FBDataBase, 'TABL$_TB','SC_REF','ID = '''+TAmunhotepForm(aOwner).HelpKeyWord+''' ', lkFileName);
      TERPFormRpti_OnGetSQLFileName(aOwner, lkFileName);
      lkQr.SQL.Text := StringsLoadFromFile(lkFileName);
      end; 
    TSynEdit(aOwner.FindComponent('SynEdit')).Text := lkQr.SQL.Text;  
    lkQr.Prepare;
    if(lkQr.Params.Count > 0)then
      TERPFormRpti_OnProcessParams(aOwner, lkQr);
    lkQr.EnableControls;  
    try
      lkQr.Open;
    finally
      with TxcPageControlEx(aOwner.FindComponent(obj_name_erp_pagecontrol)) do
        if(ActivePageIndex = 0)then
          ActivePageIndex := 1;
    end;
  end;
  //============================================================================
  function TERPFormRpti_CreateTabSheetChartPie(aOwner:TComponent; aPC:TxcPageControlEx; const aFieldName, aCaption, aChartTitle, aXLabelsSource:string):TxcTabSheet;
  var
    lkChart :TDBChart;
  begin
    Result := CreateTxcTabSheet(aPC,'tsChartPie_'+aFieldName,aCaption, 371,Amunhotep.MainForm.StyleManager.Colors.Highlight);
    lkChart := Interface_TeeChart_Create(aOwner, Result, 'DBChartPie_'+aFieldName);
    with lkChart do
      begin
      Title.Text.Text := aChartTitle;
      end;
    with TPieSeries.Create(aOwner) do
      begin
      Name                  := ClassName+'_'+aFieldName;
      ParentChart           := lkChart;
      ShowInLegend          := true;
      Visible               := true;
      Circled               := true;
      DataSource            := TERPForm_DBGridMain(aOwner).DataSource.DataSet;
      PieValues.Order       := loDescending;
      PieValues.DateTime    := false;
      PieValues.ValueSource := aFieldName;
      XLabelsSource         := aXLabelsSource;
      end;
  end;
  //============================================================================
  function TERPFormRpti_CreateTabSheetChartBar(aOwner:TComponent; aPC:TxcPageControlEx; const aFieldName, aCaption, aChartTitle, aXLabelsSource:string):TxcTabSheet;
  var
    lkChart :TDBChart;
  begin
    Result := CreateTxcTabSheet(aPC,'tsChartBar_'+aFieldName,aCaption, 376,Amunhotep.MainForm.StyleManager.Colors.Highlight);
    lkChart := Interface_TeeChart_Create(aOwner, Result, 'DBChartBar_'+aFieldName);
    with lkChart do
      begin
      Title.Text.Text := aChartTitle;
      end;
    lkChart.BottomAxis.LabelsAngle := 90;
    with TBarSeries.Create(aOwner) do
      begin
      Name                := ClassName+'_'+aFieldName;
      ParentChart         := lkChart;
      ShowInLegend        := true;
      Visible             := true;
      ColorEachPoint      := true;
      Marks.Visible       := false;
      DataSource          := TERPForm_DBGridMain(aOwner).DataSource.DataSet;
      YValues.Order       := loDescending;
      YValues.DateTime    := false;
      YValues.ValueSource := aFieldName;
      XLabelsSource       := aXLabelsSource;
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_dtsMain_AfterOpen(DataSet :TDataSet);  
  begin
    with DataSet.Owner do
      if(TERPForm_Settings(Owner).Values[ERP_SETTINGS_DATAMEMORY] = '1')then
        if not TERPForm_MemTableMain(Owner).Active then
          try
            TERPForm_MemTableMain(Owner).Open;
          finally
          end;
  end;
  //============================================================================
  procedure TERPFormRpti_dtsMain_BeforeClose(DataSet :TDataSet);
  begin 
    with DataSet.Owner do
      if(TERPForm_Settings(Owner).Values[ERP_SETTINGS_DATAMEMORY] = '1')then
        with TERPForm_MemTableMain(Owner) do
          if Active then
            begin
            if(State <> dsBrowse)then
              try
                Post;
              except
                Cancel;
              end;
            Close;
            end;
  end;
  //============================================================================
  procedure TERPFormRpti_actViewRefresh_OnExecute(Sender :TObject);
  begin
    TERPFormRpti_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormRpti_DoDefaultPreview(aOwner :TComponent);
  var
    lkRptId    :string;
    lkRptName  :string;
    lkRptPath  :string;
    lkResource :string;
    lkRpt      :TxReport;
    lkLBL      :TxrLabel;
    lkImg      :TxrImage;
    lkTr       :TxFBTransaction;
    lkQr       :TxFBQuery;
    lkCnt      :Integer; 
  begin
    if TERPFormRpti_OnPrint(aOwner) then exit;
    if not TERPDialogPrint_Execute(ERP_OBJECTTYPE_RPT, TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME], '1', GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT),lkRptId,lkRptName,lkRptPath) then exit;
    lkResource := StringsLoadFromFile(lkRptPath);
    if(lkResource = '')then
      begin
      WriteLn('ERROR LOAD :'+lkRptPath);  
      exit;
      end;
    lkRpt := TxReport(StrToComponent(lkResource));
    lkRpt.DataBase := FBDataBase;
    lkRpt.Title    := lkRptName;
    lkRpt.Tag      := StrToInt(lkRptId);
    lkTr := TxFBTransaction.Create(nil);
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
    lkQr := TxFBQuery.Create(lkTr);
    with lkQr do
      begin
      Transaction := lkTr;
      SQL.Text := 'SELECT R1.* FROM TABL$_TB_DOCSRPTSQL R1 WHERE (R1.RPT_ID = '''+lkRptId+''') ORDER BY R1.ORDERID';
      end;
    lkQr.Open;
    lkQr.First;
    lkCnt := 0;
    lkRpt.DataSets.Clear;
    while not lkQr.EOF do
      begin
      lkCnt := lkCnt + 1;
      if(lkRpt.DataSets.Count < lkCnt)then
        lkRpt.DataSets.Add;
      with lkRpt.DataSets[lkCnt-1] do
        begin
        Name         := lkQr.FieldByName('NAME'  ).AsString;
        MasterDataSet:= lkQr.FieldByName('PARENT').AsString;
        if(StrTrimAll(lkQr.FieldByName('PATH').AsString) = '')then
          SQL.Text   := TERPForm_QueryMain(aOwner).SQL.Text
         else
          SQL.Text   := StringsLoadFromFile(lkQr.FieldByName('PATH').AsString);
        Query.Prepare;
        if(Query.Params.Count > 0)then
          TERPFormRpti_OnProcessParams(aOwner, Query);
        end;  
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;

    lkImg := nil;
    if(lkRpt.FindComponent('ImgLogo')   <> nil)then lkImg := TxrImage(lkRpt.FindComponent('ImgLogo'));
    if(lkRpt.FindComponent('ImageLogo') <> nil)then lkImg := TxrImage(lkRpt.FindComponent('ImageLogo'));
    if(lkImg <> nil)then
      begin
      lkResource := StrAbsolutePath('../conf/ent/logo.bmp', Amunhotep.ExeName);
      if FileExists(lkResource)then
        try lkImg.Picture.LoadFromFile(lkResource) except end;
      end;
    lkLBL := nil;
    if(lkRpt.FindComponent('lblCaption') <> nil)then lkLBL := TxrLabel(lkRpt.FindComponent('lblCaption'));
    if(lkLBL <> nil)then
      lkLBL.Caption := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION]+//' ['+msg_erp_report_done+' '+FormatDateTime('dd.mm.yyyy hh:nn:ss', Now)+']'+#13#10#$20#$20#$20#$20+
        lkRptName+#13#10#$20#$20#$20#$20+TERPFormRpti_GetExportFilter(aOwner);
    TERPFormRpti_BeforePreview(aOwner, lkRpt);  
    lkRpt.Prepare;
    lkRpt.Preview;
  end;
  //============================================================================
  procedure TERPFormRpti_actPrintGrid_OnExecute(Sender :TObject);
  begin
    TERPFormRpti_DoDefaultPreview(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormRpti_actPrintGrid_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin
    lkEnabled := TERPForm_DBGridMain(TComponent(Sender).Owner).DataSource.DataSet.Active;
    if lkEnabled then lkEnabled := (TERPForm_DBGridMain(TComponent(Sender).Owner).DataSource.DataSet.RecordCount > 0);
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure TERPFormRpti_ColumnsCreate(aOwner:TComponent; aDBG:TDBGridEh; aQr:TxFBQuery);
  var
    i          :Integer;
    lkSettings :TStrings;
    lkCol      :TColumnEh; 
  begin
    lkSettings := TERPForm_Settings(aOwner);
    i := 0;
    aQr.First;   
    while not aQr.EOF do
      begin
      if( (aQr.FieldByName('ACCS_FLAG_READ').AsInteger<=0) or (aQr.FieldByName('FLAG_DELETE').AsInteger=1) )then
        begin
        i := i + 1;
        aQr.Next;
        continue;
        end;
      if(Pos('DOMN$BLOB_', UpperCase(aQr.FieldByName('FIELD_TYPE').AsString)) = 1)then
        TERPForm_BlobInterface_Create(aDBG.DataSource, TxcPageControlEx(aOwner.FindComponent(obj_name_erp_pagecontroldetail)), 
          aQr.FieldByName('NAME').AsString, StrTrimAll(aQr.FieldByName('ID').AsString), UpperCase(aQr.FieldByName('FIELD_TYPE').AsString), false)
       else
        begin
        lkCol := CreateTColumnEh2(aDBG, aQr.FieldByName('ID').AsString, aQr.FieldByName('FORMAT').AsString, aQr.FieldByName('NAME').AsString,
          aQr.FieldByName('HINT').AsString, aQr.FieldByName('WIDTH').AsInteger, aQr.FieldByName('COL_INDEX').AsInteger,
          aQr.FieldByName('ALIGNMENT').AsInteger, aQr.FieldByName('COLOR').AsInteger,
          aQr.FieldByName('KEY_LIST').AsString, aQr.FieldByName('PICK_LIST').AsString, []);
        with lkCol do
          begin
          AutoDropDown      := true;
          Title.Orientation := IntToTTextOrientationEh(aQr.FieldByName('ORIENTATION').AsInteger);
          if(StrTrimAll(aQr.FieldByName('ID').AsString) = 'ID')then
            begin
            with Footer do
              begin
              DisplayFormat := '# ### ### ##0';
              Alignment     := taRightJustify;
              ValueType     := fvtCount;
              end;
            Title.SortMarker := smDownEh;
            end;
          ReadOnly := true;
          end;  
        if(aQr.FieldByName('FLAG_FOOTER').AsInteger <> 0)then
          begin
          aDBG.HelpKeyWord := IntToStr(MaxInteger(StrToInt(aDBG.HelpKeyWord), aQr.FieldByName('FOOTER_COUNT').AsInteger));
          ERP_DBGridEh_Column_FootersLoad(lkCol, aQr.Transaction, aQr.FieldByName('TB_ID').AsString, aQr.FieldByName('ID').AsString);
          end;           
        end;  
      i := i + 1;
      aQr.Next;
      end; 
  end;
  //============================================================================
  procedure TERPFormRpti_ConfigColumns_AutoFill(Sender :TObject);
  var
    i :Integer;
    lkTB :string;
  begin
    lkTB := TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TABLENAME];
    with TERPForm_DBGridMain(TComponent(Sender).Owner) do
      for i:=0 to Columns.Count-1 do
        begin
        ExecSQL(FBDataBase,'UPDATE OR INSERT INTO TABL$_TB_COLS(TB_ID, ID)VALUES('''+lkTB+''', '''+Columns[i].FieldName+''')MATCHING(TB_ID, ID);');
        end;
  end;
  //============================================================================
  procedure TERPFormRpti_DatabaseMenuItem_OnClick(Sender :TObject);
  var
    lkScName :string;
    lkOwner  :TComponent;
    i        :Integer;
  begin
    lkOwner := TComponent(Sender); 
    while(lkOwner <> nil)do
      begin
      if ObjectInheritsFrom(lkOwner,'TCustomForm')then
        break; 
      lkOwner := lkOwner.Owner;
      end;
    if not ObjectInheritsFrom(lkOwner,'TCustomForm')then exit;
  
    if not TERPForm_ActiveDataSet(lkOwner).Active then exit;
    if not(TERPForm_ActiveDataSet(lkOwner).RecordCount > 0)then 
      begin
      exit;
      end;
    lkScName := ERP_DBMenuItem_GetScript(TComponent(Sender).Tag);
    if(StrTrimAll(lkScName) = '')then exit;
    with TERPForm_ActiveDataSet(lkOwner) do
      for i:=0 to Fields.Count-1 do
        SetGlobalVariable(Fields[i].FieldName, Fields[i].AsString);
    call(lkScName);
  end;
  //============================================================================
  procedure TERPFormRpti_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    TERPForm_GridSettingsSave(TERPForm_DBGridMain(TComponent(Sender)), TERPForm_Settings(TComponent(Sender)).Values[ERP_SETTINGS_TEMPFILENAME] );
    Action := caFree;
  end;
  //============================================================================
  function TERPFormRpti_Create(const aReportGUID :string):TAmunhotepForm;
  var
    lkSettings   :TStrings;
    lkPC         :TxcPageControlEx;
    lkPCDetail   :TxcPageControlEx;
    lkSB         :TScrollBox;
    lkTrLoad     :TxFBTransaction;
    lkQrLoad     :TxFBQuery;
    lkDSLoad     :TDataSource;
    lkTr         :TxFBTransaction;
    lkQr         :TxFBQuery;
    lkDS, lkDSMT :TDataSource;
    lkDSDrv      :TDataSetDriverEh;
    lkMT         :TMemTableEh;
    lkDBG        :TDBGridEh;
    lkMainMenu   :TMainMenu;
    lkMI         :TMenuItem;
    lkMIMenuMain :TMenuItem;
    lkMIView     :TMenuItem;
    lkMIObj      :TMenuItem;
    lkAct        :TCustomAction;
    lkTBTerm     :TxcGradientPanelVista;
    lkTBData     :TxcGradientPanelVista;
    lkTBDataView :TxcGradientPanelVista;
    lkTBDataNav  :TxcGradientPanelVista;
    lkTBDataExp  :TxcGradientPanelVista;
    lkTBB        :TxcToolBarButton;
    lkSplt       :TSplitter;
  begin
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTrLoad, lkQrLoad, lkDSLoad)  
    lkQrLoad.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETTABLE_RPTI));
    lkQrLoad.Prepare;
    lkQrLoad.ParamByName('PQ_TB_ID'   ).AsString := aReportGUID;
    lkQrLoad.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
    try
      lkQrLoad.Open;
    except
    end;
    if not(lkQrLoad.Active)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTrLoad.Free;
      Dialogs.MessageDlg(msg_error_erpsql+' "'+aReportGUID+'" !',mtWarning,[mbOk]);
      exit;
      end;  
    lkQrLoad.First;
    if(lkQrLoad.FieldByName('TB_EXISTS').AsInteger <> 1)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTrLoad.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_defined+' "'+aReportGUID+'"', mtError, [mbOk]);
      exit;
      end;
    Result := TAmunhotepForm(TERPForm_Create(lkQrLoad.FieldByName('TB_NAME').AsString, ERP_FILENAME_ICO_RPTI,ERP_FILENAME_BMP_RPTI, false, @TERPFormRpti_OnClose));
    with Result do
      begin
      HelpKeyWord := aReportGUID;
      if(GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT) = 'PEAKTOP')then
        begin
        lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actconfig      ,'Настройка объекта','',ERP_FILENAME_BMP_CONFIGURATOR,@TERPForm_actConfig_OnExecute,nil,TxcGradientPanel(Result.FindComponent(obj_name_erp_topbar)));
        lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actconfigmenu  ,'Настройка меню'   ,'',ERP_FILENAME_BMP_MENU    ,@TERPForm_actConfigMenu_OnExecute,nil,TxcGradientPanel(Result.FindComponent(obj_name_erp_topbar)));
        lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actconfig+'Col','Автозаполнение колонок','','PEAKTOP:IMG/CONFIG/ERP/DBGRID0032X0032.BMP',@TERPFormRpti_ConfigColumns_AutoFill,nil,TxcGradientPanel(Result.FindComponent(obj_name_erp_topbar)));
        end;
      end;  
    TCustomAction(Result.FindComponent(obj_name_erp_actclose)).OnExecute := @TERPFormRpti_actClose_OnExecute;
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_RPT);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_RPT);
      end;  
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_TABLENAME   ] := aReportGUID;
      Values[ERP_SETTINGS_TABLECAPTION] := lkQrLoad.FieldByName('TB_NAME').AsString;
      Values[ERP_SETTINGS_BASETYPE    ] := IntToStr(ERP_OBJECTTYPE_RPT);
      Values[ERP_SETTINGS_DATAMEMORY  ] := '1';
      Values[ERP_SETTINGS_TEMPFILENAME] := ERP_ObjectTempFileName(ERP_OBJECTTYPE_RPT,ERP_OBJECTTYPE_RPT,aReportGUID,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));
      end;
    // users recent menu
    ExecSQL(FBDataBase, 
      'EXECUTE BLOCK AS '+SQLCRLF+
      '  DECLARE VARIABLE P DOMN$INTEGER; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  IF(NOT(EXISTS(SELECT R.RDB$RELATION_ID FROM RDB$RELATIONS R WHERE(TRIM(R.RDB$RELATION_NAME)=''TABL$_USERS_RCNT''))))THEN EXIT; '+SQLCRLF+
      '  EXECUTE STATEMENT ''UPDATE OR INSERT INTO TABL$_USERS_RCNT(NAME, USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME)VALUES('''''+Result.Caption+''''', '''''+
       GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''''', 0, '''''+IntToStr(ERP_OBJECTTYPE_RPT)+''''', '''''+ScriptName+''''')MATCHING(USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME);''; '+SQLCRLF+    
      '  SELECT MAX(P.ID) FROM PROC$_USERS_LOG_INS(1000048, '''+aReportGUID+''', NULL, NULL, NULL) P INTO :P; '+SQLCRLF+
      'END');    
    lkMainMenu    := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIMenuMain  := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,ERP_FolderObjectCaption(ERP_OBJECTTYPE_RPT),'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
    lkMIObj       := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainobj ,msg_erp_tsdocdata ,'','', 48,  0);
    lkMIView      := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainview,msg_erp_mimainview,'','',150,  0);
    CreateTxFBTransQuery(Result, obj_name_erp_data_trmain, obj_name_erp_data_qrmain, 'DataSource'+obj_name_erp_data_qrmain, ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQr, lkDS);  
    with lkQr do
      begin
      AfterOpen   := @TERPFormRpti_dtsMain_AfterOpen;
      BeforeClose := @TERPFormRpti_dtsMain_BeforeClose;
      AfterScroll := nil;
      end;    
    lkDSDrv:= TDataSetDriverEh.Create(Result);
    with lkDSDrv do
      begin
      Name             := 'DataSetDriver'+lkQr.Name;
      ProviderDataSet  := lkQr;
      ResolveToDataSet := true; 
      end;
    lkMT := TMemTableEh.Create(lkTr);
    with lkMT do
      begin
      Name             := obj_name_erp_data_mtmain;
      DataDriver       := lkDSDrv;
      CachedUpdates    := false;
      Filtered         := true;
      FetchAllOnOpen   := true;
      MasterDetailSide := mdsOnSelfEh;
      end;
    lkDSMT := TDataSource.Create(lkMT);
    with lkDSMT do
      begin
      Name    := 'DataSource'+lkMT.Name;
      DataSet :=  lkMT;
      end; 
    lkPC := CreateTxcPageControlEx(Result, Result, obj_name_erp_pagecontrol, 0,36,600,600, alClient);
    CreateTxcTabSheet(lkPC,'tsTerms' ,msg_erp_tsterms  , 11,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPC,'tsData'  ,msg_erp_tsdocdata,491,Amunhotep.MainForm.StyleManager.Colors.Window    );
    CreateTxcTabSheet(lkPC,'tsCharts',msg_erp_tscharts ,376,Amunhotep.MainForm.StyleManager.Colors.Highlight );
    CreateTxcTabSheet(lkPC,'tsSQL'   ,msg_erp_tssql    ,290,Amunhotep.MainForm.StyleManager.Colors.Error     );
    lkSB  := CreateTScrollBox(Result,lkPC.Pages[0],obj_name_erp_scrollboxmain,0,0,600,600,alClient);
    lkPCDetail := CreateTxcPageControlEx(Result, lkPC.Pages[1], obj_name_erp_pagecontroldetail, 0,36,200,600, alBottom);
    lkPCDetail.Visible := false;
    lkDBG := CreateTDBGridEh (Result,lkPC.Pages[1],lkDS,obj_name_erp_data_dbgmain, 0,100,200,200,alClient);
    with lkDBG do
      begin
      HelpKeyWord   := '0';
      DataSource := lkDSMT;
      with STFilter do
        begin
        InstantApply := true;
        Local        := true;
        Location     := stflUnderTitleFilterEh;
        Visible      := true;
        end;
      with IndicatorTitle do
        begin
        UseGlobalMenu    := true;
        ShowDropDownSign := true;
        TitleButton      := true;
        end;
      Options      := Options   + [dgMultiSelect, dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghAutoSortMarking, dghMultiSortMarking, 
                      dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, dghExtendVertLines];
      AllowedOperations := [];
      EditActions  := [geaCopyEh, geaSelectAllEh];
      SortLocal    := true;
      VTitleMargin := 8;
      Columns.Clear;
      end;
    lkTBTerm := CreateTxcGradientPanelVistaToolBar(Result,lkPC.Pages[0],'tb'+lkPC.Pages[0].Name,'',alTop,0,0,24,600,xbsRaized);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewrefresh,msg_erp_actviewrefresh2,msg_erp_actviewrefresh2_hint,SHORTCUT_DATA_REFRESH,0,170,@TERPFormRpti_actViewRefresh_OnExecute,nil                                 ,lkTBTerm     ,lkMIMenuMain);
    with TxcToolBarButton(lkTBTerm.Controls[0]) do
      begin
      Width       := 96;
      ShowCaption := true;
      end;
    lkTBData    := CreateTxcGradientPanelVistaToolBar(Result,lkPC.Pages[1],'tb'+lkPC.Pages[1].Name,'',alTop,0,0,24,600,xbsRaized);
    lkTBB := CreateTxcToolBarButton(lkTBData, lkTBData,'tbb'+lkAct.Name, '','', 1,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultEditButtonWidth, alLeft, -1, lkAct);
    with lkTBB do
      begin
      ShowCaption := true;
      end;
    if(lkQrLoad.FieldByName('TB_ACCS_PRN_CNT').AsInteger > 0)then
      begin
      lkMI  := CreateTMenuItem(lkMIObj,obj_name_erp_mimainobjprint_h ,msg_erp_mimainobjprint_h ,'','', -1,0); 
      lkAct := TERPForm_CreateAction2(Result,obj_name_erp_actprintgrid,msg_erp_actprintgrid,msg_erp_actprintgrid_hint,SHORTCUT_PRINT,0,237,@TERPFormRpti_actPrintGrid_OnExecute,@TERPFormRpti_actPrintGrid_OnUpdate,lkTBData,64,lkMIObj);
      end;
    CreateTMenuItem(lkMIMenuMain,obj_name_erp_mimaindb,msg_erp_mimaindb,'','',ERP_ObjectImageIndex(ERP_OBJECTTYPE_RPTS),  0);
    ERP_DBGridEh_StdActions_Create(lkDBG, [erpGrid, erpGridGroup, erpGridNavigation, erpGridExport], lkTBData, lkMIView);
    ERP_DBMenuItems_Build(lkMIMenuMain, aReportGUID, '0', @TERPFormRpti_DatabaseMenuItem_OnClick);
    // for backward compability !
    lkTBDataView:= CreateTxcGradientPanelVistaToolBar(Result,lkTBData,obj_name_erp_toolbar_view  ,'',alLeft,2000,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkTBDataView.Width := TWinControl_AutoWidth2(lkTBDataView)+2;  
    lkTBDataNav := CreateTxcGradientPanelVistaToolBar(Result,lkTBData,obj_name_erp_toolbar_nav   ,'',alLeft,2200,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkTBDataNav.Width := TWinControl_AutoWidth2(lkTBDataNav)+2;  
    lkTBDataExp := CreateTxcGradientPanelVistaToolBar(Result,lkTBData,obj_name_erp_toolbar_export,'',alLeft,2400,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkTBDataExp.Width := TWinControl_AutoWidth2(lkTBDataExp)+2;  
    RegisterSynEdit(Interface_SynEdit_Create(Result, lkPC.Pages[3], 'SynEdit'), ftSQL);
    if(GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT) <> 'PEAKTOP')then
      lkPC.Pages[3].PageControl := nil;
    TERPFormRpti_OnTerms(Result, lkSB);
    if not TERPFormRpti_OnColumnsCreate(Result, lkDBG) then
      begin
      if lkQrLoad.Active then
        lkQrLoad.Close;
      lkQrLoad.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETCOLUMNS_REF));
      lkQrLoad.Prepare;
      lkQrLoad.ParamByName('PQ_TB_ID'   ).AsString := aReportGUID;
      lkQrLoad.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
      lkQrLoad.Open;
      if not(lkQrLoad.Active)then
        begin
        if lkTrLoad.InTransaction then
          lkTrLoad.Commit;
        lkTrLoad.Free;
        Dialogs.MessageDlg(msg_error_erpsql+' "'+aReportGUID+'" !',mtWarning,[mbOk]);
        end;  
      TERPFormRpti_ColumnsCreate(Result, lkDBG, lkQrLoad);
      end;
    TERPForm_GridSettingsLoad(TERPForm_DBGridMain(Result), lkSettings.Values[ERP_SETTINGS_TEMPFILENAME]);
    TERPFormRpti_OnColumnsCreated(Result, lkDBG); 
    lkDBG.FooterRowCount := StrToInt(lkDBG.HelpKeyWord);
    if(lkDBG.FooterRowCount > 0)then
      lkDBG.SumList.Active := true;
    TERPFormRpti_OnChart(Result, lkPC.Pages[2]);
    if lkTrLoad.InTransaction then
      lkTrLoad.Commit;
    lkTrLoad.Free;
    TxcPageControlEx_ActivateDefaultPage(lkPC);
    if(lkPCDetail.PageCount > 0)then
      begin
      lkPCDetail.Visible := true;
      lkSplt := CreateTSplitter(Result,lkPCDetail.Parent,obj_name_erp_splitterdetail,alBottom,0,lkPCDetail.Top-2,4,800);
      end;
    ERP_ObjectExtension_Call(Result, lkPCDetail, lkMT); 
  end;                   
