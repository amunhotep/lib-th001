{$DEFINE PEAKTOP:IDE/ERP/DATABASE/DLG_SELECT.INC}
{$IFNDEF PEAKTOP:OBJ/TCOMBOBOX.INC}                          {$I PEAKTOP:OBJ/TCOMBOBOX.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                          {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                          {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}              {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                       {$I PEAKTOP:OBJ/TXFBDATASETS.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DATABASE/DLG_FILENAMES.INC}         {$I ./DLG_FILENAMES.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DATABASE/DLG_LANG.INC}              {$I ./DLG_LANG.INC}                          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$I ../DBO/$COMMON/FORMERP.INC}              {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DATABASE/DIALOG_SELECT.INC ==============
  procedure ERP_DataBaseDlgSelect_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caHide;
  end;
  //============================================================================
  function ERP_DataBaseDlgSelect_Create(const aDataBasePath:string):TForm;
  var
    lkPnl     :TxcGradientPanelVista;
    lkLbl     :TLabel;
    lkCbxType :TComboBox;
    lkTr      :TxFBTransaction;
    lkDTS     :TxFBDataSet;
    lkDS      :TDataSource;
    lkDBG     :TDBGridEh;
    lkCol     :TColumnEh;
  begin
    Result := TERPForm_Create(msg_erpdatabasedlg_select, ERP_FILENAME_DATABASE_DOWNLOAD_ICO,ERP_FILENAME_DATABASE_DOWNLOAD_BMP, true, nil);
    TForm_Position_Load(Result, PrepareAbsoleteFileName('TMP:'+ERP_FILENAME_DATABASE_DOWNLOAD_CFG), 520, 880);
    lkPnl := CreateTxcGradientPanelVistaToolBar(Result, Result, obj_name_erp_toolbar, '', alTop, 0,800,TERPForm_DefaultControlHeight+4,200, xbsRaized);
    lkLbl := CreateTLabel(Result,lkPnl,msg_erpdatabasedlg_loadtype+':',TERPForm_DefaultControlIndent,1,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,alNone,taLeftJustify);
    lkCbxType := CreateTComboBox(Result,lkPnl,'', lkLbl.Left+lkLbl.Width+TERPForm_DefaultControlIndent,1,TERPForm_DefaultControlHeight,TERPForm_DefaultEditButtonWidth,msg_erpdatabasedlg_loadtype_local+#13#10+msg_erpdatabasedlg_loadtype_remote,1);
    lkCbxType.Name  := 'cbxType';
    lkCbxType.Style := csDropDownList;
    CreateTxFBTransDataSet(Result, obj_name_erp_data_trmain, obj_name_erp_data_dtsmain, 'DataSource'+obj_name_erp_data_dtsmain, ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);
    with lkDTS do
      begin
      SelectSQL.Text := 'SELECT 0 AS FLAG, R.FLAG_DELETE, R.ID, R.NAME, R.DATABASE_NAME, R.DATABASE_NAME_REMOTE, R.GUID, R.ADDRESS '+
                        'FROM TABL$R_FILIALS R WHERE (R.ID > 0) ORDER BY R.FLAG_DELETE, R.NAME ';
      end;  
    lkDBG := CreateTDBGridEh(Result,Result,lkDS,obj_name_erp_data_dbgmain, 0,100,200,200,alClient);
    with lkDBG do
      begin
      Options      := Options   + [dgRowSelect, dgAlwaysShowSelection] - [dgIndicator];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D,   
        dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, dghExtendVertLines];
      VTitleMargin := 4;
      RowHeight    := 16;
      Columns.Clear;
      end; 
    lkCol := CreateTColumnEh(lkDBG,'FLAG'                ,'','..'                        , 24,taLeftJustify);
    with lkCol do
      begin
      KeyList.Clear; 
      KeyList.Add('0');
      PickList.Text := KeyList.Text;
      ImageList := CreateTImageList(lkDBG,'ilDB',[182]);
      AlwaysShowEditButton := false;
      end;
    with lkCol do
      begin
      Layout := tlCenter;
      end;  
    lkCol := CreateTColumnEh(lkDBG,'NAME'                ,'',msg_erpdatabasedlg_filial_name, 86,taLeftJustify);
    with lkCol do
      begin
      Layout := tlCenter;
      end;  
    lkCol := CreateTColumnEh(lkDBG,'ADDRESS'             ,'','Адрес', 260,taLeftJustify);
    with lkCol do
      begin
      Layout := tlCenter;
      end;  
    lkCol := CreateTColumnEh(lkDBG,'DATABASE_NAME'       ,'',msg_erpdatabase+'|'+msg_erpdatabasedlg_loadtype_local,260,taLeftJustify);
    with lkCol do
      begin
      Layout := tlCenter;
      end;  
    lkCol := CreateTColumnEh(lkDBG,'DATABASE_NAME_REMOTE','',msg_erpdatabase+'|'+msg_erpdatabasedlg_loadtype_remote,460,taLeftJustify);
    with lkCol do
      begin
      Layout := tlCenter;
      end;  
    lkDTS.Open;
  end;
  //============================================================================
  function ERP_DataBaseDlgSelect_Execute(var aDataBasePath:string):Boolean ;
  var
    lkDlg :TForm;
  begin
    lkDlg := ERP_DataBaseDlgSelect_Create(aDataBasePath);
    with lkDlg do
      begin
      Result := (ShowModal = mrOk);
      if Result then
        begin
        if(TComboBox(FindComponent('cbxType')).ItemIndex = 1)then
          aDataBasePath := TERPForm_DataSetMain(lkDlg).FieldByName('DATABASE_NAME_REMOTE').AsString
         else
          aDataBasePath := '127.0.0.1:'+TERPForm_DataSetMain(lkDlg).FieldByName('DATABASE_NAME').AsString;
        end;
      TForm_Position_Save(lkDlg, PrepareAbsoleteFileName('TMP:'+ERP_FILENAME_DATABASE_DOWNLOAD_CFG));
      Destroy;  
      end;
  end;  
