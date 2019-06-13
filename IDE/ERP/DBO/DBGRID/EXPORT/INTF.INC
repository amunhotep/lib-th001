{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/INTF.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                {$I PEAKTOP:GLOBAL_VARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                  {$I PEAKTOP:GLOBAL_OBJECTS.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/CONST.INC} {$I ./CONST.INC}                  {$ENDIF}
  //==================== PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/INTF.INC ============
  procedure ERP_DBGridEh_ExportTo_(aDBG :TDBGridEh;const aInitFileName, aEntName, aEntAddr, aCaption, aFilterCaption, aExportScriptName:string);
  begin
    GlobalObjects_Add(ERP_DBGRID_EXPORT_GLOBALOBJECT_NAME      ,aDBG);
    SetGlobalVariable(ERP_DBGRID_EXPORT_GLOBALVARIABLE_FILENAME,aInitFileName);
    SetGlobalVariable(ERP_DBGRID_EXPORT_GLOBALVARIABLE_ENTNAME ,aEntName);
    SetGlobalVariable(ERP_DBGRID_EXPORT_GLOBALVARIABLE_ENTADDR ,aEntAddr);
    SetGlobalVariable(ERP_DBGRID_EXPORT_GLOBALVARIABLE_CAPTION ,aCaption);
    SetGlobalVariable(ERP_DBGRID_EXPORT_GLOBALVARIABLE_FILTER  ,aFilterCaption);
    call(aExportScriptName);
  end;
  //============================================================================
  procedure ERP_DBGridEh_ExportToHTML(aDBG :TDBGridEh;const aInitFileName, aEntName, aEntAddr, aCaption, aFilterCaption :string);
  begin
    ERP_DBGridEh_ExportTo_(aDBG, aInitFileName, aEntName, aEntAddr, aCaption, aFilterCaption, 'PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/HTML.PS');
  end;
  //============================================================================
  procedure ERP_DBGridEh_ExportToExcel(aDBG :TDBGridEh; const aWorkSheetName, aEntName, aEntAddr, aCaption, aFilterCaption :string);
  begin
    ERP_DBGridEh_ExportTo_(aDBG, 'Sheet1', aEntName, aEntAddr, aCaption, aFilterCaption, 'PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/EXCEL.PS');
  end;
  //============================================================================
  procedure ERP_DBGridEh_ExportToOpenOfficeCalc(aDBG :TDBGridEh; const aWorkSheetName, aEntName, aEntAddr, aCaption, aFilterCaption :string);
  begin
    ERP_DBGridEh_ExportTo_(aDBG, '', aEntName, aEntAddr, aCaption, aFilterCaption, 'PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/OPENOFFICECALC.PS');
  end;
