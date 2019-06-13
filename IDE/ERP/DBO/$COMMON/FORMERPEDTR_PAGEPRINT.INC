{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGEPRINT.INC}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGEPRINT.INC =========
  procedure TERPFormEdtr_PagePrint_Create(aOwner:TComponent; aMainPageControl:TxcPageControlEx; aMenuItemMain:TMenuItem; aDataSet:TxFBDataSet; aDataSource:TDataSource);
  var
    lkAct      :TCustomAction;
    lkPCDetail :TxcPageControlEx;
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
      Name            := obj_name_erp_data_dtsdata+obj_name_erp_objedtr_print;
      Transaction     := aDataSet.Transaction;
      DataSource      := aDataSource;
      SelectSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/PRINT_SEL.SQL')); 
      RefreshSQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/PRINT_REF.SQL')); 
      InsertSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/PRINT_INS.SQL')); 
      ModifySQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/PRINT_UPD.SQL')); 
      DeleteSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/PRINT_DEL.SQL'));
      Tag             := 0;
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      OnNewRecord     := @TERPFormEdtr_DTSPrint_OnNewRecord;
      end; 
    lkDBG := CreateTDBGridEh(aOwner,aMainPageControl.Pages[3],nil,obj_name_erp_data_dbgdata+obj_name_erp_objedtr_print,0,0,200,200,alClient);
    with lkDBG do
      begin
      DataSource := TDataSource.Create(lkDTSChild);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSChild.Name;
        DataSet := lkDTSChild; 
        end;
      AllowedOperations := [alopInsertEh, alopAppendEh, alopUpdateEh, alopDeleteEh];
      RowHeight         := 16;
      Font.Name         := 'Verdana';
      Font.Size         := 7;
      Font.Style        := [fsBold];
      Options      := Options   + [dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      VTitleMargin := 4;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBG, 'SUBTYPE','',msg_erp_objedtr_dbgprint_subtype,140, taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(msg_erp_objedtr_dbgprint_subtype0);
      PickList.Add(msg_erp_objedtr_dbgprint_subtype1);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'ORDERID','',msg_erp_objedtr_dbgprint_orderid, 40,taRightJustify);
    with lkCol do
      begin
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'FLAG_DELETE','',msg_erp_objedtr_dbgprint_flag,80,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgprint_flag);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'ID'  ,'',msg_erp_objedtr_dbgprint_id, 60,taRightJustify);
    with lkCol do
      begin
      Color    := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'NAME','',msg_erp_objedtr_dbgprint_name,240,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'PATH','',msg_erp_objedtr_dbgprint_path,440,taLeftJustify);
    lkPCDetail := CreateTxcPageControlEx(aMainPageControl.Pages[3],aMainPageControl.Pages[3],obj_name_erp_pagecontroldetail,0,600,200,200,alBottom);
    TERPForm_BlobInterface_Create(lkDBG.DataSource, lkPCDetail, msg_erp_objedtr_dbgprint_descr, 'DESCR', 'DOMN$BLOB_TEXT', false);
    CreateTxcTabSheet(lkPCDetail,'ts'+obj_name_erp_objedtr_sqlsc,msg_erp_objedtr_page_sqlscripts,290,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    CreateTxcTabSheet(lkPCDetail,'ts'+obj_name_erp_objedtr_accss,msg_erp_objedtr_pageaccss      ,244,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    lkSplt := CreateTSplitter(aMainPageControl.Pages[3],aMainPageControl.Pages[3],obj_name_erp_splitterdetail,alBottom,0,lkPCDetail.Top-4,4,4);
    // rpt accs
    CreateTxcGradientPanelVistaToolBar(lkPCDetail.Pages[2],lkPCDetail.Pages[2],obj_name_erp_toolbar,'',alTop,0,0,24,200,xbsRaized);
    lkDTSDetail := TxFBDataSet.Create(lkDTSChild);
    with lkDTSDetail do
      begin
      Name            := obj_name_erp_data_dtschilds+obj_name_erp_objedtr_accss;
      Transaction     := lkDTSChild.Transaction;
      DataSource      := lkDBG.DataSource;
      SelectSQL.Text  := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/PRINTACCSS_SEL.SQL'); 
      RefreshSQL.Text := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/PRINTACCSS_REF.SQL'); 
      ModifySQL.Text  := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/PRINTACCSS_UPD.SQL'); 
      Tag             := 0;
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      end; 
    lkDBGDetail := CreateTDBGridEh(aOwner,lkPCDetail.Pages[2],nil,obj_name_erp_data_dbgchilds+obj_name_erp_objedtr_accss,0,0,200,200,alClient);
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
    lkCol := CreateTColumnEh(lkDBGDetail,'IMG_IDX'  ,'',msg_erp_objedtr_dbgaccss_role_idx , 20,taRightJustify);
    with lkCol do
      begin
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'ROLE_ID'  ,'',msg_erp_objedtr_dbgaccss_role_id  , 60,taRightJustify);
    with lkCol do
      begin
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'ROLE_NAME','',msg_erp_objedtr_dbgaccss_role_name,400,taLeftJustify);
    with lkCol do
      begin
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'FLAG'     ,'',msg_erp_objedtr_dbgaccss_access  , 80,taLeftJustify );
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgaccss_flag_prn);
      ImageList        := CreateTImageList(lkDBGDetail, 'ilPrn', [Amunhotep.MainForm.ImageListMain.Count-1, 104]);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkDBG.FrozenCols := 3;  

    CreateTxcGradientPanelVistaToolBar(lkPCDetail.Pages[1],lkPCDetail.Pages[1],obj_name_erp_toolbar,'',alTop,0,0,24,200,xbsRaized);
    lkDTSDetail := TxFBDataSet.Create(lkDTSChild);
    with lkDTSDetail do
      begin
      Name            := obj_name_erp_data_dtschilds+obj_name_erp_objedtr_sqlsc;
      Transaction     := lkDTSChild.Transaction;
      DataSource      := lkDBG.DataSource;
      SelectSQL.Text  := 'SELECT T.RPT_ID, T.ID, T.NAME, T.PARENT, T.FLAG_DELETE, T.ORDERID, T.PATH FROM TABL$_TB_DOCSRPTSQL T WHERE (T.RPT_ID = ?ID) ORDER BY T.ORDERID'; 
      RefreshSQL.Text := 'SELECT FIRST 1 T.RPT_ID, T.ID, T.NAME, T.PARENT, T.FLAG_DELETE, T.ORDERID, T.PATH FROM TABL$_TB_DOCSRPTSQL T WHERE (T.ID = ?ID) ORDER BY T.ORDERID '; 
      InsertSQL.Text  := 'INSERT INTO TABL$_TB_DOCSRPTSQL (RPT_ID,ID,NAME,PARENT,FLAG_DELETE,ORDERID,PATH) '+SQLCRLF+
                         '  VALUES(?RPT_ID,?ID,?NAME,?PARENT,?FLAG_DELETE,?ORDERID,?PATH);'; 
      ModifySQL.Text  := 'UPDATE TABL$_TB_DOCSRPTSQL SET '+SQLCRLF+'   NAME        = ?NAME '+SQLCRLF+'  ,PARENT      = ?PARENT '+SQLCRLF+
                         '  ,FLAG_DELETE = ?FLAG_DELETE '+SQLCRLF+'  ,ORDERID     = ?ORDERID '+SQLCRLF+'  ,PATH        = ?PATH '+SQLCRLF+'WHERE (ID = ?ID);';
      DeleteSQL.Text  := 'DELETE FROM TABL$_TB_DOCSRPTSQL T WHERE (T.ID = ?ID)';
      Tag             := 0;
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      OnNewRecord     := @TERPFormEdtr_DTSPrintSQL_OnNewRecord;
      end; 
    lkDBGDetail := CreateTDBGridEh(aOwner,lkPCDetail.Pages[1],nil,obj_name_erp_data_dbgchilds+obj_name_erp_objedtr_sqlsc,0,0,200,200,alClient);
    with lkDBGDetail do
      begin
      DataSource := TDataSource.Create(lkDTSDetail);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSDetail.Name;
        DataSet := lkDTSDetail; 
        end;
      AllowedOperations := [alopInsertEh, alopAppendEh, alopUpdateEh, alopDeleteEh];
      RowHeight         := 16;
      Font.Name         := 'Verdana';
      Font.Size         := 7;
      Font.Style        := [fsBold];
      Options      := Options   + [dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      VTitleMargin := 4;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'ORDERID','',msg_erp_objedtr_dbgprintsql_orderid, 40,taRightJustify);
    with lkCol do
      begin
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'FLAG_DELETE','',msg_erp_objedtr_dbgprintsql_flag,80,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      KeyList.Add('0');
      KeyList.Add('1');
      PickList.Clear;
      PickList.Add(#$20);
      PickList.Add(msg_erp_objedtr_dbgprintsql_flag);
      ShowImageAndText     := true;
      AlwaysShowEditButton := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'ID'    ,'',msg_erp_objedtr_dbgprintsql_id   , 60,taRightJustify);
    with lkCol do
      begin
      Color    := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBGDetail,'NAME'  ,'',msg_erp_objedtr_dbgprintsql_name  , 96,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBGDetail,'PARENT','',msg_erp_objedtr_dbgprintsql_parent, 96,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBGDetail,'PATH'  ,'',msg_erp_objedtr_dbgprintsql_path  ,440,taLeftJustify);
  end;
