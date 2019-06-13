{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/FORMREFITEM_ACTIONS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                       {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$I ../$COMMON/FORMERP.INC}                  {$ENDIF}
  //============ PEAKTOP:IDE/ERP/DBO/REF/FORMREFITEM_ACTIONS.INC ===============
  procedure TERPFormItemRef_actGridDataDetail_OnUpdate(Sender :TObject);
  begin
    with TCustomAction(Sender) do Enabled := (Tag <> 1);
  end;
  //============================================================================
  procedure TERPFormItemRef_actGridDataDetail_OnExecute(Sender :TObject);
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
      lkPCDetail.OnChange := @TERPFormItem_PCDetail_OnChange;
      lkAct := TERPForm_CreateAction(lkOwner, obj_name_erp_actviewdetail, msg_erp_actviewdetail, msg_erp_actviewdetail_hint,SHORTCUT_DATA_DETAIL,0,491,
                 @TERPFormItem_actViewDetail_OnExecute, @TERPFormItem_actViewDetail_OnUpdate, lkToolBar, nil);
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
    TERPFormItem_LoadChilds(lkQr, lkOwner, TDataSource(TERPForm_DataSetMain(lkOwner).FindComponent('DataSource'+TERPForm_DataSetMain(lkOwner).Name)), false);
    lkTr.Free;
    if not lkPCDetail.Visible then
      TERPFormItem_actViewDetail_OnExecute(Sender);
    TComponent(Sender).Tag := 1;
  end;      
