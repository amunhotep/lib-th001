{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/EXTS/COMMON.INC}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                           {$I PEAKTOP:OBJ/TSPLITTER.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                            {$I PEAKTOP:OBJ/TXCPANEL.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                           {$I PEAKTOP:OBJ/TCOLUMNEH.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                           {$I PEAKTOP:OBJ/TDBGRIDEH.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                    {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                        {$I PEAKTOP:OBJ/TXFBDATASETS.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}                 {$I ../../OBJECTNAMES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}              {$I ../../DBGRID/ACTIONS.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC}          {$I ../../$COMMON/EXTENSIONS.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC}        {$I ../../$COMMON/FORMERP_BLOB.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}        {$I ../../$COMMON/FORMERP_LANG.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}             {$I ../../$COMMON/FORMERP.INC}        {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/REF/EXTS/COMMON.INC ==================
type 
  TProcedure_ERPDBGridEh_ColumnsCreate = procedure (aOwner :TComponent; Sender :TDBGridEh);
  //============================================================================
  function TERPFormGridRefExts_PageCreate(aOwner :TComponent; const aSuffix, aCaption:string):TxcTabSheet;
  var 
    lkPC :TxcPageControlEx;
  begin
    lkPC   := TxcPageControlEx(aOwner.FindComponent(obj_name_erp_pagecontroldetail));
    Result := TxcTabSheet.Create(lkPC);
    with Result do
      begin
      Name        := obj_name_erp_tabsheetdata+aSuffix;
      Parent      := lkPC;
      PageControl := lkPC;
      Caption     := aCaption;
      ImageIndex  := ERP_ObjectImageIndex(ERP_OBJECTTYPE_OPER);
      Color       := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      PageIndex   := 0;
      end;
    TxcPageControlEx_ActivateDefaultPage(lkPC);  
  end;
  //============================================================================
  function TERPFormGridRefExts_PageCreateData(aOwner :TComponent; aMasterDataSet :TDataSet; const aSuffix, aCaption, aSelectSQL:string;
            aProc :TProcedure_ERPDBGridEh_ColumnsCreate):TxcTabSheet;
  var 
    lkToolBar    :TxcGradientPanelVista;
    lkDataSet    :TxFBDataSet; 
    lkDataSource :TDataSource; 
    lkDBG        :TDBGridEh;          
  begin
    Result := TERPFormGridRefExts_PageCreate(aOwner, aSuffix, aCaption);
    lkToolBar := CreateTxcGradientPanelVistaToolBar(Result,Result,obj_name_erp_toolbar,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsNone);
    lkDataSet := TxFBDataSet.Create(aMasterDataSet);
    with lkDataSet do
      begin
      Name           := obj_name_erp_data_qrchilds+aSuffix;
      Transaction    := TERPForm_TransactionMain(aOwner);
      DataSource     := TDataSource(aMasterDataSet.FindComponent('DataSource'+aMasterDataSet.Name));
      SelectSQL.Text := aSelectSQL;
      end;
    lkDataSource := TDataSource.Create(lkDataSet);
    with lkDataSource do
      begin
      DataSet := lkDataSet;
      Name    := 'DataSource'+lkDataSet.Name;
      end;
    lkDBG := CreateTDBGridEh(aOwner, Result, lkDataSource, obj_name_erp_data_dbgchilds+aSuffix, 0,0,200,200, alClient);  
    with lkDBG do
      begin
      HelpKeyWord    := '1';
      FooterRowCount := 1;
      FooterColor    := Amunhotep.MainForm.StyleManager.Colors.Foreground or $A0A0A0;
      end;
    if(aProc <> nil)then  
      aProc(aOwner, lkDBG);
    ERP_DBGridEh_StdActions_Create(lkDBG, [erpGrid, erpGridNavigation, erpGridExport], lkToolBar, nil);  
  end;  
