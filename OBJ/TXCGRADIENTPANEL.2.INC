{$DEFINE PEAKTOP:OBJ/TXCGRADIENTPANEL.2.INC}
  //==================== PEAKTOP:OBJ/TXCGRADIENTPANEL.2.INC ====================
  function CreateTxcGradientPanel(aOwner:TComponent; aParent :TWinControl; const aName, aCaption:string; const aAlign :TAlign; const aAlignment :TAlignment;
             const aLeft, aTop, aHeight, aWidth :Integer; const aBorderStyle:TxcBorderStyle; const aGradientDirect:TxcGradientDirect):TxcGradientPanel;
  begin
    Result := nil;
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TxcGradientPanel(aOwner.FindComponent(aName))
     else 
      Result := TxcGradientPanel.Create(aOwner);
    with Result do
      begin  
      Visible := false;  
      Parent  := aParent;
      if(aName <> '')then 
        Name := aName;
      StyleManager  := Amunhotep.MainForm.StyleManager;
      GradientDirect:= aGradientDirect;
      BorderStyle   := aBorderStyle;
      Alignment     := aAlignment;
      Caption       := aCaption;
      Left          := aLeft;
      Top           := aTop;
      Height        := aHeight;
      Width         := aWidth;
      Align         := aAlign;
      Visible       := true;
      end;  
  end;
