{$DEFINE PEAKTOP:OBJ/TDBEDIT.INC}
  //==================== PEAKTOP:OBJ/TDBEDIT.INC ===============================
  function CreateTDBEdit(a_Owner :TComponent; a_Parent:TWinControl; a_DataSource :TDataSource; const a_DataField:string; const a_Left, a_Top, a_Height, a_Width:Integer):TDBEdit;
  begin
    Result := TDBEdit.Create(a_Owner);
    with Result do
      begin
      Parent     := a_Parent;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Ctl3D      := false;
      Left       := a_Left;
      Top        := a_Top;
      Height     := a_Height;
      Width      := a_Width;
      DataSource := a_DataSource;
      DataField  := a_DataField;
      end;
  end;
