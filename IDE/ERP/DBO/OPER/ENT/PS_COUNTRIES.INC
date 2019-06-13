{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/ENT/PS_COUNTRIES.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                        {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                        {$I PEAKTOP:OBJ/TXFBDATASETS.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                             {$I PEAKTOP:OBJ/TACTION.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                          {$I PEAKTOP:OBJ/TIMAGELIST.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                              {$I PEAKTOP:OBJ/TLABEL.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                           {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                           {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBEDITEH.INC}                           {$I PEAKTOP:OBJ/TDBEDITEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                    {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}               {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBAR.INC}                         {$I PEAKTOP:OBJ/TXCGROUPBAR.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBOX.INC}                         {$I PEAKTOP:OBJ/TXCGROUPBOX.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                    {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                    {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                         {$I PEAKTOP:OBJ/TXCTABSHEET.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBCTRLGRID.INC}                         {$I PEAKTOP:OBJ/TDBCTRLGRID.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                           {$I PEAKTOP:OBJ/TSPLITTER.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCDBLABEL.INC}                          {$I PEAKTOP:OBJ/TXCDBLABEL.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}              {$I ../../DBGRID/ACTIONS.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}        {$I ../../$COMMON/FORMERP_LANG.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}             {$I ../../$COMMON/FORMERP.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/ENT/PS_COUNTRIES_LANG.INC}  {$I ./PS_COUNTRIES_LANG.INC}                 {$ENDIF}  
  //============= PEAKTOP:IDE/ERP/DBO/OPER/ENT/PS_COUNTRIES.INC ================
  procedure TERPFormOperENTPSCountries_DTSMain_AfterScroll(DataSet :TDataSet);
  begin
//    TxcPageControlEx(DataSet.Owner.Owner.FindComponent(obj_name_erp_pagecontroldetail)).Pages[2].Visible := (DataSet.FieldByName('FLAG_GRID').AsInteger = 1);
  end;
  //============================================================================
  procedure TERPFormOperENTPSCountries_DTSGrid_OnNewRecord(DataSet :TDataSet);
  begin
    with TxFBDataSet(DataSet) do
      begin
      FieldByName('COUNTRIESTP_ID').AsString := DataSource.DataSet.FieldByName('ID').AsString;
      FieldByName('ID'            ).AsString := '0';
      FieldByName('NAME'          ).AsString := '';
      FieldByName('FLAG_DELETE'   ).AsString := '0';
      FieldByName('SUMMIN'        ).AsString := '0';
      FieldByName('SUMMAX'        ).AsString := '0';
      FieldByName('DAYSFROM'      ).AsString := '0';
      FieldByName('DAYSTO'        ).AsString := '0';
      FieldByName('PC'            ).AsString := '0';
      FieldByName('PCPEN'         ).AsString := '0';
      end;
  end;
  //============================================================================
  procedure TERPFormOperENTPSSettingsCountries_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end; 
  //============================================================================
  function TERPFormOperENTPSCountries_Create:TAmunhotepForm;
  var
    lkSettings    :TStrings;
    lkMainMenu    :TMainMenu;
    lkMIMenuMain  :TMenuItem;
    lkMIView      :TMenuItem;
    lkMIObj       :TMenuItem;
    lkMIPrint     :TMenuItem;
    lkMI          :TMenuItem;
    lkGB          :TxcGroupBox;
    lkPnlLeft     :TxcGradientPanel;
    lkToolBarLeft :TxcGradientPanelVista;
    lkSplt        :TSplitter;
    lkPCDetail    :TxcPageControlEx;
    lkTr          :TxFBTransaction;
    lkDTS         :TxFBDataSet;
    lkDS          :TDataSource;
    lkDBCG        :TDBCtrlGrid;
    lkDBL         :TxcDBLabel;
    lkDBCGParent  :TWinControl; 
    lkDTSEx       :TxFBDataSet;
    lkDSEx        :TDataSource;
    lkDBGEx       :TDBGridEh;
    lkCol         :TColumnEh;
    lkToolBarEx   :TxcGradientPanelVista;
    lkDTSGrid     :TxFBDataSet;
    lkDSGrid      :TDataSource;
    lkDBGGrid     :TDBGridEh;
    lkToolBarGrid :TxcGradientPanelVista;
    lkLastTop,i   :Integer;   
  begin
    DontAutoFree;
    Result := TAmunhotepForm(TERPForm_Create(msg_erp_entps_settings_countries, ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), false, @TERPFormOperENTPSSettingsCountries_OnClose));
    lkLastTop := 0;
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      lkLastTop := Top + Height;
      end;  
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_BUFFERVAR       ] := '';
      Values[ERP_SETTINGS_TABLENAME       ] := '';
      Values[ERP_SETTINGS_TABLECAPTION    ] := msg_erp_entps_settings_countries;
      Values[ERP_SETTINGS_REF_TREE        ] := '0';
      Values[ERP_SETTINGS_REF_TREEORGROUP ] := '0';
      Values[ERP_SETTINGS_REF_TREEFIELD   ] := '';
      Values[ERP_SETTINGS_BASETYPE        ] := IntToStr(ERP_OBJECTTYPE_OPER);
      Values[ERP_SETTINGS_TEMPFILENAME    ] := 'TMP:'+ERP_DIRECTORY_CFG+'/OPER_ENTPS_SETTINGS_COUNTRIES.CFG'
      end;
    // data model  
    CreateTxFBTransDataSet(Result, obj_name_erp_data_trmain, obj_name_erp_data_dtsmain, 'DataSource'+obj_name_erp_data_dtsmain, ['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);
    with lkDTS do
      begin
      SelectSQL.Text  := 'SELECT R.* FROM TABL$R_COUNTRIESTP R ORDER BY R.ID ';
      RefreshSQL.Text := 'SELECT FIRST 1 R.* FROM TABL$R_COUNTRIESTP R WHERE (R.ID = ?ID)';
      ModifySQL.Text  := 
        'UPDATE TABL$R_COUNTRIESTP P SET '+SQLCRLF+
        '   P.NAME           = ?NAME '+SQLCRLF+
        '  ,P.FLAG_DELETE    = ?FLAG_DELETE '+SQLCRLF+
        '  ,P.PC             = ?PC '+SQLCRLF+
        '  ,P.PCPEN          = ?PCPEN '+SQLCRLF+
        '  ,P.MINDAYSCNT     = ?MINDAYSCNT '+SQLCRLF+
        '  ,P.FLAG_GRID      = ?FLAG_GRID '+SQLCRLF+
        '  ,P.FLAG_OVERDRAFT = ?FLAG_OVERDRAFT '+SQLCRLF+
        '  ,P.FLAG_GROUP     = ?FLAG_GROUP '+SQLCRLF+
//        '  ,P.FLAG_BEFORE    = ?FLAG_BEFORE '+SQLCRLF+
        'WHERE (P.ID = ?ID);';      
      AfterOpen       := @TERPForm_OpenDataSetsChilds;
      BeforeClose     := @TERPForm_CloseDataSetsChilds;
      AfterScroll     := @TERPFormOperENTPSCountries_DTSMain_AfterScroll;
      end;  
    lkDTSEx := TxFBDataSet.Create(lkDTS);
    with lkDTSEx do
      begin
      Name            := obj_name_erp_data_dtsdata+'Ex';
      DataBase        := lkDTS.DataBase;
      Transaction     := lkDTS.Transaction;
      DataSource      := lkDS;
      SelectSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/OPER/ENT/PS_COUNTRIES_EX_SEL.SQL'));
      RefreshSQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/OPER/ENT/PS_COUNTRIES_EX_REF.SQL'));
      ModifySQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/OPER/ENT/PS_COUNTRIES_EX_UPD.SQL'));
      end;
    lkDSEx  := TDataSource.Create(lkDTSEx);
    with lkDSEx do
      begin
      Name    := 'DataSource'+lkDTSEx.Name;
      DataSet := lkDTSEx;
      end;
    lkDTSGrid := TxFBDataSet.Create(lkDTS);
    with lkDTSGrid do
      begin
      Name            := obj_name_erp_data_dtsdata+'Grid';
      DataBase        := lkDTS.DataBase;
      Transaction     := lkDTS.Transaction;
      DataSource      := lkDS;
      SelectSQL.Text  := 
        'SELECT G.COUNTRIESTP_ID, G.ID, G.NAME, G.FLAG_DELETE, G.SUMMIN, G.SUMMAX, G.DAYSFROM, G.DAYSTO, G.PC, G.PCPEN '+SQLCRLF+
        'FROM   TABL$R_COUNTRIESGRID G '+SQLCRLF+
        'WHERE  (G.COUNTRIESTP_ID = ?ID) '+SQLCRLF+
        'ORDER BY G.DAYSFROM, G.SUMMIN';
      RefreshSQL.Text  := 
        'SELECT FIRST 1 G.COUNTRIESTP_ID, G.ID, G.NAME, G.FLAG_DELETE, G.SUMMAX, G.SUMMIN, G.DAYSFROM, G.DAYSTO, G.PC, G.PCPEN '+SQLCRLF+
        'FROM   TABL$R_COUNTRIESGRID G '+SQLCRLF+
        'WHERE  (G.ID = ?ID)';
      InsertSQL.Text  := 
        'INSERT INTO TABL$R_COUNTRIESGRID (COUNTRIESTP_ID, ID, NAME, FLAG_DELETE, SUMMIN, '+SQLCRLF+
        '  SUMMAX, DAYSFROM, DAYSTO, PC, PCPEN) '+SQLCRLF+
        'VALUES (?COUNTRIESTP_ID, ?ID, ?NAME, ?FLAG_DELETE, ?SUMMIN, '+SQLCRLF+
        '  ?SUMMAX, ?DAYSFROM, ?DAYSTO, ?PC, ?PCPEN); ';
      ModifySQL.Text  := 
        'UPDATE TABL$R_COUNTRIESGRID SET '+SQLCRLF+
        '   COUNTRIESTP_ID = ?COUNTRIESTP_ID '+SQLCRLF+
        '  ,NAME           = ?NAME '+SQLCRLF+
        '  ,FLAG_DELETE    = ?FLAG_DELETE '+SQLCRLF+
        '  ,SUMMIN         = ?SUMMIN '+SQLCRLF+
        '  ,SUMMAX         = ?SUMMAX '+SQLCRLF+
        '  ,DAYSFROM       = ?DAYSFROM '+SQLCRLF+
        '  ,DAYSTO         = ?DAYSTO '+SQLCRLF+
        '  ,PC             = ?PC '+SQLCRLF+
        '  ,PCPEN          = ?PCPEN '+SQLCRLF+
        'WHERE (ID = ?ID); ';
      DeleteSQL.Text := 'DELETE FROM TABL$R_COUNTRIESGRID T WHERE (T.ID = ?ID); ';
      OnNewRecord := @TERPFormOperENTPSCountries_DTSGrid_OnNewRecord;  
      end;
    lkDSGrid  := TDataSource.Create(lkDTSGrid);
    with lkDSGrid do
      begin
      Name    := 'DataSource'+lkDTSGrid.Name;
      DataSet := lkDTSGrid;
      end;

    lkMainMenu    := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIMenuMain  := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,ERP_ObjectCaption(ERP_OBJECTTYPE_OPER),'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
    lkMIObj       := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainobj       ,msg_erp_mimainobj     ,'','',ERP_ObjectImageIndex(ERP_OBJECTTYPE_OPER),0);
    lkMIView      := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainview      ,msg_erp_mimainview    ,'','',150,0);
    lkMIPrint     := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainobjprint_h,msg_erp_mimainobjprint,'','',104,0);
    lkGB          := CreateTxcGroupBox(Result, Result, 'gbGlobal', 'Глобальные настройки', alTop, 0,lkLastTop+1,120,200);
    with lkGB do
      begin
      Font.Size  := 8;
      Font.Style := [fsBold];
      lkLastTop  := lkLastTop + Height;
      end;
    lkPnlLeft := CreateTxcGradientPanel(Result, Result, obj_name_erp_panelleft, '', alLeft, 0, lkLastTop, 200, 220, xbsNone, gdLeftToRight); 
    with CreateTxcGradientPanelVista(lkPnlLeft, lkPnlLeft, obj_name_erp_panelleft+'Caption', msg_erp_entps_settings_courses, alTop, 0,0,24,200, xbsRaized) do
      begin
      Font.Size  := 8;
      Font.Style := [fsBold];
      end; 
    lkToolBarLeft := CreateTxcGradientPanelVistaToolBar(lkPnlLeft, lkPnlLeft, lkPnlLeft.Name+'ToolBar', '', alTop, 0,24,24,200, xbsRaized);
    
    lkDBCG := CreateTDBCtrlGrid(Result, lkPnlLeft, obj_name_erp_dbctrlgrid, 0, 0, 200, 220, alClient, 1, 10);
    with lkDBCG do
      begin
      DataSource  := lkDS;
      Orientation := goVertical;
      PanelHeight := 24;
      Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
      AllowInsert := false;
      AllowDelete := false;
      end;
    lkDBCGParent := nil;
    for i:=0 to lkDBCG.ControlCount-1 do
      if(UpperCase(lkDBCG.Controls[i].ClassName) = 'TDBCTRLPANEL')then
        begin
        lkDBCGParent := TWinControl(lkDBCG.Controls[i]);
        break;
        end;  
    lkDBL := CreateTxcDBLabel(lkDBCG, lkDBCGParent, lkDS, 'NAME', 0, 0, 200, 200, alClient, taCenter);
    with lkDBL do
      begin
      Layout       := taTop;
      Font.Size    := 10;
      Font.Style   := [fsBold];
      FlatColor    := Amunhotep.MainForm.StyleManager.Colors.Background;
      FlyByColor   := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
      FlyByEnabled := true;
      ShadowColor  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      TextStyle    := tsNormal;
      end;
    lkSplt := CreateTSplitter(Result, Result, '', alLeft, lkPnlLeft.Left+lkPnlLeft.Width, 0, 200, 4);  
    lkPCDetail := CreateTxcPageControlEx(Result,Result,obj_name_erp_pagecontroldetail,0,lkLastTop+1,200,200,alClient);
    CreateTxcTabSheet(lkPCDetail,'tsCOUNTRIESTP'  ,msg_erp_entps_settings              , 53,Amunhotep.MainForm.StyleManager.Colors.Window);
    CreateTxcTabSheet(lkPCDetail,'tsCOUNTRIESEX'  ,msg_erp_entps_settings_metals_course,260,$C0FFFF);
    CreateTxcTabSheet(lkPCDetail,'tsCOUNTRIESGRID',msg_erp_entps_settings_pc_grids     ,342,ERP_ObjectColor(ERP_OBJECTTYPE_OPER));
    TxcPageControlEx_ActivateDefaultPage(lkPCDetail);
    //--------- CourceSettings
    
    //--------- CountriesEx
    lkToolBarEx := CreateTxcGradientPanelVistaToolBar(lkPCDetail.Pages[1], lkPCDetail.Pages[1], lkPCDetail.Pages[1].Name+'ToolBar', '', alTop, 0,0,24,200, xbsRaized);
    lkDBGEx := CreateTDBGridEh(Result,lkPCDetail.Pages[1],lkDSEx,obj_name_erp_data_dbgdata+lkPCDetail.Pages[1].Name, 0,100,200,200,alClient);
    with lkDBGEx do
      begin
      Color       := lkPCDetail.Pages[1].Color;
      Font.Style  := [fsBold]; 
      Font.Size   := 8; 
      HelpKeyWord := '0';
      with IndicatorTitle do
        begin
        UseGlobalMenu    := true;
        ShowDropDownSign := true;
        TitleButton      := true;
        end;
      Options      := Options   + [dgAlwaysShowSelection] - [dgMultiSelect];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, 
         dghExtendVertLines, dghHotTrack] - [dghAutoSortMarking, dghMultiSortMarking];
      EditActions  := [geaSelectAllEh, geaCopyEh];
      ShowHint     := true;
      VTitleMargin := 4;
      Columns.Clear;
      end; 
    lkMI := CreateTMenuItem(lkMIView,lkPCDetail.Pages[1].Name+'View',lkPCDetail.Pages[1].Caption,'','',lkPCDetail.Pages[1].ImageIndex,0);
    ERP_DBGridEh_StdActions_Create(lkDBGEx, [erpGrid, erpGridNavigation, erpGridExport], lkToolBarEx, lkMI);
    lkCol := CreateTColumnEh(lkDBGEx, 'PROBE', '', msg_erp_entps_settings_metals_probe, 56, taCenter);
    with lkCol do
      begin
      Color      := Amunhotep.MainForm.StyleManager.Colors.Foreground + $101010;
      ReadOnly   := true;
      end;
    lkCol := CreateTColumnEh(lkDBGEx, 'KURS1000086', '# ### ##0.00', msg_erp_entps_settings_metals+'|'+msg_erp_entps_settings_metals_au, 72, taRightJustify);
    with lkCol do
      begin
      ButtonStyle          := cbsDropDown          
      AutoDropDown         := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBGEx, 'KURS1000087', '# ### ##0.00', msg_erp_entps_settings_metals+'|'+msg_erp_entps_settings_metals_ag, 72, taRightJustify);
    with lkCol do
      begin
      ButtonStyle          := cbsDropDown          
      AutoDropDown         := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBGEx, 'KURS1000088', '# ### ##0.00', msg_erp_entps_settings_metals+'|'+msg_erp_entps_settings_metals_pt, 72, taRightJustify);
    with lkCol do
      begin
      ButtonStyle          := cbsDropDown          
      AutoDropDown         := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBGEx, 'KURS1000089', '# ### ##0.00', msg_erp_entps_settings_metals+'|'+msg_erp_entps_settings_metals_pd, 72, taRightJustify);
    with lkCol do
      begin
      ButtonStyle          := cbsDropDown          
      AutoDropDown         := true;
      AlwaysShowEditButton := true;
      end;
    lkDBGEx.FrozenCols := 1;   
    //--------- PC Grids
    lkToolBarGrid := CreateTxcGradientPanelVistaToolBar(lkPCDetail.Pages[2], lkPCDetail.Pages[2], lkPCDetail.Pages[2].Name+'ToolBar', '', alTop, 0,0,24,200, xbsRaized);
    lkDBGGrid := CreateTDBGridEh(Result,lkPCDetail.Pages[2],lkDSGrid,obj_name_erp_data_dbgdata+lkPCDetail.Pages[2].Name, 0,100,200,200,alClient);
    with lkDBGGrid do
      begin
      Color       := lkPCDetail.Pages[2].Color;
      Font.Style  := [fsBold]; 
      Font.Size   := 8; 
      HelpKeyWord := '0';
      with IndicatorTitle do
        begin
        UseGlobalMenu    := true;
        ShowDropDownSign := true;
        TitleButton      := true;
        end;
      Options      := Options   + [dgAlwaysShowSelection] - [dgMultiSelect];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D,  
        dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, dghExtendVertLines, dghHotTrack] - [dghAutoSortMarking, dghMultiSortMarking];
      EditActions  := [geaSelectAllEh, geaCopyEh];
      ShowHint     := true;
      VTitleMargin := 4;
      Columns.Clear;
      end; 
    lkMI := CreateTMenuItem(lkMIView,lkPCDetail.Pages[2].Name+'View',lkPCDetail.Pages[2].Caption,'','',lkPCDetail.Pages[2].ImageIndex,0);
    ERP_DBGridEh_StdActions_Create(lkDBGGrid, [erpGrid, erpGridNavigation, erpGridExport], lkToolBarGrid, lkMI);
    lkCol := CreateTColumnEh(lkDBGGrid, 'ID', '# ### ##0', msg_erp_entps_settings_grid_recid, 80, taRightJustify);
    with lkCol do
      begin
      Color      := Amunhotep.MainForm.StyleManager.Colors.Foreground + $101010;
      ReadOnly   := true;
      end;   
    lkCol := CreateTColumnEh(lkDBGGrid, 'SUMMIN', '# ### ##0.00', msg_erp_entps_settings_grid_summin, 80, taRightJustify);
    with lkCol do
      begin
      HideDuplicates       := true;
      ButtonStyle          := cbsDropDown          
      AutoDropDown         := true;
      AlwaysShowEditButton := true;
      end;   
    lkCol := CreateTColumnEh(lkDBGGrid, 'DAYSFROM', '# ### ##0' , msg_erp_entps_settings_grid_daysfrom, 80, taRightJustify);
    with lkCol do
      begin
      HideDuplicates       := true;
      ButtonStyle          := cbsDropDown          
      AutoDropDown         := true;
      AlwaysShowEditButton := true;
      end;   
    lkCol := CreateTColumnEh(lkDBGGrid, 'PC', '# ### ##0.00', msg_erp_entps_settings_grid_dayspc, 80, taRightJustify);
    with lkCol do
      begin
      ButtonStyle          := cbsDropDown          
      AutoDropDown         := true;
      AlwaysShowEditButton := true;
      end;   
    lkCol := CreateTColumnEh(lkDBGGrid, 'PCPEN', '# ### ##0.00',msg_erp_entps_settings_grid_dayspcpen, 80, taRightJustify);
    with lkCol do
      begin
      Color := $00FFC0FF;
      ButtonStyle          := cbsDropDown          
      AutoDropDown         := true;
      AlwaysShowEditButton := true;
      end;   
    lkCol := CreateTColumnEh(lkDBGGrid, 'NAME', '', msg_erp_entps_settings_grid_coment, 400, taLeftJustify);
    lkDBGGrid.FrozenCols := 1;   
    //-----------------
    Amunhotep.MainForm.xcMenu.AddMenu(lkMainMenu); lkMainMenu.OwnerDraw := true;
    Result.Menu := lkMainMenu;
    try lkDTS.Open; except end;
  end;
