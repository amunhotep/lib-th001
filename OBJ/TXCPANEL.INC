{$DEFINE PEAKTOP:OBJ/TXCPANEL.INC}
  //==================== PEAKTOP:OBJ/TXCPANEL.INC ==============================
  function CreateTxcPanel(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; const aAlign :TAlign;
             const aLeft, aTop, aHeight, aWidth :Integer; const aBorderStyle:TxcBorderStyle):TxcPanel;
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TxcPanel(aOwner.FindComponent(aName))
     else
      Result := TxcPanel.Create(aOwner);
    with Result do
      begin
      if(aName <> '')then 
        Name       := aName;
      Parent       := aParent;
      StyleManager := Amunhotep.MainForm.StyleManager;
      BorderStyle  := aBorderStyle;
      Caption      := aCaption;
      Left         := aLeft;
      Top          := aTop;
      Height       := aHeight;
      Width        := aWidth;
      Align        := aAlign;
      end;
  end;
