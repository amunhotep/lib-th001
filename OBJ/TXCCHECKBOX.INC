{$DEFINE PEAKTOP:OBJ/TXCCHECKBOX.INC}
  //===================== PEAKTOP:OBJ/TXCCHECKBOX.INC ==========================
  function CreateTxcCheckBox(aOwner:TComponent; aParent:TWinControl; const aName, aCaption, aHint:string; const aAlign :TAlign; 
             const aLeft, aTop, aHeight, aWidth :Integer; const aChecked:Boolean):TxcCheckBox;
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TxcCheckBox(aOwner.FindComponent(aName))
     else
      Result := TxcCheckBox.Create(aOwner);
    with Result do
      begin
      Parent       := aParent;
      if(StrTrimAll(aName)<>'')then
        Name       := aName;
      Left         := aLeft;
      Top          := aTop;
      Height       := aHeight;
      Width        := aWidth;
      Align        := aAlign;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Caption      := aCaption;
      Hint         := aHint;
      Checked      := aChecked;
      end;
  end;
