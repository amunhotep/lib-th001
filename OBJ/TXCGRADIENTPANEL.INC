{$DEFINE PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}
  //================= PEAKTOP:OBJ/TXCGRADIENTPANEL.INC =========================
  function CreateTxcGradientPanel(aOwner:TComponent; aParent:TWinControl; 
             const aName, aCaption:string; const aAlign :TAlign; const aLeft, aTop, aHeight, aWidth :Integer;
             const aBorderStyle:TxcBorderStyle; const aGradientDirect:TxcGradientDirect):TxcGradientPanel;
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TxcGradientPanel(aOwner.FindComponent(aName))
     else 
      Result := TxcGradientPanel.Create(aOwner);
    with Result do
      begin
      if(aName <> '')then 
        Name := aName;
      Parent        := aParent;
      StyleManager  := Amunhotep.MainForm.StyleManager;
      GradientDirect:= aGradientDirect;
      BorderStyle   := aBorderStyle;
      Caption       := aCaption;
      Left          := aLeft;
      Top           := aTop;
      Height        := aHeight;
      Width         := aWidth;
      Align         := aAlign;
      end;
  end;
