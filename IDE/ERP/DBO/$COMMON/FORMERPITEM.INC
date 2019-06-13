{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                       {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                         {$I PEAKTOP:GLOBAL_OBJECTS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                          {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                          {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}                          {$I PEAKTOP:OBJ/TMENUITEM.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                          {$I PEAKTOP:OBJ/TSPLITTER.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                   {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}              {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                   {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                   {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                        {$I PEAKTOP:OBJ/TXCTABSHEET.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSCROLLBOX.INC}                         {$I PEAKTOP:OBJ/TSCROLLBOX.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                       {$I PEAKTOP:OBJ/TXFBDATASETS.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBTREEVIEW.INC}                       {$I PEAKTOP:OBJ/TXFBTREEVIEW.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}                  {$I ../SHORTCUTS.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}             {$I ../DBGRID/ACTIONS.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC}        {$I ../DBGRID/FOOTERS_LOAD.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/INTF.INC}          {$I ../DBGRID/PRINT/INTF.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/LOADITEMS.INC}             {$I ../MENU/LOADITEMS.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC}       {$I ./FORMERP_BLOB.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}       {$I ./FORMERP_LANG.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$I ./FORMERP.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC}         {$I ./EXTENSIONS.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_FILTER.INC} {$I ./FORMERPGRID_FILTER.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM_HEADER.INC} {$I ./FORMERPITEM_HEADER.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM_ACTIONS.INC}{$I ./FORMERPITEM_ACTIONS.INC}               {$ENDIF}
  //================ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM.INC ===============
  procedure TERPFormItem_DataSetMain_AfterScroll(DataSet :TDataSet);
  var
    lkCapt :string;
  begin
    if( (TERPForm_ObjType(DataSet.Owner.Owner) = ERP_OBJECTTYPE_REF) or (TERPForm_ObjType(DataSet.Owner.Owner) = ERP_OBJECTTYPE_REG) )then
      begin
      if(DataSet.FindField('NAME') <> nil)then
        lkCapt := DataSet.FieldByName('NAME').AsString;
      if(StrTrimAll(lkCapt) = '')then  
        lkCapt := TERPForm_Settings(DataSet.Owner.Owner).Values[ERP_SETTINGS_TABLECAPTION]+' ['+DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+']';
      TERPForm_SetCaption(DataSet.Owner.Owner, lkCapt);
      end
  end;
  //============================================================================
  procedure TERPFormItem_DataSetMain_AfterOpen(DataSet :TDataSet);  
  begin
    TERPForm_OpenDataSetsChilds(DataSet);
  end;
  //============================================================================
  procedure TERPFormItem_DataSetMain_BeforeClose(DataSet :TDataSet);
  begin
    TERPForm_CloseDataSetsChilds(DataSet);
  end;
  //============================================================================
  procedure TERPFormItem_DataSetMain_AfterPost(DataSet :TDataSet);
  begin
    TERPFormItem_RefreshView(DataSet.Owner.Owner);  
  end;
  //============================================================================
  procedure TERPFormItem_DataSetMain_AfterEdit(DataSet :TDataSet);
  var
    i :Integer;
  begin
    for i:=0 to DataSet.Fields.Count-1 do
      begin
      if( DataSet.Fields[i].FieldName = ERP_SQL_PERIODICALDATEFIELD )then
        try DataSet.Fields[i].AsDateTime := Now; except end;
      end;
  end;
  //============================================================================
  procedure TERPFormItem_evMain_OnEventAlert(Sender :TObject; EventName: string; EventCount: LongInt; var CancelAlerts: Boolean);
  begin
    with TERPForm_DataSetMain(TComponent(Sender).Owner) do
      begin
      if(Active and (State = dsBrowse) )then
        TERPFormItem_RefreshView(TComponent(Sender).Owner);
      end; 
    CancelAlerts := false;
  end;
  //============================================================================
  procedure TERPFormItem_DatabaseMenuItem_OnClick(Sender :TObject);
  var
    lkScName :string;
    lkOwner  :TComponent;
  begin
    lkOwner := TComponent(Sender); 
    while(lkOwner <> nil)do
      begin
      if ObjectInheritsFrom(lkOwner,'TCustomForm')then
        break; 
      lkOwner := lkOwner.Owner;
      end;
    if not ObjectInheritsFrom(lkOwner,'TCustomForm')then exit;
    with TERPForm_DataSetMain(lkOwner) do
      begin
      if not Active then exit;
      if not(RecordCount > 0)then exit;
      lkScName := ERP_DBMenuItem_GetScript(TComponent(Sender).Tag);
      if(StrTrimAll(lkScName) = '')then exit;
      SetGlobalVariable(TERPForm_Settings(lkOwner).Values[ERP_SETTINGS_BUFFERVAR], TERPForm_Settings(lkOwner).Values[ERP_DATASET_DBKEY]);
      call(lkScName);
      end;
  end;
  //============================================================================
  procedure TERPFormItem_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    TERPFormItem_Destroy(TComponent(Sender));
    Action := caFree;
  end;
  //============================================================================
  function TERPFormItem_Create(const aCaption, aMenuItemCaption, aFileNameIcon, aFileNameBitmap :string; 
             const aModalForm:Boolean; const aCreateParams:TFormERPParams):TForm;
  var
    lkMainMenu    :TMainMenu;
    lkMIMenuMain  :TMenuItem;
    lkMIView      :TMenuItem;
    lkMIItem      :TMenuItem;
    lkMI          :TMenuItem;
    lkPanelClient :TxcGradientPanel;
    lkToolBar     :TxcGradientPanelVista;
    lkToolBarView :TxcGradientPanelVista;
    lkToolBarItem :TxcGradientPanelVista;
    lkToolBarExp  :TxcGradientPanelVista;
    lkLBL         :TLabel;
    lkTr          :TxFBTransaction;
    lkDTS         :TxFBDataSet;
    lkDS          :TDataSource;
    lkEvents      :TxFBEvents;
    lkSplt        :TSplitter;
    lkPCDetail    :TxcPageControlEx;
    lkAct         :TCustomAction;
  begin
    Result := TERPForm_Create(aCaption, aFileNameIcon, aFileNameBitmap, aModalForm, @TERPFormItem_OnClose);
    TCustomAction(Result.FindComponent(obj_name_erp_actclose)).OnExecute := @TERPFormItem_actClose_OnExecute;
    if( not aModalForm and (GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT) = 'PEAKTOP'))then
      lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actconfig,'Настройка объекта','',ERP_FILENAME_BMP_CONFIGURATOR ,@TERPForm_actConfig_OnExecute,nil,TxcGradientPanel(Result.FindComponent(obj_name_erp_topbar)));
    lkMainMenu    := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIMenuMain  := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,aMenuItemCaption  ,'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
    lkMIItem      := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainitem,msg_erp_mimainitem,'','',103,  0);
    lkMIView      := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainview,msg_erp_mimainview,'','',150,  0);
    lkPanelClient := CreateTxcGradientPanel(Result,Result,obj_name_erp_panelclient,'',alClient,1,1,600,800,xbsNone, gdRightToLeft); 
    lkToolBar     := CreateTxcGradientPanelVistaToolBar(Result,lkPanelClient,obj_name_erp_toolbar,'',alTop, 0, 24,TERPForm_DefaultToolButtonWidth+2, 200,xbsRaized);
    lkToolBarView := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_view  ,'',alLeft, TERPForm_DefaultToolButtonWidth,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkLBL := CreateTLabel(lkToolBar,lkToolBar,'', lkToolBarView.Left+lkToolBarView.Width+1,1,lkToolBar.Height-2,TERPForm_DefaultToolSeparatorWidth,alLeft,taCenter);
    lkToolBarItem := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_item  ,'',alLeft, lkLBL.Left+lkLBL.Width+1,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkLBL := CreateTLabel(lkToolBar,lkToolBar,'', lkToolBarItem.Left+lkToolBarItem.Width+1,1,lkToolBar.Height-2,TERPForm_DefaultToolSeparatorWidth,alLeft,taCenter);
    lkToolBarExp  := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_export,'',alLeft, lkLBL.Left+lkLBL.Width+1,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkLBL := CreateTLabel(lkToolBar,lkToolBar,'', lkToolBarExp.Left+lkToolBarExp.Width+1,1,lkToolBar.Height-2,TERPForm_DefaultToolSeparatorWidth,alLeft,taCenter);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewrefresh,msg_erp_actviewrefresh,msg_erp_actviewrefresh_hint,SHORTCUT_DATA_REFRESH,0,170,@TERPFormItem_actViewRefresh_OnExecute,nil                                 ,lkToolBarView,lkMIView);
    CreateTxFBTransDataSet(Result, obj_name_erp_data_trmain, obj_name_erp_data_dtsmain, 'DataSource'+obj_name_erp_data_dtsmain, ['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);  
    with lkDTS do
      begin
      AfterOpen   := @TERPFormItem_DataSetMain_AfterOpen;
      BeforeClose := @TERPFormItem_DataSetMain_BeforeClose;
      AfterScroll := @TERPFormItem_DataSetMain_AfterScroll;
      AfterPost   := @TERPFormItem_DataSetMain_AfterPost;
      AfterEdit   := @TERPFormItem_DataSetMain_AfterEdit;
      end;    
    if not(erpGridNoCopy in aCreateParams)then
      begin
      lkAct := TERPForm_CreateAction(Result,obj_name_erp_actcopytoclbrd,msg_erp_actcopytoclbrd,msg_erp_actcopytoclbrd_hint,SHORTCUT_DATA_COPYTOCLIPBOARD,0, 68,@TERPFormItem_actCopyToClipboard_OnExecute,@TERPFormItem_actPrintItem_OnUpdate,lkToolBarItem,lkMIItem);
      lkMI  := CreateTMenuItem(lkMIItem,'N00001' ,'-','','', -1,0);
      end; 
    if(erpGridEdit in aCreateParams)then
      begin
      if(erpGridEditPostCancel in aCreateParams)then
        begin  
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actpost  ,msg_erp_actpost  ,msg_erp_actpost_hint  ,SHORTCUT_DATA_POST  ,0,143,@TERPFormItem_actEditPost_OnExecute  ,@TERPFormItem_actEditPost_OnUpdate,lkToolBarItem,lkMIItem);
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actcancel,msg_erp_actcancel,msg_erp_actcancel_hint,SHORTCUT_DATA_CANCEL,0,171,@TERPFormItem_actEditCancel_OnExecute,@TERPFormItem_actEditPost_OnUpdate,lkToolBarItem,lkMIItem);
        lkMI  := CreateTMenuItem(lkMIItem,'N00002' ,'-','','', -1,0); 
        end;
      if(erpGridEditMark in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actmark  ,msg_erp_actmark  ,msg_erp_actmark_hint  ,SHORTCUT_DOC_MARKDELETE  ,0,300,@TERPFormItem_actEditMark_OnExecute  ,@TERPFormItem_actPrintItem_OnUpdate,lkToolBarItem,lkMIItem);
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actunmark,msg_erp_actunmark,msg_erp_actunmark_hint,SHORTCUT_DOC_UNMARKDELETE,0,299,@TERPFormItem_actEditUnMark_OnExecute,@TERPFormItem_actPrintItem_OnUpdate,lkToolBarItem,lkMIItem);
        lkMI  := CreateTMenuItem(lkMIItem,'N00003' ,'-','','', -1,0); 
        end;
      if(erpGridEditCommit in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actcommit  ,msg_erp_actcommit  ,msg_erp_actcommit_hint  ,SHORTCUT_DOC_COMMIT  ,0,298,@TERPFormItem_actEditCommit_OnExecute  ,@TERPFormItem_actPrintItem_OnUpdate,lkToolBarItem,lkMIItem);
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actuncommit,msg_erp_actuncommit,msg_erp_actuncommit_hint,SHORTCUT_DOC_UNCOMMIT,0,297,@TERPFormItem_actEditUnCommit_OnExecute,@TERPFormItem_actPrintItem_OnUpdate,lkToolBarItem,lkMIItem);
        lkMI  := CreateTMenuItem(lkMIItem,'N00004' ,'-','','', -1,0); 
        end;
      end;
    if(erpGridPrintItem in aCreateParams)then
      begin
      lkAct := TERPForm_CreateAction(Result,obj_name_erp_actprintitem,msg_erp_actprintitem,msg_erp_actprintitem_hint,SHORTCUT_PRINT,0,105,@TERPFormItem_actPrintItem_OnExecute,@TERPFormItem_actPrintItem_OnUpdate,lkToolBarExp,lkMIItem);
      end;
    if(erpEvents in aCreateParams)then
      begin
      lkEvents := TxFBEvents.Create(Result);
      with lkEvents do
        begin
        Name         := obj_name_erp_data_evmain;
        DataBase     := FBDataBase;
        OnEventAlert := @TERPFormItem_evMain_OnEventAlert;
        Events.Clear;
        end;
      end;  
    if(erpDetail in aCreateParams)then
      begin
      lkSplt := CreateTSplitter(Result,lkPanelClient,obj_name_erp_splitterdetail,alBottom,0,600,4,800);
      lkPCDetail := CreateTxcPageControlEx(Result,lkPanelClient,obj_name_erp_pagecontroldetail,0,600,200,200,alBottom);
      lkPCDetail.OnChange := @TERPFormItem_PCDetail_OnChange;
      lkAct := TERPForm_CreateAction(Result, obj_name_erp_actviewdetail, msg_erp_actviewdetail, msg_erp_actviewdetail_hint,SHORTCUT_DATA_DETAIL,0,491,@TERPFormItem_actViewDetail_OnExecute, @TERPFormItem_actViewDetail_OnUpdate, lkToolBarView, lkMIView);
      if(not(erpDetailVisible in aCreateParams))then
        begin
        lkPCDetail.Visible := false;
        lkSplt.Visible     := false;       
        end;
      if(erpDetailExternal in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actgriddataextr,msg_erp_actgriddataextr,msg_erp_actgriddataextr_hint,'',0,395,@TERPFormItem_actViewExternal_OnExecute, @TERPFormItem_actViewExternal_OnUpdate, lkToolBarView, lkMIView);
        end;  
      end;
    lkToolBarView.Width := TWinControl_AutoWidth(lkToolBarView)+2; lkToolBarView.Visible:= (lkToolBarView.ControlCount > 0);   
    lkToolBarItem.Width := TWinControl_AutoWidth(lkToolBarItem)+2; lkToolBarItem.Visible:= (lkToolBarItem.ControlCount > 0);  
    lkToolBarExp.Width  := TWinControl_AutoWidth(lkToolBarExp )+2; lkToolBarExp.Visible := (lkToolBarExp.ControlCount  > 0);
    Amunhotep.MainForm.xcMenu.AddMenu(lkMainMenu); lkMainMenu.OwnerDraw := true;
    Result.Menu := lkMainMenu;
  end;
