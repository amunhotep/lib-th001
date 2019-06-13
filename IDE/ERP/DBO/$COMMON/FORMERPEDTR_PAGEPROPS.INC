{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGEPROPS.INC}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGEPROPS.INC =========
  procedure TERPFormEdtr_PageProps_Create(aOwner:TComponent; aMainPageControl:TxcPageControlEx; aMenuItemMain:TMenuItem; aDataSet:TxFBDataSet; aDataSource:TDataSource);
  var
    lkStr      :string;
    lkAct      :TCustomAction;
    lkPnl      :TxcGradientPanel;
    lkLastTop  :Integer;
    lkLBL      :TLabel;
    lkDBE      :TDBEditEh;
    lkDBNE     :TDBNumberEditEh;
    lkDBCBX    :TDBComboBoxEh;
  begin
    lkPnl     := CreateTxcGradientPanel(aMainPageControl.Pages[0],aMainPageControl.Pages[0],'','',alClient, 0,25,200,200,xbsNone, gdRightToLeft);
    lkPnl.Font.Style := [fsBold];
    lkLastTop := lkLastTop + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_tabletype, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeTYPE_PATH', 'TYPE_PATH', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    with lkDBE do
      begin
      Color    := Amunhotep.MainForm.StyleManager.Colors.Window;
      ReadOnly := true;
      with EditButtons.Add do
        begin
        Visible := true;
        Style   := ebsEllipsisEh;
        OnClick := @TERPFormEdtr_dbeTYPE_PATH_OnEditButtonClick;
        end;
      end;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_tablename, lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner, lkPnl,aDataSource, 'dbeID', 'ID', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;

    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_tablecapt, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeNAME', 'NAME', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_tablecapt2, lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeNAME2', 'NAME2', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;

    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_buffervar, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeBUFFER_VAR', 'BUFFER_VAR', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_genrid, lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeGENR_FLD', 'GENR_FLD', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_genr, lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeGENR', 'GENR', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    if GetField(FBDataBase, 'RDB$GENERATORS', 'TRIM(RDB$GENERATOR_NAME)','', lkStr) then
      with lkDBE.MRUList do
        begin
        Limit      := 100;
        Rows       := 16;
        Items.Text := lkStr;
        Active     := true;
        end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_tree, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBCBX := CreateTDBComboBoxEh(aOwner,lkPnl,aDataSource, 'dbcbxTREE', 'TREE', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    with lkDBCBX do
      begin
      KeyItems.Clear;
      KeyItems.Add('0');
      KeyItems.Add('1');
      Items.Clear;
      Items.Add(msg_erp_objedtr_props_tree_no);
      Items.Add(msg_erp_objedtr_props_tree_yes);
      end;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_treeroot, lkDBCBX.Left+lkDBCBX.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeROOT_PARENT_ID', 'ROOT_PARENT_ID', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_groupbar, lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBCBX := CreateTDBComboBoxEh(aOwner,lkPnl,aDataSource, 'dbcbxFLAG_SHOWGROUPBAR', 'FLAG_SHOWGROUPBAR', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    with lkDBCBX do
      begin
      KeyItems.Clear;
      KeyItems.Add('0');
      KeyItems.Add('1');
      Items.Clear;
      Items.Add(msg_erp_objedtr_props_groupbar_no);
      Items.Add(msg_erp_objedtr_props_groupbar_yes);
      end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;

    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_logins, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBCBX := CreateTDBComboBoxEh(aOwner,lkPnl,aDataSource, 'dbcbxFLAG_LOG_INS', 'FLAG_LOG_INS', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    with lkDBCBX do
      begin
      KeyItems.Clear;
      KeyItems.Add('0');
      KeyItems.Add('1');
      Items.Clear;
      Items.Add(msg_erp_objedtr_props_logins_no);
      Items.Add(msg_erp_objedtr_props_logins_yes);
      end;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_logupd, lkDBCBX.Left+lkDBCBX.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBCBX := CreateTDBComboBoxEh(aOwner,lkPnl,aDataSource, 'dbcbxFLAG_LOG_UPD', 'FLAG_LOG_UPD', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    with lkDBCBX do
      begin
      KeyItems.Clear;
      KeyItems.Add('0');
      KeyItems.Add('1');
      Items.Clear;
      Items.Add(msg_erp_objedtr_props_logupd_no);
      Items.Add(msg_erp_objedtr_props_logupd_yes);
      end;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_logdel, lkDBCBX.Left+lkDBCBX.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBCBX := CreateTDBComboBoxEh(aOwner,lkPnl,aDataSource, 'dbcbxFLAG_LOG_DEL', 'FLAG_LOG_DEL', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, Trunc(TERPFormEdtr_DefaultDBEditWidth / 2));
    with lkDBCBX do
      begin
      KeyItems.Clear;
      KeyItems.Add('0');
      KeyItems.Add('1');
      Items.Clear;
      Items.Add(msg_erp_objedtr_props_logdel_no);
      Items.Add(msg_erp_objedtr_props_logdel_yes);
      end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;

    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_edittype, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBCBX := CreateTDBComboBoxEh(aOwner,lkPnl,aDataSource, 'dbcbxFLAG_EDITINGRID', 'FLAG_EDITINGRID', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, TERPFormEdtr_DefaultDBEditWidth);
    with lkDBCBX do
      begin
      KeyItems.Clear;
      KeyItems.Add('0');
      KeyItems.Add('1');
      Items.Clear;
      Items.Add(msg_erp_objedtr_props_edittypeform);
      Items.Add(msg_erp_objedtr_props_edittypegrid);
      end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_sc, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeSC_REF', 'SC_REF', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, TERPFormEdtr_DefaultDBEditWidth);
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptedit,msg_erp_objedtr_tbbscriptedit,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,26,nil)do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptEdit_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptrun ,msg_erp_objedtr_tbbscriptrun ,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent*2+TERPForm_DefaultEditButtonWidth,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,24,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptRun_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptgen ,msg_erp_objedtr_tbbscriptgen ,lkDBE.Left+lkDBE.Width+(TERPForm_DefaultControlIndent*3)+(TERPForm_DefaultEditButtonWidth*2),lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,19,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptGen_OnClick;
      end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_sc_item, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeSC_ITEM', 'SC_ITEM', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, TERPFormEdtr_DefaultDBEditWidth);
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptedit,msg_erp_objedtr_tbbscriptedit,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,26,nil)do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptEdit_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptrun ,msg_erp_objedtr_tbbscriptrun ,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent*2+TERPForm_DefaultEditButtonWidth,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,24,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptRun_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptgen ,msg_erp_objedtr_tbbscriptgen ,lkDBE.Left+lkDBE.Width+(TERPForm_DefaultControlIndent*3)+(TERPForm_DefaultEditButtonWidth*2),lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,19,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptGen_OnClick;
      end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_scdlg, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeSC_REF_DLG', 'SC_REF_DLG', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, TERPFormEdtr_DefaultDBEditWidth);
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptedit,msg_erp_objedtr_tbbscriptedit,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,26,nil)do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptEdit_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptrun ,msg_erp_objedtr_tbbscriptrun ,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent*2+TERPForm_DefaultEditButtonWidth,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,24,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptRun_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptgen ,msg_erp_objedtr_tbbscriptgen ,lkDBE.Left+lkDBE.Width+(TERPForm_DefaultControlIndent*3)+(TERPForm_DefaultEditButtonWidth*2),lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,19,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptGen_OnClick;
      end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;
      lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_scdlg_width,lkDBE.Left, lkLastTop, TERPForm_DefaultControlHeight, 96,alNone,taLeftJustify);
      lkDBNE:= CreateTDBNumberEditEh(aOwner,lkPnl,aDataSource, 'dbneDLG_WIDTH', 'DLG_WIDTH', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, 60);
      lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_scdlg_height,lkDBNE.Left+lkDBNE.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, 96,alNone,taLeftJustify);
      lkDBNE:= CreateTDBNumberEditEh(aOwner,lkPnl,aDataSource, 'dbneDLG_HEIGHT', 'DLG_HEIGHT', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, 60);
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_sc_itemdlg, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeSC_ITEM_DLG', 'SC_ITEM_DLG', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, TERPFormEdtr_DefaultDBEditWidth);
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptedit,msg_erp_objedtr_tbbscriptedit,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,26,nil)do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptEdit_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptrun ,msg_erp_objedtr_tbbscriptrun ,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent*2+TERPForm_DefaultEditButtonWidth,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,24,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptRun_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptgen ,msg_erp_objedtr_tbbscriptgen ,lkDBE.Left+lkDBE.Width+(TERPForm_DefaultControlIndent*3)+(TERPForm_DefaultEditButtonWidth*2),lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,19,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptGen_OnClick;
      end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(aMainPageControl.Pages[0],lkPnl, msg_erp_objedtr_props_sc_help, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight,TERPFormEdtr_DefaultLabelWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(aOwner,lkPnl,aDataSource, 'dbeHELPFILE', 'HELPFILE', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlHeight, TERPFormEdtr_DefaultDBEditWidth);
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptedit,msg_erp_objedtr_tbbscriptedit,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,26,nil)do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptEdit_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptrun ,msg_erp_objedtr_tbbscriptrun ,lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent*2+TERPForm_DefaultEditButtonWidth,lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,24,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptRun_OnClick;
      end;
    with CreateTxcToolBarButton(lkDBE,lkPnl,'',msg_erp_objedtr_tbbscriptgen ,msg_erp_objedtr_tbbscriptgen ,lkDBE.Left+lkDBE.Width+(TERPForm_DefaultControlIndent*3)+(TERPForm_DefaultEditButtonWidth*2),lkLastTop,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,19,nil) do
      begin
      ShowCaption := true;
      OnClick     := @TERPFormEdtr_tbbScriptGen_OnClick;
      end;
    lkLastTop := lkLastTop + lkLBL.Height + TERPForm_DefaultControlIndent;

    lkAct := TERPForm_CreateAction2(aOwner,obj_name_erp_objedtr_actviewmenu,msg_erp_objedtr_actviewmenu,msg_erp_objedtr_actviewmenu_hint,SHORTCUT_TREE_INSERT ,0,446,@TERPFormEdtr_actViewMenu_OnExecute   ,@TERPFormEdtr_actViewMenu_OnUpdate ,TxcGradientPanel(aMainPageControl.Pages[0].FindComponent(obj_name_erp_toolbar)),TERPForm_DefaultEditButtonWidth,aMenuItemMain.Items[0]);
  end;
