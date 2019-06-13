{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/FORMREF_ACTIONS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID.INC}   {$I ../$COMMON/FORMERPGRID.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/INTERFACE.INC}  {$I ../OPER/LOCAL/INTERFACE.INC} {$ENDIF}
  //================ PEAKTOP:IDE/ERP/DBO/REF/FORMREF_ACTIONS.INC ===============
  procedure TERPFormGridRef_FBTreeView_OnClick(Sender :TObject);
  begin
    TERPFormGrid_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormGridRef_FBTreeView_OnBuildNode(Sender :TObject; StateFieldValue :Variant; var StateImage :Integer);
  begin
    if(TComponent(Sender).Tag = 1)then
      StateImage := 0
     else
      StateImage := Integer(StateFieldValue);
  end;
  //============================================================================
  procedure TERPFormGridRef_FBTreeView_OnDragDrop(Sender, Source: TObject; X, Y: Integer);
  var
    lkMsg :string;
    lkNode:TTreeNode;
  begin  
    if(Source <> TERPForm_DBGridMain(TComponent(Sender).Owner))then exit;
    with TERPForm_DBGridMain(TComponent(Sender).Owner) do
      begin
      lkNode := TxFBTreeView(Sender).GetNodeAt(X, Y);
      lkMsg  := msg_erp_move_item_into+' "'+lkNode.Text+'"  ?';
      if(Dialogs.MessageDlg(lkMsg, mtConfirmation, [mbYes, mbNo]) <> mrYes)then exit;
      TERPFormGrid_UpdateSelectedRecords(TComponent(Sender).Owner, 
        TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_REF_TREEFIELD], TxFBTreeView(Sender).GetIdByNode(lkNode));
      end;
  end;
  //============================================================================
  procedure TERPFormGridRef_FBTreeView_OnDragOver(Sender, Source: TObject; X, Y: Integer;State: TDragState; var Accept: Boolean);
  begin  
    Accept := (Source = TERPForm_DBGridMain(TComponent(Sender).Owner)); 
  end;  
  //============================================================================
  procedure TERPFormGridRef_actGridDataForm_OnExecute(Sender :TObject);
  var
    lkSQLSelect  :string; 
    lkSQLRefresh :string; 
    lkSQLUpdate  :string;  
    lkSQLDelete  :string;
    lkOwner      :TComponent;
    lkToolBar    :TxcGradientPanelVista;
    lkSB         :TScrollBox;
    lkSplt       :TSplitter;
    lkPCDetail   :TxcPageControlEx;
    lkTS         :TxcTabSheet;
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
    lkTS := CreateTxcTabSheet(lkPCDetail,'', '['+msg_erp_tsdocdata+']',TCustomAction(Sender).ImageIndex, Amunhotep.MainForm.StyleManager.Colors.Window);
    lkTS.PageIndex := 0;
    TxcPageControlEx_ActivateDefaultPage(lkPCDetail);
    lkSB := CreateTScrollBox(lkTS,lkTS,obj_name_erp_scrollboxmain,1,1,600,800,alClient);
    lkSB.Color := lkTS.Color;
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQR, lkDS)  
    TERPFormRefItem_LoadAttrs(lkOwner, lkSB, TERPForm_DBGridMain(lkOwner).DataSource, TERPForm_ObjId(lkOwner), lkQr, false, lkSQLSelect, lkSQLRefresh, lkSQLUpdate, lkSQLDelete);
    lkTr.Free;
    if not lkPCDetail.Visible then
      TERPFormGrid_actViewDetail_OnExecute(Sender);
    TComponent(Sender).Tag := 1;
  end;
  //============================================================================
  procedure TERPFormGridRef_actGridDataDetail_OnExecute(Sender :TObject);
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
  procedure TERPFormGridRef_actGridDataForm_OnUpdate(Sender :TObject);
  begin
    with TCustomAction(Sender) do Enabled := (Tag <> 1);
  end;
  //============================================================================
  procedure TERPFormGridRef_actGridDataLocalization_OnExecute(Sender :TObject);
  var
    lkOwner      :TComponent;
    lkToolBar    :TxcGradientPanelVista;
    lkSplt       :TSplitter;
    lkPCDetail   :TxcPageControlEx;
    lkTS         :TxcTabSheet;
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
    lkTS := CreateTxcTabSheet(lkPCDetail,'', msg_erp_tslocal, TCustomAction(Sender).ImageIndex, Amunhotep.MainForm.StyleManager.Colors.Foreground);
    lkTS.PageIndex := 0;
    LocalizationIntf_Create(lkOwner, lkTS, TERPForm_DBGridMain(lkOwner).DataSource, TERPForm_ObjId(lkOwner) );
    TxcPageControlEx_ActivateDefaultPage(lkPCDetail);
    if not lkPCDetail.Visible then
      TERPFormGrid_actViewDetail_OnExecute(Sender);
    TComponent(Sender).Tag := 1;
  end;
  //============================================================================
  procedure TERPFormGridRef_tbbABC_OnClick(Sender :TObject);
  begin
    TERPFormGrid_RefreshView(TComponent(Sender).Owner.Owner);
  end;    
