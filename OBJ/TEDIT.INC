{$DEFINE PEAKTOP:OBJ/TEDIT.INC}
  //============================================================================
  function CreateTEdit(a_Owner :TComponent; a_Parent:TWinControl; const a_Name:string; const a_Left, a_Top, a_Height, a_Width:Integer):TEdit;
  begin
    if(a_Owner.FindComponent(a_Name) <> nil)then
      Result := TEdit(a_Owner.FindComponent(a_Name))
     else 
      Result := TEdit.Create(a_Owner);
    with Result do
      begin  
      Name       := a_Name;
      Parent     := a_Parent;
      Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
      Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      Ctl3D      := false;
      Left       := a_Left;
      Top        := a_Top;
      Height     := a_Height;
      Width      := a_Width;
      Text       := '';
      end;
  end;
  //============================================================================
  function FindTEdit(a_Owner :TComponent; const a_Name:string):TEdit;
  begin
    Result := nil;
    if(a_Owner.FindComponent(a_Name) <> nil)then
      begin
      Result            := TEdit(a_Owner.FindComponent(a_Name));
      Result.Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
      Result.Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      end;
  end;
