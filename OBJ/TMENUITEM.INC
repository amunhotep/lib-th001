{$DEFINE PEAKTOP:OBJ/TMENUITEM.INC}
  //=================== PEAKTOP:OBJ/TMENUITEM.INC ==============================
  function CreateFindTMenuItem(aParentItem :TMenuItem;const aName:string; const aNewIndex:Integer):TMenuItem;
  var
    i :Integer;
  begin
    Result := nil;
    for i:=0 to aParentItem.Count-1 do
      if(UpperCase(aParentItem.Items[i].Name) = UpperCase(aName))then
        begin
        Result := aParentItem.Items[i];
        exit;
        end;
    for i:=0 to aParentItem.ComponentCount-1 do
      if(UpperCase(aParentItem.Components[i].Name) = UpperCase(aName))then
        begin
        Result := TMenuItem(aParentItem.Components[i]);
        exit;
        end;
    Result := TMenuItem.Create(aParentItem);
    Result.Name := aName;  
    if(aNewIndex > -1)then
      aParentItem.Insert(aNewIndex, Result)     
     else  
      aParentItem.Add(Result);
    Amunhotep.MainForm.xcMenu.AssignMethods(Result);
  end;
  //============================================================================
  function CreateTMenuItem(aParentItem :TMenuItem;const aName, aCaption, aHint, aShortCut:string; aImageIndex, aGroupIndex :Integer):TMenuItem;
  begin
    Result := CreateFindTMenuItem(aParentItem, aName, -1); 
    with Result do
      begin
      if(aName <> '')then
        Name     := aName;
      Caption    := aCaption;
      Hint       := aHint;
      ImageIndex := aImageIndex;
      GroupIndex := aGroupIndex;
      Visible    := true; 
      try ShortCut := TextToShortCut(aShortCut); finally end;
      end;
  end;
  //============================================================================
  function CreateTMenuItemLine(aParentItem :TMenuItem;const aName:string):TMenuItem;
  begin
    Result := CreateTMenuItem(aParentItem, aName,'-','','',-1,0);
  end;
  //============================================================================
  function CreateTMenuItem2(aParentItem :TMenuItem; aAction:TCustomAction):TMenuItem;
  begin
    Result := CreateFindTMenuItem(aParentItem, 'mi_'+aAction.Name, -1); 
    Result.Action := aAction;
    if(aAction.Name <> '')then
      Result.Name := 'mi_'+aAction.Name;
  end;
  //============================================================================
  function CreateTMenuItemIns(aParentItem :TMenuItem;const aName, aCaption, aHint, aShortCut:string; aImageIndex, aGroupIndex, aInsertIndex :Integer):TMenuItem;
  begin
    Result := CreateFindTMenuItem(aParentItem, aName, aInsertIndex); 
    with Result do
      begin
      Name       := aName;
      Caption    := aCaption;
      Hint       := aHint;
      ImageIndex := aImageIndex;
      GroupIndex := aGroupIndex;
      Visible    := true; 
      try ShortCut := TextToShortCut(aShortCut); finally end;
      end;
  end;
