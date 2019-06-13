{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/PROC.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                   {$I PEAKTOP:GLOBAL_VARIABLES.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}            {$I ../../OBJECTNAMES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC} {$I ../../$COMMON/FORMERP_HEADER.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}  {$I ../../USERS/GLOBALVARIABLES.INC}  {$ENDIF}
  //=================== PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/PROC.INC ============== 
  procedure ERP_DataSet_PrintPreview(const aReportId, aReportName, aReportPath :string; const aPreview:Boolean);
  var
    lkResource :string;
    lkFileName :string;
    lkDTS      :TxFBDataSet;
    lkRpt      :TxReport;
    lkImg      :TxrImage;
    lkLbl      :TxrLabel;
    lkTr       :TxFBTransaction;
    lkQr       :TxFBQuery;
    lkCnt, i   :Integer; 
    lkNumber   :Integer;
    lkTypeId   :Integer;
    lkFSID     :string;
    lkFSPath   :string;
    lkFSSRC    :string;
    lkSQLID      :string;     
    lkSQLOrderBy :string;     
  begin
    lkResource := '';
    lkResource := StringsLoadFromFile(aReportPath);
    if(lkResource = '')then
      begin
      Dialogs.MessageDlg('Не удалось загрузить шаблон печати !'+#13#10#13#10+aReportPath, mtError, [mbOK]);
      exit;
      end;
    lkRpt := TxReport(StrToComponent(lkResource));
    lkRpt.DataBase := FBDataBase;
    lkRpt.Title    := aReportName;
    lkImg := nil;
    if(lkRpt.FindComponent('ImgLogo')   <> nil)then lkImg := TxrImage(lkRpt.FindComponent('ImgLogo'));
    if(lkRpt.FindComponent('ImageLogo') <> nil)then lkImg := TxrImage(lkRpt.FindComponent('ImageLogo'));
    if(lkImg <> nil)then
      begin
      lkResource := StrAbsolutePath('../conf/ent/logo.bmp', Amunhotep.ExeName);
      if FileExists(lkResource)then
        try lkImg.Picture.LoadFromFile(lkResource) except end;
      end;

    lkImg := nil; if(lkRpt.FindComponent('ImgObj') <> nil)then lkImg := TxrImage(lkRpt.FindComponent('ImgObj'));
    if(lkImg <> nil)then
      begin
      lkResource := PrepareAbsoleteFileName(ERP_ObjectPreviewBitmap(StrToInt(TERPForm_Settings(Amunhotep.MainForm.ActiveMDIChild).Values[ERP_SETTINGS_BASETYPE])));
      if FileExists(lkResource)then
        try 
          lkImg.Picture.LoadFromFile(lkResource);
        finally 
          with lkImg.Picture.Bitmap do
            begin
            TransparentColor := Canvas.Pixels[0,0];
            TransparentMode  := tmAuto;
            Transparent      := true;
            end;
        end;
      end;

    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        Add('isc_tpb_read_committed');
        Add('isc_tpb_read');
        Add('isc_tpb_rec_version');
        Add('isc_tpb_nowait');
        end;
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQr do
      begin
      Transaction := lkTr;
      SQL.Text := 'SELECT R1.* FROM TABL$_TB_DOCSRPTSQL R1 WHERE (R1.RPT_ID = '''+aReportId+''') ORDER BY R1.ORDERID';
      end;
    lkQr.Open;
    lkQr.First;
    lkCnt := 0;
    while not lkQr.EOF do
      begin
      lkFSID := '';
      lkFSSRC:= '';
      lkCnt := lkCnt + 1;
      if(lkRpt.DataSets.Count < lkCnt)then
        lkRpt.DataSets.Add;
      with lkRpt.DataSets[lkCnt-1] do
        begin
        Name         := lkQr.FieldByName('NAME'  ).AsString;
        MasterDataSet:= lkQr.FieldByName('PARENT').AsString;
        lkFileName   := lkQr.FieldByName('PATH').AsString;
        if(UpperCase(StrTrimAll(lkFileName)) = ERP_SQL_CURRENT_QUERY)then
          begin
          lkDTS  := nil;
          try
            with TERPForm_ActiveDBGrid(Amunhotep.MainForm.ActiveMDIChild) do
              begin
              if(UpperCase(DataSource.DataSet.ClassName) = 'TXFBDATASET')then
                lkDTS := TxFBDataSet(DataSource.DataSet)
               else if(UpperCase(DataSource.DataSet.ClassName) = 'TMEMTABLEEH')then
                begin
                lkDTS   := TxFBDataSet(TDataSetDriverEh(TMemTableEh(DataSource.DataSet).DataDriver).ProviderDataSet);
                lkFSSRC := '';
                if STFilter.Visible then
                  for i:=0 to Columns.Count-1 do
                    if(Columns[i].STFilter.ExpressionStr <> '')then
                      lkFSSRC := '~';
                if(lkFSSRC <> '')then
                  begin
                  DataSource.DataSet.DisableControls;
                  SaveBookMark;
                  DataSource.DataSet.First;
                  while not DataSource.DataSet.EOF do
                    begin
                    lkFSSRC := lkFSSRC + DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString + '~';
                    DataSource.DataSet.Next;
                    end;
                  RestoreBookMark;
                  DataSource.DataSet.EnableControls;
                  lkFSPath := 'DB:HOME/'+GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+'/PRINT_'+aReportId+'.TXT';
                  GetFieldCommit(lkDTS.DataBase, 'PROC$_FS_CREATE_FILE('''+StrReplaceStr(lkFSPath,'''','''''')+''', '''+lkFSSRC+''')', 'ID', '', lkFSID);
                  end;
                end;
              end;
          except
            lkRpt.Free;
            exit;
          end;  
          if(lkDTS <> nil)then
            begin
            lkFSSRC  := lkDTS.SelectSQL.Text;                                   // getting query text;
            lkFSPath := '';                                                     // temporary variable for ORDER BY clause
            if(lkFSID <> '')then
              begin
              i := Pos('ORDER BY ', lkFSSRC);
              if(i > 0)then
                begin
                lkSQLOrderBy := Copy(lkFSSRC, i, Length(lkFSSRC) - i + 1);      // saving ORDER BY clause
                Delete(lkFSSRC, i, Length(lkFSSRC) - i + 1);                    // delete ORDER BY clause from script
                end;
              lkFSSRC := lkFSSRC + SQLCRLF + 
                '  AND ( (SELECT FIRST 1 FS.SRC FROM TABL$_FS FS WHERE(FS.ID = '''+lkFSID+
                ''')) CONTAINING ''~''||'+{ERP_SQL_TABLEPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT,0)}'ID||''~'') '+SQLCRLF+
                lkSQLOrderBy;                                                   // restoring ORDER BY clause
              end;
            SQL.Text := lkFSSRC;                                                // setting query text;
            Query.Prepare;
            if(Query.Params.Count > 0)then
              for i:=0 to Query.Params.Count-1 do
                Query.Params[i].Value := lkDTS.ParamByName(Query.Params[i].Name).Value;
            end
          end
         else 
          SQL.Text := StringsLoadFromFile(lkFileName);
        //Dialogs.MessageDlg(SQL.Text, mtInformation, [mbOk]);  
        if( (StrTrimAll(MasterDataSet) = '') and (UpperCase(StrTrimAll(lkFileName)) <> ERP_SQL_CURRENT_QUERY) ) then
          begin
          Query.Prepare;
          if(Query.Params.Count > 0)then
            for i:=0 to Query.Params.Count-1 do
              Query.Params[i].AsString := GetGlobalVariable(Query.Params[i].Name);
          end;      
        end; 
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
    lkLbl := nil;
    if(lkRpt.FindComponent('lblObjCaption') <> nil)then lkLbl := TxrLabel(lkRpt.FindComponent('lblObjCaption'));
    if(lkLbl <> nil)then 
      begin
      lkTypeId := StrToInt(TERPForm_Settings(Amunhotep.MainForm.ActiveMDIChild).Values[ERP_SETTINGS_BASETYPE]);
      if(lkTypeId = ERP_OBJECTTYPE_DOC)then
        lkLbl.Caption := TERPForm_Settings(Amunhotep.MainForm.ActiveMDIChild).Values[ERP_SETTINGS_TABLECAPTION]
       else 
        lkLbl.Caption := ERP_ObjectCaption(lkTypeId)+' "'+TERPForm_Settings(Amunhotep.MainForm.ActiveMDIChild).Values[ERP_SETTINGS_TABLECAPTION]+'"';
      end;  
    lkRpt.Prepare;
    if aPreview then 
      lkRpt.Preview
     else
      begin
      lkRpt.Print;
      lkRpt.Free;
      end; 
  end;  
