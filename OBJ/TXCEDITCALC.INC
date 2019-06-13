{$DEFINE PEAKTOP:OBJ/TXCEDITCALC.INC}
  //==================== PEAKTOP:OBJ/TXCEDITCALC.INC ===========================
  function CreateTxcEditCalc(aOwner :TComponent; aParent:TWinControl; const aName:string; const aLeft, aTop, aHeight, aWidth:Integer):TxcEditCalc;
  var
    lkCmp :TComponent;
  begin
    lkCmp := aOwner.FindComponent(aName);
    if(lkCmp <> nil)then
      Result := TxcEditCalc(lkCmp)
     else 
      Result := TxcEditCalc.Create(aOwner);
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
  function FindTxcEditCalc(aOwner :TComponent; const aName:string):TxcEditCalc;
  begin
    Result := TxcEditCalc(aOwner.FindComponent(aName));
    if(Result <> nil)then
      begin
      Result.Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
      Result.Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      end;
  end;
