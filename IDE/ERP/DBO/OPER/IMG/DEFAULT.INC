{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/IMG/DEFAULT.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                              {$I PEAKTOP:OBJ/TLABEL.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGE.INC}                              {$I PEAKTOP:OBJ/TIMAGE.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}                           {$I PEAKTOP:OBJ/TMENUITEM.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                           {$I PEAKTOP:OBJ/TSPLITTER.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                    {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}               {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                            {$I PEAKTOP:OBJ/TXCPANEL.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                    {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                    {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                         {$I PEAKTOP:OBJ/TXCTABSHEET.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSCROLLBOX.INC}                          {$I PEAKTOP:OBJ/TSCROLLBOX.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                        {$I PEAKTOP:OBJ/TXFBDATASETS.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                           {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                           {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/DBINTERFACE/IMAGE.INC}                   {$I PEAKTOP:OBJ/DBINTERFACE/IMAGE.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/DBINTERFACE/TEXT.INC}                    {$I PEAKTOP:OBJ/DBINTERFACE/TEXT.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC}         {$I ../../DBGRID/COL_PROTOCOL.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC}         {$I ../../DBGRID/FOOTERS_LOAD.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}              {$I ../../DBGRID/ACTIONS.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}             {$I ../../$COMMON/FORMERP.INC}               {$ENDIF}
  //============================================================================
  procedure TERPFormOperIMG_CloseDataSets(aOwner :TComponent);
  var
    lkSettings :TStrings;
  begin
    lkSettings := TERPForm_Settings(aOwner);
    if(TERPForm_TransactionMain(aOwner).InTransaction)then
      begin
      with TERPForm_DataSetMain(aOwner) do
        if Active then
          begin
          if(State <> dsBrowse)then
            try
              Post;
            except
              Cancel;
            end;
          lkSettings.Values[ERP_SETTINGS_BOOKMARK] := '1';  
          lkSettings.Values[ERP_SETTINGS_SAVERECNO] := IntToStr(RecNo);  
          Close;   
          end;
      TERPForm_TransactionMain(aOwner).Commit;
      end;
  end;
  //============================================================================
  procedure TERPFormOperIMG_RefreshView(aOwner :TComponent);
  var
    lkSettings :TStrings;
  begin
    TERPFormOperIMG_CloseDataSets(aOwner);
    lkSettings := TERPForm_Settings(aOwner); 
    with TERPForm_DataSetMain(aOwner) do
      begin
      Prepare;
      ParamByName('OBJ_ID').AsString := lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD];  
      ParamByName('REC_ID').AsString := lkSettings.Values[ERP_SETTINGS_REF_TREE     ];  
      Open;
      end;
    with TERPForm_Settings(aOwner) do  
      if( Values[ERP_SETTINGS_BOOKMARK] = '1' )then
        begin
        if TERPForm_DBGridMain(aOwner).DataSource.DataSet.Active then   
          TERPForm_DBGridMain(aOwner).DataSource.DataSet.RecNo := StrToInt(Values[ERP_SETTINGS_SAVERECNO]);
        Values[ERP_SETTINGS_SAVERECNO] := '0';
        Values[ERP_SETTINGS_BOOKMARK ] := '0';
        end;  
  end;
  //============================================================================
  procedure TERPFormOperIMG_actViewRefresh_OnExecute(Sender :TObject);
  begin
    TERPFormOperIMG_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormOperIMG_DataSetMain_OnNewRecord(DataSet :TDataSet);
  var
    lkSettings :TStrings;
    lkDBG      :TDBGridEh;
    lkStr      :string;
  begin
    lkDBG      := TERPForm_DBGridMain(DataSet.Owner.Owner);
    lkSettings := TERPForm_Settings(lkDBG.Owner);
    TERPForm_DBGrid_FillValuesGrid(DataSet, TERPForm_DataSetMain(DataSet.Owner.Owner), lkDBG);
    DataSet.FieldByName('DATE_COMMIT').AsDateTime := Now;
    DataSet.FieldByName('USER_ID'    ).AsString   := GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT);
    lkStr := '';
    if GetField(FBDataBase, 'TABL$R_WRK', 'NAME', 'USER_NAME = '''+GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+'''', lkStr)then
      DataSet.FieldByName('USER_NAME').AsString   := lkStr;

    lkStr := '';
    if GetField(FBDataBase, lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD], 'NAME', 'ID = '''+lkSettings.Values[ERP_SETTINGS_REF_TREE]+'''', lkStr)then
      DataSet.FieldByName('NAME'     ).AsString   := lkStr + ' [' + FormatDateTime('dd.mm.yyyy hh:nn:ss', Now)+']';
  end;
  //============================================================================
  procedure TERPFormOperIMG_DataSetMain_AfterPost(DataSet :TDataSet);
  begin
    TERPFormOperIMG_RefreshView(DataSet.Owner.Owner);
  end;
  //============================================================================
  procedure TERPFormOperIMG_evMain_OnEventAlert(Sender :TObject; EventName: string; EventCount: LongInt; var CancelAlerts: Boolean);
  begin
    TERPFormOperIMG_RefreshView(TComponent(Sender).Owner);
    CancelAlerts := false;
  end;
  //============================================================================
  procedure TERPFormOperIMG_actPrintItem_OnExecute(Sender :TObject);
  var
    lkDBG      :TDBGridEh;
    lkSQL      :string;
    lkStr      :string;
    lkRpt      :TxReport;
    lkBndDetail:TxrBand;
    lkImg      :TxrDBImage;
    lkLbl      :TxrLabel;
  begin
    lkDBG      := TERPForm_DBGridMain(TComponent(Sender).Owner);
    if not lkDBG.DataSource.DataSet.Active then exit;
    if not (lkDBG.DataSource.DataSet.RecordCount > 0)then exit;
    lkSQL := StringsLoadFromFile( StrAbsolutePath('./PRINTITEM.SQL', ScriptName) );
    lkSQL := StrReplaceStr(lkSQL, '?ID', ''''+lkDBG.DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''' );
    lkRpt := TxReport.Create(nil);
    lkRpt.DataBase := FBDataBase;
    while(lkRpt.DataSets.Count < 1)do
      lkRpt.DataSets.Add;
    lkRpt.DataSets[0].SQL.Text := lkSQL;
    lkRpt.DataSetIndex         := 0;
    lkRpt.Page.Columns         := 1;
    lkRpt.Page.Orientation     := poLandscape;
    lkRpt.Page.PaperSize       := A4;
    lkBndDetail                := TxrBand.Create(lkRpt);
    lkBndDetail.Parent         := lkRpt;
    lkBndDetail.ParentReport   := lkRpt;
    lkBndDetail.BandType       := rbDetail;
    lkBndDetail.Height         := 602;
    lkBndDetail.Frame.Left     := True;
    {
    lkLbl              := TxrLabel.Create(lkRpt);
    lkLbl.Parent       := lkBndDetail;
    lkLbl.Left         := 1;
    lkLbl.Top          := 1;
    lkLbl.Height       := 16;
    lkLbl.Width        := 1024;
    lkLbl.Align        := alTop;
    lkLbl.Caption      := 'Test';
    }
    lkImg              := TxrDBImage.Create(lkRpt);
    lkImg.Parent       := lkBndDetail;
    lkImg.Left         := 1;
    lkImg.Top          := 1;
    lkImg.Height       := lkBndDetail.Height - 1;
    lkImg.Width        := Trunc(lkBndDetail.Height / 2 * 3) - 1;
    lkImg.Align        := alLeft;
    lkImg.Stretch      := True;
    lkImg.DataSetIndex := 0;
    lkImg.DataField    := 'IMG';
    lkRpt.Prepare;
    lkRpt.Preview;
  end;
  //============================================================================
  procedure TERPFormOperIMG_actPrintItem_OnUpdate(Sender :TObject);
  var
    lkDBG     :TDBGridEh;
    lkEnabled :Boolean;
  begin
    lkDBG := TERPForm_DBGridMain(TComponent(Sender).Owner);
    lkEnabled := lkDBG.DataSource.DataSet.Active;
    if lkEnabled then
      lkEnabled := (lkDBG.DataSource.DataSet.RecordCount > 0);
    TCustomAction(Sender).Enabled := lkEnabled;  
  end;
  //============================================================================
  procedure TERPFormOperIMG_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    with TxFBEvents(TComponent(Sender).FindComponent(obj_name_erp_data_evmain)) do
      if Registered then
        UnRegisterEvents;
    TERPFormOperIMG_CloseDataSets(TComponent(Sender));
    Action := caFree;
    AutoFree; 
  end; 
  //============================================================================
  function TERPFormOperIMG_Create(const aOBJ_ID, aREC_ID:string):TAmunhotepForm;
  var
    lkSettings    :TStrings;
    lkMainMenu    :TMainMenu;
    lkMIMenuMain  :TMenuItem;
    lkMIView      :TMenuItem;
    lkMIItem      :TMenuItem;
    lkImg         :TImage;
    lkLBL         :TLabel;
    lkTBB         :TxcToolBarButton;
    lkPanelTop    :TxcGradientPanel;
    lkPanelLeft   :TxcPanel;
    lkPanelClient :TxcPanel;
    lkToolBar     :TxcGradientPanelVista;
    lkSplt        :TSplitter;
    lkPCDetail    :TxcPageControlEx;
    lkTS          :TxcTabSheet;
    lkEvents      :TxFBEvents;
    lkTr          :TxFBTransaction;
    lkDTS         :TxFBDataSet;
    lkQr          :TxFBQuery;
    lkDS          :TDataSource;
    lkDBG         :TDBGridEh;
    lkCol         :TColumnEh;
    lkAct         :TCustomAction;
    lkLastTop     :Integer;
  begin
    DontAutoFree;
    Result := TAmunhotepForm(TERPForm_Create('Изображения объекта', 'PEAKTOP:IMG/CONFIG/MIME/BMP0016X0016.ICO', 'PEAKTOP:IMG/CONFIG/MIME/BMP0032X0032.BMP', false, @TERPFormOperIMG_OnClose));
    lkLastTop := 1;
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_DOC);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_DOC);
      lkLastTop := MaxInteger(lkLastTop, (Top+Height+1));
      end;  
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_BUFFERVAR      ] := 'IMG_ID';
      Values[ERP_SETTINGS_TABLENAME      ] := 'TABL$_IMG';
      Values[ERP_SETTINGS_TABLECAPTION   ] := 'Изображения объекта';
      Values[ERP_SETTINGS_REF_TREE       ] := aREC_ID;
      Values[ERP_SETTINGS_REF_TREEORGROUP] := '0';
      Values[ERP_SETTINGS_REF_TREEFIELD  ] := aOBJ_ID;
      Values[ERP_SETTINGS_ITEM_SCRIPT    ] := ScriptName;
      Values[ERP_SETTINGS_ITEM_SCRIPTDLG ] := '';
      Values[ERP_SETTINGS_BASETYPE       ] := IntToStr(ERP_OBJECTTYPE_OPER);
      Values[ERP_SETTINGS_TEMPFILENAME   ] := ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER,'TABL$_IMG',GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));
      end;
    lkMainMenu    := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIMenuMain  := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,'Изображения','','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
    lkMIItem      := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainitem      ,msg_erp_mimainitem,'','',103,  0);
    lkMIView      := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainview      ,msg_erp_mimainview,'','',150,  0);
    lkPanelTop    := CreateTxcGradientPanel(Result,Result,obj_name_erp_paneltop,'',alTop,1,lkLastTop,64,800,xbsNone, gdRightToLeft);
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQr, lkDS);
    with lkQr do
      begin
      SQL.Text := StringsLoadFromFile(StrAbsolutePath('./DEFAULT_OBJ.SQL',ScriptName));
      Prepare;
      ParamByName('OBJ_ID').AsString := aOBJ_ID;
      ParamByName('REC_ID').AsString := aREC_ID;
      Open;
      First;
      end;
    lkImg := CreateTImage(Result, lkPanelTop, '', alNone, 1,1,33,33);
    lkImg.Picture.LoadFromFile(PrepareAbsoleteFileName(ERP_ObjectBitmap(lkQr.FieldByName('OBJ_TYPE').AsInteger)));
    lkLbl := CreateTLabel(Result, lkPanelTop, ERP_ObjectCaption(lkQr.FieldByName('OBJ_TYPE').AsInteger)+': "'+lkQr.FieldByName('OBJ_NAME').AsString+'"',
      lkImg.Left+lkImg.Width+4, lkImg.Top, lkImg.Height, 1024, alNone, taLeftJustify);
    with lkLBL do
      begin
      Font.Name  := 'Verdana';
      Font.Size  := 14;
      Font.Style := [fsBold];
      end;    
    lkLbl := CreateTLabel(Result, lkPanelTop, '', lkImg.Left, lkImg.Top+lkImg.Height+4, 20, 1024, alNone, taLeftJustify);
    with lkLBL do
      begin
      Caption    := '  Код:"'+aREC_ID+'"; Название: "'+lkQr.FieldByName('REC_NAME').AsString+'"';
      Font.Name  := 'Verdana';
      Font.Size  := 10;
      Font.Style := [fsBold];
      end;    
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      Colors.HotTrack       := ERP_ObjectColorLight(lkQr.FieldByName('OBJ_TYPE').AsInteger);
      Colors.HotTrackBorder := ERP_ObjectColor(lkQr.FieldByName('OBJ_TYPE').AsInteger);
      end;  
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;    
    lkLastTop     := MaxInteger(lkLastTop, lkPanelTop.Top + lkPanelTop.Height + 1);
    lkToolBar     := CreateTxcGradientPanelVistaToolBar(Result,Result,obj_name_erp_toolbar,'',alTop, 1,lkLastTop,TERPForm_DefaultToolButtonWidth+2, 200,xbsRaized);
    lkPanelClient := CreateTxcPanel(Result,Result,obj_name_erp_panelclient,'',alClient,1,lkToolBar.Top+lkToolBar.Height+1,600,800,xbsNone); 
    lkPanelLeft   := CreateTxcPanel(Result,Result,obj_name_erp_panelleft,'',alLeft,1,lkToolBar.Top+lkToolBar.Height+1,600,440,xbsNone); 
    lkSplt := CreateTSplitter(Result,Result,obj_name_erp_splitterleft,alLeft,lkPanelLeft.Left+lkPanelLeft.Width+1,1,4,4);
    TERPForm_CreateAction(Result,obj_name_erp_actviewrefresh,msg_erp_actviewrefresh,msg_erp_actviewrefresh_hint,SHORTCUT_DATA_REFRESH,0,170,@TERPFormOperIMG_actViewRefresh_OnExecute,nil, lkToolBar,lkMIView);
    CreateTxFBTransDataSet(Result, obj_name_erp_data_trmain, obj_name_erp_data_dtsmain, 'DataSource'+obj_name_erp_data_dtsmain, ['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);  
    with lkDTS do
      begin
      with GeneratorField do
        begin 
        ApplyEvent := gamOnServer;
        Field      := 'ID';
        Generator  := 'GENR$_IMG_ID';
        IncrementBy:= 1;
        end;
      SelectSQL.Text := 
        'SELECT I.ID AS '+ERP_DATASET_DBKEY+', I.ID, I.NAME, I.FLAG_DELETE, I.OBJ_ID, I.REC_ID '+SQLCRLF+
        '      ,I.IMG, I.DATE_COMMIT, I.USER_ID, I.DECR '+SQLCRLF+
        '      ,(SELECT FIRST 1 COALESCE(W.NAME, I.USER_ID) FROM TABL$R_WRK W WHERE(W.USER_NAME = I.USER_ID)) AS USER_NAME '+SQLCRLF+
        'FROM   TABL$_IMG I '+SQLCRLF+
        'WHERE  (I.OBJ_ID = ?OBJ_ID) '+SQLCRLF+
        '  AND  (I.REC_ID = ?REC_ID) '+SQLCRLF+
        'ORDER BY I.ID ';
      RefreshSQL.Text := 
        'SELECT I.ID AS '+ERP_DATASET_DBKEY+', I.ID, I.NAME, I.FLAG_DELETE, I.OBJ_ID, I.REC_ID '+SQLCRLF+
        '      ,I.IMG, I.DATE_COMMIT, I.USER_ID, I.DECR '+SQLCRLF+
        '      ,(SELECT FIRST 1 COALESCE(W.NAME, I.USER_ID) FROM TABL$R_WRK W WHERE(W.USER_NAME = I.USER_ID)) AS USER_NAME '+SQLCRLF+
        'FROM   TABL$_IMG I '+SQLCRLF+
        'WHERE  (I.ID = ?'+ERP_DATASET_DBKEY+') '+SQLCRLF;
      InsertSQL.Text := 
        'INSERT INTO TABL$_IMG (ID, NAME, FLAG_DELETE, OBJ_ID, REC_ID, IMG, DATE_COMMIT, USER_ID, DECR) '+SQLCRLF+
        '  VALUES(?ID, ?NAME, ?FLAG_DELETE, '''+aOBJ_ID+''', '''+aREC_ID+''', ?IMG, ?DATE_COMMIT, ?USER_ID, ?DECR); ';
      ModifySQL.Text := 
        'UPDATE TABL$_IMG I SET '+SQLCRLF+
        '   I.ID          = ?ID '+SQLCRLF+
        '  ,I.NAME        = ?NAME '+SQLCRLF+
        '  ,I.FLAG_DELETE = ?FLAG_DELETE '+SQLCRLF+
        '  ,I.OBJ_ID      = '''+aOBJ_ID+''' '+SQLCRLF+
        '  ,I.REC_ID      = '''+aREC_ID+''' '+SQLCRLF+
        '  ,I.IMG         = ?IMG '+SQLCRLF+
        '  ,I.DATE_COMMIT = ?DATE_COMMIT '+SQLCRLF+
        '  ,I.USER_ID     = ?USER_ID '+SQLCRLF+
        '  ,I.DECR        = ?DECR '+SQLCRLF+
        'WHERE (I.ID = ?'+ERP_DATASET_DBKEY+');';
      DeleteSQL.Text := ' DELETE FROM TABL$_IMG I WHERE (I.ID = ?'+ERP_DATASET_DBKEY+');';          
      Prepare;
      ParamByName('OBJ_ID').AsString := aOBJ_ID;  
      ParamByName('REC_ID').AsString := aREC_ID;  
      OnNewRecord := @TERPFormOperIMG_DataSetMain_OnNewRecord;
      AfterPost   := @TERPFormOperIMG_DataSetMain_AfterPost;
      AfterDelete := @TERPFormOperIMG_DataSetMain_AfterPost;
//      AfterOpen   := @TERPForm_DataSetMain_AfterOpen;
//      BeforeClose := @TERPForm_DataSetMain_BeforeClose;
//      AfterScroll := @TERPForm_DataSetMain_AfterScroll;
      end;    
    lkDBG := CreateTDBGridEh(Result,lkPanelLeft,lkDS,obj_name_erp_data_dbgmain, 0,100,200,200,alClient);
    with lkDBG do
      begin
      HelpKeyWord       := '0';
      with IndicatorTitle do
        begin
        UseGlobalMenu   := true;
        ShowDropDownSign:= true;
        TitleButton     := true;
        end;
      IndicatorOptions  := [gioShowRowIndicatorEh, gioShowRowselCheckboxesEh];  
      Options           := Options   + [dgMultiSelect, dgAlwaysShowSelection];  
      OptionsEh         := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghAutoSortMarking, dghMultiSortMarking,  
                                        dghIncSearch, dghPreferIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, 
                                        dghColumnMove, dghExtendVertLines, dghHotTrack];
      EditActions       := [geaCopyEh, geaSelectAllEh];
      SortLocal         := true;
      ShowHint          := true;
      //RowLines          := 2;
      //RowPanel.Active   := true;                        
      VTitleMargin      := 4;
      UseMultiTitle     := True;
      //OnKeyDown         := @TERPFormGrid_DBGrid_OnKeyDown;
      Columns.Clear;
      end; 
    lkCol := CreateTColumnEh(lkDBG,'FLAG_DELETE','','X',16,taLeftJustify);
    with lkCol do
      begin
      InRowLinePos := 0;
      Visible := true;
      KeyList.Clear ; KeyList.Add('1') ; KeyList.Add('0');
      PickList.Clear; PickList.Add('X'); PickList.Add(' ');
      CheckBoxes := true;
      ColParams.Clear;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLE             =  0;
      ColParams.Add('FLAG_DELETE');//  ERP_COL_INDEX_FIELD             =  1;
      ColParams.Add('');//  ERP_COL_INDEX_REF_TABLE         =  2;
      ColParams.Add('');//  ERP_COL_INDEX_REF_FIELD         =  3;
      ColParams.Add('');//  ERP_COL_INDEX_REF_KEYFIELD      =  4;
      ColParams.Add('');//  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
      ColParams.Add('0');//  ERP_COL_INDEX_VALUEDEFAULT      =  7;
      ColParams.Add('DOMN$BOOLEAN');//  ERP_COL_INDEX_FIELDTYPE         =  8;
      ColParams.Add('0');//  ERP_COL_INDEX_PERIODICAL        =  9;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEEMPTY        = 10;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLEMAIN         = 13;
      ColParams.Add(IntToStr(ERP_OBJECTTYPE_OPER));//  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
      ColParams.Add('IMG_ID');//  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
      ColParams.Add('');//  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
      end;
    lkCol := CreateTColumnEh(lkDBG,'ID','# ### ##0','код',59,taRightJustify);
    with lkCol do
      begin
      InRowLinePos := 0;
      Visible := true;
      ColParams.Clear;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLE             =  0;
      ColParams.Add('ID');//  ERP_COL_INDEX_FIELD             =  1;
      ColParams.Add('');//  ERP_COL_INDEX_REF_TABLE         =  2;
      ColParams.Add('');//  ERP_COL_INDEX_REF_FIELD         =  3;
      ColParams.Add('');//  ERP_COL_INDEX_REF_KEYFIELD      =  4;
      ColParams.Add('');//  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
      ColParams.Add('-1');//  ERP_COL_INDEX_VALUEDEFAULT      =  7;
      ColParams.Add('DOMN$INTEGER');//  ERP_COL_INDEX_FIELDTYPE         =  8;
      ColParams.Add('0');//  ERP_COL_INDEX_PERIODICAL        =  9;
      ColParams.Add('0');//  ERP_COL_INDEX_VALUEEMPTY        = 10;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLEMAIN         = 13;
      ColParams.Add(IntToStr(ERP_OBJECTTYPE_OPER));//  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
      ColParams.Add('IMG_ID');//  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
      ColParams.Add('');//  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
      end;
    lkCol := CreateTColumnEh(lkDBG,'NAME','','название изображения',220,taLeftJustify);
    with lkCol do
      begin
      InRowLinePos := 0;
      Visible := true;
      ColParams.Clear;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLE             =  0;
      ColParams.Add('NAME');//  ERP_COL_INDEX_FIELD             =  1;
      ColParams.Add('');//  ERP_COL_INDEX_REF_TABLE         =  2;
      ColParams.Add('');//  ERP_COL_INDEX_REF_FIELD         =  3;
      ColParams.Add('');//  ERP_COL_INDEX_REF_KEYFIELD      =  4;
      ColParams.Add('');//  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEDEFAULT      =  7;
      ColParams.Add('DOMN$PSTRING');//  ERP_COL_INDEX_FIELDTYPE         =  8;
      ColParams.Add('0');//  ERP_COL_INDEX_PERIODICAL        =  9;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEEMPTY        = 10;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLEMAIN         = 13;
      ColParams.Add(IntToStr(ERP_OBJECTTYPE_OPER));//  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
      ColParams.Add('IMG_ID');//  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
      ColParams.Add('');//  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
      end;
    lkCol := CreateTColumnEh(lkDBG,'DATE_COMMIT','dd.mm.yyyy hh:nn:ss','дата',76,taLeftJustify);
    with lkCol do
      begin
      InRowLinePos := 1;
      Visible := true;
      ColParams.Clear;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLE             =  0;
      ColParams.Add('DATE_COMMIT');//  ERP_COL_INDEX_FIELD             =  1;
      ColParams.Add('');//  ERP_COL_INDEX_REF_TABLE         =  2;
      ColParams.Add('');//  ERP_COL_INDEX_REF_FIELD         =  3;
      ColParams.Add('');//  ERP_COL_INDEX_REF_KEYFIELD      =  4;
      ColParams.Add('');//  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
      ColParams.Add('0');//  ERP_COL_INDEX_VALUEDEFAULT      =  7;
      ColParams.Add('DOMN$DATETIME');//  ERP_COL_INDEX_FIELDTYPE         =  8;
      ColParams.Add('0');//  ERP_COL_INDEX_PERIODICAL        =  9;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEEMPTY        = 10;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLEMAIN         = 13;
      ColParams.Add(IntToStr(ERP_OBJECTTYPE_OPER));//  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
      ColParams.Add('IMG_ID');//  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
      ColParams.Add('');//  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
      end;
    lkCol := CreateTColumnEh(lkDBG,'USER_ID','','пользователь',80,taLeftJustify);
    with lkCol do
      begin
      InRowLinePos := 1;
      Visible      := true;
      Color        := lkDBG.FixedColor;
      ReadOnly     := True;
      ColParams.Clear;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLE             =  0;
      ColParams.Add('USER_ID');//  ERP_COL_INDEX_FIELD             =  1;
      ColParams.Add('');//  ERP_COL_INDEX_REF_TABLE         =  2;
      ColParams.Add('');//  ERP_COL_INDEX_REF_FIELD         =  3;
      ColParams.Add('');//  ERP_COL_INDEX_REF_KEYFIELD      =  4;
      ColParams.Add('');//  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
      ColParams.Add(GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));//  ERP_COL_INDEX_VALUEDEFAULT      =  7;
      ColParams.Add('DOMN$PSTRING');//  ERP_COL_INDEX_FIELDTYPE         =  8;
      ColParams.Add('0');//  ERP_COL_INDEX_PERIODICAL        =  9;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEEMPTY        = 10;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLEMAIN         = 13;
      ColParams.Add(IntToStr(ERP_OBJECTTYPE_OPER));//  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
      ColParams.Add('IMG_ID');//  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
      ColParams.Add('');//  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
      end;
    lkCol := CreateTColumnEh(lkDBG,'USER_NAME','','сотрудник',139,taLeftJustify);
    with lkCol do
      begin
      InRowLinePos := 1;
      Visible      := true;
      Color        := lkDBG.FixedColor;
      ReadOnly     := True;
      ColParams.Clear;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLE             =  0;
      ColParams.Add('USER_NAME');//  ERP_COL_INDEX_FIELD             =  1;
      ColParams.Add('');//  ERP_COL_INDEX_REF_TABLE         =  2;
      ColParams.Add('');//  ERP_COL_INDEX_REF_FIELD         =  3;
      ColParams.Add('');//  ERP_COL_INDEX_REF_KEYFIELD      =  4;
      ColParams.Add('');//  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEDEFAULT      =  7;
      ColParams.Add('DOMN$PSTRING');//  ERP_COL_INDEX_FIELDTYPE         =  8;
      ColParams.Add('0');//  ERP_COL_INDEX_PERIODICAL        =  9;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEEMPTY        = 10;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLEMAIN         = 13;
      ColParams.Add(IntToStr(ERP_OBJECTTYPE_OPER));//  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
      ColParams.Add('IMG_ID');//  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
      ColParams.Add('');//  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
      end;
    lkCol := CreateTColumnEh(lkDBG,'OBJ_ID','','объект',160,taLeftJustify);
    with lkCol do
      begin
      InRowLinePos := 0;
      Visible := false;
      Color        := lkDBG.FixedColor;
      ReadOnly     := True;
      ColParams.Clear;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLE             =  0;
      ColParams.Add('OBJ_ID');//  ERP_COL_INDEX_FIELD             =  1;
      ColParams.Add('');//  ERP_COL_INDEX_REF_TABLE         =  2;
      ColParams.Add('');//  ERP_COL_INDEX_REF_FIELD         =  3;
      ColParams.Add('');//  ERP_COL_INDEX_REF_KEYFIELD      =  4;
      ColParams.Add('');//  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
      ColParams.Add(aOBJ_ID);//  ERP_COL_INDEX_VALUEDEFAULT      =  7;
      ColParams.Add('DOMN$PSTRING');//  ERP_COL_INDEX_FIELDTYPE         =  8;
      ColParams.Add('0');//  ERP_COL_INDEX_PERIODICAL        =  9;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEEMPTY        = 10;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLEMAIN         = 13;
      ColParams.Add(IntToStr(ERP_OBJECTTYPE_OPER));//  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
      ColParams.Add('IMG_ID');//  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
      ColParams.Add('');//  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
      end;
    lkCol := CreateTColumnEh(lkDBG,'REC_ID','','элемент',160,taLeftJustify);
    with lkCol do
      begin
      InRowLinePos := 0;
      Visible := false;
      Color        := lkDBG.FixedColor;
      ReadOnly     := True;
      ColParams.Clear;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLE             =  0;
      ColParams.Add('REC_ID');//  ERP_COL_INDEX_FIELD             =  1;
      ColParams.Add('');//  ERP_COL_INDEX_REF_TABLE         =  2;
      ColParams.Add('');//  ERP_COL_INDEX_REF_FIELD         =  3;
      ColParams.Add('');//  ERP_COL_INDEX_REF_KEYFIELD      =  4;
      ColParams.Add('');//  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
      ColParams.Add(aREC_ID);//  ERP_COL_INDEX_VALUEDEFAULT      =  7;
      ColParams.Add('DOMN$PSTRING');//  ERP_COL_INDEX_FIELDTYPE         =  8;
      ColParams.Add('0');//  ERP_COL_INDEX_PERIODICAL        =  9;
      ColParams.Add('');//  ERP_COL_INDEX_VALUEEMPTY        = 10;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
      ColParams.Add('');//  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
      ColParams.Add('TABL$_IMG');//  ERP_COL_INDEX_TABLEMAIN         = 13;
      ColParams.Add(IntToStr(ERP_OBJECTTYPE_OPER));//  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
      ColParams.Add('IMG_ID');//  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
      ColParams.Add('');//  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
      ColParams.Add('');//  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
      end;
    Result.ActiveControl := lkDBG;  
    ERP_DBGridEh_StdActions_Create(lkDBG, [erpGrid, erpGridNavigation], lkToolBar, lkMIView);
    ERP_DBGridEh_EdtActions_Create(lkDBG, [erpGrid, erpGridEdit, erpGridEditIns,erpGridEditUpd,erpGridEditDel,erpGridEditPostCancel,erpGridNoCopy, erpGridNoImages], lkToolBar, lkMIItem);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actprintitem,msg_erp_actprintitem,msg_erp_actprintitem_hint,SHORTCUT_PRINT,0,105,@TERPFormOperIMG_actPrintItem_OnExecute,@TERPFormOperIMG_actPrintItem_OnUpdate,lkToolBar,lkMIItem);
    DBInterfaceCreateImage(Result, lkPanelClient, lkDS, 'IMG', false);
    lkSplt     := CreateTSplitter(Result,lkPanelClient,obj_name_erp_splitterdetail,alBottom,0,600,4,800);
    lkPCDetail := CreateTxcPageControlEx(Result,lkPanelClient,obj_name_erp_pagecontroldetail,0,600,200,200,alBottom);
    lkTS := CreateTxcTabSheet(lkPCDetail, 'tsDescr', 'Коментарии к изображению', 26, Amunhotep.MainForm.StyleManager.Colors.Foreground);
    DBInterfaceCreateText(Result, lkTS, lkDS, 'DECR', false);
    TxcPageControlEx_ActivateDefaultPage(lkPCDetail);
    lkEvents := TxFBEvents.Create(Result);
    with lkEvents do
      begin
      Name         := obj_name_erp_data_evmain;
      DataBase     := FBDataBase;
      OnEventAlert := @TERPFormOperIMG_evMain_OnEventAlert;
      Events.Clear;
      Events.Add('TABL$_IMG');
      if not Registered then
        RegisterEvents;
      end;
    TERPFormOperIMG_RefreshView(Result);
    Amunhotep.MainForm.xcMenu.AddMenu(lkMainMenu); lkMainMenu.OwnerDraw := true;
    Result.Menu := lkMainMenu;
  end;
