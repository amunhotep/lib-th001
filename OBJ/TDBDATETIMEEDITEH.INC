{$DEFINE PEAKTOP:OBJ/TDBDATETIMEEDITEH.INC}
  //============================================================================
  function FindTDBDateTimeEditEh(a_Owner :TComponent; const a_ObjectName :string):TDBDateTimeEditEh;
  var
    lkComp :TComponent;
  begin
    Result := nil;
    lkComp := a_Owner.FindComponent(a_ObjectName);
    if(lkComp <> nil)then
      if(ObjectInheritsFrom(lkComp, 'TDBDateTimeEditEh'))then
        begin
        Result := TDBDateTimeEditEh(lkComp);
        with Result do
          begin
          Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
          Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
          Ctl3D      := false;
          Flat       := true;
          end;
        end;
  end;
  //============================================================================  
