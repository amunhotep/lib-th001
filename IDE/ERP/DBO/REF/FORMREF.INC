{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/FORMREF.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID.INC}      {$I ../$COMMON/FORMERPGRID.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/STDTREEACTNS.INC}     {$I ../$COMMON/STDTREEACTNS.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REF.INC} {$I ../DBGRID/GETCELLPARAMS_REF.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADATTRS.INC}    {$I ./FORMREF_LOADATTRS.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCOLUMNS.INC}  {$I ./FORMREF_LOADCOLUMNS.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCHILDS.INC}   {$I ./FORMREF_LOADCHILDS.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_ACTIONS.INC}      {$I ./FORMREF_ACTIONS.INC}            {$ENDIF}
  //======================== PEAKTOP:IDE/ERP/DBO/REF/FORMREF.INC ===============
const
  ERP_REFERENCE_ABCGROUPINDEX = 22;
  //============================================================================
  function Reference_Create(const aObjId:string):TForm;  forward;
  function Reference_Execute(const aObjId:string):TForm; forward;
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
    i          :Integer;
    lkOrderBy  :string;
    lkSQL      :string;
    lkSettings :TStrings;
    lkID       :string;
  label 
    loop_not_tree;  
  begin
    lkID := '';
    with TERPForm_DBGridMain(aOwner).DataSource.DataSet do
      if Active then
        if( (RecordCount > 0) and (FindField(ERP_DATASET_DBKEY) <> nil) )then
          lkID := FieldByName(ERP_DATASET_DBKEY).AsString;
    TERPFormGrid_CloseDataSets(aOwner);
    lkSettings := TERPForm_Settings(aOwner); 
    lkSQL      := TERPFormGrid_SQL(aOwner).Text;
    if(lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] = '1')then
      begin
      if(aOwner.FindComponent(obj_name_erp_actviewpanelleft+'2') <> nil)then
        if(TCustomAction(aOwner.FindComponent(obj_name_erp_actviewpanelleft+'2')).Tag = 1)then
          goto loop_not_tree;
      with TxFBTreeView(aOwner.FindComponent(obj_name_erp_fbtreeview)) do
        begin
        if(TERPForm_DataSetMain(aOwner).SQLFilter.Text <> '')then
          lkSQL := lkSQL+'  AND ('+TERPForm_DataSetMain(aOwner).SQLFilter.Text+' = '''+GetId+''') '+SQLCRLF
         else
          lkSQL := lkSQL+'  AND ('+ERP_SQL_TABLEPREFIX+'.'+lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD]+' = '''+GetId+''') '+SQLCRLF;
        end;
      end;  
  loop_not_tree:
    if(aOwner.FindComponent(obj_name_erp_toolbarabc) <> nil)then    
      with TxcGradientPanel(aOwner.FindComponent(obj_name_erp_toolbarabc)) do
        for i:=0 to ControlCount-1 do
          if(ObjectInheritsFrom(Controls[i],'TxcToolBarButton'))then
            if( (TxcToolBarButton(Controls[i]).Down) and (Controls[i].Tag <> -1) )then
              begin
              lkSQL := lkSQL+'  AND (UPPER('+ERP_SQL_TABLEPREFIX+'.NAME) STARTING WITH '''+Chr(Controls[i].Tag)+''') '+SQLCRLF;
              break;
              end;
    with TERPForm_DBGridMain(aOwner) do
      begin
      if(Tag <> 1)then
        lkSQL := lkSQL+'  AND (('+ERP_SQL_TABLEPREFIX+'.FLAG_DELETE <> 1) OR ('+ERP_SQL_TABLEPREFIX+'.FLAG_DELETE IS NULL)) '+SQLCRLF;
      lkOrderBy := '';
      for i:=1 to Columns.Count-1 do
        if(Columns[i].Title.SortMarker <> smNoneEh)then
          begin
          if(StrTrimAll(lkOrderBy) <> '')then
            lkOrderBy := lkOrderBy +', ';
          lkOrderBy := Columns[i].FieldName;
          if(Columns[i].Title.SortMarker = smUpEh)then
            lkOrderBy := lkOrderBy + ' ASCENDING'
           else
            lkOrderBy := lkOrderBy + ' DESCENDING'
          end; 
      if(StrTrimAll(lkOrderBy) = '')then
        lkOrderBy := ERP_DATASET_DBKEY + ' ASCENDING';
      lkSQL := lkSQL + 'ORDER BY '+lkOrderBy;    
      end;
    with TERPForm_DataSetMain(aOwner) do
      begin
      SelectSQL.Text := lkSQL; 
      Open;
      end; 
{
    if( (StrTrimAll(lkID)<>'') or (UpperCase(lkID) <> 'NULL') )then
      with TERPForm_DBGridMain(aOwner).DataSource.DataSet do
        if Active then
          if( (RecordCount > 0) and (FindField(ERP_DATASET_DBKEY) <> nil) )then
            begin
            DisableControls;
            First;
            while not EOF do
              begin
              if(FieldByName(ERP_DATASET_DBKEY).AsString = lkID)then
                begin
                EnableControls;
                exit;
                end;
              Next;
              end;
            EnableControls;
            end;
}
  end;
  //============================================================================
  procedure TERPFormGrid_PanelLeft_OnShowHide(aOwner :TComponent);
  begin
    if(aOwner.FindComponent(obj_name_erp_actviewpanelleft+'2') <> nil)then
      TERPFormGrid_RefreshView(aOwner);
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_AfterScroll(DataSet :TDataSet);
  var
    lkCmp :TComponent;
  begin
    lkCmp := DataSet.Owner.Owner.FindComponent(obj_name_erp_pagecontroldetail);
    if(lkCmp <> nil)then
      TERPFormGrid_PCDetail_OnChange(TxcPageControlEx(lkCmp));
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
    Result := ERP_ObjectCaption(2)+#$20+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION];
  end;
  //============================================================================
  function TERPFormGrid_ExportGetFilter(aOwner :TComponent):string;
  begin
    Result := '';
  end;
  //============================================================================
  function TERPFormGrid_ExportGetFileName(aOwner :TComponent):string;
  begin
    Result := ERP_ObjectCaption(2)+#$20+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION];
  end;   
  //============================================================================
  procedure TERPForm_StandardTree_AfterBuildData(aFBTreeView:TxFBTreeView);
  begin
    TERPFormGrid_RefreshView(aFBTreeView.Owner);
  end;                
  //============================================================================
  procedure TERPFormGridRef_PositionOnRecord(aOwner :TComponent; const RebuildTree:Boolean);
  var
    lkID, lkS  :string;
    lkSettings :TStrings;
  begin 
    TERPFormGrid_CloseDataSets(aOwner);
    lkSettings := TERPForm_Settings(aOwner);
    lkId := GetGlobalVariable(lkSettings.Values[ERP_SETTINGS_BUFFERVAR]);
    if RebuildTree then
      if(lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] = '1')then
        with TxFBTreeView(aOwner.FindComponent(obj_name_erp_fbtreeview)) do
          begin
          ClearTree;
          lkS    := '';
          if(StrTrimAll(lkID) <> '')then
            if GetField(FBDataBase, lkSettings.Values[ERP_SETTINGS_TABLENAME], lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD], '(ID = '''+lkID+''')', lkS) then
              if(StrTrimAll(lkS) <> '')then
                BuildNodeById(lkS);
          if(Items.Count <= 0)then
            begin    
            BuildTree;
            if(Items.Count > 0)then
              Items[0].Selected := true;
            end;  
          end;
    TERPFormGrid_RefreshView(aOwner); 
    with TERPForm_DBGridMain(aOwner).DataSource.DataSet do
      if( ( (StrTrimAll(lkID)<>'') or (UpperCase(lkID) <> 'NULL') ) and Active )then
        if( (RecordCount > 0) and (FindField(ERP_DATASET_DBKEY) <> nil) )then
          begin
          DisableControls;
          First;
          while not EOF do
            begin
            if(FieldByName(ERP_DATASET_DBKEY).AsString = lkID)then
              begin
              EnableControls;
              exit;
              end;
            Next;
            end;
          EnableControls;
          end;
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_AfterPost(DataSet :TDataSet);
  begin
    TERPFormGrid_RefreshView(DataSet.Owner.Owner);
  end;
  //============================================================================
  function TERPFormGridRef_Create(const aObjId:string;const aModalForm:Boolean):TForm;
  var
    i, c           :Integer;
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
    lkMIItemGroup  :TMenuItem;
    lkPanelLeft    :TxcPanel;
    lkToolBarLeft  :TxcGradientPanelVista;
    lkPanelClient  :TxcPanel;
    lkToolBar      :TxcGradientPanelVista;
    lkToolBarABC   :TxcGradientPanel;
    lkFBTreeView   :TxFBTreeView;
    lkEvents       :TxFBEvents;
    lkSQLSelect    :string; 
    lkSQLRefresh   :string; 
    lkSQLInsert    :string; 
    lkSQLUpdate    :string; 
    lkSQLDelete    :string;
    lkSelectFilter :string;
    lkTActs        :TERPTreeActions;
  begin
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQR, lkDS)  
    lkCreateParams := [erpGrid, erpEvents, erpGridNavigation, erpEvents];
//    if not aModalForm then
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
    if((lkQr.FieldByName('TB_TREE').AsInteger = 1) or (lkQr.FieldByName('GROUPTB_EXISTS').AsInteger = 1))then 
      lkCreateParams := lkCreateParams + [erpPanelLeft, erpPanelLeftToolBar, erpPanelLeftShowHide, erpPanelLeftVisible, erpPanelLeftGroup];
    if((not aModalForm) and (lkQr.FieldByName('TB_ACCS_PRN_CNT').AsInteger > 0) )then
      lkCreateParams := lkCreateParams + [erpGridExport, erpGridPrint, erpGridPrintItem];
    if((lkQr.FieldByName('TB_CHILD_COUNT').AsInteger > 0) or (lkQr.FieldByName('TB_BLOB_COUNT').AsInteger > 0) or (lkQr.FieldByName('TB_FLAG_EXTERNAL').AsInteger <> 0))then
      begin
      lkCreateParams := lkCreateParams + [erpDetail];
      if(lkQr.FieldByName('TB_FLAG_EXTERNAL').AsInteger <> 0)then
        lkCreateParams := lkCreateParams + [erpDetailExternal];
      end;
    if ERP_ObjectExtension_FileExists(aObjId, ERP_OBJECTTYPE_REF)then  
      lkCreateParams := lkCreateParams + [erpDetail, erpDetailExtensions];
    if(lkQr.FieldByName('TB_ACCS_EDIT_CNT').AsInteger > 0)then
      begin
      lkCreateParams := lkCreateParams + [erpGridEdit, erpGridEditPostCancel];
      if(lkQr.FieldByName('TB_ACCS_INS_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditIns, erpGridEditCreate];
      if(lkQr.FieldByName('TB_ACCS_UPD_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditUpd, erpGridEditEdt, erpGridEditMark, erpGridEditUpdGroup];
      if(lkQr.FieldByName('TB_ACCS_DEL_CNT').AsInteger > 0)then lkCreateParams := lkCreateParams + [erpGridEditDel];
      end;
//    lkCreateParams := lkCreateParams - [erpGridGroup];
    Result := TERPFormGrid_Create(lkQr.FieldByName('TB_NAME').AsString, ERP_ObjectCaption(ERP_OBJECTTYPE_REF), ERP_ObjectIcon(ERP_OBJECTTYPE_REF), ERP_ObjectBitmap(ERP_OBJECTTYPE_REF), aModalForm, lkCreateParams);
    with Result do
      begin
      HelpKeyWord := aObjId;
      if aModalForm then    
        begin
        TForm_Position_Load(Result, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_REF,ERP_OBJECTTYPE_REF,aObjId,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))),
          MaxInteger(lkQr.FieldByName('TB_DLG_HEIGHT').AsInteger,600), MaxInteger(lkQr.FieldByName('TB_DLG_WIDTH').AsInteger,800));
        //ExecSQL(FBDataBase, 'EXECUTE PROCEDURE PROC$_USERS_LOG_INS(1000014, '''+aObjId+''', NULL, NULL, NULL);');  
        end  
       else 
        begin
        // logging and users recent menu
        ExecSQL(FBDataBase,'EXECUTE BLOCK AS DECLARE VARIABLE P DOMN$INTEGER; '+SQLCRLF+'BEGIN '+SQLCRLF+
          '  IF(NOT(EXISTS(SELECT R.RDB$RELATION_ID FROM RDB$RELATIONS R WHERE(TRIM(R.RDB$RELATION_NAME)=''TABL$_USERS_RCNT''))))THEN EXIT; '+SQLCRLF+
          '  EXECUTE STATEMENT ''UPDATE OR INSERT INTO TABL$_USERS_RCNT(NAME, USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME)VALUES('''''+Result.Caption+''''', '''''+
           GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''''', 0, '''''+IntToStr(ERP_OBJECTTYPE_REF)+''''', '''''+ScriptName+
           ''''')MATCHING(USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME);''; '+SQLCRLF+
           '  /* SELECT MAX(P.ID) FROM PROC$_USERS_LOG_INS(1000012, '''+AOBJID+''', NULL, NULL, NULL) P INTO :P; */'+SQLCRLF+
           '  END');    
        end;
      end;  
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_REF);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_REF);
      end;  
    with TERPForm_DataSetMain(Result) do
      begin
      with GeneratorField do
        begin 
        ApplyEvent := gamOnServer;
        Field      := lkQr.FieldByName('TB_GENR_FLD').AsString;
        Generator  := lkQr.FieldByName('TB_GENR').AsString;
        IncrementBy:= 1;
        end;
      end; 
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_BUFFERVAR      ] := lkQr.FieldByName('TB_BUFFER_VAR').AsString;
      Values[ERP_SETTINGS_TABLENAME      ] := aObjId;
      Values[ERP_SETTINGS_TABLECAPTION   ] := lkQr.FieldByName('TB_NAME').AsString;
      Values[ERP_SETTINGS_REF_TREE       ] := '0';
      Values[ERP_SETTINGS_REF_TREEORGROUP] := '0';
      Values[ERP_SETTINGS_REF_TREEFIELD  ] := '';
      Values[ERP_SETTINGS_ITEM_SCRIPT    ] := lkQr.FieldByName('TB_SC_ITEM').AsString;
      Values[ERP_SETTINGS_ITEM_SCRIPTDLG ] := lkQr.FieldByName('TB_SC_ITEM_DLG').AsString;
      Values[ERP_SETTINGS_BASETYPE       ] := '2';
      Values[ERP_SETTINGS_TEMPFILENAME   ] := ERP_ObjectTempFileName(ERP_OBJECTTYPE_REF,ERP_OBJECTTYPE_REF,aObjId,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));
      end;
    lkMainMenu   := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu)); 
    lkMIMenuMain := TMenuItem(lkMainMenu.Items.FindComponent(obj_name_erp_mimainmenu));//lkMIMenuMain.Caption := ERP_ObjectCaption(2);
    lkMIItem     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainitem));
    lkMIObj      := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainobj)); lkMIObj.ImageIndex := ERP_ObjectImageIndex(ERP_OBJECTTYPE_REF); lkMIObj.Caption := ERP_ObjectCaption(2);
    lkMIView     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainview));
    if not aModalForm then
      begin
      lkAct := TCustomAction(Result.FindComponent(obj_name_erp_actprintitem));lkAct.ImageIndex := 178;
      lkAct := TCustomAction(Result.FindComponent(obj_name_erp_actprintgrid));lkAct.ImageIndex := 234;
      CreateTMenuItem(lkMIMenuMain,obj_name_erp_mimaindb,msg_erp_mimaindb,'','',ERP_ObjectImageIndex(ERP_OBJECTTYPE_REFS),  0);
      ERP_DBMenuItems_Build(lkMIMenuMain, aObjId, '0', @TERPFormGrid_DatabaseMenuItem_OnClick);
      end;    
    lkPanelClient:= TxcPanel(Result.FindComponent(obj_name_erp_panelclient));
    lkToolBar    := TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbar));
    lkEvents     := TxFBEvents(Result.FindComponent(obj_name_erp_data_evmain));
    lkEvents.Events.Add(aObjId);
    if(lkQr.FieldByName('TB_FLAG_SHOWGROUPBAR').AsInteger = 1)then
      begin
      lkToolBarABC := CreateTxcGradientPanelVistaToolBar(Result,lkPanelClient,obj_name_erp_toolbarabc, '', alTop, 0,lkToolBar.Top+lkToolBar.Height+1,20, 200, xbsRaized);
      with lkToolBarABC do
        begin
        Font.Style := [fsBold];
        Font.Size  := 8;
        Visible    := false;
        ShowHint   := true;
        with CreateTxcToolBarButton(lkToolBarABC,lkToolBarABC,'',' бяе',msg_erp_show_on_litera+' "бяе" ',1,1,32,32,alLeft,-1,nil) do
          begin
          ShowCaption:= true;
          GroupIndex := ERP_REFERENCE_ABCGROUPINDEX;
          Tag        := -1;
          Down       := (ERP_SETTINGS_REF_LITERA = '');
          OnClick    := @TERPFormGridRef_tbbABC_OnClick;
          end;
        c := 0;  
        for i:=Ord('ю') to Ord('ъ') do
          with CreateTxcToolBarButton(lkToolBarABC,lkToolBarABC,'',Chr(i),msg_erp_show_on_litera+' "'+Chr(i)+'" ',33+(c*16),1,32,16,alLeft,-1,nil) do
            begin
            c := c + 1;
            ShowCaption:= true;
            GroupIndex := ERP_REFERENCE_ABCGROUPINDEX;
            Tag        := i;
            Down       := (ERP_SETTINGS_REF_LITERA = Chr(i));
            OnClick    := @TERPFormGridRef_tbbABC_OnClick;
            end;
        for i:=Ord('A') to Ord('Z') do
          with CreateTxcToolBarButton(lkToolBarABC,lkToolBarABC,'',Chr(i),msg_erp_show_on_litera+' "'+Chr(i)+'" ',33+(c*16),1,32,16,alLeft,-1,nil) do
            begin
            c := c + 1;
            ShowCaption:= true;
            GroupIndex := ERP_REFERENCE_ABCGROUPINDEX;
            Tag        := i;
            Down       := (ERP_SETTINGS_REF_LITERA = Chr(i));
            OnClick    := @TERPFormGridRef_tbbABC_OnClick;
            end;
        Visible := true;
        end;
      end;    
    if((lkQr.FieldByName('TB_TREE').AsInteger = 1) or (lkQr.FieldByName('GROUPTB_EXISTS').AsInteger = 1))then
      begin
      lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] := '1';
      lkPanelLeft   := TxcPanel(Result.FindComponent(obj_name_erp_panelleft));
      lkToolBarLeft := TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbarleft));
      lkMIItemGroup := CreateTMenuItem(lkMIItem,obj_name_erp_mimainitemgroup,msg_erp_mimainitemgroup,'','',18,0);
      lkFBTreeView  := CreateTxFBTreeView(Result, lkPanelLeft, obj_name_erp_fbtreeview, 1,1,200,200,alClient);
      with lkFBTreeView do
        begin
        HelpKeyWord := '';
        Images      := CreateTImageList(lkFBTreeView, 'ilFBTreeView', [30]);
        Tag         := 1;    
        OnClick     := @TERPFormGridRef_FBTreeView_OnClick;
        OnBuildNode := @TERPFormGridRef_FBTreeView_OnBuildNode;
        OnDragDrop  := @TERPFormGridRef_FBTreeView_OnDragDrop;
        OnDragOver  := @TERPFormGridRef_FBTreeView_OnDragOver;
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
      lkTActs := [];  
      if((lkQr.FieldByName('TB_ACCS_INS_CNT').AsInteger > 0) or (lkQr.FieldByName('GROUPTB_ACCS_INS_CNT').AsInteger > 0))then lkTActs := lkTActs + [eacTreeNew,eacTreeIns];
      if((lkQr.FieldByName('TB_ACCS_UPD_CNT').AsInteger > 0) or (lkQr.FieldByName('GROUPTB_ACCS_UPD_CNT').AsInteger > 0))then lkTActs := lkTActs + [eacTreeUpd,eacTreeEdt];
      if((lkQr.FieldByName('TB_ACCS_DEL_CNT').AsInteger > 0) or (lkQr.FieldByName('GROUPTB_ACCS_DEL_CNT').AsInteger > 0))then lkTActs := lkTActs + [eacTreeDel];
      TERPForm_StandardTree_CreateActions(lkFBTreeView, lkToolBarLeft, lkMIItemGroup, lkTActs);  
      with TERPForm_DBGridMain(Result) do
        DragMode := dmAutomatic;
      end;
    TERPFormGrid_LoadDBGridColumns(aObjId, lkQr, TERPForm_DBGridMain(Result), TxcPageControlEx(Result.FindComponent(obj_name_erp_pagecontroldetail)), 
      (lkSettings.Values[ERP_SETTINGS_REF_TREEORGROUP] = '1'), false, 
      lkSettings.Values[ERP_SETTINGS_REF_TREEFIELD], lkSQLSelect, lkSQLRefresh, lkSQLInsert, lkSQLUpdate, lkSQLDelete, lkSelectFilter);
    TERPForm_GridSettingsLoad(TERPForm_DBGridMain(Result), lkSettings.Values[ERP_SETTINGS_TEMPFILENAME]);
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
    with TERPForm_MemTableMain(Result) do
      begin 
      //AfterPost    := @TERPForm_DataSetMain_AfterPost;
      //AfterCancel  := @TERPForm_DataSetMain_AfterCancel;
      //BeforePost   := @TERPForm_DataSetMain_BeforePost;
      //BeforeInsert := @TERPForm_DataSetMain_BeforeInsertEdit;
      //BeforeEdit   := @TERPForm_DataSetMain_BeforeInsertEdit; 
      AfterDelete  := @TERPForm_DataSetMain_AfterPost;
      end;  
    with TERPForm_DBGridMain(Result) do
      begin
      OnGetCellParams := @ERP_DBGridEh_OnGetCellParams_Ref;
      OnDblClick      := nil;
      end;   
    lkToolBar := TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbar_view));
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actgriddatadet ,msg_erp_actgriddatadet ,msg_erp_actgriddatadet_hint ,'',0,392,@TERPFormGridRef_actGridDataDetail_OnExecute      ,@TERPFormGridRef_actGridDataForm_OnUpdate,lkToolBar,lkMIObj);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actgriddataform,msg_erp_actgriddataform,msg_erp_actgriddataform_hint,'',0,393,@TERPFormGridRef_actGridDataForm_OnExecute        ,@TERPFormGridRef_actGridDataForm_OnUpdate,lkToolBar,lkMIObj);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actgriddataloc ,msg_erp_actgriddataloc ,msg_erp_actgriddataloc_hint ,'',0,599,@TERPFormGridRef_actGridDataLocalization_OnExecute,@TERPFormGridRef_actGridDataForm_OnUpdate,lkToolBar,lkMIObj);
    lkToolBar.Width := TWinControl_AutoWidth(lkToolBar)+2;   
    TERPFormGridRef_PositionOnRecord(Result, true);
    if not aModalForm then
      if not lkEvents.Registered then
        lkEvents.RegisterEvents;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
    //StringsSaveToFile(PrepareAbsoleteFileName('TMP:ERP_SETTINGS_REF_'+aObjId+'.XFM'), ComponentToStr(Result));  
    Result.ActiveControl := TERPForm_DBGridMain(Result); 
  end;
  //============================================================================
  function Reference_Create(const aObjId :string):TForm;
  begin
    Result := TERPFormGridRef_Create(aObjId, false);
  end;
  //============================================================================
  function Reference_Execute(const aObjId :string):TForm;
  begin
    Result := TERPFormGridRef_Create(aObjId, true);
    with Result do
      begin
      SetGlobalVariable(TERPForm_Settings(Result).Values[ERP_SETTINGS_BUFFERVAR], 'NULL');
      if(ShowModal <> mrOK)then
        SetGlobalVariable(TERPForm_Settings(Result).Values[ERP_SETTINGS_BUFFERVAR], 'NULL')
       else
        with TERPForm_DBGridMain(Result).DataSource.DataSet do
          begin
          if(FindField(ERP_DATASET_DBKEY) <> nil)then
            SetGlobalVariable(TERPForm_Settings(Result).Values[ERP_SETTINGS_BUFFERVAR], FindField(ERP_DATASET_DBKEY).AsString);
          end;
      TForm_Position_Save(Result, PrepareAbsoleteFileName(TERPForm_Settings(Result).Values[ERP_SETTINGS_TEMPFILENAME]) );
      Result.Free;
      end;  
  end; 
