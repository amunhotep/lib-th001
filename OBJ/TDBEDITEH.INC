{$DEFINE PEAKTOP:OBJ/TDBEDITEH.INC}
  //======================== PEAKTOP:OBJ/TDBEDITEH.INC =========================
  function CreateTDBEditEh(a_Owner :TComponent;const a_ObjectName :string; a_Parent:TWinControl;
    a_DataSource :TDataSource; const a_DataField:string; const a_Left, a_Top, a_Height, a_Width:Integer):TDBEditEh;
  begin
    if(a_Owner.FindComponent(a_ObjectName) <> nil)then
      Result := TDBEditEh(a_Owner.FindComponent(a_ObjectName))
     else 
      Result := TDBEditEh.Create(a_Owner);
    with Result do
      begin
      if(a_ObjectName <> '')then
        Name     := a_ObjectName;
      Parent     := a_Parent;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Ctl3D      := false;
      Flat       := true;
      Left       := a_Left;
      Top        := a_Top;
      Height     := a_Height;
      Width      := a_Width;
      DataSource := a_DataSource;
      DataField  := a_DataField;
      end;
  end;
  //============================================================================
  function FindTDBEditEh(a_Owner :TComponent; const a_ObjectName :string):TDBEditEh;
  var
    lkComp :TComponent;
  begin
    Result := nil;
    lkComp := a_Owner.FindComponent(a_ObjectName);
    if(lkComp <> nil)then
      if(ObjectInheritsFrom(lkComp, 'TDBEditEh'))then
        begin
        Result := TDBEditEh(lkComp);
        with Result do
          begin
          Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
          Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
          Ctl3D      := false;
          Flat       := true;
          end;
        end;
  end;
