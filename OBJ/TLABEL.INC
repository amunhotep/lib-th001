{$DEFINE PEAKTOP:OBJ/TLABEL.INC}
  //======================== PEAKTOP:OBJ/TLABEL.INC ============================
  function CreateTLabel(aOwner :TComponent; aParent:TWinControl; const aCaption:string; const aLeft, aTop, aHeight, aWidth:Integer;
              const aAlign:TAlign; const aAlignment :TAlignment):TLabel;
  begin
    Result := TLabel.Create(aOwner);
    with Result do
      begin
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
