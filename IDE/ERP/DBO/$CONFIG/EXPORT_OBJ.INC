{$DEFINE PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_TYPES.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_HEADER.INC}  {$I ./EXPORT_HEADER.INC}  {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_TYPES.INC =============
  procedure ERP_ConfigExportTypes();
  var
    lkTr         :TxFBTransaction;
    lkQr         :TxFBQuery;
    lkFileName   :string;
    lkSRC        :string;
  begin
    CreateTxFBQuery(['isc_tpb_read_committed','isc_tpb_read','isc_tpb_rec_version','isc_tpb_nowait'], lkTr, lkQr);
    lkQr.SQL.Text := 'SELECT R.* FROM TABL$_TB_TYPES R ORDER BY R.ID ';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkSRC := 
        'EXECUTE BLOCK AS '+SQLCRLF+
        '  DECLARE VARIABLE P_ID TYPE OF COLUMN TABL$_TB_TYPES.ID; '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  UPDATE OR INSERT INTO TABL$_TB_TYPES ( '+SQLCRLF+
        '     ROOT_ID '+SQLCRLF+
        '    ,ID '+SQLCRLF+
        '    ,PARENT_ID '+SQLCRLF+
        '    ,NAME '+SQLCRLF+
        '    ,NAME2 '+SQLCRLF+
        '  )VALUES( '+SQLCRLF+
        '     '+lkQr.FieldByName('ROOT_ID').AsString+' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('ID').AsString+' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('PARENT_ID').AsString+' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('NAME').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('NAME2').AsString,'''','''''')+''' '+SQLCRLF+
        '  )MATCHING (ID) RETURNING ID INTO :P_ID; '+SQLCRLF+
        '  UPDATE TABL$_TB_TYPES R SET R.ID = '+lkQr.FieldByName('ID').AsString+' WHERE (R.ID = :P_ID); '+SQLCRLF+
        'END';
      lkFileName := PrepareAbsoleteFileName(ERP_DIRECTORY_SQLLOAD_STRUCTURE+'TYPES/'+ERP_FILENAME_SQL_EXPORTIMPORTITEM+'1_'+FormatFloat('#00000000',lkQr.FieldByName('ID').AsInteger)+'.SQL');
      WriteLn(lkFileName);
      if not DirectoryExists(ExtractFilePath(lkFileName))then 
        CreateDir(ExtractFilePath(lkFileName));        
      StringsSaveToFile(lkFileName, lkSRC);
      lkQr.Next;
      end;
    if lkTr.InTransaction then lkTr.Commit;

    lkQr.SQL.Text := 'SELECT R.* FROM TABL$_TB_DOCS R ORDER BY R.ID ';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkSRC := 
        'EXECUTE BLOCK AS '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  UPDATE OR INSERT INTO TABL$_TB_DOCS ( '+SQLCRLF+
        '     TYPE_ID '+SQLCRLF+
        '    ,ID '+SQLCRLF+
        '    ,NAME '+SQLCRLF+
        '    ,COLOR_FRG '+SQLCRLF+
        '    ,COLOR_BGR '+SQLCRLF+
        '    ,COLOR_FRG_HTML '+SQLCRLF+
        '    ,COLOR_BGR_HTML '+SQLCRLF+
        '    ,NUM_PREFIX '+SQLCRLF+
        '    ,GENR '+SQLCRLF+
        '    ,GENR_NAME '+SQLCRLF+
        '    ,ACCSS_COMM '+SQLCRLF+
        '    ,ACCSS_UNCOM '+SQLCRLF+
        '    ,ACCSS_PRINT '+SQLCRLF+
        '    ,ACCSS_PRN '+SQLCRLF+
        '    ,ACCSS_EXP '+SQLCRLF+
        '  )VALUES( '+SQLCRLF+
        '     '+lkQr.FieldByName('TYPE_ID').AsString+' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('ID').AsString+' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('NAME').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('COLOR_FRG').AsString+' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('COLOR_BGR').AsString+' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('COLOR_FRG_HTML').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('COLOR_BGR_HTML').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('NUM_PREFIX').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('GENR').AsString+' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('GENR_NAME').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('ACCSS_COMM').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('ACCSS_UNCOM').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('ACCSS_PRINT').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('ACCSS_PRN').AsString ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('ACCSS_EXP').AsString ,'''','''''')+''' '+SQLCRLF+
        '  )MATCHING (TYPE_ID); '+SQLCRLF+
        'END';
      lkFileName := PrepareAbsoleteFileName(ERP_DIRECTORY_SQLLOAD_STRUCTURE+'TYPES/'+ERP_FILENAME_SQL_EXPORTIMPORTITEM+'2_'+FormatFloat('#00000000',lkQr.FieldByName('ID').AsInteger)+'.SQL');
      WriteLn(lkFileName);
      if not DirectoryExists(ExtractFilePath(lkFileName))then 
        CreateDir(ExtractFilePath(lkFileName));        
      StringsSaveToFile(lkFileName, lkSRC);
      lkQr.Next;
      end;
    if lkTr.InTransaction then lkTr.Commit;

    lkTr.Free;  
  end;
