{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/INTF.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                {$I PEAKTOP:GLOBAL_VARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/CONST.INC}  {$I ./CONST.INC}                  {$ENDIF}
  //==================== PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/INTF.INC ============
  procedure ERP_DBGridEh_PrintItem(const aObjType, aObjName :string);
  begin
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_TYPE, aObjType);
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_NAME, aObjName);
    call('PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/PRINT_ITEM.PS');
  end;
  //============================================================================
  procedure ERP_DBGridEh_Print(const aObjType, aObjName :string);
  begin
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_TYPE, aObjType);
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_NAME, aObjName);
    call('PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/PRINT.PS');
  end;
  //============================================================================
  procedure ERP_DBGridEh_PreviewItem(const aObjType, aObjName :string);
  begin
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_TYPE, aObjType);
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_NAME, aObjName);
    call('PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/PREVIEW_ITEM.PS');
  end;
  //============================================================================
  procedure ERP_DBGridEh_Preview(const aObjType, aObjName :string);
  begin
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_TYPE, aObjType);
    SetGlobalVariable(ERP_DBGRID_PRINT_GLOBALOBJECT_NAME, aObjName);
    call('PEAKTOP:IDE/ERP/DBO/DBGRID/PRINT/PREVIEW.PS');
  end;  
