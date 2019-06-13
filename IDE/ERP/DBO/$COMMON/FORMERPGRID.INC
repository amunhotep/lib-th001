{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                        {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                          {$I PEAKTOP:GLOBAL_OBJECTS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/TARRAYSTRINGUNIQUE.INC}             {$I PEAKTOP:SYSUTILS/TARRAYSTRINGUNIQUE.INC} {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/SQL/GETFIELDS.INC}                  {$I PEAKTOP:SYSUTILS/SQL/GETFIELDS.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                           {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                           {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDATETIMEPICKER.INC}                     {$I PEAKTOP:OBJ/TDATETIMEPICKER.INC}         {$ENDIF}
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
{$IFNDEF PEAKTOP:OBJ/TXFBTREEVIEW.INC}                        {$I PEAKTOP:OBJ/TXFBTREEVIEW.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}                   {$I ../SHORTCUTS.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}                 {$I ../OBJECTNAMES.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC}         {$I ../DBGRID/COL_PROTOCOL.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC}         {$I ../DBGRID/FOOTERS_LOAD.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/INTF.INC}           {$I ../DBGRID/PRINT/INTF.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}              {$I ../DBGRID/ACTIONS.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/LOADITEMS.INC}              {$I ../MENU/LOADITEMS.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC}        {$I ./FORMERP_BLOB.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}        {$I ./FORMERP_LANG.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}             {$I ./FORMERP.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC}          {$I ./EXTENSIONS.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_FILTER.INC}  {$I ./FORMERPGRID_FILTER.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_HEADER.INC}  {$I ./FORMERPGRID_HEADER.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_ACTIONS.INC} {$I ./FORMERPGRID_ACTIONS.INC}               {$ENDIF}
var
  TERPFormGrid_RefreshingNow :Boolean;
  //============== PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID.INC =================
  procedure TERPFormGrid_dtsMain_AfterOpen(DataSet :TDataSet);  
  begin
    with DataSet.Owner do
      if(TERPForm_Settings(Owner).Values[ERP_SETTINGS_DATAMEMORY] = '1')then
        with  TERPForm_MemTableMain(Owner) do
          if not Active then
            try
              Open;
            finally
              //SortByFields();
            end;
  end;
  //============================================================================
  procedure TERPFormGrid_dtsMain_BeforeClose(DataSet :TDataSet);
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
  procedure TERPForm_DataSetMain_AfterOpen(DataSet :TDataSet);  
  var
    lkVar:string;
    lkID :string;
  begin
    lkVar := StrTrimAll(TERPForm_Settings(DataSet.Owner.Owner).Values[ERP_SETTINGS_GOTOVAR]);
    if(lkVar <> '')then
      begin
      lkID := UpperCase(StrTrimAll(GetGlobalVariable(lkVar)));
      if not((lkID='NULL') or (lkID='0')) then
        begin
        with DataSet do
          begin
          DisableControls;
          while( (not EOF) and (lkID <> FieldByName(ERP_DATASET_DBKEY).AsString) )do
            Next;
          EnableControls;
          end;  
        SetGlobalVariable(lkVar, '0');  
        end;
      end; 
    TERPForm_OpenDataSetsChilds(DataSet);
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_BeforeClose(DataSet :TDataSet);
  begin
    with TERPForm_Settings(DataSet.Owner.Owner) do
      begin
      Values[ERP_SETTINGS_SAVERECNO] := IntToStr(DataSet.RecNo);
      Values[ERP_SETTINGS_BOOKMARK ] := '1';
      if(StrTrimAll(Values[ERP_SETTINGS_BUFFERVAR]) <> '')then
        begin
        SetGlobalVariable(Values[ERP_SETTINGS_BUFFERVAR], DataSet.FieldByName(ERP_DATASET_DBKEY).AsString);
        if ObjectInheritsFrom(DataSet, 'TMemTableEh')then
          if( (TERPForm_DataSetMain(DataSet.Owner.Owner).GeneratorField.Field <> '') and (DataSet.RecordCount>0) )then
            begin
            SetGlobalVariable(Values[ERP_SETTINGS_BUFFERVAR], DataSet.FieldByName(TERPForm_DataSetMain(DataSet.Owner.Owner).GeneratorField.Field).AsString);
            end;
        end;
      // for tree references user may choose item on a tree 
      if((StrToInt(Values[ERP_SETTINGS_BASETYPE]) = ERP_OBJECTTYPE_REF) and (Values[ERP_SETTINGS_REF_TREE] = '1'))then
        if ObjectInheritsFrom(TCustomForm(DataSet.Owner.Owner).ActiveControl, 'TxFBTreeView')then
          SetGlobalVariable(Values[ERP_SETTINGS_BUFFERVAR], TxFBTreeView(TCustomForm(DataSet.Owner.Owner).ActiveControl).GetId);
      end;
    TERPForm_CloseDataSetsChilds(DataSet);
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_AfterEdit(DataSet :TDataSet);
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
  procedure TERPFormGrid_evMain_OnEventAlert(Sender :TObject; EventName: string; EventCount: LongInt; var CancelAlerts: Boolean);
  begin
//    if( Amunhotep.MainForm.ActiveMDIChild = TForm(TComponent(Sender).Owner) )then
      with TERPForm_DBGridMain(TComponent(Sender).Owner).DataSource.DataSet do
        begin
        if((not TERPFormGrid_RefreshingNow) and Active and (State = dsBrowse) )then
          TERPFormGrid_RefreshView(TComponent(Sender).Owner);
        end; 
    CancelAlerts := false;
  end;
  //============================================================================
  procedure TERPFormGrid_DBGrid_OnKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  begin
    if(Shift = [])then
      begin
      if(Key = $74 (*F5   *) )then TERPFormGrid_RefreshView(TComponent(Sender).Owner);
      if(Key = $7B (*F12  *) )then TERPForm_actOk_OnExecute(TComponent(Sender).Owner.FindComponent(obj_name_erp_actok));
      end; 
    if(Shift = [ssCtrl])then
      begin
      if(Key = $0D (*VK_RETURN*) )then TERPForm_actOk_OnExecute(TComponent(Sender).Owner.FindComponent(obj_name_erp_actok));
      if(Key = $73 (*VK_F4    *) )then TERPForm_actClose_OnExecute(TComponent(Sender).Owner.FindComponent(obj_name_erp_actclose));
      if(Key = $2E (*VK_DELETE*) )then ERP_DBGridEh_actEdtDel_OnExecute(Sender);
      end;   
  end;
  //============================================================================
  procedure TERPFormGrid_DatabaseMenuItem_OnClick(Sender :TObject);
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
    lkScName := ERP_DBMenuItem_GetScript(TComponent(Sender).Tag);
    if(StrTrimAll(lkScName) = '')then exit;
    with TERPForm_ActiveDBGrid(lkOwner).DataSource.DataSet do
      begin 
      if not Active then exit;
      if not(RecordCount > 0)then exit; 
      SetGlobalVariable(TERPForm_Settings(lkOwner).Values[ERP_SETTINGS_BUFFERVAR], FieldByName(ERP_DATASET_DBKEY).AsString);
      end;
    call(lkScName);
  end;
  //============================================================================
  procedure TERPFormGrid_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    TERPForm_GridSettingsSave(TERPForm_DBGridMain(TComponent(Sender)), TERPForm_Settings(TComponent(Sender)).Values[ERP_SETTINGS_TEMPFILENAME] );
    TERPFormGrid_Destroy(TComponent(Sender));
    Action := caFree;
  end;
  //============================================================================
  function TERPFormGrid_Create(const aCaption, aMenuItemCaption, aFileNameIcon, aFileNameBitmap :string; 
             const aModalForm:Boolean; const aCreateParams:TFormERPParams):TForm;
  var
    lkMainMenu    :TMainMenu;
    lkMIMenuMain  :TMenuItem;
    lkMIView      :TMenuItem;
    lkMIObj       :TMenuItem;
    lkMIItem      :TMenuItem;
    lkMIPrint     :TMenuItem;
    lkPanelLeft   :TxcPanel;
    lkToolBarLeft :TxcGradientPanelVista;
    lkPanelClient :TxcPanel;
    lkToolBar     :TxcGradientPanelVista;
    lkToolBarView :TxcGradientPanelVista;
    lkToolBarItem :TxcGradientPanelVista;
    lkToolBarExp  :TxcGradientPanelVista;
    lkPanelDate   :TxcGradientPanelVista;
    lkLBL         :TLabel;
    lkDTPDateFrom :TDateTimePicker;
    lkDTPDateTo   :TDateTimePicker;
    lkTr          :TxFBTransaction;
    lkDTS         :TxFBDataSet;
    lkDS, lkDSMT  :TDataSource;
    lkDSDrv       :TDataSetDriverEh;
    lkMT          :TMemTableEh;
    lkDBG         :TDBGridEh;
    lkEvents      :TxFBEvents;
    lkSplt        :TSplitter;
    lkPCDetail    :TxcPageControlEx;
    lkAct         :TCustomAction;
  begin
    TERPFormGrid_RefreshingNow := False;
    Result := TERPForm_Create(aCaption, aFileNameIcon, aFileNameBitmap, aModalForm, @TERPFormGrid_OnClose);
    TCustomAction(Result.FindComponent(obj_name_erp_actclose)).OnExecute := @TERPFormGrid_actClose_OnExecute;
    if( not aModalForm and (GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT) = 'PEAKTOP'))then
      begin
      lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actconfig    ,'Настройка объекта','',ERP_FILENAME_BMP_CONFIGURATOR,@TERPForm_actConfig_OnExecute,nil,TxcGradientPanel(Result.FindComponent(obj_name_erp_topbar)));
      lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actconfigmenu,'Настройка меню'   ,'',ERP_FILENAME_BMP_MENU    ,@TERPForm_actConfigMenu_OnExecute,nil,TxcGradientPanel(Result.FindComponent(obj_name_erp_topbar)));
      end;
    lkMainMenu    := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIMenuMain  := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,aMenuItemCaption  ,'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
    lkMIItem      := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainitem      ,msg_erp_mimainitem,'','',103,  0);
    lkMIObj       := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainobj       ,msg_erp_mimainobj ,'','', 91,  0);
    lkMIView      := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainview      ,msg_erp_mimainview,'','',150,  0);
    lkMIPrint     := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainobjprint_h,msg_erp_mimainobjprint,'','',104,  0);
    lkPanelClient := CreateTxcPanel(Result,Result,obj_name_erp_panelclient,'',alClient,1,1,600,800,xbsNone); 
    lkToolBar     := CreateTxcGradientPanelVistaToolBar(Result,lkPanelClient,obj_name_erp_toolbar,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsNone);
    lkToolBarView := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_view  ,'',alLeft, TERPForm_DefaultToolButtonWidth,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkLBL := CreateTLabel(lkToolBar,lkToolBar,'', lkToolBarView.Left+lkToolBarView.Width+1,1,lkToolBar.Height-2,TERPForm_DefaultToolSeparatorWidth,alLeft,taCenter);
    lkToolBarItem := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_item  ,'',alLeft, lkLBL.Left+lkLBL.Width+1,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkLBL := CreateTLabel(lkToolBar,lkToolBar,'', lkToolBarItem.Left+lkToolBarItem.Width+1,1,lkToolBar.Height-2,TERPForm_DefaultToolSeparatorWidth,alLeft,taCenter);
    lkToolBarExp  := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_export,'',alLeft, lkLBL.Left+lkLBL.Width+1,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkLBL := CreateTLabel(lkToolBar,lkToolBar,'', lkToolBarExp.Left+lkToolBarExp.Width+1,1,lkToolBar.Height-2,TERPForm_DefaultToolSeparatorWidth,alLeft,taCenter);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewrefresh,msg_erp_actviewrefresh,msg_erp_actviewrefresh_hint,SHORTCUT_DATA_REFRESH,0,170,@TERPFormGrid_actViewRefresh_OnExecute,nil                                 ,lkToolBarView,lkMIObj);
    if(erpEvents in aCreateParams)then
      lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewrefreshauto,msg_erp_actviewrefreshauto,msg_erp_actviewrefreshauto_hint,'',0,600,@TERPFormGrid_actViewRefreshAuto_OnExecute,@TERPFormGrid_actViewRefreshAuto_OnUpdate,lkToolBarView,lkMIObj);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewhidden ,msg_erp_actviewhidden ,msg_erp_actviewhidden_hint ,SHORTCUT_DATA_SHOWALL,0, 84,@TERPFormGrid_actViewHidden_OnExecute ,@TERPFormGrid_actViewHidden_OnUpdate,lkToolBarView,lkMIObj);
    if(erpDatePeriod in aCreateParams)then
      begin
      lkPanelDate := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_paneldate,'',alLeft,
        1,1,lkToolBar.Height-2,202+TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle); 
