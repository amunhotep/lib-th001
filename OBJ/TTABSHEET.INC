{$DEFINE PEAKTOP:OBJ/TTABSHEET.INC}
  //====================== PEAKTOP:OBJ/TTABSHEET.INC ===========================
  function CreateTTabSheet(aPageControl:TPageControl; const aName, aCaption:string):TTabSheet;
  begin
    Result := TTabSheet.Create(aPageControl);
    with Result do
      begin
      Parent      := aPageControl;
      PageControl := aPageControl;
      Name        := aName;
      Caption     := aCaption;
      end;  
  end;
