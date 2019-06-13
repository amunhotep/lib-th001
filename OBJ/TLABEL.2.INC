{$DEFINE PEAKTOP:OBJ/TLABEL.2.INC}
  //======================== PEAKTOP:OBJ/TLABEL.2.INC ============================
  function CreateTLabel2(aOwner :TComponent; aParent:TWinControl; const aName, aCaption:string; const aLeft, aTop, aHeight, aWidth:Integer;
              const aAlign:TAlign; const aAlignment :TAlignment):TLabel;
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TLabel(aOwner.FindComponent(aName))
     else 
      Result := TLabel.Create(aOwner);
    with Result do
      begin
      Name       := aName;
      Parent     := aParent;
      AutoSize   := false;
      Caption    := aCaption;
      Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      Transparent:= true;
      Left       := aLeft;
      Top        := aTop;
      Height     := aHeight;
      Width      := aWidth;
      Align      := aAlign;
      Alignment  := aAlignment;
      Layout     := taMiddle;
      end; 
  end;
