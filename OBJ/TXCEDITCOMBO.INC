{$DEFINE PEAKTOP:OBJ/TXCEDITCOMBO.INC}
  //=================== PEAKTOP:OBJ/TXCEDITCOMBO.INC ===========================
  function CreateTxcEditCombo(aOwner :TComponent; aParent:TWinControl; const aName:string; const aLeft, aTop, aHeight, aWidth:Integer):TxcEditCombo;
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TxcEditCombo(aOwner.FindComponent(aName))
     else 
      Result := TxcEditCombo.Create(aOwner);
    with Result do
      begin
      Name       := aName;
      Parent     := aParent;
      Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
      Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      Ctl3D      := false;
      Left       := aLeft;
      Top        := aTop;
      Height     := aHeight;
      Width      := aWidth;
      Text       := '';
      end;
  end;
  //============================================================================
  function FindTxcEditCombo(aOwner :TComponent; const aName:string):TxcEditCombo;
  begin
    Result := nil;
    if(aOwner.FindComponent(aName) = nil)then exit;
    Result := TxcEditCombo(aOwner.FindComponent(aName));
    with Result do
      begin
      Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
      Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      end;
  end;
