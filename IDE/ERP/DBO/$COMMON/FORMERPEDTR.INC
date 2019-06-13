{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                       {$I PEAKTOP:GLOBAL_VARIABLES.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                            {$I PEAKTOP:OBJ/TACTION.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                         {$I PEAKTOP:OBJ/TIMAGELIST.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                          {$I PEAKTOP:OBJ/TCOLUMNEH.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                          {$I PEAKTOP:OBJ/TSPLITTER.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                          {$I PEAKTOP:OBJ/TDBGRIDEH.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                             {$I PEAKTOP:OBJ/TLABEL.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBEDITEH.2.INC}                        {$I PEAKTOP:OBJ/TDBEDITEH.2.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBNUMBEREDITEH.2.INC}                  {$I PEAKTOP:OBJ/TDBNUMBEREDITEH.2.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBCOMBOBOXEH.2.INC}                    {$I PEAKTOP:OBJ/TDBCOMBOBOXEH.2.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                           {$I PEAKTOP:OBJ/TXCPANEL.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                   {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}              {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBAR.INC}                        {$I PEAKTOP:OBJ/TXCGROUPBAR.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                   {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                   {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                        {$I PEAKTOP:OBJ/TXCTABSHEET.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                       {$I PEAKTOP:OBJ/TXFBDATASETS.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/FILENAMES_TEMPLATES.INC}        {$I ../FILENAMES_TEMPLATES.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}      {$I ../USERS/GLOBALVARIABLES.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$I ./FORMERP.INC}                            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC}       {$I ./FORMERP_BLOB.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}       {$I ./FORMERP_LANG.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_NAMES.INC}  {$I ./FORMERPEDTR_NAMES.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_HEADER.INC} {$I ./FORMERPEDTR_HEADER.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_LANG.INC}   {$I ./FORMERPEDTR_LANG.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_ACTIONS.INC}{$I ./FORMERPEDTR_ACTIONS.INC}                {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR.INC ==============
const
  TERPFormEdtr_DefaultLabelWidth  = 128;
  TERPFormEdtr_DefaultDBEditWidth = 400;
  //============================================================================
  procedure TERPFormEdtr_dtsMain_AfterOpen(DataSet :TDataSet);
  var
    i:Integer;
  begin
    for i:=0 to DataSet.ComponentCount-1 do
      if ObjectInheritsFrom(DataSet.Components[i],'TDataSet') then
        with TDataSet(DataSet.Components[i]) do
          if not Active then try Open; except; end;
  end;
  //============================================================================
  procedure TERPFormEdtr_dtsMain_BeforeClose(DataSet :TDataSet);
  var
    i:Integer;
  begin
    for i:=0 to DataSet.ComponentCount-1 do
      if ObjectInheritsFrom(DataSet.Components[i],'TDataSet') then
        with TDataSet(DataSet.Components[i]) do
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
  procedure TERPFormEdtr_dtsMain_AfterScroll(DataSet :TDataSet);
  begin
    with DataSet.Owner do
      TERPForm_SetCaption(Owner, ERP_ObjectCaption(TERPForm_ObjType(Owner))+': "'+DataSet.FieldByName('NAME').AsString+'"');
  end;
  //============================================================================
  procedure TERPFormEdtr_DTSChild_AfterOpen(DataSet :TDataSet);
  begin
    if(DataSet.Tag <> 0)then
      DataSet.RecNo := DataSet.Tag;
    DataSet.Tag := 0;
    TERPFormEdtr_dtsMain_AfterOpen(DataSet);
  end;
  //============================================================================
  procedure TERPFormEdtr_DTSChild_BeforeClose(DataSet :TDataSet);
  begin
    DataSet.Tag := DataSet.RecNo;
    TERPFormEdtr_dtsMain_BeforeClose(DataSet);
  end;
  //============================================================================
  procedure TERPFormEdtr_DTSAttrs_OnNewRecord(DataSet :TDataSet);
  begin
    DataSet.FieldByName('TB_ID' ).AsString := TERPForm_ObjId(DataSet.Owner.Owner.Owner);
  end;
  //=================================================================================
  procedure TERPFormEdtr_DTSAttrsFooters_OnNewRecord(DataSet :TDataSet);
  var 
    lkStr :string;
  begin
    lkStr := '-2';
    GetField(FBDataBase, 'RDB$DATABASE', ' GEN_ID(GENR$_TB_COLS_FOOTERS_ID, 0) ', '', lkStr);
    WriteLn('"'+lkStr+'"');  
    with DataSet do
      begin
      FieldByName('ID'        ).AsInteger := StrToInt(lkStr) + 1;
      FieldByName('TB_ID'     ).AsString  := TDataSet(Owner).FieldByName('TB_ID').AsString;
      FieldByName('TC_ID'     ).AsString  := TDataSet(Owner).FieldByName('ID'   ).AsString;
      FieldByName('NAME'      ).AsString  := 'Кол-во:';
      FieldByName('ALIGNMENT' ).AsInteger := 1;
      FieldByName('FORMAT'    ).AsString  := '# ### ### ##0';
      FieldByName('VALUE_TYPE').AsString  := 'COUNT';
      end;
  end;
  //============================================================================
  procedure TERPFormEdtr_DTSPrint_OnNewRecord(DataSet :TDataSet);
  var 
    lkStr :string;
  begin
    lkStr := '-1';
    if GetField(FBDataBase, 'RDB$DATABASE', 'GEN_ID(GENR$_TB_DOCSRPT_ID, 0)', '', lkStr)then
      lkStr := IntToStr( StrToInt(lkStr) + 1 );
    DataSet.FieldByName('SUBTYPE').AsString := '0';
    DataSet.FieldByName('ID'     ).AsString := lkStr;
    DataSet.FieldByName('NAME'   ).AsString := 'Введите название шаблона печати';
    DataSet.FieldByName('OBJ_ID' ).AsString := TERPForm_ObjId(DataSet.Owner.Owner.Owner);
  end;
  //============================================================================
  procedure TERPFormEdtr_DTSPrintSQL_OnNewRecord(DataSet :TDataSet);
  var 
    lkStr :string;
  begin
    lkStr := '-1';
    if GetField(FBDataBase, 'RDB$DATABASE', 'GEN_ID(GENR$_TB_DOCSRPTSQL_ID, 0)', '', lkStr)then
      lkStr := IntToStr( StrToInt(lkStr) + 1 );
    DataSet.FieldByName('ID'     ).AsString := lkStr;
    DataSet.FieldByName('NAME'   ).AsString := 'qrMain';
    DataSet.FieldByName('PARENT' ).AsString := '';
    DataSet.FieldByName('RPT_ID' ).AsString := TDataSet(DataSet.Owner).FieldByName('ID').AsString;
  end;
  //============================================================================
  procedure TERPFormEdtr_dbgAttrs_OnGetCellParams(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
    if(Column.Tag = 666)then exit;
    if(not(Column.Field.DataSet.Active))then exit;
    if(Column.Field.DataSet.RecordCount = 0)then exit;
    if(UpperCase(Column.FieldName) = 'COLOR')then
      Background := Column.Field.AsInteger
     else 
      Background := Amunhotep.MainForm.StyleManager.Colors.Window;
    case Column.Field.DataSet.FieldByName('IMG_INDX').AsInteger of
      0: aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      1: aFont.Color := $008000FF;
      2: aFont.Color := $00A06000;
      3: aFont.Color := $00C00020;
      4: aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Background;
      5: aFont.Color := $00006020;
      6: aFont.Color := $00804000;
      else aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
    end;
  end;
  //============================================================================
  procedure TERPFormEdtr_dbgLinks_OnGetCellParams(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
    if(Column.Tag = 666)then exit;
    if(not(Column.Field.DataSet.Active))then exit;
    if(Column.Field.DataSet.RecordCount = 0)then exit;
    if(Column.Field.DataSet.FieldByName('TC_FLAG').AsInteger=1)then
      aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Background;
  end;
  //============================================================================
  procedure TERPFormEdtr_dbgAttrs_COLOR_OnEditButtonClick(Sender :TObject; var Handled : Boolean);
  var
    lkColor :TColor;
  begin
    Handled := true;
    with TDBGridEh(TComponent(Sender).Owner.Owner).DataSource.DataSet do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkColor := FieldByName('COLOR').AsInteger;
      if not Dialogs.SelectColor(lkColor) then exit;
      if(State = dsBrowse)then
        Edit;
      FieldByName('COLOR').AsInteger := lkColor;  
      end;   
  end;
  //============================================================================
  procedure TERPFormEdtr_dbeTYPE_PATH_OnEditButtonClick(Sender :TObject; var Handled : Boolean);
  var
    lkTypeId :string;
    lkSQL    :string;
  begin
    Handled := true;
    lkTypeId := TDBEditEh(TComponent(Sender).Owner).DataSource.DataSet.FieldByName('TYPE_ID').AsString;   
    SetGlobalVariable('TYPE_ID', lkTypeId)
    call(PrepareAbsoleteFileName(StrAbsolutePath('../'+ERP_ObjectDir(TERPForm_ObjType(TComponent(Sender).Owner.Owner))+'DIALOGCASEFOLDER.PS',ScriptName)));
    lkTypeId := GetGlobalVariable('TYPE_ID');
    if((UpperCase(lkTypeId) = 'NULL') or (StrTrimAll(lkTypeId) = ''))then exit;
    lkSQL := 'UPDATE TABL$_TB T SET T.TYPE_ID = '''+lkTypeId+''' WHERE (T.ID = '''+TERPForm_ObjId(TComponent(Sender).Owner.Owner)+''')';
    ExecSQL(FBDataBase, lkSQL);
    TERPFormEdtr_RefreshView(TComponent(Sender).Owner.Owner);  
  end;
  {$I ./FORMERPEDTR_PAGEPROPS.INC}
  {$I ./FORMERPEDTR_PAGEATTRS.INC}
  {$I ./FORMERPEDTR_PAGEACCSS.INC}
  {$I ./FORMERPEDTR_PAGEPRINT.INC}
  {$I ./FORMERPEDTR_PAGECHILD.INC}
  {$I ./FORMERPEDTR_PAGEPARNT.INC}
  {$I ./FORMERPEDTR_PAGELINKS.INC}
  //============================================================================
  procedure TERPFormEdtr_actClose_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_CloseDataSets(TComponent(Sender).Owner);
    TComponent(Sender).Owner.Free;
  end;
  //============================================================================
  procedure TERPFormEdtr_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    TERPFormEdtr_CloseDataSets(TComponent(Sender));
    Action := caFree;
  end; 
  //============================================================================
  function TERPFormEdtr_Create(const aObjId:string; const aObjType:Integer):TAmunhotepForm;
  var
    i          :Integer;
    lkMainMenu :TMainMenu;
    lkMIMain   :TMenuItem;
    lkAct      :TCustomAction;
    lkPC       :TxcPageControlEx;
    lkTr       :TxFBTransaction; 
    lkDTS      :TxFBDataSet;
    lkDS       :TDataSource;
  begin
    DontAutoFree;
    Result := TAmunhotepForm(TERPForm_Create(ERP_ObjectCaption(aObjType), ERP_ObjectIcon(aObjType), ERP_ObjectBitmap(aObjType), false, @TERPFormEdtr_OnClose));
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(aObjType);
      Colors.HotTrackBorder := ERP_ObjectColor(aObjType);
      end;  
    lkAct := TCustomAction(Result.FindComponent(obj_name_erp_actclose)); lkAct.OnExecute := @TERPFormEdtr_actClose_OnExecute;
    with TERPForm_Settings(Result) do
      begin
      Values[ERP_SETTINGS_TABLENAME   ] := aObjId;
      Values[ERP_SETTINGS_TABLECAPTION] := '';
      Values[ERP_SETTINGS_TYPESLIST   ] := '';
      Values[ERP_SETTINGS_BASETYPE    ] := IntToStr(aObjType);
      end;
    // data sets
    CreateTxFBTransDataSet(Result, obj_name_erp_data_trmain, obj_name_erp_data_dtsmain, 'DataSource'+obj_name_erp_data_dtsmain, ['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);
    with lkDTS do
      begin
      AfterOpen   := @TERPFormEdtr_dtsMain_AfterOpen;
      BeforeClose := @TERPFormEdtr_dtsMain_BeforeClose;
      AfterScroll := @TERPFormEdtr_dtsMain_AfterScroll;
      end;  
    // main page control
    lkPC := CreateTxcPageControlEx(Result,Result,obj_name_erp_pagecontrol,0,600,200,200,alClient);
    CreateTxcTabSheet(lkPC,'ts'+obj_name_erp_objedtr_props,msg_erp_objedtr_pageprops,148,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPC,'ts'+obj_name_erp_objedtr_attrs,msg_erp_objedtr_pageattrs,402,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPC,'ts'+obj_name_erp_objedtr_accss,msg_erp_objedtr_pageaccss,244,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPC,'ts'+obj_name_erp_objedtr_print,msg_erp_objedtr_pageprint,104,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPC,'ts'+obj_name_erp_objedtr_child,msg_erp_objedtr_pagechild,491,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPC,'ts'+obj_name_erp_objedtr_parnt,msg_erp_objedtr_pageparen, 65,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPC,'ts'+obj_name_erp_objedtr_links,msg_erp_objedtr_pagelinks,445,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    // main menu
    lkMainMenu := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIMain   := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,msg_erp_objedtr_mimain,'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
    for i:=0 to lkPC.PageCount-1 do
      begin
      CreateTMenuItem(lkMIMain,obj_name_erp_mimainmenu+lkPC.Pages[i].Name,lkPC.Pages[i].Caption,'','',lkPC.Pages[i].ImageIndex,0);
      CreateTxcGradientPanelVistaToolBar(lkPC.Pages[i],lkPC.Pages[i],obj_name_erp_toolbar,'',alTop,0,0,24,200,xbsRaized);
      if(i = 0)then
        lkAct := TERPForm_CreateAction2(Result,obj_name_erp_actviewrefresh     ,msg_erp_actviewrefresh     ,msg_erp_actviewrefresh_hint     ,SHORTCUT_DATA_REFRESH,0,170,@TERPFormEdtr_actViewRefresh_OnExecute,nil                                ,TxcGradientPanel(lkPC.Pages[0].FindComponent(obj_name_erp_toolbar)),TERPForm_DefaultEditButtonWidth,lkMIMain.Items[0])
       else
        with CreateTxcToolBarButton3(lkPC.Pages[i].FindComponent(obj_name_erp_toolbar),TWinControl(lkPC.Pages[i].FindComponent(obj_name_erp_toolbar)),lkAct) do
          begin
          ShowCaption := true;
          Width       := TERPForm_DefaultEditButtonWidth;
          end;
      end;
    TERPFormEdtr_PageProps_Create(Result,lkPC,lkMIMain,lkDTS,lkDS);
    TERPFormEdtr_PageAttrs_Create(Result,lkPC,lkMIMain,lkDTS,lkDS);
    TERPFormEdtr_PageAccss_Create(Result,lkPC,lkMIMain,lkDTS,lkDS);
    TERPFormEdtr_PagePrint_Create(Result,lkPC,lkMIMain,lkDTS,lkDS);
    TERPFormEdtr_PageChild_Create(Result,lkPC,lkMIMain,lkDTS,lkDS);
    TERPFormEdtr_PageParnt_Create(Result,lkPC,lkMIMain,lkDTS,lkDS);
    TERPFormEdtr_PageLinks_Create(Result,lkPC,lkMIMain,lkDTS,lkDS);
    Amunhotep.MainForm.xcMenu.AddMenu(lkMainMenu); lkMainMenu.OwnerDraw := true;
    TxcPageControlEx_ActivateDefaultPage(lkPC);
    TERPFormEdtr_RefreshView(Result);
  end;  
