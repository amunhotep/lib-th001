{$DEFINE PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_ROLES.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_HEADER.INC}  {$I ./EXPORT_HEADER.INC}  {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_ROLES.INC =============
  procedure ERP_ConfigExportRoles(const aRootPath :string; const aReplacePathToLocal:Boolean);
  var
    lkTr         :TxFBTransaction;
    lkQr         :TxFBQuery;
    lkFileName   :string;
    lkSRC        :string;
  begin
    CreateTxFBQuery(['isc_tpb_read_committed','isc_tpb_read','isc_tpb_rec_version','isc_tpb_nowait'], lkTr, lkQr);
    lkQr.SQL.Text := 'SELECT R.* FROM TABL$_USERS_ROLES R ORDER BY R.ID ';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkSRC := 
        'EXECUTE BLOCK AS '+SQLCRLF+
        '  DECLARE VARIABLE P_ID TYPE OF COLUMN TABL$_USERS_ROLES.ID; '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  UPDATE OR INSERT INTO TABL$_USERS_ROLES ( '+SQLCRLF+
        '     ID '+SQLCRLF+
        '    ,NAME '+SQLCRLF+
        '  )VALUES( '+SQLCRLF+
        '     '''+StrReplaceStr(lkQr.FieldByName('ID').AsString  ,'''','''''')+''' '+SQLCRLF+
        '    ,'''+StrReplaceStr(lkQr.FieldByName('NAME').AsString,'''','''''')+''' '+SQLCRLF+
        '  )MATCHING (ID) RETURNING ID INTO :P_ID; '+SQLCRLF+
        '  UPDATE TABL$_USERS_ROLES R SET R.ID = '''+StrReplaceStr(lkQr.FieldByName('ID').AsString  ,'''','''''')+''' WHERE (R.ID = :P_ID); '+SQLCRLF+
        'END';
      lkFileName := PrepareAbsoleteFileName(ERP_ObjectDirStructure(ERP_OBJECTTYPE_ROLES)+ERP_FILENAME_SQL_EXPORTIMPORTITEM+'_'+lkQr.FieldByName('ID').AsString+'.SQL');
      WriteLn(lkFileName);
      if not DirectoryExists(ExtractFilePath(lkFileName))then 
        CreateDir(ExtractFilePath(lkFileName));        
      StringsSaveToFile(lkFileName, lkSRC);
      lkQr.Next;
      end;
    if lkTr.InTransaction then lkTr.Commit;
    lkTr.Free;  
  end;
