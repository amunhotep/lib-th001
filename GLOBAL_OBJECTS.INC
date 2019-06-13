{$DEFINE PEAKTOP:GLOBAL_OBJECTS.INC}
  //======================= PEAKTOP:GLOBAL_OBJECTS.INC =========================
  function GlobalObjects_Exists(const aName:string; var AnObjectIndex :Integer):Boolean;
  begin
    AnObjectIndex := GlobalObjects.IndexOf(aName);
    Result := (AnObjectIndex > -1);
  end;
  //============================================================================
  function GlobalObjects_Find(const aName:string):TObject;
  var
    lkIndx :Integer;
  begin
    Result := nil;
    if GlobalObjects_Exists(aName, lkIndx)then
      Result := GlobalObjects.Objects[lkIndx];
  end;
  //============================================================================
  function GlobalObjects_Add(const aName:string; AnObject :TObject):Integer;
  begin
    if GlobalObjects_Exists(aName, Result)then
      GlobalObjects.Objects[Result] := AnObject
     else
      Result := GlobalObjects.AddObject(aName, AnObject);
  end;
  //============================================================================
  procedure GlobalObjects_Delete(const aName:string);
  var
    lkIndx :Integer;
  begin
    if GlobalObjects_Exists(aName, lkIndx)then
      GlobalObjects.Delete(lkIndx);
  end;
