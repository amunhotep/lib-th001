{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_ACTIONS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC}          {$I ./EXTENSIONS.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_ACTIONS.INC}     {$I ./FORMERP_ACTIONS.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_HEADER.INC}  {$I ./FORMERPGRID_HEADER.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADATTRS.INC}       {$I ../REF/FORMREF_LOADATTRS.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCOLUMNS.INC}     {$I ../REF/FORMREF_LOADCOLUMNS.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCHILDS.INC}      {$I ../REF/FORMREF_LOADCHILDS.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/DATEPERIODDLG.INC}          {$I ../OPER/DATEPERIODDLG.INC}       {$ENDIF}
  //=========== PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_ACTIONS.INC ============
  procedure TERPFormGrid_actViewRefresh_OnExecute(Sender :TObject);
  begin
    TERPFormGrid_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormGrid_actViewRefreshAuto_OnExecute(Sender :TObject);
  begin
    with TxFBEvents(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_evmain)) do
      if Registered then
        UnRegisterEvents
       else
        RegisterEvents; 
  end;
  //============================================================================
  procedure TERPFormGrid_actViewRefreshAuto_OnUpdate(Sender :TObject);
  begin
    with TCustomAction(Sender) do
      Checked := TxFBEvents(Owner.FindComponent(obj_name_erp_data_evmain)).Registered;  
  end;
  //============================================================================
  procedure TERPFormGrid_actViewHidden_OnExecute(Sender :TObject);
  var
    lkDBG :TDBGridEh;
  begin
    lkDBG := TERPForm_DBGridMain(TComponent(Sender).Owner);
    if lkDBG.Tag = 0 then lkDBG.Tag := 1 else lkDBG.Tag := 0; 
    TERPFormGrid_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormGrid_actViewHidden_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Checked := (TERPForm_DBGridMain(TComponent(Sender).Owner).Tag = 1);
  end;
  //============================================================================
  procedure TERPFormGrid_actViewDate_OnExecute(Sender :TObject);
  var
    lkDateFrom:TDateTime;
    lkDateTo  :TDateTime;
  begin
    lkDateFrom := TDateTimePicker(TComponent(Sender).Owner.FindComponent(obj_name_erp_dtpdatefrom)).Date;
    lkDateTo   := TDateTimePicker(TComponent(Sender).Owner.FindComponent(obj_name_erp_dtpdateto  )).Date;
    if not Amunhotep_DatePeriodDialog_Execute(lkDateFrom, lkDateTo) then exit;
    TDateTimePicker(TComponent(Sender).Owner.FindComponent(obj_name_erp_dtpdatefrom)).Date := lkDateFrom;
    TDateTimePicker(TComponent(Sender).Owner.FindComponent(obj_name_erp_dtpdateto  )).Date := lkDateTo;
    TERPFormGrid_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormGrid_actViewDetail_OnExecute(Sender :TObject);
  var
    lkPC  :TxcPageControlEx;
    lkSplt:TSplitter;
  begin
    lkPC  := TxcPageControlEx(TComponent(Sender).Owner.FindComponent(obj_name_erp_pagecontroldetail));
    lkSplt:= TSplitter(TComponent(Sender).Owner.FindComponent(obj_name_erp_splitterdetail));
    if((lkPC=nil) or (lkSplt=nil))then exit;
    lkPC.Visible   := not lkPC.Visible;
    lkSplt.Visible := lkPC.Visible; 
    if lkPC.Visible then
      begin
      lkSplt.Top := lkPC.Top - lkSplt.Height;
      TERPFormGrid_PCDetail_OnChange(lkPC);
      TERPForm_DataSetMain_AfterScroll(TERPForm_DBGridMain(TComponent(Sender).Owner).DataSource.DataSet);
      end;
  end;
  //============================================================================
  procedure TERPFormGrid_actViewDetail_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Checked := TxcPageControlEx(TComponent(Sender).Owner.FindComponent(obj_name_erp_pagecontroldetail)).Visible;
  end;
  //============================================================================
  procedure TERPFormGrid_actViewDataDetail_OnExecute(Sender :TObject);
  var
    lkOwner      :TComponent;
    lkToolBar    :TxcGradientPanelVista;
    lkSplt       :TSplitter;
    lkPCDetail   :TxcPageControlEx;
    lkTr         :TxFBTransaction;
    lkQr         :TxFBQuery;
    lkDS         :TDataSource;
    lkAct        :TCustomAction;
  begin
    if(TComponent(Sender).Tag = 1)then exit;
    lkOwner := TComponent(Sender).Owner;
    if(TComponent(Sender).Owner.FindComponent(obj_name_erp_pagecontroldetail) = nil)then
      begin
      lkToolBar := TxcGradientPanelVista(lkOwner.FindComponent(obj_name_erp_toolbar_view));
      lkSplt := CreateTSplitter(lkOwner, TWinControl(lkOwner.FindComponent(obj_name_erp_panelclient)),obj_name_erp_splitterdetail,alBottom,0,600,4,800);
      lkPCDetail := CreateTxcPageControlEx(lkOwner,TWinControl(TComponent(Sender).Owner.FindComponent(obj_name_erp_panelclient)),obj_name_erp_pagecontroldetail,0,600,200,200,alBottom);
      lkPCDetail.OnChange := @TERPFormGrid_PCDetail_OnChange;
      lkAct := TERPForm_CreateAction(lkOwner, obj_name_erp_actviewdetail, msg_erp_actviewdetail, msg_erp_actviewdetail_hint,SHORTCUT_DATA_DETAIL,0,491,
                 @TERPFormGrid_actViewDetail_OnExecute, @TERPFormGrid_actViewDetail_OnUpdate, lkToolBar, nil);
      lkToolBar.Width := TWinControl_AutoWidth(lkToolBar)+2;
      end
     else
      lkPCDetail := TxcPageControlEx(lkOwner.FindComponent(obj_name_erp_pagecontroldetail)); 
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQR, lkDS)  
    lkQr.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_TABLECHILD_REF));
    lkQr.Prepare;
    lkQr.ParamByName('PQ_TB_ID'   ).AsString := TERPForm_ObjId(lkOwner);
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
      Dialogs.MessageDlg(msg_error_erpsql+' "'+TERPForm_ObjId(lkOwner)+'" !',mtWarning,[mbOk]);
      exit;
      end;  
    TERPFormItem_LoadChilds(lkQr, lkOwner, TERPForm_DBGridMain(lkOwner).DataSource, false);
    lkTr.Free;
    if not lkPCDetail.Visible then
      TERPFormGrid_actViewDetail_OnExecute(Sender);
    TComponent(Sender).Tag := 1;
  end;
  //============================================================================
  procedure TERPFormGrid_actViewExternal_OnExecute(Sender :TObject);
  var
    lkOwner   :TComponent;
    lkToolBar :TxcGradientPanelVista;
    lkSplt    :TSplitter;
    lkPCDetail:TxcPageControlEx;
    lkTS      :TxcTabSheet;
    lkAct     :TCustomAction;
  begin
    if(TComponent(Sender).Tag = 1)then exit;
    lkOwner := TComponent(Sender).Owner;
    if(lkOwner.FindComponent(obj_name_erp_pagecontroldetail) = nil)then
      begin
      lkToolBar := TxcGradientPanelVista(lkOwner.FindComponent(obj_name_erp_toolbar_view));
      lkSplt := CreateTSplitter(lkOwner, TWinControl(lkOwner.FindComponent(obj_name_erp_panelclient)),obj_name_erp_splitterdetail,alBottom,0,600,4,800);
      lkPCDetail := CreateTxcPageControlEx(lkOwner,TWinControl(TComponent(Sender).Owner.FindComponent(obj_name_erp_panelclient)),obj_name_erp_pagecontroldetail,0,600,200,200,alBottom);
      lkPCDetail.OnChange := @TERPFormGrid_PCDetail_OnChange;
      lkAct := TERPForm_CreateAction(lkOwner, obj_name_erp_actviewdetail, msg_erp_actviewdetail, msg_erp_actviewdetail_hint,SHORTCUT_DATA_DETAIL,0,491,
                 @TERPFormGrid_actViewDetail_OnExecute, @TERPFormGrid_actViewDetail_OnUpdate, lkToolBar, nil);
      lkToolBar.Width := TWinControl_AutoWidth(lkToolBar) + 2;
      end
     else
      lkPCDetail := TxcPageControlEx(lkOwner.FindComponent(obj_name_erp_pagecontroldetail)); 
    lkTS := CreateTxcTabSheet(lkPCDetail,obj_name_erp_tabsheetexternal, '['+msg_erp_tsexternal+']', TCustomAction(Sender).ImageIndex, $FF0080);
    ERP_ObjectExtension_CallScript(lkOwner, lkTS, TERPForm_DBGridMain(lkOwner).DataSource.DataSet, 'PEAKTOP:IDE/ERP/DBO/OPER/EXTERNAL/DEFAULT_PANEL.PS' );
    TxcPageControlEx_ActivateDefaultPage(lkPCDetail);
    if not lkPCDetail.Visible then
      TERPFormGrid_actViewDetail_OnExecute(Sender);
    TComponent(Sender).Tag := 1;
  end;
  //============================================================================
  procedure TERPFormGrid_actGridDataExts_OnExecute(Sender :TObject);
  var
    lkOwner      :TComponent;
    lkToolBar    :TxcGradientPanelVista;
    lkSplt       :TSplitter;
    lkPCDetail   :TxcPageControlEx;
    lkAct        :TCustomAction;
  begin
    lkOwner := TComponent(Sender).Owner;
    if(TComponent(Sender).Owner.FindComponent(obj_name_erp_pagecontroldetail) = nil)then
      begin
      lkToolBar := TxcGradientPanelVista(lkOwner.FindComponent(obj_name_erp_toolbar_view));
      lkSplt := CreateTSplitter(lkOwner, TWinControl(lkOwner.FindComponent(obj_name_erp_panelclient)),obj_name_erp_splitterdetail,alBottom,0,600,4,800);
      lkPCDetail := CreateTxcPageControlEx(lkOwner,TWinControl(TComponent(Sender).Owner.FindComponent(obj_name_erp_panelclient)),obj_name_erp_pagecontroldetail,0,600,200,200,alBottom);
      lkPCDetail.OnChange := @TERPFormGrid_PCDetail_OnChange;
      lkAct := TERPForm_CreateAction(lkOwner, obj_name_erp_actviewdetail, msg_erp_actviewdetail, msg_erp_actviewdetail_hint,SHORTCUT_DATA_DETAIL,0,491,
                 @TERPFormGrid_actViewDetail_OnExecute, @TERPFormGrid_actViewDetail_OnUpdate, lkToolBar, nil);
      end
     else
      lkPCDetail := TxcPageControlEx(lkOwner.FindComponent(obj_name_erp_pagecontroldetail)); 
    ERP_ObjectExtension_Call(lkOwner, lkPCDetail, TERPForm_DBGridMain(lkOwner).DataSource.DataSet);
    TxcPageControlEx_ActivateDefaultPage(lkPCDetail);
    if not lkPCDetail.Visible then
      TERPFormGrid_actViewDetail_OnExecute(Sender);
    lkToolBar.Width := TWinControl_AutoWidth(lkToolBar)+2;
  end;
  //============================================================================
  procedure TERPFormGrid_actViewExternal_OnUpdate(Sender :TObject);
  begin
    with TCustomAction(Sender) do Enabled := (Tag <> 1);
  end;
  //============================================================================
  procedure TERPFormGrid_actViewPanelLeft_OnExecute(Sender :TObject);
  var
    lkPnl :TxcPanel;
    lkSplt:TSplitter;
  begin
    lkPnl  := TxcPanel(TComponent(Sender).Owner.FindComponent(obj_name_erp_panelleft));
    lkSplt := TSplitter(TComponent(Sender).Owner.FindComponent(obj_name_erp_splitterleft));
    if((lkPnl=nil) or (lkSplt=nil))then exit;
    lkPnl.Visible := not lkPnl.Visible;
    lkSplt.Visible := lkPnl.Visible; 
    if lkPnl.Visible then
      begin
      lkSplt.Left := lkPnl.Left + lkPnl.Width + lkSplt.Width;
      TComponent(Sender).Tag := 0;
      end
     else 
      TComponent(Sender).Tag := 1;
    TERPFormGrid_PanelLeft_OnShowHide(TComponent(Sender).Owner);  
  end;
  //============================================================================
  procedure TERPFormGrid_actViewPanelLeft_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Checked := TxcPanel(TComponent(Sender).Owner.FindComponent(obj_name_erp_panelleft)).Visible;
  end;
  //============================================================================
  procedure TERPFormGrid_actViewPanelLeft2_OnUpdate(Sender :TObject);
  begin
    with TCustomAction(Sender) do
      Checked := (Tag = 1);
  end;
  //============================================================================
  procedure TERPFormGrid_actPrintGrid_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin
    lkEnabled := TERPForm_DBGridMain(TComponent(Sender).Owner).DataSource.DataSet.Active;
    if lkEnabled then lkEnabled := (TERPForm_DBGridMain(TComponent(Sender).Owner).DataSource.DataSet.RecordCount > 0);
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure TERPFormGrid_actPrintGrid_OnExecute(Sender :TObject);
  var
    lkTypeId :Integer;
    lkObjName:string;
  begin
    if TERPFormGrid_PrintGrid(TComponent(Sender).Owner) then exit;
    lkTypeId := StrToInt(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_BASETYPE ]);
    lkObjName:= TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TABLENAME];
    if(lkTypeId = 0)then exit;
    with TERPForm_ActiveDataSet(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if(not(RecordCount>0))then exit;
      SetGlobalVariable(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_BUFFERVAR], FieldByName(ERP_DATASET_DBKEY).AsString);
      if( (lkTypeId = ERP_OBJECTTYPE_DOC) or (lkTypeId = ERP_OBJECTTYPE_JRNL) )then
        lkObjName := TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_DOCTYPE];
      ERP_DBGridEh_Preview(IntToStr(lkTypeId), lkObjName);
      end;
  end;
  //============================================================================
  procedure TERPFormGrid_actPrintItem_OnExecute(Sender :TObject);
  var
    lkTypeId :Integer;
    lkObjName:string;
  begin
    if TERPFormGrid_PrintItem(TComponent(Sender).Owner) then exit;
    lkTypeId := StrToInt(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_BASETYPE ]);
    lkObjName:= TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TABLENAME];
    if(lkTypeId = 0)then exit;
    with TERPForm_ActiveDataSet(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if(not(RecordCount>0))then exit;
      SetGlobalVariable(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_BUFFERVAR], FieldByName(ERP_DATASET_DBKEY).AsString);
      if( (lkTypeId = ERP_OBJECTTYPE_DOC) or (lkTypeId = ERP_OBJECTTYPE_JRNL) )then
        begin
        if(FindField('TYPE_ID') = nil)then 
          begin
          Dialogs.MessageDlg(msg_error_cannotfind_typeofdoc, mtWarning, [mbOk]);
          exit;
          end;
        lkObjName := FieldByName('TYPE_ID').AsString;
        end;
      ERP_DBGridEh_PreviewItem(IntToStr(lkTypeId), lkObjName)
      end;
  end;
  //============================================================================
  procedure TERPFormGrid_actClose_OnExecute(Sender :TObject);
  begin
    TERPForm_GridSettingsSave(TERPForm_DBGridMain(TComponent(Sender).Owner), TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TEMPFILENAME]);
    TERPFormGrid_Destroy(TComponent(Sender).Owner);
    TERPForm_actClose_OnExecute(Sender);
  end;
