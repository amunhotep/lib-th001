{$DEFINE PEAKTOP:OBJ/TIMAGE_LOGO.INC}
  //====================== PEAKTOP:OBJ/TIMAGE_LOGO.INC =========================
  function CreateTImageLogo(aOwner:TComponent; aParent:TWinControl; const aName:string; const aAlign :TAlign; 
             const aLeft, aTop, aHeight, aWidth :Integer;
             const aResourceFileName:string):TImage;
  var
    lkCmp  :TComponent;
    lkStrm :TMemoryStream;
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
      if FileExists(aResourceFileName)then
        try
          lkStrm  := TMemoryStream.Create;
          if StreamLoadFromFile(aResourceFileName, lkStrm)then
            Picture.Bitmap.LoadFromStream(lkStrm);
        finally    
          lkStrm.Free;
        end;  
      end;
  end;
