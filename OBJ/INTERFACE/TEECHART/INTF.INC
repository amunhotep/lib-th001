{$DEFINE PEAKTOP:OBJ/INTERFACE/TEECHART/INTF.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                      {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                        {$I PEAKTOP:GLOBAL_OBJECTS.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/TEECHART/GLOBALVARIABLES.INC}{$I ./GLOBALVARIABLES.INC}         {$ENDIF}
  //================ PEAKTOP:OBJ/INTERFACE/TEECHART/INTF.INC ===================
  function Interface_TeeChart_Create(aOwner :TComponent; aParent :TWinControl; const aName :string):TDBChart;
  var
    lkCmp :TComponent;
  begin
    Result := nil;
    GlobalObjects_Add(INTF_TEECHART_OBJNAME_OWNER ,aOwner );
    GlobalObjects_Add(INTF_TEECHART_OBJNAME_PARENT,aParent);
    SetGlobalVariable(INTF_TEECHART_OBJNAME       ,aName  )
    call(PrepareAbsoleteFileName('PEAKTOP:OBJ/INTERFACE/TEECHART/DEFAULT.PS'));
    lkCmp := aOwner.FindComponent(aName);
    if(lkCmp <> nil)then
      Result := TDBChart(lkCmp);
  end;
