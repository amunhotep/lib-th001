{$DEFINE PEAKTOP:IDE/ERP/DBO/REG/FORMREG.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID.INC}      {$I ../$COMMON/FORMERPGRID.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REG.INC} {$I ../DBGRID/GETCELLPARAMS_REG.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADATTRS.INC}    {$I ../REF/FORMREF_LOADATTRS.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCOLUMNS.INC}  {$I ../REF/FORMREF_LOADCOLUMNS.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCHILDS.INC}   {$I ../REF/FORMREF_LOADCHILDS.INC}         {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/REG/FORMREG.INC =====================
  function Registry_Create(const aObjId:string):TForm;  forward;
  function Registry_Execute(const aObjId:string):TForm; forward;
  //============================================================================
  function TERPFormGrid_PrintGrid(aOwner :TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  function TERPFormGrid_PrintItem(aOwner :TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormGrid_RefreshView(aOwner :TComponent);
  var
    lkSQL      :string;
    lkSettings :TStrings;
  begin
    TERPFormGrid_CloseDataSets(aOwner);
    lkSettings := TERPForm_Settings(aOwner);
    lkSQL      := TERPFormGrid_SQL(aOwner).Text;
    if(lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] = '1')then
      with TxFBTreeView(aOwner.FindComponent(obj_name_erp_fbtreeview)) do
        begin
        if(TERPForm_DataSetMain(aOwner).SQLFilter.Text <> '')then
          lkSQL := lkSQL+'  AND ('+TERPForm_DataSetMain(aOwner).SQLFilter.Text+' = '''+GetId+''') '+SQLCRLF
         else
          lkSQL := lkSQL+'  AND ('+ERP_SQL_TABLEPREFIX+'.'+lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD]+' = '''+GetId+''') '+SQLCRLF;
        end;
    if(TERPForm_DBGridMain(aOwner).Tag <> 1)then
      lkSQL := lkSQL+'  AND ( ('+ERP_SQL_TABLEPREFIX+'.FLAG_DELETE <> 1) OR ('+ERP_SQL_TABLEPREFIX+'.FLAG_DELETE IS NULL) ) '+SQLCRLF;
//    Dialogs.MessageDlg(lkSQL, mtInformation, [mbOk]);  
    with TERPForm_DataSetMain(aOwner) do
      begin
      SelectSQL.Text := lkSQL; 
      if(lkSettings.Values[ERP_SETTINGS_REGMOVE] <> '0')then
        begin
        Prepare;
        ParamByName(ERP_SQL_FIELDDATEFROM).AsDate := TERPFormGrid_dtpDateFrom(aOwner).Date;  
        ParamByName(ERP_SQL_FIELDDATETO  ).AsDate := TERPFormGrid_dtpDateTo(aOwner).Date+1;
        end;
      Open;
      if not Active then exit;
      end;
    with TERPForm_Settings(aOwner) do  
      if( (Values[ERP_SETTINGS_DATAMEMORY] = '1') and (Values[ERP_SETTINGS_BOOKMARK] = '1') )then  
        if TERPForm_DBGridMain(aOwner).DataSource.DataSet.Active then   
          begin
          TERPForm_DBGridMain(aOwner).DataSource.DataSet.RecNo := StrToInt(Values[ERP_SETTINGS_SAVERECNO]);
          Values[ERP_SETTINGS_SAVERECNO] := '0';
          Values[ERP_SETTINGS_BOOKMARK ] := '0';
          end;
  end;
  //============================================================================
  procedure TERPFormGrid_PanelLeft_OnShowHide(aOwner :TComponent);
  begin
    if(TERPForm_Settings(aOwner).Values[ERP_SETTINGS_REF_TREEORGROUP] = '1')then
      if TERPForm_DataSetMain(aOwner).Active then
        if(TERPForm_DataSetMain(aOwner).RecordCount > 0)then
          with TxFBTreeView(aOwner.FindComponent(obj_name_erp_fbtreeview)) do
            if Parent.Visible then
               begin
               ClearTree;
               BuildNodeById(TERPForm_MemTableMain(aOwner).FieldByName(TERPForm_Settings(aOwner).Values[ERP_SETTINGS_REF_TREEFIELD]).AsString);
               WriteLn(GetId);
               end;
    TERPFormGrid_RefreshView(aOwner);
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_AfterScroll(DataSet :TDataSet);
  begin
    
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_OnNewRecord(DataSet :TDataSet);
  var
    lkSettings :TStrings;
    lkDBG      :TDBGridEh;
  begin
    lkDBG      := TERPForm_DBGridMain(DataSet.Owner.Owner);
    lkSettings := TERPForm_Settings(lkDBG.Owner);
    TERPForm_DBGrid_FillValuesGrid(DataSet, TERPForm_DataSetMain(DataSet.Owner.Owner), lkDBG);
    if(lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] = '1')then
      DataSet.FieldByName(lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD]).AsString := TxFBTreeView(lkDBG.Owner.FindComponent(obj_name_erp_fbtreeview)).GetId;
  end;
  //============================================================================
  function TERPFormGrid_ExportGetCaption(aOwner :TComponent):string;
  begin
    Result := ERP_ObjectCaption(6)+#$20+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION];
  end;
  //============================================================================
  function TERPFormGrid_ExportGetFilter(aOwner :TComponent):string;
  begin
    Result := '';
  end;
  //============================================================================
  function TERPFormGrid_ExportGetFileName(aOwner :TComponent):string;
  begin
    Result := ERP_ObjectCaption(6)+#$20+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION];
  end;                   
  //============================================================================
  procedure TERPFormGridReg_FBTreeView_OnClick(Sender :TObject);
  begin
    TERPFormGrid_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormGridReg_FBTreeView_OnBuildNode(Sender :TObject; StateFieldValue :Variant; var StateImage :Integer);
  begin
    if(TComponent(Sender).Tag = 1)then
      StateImage := 0
     else
      StateImage := Integer(StateFieldValue);
  end;
  //============================================================================
  procedure TERPFormGridReg_DBGrid_OnDblClick(Sender: TObject);
  var
    lkFrm :TComponent;
  begin
    lkFrm := TERPForm_GetOwner(TComponent(Sender));
    if(TForm(lkFrm).FormStyle = fsMDIChild)then
      begin
      with TDBGridEh(Sender).DataSource.DataSet do
        begin
        SetGlobalVariable('J_ID', FieldByName('J_ID').AsString);
        if(FindField('J_TYPE_ID') <> nil)then
          call(StrReplaceStr('PEAKTOP:IDE/ERP/CONFIG/DOC/<%OBJECT_TYPE%>/EDIT.PS', '<%OBJECT_TYPE%>', FieldByName('J_TYPE_ID').AsString));
        end;  
      end
     else
      begin
      TForm(lkFrm).ModalResult := mrOk;
      end; 
  end;
  //============================================================================
  procedure TERPFormGridReg_PositionOnRecord(aOwner :TComponent);
  var
    lkID       :string;
    lkSettings :TStrings;
  begin 
    TERPFormGrid_CloseDataSets(aOwner);
    lkSettings := TERPForm_Settings(aOwner);
    lkId := GetGlobalVariable(lkSettings.Values[ERP_SETTINGS_BUFFERVAR]);
    if(lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] = '1')then
      with TxFBTreeView(aOwner.FindComponent(obj_name_erp_fbtreeview)) do
        begin
        ClearTree;
        BuildTree;
        if(Items.Count > 0)then
          Items[0].Selected := true;
        end;
    TERPFormGrid_RefreshView(aOwner); 
  end;
  //============================================================================
  function TERPFormGridReg_Create(const aObjId:string;const aModalForm:Boolean):TForm;
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
    lkMIObj        :TMenuItem;
    lkMIItem       :TMenuItem;
    lkPanelClient  :TxcPanel;
    lkPanelLeft    :TxcPanel;
    lkToolBar      :TxcGradientPanelVista;
    lkFBTreeView   :TxFBTreeView;
    lkEvents       :TxFBEvents;

    lkSQLSelect    :string; 
    lkSQLRefresh   :string; 
    lkSQLInsert    :string; 
    lkSQLUpdate    :string; 
    lkSQLDelete    :string;
    lkSelectFilter :string;
  begin
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQR, lkDS)  
    lkCreateParams := [erpGrid, erpEvents, erpGridNavigation, erpEvents];
    if not aModalForm then
      lkCreateParams := lkCreateParams + [erpGridGroup];  
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
    if(lkQr.FieldByName('TB_FLAG_MOVE').AsInteger <> 0)then
      lkCreateParams := lkCreateParams + [erpDatePeriod, erpDatePeriodAutoRefresh];
    if((not aModalForm) and (lkQr.FieldByName('TB_ACCS_PRN_CNT').AsInteger > 0) )then
      lkCreateParams := lkCreateParams + [erpGridExport, erpGridPrint, erpGridPrintItem];
    if((not aModalForm) and ((lkQr.FieldByName('TB_CHILD_COUNT').AsInteger > 0) or(lkQr.FieldByName('TB_BLOB_COUNT').AsInteger > 0)) )then
      lkCreateParams := lkCreateParams + [erpDetail];
    if ERP_ObjectExtension_FileExists(aObjId, ERP_OBJECTTYPE_REG)then  
      lkCreateParams := lkCreateParams + [erpDetail, erpDetailExtensions];
    if((lkQr.FieldByName('TB_TREE').AsInteger = 1) or (lkQr.FieldByName('GROUPTB_EXISTS').AsInteger = 1))then 
      lkCreateParams := lkCreateParams + [erpPanelLeft, erpPanelLeftShowHide, erpPanelLeftVisible];
    if(lkQr.FieldByName('TB_ACCS_EDIT_CNT').AsInteger > 0)then
      begin
      lkCreateParams := lkCreateParams + [erpGridEdit, erpGridEditPostCancel];
      if(lkQr.FieldByName('TB_ACCS_INS_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditIns];
      if(lkQr.FieldByName('TB_ACCS_UPD_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditUpd, erpGridEditEdt, erpGridEditMark];
      if(lkQr.FieldByName('TB_ACCS_DEL_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditDel];
      end;
    Result := TERPFormGrid_Create(lkQr.FieldByName('TB_NAME').AsString, ERP_ObjectCaption(ERP_OBJECTTYPE_REG), ERP_ObjectIcon(ERP_OBJECTTYPE_REG), ERP_ObjectBitmap(ERP_OBJECTTYPE_REG),aModalForm,lkCreateParams);
    with Result do
      begin
      HelpKeyWord := aObjId;
      if aModalForm then
        begin
        TForm_Position_Load(Result, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_REG,ERP_OBJECTTYPE_REG,aObjId,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))),
          MaxInteger(lkQr.FieldByName('TB_DLG_HEIGHT').AsInteger,600), MaxInteger(lkQr.FieldByName('TB_DLG_WIDTH').AsInteger ,600));  
        end;
      end;  
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_REG);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_REG);
      end;  
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_BUFFERVAR       ] := lkQr.FieldByName('TB_BUFFER_VAR').AsString;
      Values[ERP_SETTINGS_TABLENAME       ] := aObjId;
      Values[ERP_SETTINGS_TABLECAPTION    ] := lkQr.FieldByName('TB_NAME').AsString;
      Values[ERP_SETTINGS_BASETYPE        ] := IntToStr(ERP_OBJECTTYPE_REG);
      Values[ERP_SETTINGS_REF_TREE        ] := '0';
      Values[ERP_SETTINGS_REF_TREEORGROUP ] := '0';
      Values[ERP_SETTINGS_REF_TREEFIELD   ] := '';
      Values[ERP_SETTINGS_REGMOVE         ] := lkQr.FieldByName('TB_FLAG_MOVE').AsString;
      Values[ERP_SETTINGS_TEMPFILENAME    ] := ERP_ObjectTempFileName(ERP_OBJECTTYPE_REG,ERP_OBJECTTYPE_REG,aObjId,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));
      end;
    // users recent menu
    ExecSQL(FBDataBase, 
      'EXECUTE BLOCK AS '+SQLCRLF+
      '  DECLARE VARIABLE P DOMN$INTEGER; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  IF(NOT(EXISTS(SELECT R.RDB$RELATION_ID FROM RDB$RELATIONS R WHERE(TRIM(R.RDB$RELATION_NAME)=''TABL$_USERS_RCNT''))))THEN EXIT; '+SQLCRLF+
      '  EXECUTE STATEMENT ''UPDATE OR INSERT INTO TABL$_USERS_RCNT(NAME, USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME)VALUES('''''+Result.Caption+''''', '''''+
       GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''''', 0, '''''+IntToStr(ERP_OBJECTTYPE_REG)+''''', '''''+ScriptName+''''')MATCHING(USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME);''; '+SQLCRLF+    
      '  /* SELECT MAX(P.ID) FROM PROC$_USERS_LOG_INS(1000044, '''+aObjId+''', NULL, NULL, NULL) P INTO :P; */ '+SQLCRLF+
      'END');    
    lkMainMenu   := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu)); 
    lkMIMenuMain := TMenuItem(lkMainMenu.Items.FindComponent(obj_name_erp_mimainmenu));//lkMIMenuMain.Caption := ERP_ObjectCaption(2);
    lkMIItem     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainitem));
    lkMIObj      := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainobj)); lkMIObj.ImageIndex := 46; lkMIObj.Caption := ERP_ObjectCaption(ERP_OBJECTTYPE_REG);
    lkMIView     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainview));
    if not aModalForm then
      begin
      lkAct      := TCustomAction(Result.FindComponent(obj_name_erp_actprintitem));lkAct.ImageIndex := 233;
      lkAct      := TCustomAction(Result.FindComponent(obj_name_erp_actprintgrid));lkAct.ImageIndex := 240;
      CreateTMenuItem(lkMIMenuMain,obj_name_erp_mimaindb,msg_erp_mimaindb,'','',ERP_ObjectImageIndex(ERP_OBJECTTYPE_REGS),  0);
      ERP_DBMenuItems_Build(lkMIMenuMain, aObjId, '0', @TERPFormGrid_DatabaseMenuItem_OnClick);
      end;    
    lkPanelClient:= TxcPanel(Result.FindComponent(obj_name_erp_panelclient));
    lkToolBar    := TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbar));
    lkEvents     := TxFBEvents(Result.FindComponent(obj_name_erp_data_evmain));
    lkEvents.Events.Add(aObjId);
    if((lkQr.FieldByName('TB_TREE').AsInteger = 1) or (lkQr.FieldByName('GROUPTB_EXISTS').AsInteger = 1))then
      begin
      lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] := '1';
      lkPanelLeft   := TxcPanel(Result.FindComponent(obj_name_erp_panelleft));
      lkFBTreeView  := CreateTxFBTreeView(Result, lkPanelLeft, obj_name_erp_fbtreeview, 1,1,200,200,alClient);
      with lkFBTreeView do
        begin
        Images      := CreateTImageList(lkFBTreeView, 'ilFBTreeView', [30]);
        Tag         := 1;    
        OnClick     := @TERPFormGridReg_FBTreeView_OnClick;
        OnBuildNode := @TERPFormGridReg_FBTreeView_OnBuildNode;
        with DBTreeInfo do
          begin
          FieldId       := 'ID';
          FieldName     := 'NAME';
          FieldParentId := 'PARENT_ID';
          FieldStateId  := 'ID';
          RootParentId  := '0';
          OrderBy       := 'NAME';
          if(lkQr.FieldByName('TB_TREE').AsInteger = 1)then
            begin
            lkSettings.Values[ERP_SETTINGS_REF_TREE]      := '1';
            lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD] := FieldParentId;
            TableName   := aObjId;
            ShowItemId  := (lkQr.FieldByName('TB_FLAG_SHOW_ITEM_ID').AsInteger = 1);
            if(StrTrimAll(lkQr.FieldByName('TB_STATE_FIELDNAME').AsString) <> '')then
              FieldStateId := lkQr.FieldByName('TB_STATE_FIELDNAME').AsString;
            if(StrTrimAll(lkQr.FieldByName('TB_ROOT_PARENT_ID').AsString) <> '')then
              RootParentId := lkQr.FieldByName('TB_ROOT_PARENT_ID').AsString;
            end
           else
            begin
            lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD] := StrTrimAll(lkQr.FieldByName('GROUPTB_INDEX_FIELDS').AsString);
            TableName   := StrTrimAll(lkQr.FieldByName('GROUPTB_ID').AsString);
            ShowItemId  := (lkQr.FieldByName('GROUPTB_SHOWID').AsInteger = 1);
            if(StrTrimAll(lkQr.FieldByName('GROUPTB_ROOT_ID').AsString) <> '')then
              RootParentId := lkQr.FieldByName('GROUPTB_ROOT_ID').AsString;
            lkEvents.Events.Add(StrTrimAll(lkQr.FieldByName('GROUPTB_ID').AsString));
            end; 
          end;
        end;
      end; 

    if lkTr.InTransaction then
      lkTr.Commit;
    lkQr.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETCOLUMNS_REF));
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
    TERPFormGrid_LoadDBGridColumns(aObjId, lkQr, TERPForm_DBGridMain(Result), nil, //TxcPageControlEx(Result.FindComponent(obj_name_erp_pagecontroldetail)), 
      (lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] = '1'), (lkSettings.Values[ERP_SETTINGS_REGMOVE] <> '0'), 
      lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD], lkSQLSelect, lkSQLRefresh, lkSQLInsert, lkSQLUpdate, lkSQLDelete, lkSelectFilter);
    TERPForm_GridSettingsLoad(TERPForm_DBGridMain(Result), lkSettings.Values[ERP_SETTINGS_TEMPFILENAME]);
    with TERPForm_DBGridMain(Result) do
      begin
      OnGetCellParams := @ERP_DBGridEh_OnGetCellParams_Reg;
      if(lkSettings.Values[ERP_SETTINGS_REGMOVE] <> '0')then
        OnDblClick    := @TERPFormGridReg_DBGrid_OnDblClick;
      end;
    TERPFormGrid_SQL(Result).Text := lkSQLSelect;
    with TERPForm_DataSetMain(Result) do
      begin 
      if(lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] = '1')then
        SQLFilter.Text:= lkSelectFilter;
      SelectSQL.Text  := lkSQLSelect;  
      RefreshSQL.Text := lkSQLRefresh;
      if(erpGridEditIns in lkCreateParams)then InsertSQL.Text := lkSQLInsert; 
      if(erpGridEditUpd in lkCreateParams)then ModifySQL.Text := lkSQLUpdate;
      if(erpGridEditDel in lkCreateParams)then DeleteSQL.Text := lkSQLDelete;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
    if not lkEvents.Registered then
      lkEvents.RegisterEvents;
    //StringsSaveToFile(PrepareAbsoleteFileName('TMP:ERP_SETTINGS_REF_'+aObjId+'.CFG'), lkSettings.Text);
    Result.ActiveControl := TERPForm_DBGridMain(Result);  
    TERPFormGridReg_PositionOnRecord(Result);  
  end;
  //============================================================================
  function Registry_Create(const aObjId:string):TForm;
  begin
    Result := TERPFormGridReg_Create(aObjId, false);
    ERP_ObjectExtension_Call(Result, TxcPageControlEx(Result.FindComponent(obj_name_erp_pagecontroldetail)), TERPForm_MemTableMain(Result)); 
  end;
  //============================================================================
  function Registry_Execute(const aObjId:string):TForm;
  begin
    Result := TERPFormGridReg_Create(aObjId, true);
    with Result do
      begin
      SetGlobalVariable(TERPForm_Settings(Result).Values[ERP_SETTINGS_BUFFERVAR], 'NULL');
      if(ShowModal <> mrOK)then
        SetGlobalVariable(TERPForm_Settings(Result).Values[ERP_SETTINGS_BUFFERVAR], 'NULL');
      TForm_Position_Save(Result, PrepareAbsoleteFileName(TERPForm_Settings(Result).Values[ERP_SETTINGS_TEMPFILENAME]) );  
      Free;
      end;  
  end; 
