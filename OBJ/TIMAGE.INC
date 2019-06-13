{$DEFINE PEAKTOP:OBJ/TIMAGE.INC}
  //====================== PEAKTOP:OBJ/TIMAGE.INC ==============================
  function CreateTImage(aOwner:TComponent; aParent:TWinControl; const aName:string; const aAlign :TAlign; const aLeft, aTop, aHeight, aWidth :Integer):TImage;
  var
    lkCmp:TComponent;
  begin
    lkCmp := aOwner.FindComponent(aName);
    if(lkCmp = nil)then
      Result := TImage.Create(aOwner)
     else
      Result := TImage(lkCmp); 
    with Result do
      begin
      if(aName <> '')then 
        Name      := aName;
      Parent      := aParent;
      Left        := aLeft;
      Top         := aTop;
      Height      := aHeight;
      Width       := aWidth;
      Align       := aAlign;
      Transparent := true;
      Center      := true;
      Stretch     := true;
      Proportional:= true;
      end;
  end;