//      lkLBL := CreateTLabel(lkToolBar,lkToolBar,'', lkPanelDate.Left+1,1,lkToolBar.Height-2,TERPForm_DefaultToolSeparatorWidth,alLeft,taCenter);
      lkLBL := CreateTLabel(lkPanelDate,lkPanelDate,msg_erp_lbldatefrom, 1,1,lkPanelDate.Height-2,TERPForm_DefaultToolButtonWidth - 8,alNone,taCenter);
      lkLBL.Font.Size := 10;
      lkLBL.Font.Style:= [fsBold];
      lkDTPDateFrom := CreateTDateTimePicker(Result,lkPanelDate,obj_name_erp_dtpdatefrom,lkLBL.Left+lkLBL.Width+1,1,lkPanelDate.Height-2,80,Now);
      if(erpDatePeriodAutoRefresh in aCreateParams)then
        lkDTPDateFrom.OnCloseUp := @TERPFormGrid_actViewRefresh_OnExecute;
      if TERPFormGrid_DataSetFilter_DateInit then
        lkDTPDateFrom.Date := TERPFormGrid_DataSetFilter_DateFrom;   
      lkLBL := CreateTLabel(lkPanelDate,lkPanelDate,msg_erp_lbldateto, lkDTPDateFrom.Left+lkDTPDateFrom.Width+1,1,lkPanelDate.Height-2,TERPForm_DefaultToolButtonWidth,alNone,taCenter);
      lkLBL.Font.Size := 10;
      lkLBL.Font.Style:= [fsBold];
      lkDTPDateTo   := CreateTDateTimePicker(Result,lkPanelDate,obj_name_erp_dtpdateto ,lkLBL.Left+lkLBL.Width+1,1,lkPanelDate.Height-2,80,Now);
      if(erpDatePeriodAutoRefresh in aCreateParams)then
        lkDTPDateTo.OnCloseUp := @TERPFormGrid_actViewRefresh_OnExecute;
      if TERPFormGrid_DataSetFilter_DateInit then
        lkDTPDateTo.Date := TERPFormGrid_DataSetFilter_DateTo;  
      lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewdate,msg_erp_actviewdate,msg_erp_actviewdate_hint,SHORTCUT_DATA_DATE,0,147,@TERPFormGrid_actViewDate_OnExecute,nil,nil,lkMIObj);
      CreateTxcToolBarButton(lkPanelDate, lkPanelDate, 'tbb'+lkAct.Name, '','', lkDTPDateTo.Left+ lkDTPDateTo.Width+1,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth, alRight, -1, lkAct);
      lkPanelDate.Width := TWinControl_AutoWidth(lkPanelDate) + TERPForm_DefaultControlIndent;   
      end; 
    if(erpPanelLeft in aCreateParams)then
      begin
      lkPanelLeft := CreateTxcPanel(Result,Result,obj_name_erp_panelleft,'',alLeft,1,1,600,200,xbsNone); 
      lkSplt := CreateTSplitter(Result,Result,obj_name_erp_splitterleft,alLeft,lkPanelLeft.Left+lkPanelLeft.Width+1,1,4,4);
      if(erpPanelLeftToolBar in aCreateParams)then
        lkToolBarLeft := CreateTxcGradientPanelVistaToolBar(Result,lkPanelLeft,obj_name_erp_toolbarleft,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth, 200,TERPForm_DefaultToolBarBorderStyle);
      if(erpPanelLeftShowHide in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(Result, obj_name_erp_actviewpanelleft, msg_erp_actviewpanelleft, msg_erp_actviewpanelleft_hint, SHORTCUT_DATA_LEFTBAR,0,18,@TERPFormGrid_actViewPanelLeft_OnExecute, @TERPFormGrid_actViewPanelLeft_OnUpdate, lkToolBarView, lkMIObj);
        if(not(erpPanelLeftVisible in aCreateParams))then
          begin
          lkPanelLeft.Visible := false;
          lkSplt.Visible := false;
          end;    
        if(erpPanelLeftGroup in aCreateParams)then
          lkAct := TERPForm_CreateAction(Result, obj_name_erp_actviewpanelleft+'2', msg_erp_actviewpanelleft2, msg_erp_actviewpanelleft_hint2, '',0,17,@TERPFormGrid_actViewPanelLeft_OnExecute, @TERPFormGrid_actViewPanelLeft2_OnUpdate, lkToolBarView, lkMIObj);
        end;  
      end;  
    CreateTxFBTransDataSet(Result, obj_name_erp_data_trmain, obj_name_erp_data_dtsmain, 'DataSource'+obj_name_erp_data_dtsmain, ['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);  
    with lkDTS do
      begin
      AfterOpen   := @TERPForm_DataSetMain_AfterOpen;
      BeforeClose := @TERPForm_DataSetMain_BeforeClose;
      AfterScroll := @TERPForm_DataSetMain_AfterScroll;
      OnNewRecord := @TERPForm_DataSetMain_OnNewRecord;
      end;    
    if(erpGrid in aCreateParams)then
      begin    
      lkDBG := CreateTDBGridEh(Result,lkPanelClient,lkDS,obj_name_erp_data_dbgmain, 0,100,200,200,alClient);
      with lkDBG do
        begin
        HelpKeyWord := '0';
        with IndicatorTitle do
          begin
          UseGlobalMenu    := true;
          ShowDropDownSign := true;
          TitleButton      := true;
          end;
        Options      := Options   + [dgMultiSelect, dgAlwaysShowSelection];  
        OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghAutoSortMarking, dghMultiSortMarking,  
          dghIncSearch, dghPreferIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, dghExtendVertLines, dghHotTrack];
        EditActions  := [geaSelectAllEh];
        if(erpGridExport in aCreateParams)then
          EditActions:= EditActions + [geaCopyEh];
        SortLocal    := true;
        ShowHint     := true;
        VTitleMargin := 4;
        OnKeyDown    := @TERPFormGrid_DBGrid_OnKeyDown;
        Columns.Clear;
        end; 
      Result.ActiveControl := lkDBG;  
      if(erpGridGroup in aCreateParams)then
        begin    
        TERPForm_Settings(Result).Values[ERP_SETTINGS_DATAMEMORY]:= '1';
        with lkDTS do
          begin
          AfterOpen   := @TERPFormGrid_dtsMain_AfterOpen;
          BeforeClose := @TERPFormGrid_dtsMain_BeforeClose;
          AfterScroll := nil;
          OnNewRecord := nil;
          end;    
        lkDSDrv:= TDataSetDriverEh.Create(Result);
        with lkDSDrv do
          begin
          Name             := 'DataSetDriver'+lkDTS.Name;
          ProviderDataSet  := lkDTS;
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
//          StoreDefs         := true;
          Options          := [mtoTextFieldsCaseInsensitive];
          AfterOpen        := @TERPForm_DataSetMain_AfterOpen;
          BeforeClose      := @TERPForm_DataSetMain_BeforeClose;
          AfterScroll      := @TERPForm_DataSetMain_AfterScroll;
          OnNewRecord      := @TERPForm_DataSetMain_OnNewRecord;
          AfterEdit        := @TERPForm_DataSetMain_AfterEdit;
          end;
        lkDSMT := TDataSource.Create(lkMT);
        with lkDSMT do
          begin
          Name    := 'DataSource'+lkMT.Name;
          DataSet :=  lkMT;
          end; 
        with lkDBG do
          begin
          DataSource := lkDSMT;
          with STFilter do
            begin
            InstantApply := true;
            Local        := true;
            Location     := stflUnderTitleFilterEh;
            Visible      := true;
            end;
          end;
        end;
      ERP_DBGridEh_EdtActions_Create(lkDBG, aCreateParams, lkToolBar, lkMIItem);
      ERP_DBGridEh_StdActions_Create(lkDBG, aCreateParams, lkToolBar, lkMIView);
      if(erpGridPrint in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actprintgrid,msg_erp_actprintgrid,msg_erp_actprintgrid_hint,SHORTCUT_PRINT_ALT,0,239,@TERPFormGrid_actPrintGrid_OnExecute,@TERPFormGrid_actPrintGrid_OnUpdate,lkToolBarExp,lkMIPrint);
        if(erpGridPrintItem in aCreateParams)then
          lkAct := TERPForm_CreateAction(Result,obj_name_erp_actprintitem,msg_erp_actprintitem,msg_erp_actprintitem_hint,SHORTCUT_PRINT,0,105,@TERPFormGrid_actPrintItem_OnExecute,@TERPFormGrid_actPrintGrid_OnUpdate,lkToolBarExp,lkMIPrint);
        end;
      end;
    if(erpEvents in aCreateParams)then
      begin
      lkEvents := TxFBEvents.Create(Result);
      with lkEvents do
        begin
        Name         := obj_name_erp_data_evmain;
        DataBase     := FBDataBase;
        OnEventAlert := @TERPFormGrid_evMain_OnEventAlert;
        Events.Clear;
        end;
      end;  
    if(erpDetail in aCreateParams)then
      begin
      lkSplt := CreateTSplitter(Result,lkPanelClient,obj_name_erp_splitterdetail,alBottom,0,600,4,800);
      lkPCDetail := CreateTxcPageControlEx(Result,lkPanelClient,obj_name_erp_pagecontroldetail,0,600,200,200,alBottom);
      lkPCDetail.OnChange := @TERPFormGrid_PCDetail_OnChange;
      lkAct := TERPForm_CreateAction(Result, obj_name_erp_actviewdetail, msg_erp_actviewdetail, msg_erp_actviewdetail_hint,SHORTCUT_DATA_DETAIL,0,491,@TERPFormGrid_actViewDetail_OnExecute, @TERPFormGrid_actViewDetail_OnUpdate, lkToolBarView, lkMIObj);
      if(not(erpDetailVisible in aCreateParams))then
        begin
        lkPCDetail.Visible := false;
        lkSplt.Visible     := false;       
        end;
      if(erpDetailExternal in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actgriddataextr,msg_erp_actgriddataextr,msg_erp_actgriddataextr_hint,'',0,395,@TERPFormGrid_actViewExternal_OnExecute, @TERPFormGrid_actViewExternal_OnUpdate, lkToolBarView, lkMIObj);
        end;  
      {
      if(erpDetailExtensions in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(Result,obj_name_erp_actgriddataexts,msg_erp_actgriddataexts,msg_erp_actgriddataexts_hint,'',0,398,@TERPFormGrid_actGridDataExts_OnExecute,nil                                     ,lkToolBarView,lkMIObj);
        end;  
      }
      end;
    lkToolBarView.Width := TWinControl_AutoWidth(lkToolBarView)+2; lkToolBarView.Visible:= (lkToolBarView.ControlCount > 0);   
    lkToolBarItem.Width := TWinControl_AutoWidth(lkToolBarItem)+2; lkToolBarItem.Visible:= (lkToolBarItem.ControlCount > 0);  
    lkToolBarExp.Width  := TWinControl_AutoWidth(lkToolBarExp )+2; lkToolBarExp.Visible := (lkToolBarExp.ControlCount  > 0);  
    Amunhotep.MainForm.xcMenu.AddMenu(lkMainMenu); lkMainMenu.OwnerDraw := true;
    Result.Menu := lkMainMenu;
  end;
