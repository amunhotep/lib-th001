{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/FORMREFITEM.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM.INC}      {$I ../$COMMON/FORMERPITEM.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REF.INC} {$I ../DBGRID/GETCELLPARAMS_REF.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADATTRS.INC}    {$I ./FORMREF_LOADATTRS.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCOLUMNS.INC}  {$I ./FORMREF_LOADCOLUMNS.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCHILDS.INC}   {$I ./FORMREF_LOADCHILDS.INC}       {$ENDIF}  
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREFITEM_ACTIONS.INC}  {$I ./FORMREFITEM_ACTIONS.INC}      {$ENDIF}
  //===================== PEAKTOP:IDE/ERP/DBO/REF/FORMREFITEM.INC ==============
  function TERPFormItem_PrintGrid(aOwner :TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  function TERPFormItem_PrintItem(aOwner :TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  function TERPFormRefItem_Create(const aObjId :string; const aModalForm:Boolean):TForm;
  var
    lkStr          :string; 
    lkSettings     :TStrings;
    lkCreateParams :TFormERPParams;
    lkTr           :TxFBTransaction;
    lkQr           :TxFBQuery;
    lkDS           :TDataSource;
    lkAct          :TCustomAction;
    lkMainMenu     :TMainMenu;
    lkMIMenuMain   :TMenuItem;
    lkMIView       :TMenuItem;
    lkMIItem       :TMenuItem;
    lkSB           :TScrollBox;
    lkPanelClient  :TxcGradientPanel;
    lkToolBar      :TxcGradientPanelVista;
    lkEvents       :TxFBEvents;
    lkSQLSelect    :string; 
    lkSQLRefresh   :string; 
    lkSQLUpdate    :string; 
    lkSQLDelete    :string;
  begin
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQR, lkDS)  
    lkCreateParams := [erpEvents];
    lkQr.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETTABLE_REF));
    lkQr.Prepare;
    lkQr.ParamByName('PQ_TB_ID'   ).AsString := aObjId;
    lkQr.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
    try
      lkQr.Open;
    except
    end;
    if not(lkQr.Active)then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpsql+' "'+aObjId+'" !',mtWarning,[mbOk]);
      exit;
      end;  
    lkQr.First;
    if(lkQr.FieldByName('TB_EXISTS').AsInteger <> 1)then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_defined+' "'+aObjId+'"', mtError, [mbOk]);
      exit;
      end;
    if(lkQr.FieldByName('TB_REL_EXISTS').AsInteger <> 1)then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_exists+' "'+aObjId+'"', mtError, [mbOk]);
      exit;
      end;
    if(not(lkQr.FieldByName('TB_ACCS_SEL_CNT').AsInteger > 0))then
      begin
      lkStr := lkQr.FieldByName('TB_NAME').AsString;
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpobject_acces_denied+' "'+lkStr+'" !',mtWarning,[mbOk]);
      exit;
      end;
    if((lkQr.FieldByName('TB_TREE').AsInteger = 1) or (lkQr.FieldByName('GROUPTB_EXISTS').AsInteger = 1))then
      begin
      
      end; 
    if((not aModalForm) and (lkQr.FieldByName('TB_ACCS_PRN_CNT').AsInteger > 0) )then
      lkCreateParams := lkCreateParams + [erpGridExport, erpGridPrint, erpGridPrintItem];
    if( (lkQr.FieldByName('TB_CHILD_COUNT').AsInteger > 0) or(lkQr.FieldByName('TB_BLOB_COUNT').AsInteger > 0) or (lkQr.FieldByName('TB_FLAG_EXTERNAL').AsInteger <> 0))then
      begin
      lkCreateParams := lkCreateParams + [erpDetail];
      if(lkQr.FieldByName('TB_FLAG_EXTERNAL').AsInteger <> 0)then
        lkCreateParams := lkCreateParams + [erpDetailExternal];
      end;
    if(lkQr.FieldByName('TB_ACCS_EDIT_CNT').AsInteger > 0)then
      begin
      lkCreateParams := lkCreateParams + [erpGridEdit, erpGridEditPostCancel];
      if(lkQr.FieldByName('TB_ACCS_INS_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditIns];
      if(lkQr.FieldByName('TB_ACCS_UPD_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditUpd, erpGridEditMark];
      if(lkQr.FieldByName('TB_ACCS_DEL_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditDel];
      end;
    Result := TERPFormItem_Create(lkQr.FieldByName('TB_NAME').AsString, ERP_ObjectCaptionItem(lkQr.FieldByName('TB_BASE_TYPE_ID').AsInteger), ERP_ObjectIcon(lkQr.FieldByName('TB_BASE_TYPE_ID').AsInteger), ERP_ObjectBitmap(lkQr.FieldByName('TB_BASE_TYPE_ID').AsInteger), aModalForm, lkCreateParams);
    with Result do
      begin
      HelpKeyWord := aObjId;
      if aModalForm then
        TForm_Position_Load(Result, PrepareAbsoleteFileName('TMP:'+ERP_FILENAME_CFG_DIALOG_REF+aObjId+ERP_FILENAME_CFG_ITEM_SUFFIX+'.CFG'),
          MaxInteger(lkQr.FieldByName('TB_DLG_HEIGHT').AsInteger,400), MaxInteger(lkQr.FieldByName('TB_DLG_WIDTH').AsInteger ,600));  
      end;  
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(lkQr.FieldByName('TB_BASE_TYPE_ID').AsInteger);
      Colors.HotTrackBorder := ERP_ObjectColor(lkQr.FieldByName('TB_BASE_TYPE_ID').AsInteger);
      end;  
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_BUFFERVAR       ] := lkQr.FieldByName('TB_BUFFER_VAR').AsString;
      Values[ERP_SETTINGS_TABLENAME       ] := aObjId;
      Values[ERP_SETTINGS_TABLECAPTION    ] := lkQr.FieldByName('TB_NAME').AsString;
      Values[ERP_SETTINGS_REF_TREE        ] := '0';
      Values[ERP_SETTINGS_REF_TREEORGROUP ] := '0';
      Values[ERP_SETTINGS_REF_TREEFIELD   ] := '';
      Values[ERP_SETTINGS_BASETYPE        ] := '2';
      Values[ERP_SETTINGS_ITEM_SCRIPT     ] := lkQr.FieldByName('TB_SC_ITEM').AsString;
      Values[ERP_SETTINGS_ITEM_SCRIPTDLG  ] := lkQr.FieldByName('TB_SC_ITEM_DLG').AsString;
      Values[ERP_DATASET_DBKEY            ] := GetGlobalVariable(Values[ERP_SETTINGS_BUFFERVAR]);
      end;
    lkMainMenu   := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu)); 
    lkMIMenuMain := TMenuItem(lkMainMenu.Items.FindComponent(obj_name_erp_mimainmenu));
    lkMIItem     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainitem));
    lkMIView     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainview));
    if not aModalForm then
      begin
      lkAct := TCustomAction(Result.FindComponent(obj_name_erp_actprintitem));lkAct.ImageIndex := 178;
      CreateTMenuItem(lkMIMenuMain,obj_name_erp_mimaindb,msg_erp_mimaindb,'','',ERP_ObjectImageIndex(ERP_OBJECTTYPE_REFS),  0);
      ERP_DBMenuItems_Build(lkMIMenuMain, aObjId, '0', @TERPFormItem_DatabaseMenuItem_OnClick);
      end;    
    lkPanelClient:= TxcGradientPanel(Result.FindComponent(obj_name_erp_panelclient));
    lkToolBar    := TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbar));
    lkSB := CreateTScrollBox(Result,lkPanelClient,obj_name_erp_scrollboxmain,1,lkToolBar.Top+lkToolBar.Height+1,600,800,alClient);
    with lkSB do
      begin
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      end;
    lkEvents     := TxFBEvents(Result.FindComponent(obj_name_erp_data_evmain));
    lkEvents.Events.Add(aObjId);
    lkSQLSelect    := ''; 
    lkSQLRefresh   := ''; 
    lkSQLUpdate    := ''; 
    lkSQLDelete    := '';
    TERPFormRefItem_LoadAttrs(Result, lkSB, TDataSource(TERPForm_DataSetMain(Result).FindComponent('DataSource'+obj_name_erp_data_dtsmain)), aObjId, lkQr, true, 
      lkSQLSelect, lkSQLRefresh, lkSQLUpdate, lkSQLDelete);
    TERPFormItem_SQL(Result).Text := lkSQLSelect;
    with TERPForm_DataSetMain(Result) do
      begin 
      SelectSQL.Text  := lkSQLSelect;  
      RefreshSQL.Text := lkSQLRefresh;
      if(erpGridEditUpd in lkCreateParams)then ModifySQL.Text := lkSQLUpdate;
      if(erpGridEditDel in lkCreateParams)then DeleteSQL.Text := lkSQLDelete;
      end;
    lkToolBar := TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbar_view));
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actgriddatadet ,msg_erp_actgriddatadet ,msg_erp_actgriddatadet_hint ,'',0,392,@TERPFormItemRef_actGridDataDetail_OnExecute,@TERPFormItemRef_actGridDataDetail_OnUpdate,lkToolBar,lkMIView);
    lkToolBar.Width := TWinControl_AutoWidth(lkToolBar)+2;   
    TERPFormItem_RefreshView(Result);
    if not lkEvents.Registered then
      lkEvents.RegisterEvents;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
//    StringsSaveToFile(PrepareAbsoleteFileName('TMP:ERP_SETTINGS_REFITEM_'+aObjId+'.'+obj_name_erp_data_dtsmain+'.XFM'), ComponentToStr(Result));  
  end;
  //============================================================================
  function ReferenceItem_Create(const aObjId:string):TAmunhotepForm;
  begin
    Result := TAmunhotepForm(TERPFormRefItem_Create(aObjId, false));
    ERP_ObjectExtension_Call(Result, TxcPageControlEx(Result.FindComponent(obj_name_erp_pagecontroldetail)), TERPForm_DataSetMain(Result)); 
  end;
  //============================================================================
  function ReferenceItem_Execute(const aObjId:string):Boolean;
  var
    lkForm :TForm;
  begin
    try
      lkForm := TERPFormRefItem_Create(aObjId, true);
      Result := (lkForm.ShowModal = mrOk);
      TForm_Position_Save(lkForm, PrepareAbsoleteFileName('TMP:'+ERP_FILENAME_CFG_DIALOG_REF+aObjId+ERP_FILENAME_CFG_ITEM_SUFFIX+'.CFG'));  
    finally  
      lkForm.Free;
    end;  
  end;  
