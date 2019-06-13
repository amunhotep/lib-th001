{$DEFINE PEAKTOP:OBJ/TDBCOMBOBOXEH.INC}
  //======================= PEAKTOP:OBJ/TDBCOMBOBOXEH.INC ======================
  function FindTDBComboBoxEh(a_Owner :TComponent; const a_ObjectName :string):TDBComboBoxEh;
  var
    lkComp :TComponent;
  begin
    Result := nil;
    lkComp := a_Owner.FindComponent(a_ObjectName);
    if(lkComp <> nil)then
      if(ObjectInheritsFrom(lkComp, 'TDBComboBoxEh'))then
        begin
        Result := TDBComboBoxEh(lkComp);
        with Result do
          begin
          Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
          Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
          Ctl3D      := false;
          Flat       := true;
          end;
        end;
  end;
