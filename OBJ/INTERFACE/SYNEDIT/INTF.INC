{$DEFINE PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                     {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                       {$I PEAKTOP:GLOBAL_OBJECTS.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/SYNEDIT/GLOBALVARIABLES.INC}{$I ./GLOBALVARIABLES.INC}         {$ENDIF}
  //================ PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC ====================
  function Interface_SynEdit_Create(aOwner :TComponent; aParent :TWinControl; const aName :string):TSynEdit;
  var
    lkCmp :TComponent;
  begin
    Result := nil;
    GlobalObjects_Add(INTF_SYNEDIT_OBJNAME_OWNER ,aOwner );
    GlobalObjects_Add(INTF_SYNEDIT_OBJNAME_PARENT,aParent);
    SetGlobalVariable(INTF_SYNEDIT_OBJNAME       ,aName  )
    call(PrepareAbsoleteFileName('PEAKTOP:OBJ/INTERFACE/SYNEDIT/DEFAULT.PS'));
    lkCmp := aOwner.FindComponent(aName);
    if(lkCmp <> nil)then
      Result := TSynEdit(lkCmp);
  end;
