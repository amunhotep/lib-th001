{$DEFINE PEAKTOP:OBJ/TDBEDITEH.2.INC}
  //====================== PEAKTOP:OBJ/TDBEDITEH.2.INC =========================
  function CreateTDBEditEh(aOwner :TComponent; aParent:TWinControl; aDataSource :TDataSource; 
    const aObjectName, aDataField:string; const aLeft, aTop, aHeight, aWidth:Integer):TDBEditEh;
  begin
    if(aOwner.FindComponent(aObjectName) <> nil)then
      Result := TDBEditEh(aOwner.FindComponent(aObjectName))
     else
      Result := TDBEditEh.Create(aOwner);
    with Result do
      begin
      if(aObjectName <> '')then
        Name     := aObjectName;
      Parent     := aParent;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Ctl3D      := false;
      Flat       := true;
      Left       := aLeft;
      Top        := aTop;
      Height     := aHeight;
      Width      := aWidth;
      DataSource := aDataSource;
      DataField  := aDataField;
      end;
  end;
