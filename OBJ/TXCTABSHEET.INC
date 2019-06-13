{$DEFINE PEAKTOP:OBJ/TXCTABSHEET.INC}
  //====================== PEAKTOP:OBJ/TXCTABSHEET.INC =========================
  function CreateTxcTabSheet(aPageControl:TxcPageControlEx; const aName, aCaption:string; const aImageIndex :Integer; const aColor:TColor):TxcTabSheet;
  begin
    if(aPageControl.FindComponent(aName) <> nil)then
      Result := TxcTabSheet(aPageControl.FindComponent(aName))
     else 
      Result := TxcTabSheet.Create(aPageControl);
    with Result do
      begin
      if(StrTrimAll(aName) <> '')then
        Name      := aName;
      Parent      := aPageControl;
      PageControl := aPageControl;
      Caption     := aCaption;
      ImageIndex  := aImageIndex;
      Color       := aColor;
      end;  
  end;
