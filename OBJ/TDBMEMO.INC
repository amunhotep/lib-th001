{$DEFINE PEAKTOP:OBJ/TDBMEMO.INC}
  //============================================================================
  function FindTDBMemo(a_Owner :TComponent; const a_ObjectName :string):TDBMemo;
  var
    lkComp :TComponent;
  begin
    Result := nil;
    lkComp := a_Owner.FindComponent(a_ObjectName);
    if(lkComp <> nil)then
      if(ObjectInheritsFrom(lkComp, 'TDBMemo'))then
        begin
        Result := TDBMemo(lkComp);
        with Result do
          begin
          Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
          Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
          ScrollBars := ssBoth;
          end;
        end;
  end;
  //============================================================================  
