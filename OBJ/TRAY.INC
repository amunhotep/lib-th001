{$DEFINE PEAKTOP:OBJ/TRAY.INC}
{$DEFINE PEAKTOP:OBJ/TRAY.INC:20110301}
  //======================== PEAKTOP:OBJ/TRAY.INC ==============================
  function CreateTray(const aPanelName, aPanelCaption, aPanelHint:string):TxcToolBarButton;
  var
    i     :Integer;
    Parnt :TxcGradientPanel;
  begin
    Result := nil;
    for i:=0 to Amunhotep.MainForm.ComponentCount-1 do
      if(UpperCase(Amunhotep.MainForm.Components[i].ClassName) = 'TXCGRADIENTPANEL')then
        if(UpperCase(Amunhotep.MainForm.Components[i].Name) = 'STATUSPANEL')then
          begin
          Parnt := TxcGradientPanel(Amunhotep_MainForm.Components[i]);
          break;
          end;
    Parnt.Height := 20;      
    for i:=0 to Parnt.ComponentCount-1 do
      if(UpperCase(Parnt.Components[i].ClassName) = 'TXCTOOLBARBUTTON')then
        if(UpperCase(Parnt.Components[i].Name) = UpperCase(aPanelName))then
          begin
          Result := TxcToolBarButton(Parnt.Components[i]);
          break;
          end;
    if(Result = nil)then      
      Result := TxcToolBarButton.Create(Parnt);
    with Result do
      begin  
      Parent         := Parnt;
      Name           := aPanelName;
      Width          := 64;
      Left           := 0;
      Align          := alRight;
      Caption        := aPanelCaption;
      Hint           := aPanelHint;
      ShowHint       := true;
      StyleManager   := Amunhotep.MainForm.StyleManager;
      ImagesSmall    := Amunhotep.MainForm.ImageListMain;
      ImageIndex     := -1; 
      end;
  end;
  //============================================================================
  procedure DestroyTray(const aPanelName:string);
  var
    i     :Integer;
    Parnt :TxcGradientPanel;
  begin
    for i:=0 to Amunhotep.MainForm.ComponentCount-1 do
      if(AnsiUpperCase(Amunhotep.MainForm.Components[i].ClassName) = 'TXCGRADIENTPANEL')then
        if(AnsiUpperCase(Amunhotep.MainForm.Components[i].Name) = 'STATUSPANEL')then
          begin
          Parnt := TxcGradientPanel(Amunhotep.MainForm.Components[i]);
          break;
          end;
    for i:=0 to Parnt.ComponentCount-1 do
      if(UpperCase(Parnt.Components[i].ClassName) = 'TXCTOOLBARBUTTON')then
        if(UpperCase(Parnt.Components[i].Name) = UpperCase(aPanelName))then
          begin
          Parnt.Components[i].Free;
          break;
          end;
  end;    
