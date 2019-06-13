{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/INTERFACE.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                       {$I PEAKTOP:GLOBAL_VARIABLES.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                         {$I PEAKTOP:GLOBAL_OBJECTS.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}      {$I ../../$COMMON/FORMERP_NAMES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/GLOBALVARIABLES.INC} {$I ./GLOBALVARIABLES.INC}           {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/INTERFACE.INC ===============
  function LocalizationIntf_Create(aOwner:TComponent; aParent:TWinControl; aMasterDataSource:TDataSource; const aObjId :string):TxcPanel;
  var
    lkCmp :TComponent;
  begin
    Result := nil;
    GlobalObjects_Add(ERP_GLOBALVARIABLE_LOCALIZATION_OBJOWNER     ,aOwner);
    GlobalObjects_Add(ERP_GLOBALVARIABLE_LOCALIZATION_OBJPARENT    ,aParent);
    GlobalObjects_Add(ERP_GLOBALVARIABLE_LOCALIZATION_OBJDATASOURCE,aMasterDataSource);
    SetGlobalVariable(ERP_GLOBALVARIABLE_LOCALIZATION_OBJTABLE     ,aObjId);
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/DEFAULT_PANEL.PS'));
    lkCmp := aOwner.FindComponent(obj_name_erp_panelcoments);
    if(lkCmp <> nil)then
      Result := TxcPanel(lkCmp);
  end;
