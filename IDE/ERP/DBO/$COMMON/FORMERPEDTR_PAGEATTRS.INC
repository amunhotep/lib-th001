{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGEATTRS.INC}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGEATTRS.INC =========
  procedure TERPFormEdtr_PageAttrs_Create(aOwner:TComponent; aMainPageControl:TxcPageControlEx; aMenuItemMain:TMenuItem; aDataSet:TxFBDataSet; aDataSource:TDataSource);
  var
    lkStr      :string;
    lkAct      :TCustomAction;
    lkPCDetail :TxcPageControlEx;
    lkPCSubDet :TxcPageControlEx;
    lkSplt     :TSplitter; 
    lkDBG      :TDBGridEh;
    lkDBGDetail:TDBGridEh;
    lkCol      :TColumnEh;
    lkDTSChild :TxFBDataSet; 
    lkDTSDetail:TxFBDataSet; 
  begin
    lkDTSChild := TxFBDataSet.Create(aDataSet);
    with lkDTSChild do
      begin
      Name            := obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs;
      Transaction     := aDataSet.Transaction;
      DataSource      := aDataSource;
      SelectSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLUMNS_02_SEL.SQL')); 
      RefreshSQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLUMNS_02_REF.SQL')); 
      InsertSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLUMNS_02_INS.SQL')); 
      ModifySQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLUMNS_02_UPD.SQL')); 
      DeleteSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLUMNS_02_DEL.SQL'));
      Tag             := 0;
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      OnNewRecord     := @TERPFormEdtr_DTSAttrs_OnNewRecord;
      end; 
    lkDBG := CreateTDBGridEh(aOwner,aMainPageControl.Pages[1],nil,obj_name_erp_data_dbgdata+obj_name_erp_objedtr_attrs,0,0,200,200,alClient);
    with lkDBG do
      begin
      DataSource := TDataSource.Create(lkDTSChild);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSChild.Name;
        DataSet := lkDTSChild; 
        end;
      AllowedOperations := [alopInsertEh, alopAppendEh, alopUpdateEh, alopDeleteEh];
      Font.Name         := 'Verdana';
      Font.Size         := 7;
      Font.Style        := [fsBold];
      Options      := Options   + [dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      VTitleMargin := 4;
      OnGetCellParams := @TERPFormEdtr_DBGAttrs_OnGetCellParams;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBG,'IMG_INDX','',msg_erp_objedtr_dbgattrs_imgindex, 24,taLeftJustify);
    with lkCol do
      begin
      Color := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      KeyList.Add('2');
      KeyList.Add('3');
      KeyList.Add('4');
      KeyList.Add('5');
      KeyList.Add('6');
      PickList.Text := KeyList.Text;
      ImageList := CreateTImageList(lkDBG, 'ilImageIndex', [403, 400, 399, 398, 397, 396, 395]);
      ReadOnly  := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'COL_INDEX'  ,'# ### ##0',msg_erp_objedtr_dbgattrs_colindex  , 24,taRightJustify);
    lkCol := CreateTColumnEh(lkDBG,'ROW_INDEX'  ,'# ### ##0',msg_erp_objedtr_dbgattrs_rowindex  , 24,taRightJustify);
    lkCol := CreateTColumnEh(lkDBG,'FLAG_DELETE',''         ,msg_erp_objedtr_dbgattrs_flag      , 32,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgattrs_flag);
      ImageList            := CreateTImageList(lkDBG, 'ilFlag', [Amunhotep.MainForm.ImageListMain.Count-1, 70]);
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'TB_ID'      ,'',msg_erp_objedtr_dbgattrs_tbid     , 96,taLeftJustify); lkCol.Visible := false;
    lkCol := CreateTColumnEh(lkDBG,'ID'         ,'',msg_erp_objedtr_dbgattrs_id       , 96,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'FIELD_TYPE' ,'',msg_erp_objedtr_dbgattrs_fieldtype,120,taLeftJustify);
    with lkCol do
      begin
      lkStr := '';
      if GetField(FBDataBase, 'TABL$_TB','ID','BASE_TYPE_ID=1 ORDER BY ID',lkStr)then
        begin
        KeyList.Text  := lkStr;
        PickList.Text := lkStr;
        AlwaysShowEditButton := true;
        end;
      end;
    lkCol := CreateTColumnEh(lkDBG,'NAME'       ,'',msg_erp_objedtr_dbgattrs_name     ,160,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'HINT'       ,'',msg_erp_objedtr_dbgattrs_hint     ,160,taLeftJustify); lkCol.Visible := false;
    lkCol := CreateTColumnEh(lkDBG,'ORIENTATION','',msg_erp_objedtr_dbgattrs_orient   , 20,taLeftJustify);
    with lkCol do
      begin
      Title.Orientation := tohVertical;
      KeyList.Clear;
      KeyList.Add('1');
      KeyList.Add('0');
      PickList.Clear;
      PickList.Add('X');
      PickList.Add(#$20);
      NotInKeyListIndex := 1;
      CheckBoxes := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'ALIGNMENT' ,''    ,msg_erp_objedtr_dbgattrs_alignment       , 72,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      KeyList.Add('2');
      PickList.Clear;
      PickList.Add(msg_erp_objedtr_dbgattrs_alignment0);
      PickList.Add(msg_erp_objedtr_dbgattrs_alignment1);
      PickList.Add(msg_erp_objedtr_dbgattrs_alignment2);
      ImageList := CreateTImageList(lkDBG, 'ilAlignment', [109,110,108]);
      ShowImageAndText  := true;
      NotInKeyListIndex := 0;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'WIDTH'        ,'# ### ##0',msg_erp_objedtr_dbgattrs_width      , 40,taRightJustify);
    lkCol := CreateTColumnEh(lkDBG,'COLOR'        ,''         ,msg_erp_objedtr_dbgattrs_color      , 72,taRightJustify);
    with lkCol do
      begin
      with EditButtons.Add do
        begin
        Visible := true;
        Style   := ebsEllipsisEh;
        OnClick := @TERPFormEdtr_dbgAttrs_COLOR_OnEditButtonClick;
        end;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'EDT_LEFT'       ,'# ### ##0',msg_erp_objedtr_dbgattrs_left       , 32,taRightJustify);
    lkCol := CreateTColumnEh(lkDBG,'EDT_TOP'        ,'# ### ##0',msg_erp_objedtr_dbgattrs_top        , 32,taRightJustify);
    lkCol := CreateTColumnEh(lkDBG,'FORMAT'         ,''         ,msg_erp_objedtr_dbgattrs_format     ,120,taLeftJustify );
    TERPFormEdtr_FillStandardFormats(lkCol.MRUList.Items); lkCol.MRUList.Active := true;
    lkCol := CreateTColumnEh(lkDBG,'FLAG_UPDDEFAULT',''         ,msg_erp_objedtr_dbgattrs_defaultvalf, 20,taLeftJustify );
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('1');
      KeyList.Add('0');
      PickList.Clear;
      PickList.Add('X');
      PickList.Add(#$20);
      NotInKeyListIndex := 1;
      CheckBoxes := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'DEFAULT_VALUE'  ,''         ,msg_erp_objedtr_dbgattrs_defaultval , 60,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'FLAG_UPDNULL'   ,''         ,msg_erp_objedtr_dbgattrs_nullvalf   , 20,taLeftJustify );
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('1');
      KeyList.Add('0');
      PickList.Clear;
      PickList.Add('X');
      PickList.Add(#$20);
      NotInKeyListIndex := 1;
      CheckBoxes := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'EMPTY_VALUE'    ,''         ,msg_erp_objedtr_dbgattrs_nullval    , 60,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'REF_TABLE'      ,''         ,msg_erp_objedtr_dbgattrs_reftable   ,120,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'REF_FIELD'      ,''         ,msg_erp_objedtr_dbgattrs_reffield   , 80,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'REF_KEYFIELD'   ,''         ,msg_erp_objedtr_dbgattrs_refkeyfield, 80,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'SUBKONTO_FIELD' ,''         ,'Поле счета для субконто'           , 80,taLeftJustify );
    lkPCDetail := CreateTxcPageControlEx(aMainPageControl.Pages[1],aMainPageControl.Pages[1],obj_name_erp_pagecontroldetail,0,600,120,200,alBottom);
    TERPForm_BlobInterface_Create(lkDBG.DataSource,lkPCDetail,msg_erp_objedtr_dbgattrs_hint   ,'HINT'    ,'DOMN$BLOB_TEXT',false);
    CreateTxcTabSheet(lkPCDetail,'',msg_erp_objedtr_dbgattrs_autofill  , 15,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    lkPCSubDet := CreateTxcPageControlEx(lkPCDetail.Pages[1],lkPCDetail.Pages[1],obj_name_erp_pagecontroldetail,0,0,180,200,alClient);
    TERPForm_BlobInterface_Create(lkDBG.DataSource,lkPCSubDet,msg_erp_objedtr_dbgattrs_autofillk,'KEY_LIST' ,'DOMN$BLOB_TEXT',false);
    TERPForm_BlobInterface_Create(lkDBG.DataSource,lkPCSubDet,msg_erp_objedtr_dbgattrs_autofillv,'PICK_LIST','DOMN$BLOB_TEXT',false);
    TERPForm_BlobInterface_Create(lkDBG.DataSource,lkPCDetail,msg_erp_objedtr_dbgattrs_calcsql  ,'CALC_SQL','DOMN$BLOB_SQL' ,false);
    CreateTxcTabSheet(lkPCDetail,'',msg_erp_objedtr_dbgattrs_detfooter ,262,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPCDetail,'',msg_erp_objedtr_dbgattrs_detadd    ,249,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPCDetail,'',msg_erp_objedtr_pageaccss          ,244,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    lkSplt := CreateTSplitter(aMainPageControl.Pages[1],aMainPageControl.Pages[1],obj_name_erp_splitterdetail,alBottom,0,lkPCDetail.Top-4,4,4);
    // attr accs
    CreateTxcGradientPanelVistaToolBar(lkPCDetail.Pages[5],lkPCDetail.Pages[5],obj_name_erp_toolbar,'',alTop,0,0,24,200,xbsRaized);
    lkDTSDetail := TxFBDataSet.Create(lkDTSChild);
    with lkDTSDetail do
      begin
      Name            := obj_name_erp_data_dtschilds+obj_name_erp_objedtr_accss;
      Transaction     := lkDTSChild.Transaction;
      DataSource      := lkDBG.DataSource;
      SelectSQL.Text  := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLULMNSACCSS_SEL.SQL'); 
      RefreshSQL.Text := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLULMNSACCSS_REF.SQL'); 
      ModifySQL.Text  := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLULMNSACCSS_UPD.SQL');      
      Tag             := 0;
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      end; 
    lkDBGDetail := CreateTDBGridEh(aOwner,lkPCDetail.Pages[5],nil,obj_name_erp_data_dbgchilds+obj_name_erp_objedtr_attrs+obj_name_erp_objedtr_accss,0,0,200,200,alClient);
    with lkDBGDetail do
      begin
      DataSource := TDataSource.Create(lkDTSDetail);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSDetail.Name;
        DataSet := lkDTSDetail; 
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

    lkCol := CreateTColumnEh(lkDBGDetail,'IMG_IDX'  ,'',msg_erp_objedtr_dbgaccss_role_idx , 24,taRightJustify);
    with lkCol do
      begin
      KeyList.Clear ; KeyList.Add('0');
      PickList.Clear; PickList.Add('0');
      ImageList := CreateTImageList(lkDBGDetail, 'ilRole', [ERP_ObjectImageIndex(ERP_OBJECTTYPE_ROLE)]);
      ReadOnly  := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'ROLE_ID'  ,'',msg_erp_objedtr_dbgaccss_role_id  , 48,taRightJustify);
    with lkCol do
      begin
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'ROLE_NAME','',msg_erp_objedtr_dbgaccss_role_name,220,taLeftJustify);
    with lkCol do
      begin
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail, 'FLAG_READ','',msg_erp_objedtr_dbgaccss_access+'|'+msg_erp_objedtr_dbgaccss_flag_sel, 80, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgaccss_flag_sel);
      ImageList            := CreateTImageList(lkDBGDetail, 'ilSel', [Amunhotep.MainForm.ImageListMain.Count-1, 103]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail, 'FLAG_WRITE','',msg_erp_objedtr_dbgaccss_access+'|'+msg_erp_objedtr_dbgaccss_flag_upd, 96, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgaccss_flag_upd);
      ImageList        := CreateTImageList(lkDBGDetail, 'ilUpd', [Amunhotep.MainForm.ImageListMain.Count-1, 175]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkDBGDetail.FrozenCols := 3;
    // attrs footers
    CreateTxcGradientPanelVistaToolBar(lkPCDetail.Pages[3],lkPCDetail.Pages[3],obj_name_erp_toolbar,'',alTop,0,0,24,200,xbsRaized);
    lkDTSDetail := TxFBDataSet.Create(lkDTSChild);
    with lkDTSDetail do
      begin
      Name            := obj_name_erp_data_dtschilds+obj_name_erp_objedtr_footers;
      Transaction     := lkDTSChild.Transaction;
      DataSource      := lkDBG.DataSource;
      SelectSQL.Text  :=  
        'SELECT F.TB_ID, F.TC_ID, F.ID, F.NAME, F.FLAG_DELETE, F.ALIGNMENT, F.FORMAT, F.VALUE_TYPE '+SQLCRLF+
        'FROM   TABL$_TB_COLS_FOOTERS F '+SQLCRLF+
        'WHERE  (F.TB_ID = ?TB_ID) '+SQLCRLF+
        '  AND  (F.TC_ID = ?ID) '+SQLCRLF+
        'ORDER BY F.ID ';
      RefreshSQL.Text :=  
        'SELECT FIRST 1 F.TB_ID, F.TC_ID, F.ID, F.NAME, F.FLAG_DELETE, F.ALIGNMENT, F.FORMAT, F.VALUE_TYPE '+SQLCRLF+
        'FROM   TABL$_TB_COLS_FOOTERS F '+SQLCRLF+
        'WHERE  (F.ID = ?ID)';
      InsertSQL.Text  := 'INSERT INTO TABL$_TB_COLS_FOOTERS(TB_ID, TC_ID, ID, NAME, FLAG_DELETE, ALIGNMENT, FORMAT, VALUE_TYPE) '+SQLCRLF+
                         ' VALUES(?TB_ID, ?TC_ID, ?ID, ?NAME, ?FLAG_DELETE, ?ALIGNMENT, ?FORMAT, ?VALUE_TYPE);';         
      ModifySQL.Text  :=       
        'UPDATE TABL$_TB_COLS_FOOTERS FF SET '+SQLCRLF+
        '  FF.NAME        = ?NAME '+SQLCRLF+
        ' ,FF.FLAG_DELETE = ?FLAG_DELETE '+SQLCRLF+
        ' ,FF.ALIGNMENT   = ?ALIGNMENT '+SQLCRLF+
        ' ,FF.FORMAT      = ?FORMAT '+SQLCRLF+
        ' ,FF.VALUE_TYPE  = ?VALUE_TYPE '+SQLCRLF+
        'WHERE (FF.ID = ?ID);';
      DeleteSQL.Text  := 'DELETE FROM TABL$_TB_COLS_FOOTERS T WHERE (T.ID = ?ID)';
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      OnNewRecord     := @TERPFormEdtr_DTSAttrsFooters_OnNewRecord;
      end; 
    lkDBGDetail := CreateTDBGridEh(aOwner,lkPCDetail.Pages[3],nil,obj_name_erp_data_dbgchilds+obj_name_erp_objedtr_attrs+obj_name_erp_objedtr_footers,0,0,200,200,alClient);
    with lkDBGDetail do
      begin
      DataSource := TDataSource.Create(lkDTSDetail);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSDetail.Name;
        DataSet := lkDTSDetail; 
        end;
      AllowedOperations := AllowedOperations + [alopUpdateEh, alopDeleteEh];
      Font.Name         := 'Verdana';
      Font.Size         := 8;
      Font.Style        := [fsBold];
      Options      := Options   + [dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      VTitleMargin := 4;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'ID'  ,'# ### ##0',msg_erp_objedtr_dbgattrsfoot_id  , 80,taRightJustify);
    with lkCol do
      begin
      Color    := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'FLAG_DELETE','',msg_erp_objedtr_dbgattrsfoot_flag  , 40,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      KeyList.Add(' ');
      KeyList.Add(msg_erp_objedtr_dbgattrsfoot_flag);
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail, 'VALUE_TYPE','',msg_erp_objedtr_dbgattrsfoot_type, 96, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('SUM');
      KeyList.Add('AVG');
      KeyList.Add('COUNT');
      KeyList.Add('VALUE');
      KeyList.Add('STATIC');
      PickList.Text := KeyList.Text;
      ImageList            := CreateTImageList(lkDBGDetail, 'ilValueType', [262, 14, 13, 403, 291]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail, 'NAME'     ,'',msg_erp_objedtr_dbgattrsfoot_name ,220, taLeftJustify);
    lkCol := CreateTColumnEh(lkDBGDetail, 'FORMAT'   ,'',msg_erp_objedtr_dbgattrs_format   ,220, taLeftJustify);
    TERPFormEdtr_FillStandardFormats(lkCol.MRUList.Items); lkCol.MRUList.Active := true;
    lkCol := CreateTColumnEh(lkDBGDetail, 'ALIGNMENT','',msg_erp_objedtr_dbgattrs_alignment, 96, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      KeyList.Add('2');
      PickList.Clear;
      PickList.Add(msg_erp_objedtr_dbgattrs_alignment0);
      PickList.Add(msg_erp_objedtr_dbgattrs_alignment1);
      PickList.Add(msg_erp_objedtr_dbgattrs_alignment2);
      ImageList := CreateTImageList(lkDBGDetail, 'ilAlignment', [109,110,108]);
      ShowImageAndText  := true;
      NotInKeyListIndex := 0;
      AlwaysShowEditButton := true;
      end;
    // attrs actions
    lkAct := TERPForm_CreateAction2(aOwner,obj_name_erp_objedtr_actattrs_viewcols  ,msg_erp_actviewcolumns     ,msg_erp_actviewcolumns_hint     ,'',0,190,@TERPFormEdtr_actAttrsViewColumns_OnExecute      ,nil,TxcGradientPanel(aMainPageControl.Pages[1].FindComponent(obj_name_erp_toolbar)),TERPForm_DefaultEditButtonWidth-32,aMenuItemMain.Items[1]);
    lkAct := TERPForm_CreateAction2(aOwner,obj_name_erp_objedtr_actattrs_autodetect,msg_erp_actattrs_autodetect,msg_erp_actattrs_autodetect_hint,'',0,320,@TERPFormEdtr_actAttrsAutoDetect_OnExecute       ,nil,TxcGradientPanel(aMainPageControl.Pages[1].FindComponent(obj_name_erp_toolbar)),TERPForm_DefaultEditButtonWidth   ,aMenuItemMain.Items[1]);
    lkAct := TERPForm_CreateAction2(aOwner,obj_name_erp_objedtr_actattrs_rename    ,msg_erp_actattrs_rename    ,msg_erp_actattrs_rename_hint    ,'',0,393,@TERPFormEdtr_actAttrsRename_OnExecute           ,nil,TxcGradientPanel(aMainPageControl.Pages[1].FindComponent(obj_name_erp_toolbar)),TERPForm_DefaultEditButtonWidth+16,aMenuItemMain.Items[1]);
    // attrs footers actions
    CreateTMenuItem(aMenuItemMain.Items[1], aMenuItemMain.Items[1].Name+'002', '_'+msg_erp_objedtr_dbgattrs_detfooter, '', '',262, 0);
    lkAct := TERPForm_CreateAction2(aOwner,obj_name_erp_objedtr_actattrs_footerins   ,msg_erp_actins          ,msg_erp_actins_hint            ,'',0,301,@TERPFormEdtr_actAttrsFooterIns_OnExecute          ,nil,TxcGradientPanel(lkPCDetail.Pages[3].FindComponent(obj_name_erp_toolbar)),TERPForm_DefaultEditButtonWidth,aMenuItemMain.Items[1]);
    lkAct := TERPForm_CreateAction2(aOwner,obj_name_erp_objedtr_actattrs_footerdel   ,msg_erp_actdel          ,msg_erp_actdel_hint            ,'',0,303,@TERPFormEdtr_actAttrsFooterDel_OnExecute          ,nil,TxcGradientPanel(lkPCDetail.Pages[3].FindComponent(obj_name_erp_toolbar)),TERPForm_DefaultEditButtonWidth,aMenuItemMain.Items[1]);
    // attrs accss actions
    CreateTMenuItem(aMenuItemMain.Items[1], aMenuItemMain.Items[1].Name+'003', '_'+msg_erp_objedtr_pageaccss, '', '',244, 0);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actattrsaccss_roleshr ,msg_erp_actaccss_roleshr ,msg_erp_actaccss_roleshr_hint ,'',0,421,@TERPFormEdtr_actAttrsAccsRoleShr_OnExecute        ,nil,TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[1]);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actattrsaccss_rolervk ,msg_erp_actaccss_rolervk ,msg_erp_actaccss_rolervk_hint ,'',0,422,@TERPFormEdtr_actAttrsAccsRoleRvk_OnExecute        ,nil,TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[1]);
    CreateTMenuItem(aMenuItemMain.Items[1], aMenuItemMain.Items[1].Name+'006', '_'+msg_erp_miaccss_share, '', '',412, 0);
    CreateTLabel(lkPCDetail.Pages[5], TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)), msg_erp_miaccss_share, TWinControl_AutoWidth(TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar))), 0, 24,160, alLeft, taLeftJustify);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actattrsaccss_shareall,msg_erp_actaccss_all,msg_erp_miaccss_share+msg_erp_actaccss_all,'',0,421,@TERPFormEdtr_actAttrsAccsShareAll_OnExecute,nil,TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[1]);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actattrsaccss_sharesel,msg_erp_actaccss_sel,msg_erp_miaccss_share+msg_erp_actaccss_sel,'',0,103,@TERPFormEdtr_actAttrsAccsShareSel_OnExecute,nil,TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[1]);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actattrsaccss_shareupd,msg_erp_actaccss_upd,msg_erp_miaccss_share+msg_erp_actaccss_upd,'',0,175,@TERPFormEdtr_actAttrsAccsShareUpd_OnExecute,nil,TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[1]);
    CreateTMenuItem(aMenuItemMain.Items[1], aMenuItemMain.Items[1].Name+'007', '_'+msg_erp_miaccss_revok, '', '',415, 0);
    CreateTLabel(lkPCDetail.Pages[5], TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)), msg_erp_miaccss_revok, TWinControl_AutoWidth(TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)))-48, 0, 24,160, alLeft, taLeftJustify);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actattrsaccss_revokall,msg_erp_actaccss_all,msg_erp_miaccss_revok+msg_erp_actaccss_all,'',0,422,@TERPFormEdtr_actAttrsAccsRevokAll_OnExecute,nil,TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[1]);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actattrsaccss_revoksel,msg_erp_actaccss_sel,msg_erp_miaccss_revok+msg_erp_actaccss_sel,'',0,103,@TERPFormEdtr_actAttrsAccsRevokSel_OnExecute,nil,TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[1]);
    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actattrsaccss_revokupd,msg_erp_actaccss_upd,msg_erp_miaccss_revok+msg_erp_actaccss_upd,'',0,175,@TERPFormEdtr_actAttrsAccsRevokUpd_OnExecute,nil,TxcGradientPanel(lkPCDetail.Pages[5].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[1]);
  end;
