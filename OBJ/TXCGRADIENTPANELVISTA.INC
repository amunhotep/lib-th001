{$DEFINE PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}
  //===================== PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC ================
  procedure TxcGradientPanelVista_SetColorsToolBar(aPanel :TxcGradientPanelVista);
  begin
    with aPanel do
      begin
      Font.Size    := 7;
      Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
      StyleManager := nil;
      with Amunhotep.MainForm.StyleManager.Colors do
        begin
        Colors.HotTrack       := Window;
        Colors.Background     := Foreground + $202020;
        Colors.Border         := Background + $404040;
        Colors.HotTrackBorder := Foreground + $202020;
        end;
      end;
  end;  
  //============================================================================
  function CreateTxcGradientPanelVista(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; const aAlign :TAlign;
             const aLeft, aTop, aHeight, aWidth :Integer; const aBorderStyle:TxcBorderStyle):TxcGradientPanelVista;
  begin
    if(aOwner.FindComponent(aName) = nil)then
      Result := TxcGradientPanelVista.Create(aOwner)
     else 
      Result := TxcGradientPanelVista(aOwner.FindComponent(aName));
    with Result do
      begin
      if(aName<>'')then 
        Name := aName;
      Parent := aParent;
      SetBounds(aLeft, aTop, aWidth, aHeight);
      StyleManager  := Amunhotep.MainForm.StyleManager;
      BorderStyle   := aBorderStyle;
      Caption       := aCaption;
      Align         := aAlign;
      Font.Name     := 'Verdana';
      Font.Size     := 14;
      Font.Style    := [fsBold];
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Window;
      end;
  end;
  //============================================================================
  function CreateTxcGradientPanelVistaToolBar(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; 
             const aAlign :TAlign; const aLeft, aTop, aHeight, aWidth :Integer;  const aBorderStyle:TxcBorderStyle):TxcGradientPanelVista;
  begin
    Result := CreateTxcGradientPanelVista(aOwner, aParent, aName, aCaption, aAlign, aLeft, aTop, aHeight, aWidth, aBorderStyle);
    TxcGradientPanelVista_SetColorsToolBar(Result);
  end;  
