{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/DATAVIEW.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                        {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                          {$I PEAKTOP:GLOBAL_OBJECTS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                           {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                           {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                    {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                         {$I PEAKTOP:OBJ/TXCTABSHEET.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}               {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}                 {$I ../OBJECTNAMES.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC}         {$I ../DBGRID/FOOTERS_LOAD.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}              {$I ../DBGRID/ACTIONS.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}       {$I ../USERS/GLOBALVARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}       {$I ../$COMMON/FORMERP_NAMES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/DATAVIEW_GLOBALVARIABLES.INC}{$I ./DATAVIEW_GLOBALVARIABLES.INC}          {$ENDIF}
  //=================== PEAKTOP:IDE/ERP/DBO/DOC/DATAVIEW.INC ===================
  procedure DocDataIntf_Create(aOwner:TComponent; aParent :TWinControl; const aMasterTableName:string;aMasterTransaction:TxFBTransaction; aMasterDataSource:TDataSource; aQr:TxFBQuery);
  var
    lkPCData     :TxcPageControlEx;
    lkToolBar    :TxcGradientPanelVista;
    lkQrDet      :TxFBQuery;
    i, lkCounter :Integer;
    lkTS         :TxcTabSheet;
    lkQr         :TxFBQuery;
    lkDSQR       :TDataSource;
    lkDBG        :TDBGridEh;
    lkCol        :TColumnEh;
    lkS          :string;
    lkSQLFldName :string;
    lkSQLFields  :string;
    lkSQLTables  :string;
    lkSQLWhere   :string;
  begin
    DontAutoFree;
    lkPCData:= CreateTxcPageControlEx(aOwner,aParent,obj_name_erp_pagecontroldata,0,0,200,240,alClient);
    lkQrDet := TxFBQuery.Create(aQr);
    with lkQrDet do
      begin
      Transaction := aQr.Transaction;
      end;
    aQr.FetchAll;
    i := 0;  
    aQr.First;
    while not aQr.EOF do
      begin
      lkTS  := CreateTxcTabSheet(lkPCData, obj_name_erp_tabsheetdata+FormatFloat(ERP_SQL_FIELDFORMAT,i),aQr.FieldByname('TB_NAME').AsString, 491, Amunhotep.MainForm.StyleManager.Colors.Foreground);
      lkQr := TxFBQuery.Create(aMasterDataSource.DataSet);
      with lkQr do
        begin
        Name        := obj_name_erp_data_qrdata+FormatFloat(ERP_SQL_FIELDFORMAT, i);
        Transaction := aMasterTransaction;
        DataSource  := aMasterDataSource;
        SQL.Text    := '';
        end;
      lkDSQR := TDataSource.Create(lkQr);
      with lkDSQR do
        begin
        Name    := 'DataSource'+lkQr.Name;
        DataSet := lkQr;
        end;
      lkDBG := CreateTDBGridEh(aOwner,lkTS,lkDSQR,obj_name_erp_data_dbgdata+FormatFloat(ERP_SQL_FIELDFORMAT, i),0,0,200,200,alClient);
      with lkDBG do
        begin
        Name         := obj_name_erp_data_dbgdata+FormatFloat(ERP_SQL_FIELDFORMAT, i);
        Options      := [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgAlwaysShowSelection];
        OptionsEh    := [dghFixed3D, dghFrozen3D, dghFooter3D, dghAutoSortMarking, dghMultiSortMarking, dghIncSearch, dghRowHighlight, dghColumnResize, dghColumnMove,dghExtendVertLines];
        ReadOnly     := true;
        VTitleMargin := 2;
        UseMultiTitle:= true;
        end; 
      lkToolBar := CreateTxcGradientPanelVistaToolBar(lkDBG, lkDBG.Parent,lkDBG.Name+'_'+obj_name_erp_toolbar,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsRaized);
      ERP_DBGridEh_StdActions_Create(lkDBG, [erpGrid, erpGridNavigation, erpGridExport], lkToolBar, nil);
      lkSQLTables := aQr.FieldByName('TB_ID').AsString+' '+ERP_SQL_DETAILPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i);  
      lkSQLFields := '';
      lkSQLWhere  := '';
      if lkQrDet.Active then 
        lkQrDet.Close;
      lkQrDet.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETCOLUMNS_DOC));
      lkQrDet.Prepare;
      lkQrDet.ParamByName('PQ_TB_ID'   ).AsString := aQr.FieldByname('TB_ID').AsString;  
      lkQrDet.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;  
      lkQrDet.Open;
      lkQrDet.First;
      lkCounter := 0;
      while not lkQrDet.EOF do
        begin
        if( (StrTrimAll(lkQrDet.FieldByName('ID').AsString) = StrTrimAll(lkQrDet.FieldByName('REF_KEYFIELD').AsString)) and 
            (StrTrimAll(lkQrDet.FieldByName('REF_TABLE').AsString) = aMasterTableName) )then
          begin
          lkSQLFields := ERP_SQL_DETAILPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+lkQrDet.FieldByName('ID').AsString+' AS '+ERP_DATASET_DBKEY+lkSQLFields;
          lkSQLWhere  := 'WHERE ('+ERP_SQL_DETAILPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT,i)+'.'+lkQrDet.FieldByName('ID').AsString+' = ?'+ERP_DATASET_DBKEY+') '+SQLCRLF;
          lkCounter := lkCounter + 1;
          lkQrDet.Next;
          continue;
          end;
        if(lkQrDet.FieldByName('CALC_SQL').AsString <> '')then
          begin
          lkS := lkQrDet.FieldByName('CALC_SQL').AsString;
          if(Pos('?', lkS) > 0)then
            lkS := StrReplaceStr(lkS, '?', ERP_SQL_DETAILPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.');  
          lkSQLFields := lkSQLFields + SQLCRLF + '      ,('+lkS+') AS '+lkQrDet.FieldByName('ID').AsString;
          end
         else
          begin 
          lkSQLFldName := ERP_SQL_DETAILPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+lkQrDet.FieldByName('ID').AsString;
          lkSQLFields  := lkSQLFields + SQLCRLF + '      ,'+ lkSQLFldName;
          if(lkQrDet.FieldByName('REF_TABLE').AsString <> '')then
            begin
            lkCounter := lkCounter + 1;
            lkS := lkQrDet.FieldByName('REF_TABLE').AsString;
            if(Pos('?', lkS) > 0)then // stored procedure
              lkS := StrReplaceStr(lkS, '?', #$20+ERP_SQL_DETAILPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.');
            lkS := '(SELECT FIRST 1 '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, lkCounter)+'.'+lkQrDet.FieldByName('REF_FIELD').AsString+
              ' FROM '+lkS+' '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, lkCounter);
            if(lkQrDet.FieldByName('REF_KEYFIELD').AsString <> '')then  
              lkS := lkS +' WHERE ('+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, lkCounter)+'.'+lkQrDet.FieldByName('REF_KEYFIELD').AsString+' = '+lkSQLFldName+')';
            lkS := lkS +') AS '+lkQrDet.FieldByName('ID').AsString+ERP_SQL_FIELDSUFFIX;
            lkSQLFields := lkSQLFields + SQLCRLF + '      ,' +lkS; 
            end;
          end;
        if(lkQrDet.FieldByName('FLAG_DELETE').AsInteger = 0)then
          begin
          lkCol := CreateTColumnEh(lkDBG, lkQrDet.FieldByName('ID').AsString, lkQrDet.FieldByName('FORMAT').AsString,
                     lkQrDet.FieldByName('NAME').AsString, lkQrDet.FieldByName('WIDTH').AsInteger, IntToTAlignment(lkQrDet.FieldByName('ALIGNMENT').AsInteger));
          with lkCol do
            begin     
            Title.Hint := lkQrDet.FieldByName('HINT').AsString;
            if(StrTrimAll(Title.Hint) = '')then
              Title.Hint := StrReplaceStr(Title.Caption, '|', SQLCRLF+SQLCRLF);
            Title.Orientation := IntToTTextOrientationEh(lkQrDet.FieldByName('ORIENTATION').AsInteger);
            ColParams.Clear;
            ColParams.Add(lkQrDet.FieldByName('TB_ID').AsString);        //0
            ColParams.Add(lkQrDet.FieldByName('ID').AsString);           //1
            ColParams.Add(lkQrDet.FieldByName('REF_TABLE').AsString);    //2
            ColParams.Add(lkQrDet.FieldByName('REF_FIELD').AsString);    //3
            ColParams.Add(lkQrDet.FieldByName('REF_KEYFIELD').AsString); //4
            ColParams.Add('');//lkQrDet.FieldByName('ID').AsString);     //5
            ColParams.Add('');//lkQrDet.FieldByName('ID').AsString);     //6
            if(lkQrDet.FieldByName('KEY_LIST').AsString <> '')then
              begin
              KeyList.Text  := lkQrDet.FieldByName('KEY_LIST').AsString; 
              PickList.Text := lkQrDet.FieldByName('PICK_LIST').AsString;
              end;  
            if(lkQrDet.FieldByName('REF_TABLE').AsString <> '')then
              FieldName := FieldName + ERP_SQL_FIELDSUFFIX;
            end;
          if(lkQrDet.FieldByName('FLAG_FOOTER').AsInteger <> 0)then
            begin
            lkDBG.FooterRowCount := MaxInteger(lkDBG.FooterRowCount, lkQrDet.FieldByName('FOOTER_COUNT').AsInteger);
            ERP_DBGridEh_Column_FootersLoad(lkCol, lkQrDet.Transaction, lkQrDet.FieldByName('TB_ID').AsString, lkQrDet.FieldByName('ID').AsString);
            end;           
          end;
        lkCounter := lkCounter + 1;
        lkQrDet.Next;
        end;
      if lkQrDet.Active then 
        lkQrDet.Close;
      lkQr.SQL.Text := 'SELECT '+lkSQLFields+' '+SQLCRLF+'FROM   '+lkSQLTables+' '+SQLCRLF+lkSQLWhere;
      //Dialogs.MessageDlg(lkQr.SQL.Text, mtInformation, [mbOk]);
      if(lkDBG.FooterRowCount > 0)then
        lkDBG.SumList.Active := true;
      i := i + 1;
      aQr.Next;
      end;
    lkQrDet.Free;
    TxcPageControlEx_ActivateDefaultPage(lkPCData);    
  end;
