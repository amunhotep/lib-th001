{$DEFINE PEAKTOP:OBJ/TDBGRIDEH.INC}
  //======================== PEAKTOP:OBJ/TDBGRIDEH.INC =========================
  function CreateTDBGridEh(aOwner :TComponent; aParent:TWinControl; aDataSource :TDataSource; const aObjectName :string;
            const aLeft, aTop, aHeight, aWidth:Integer; const aAlign :TAlign):TDBGridEh;
  begin
    if(aOwner.FindComponent(aObjectName) <> nil)then
      Result := TDBGridEh(aOwner.FindComponent(aObjectName))
     else 
      Result := TDBGridEh.Create(aOwner);
    with Result do
      begin
      if(aObjectName <> '')then
        Name          := aObjectName;
      Parent          := aParent;
      HelpKeyWord     := '0'; // we use it as saved FooterRowCount;
      DrawMemoText    := true;
      with Amunhotep.MainForm.StyleManager.Colors do
        begin
        Color           := Window;
        Font.Color      := Border;
        FixedColor      := Foreground;
        FooterColor     := Foreground;
        FooterFont.Color:= Border;
        TitleFont.Color := Border;
        end;
      FooterFont.Style:= FooterFont.Style + [fsBold];
      TitleFont.Style := TitleFont.Style  + [fsBold];
      Ctl3D           := false;
      Flat            := true;
      {$IFDEF AMUNHOTEP4832}
      OptionsEh       := OptionsEh + [dghFixed3D, dghFrozen3D,{dghIncSearch,} dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, dghExtendVertLines, dghHotTrack];
      {$ELSE}
      OptionsEh       := OptionsEh + [dghFixed3D, dghFrozen3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, dghExtendVertLines, dghHotTrack];
      {$ENDIF}
      Left            := aLeft;
      Top             := aTop;
      Height          := aHeight;
      Width           := aWidth;
      Align           := aAlign;
      DataSource      := aDataSource;
      UseMultiTitle   := true;
      ShowHint        := true;
      VTitleMargin    := 4;
      {$IFDEF AMUNHOTEP4832}
      SearchPanel.FilterOnTyping  := True;
      IndicatorParams.FillStyle   := cfstGradientEh;
      FooterParams.FillStyle      := cfstGradientEh;
      TitleParams.SortMarkerStyle := smstClassicEh;
      TitleParams.Color           := FixedColor;
      TitleParams.SecondColor     := Color;
      TitleParams.FillStyle       := cfstGradientEh;
      {$ENDIF}
      end;
  end;
