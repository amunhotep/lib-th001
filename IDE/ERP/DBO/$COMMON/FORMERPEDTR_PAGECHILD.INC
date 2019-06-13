{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGECHILD.INC}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGECHILD.INC =========
  procedure TERPFormEdtr_PageChild_Create(aOwner:TComponent; aMainPageControl:TxcPageControlEx; aMenuItemMain:TMenuItem; aDataSet:TxFBDataSet; aDataSource:TDataSource);
  var
    lkAct      :TCustomAction;
    lkDBG      :TDBGridEh;
    lkCol      :TColumnEh;
    lkDTSChild :TxFBDataSet; 
    lkMI       :TMenuItem;
    i          :Integer;
  begin
    lkDTSChild := TxFBDataSet.Create(aDataSet);
    with lkDTSChild do
      begin
      Name            := obj_name_erp_data_dtsdata+obj_name_erp_objedtr_child;
      Transaction     := aDataSet.Transaction;
      DataSource      := aDataSource;
      SelectSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/CHILDS_SEL.SQL')); 
      RefreshSQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/CHILDS_REF.SQL')); 
      ModifySQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/CHILDS_UPD.SQL')); 
      DeleteSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/CHILDS_DEL.SQL'));
      Tag             := 0;
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      end; 
    lkDBG := CreateTDBGridEh(aOwner,aMainPageControl.Pages[4],nil,obj_name_erp_data_dbgdata+obj_name_erp_objedtr_child,0,0,200,200,alClient);
    with lkDBG do
      begin
      DataSource := TDataSource.Create(lkDTSChild);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSChild.Name;
        DataSet := lkDTSChild; 
        end;
      AllowedOperations := [alopUpdateEh, alopDeleteEh];
      RowHeight         := 16;
      Font.Name         := 'Verdana';
      Font.Size         := 7;
      Font.Style        := [fsBold];
      Options      := Options   + [dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      VTitleMargin := 4;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBG,'TB_CHILD_TYPE_ID'  ,'','', 20,taLeftJustify);
    with lkCol do
      begin
      Color    := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      ReadOnly := true;
      KeyList.Clear;
      for i:=ERP_OBJECTTYPE_UNKN to ERP_OBJECTTYPES_COUNT-1 do
        KeyList.Add(IntToStr(i));
      PickList.Text := KeyList.Text;
      ImageList := CreateTImageListConfiguration(lkDBG, 'ilImageListConfig');
      end;
    lkCol := CreateTColumnEh(lkDBG,'TB_CHILD_NAME'     ,'','',200,taLeftJustify);
    with lkCol do
      begin
      Color    := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'TB_CHILD_ID'       ,'','',120,taLeftJustify);
    with lkCol do
      begin
      Color    := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      ReadOnly := true;
      end;
    lkCol := CreateTColumnEh(lkDBG,'INDEX_FIELDS'      ,'','', 60,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'KEY_FIELDS'        ,'','', 60,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'CHILD_TYPE'        ,'','',160,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear   ; PickList.Clear;
      KeyList.Add('0'); PickList.Add('не указано');
      KeyList.Add('1'); PickList.Add('починенный объект');
      KeyList.Add('2'); PickList.Add('детальная часть документа');
      KeyList.Add('3'); PickList.Add('зарезервировано');
      KeyList.Add('4'); PickList.Add('группирующий объект');
      end;
    lkCol := CreateTColumnEh(lkDBG,'FLAG_SHOW'         ,'','', 48,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear   ; PickList.Clear;
      KeyList.Add('0'); PickList.Add('');
      KeyList.Add('1'); PickList.Add('отображать');
      end;
//    lkAct := TERPForm_CreateAction(aOwner,obj_name_erp_objedtr_actaccss_fill    ,msg_erp_actaccss_fill    ,msg_erp_actaccss_fill_hint    ,'',0,412,@TERPFormEdtr_actAccsFill_OnExecute    ,nil,TxcGradientPanel(aMainPageControl.Pages[2].FindComponent(obj_name_erp_toolbar)),aMenuItemMain.Items[2]);
  end;
