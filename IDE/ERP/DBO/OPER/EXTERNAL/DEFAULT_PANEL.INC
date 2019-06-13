{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/EXTERNAL/DEFAULT_PANEL.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}               {$I PEAKTOP:GLOBAL_VARIABLES.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                 {$I PEAKTOP:GLOBAL_OBJECTS.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                  {$I PEAKTOP:OBJ/TCOLUMNEH.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                  {$I PEAKTOP:OBJ/TDBGRIDEH.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}           {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}      {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}           {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}        {$I ../../OBJECTNAMES.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/IMAGELISTCONFIG.INC}    {$I ../../IMAGELISTCONFIG.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}     {$I ../../DBGRID/ACTIONS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC} {$I ../../$COMMON/EXTENSIONS.INC}          {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/$COMMON/EXTERNAL.INC ===================
  procedure TERPForm_ExternalDataSet_AfterClose(DataSet :TDataSet);
  begin
    with TxFBCustomDataSet(DataSet).Transaction do
      if InTransaction then Commit;
  end;
  //============================================================================
  procedure TERPForm_ExternalDataSet_AfterOpen(DataSet :TDataSet);
  begin
    if(DataSet.Tag > 0)then
      begin
      DataSet.RecNo := DataSet.Tag;
      DataSet.Tag   := 0;
      end;
  end;
  //============================================================================
  procedure TERPForm_ExternalDataSet_BeforeClose(DataSet :TDataSet);
  begin
    if(DataSet.RecordCount > 0)then
      DataSet.Tag := DataSet.RecNo;
  end;
  //============================================================================
  procedure TERPForm_CreateExternalInterface(aOwner, aParent, aDataSet :TComponent);
  var
    lkToolBar :TxcGradientPanelVista;
    lkTr      :TxFBTransaction;
    lkQrExtr  :TxFBQuery;
    lkDSExtr  :TDataSource;
    lkDBGExtr :TDBGridEh;
    lkCol     :TColumnEh;
  begin
    DontAutoFree;
    lkTr  := TxFBTransaction.Create(TERPForm_TransactionMain(aOwner));
    with lkTr do
      begin
      Name := TERPForm_TransactionMain(aOwner).Name+'External';
      DefaultDataBase := TERPForm_TransactionMain(aOwner).DefaultDataBase;
      with Params do
        begin
        Clear;
        Add('isc_tpb_read_committed');
        Add('isc_tpb_read');
        Add('isc_tpb_rec_version');
        Add('isc_tpb_nowait');
        end;
      end;
    lkQrExtr   := TxFBQuery.Create(aDataSet);
    with lkQrExtr do
      begin
      Name        := 'qrExternal';//obj_name_erp_data_qrexternal;
      Tag         := 0;
      Transaction := lkTr;
      DataSource  := TDataSource(aDataSet.FindComponent('DataSource'+aDataSet.Name));
      SQL.Text    := 
        'SELECT E.ID, E.NAME, E.FLAG_DELETE, E.FIRM_ID, E.FILIAL_ID, E.TB_ID, E.REC_ID '+SQLCRLF+
        '      ,E.SREC_ID, E.TB_ID_EXTERNAL, E.REC_ID_EXTERNAL, E.SREC_ID_EXTERNAL '+SQLCRLF+
        '      ,(SELECT FIRST 1 FR.NAME FROM TABL$R_FIRMS   FR WHERE (FR.ID = E.FIRM_ID)) AS FIRM_NAME '+SQLCRLF+
        '      ,(SELECT FIRST 1 FL.NAME FROM TABL$R_FILIALS FL WHERE (FL.ID = E.FILIAL_ID)) AS FILIAL_NAME '+SQLCRLF+
        '      ,(SELECT FIRST 1 TB.NAME FROM TABL$_TB TB WHERE (TB.ID = TRIM(E.TB_ID_EXTERNAL))) AS TB_NAME_EXTERNAL '+SQLCRLF+
        '      ,(SELECT FIRST 1 TB.BASE_TYPE_ID FROM TABL$_TB TB WHERE (TB.ID = TRIM(E.TB_ID_EXTERNAL))) AS TB_TYPE_EXTERNAL '+SQLCRLF+
        'FROM   TABL$_EXCHANGE E '+SQLCRLF+
        'WHERE  (E.TB_ID||'''' = '''+TERPForm_ObjId(aOwner)+''') '+SQLCRLF+
        '  AND  (E.SREC_ID = ?'+ERP_DATASET_DBKEY+') '+SQLCRLF+
        'ORDER BY E.FIRM_ID, E.FILIAL_ID ';
      AfterClose := @TERPForm_ExternalDataSet_AfterClose; 
      AfterOpen  := @TERPForm_ExternalDataSet_AfterOpen;
      BeforeClose:= @TERPForm_ExternalDataSet_BeforeClose;
      end;
    lkDSExtr := TDataSource.Create(lkQrExtr);
    with lkDSExtr do
      begin
      Name    := 'DataSource'+lkQrExtr.Name;
      DataSet := lkQrExtr;
      end;
    lkDBGExtr := CreateTDBGridEh(aOwner,TWinControl(aParent),lkDSExtr,'dbgExternal'{obj_name_erp_data_dbgexternal}, 0,100,200,200,alClient);
    with lkDBGExtr do
      begin
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      Options      := Options   + [dgRowSelect, dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghAutoSortMarking, dghMultiSortMarking,  
        dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, dghExtendVertLines];
      EditActions  := [geaSelectAllEh];
      EditActions  := EditActions + [geaCopyEh];
      SortLocal    := true;
      VTitleMargin := 4;
      Columns.Clear;
      end; 
    lkCol := CreateTColumnEh(lkDBGExtr,'ID'              ,'# ### ##0','текущая база|код записи'          , 60,taRightJustify); lkCol.Color := $FFC0FF;
    lkCol := CreateTColumnEh(lkDBGExtr,'FIRM_ID'         ,'# ### ##0','текущая база|фирма учета|код'     , 40,taRightJustify); lkCol.Color := $FFFFC0;
    lkCol := CreateTColumnEh(lkDBGExtr,'FIRM_NAME'       ,''         ,'текущая база|фирма учета|название',180,taLeftJustify ); lkCol.Color := $FFFFC0;
    lkCol := CreateTColumnEh(lkDBGExtr,'FILIAL_ID'       ,'# ### ##0','текущая база|филиал|код'          , 60,taRightJustify);
    lkCol := CreateTColumnEh(lkDBGExtr,'FILIAL_NAME'     ,''         ,'текущая база|филиал|название'     , 96,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBGExtr,'TB_TYPE_EXTERNAL',''         ,'внешняя база|тип'                 , 20,taLeftJustify ); lkCol.Color := $C0FFFF;
    lkCol.ImageList := CreateTImageListConfiguration(lkDBGExtr, 'ilTBTypeExternal');
    lkCol := CreateTColumnEh(lkDBGExtr,'TB_NAME_EXTERNAL',''         ,'внешняя база|название'            ,140,taLeftJustify ); lkCol.Color := $C0FFFF;
    lkCol := CreateTColumnEh(lkDBGExtr,'TB_ID_EXTERNAL'  ,''         ,'внешняя база|таблица'             ,140,taLeftJustify ); lkCol.Color := $C0FFFF;
    lkCol := CreateTColumnEh(lkDBGExtr,'REC_ID_EXTERNAL' ,'# ### ##0','внешняя база|код записи|числовой' , 60,taRightJustify); lkCol.Color := $C0FFFF;
    lkCol := CreateTColumnEh(lkDBGExtr,'SREC_ID_EXTERNAL',''         ,'внешняя база|код записи|строковый', 60,taLeftJustify ); lkCol.Color := $C0FFFF;
    lkCol := CreateTColumnEh(lkDBGExtr,'NAME'            ,''         ,'примечание'                       ,320,taLeftJustify );
    lkToolBar := CreateTxcGradientPanelVistaToolBar(lkDBGExtr,TWinControl(aParent),obj_name_erp_toolbar,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsNone);
    ERP_DBGridEh_StdActions_Create(lkDBGExtr, [erpGrid, erpGridNavigation, erpGridExport], lkToolBar, nil); 
  end;
