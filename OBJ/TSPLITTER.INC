{$DEFINE PEAKTOP:OBJ/TSPLITTER.INC}
  //======================= PEAKTOP:OBJ/TSPLITTER.INC ==========================
  function CreateTSplitter(aOwner:TComponent; aParent:TWinControl; const aName:string; const aAlign :TAlign; const aLeft, aTop, aHeight, aWidth :Integer):TSplitter;
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TSplitter(aOwner.FindComponent(aName))
     else 
      Result := TSplitter.Create(aOwner);
    with Result do
      begin
      if(StrTrimAll(aName) <> '')then
        Name := aName;
      Parent := aParent;
      Color  := Amunhotep_MainForm_StyleManager.Colors.Foreground;
      Align  := alNone;
      Left   := aLeft; 
      Top    := aTop; 
      Height := aHeight; 
      Width  := aWidth; 
      Align  := aAlign;
      end;
  end;  
