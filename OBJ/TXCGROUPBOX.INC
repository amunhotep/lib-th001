{$DEFINE PEAKTOP:OBJ/TXCGROUPBOX.INC}
  //========================= PEAKTOP:OBJ/TXCGROUPBOX.INC ======================
  function CreateTxcGroupBox(aOwner:TComponent; aParent:TWinControl; 
             const aName, aCaption:string; const aAlign :TAlign; const aLeft, aTop, aHeight, aWidth :Integer):TxcGroupBox;
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TxcGroupBox(aOwner.FindComponent(aName))
     else 
      Result := TxcGroupBox.Create(aOwner);
    with Result do
      begin
      if(aName <> '')then 
        Name := aName;
      Parent       := aParent;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Caption      := aCaption;
      Left         := aLeft;
      Top          := aTop;
      Height       := aHeight;
      Width        := aWidth;
      Align        := aAlign;
      {$IFDEF AMUNHOTEP4504}
      Margin       := 4;
      Transparent  := false;
      {$ENDIF}
      end;
  end;  
