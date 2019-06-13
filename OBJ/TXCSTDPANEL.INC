{$DEFINE PEAKTOP:OBJ/TXCSTDPANEL.INC}
  //==================== PEAKTOP:OBJ/TXCSTDPANEL.INC ===========================
  function CreateTxcStdPanel(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; const aAlign :TAlign;
             const aLeft, aTop, aHeight, aWidth :Integer; const aBorderStyle:TxcBorderStyle):TxcStdPanel;
  begin
    Result := TxcStdPanel.Create(aOwner);
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
