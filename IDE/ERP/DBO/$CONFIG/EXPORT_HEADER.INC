{$DEFINE PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_HEADER.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}              {$I PEAKTOP:GLOBAL_VARIABLES.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}       {$I ../OBJECTNAMES.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBQUERY.INC}                 {$I PEAKTOP:OBJ/TXFBQUERY.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/FILES/SEARCH_UTILS.INC}   {$I PEAKTOP:SYSUTILS/FILES/SEARCH_UTILS.INC}   {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/$CONFIG/EXPORT_HEADER.INC ============
const
  ERP_FOLDER_EXPORT_TYPES      = 'TYPES';
  ERP_FOLDER_EXPORT_OBJREPORTS = 'OBJRPT';
  //============================================================================
  function ERP_ConfigExport_CreateTempPath:string;
  var
    lkGUID_  :TGUID;
    lkGUID   :string; 
  begin
    CoCreateGUID(lkGUID_);
    lkGUID := GUIDToStr(lkGUID_);
    lkGUID := Copy(lkGUID, 2, Length(lkGUID)-2);
    Result := StrAbsolutePath('../tmp/'+lkGUID, Amunhotep.ExeName);
    if not DirectoryExists(Result) then
      CreateDir(Result);
  end;
