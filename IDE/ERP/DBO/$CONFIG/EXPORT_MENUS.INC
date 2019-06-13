{$DEFINE PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_MENUS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_HEADER.INC}  {$I ./EXPORT_HEADER.INC}  {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_ROLES.INC =============
  procedure ERP_ConfigExportMenus();
  var
    lkTr         :TxFBTransaction;
    lkQr         :TxFBQuery;
    lkFileName   :string;
    lkSRC        :string;
  begin
    CreateTxFBQuery(['isc_tpb_read_committed','isc_tpb_read','isc_tpb_rec_version','isc_tpb_nowait'], lkTr, lkQr);
    lkQr.SQL.Text := 'SELECT R.* FROM TABL$_MENUS R ORDER BY R.ID ';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkSRC := 
        'EXECUTE BLOCK AS '+SQLCRLF+
        '  DECLARE VARIABLE P_ID TYPE OF COLUMN TABL$_MENUS.ID; '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  UPDATE OR INSERT INTO TABL$_MENUS ( '+SQLCRLF+
        '     ID '+SQLCRLF+
        '    ,NAME '+SQLCRLF+
        '    ,DESCR '+SQLCRLF+
        '  )VALUES( '+SQLCRLF+
        '     '''+StrReplaceStr(lkQr.FieldByName('ID').AsString  ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('NAME').AsString,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('DESCR').AsString,'''','''''')+''' '+SQLCRLF+
        '  )MATCHING (ID) RETURNING ID INTO :P_ID; '+SQLCRLF+
        '  UPDATE TABL$_MENUS R SET R.ID = '+lkQr.FieldByName('ID').AsString+' WHERE (R.ID = :P_ID); '+SQLCRLF+
        'END';
      lkFileName := PrepareAbsoleteFileName(ERP_ObjectDirStructure(ERP_OBJECTTYPE_MENUS)+ERP_FILENAME_SQL_EXPORTIMPORTITEM+'1_'+lkQr.FieldByName('ID').AsString+'.SQL');
      WriteLn(lkFileName);
      if not DirectoryExists(ExtractFilePath(lkFileName))then 
        CreateDir(ExtractFilePath(lkFileName));        
      StringsSaveToFile(lkFileName, lkSRC);
      lkQr.Next;
      end;
    if lkTr.InTransaction then lkTr.Commit;

    lkQr.SQL.Text := 'SELECT R.* FROM TABL$_MENU R ORDER BY R.ID ';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkSRC := 
        'EXECUTE BLOCK AS '+SQLCRLF+
        '  DECLARE VARIABLE P_ID TYPE OF COLUMN TABL$_MENU.ID; '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  UPDATE OR INSERT INTO TABL$_MENU ( '+SQLCRLF+
        '     MENUS_ID '+SQLCRLF+
        '    ,ID '+SQLCRLF+
        '    ,NAME '+SQLCRLF+
        '    ,PARENT_ID '+SQLCRLF+
        '    ,SHORTCUT '+SQLCRLF+
        '    ,SCRIPT_NAME '+SQLCRLF+
        '    ,IMAGE_INDEX '+SQLCRLF+
        '    ,GROUP_INDEX '+SQLCRLF+
        '    ,ACCSS '+SQLCRLF+
        '  )VALUES( '+SQLCRLF+
        '     '+lkQr.FieldByName('MENUS_ID').AsString+' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('ID').AsString+' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('NAME').AsString,'''','''''')+''' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('PARENT_ID').AsString+' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('SHORTCUT').AsString,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('SCRIPT_NAME').AsString,'''','''''')+''' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('IMAGE_INDEX').AsString+' '+SQLCRLF+
        '    ,'+lkQr.FieldByName('GROUP_INDEX').AsString+' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('ACCSS').AsString,'''','''''')+''' '+SQLCRLF+
        '  )MATCHING (ID) RETURNING ID INTO :P_ID; '+SQLCRLF+
        '  UPDATE TABL$_MENU R SET R.ID = '+lkQr.FieldByName('ID').AsString+' WHERE (R.ID = :P_ID); '+SQLCRLF+
        'END';
      lkFileName := PrepareAbsoleteFileName(ERP_ObjectDirStructure(ERP_OBJECTTYPE_MENUS)+ERP_FILENAME_SQL_EXPORTIMPORTITEM+'2_'+lkQr.FieldByName('ID').AsString+'.SQL');
      WriteLn(lkFileName);
      if not DirectoryExists(ExtractFilePath(lkFileName))then 
        CreateDir(ExtractFilePath(lkFileName));        
      StringsSaveToFile(lkFileName, lkSRC);
      lkQr.Next;
      end;
    if lkTr.InTransaction then lkTr.Commit;
    lkTr.Free;  
  end;
