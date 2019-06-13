{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/INTF_COMENTS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                       {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                         {$I PEAKTOP:GLOBAL_OBJECTS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}      {$I ../$COMMON/FORMERP_NAMES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/COMENTS_GLOBALVARIABLES.INC}{$I ./COMENTS_GLOBALVARIABLES.INC}           {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/DOC/INTF_COMENTS.INC ================
  function DocComentsIntf_Create(aOwner:TComponent; aParent:TWinControl; aMasterDataSource:TDataSource):TxcPanel;
  var
    lkCmp :TComponent;
  begin
    Result := nil;
    GlobalObjects_Add(ERP_GLOBALVARIABLE_DOC_COMENTS_OBJOWNER     ,aOwner);
    GlobalObjects_Add(ERP_GLOBALVARIABLE_DOC_COMENTS_OBJPARENT    ,aParent);
    GlobalObjects_Add(ERP_GLOBALVARIABLE_DOC_COMENTS_OBJDATASOURCE,aMasterDataSource);
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/DOC/COMENTS.PS'));
    lkCmp := aOwner.FindComponent(obj_name_erp_panelcoments);
    if(lkCmp <> nil)then
      Result := TxcPanel(lkCmp);
  end;
