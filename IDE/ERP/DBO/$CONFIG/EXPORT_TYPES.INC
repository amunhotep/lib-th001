{$DEFINE PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_TYPES.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_HEADER.INC}  {$I ./EXPORT_HEADER.INC}  {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_TYPES.INC =============
  procedure ERP_ConfigExport_Types(const aRootPath :string; const aReplacePathToLocal:Boolean);
  var
    lkTr         :TxFBTransaction;
    lkQr         :TxFBQuery;
    lkQrSQL      :TxFBQuery;
    lkFolderName :string;
    lkFileName   :string;
    lkSRC        :string;
  begin
    lkFolderName := aRootPath + '/' + ERP_FOLDER_EXPORT_TYPES;
    if not DirectoryExists(lkFolderName) then
      CreateDir(lkFolderName);
    CreateTxFBQuery(['isc_tpb_read_committed','isc_tpb_read','isc_tpb_rec_version','isc_tpb_nowait'], lkTr, lkQr);
    lkQrSQL := TxFBQuery.Create(lkTr);
    lkQrSQL.Transaction := lkTr;
    lkQr.SQL.Text := 'SELECT R.* FROM TABL$_TB_TYPES R ORDER BY R.ID ';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkSRC := 
        'EXECUTE BLOCK AS '+SQLCRLF+
        '  DECLARE VARIABLE P_ID TYPE OF COLUMN TABL$_TB_TYPES.ID; '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  UPDATE OR INSERT INTO TABL$_TB_TYPES(ROOT_ID, ID, PARENT_ID, NAME, NAME2)VALUES('+SQLCRLF+
        '    '+lkQr.FieldByName('ROOT_ID').AsString+', '+lkQr.FieldByName('ID').AsString+
        ', '+lkQr.FieldByName('PARENT_ID').AsString+
        ', '''+StrReplaceStr(lkQr.FieldByName('NAME').AsString ,'''','''''')+
        ''', '''+StrReplaceStr(lkQr.FieldByName('NAME2').AsString,'''','''''')+''' '+SQLCRLF+
        '  )MATCHING (ID) RETURNING ID INTO :P_ID; UPDATE TABL$_TB_TYPES R SET R.ID = '+lkQr.FieldByName('ID').AsString+' WHERE (R.ID = :P_ID); '+SQLCRLF;
      if lkQrSQL.Active then lkQrSQL.Close;  
      lkQrSQL.SQL.Text := 'SELECT R.* FROM TABL$_TB_DOCS R WHERE (R.TYPE_ID  = '''+lkQr.FieldByName('ID').AsString+''') ORDER BY R.TYPE_ID ';
      lkQrSQL.Open;
      lkQrSQL.First;
      while not lkQrSQL.EOF do
        begin
        lkSRC := lkSRC +
        '  UPDATE OR INSERT INTO TABL$_TB_DOCS (TYPE_ID,COLOR_FRG,COLOR_BGR,COLOR_FRG_HTML,COLOR_BGR_HTML,NUM_PREFIX,GENR,GENR_NAME)'+SQLCRLF+
        '    VALUES('+lkQrSQL.FieldByName('TYPE_ID').AsString+','+lkQrSQL.FieldByName('COLOR_FRG').AsString+
        ','+lkQrSQL.FieldByName('COLOR_BGR').AsString+','''+StrReplaceStr(lkQrSQL.FieldByName('COLOR_FRG_HTML').AsString ,'''','''''')+
        ''','''+StrReplaceStr(lkQrSQL.FieldByName('COLOR_BGR_HTML').AsString ,'''','''''')+
        ''','''+StrReplaceStr(lkQrSQL.FieldByName('NUM_PREFIX').AsString ,'''','''''')+
        ''','+lkQrSQL.FieldByName('GENR').AsString+','''+StrReplaceStr(lkQrSQL.FieldByName('GENR_NAME').AsString ,'''','''''')+''')MATCHING (TYPE_ID); '+SQLCRLF;
        lkQrSQL.Next;
        end;
      if lkQrSQL.Active then lkQrSQL.Close;  

      lkQrSQL.SQL.Text := 'SELECT R.* FROM TABL$_TB_DOCSSQL R WHERE (R.DOC_ID  = '''+lkQr.FieldByName('ID').AsString+''') ORDER BY R.DOC_ID, R.SUBTYPE, R.ORDERID ';
      lkQrSQL.Open;
      lkQrSQL.First;
      while not lkQrSQL.EOF do
        begin
        lkSRC := lkSRC +
        '  UPDATE OR INSERT INTO TABL$_TB_DOCSSQL(DOC_ID,FLAG_DELETE,SUBTYPE,ORDERID,NAME,SRC)VALUES('+lkQrSQL.FieldByName('DOC_ID').AsString+
        ',0,'+lkQrSQL.FieldByName('SUBTYPE').AsString+','+lkQrSQL.FieldByName('ORDERID').AsString+
        ', '''+StrReplaceStr(lkQrSQL.FieldByName('NAME').AsString ,'''','''''')+''','''+SQLCRLF+
        StrReplaceStr(lkQrSQL.FieldByName('SRC').AsString,'''','''''')+''')MATCHING (DOC_ID, NAME, SUBTYPE); '+SQLCRLF;
        lkQrSQL.Next;
        end;
      if lkQrSQL.Active then lkQrSQL.Close;  
      lkSRC := lkSRC +'END';
      lkFileName := lkFolderName + '/' + FormatFloat('#00000000', lkQr.FieldByName('ID').AsInteger)+'00.SQL';
      StringsSaveToFile(lkFileName, lkSRC);
      lkQr.Next;
      end;
    if lkTr.InTransaction then lkTr.Commit;
    lkTr.Free;  
  end;
