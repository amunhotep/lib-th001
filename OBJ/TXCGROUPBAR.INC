{$DEFINE PEAKTOP:OBJ/TXCGROUPBAR.INC}
  //============================================================================
  function CreateTxcGroupBar(aOwner:TComponent; aParent:TWinControl; 
             const aName:string; 
             const aLeft, aTop, aHeight, aWidth:Integer;
             const aAlign:TAlign;
             const aGradientDirect :TxcGradientDirect;
             const aItemHeight, aMargin :Integer
           ):TxcGroupBar;
  var
    i :Integer;
  begin
    Result := nil;
    for i:=0 to aOwner.ComponentCount-1 do
      if(UpperCase(aOwner.Components[i].Name) = UpperCase(aName))then
        begin
        Result := TxcGroupBar(aOwner.Components[i]);
        break;  
        end;
    if(Result = nil)then    
      Result := TxcGroupBar.Create(aOwner);
    with Result do
      begin
      if(StrTrimAll(aName) <> '')then  
        Name         := aName;
      Parent         := aParent;
      Left           := aLeft;
      Top            := aTop;
      Width          := aWidth;
      Height         := aHeight;
      Align          := aAlign;
      GradientDirect := aGradientDirect;
      Gradient       := Amunhotep.MainForm.StyleManager.Gradient;
      Images         := Amunhotep.MainForm.ImageListMain;
      StyleManager   := Amunhotep.MainForm.StyleManager;
      Font.Name      := Amunhotep.MainForm.xcMenu.FontNormal.Name;
      Font.Size      := Amunhotep.MainForm.xcMenu.FontNormal.Size;
      Font.Style     := [fsBold];
      ItemHeight     := aItemHeight;
      Margin         := aMargin;
      end;
  end;
  //============================================================================
  function TxcGroupBar_AddGroupPanel(aGroupBar :TxcGroupBar; const aName,aCaption :string; const aImageIndex:Integer):TxcGroupPanel;
  var
    i :Integer;
  begin
    Result := nil;
    for i:=0 to aGroupBar.GroupPanelsCount-1 do
      if(UpperCase(aGroupBar.GroupPanels[i].Name) = UpperCase(aName))then
        begin
        Result := aGroupBar.GroupPanels[i];
        break;
        end;
    if(Result = nil)then
      Result := aGroupBar.AddGroupPanel(aCaption);
    with Result do
      begin
      if(StrTrimAll(aName) <> '')then  
        Name     := aName;
      ImageIndex := aImageIndex;
      end;
  end;
