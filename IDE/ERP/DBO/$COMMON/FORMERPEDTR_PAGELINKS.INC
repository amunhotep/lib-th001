{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGELINKS.INC}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_PAGELINKS.INC =========
  procedure TERPFormEdtr_PageLinks_Create(aOwner:TComponent; aMainPageControl:TxcPageControlEx; aMenuItemMain:TMenuItem; aDataSet:TxFBDataSet; aDataSource:TDataSource);
  var
    i          :Integer;
    lkAct      :TCustomAction;
    lkDBG      :TDBGridEh;
    lkCol      :TColumnEh;
    lkDTSChild :TxFBDataSet; 
  begin
    lkDTSChild := TxFBDataSet.Create(aDataSet);
    with lkDTSChild do
      begin
      Name            := obj_name_erp_data_dtsdata+obj_name_erp_objedtr_links;
      Transaction     := aDataSet.Transaction;
      DataSource      := aDataSource;
      SelectSQL.Text  := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/LINKS_SEL.SQL')); 
      Tag             := 0;
      BeforeClose     := @TERPFormEdtr_DTSChild_BeforeClose; 
      AfterOpen       := @TERPFormEdtr_DTSChild_AfterOpen;
      end; 
    lkDBG := CreateTDBGridEh(aOwner,aMainPageControl.Pages[6],nil,obj_name_erp_data_dbgdata+obj_name_erp_objedtr_links,0,0,200,200,alClient);
    with lkDBG do
      begin
      DataSource := TDataSource.Create(lkDTSChild);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSChild.Name;
        DataSet := lkDTSChild; 
        end;
      AllowedOperations := [];
      Font.Name         := 'Verdana';
      Font.Size         := 7;
      Font.Style        := [fsBold];
      Options           := Options   + [dgAlwaysShowSelection, dgRowSelect];  
      OptionsEh         := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      VTitleMargin      := 4;
      OnGetCellParams   := @TERPFormEdtr_dbgLinks_OnGetCellParams;
      OnDblClick        := @TERPFormEdtr_actLinksObjEdit_OnExecute;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBG,'IMG_INDX','','Объект|тип', 24,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear;
      for i:=ERP_OBJECTTYPE_UNKN to ERP_OBJECTTYPES_COUNT-1 do
        KeyList.Add(IntToStr(i));
      PickList.Text := KeyList.Text;
      ImageList := CreateTImageListConfiguration(lkDBG, 'ilImageListConfig');
      end;
    lkCol := CreateTColumnEh(lkDBG,'NAME'     ,'','Объект|Название'              ,200,taLeftJustify); lkCol.HideDuplicates := true;
    lkCol := CreateTColumnEh(lkDBG,'ID'       ,'','Объект|Имя таблицы'           ,120,taLeftJustify); lkCol.HideDuplicates := true;
    lkCol := CreateTColumnEh(lkDBG,'TC_NAME'  ,'','Аттрибут|Название'            ,140,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'TC_ID'    ,'','Аттрибут|Имя столбца'         , 80,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'TYPE_PATH','','путь к объекту в конфигурации',640,taLeftJustify); lkCol.HideDuplicates := true;
    // attrs actions
    lkAct := TERPForm_CreateAction2(aOwner,obj_name_erp_objedtr_actlinks_objedit,msg_erp_actlinks_objedit,msg_erp_actlinks_objedit_hint,'',0,53,@TERPFormEdtr_actLinksObjEdit_OnExecute,nil,TxcGradientPanel(aMainPageControl.Pages[6].FindComponent(obj_name_erp_toolbar)),TERPForm_DefaultEditButtonWidth,aMenuItemMain.Items[6]);
  end;
