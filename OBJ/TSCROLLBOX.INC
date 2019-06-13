{$DEFINE PEAKTOP:OBJ/TSCROLLBOX.INC}
  //=========================== PEAKTOP:OBJ/TSCROLLBOX.INC =====================
  function CreateTScrollBox(aOwner :TComponent; aParent:TWinControl; const aName:string; const aLeft, aTop, aHeight, aWidth:Integer; const aAlign :TAlign):TScrollBox;
  begin
    if(aOwner.FindComponent(aName) = nil)then
      Result := TScrollBox.Create(aOwner)
     else
      Result := TScrollBox(aOwner.FindComponent(aName));
    with Result do
      begin
      if(StrTrimAll(aName) <> '')then
        Name := aName;
      Parent := aParent;
      Color  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Ctl3D  := false;
      Left   := aLeft;
      Top    := aTop;
      Height := aHeight;
      Width  := aWidth;
      Align  := aAlign;
      end;
  end;
