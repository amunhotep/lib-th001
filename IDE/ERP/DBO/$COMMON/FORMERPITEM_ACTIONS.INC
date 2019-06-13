{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM_ACTIONS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}       {$I ../USERS/GLOBALVARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC}          {$I ./EXTENSIONS.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM_HEADER.INC}  {$I ./FORMERPITEM_HEADER.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}        {$I ./FORMERP_LANG.INC}           {$ENDIF}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM_ACTIONS.INC ===========
  procedure TERPFormItem_actViewRefresh_OnExecute(Sender :TObject);
  begin
    TERPFormItem_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormItem_actClose_OnExecute(Sender :TObject);
  begin
    if(ObjectInheritsFrom(TComponent(Sender).Owner, 'TForm'))then
      begin
      if(TForm(TComponent(Sender).Owner).FormStyle <> fsMDIChild)then
        begin
        TForm(TComponent(Sender).Owner).ModalResult := mrCancel;
        exit;
        end;
      end;      
    TERPFormItem_Destroy(TComponent(Sender).Owner);
    TComponent(Sender).Owner.Free;
  end;
  //============================================================================
  procedure TERPFormItem_PCDetail_OnChange(Sender :TObject);
  begin
  
  end;
  //============================================================================
  procedure TERPFormItem_actViewDetail_OnExecute(Sender :TObject);
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
      TERPFormItem_PCDetail_OnChange(lkPC);
      TERPForm_OpenDataSetsChilds( TERPForm_DataSetMain(TComponent(Sender).Owner) );
      end;
  end;
  //============================================================================
  procedure TERPFormItem_actViewDetail_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Checked := TxcPageControlEx(TComponent(Sender).Owner.FindComponent(obj_name_erp_pagecontroldetail)).Visible;
  end;
  //============================================================================
  procedure TERPFormItem_actViewExternal_OnExecute(Sender :TObject);
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
      //lkPCDetail.OnChange := @TERPFormGrid_PCDetail_OnChange;
      lkAct := TERPForm_CreateAction(lkOwner, obj_name_erp_actviewdetail, msg_erp_actviewdetail, msg_erp_actviewdetail_hint,SHORTCUT_DATA_DETAIL,0,491,
                 @TERPFormItem_actViewDetail_OnExecute, @TERPFormItem_actViewDetail_OnUpdate, lkToolBar, nil);
      lkToolBar.Width := TWinControl_AutoWidth(lkToolBar) + 2;
      end
     else
      lkPCDetail := TxcPageControlEx(lkOwner.FindComponent(obj_name_erp_pagecontroldetail)); 
    lkTS := CreateTxcTabSheet(lkPCDetail,obj_name_erp_tabsheetexternal, '['+msg_erp_tsexternal+']', TCustomAction(Sender).ImageIndex, $FF0080);
    ERP_ObjectExtension_CallScript(lkOwner, lkTS, TERPForm_DataSetMain(lkOwner), 'PEAKTOP:IDE/ERP/DBO/$COMMON/EXTERNAL.PS');
    TxcPageControlEx_ActivateDefaultPage(lkPCDetail);
    if not lkPCDetail.Visible then
      TERPFormItem_actViewDetail_OnExecute(Sender);
    TComponent(Sender).Tag := 1;
  end;
  //============================================================================
  procedure TERPFormItem_actViewExternal_OnUpdate(Sender :TObject);
  begin
    with TCustomAction(Sender) do Enabled := (Tag <> 1);
  end;
  //============================================================================
  procedure TERPFormItem_actCopyToClipBoard_OnExecute(Sender :TObject);
  var
    lkSett :TStrings;
  begin
    lkSett:= TERPForm_Settings(TComponent(Sender).Owner);
    ExecSQL(FBDataBase, 'INSERT INTO TABL$_BUFFER(NAME, USER_ID, OBJ_NAME, OBJ_ID)VALUES('''+
      ERP_ObjectGUID(StrToInt(lkSett.Values[ERP_SETTINGS_BASETYPE]))+''', '''+
      GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''', '''+lkSett.Values[ERP_SETTINGS_TABLENAME]+''', '''+lkSett.Values[ERP_DATASET_DBKEY]+'''); ');   
  end;
  //============================================================================
  procedure TERPFormItem_actEditPost_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin 
    with TERPForm_DataSetMain(TComponent(Sender).Owner) do
      begin
      lkEnabled := Active;
      if lkEnabled then 
        lkEnabled := not(State = dsBrowse);
      end;
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure TERPFormItem_actEditPost_OnExecute(Sender :TObject);
  begin 
    TERPForm_DataSetMain(TComponent(Sender).Owner).Post;
  end;
  //============================================================================
  procedure TERPFormItem_actEditCancel_OnExecute(Sender :TObject);
  begin 
    TERPForm_DataSetMain(TComponent(Sender).Owner).Cancel;
  end;
  //============================================================================
  procedure TERPFormItem_actEditMark_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actmark_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
//    TERPFormGrid_UpdateSelectedRecords(TComponent(Sender).Owner, 'FLAG_DELETE', '1');
  end;
  //============================================================================
  procedure TERPFormItem_actEditUnMark_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actunmark_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
//    TERPFormGrid_UpdateSelectedRecords(TComponent(Sender).Owner, 'FLAG_DELETE', '0');
  end;
  //============================================================================
  procedure TERPFormItem_actEditCommit_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actcommit_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
//    TERPFormGrid_UpdateSelectedRecords(TComponent(Sender).Owner, 'FLAG_COMMIT', '1');
  end;
  //============================================================================
  procedure TERPFormItem_actEditUnCommit_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actuncommit_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
//    TERPFormGrid_UpdateSelectedRecords(TComponent(Sender).Owner, 'FLAG_COMMIT', '0');
  end;
  //============================================================================
  procedure TERPFormItem_actPrintItem_OnUpdate(Sender :TObject);   
  var
    lkEnabled :Boolean;
  begin 
    with TERPForm_DataSetMain(TComponent(Sender).Owner) do
      begin
      lkEnabled := Active;
      if lkEnabled then 
        lkEnabled := (RecordCount > 0);
      end;
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure TERPFormItem_actPrintGridOrItem(aOwner :TComponent; const aDoForItem:Boolean);
  var
    lkTypeId :string;
    lkObjName:string;
    lkResult :Boolean;
  begin
    if aDoForItem then
      lkResult := TERPFormItem_PrintItem(aOwner)
     else
      lkResult := TERPFormItem_PrintGrid(aOwner);  
    if lkResult then exit;
    lkTypeId := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_BASETYPE ];
    lkObjName:= TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME];
    if(lkTypeId = '0')then exit;

    with TERPForm_DataSetMain(aOwner) do
      begin
      if not Active then exit;
      if(not(RecordCount>0))then exit;
      SetGlobalVariable(TERPForm_Settings(aOwner).Values[ERP_SETTINGS_BUFFERVAR], FieldByName(ERP_DATASET_DBKEY).AsString);
      if(lkTypeId = '4')then
        begin
        if(FindField('TYPE_ID') = nil)then 
          begin
          Dialogs.MessageDlg(msg_error_cannotfind_typeofdoc, mtWarning, [mbOk]);
          exit;
          end;
        lkObjName := FieldByName('TYPE_ID').AsString;
        end;
      if aDoForItem then
        ERP_DBGridEh_PreviewItem(lkTypeId, lkObjName)
       else
        ERP_DBGridEh_Preview(lkTypeId, lkObjName);
      end;
  end;  
  //============================================================================
  procedure TERPFormItem_actPrintItem_OnExecute(Sender :TObject);
  begin
    TERPFormItem_actPrintGridOrItem(TComponent(Sender).Owner, true);
  end; 
