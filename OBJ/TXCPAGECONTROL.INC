{$DEFINE PEAKTOP:OBJ/TXCPAGECONTROL.INC}
  //======================= PEAKTOP:OBJ/TXCPAGECONTROL.INC =====================
  function CreateTxcPageControl(aOwner:TComponent; aParent:TWinControl; const aName :string; const aLeft,aTop,aWidth,aHeight:Integer; const aAlign :TAlign):TxcPageControl;
  begin
    Result := TxcPageControl(aOwner.FindComponent(aName));
    if(Result = nil)then Result := TxcPageControl.Create(aOwner);
    with Result do
      begin
      Name         := aName;
      Parent       := aParent;
      Left         := aLeft;
      Top          := aTop;
      Height       := aHeight;
      Width        := aWidth;
      Align        := aAlign;
      StyleManager := Amunhotep.MainForm.StyleManager; 
      end;
  end;
