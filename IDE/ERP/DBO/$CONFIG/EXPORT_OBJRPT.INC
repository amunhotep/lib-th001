{$DEFINE PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_OBJRPT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_HEADER.INC}  {$I ./EXPORT_HEADER.INC}  {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_OBJRPT.INC =============
  procedure ERP_ConfigExport_ObjReports(const aRootPath :string; const aReplacePathToLocal:Boolean);
  var
    lkTr         :TxFBTransaction;
    lkQr         :TxFBQuery;
    lkQrSQL      :TxFBQuery;
    lkFolderName :string;
    lkFileName   :string;
    lkRptFilePath:string;
    lkSRC        :string;
  begin
    lkFolderName := aRootPath + '/' + ERP_FOLDER_EXPORT_OBJREPORTS;
    if not DirectoryExists(lkFolderName) then
      CreateDir(lkFolderName);
    CreateTxFBQuery(['isc_tpb_read_committed','isc_tpb_read','isc_tpb_rec_version','isc_tpb_nowait'], lkTr, lkQr);
    lkQrSQL := TxFBQuery.Create(lkTr);
    lkQrSQL.Transaction := lkTr;
    lkQr.SQL.Text := 'SELECT R.* FROM TABL$_TB_DOCSRPT R ORDER BY R.OBJ_ID, R.SUBTYPE, R.ORDERID, R.ID ';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkRptFilePath := StrReplaceStr(lkQr.FieldByName('PATH').AsString,'\','/');
      if aReplacePathToLocal then
        begin
        if(Pos('DB:CONFIG/', lkRptFilePath) = 1)then
          begin
          Delete(lkRptFilePath, 1, Length('DB:CONFIG/'));
          lkRptFilePath := 'PEAKTOP:IDE/ERP/CONFIG/' + lkRptFilePath;
          end;
        end;
      lkSRC := 
        'EXECUTE BLOCK AS '+SQLCRLF+
        '  DECLARE VARIABLE P_ID TYPE OF COLUMN TABL$_TB_DOCSRPT.ID; '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  UPDATE OR INSERT INTO TABL$_TB_DOCSRPT (OBJ_ID, NAME, ORDERID, SUBTYPE, PATH, DESCR, ACCSS)VALUES( '+SQLCRLF+
        '    '''+StrReplaceStr(lkQr.FieldByName('OBJ_ID').AsString ,'''','''''')+
        ''', '''+StrReplaceStr(lkQr.FieldByName('NAME').AsString ,'''','''''')+
        ''', '+lkQr.FieldByName('ORDERID').AsString+', '+lkQr.FieldByName('SUBTYPE').AsString+
        ', '''+StrReplaceStr(lkRptFilePath,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('DESCR').AsString,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('ACCSS').AsString,'''','''''')+''' '+SQLCRLF+
        '  )MATCHING (OBJ_ID, NAME, ORDERID, SUBTYPE) RETURNING ID INTO :P_ID; '+SQLCRLF+
        '  -- OBJECT SQL '+SQLCRLF+
        '  DELETE FROM TABL$_TB_DOCSRPTSQL R1 WHERE (R1.RPT_ID = :P_ID); '+SQLCRLF;
      lkRptFilePath := '';  
      if lkQrSQL.Active then lkQrSQL.Close;  
      lkQrSQL.SQL.Text := 'SELECT R.* FROM TABL$_TB_DOCSRPTSQL R WHERE (R.RPT_ID = '''+lkQr.FieldByName('ID').AsString+''') ORDER BY R.ORDERID ';
      lkQrSQL.Open;
      lkQrSQL.First;
      while not lkQrSQL.EOF do
        begin
        lkRptFilePath := StrReplaceStr(lkQrSQL.FieldByName('PATH').AsString,'\','/');
        if aReplacePathToLocal then
          begin
          if(Pos('DB:CONFIG/', lkRptFilePath) = 1)then
            begin
            Delete(lkRptFilePath, 1, Length('DB:CONFIG/'));
            lkRptFilePath := 'PEAKTOP:IDE/ERP/CONFIG/' + lkRptFilePath;
            end;
          end;
        lkSRC := lkSRC +
          '  UPDATE OR INSERT INTO TABL$_TB_DOCSRPTSQL (RPT_ID, NAME, PARENT, FLAG_DELETE, ORDERID, PATH) '+SQLCRLF+
          '    VALUES(:P_ID, '''+StrReplaceStr(lkQrSQL.FieldByName('NAME').AsString ,'''','''''')+
          ''', '''+StrReplaceStr(lkQrSQL.FieldByName('PARENT').AsString ,'''','''''')+
          ''', '+IntToStr(lkQrSQL.FieldByName('FLAG_DELETE').AsInteger)+', '+IntToStr(lkQrSQL.FieldByName('ORDERID').AsInteger)+', '''+
          StrReplaceStr(lkRptFilePath,'''','''''')+''') '+SQLCRLF+
          '    MATCHING (RPT_ID, NAME);'+SQLCRLF;  
        lkQrSQL.Next;
        end;
      if lkQrSQL.Active then lkQrSQL.Close;  
      lkSRC := lkSRC +'END';
      lkFileName := lkFolderName + '/' + lkQr.FieldByName('OBJ_ID').AsString+'_'+
        FormatFloat('00', lkQr.FieldByName('SUBTYPE').AsInteger)+'_'+
        FormatFloat('0000', lkQr.FieldByName('ORDERID').AsInteger)+'.SQL';
      StringsSaveToFile(lkFileName, lkSRC);
      lkQr.Next;
      end;
    if lkTr.InTransaction then lkTr.Commit;
    lkTr.Free;  
  end;
