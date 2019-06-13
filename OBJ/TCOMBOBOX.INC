{$DEFINE PEAKTOP:OBJ/TCOMBOBOX.INC}
  //=================== PEAKTOP:OBJ/TCOMBOBOX.INC ==============================
  function CreateTComboBox(aOwner :TComponent; aParent:TWinControl; const aText:string; const aLeft, aTop, aHeight, aWidth:Integer;
             const aItems:string; const aItemIndex :Integer):TComboBox;
  begin
    Result := TComboBox.Create(aOwner);
    with Result do
      begin
      Parent     := aParent;
      Text       := aText;
      Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
      Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      Left       := aLeft;
      Top        := aTop;
      Height     := aHeight;
      Width      := aWidth;
      Items.Text := aItems;
      ItemIndex  := aItemIndex;
      end;
  end;
