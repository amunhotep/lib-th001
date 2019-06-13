{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGEACCSS.INC}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGEACCSS.INC =========
  procedure TERPFormEdtr_PageAccss_Create(aOwner:TComponent; aMainPageControl:TxcPageControlEx; aMenuItemMain:TMenuItem; aDataSet:TxFBDataSet; aDataSource:TDataSource);
  var
    lkAct      :TCustomAction;
    lkDBG      :TDBGridEh;
    lkCol      :TColumnEh;
    lkDTSChild :TxFBDataSet; 
    lkMI       :TMenuItem;
  begin
    lkDTSChild := TxFBDataSet.Create(aDataSet);
    with lkDTSChild do
      begin
      Name            := obj_name_erp_data_dtsdata+obj_name_erp_objedtr_accss;
      Transaction     := aDataSet.Transaction;
      DataSource      := aDataSource;
      SelectSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/ACCESS_SEL.SQL')); 
      RefreshSQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/ACCESS_REF.SQL')); 
      ModifySQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/ACCESS_UPD.SQL')); 
      Tag             := 0;
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      end; 
    lkDBG := CreateTDBGridEh(aOwner,aMainPageControl.Pages[2],nil,obj_name_erp_data_dbgdata+obj_name_erp_objedtr_accss,0,0,200,200,alClient);
    with lkDBG do
      begin
      DataSource := TDataSource.Create(lkDTSChild);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSChild.Name;
        DataSet := lkDTSChild; 
        end;
      AllowedOperations := [alopUpdateEh];
      RowHeight         := 16;
      Font.Name         := 'Verdana';
      Font.Size         := 7;
      Font.Style        := [fsBold];
      Options      := Options   + [dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      VTitleMargin := 4;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBG,'IMGIDX'   ,'',msg_erp_objedtr_dbgaccss_role_id  , 20,taRightJustify);
    with lkCol do
      begin
      ReadOnly := true;
      KeyList.Clear;  KeyList.Add('0');
      PickList.Clear; PickList.Add(#$20);
      ImageList := CreateTImageList(lkDBG, 'ilRole', [ERP_ObjectImageIndex(ERP_OBJECTTYPE_ROLE)]);
      end;
    lkCol := CreateTColumnEh(lkDBG,'ROLE_ID'  ,'',msg_erp_objedtr_dbgaccss_role_id  , 48,taRightJustify);
    with lkCol do
      begin
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'ROLE_NAME','',msg_erp_objedtr_dbgaccss_role_name,240,taLeftJustify);
    with lkCol do
      begin
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBG, 'FLAG_SEL','',msg_erp_objedtr_dbgaccss_access+'|'+msg_erp_objedtr_dbgaccss_flag_sel, 80, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgaccss_flag_sel);
      ImageList            := CreateTImageList(lkDBG, 'ilSel', [Amunhotep.MainForm.ImageListMain.Count-1, 103]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG, 'FLAG_INS','',msg_erp_objedtr_dbgaccss_access+'|'+msg_erp_objedtr_dbgaccss_flag_ins, 96, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgaccss_flag_ins);
      ImageList        := CreateTImageList(lkDBG, 'ilIns', [Amunhotep.MainForm.ImageListMain.Count-1, 176]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG, 'FLAG_UPD','',msg_erp_objedtr_dbgaccss_access+'|'+msg_erp_objedtr_dbgaccss_flag_upd, 96, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgaccss_flag_upd);
      ImageList        := CreateTImageList(lkDBG, 'ilUpd', [Amunhotep.MainForm.ImageListMain.Count-1, 175]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG, 'FLAG_DEL','',msg_erp_objedtr_dbgaccss_access+'|'+msg_erp_objedtr_dbgaccss_flag_del, 96, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgaccss_flag_del);
      ImageList        := CreateTImageList(lkDBG, 'ilDel', [Amunhotep.MainForm.ImageListMain.Count-1, 177]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG, 'FLAG_PRINT','',msg_erp_objedtr_dbgaccss_access+'|'+msg_erp_objedtr_dbgaccss_flag_prn, 80, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgaccss_flag_prn);
      ImageList        := CreateTImageList(lkDBG, 'ilPrn', [Amunhotep.MainForm.ImageListMain.Count-1, 104]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkDBG.FrozenCols := 3;  
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_roleshr ,msg_erp_actaccss_roleshr ,msg_erp_actaccss_roleshr_hint ,'',0,421,@TERPFormEdtr_actAccsRoleShr_OnExecute ,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[2]);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_rolervk ,msg_erp_actaccss_rolervk ,msg_erp_actaccss_rolervk_hint ,'',0,422,@TERPFormEdtr_actAccsRoleRvk_OnExecute ,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[2]);
    CreateTMenuItem(aMenuItemMain.Items[2], aMenuItemMain.Items[2].Name+'002', '-', '', '',-1, 0);
    lkMI := CreateTMenuItem(aMenuItemMain.Items[2], aMenuItemMain.Items[2].Name+'003', msg_erp_miaccss_share, '', '',412, 0);
    CreateTLabel(aMainPageControl.Pages[2], TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)), msg_erp_miaccss_share, TWinControl_AutoWidth(TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar))), 0, 24,160, alLeft, taLeftJustify);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_shareall,msg_erp_actaccss_all,msg_erp_miaccss_share+msg_erp_actaccss_all,'',0,421,@TERPFormEdtr_actAccsShareAll_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_sharesel,msg_erp_actaccss_sel,msg_erp_miaccss_share+msg_erp_actaccss_sel,'',0,103,@TERPFormEdtr_actAccsShareSel_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_shareins,msg_erp_actaccss_ins,msg_erp_miaccss_share+msg_erp_actaccss_ins,'',0,176,@TERPFormEdtr_actAccsShareIns_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_shareupd,msg_erp_actaccss_upd,msg_erp_miaccss_share+msg_erp_actaccss_upd,'',0,175,@TERPFormEdtr_actAccsShareUpd_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_sharedel,msg_erp_actaccss_del,msg_erp_miaccss_share+msg_erp_actaccss_del,'',0,177,@TERPFormEdtr_actAccsShareDel_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_shareprn,msg_erp_actaccss_prn,msg_erp_miaccss_share+msg_erp_actaccss_prn,'',0,104,@TERPFormEdtr_actAccsSharePrn_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkMI := CreateTMenuItem(aMenuItemMain.Items[2], aMenuItemMain.Items[2].Name+'004', msg_erp_miaccss_revok, '', '',415, 0);
    CreateTLabel(aMainPageControl.Pages[2], TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)), msg_erp_miaccss_revok, TWinControl_AutoWidth(TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar))), 0, 24,160, alLeft, taLeftJustify);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_revokall,msg_erp_actaccss_all,msg_erp_miaccss_revok+msg_erp_actaccss_all,'',0,422,@TERPFormEdtr_actAccsRevokAll_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_revoksel,msg_erp_actaccss_sel,msg_erp_miaccss_revok+msg_erp_actaccss_sel,'',0,103,@TERPFormEdtr_actAccsRevokSel_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_revokins,msg_erp_actaccss_ins,msg_erp_miaccss_revok+msg_erp_actaccss_ins,'',0,176,@TERPFormEdtr_actAccsRevokIns_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_revokupd,msg_erp_actaccss_upd,msg_erp_miaccss_revok+msg_erp_actaccss_upd,'',0,175,@TERPFormEdtr_actAccsRevokUpd_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_revokdel,msg_erp_actaccss_del,msg_erp_miaccss_revok+msg_erp_actaccss_del,'',0,177,@TERPFormEdtr_actAccsRevokDel_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_revokprn,msg_erp_actaccss_prn,msg_erp_miaccss_revok+msg_erp_actaccss_prn,'',0,104,@TERPFormEdtr_actAccsRevokPrn_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),lkMI);
  end;
