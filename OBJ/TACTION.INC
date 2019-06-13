{$DEFINE PEAKTOP:OBJ/TACTION.INC}
  //======================== PEAKTOP:OBJ/TACTION.INC ===========================
  function FindTAction(aOwner :TComponent; const aName, aCaption, aHint, aShortCut :string; const aGroupIndex, aImageIndex :Integer):TAction;
  begin
    if(aOwner.FindComponent(aName) = nil)then
      Result := TAction.Create(aOwner)
     else
      Result := TAction(aOwner.FindComponent(aName)); 
    with Result do
      begin  
      Caption    := aCaption;
      Hint       := aHint;
      GroupIndex := aGroupIndex;
      ImageIndex := aImageIndex;
      if(StrTrimAll(aShortCut)<>'')then try ShortCut := TextToShortCut(aShortCut); except end; 
      if(StrTrimAll(aName)    <>'')then try Name     := UpperCase(aName);          except end;
      end;
  end;
  //============================================================================
  function CreateTAction(aOwner :TComponent; const aName, aCaption, aHint, aShortCut:string; const aGroupIndex, aImageIndex :Integer):TCustomAction;
  begin
    Result := FindTAction(aOwner, aName, aCaption, aHint, aShortCut, aGroupIndex, aImageIndex);
  end;

