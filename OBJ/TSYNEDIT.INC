{$DEFINE PEAKTOP:OBJ/TSYNEDIT.INC}
  //============================================================================
  function CreateTSynEdit(aOwner :TComponent; aParent :TWinControl; aName:string; aFileType :TFileType):TSynEdit;
  begin
    Result := TSynEdit.Create(aOwner);
    with Result do
      begin
      Parent     := aParent;
      Align      := alClient;
      Ctl3D      := false;
      Lines.Text := '';
      ActiveLineColor           := Amunhotep.MainForm.StyleManager.Colors.HotTrack;
      Color                     := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color                := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Size                 := 8;
      SelectedColor.Background  := Amunhotep.MainForm.StyleManager.EditorSelectColor;
      SelectedColor.Foreground  := Amunhotep.MainForm.StyleManager.Colors.Window;
      TabWidth                  := 2;
      with Gutter do
        begin
        AutoSize           := true;
        Color              := Amunhotep.MainForm.StyleManager.Colors.Foreground;
        BorderColor        := Amunhotep.MainForm.StyleManager.Colors.Border;
        BorderStyle        := gbsRight;
        GradientStartColor := Amunhotep.MainForm.StyleManager.Colors.Window;
        GradientEndColor   := Amunhotep.MainForm.StyleManager.Colors.Foreground;
        Gradient           := Amunhotep.MainForm.StyleManager.Gradient;
        Font.Color         := Amunhotep.MainForm.StyleManager.Colors.Border;
        Font.Name          := 'Verdana';
        Font.Size          := 7;
        Font.Style         := [fsBold];
        DigitCount         := 8;
        LeadingZeros       := true;
        LeftOffset         := 0;
        RightOffset        := 0;
        ShowLineNumbers    := true;
        Width              := 0;
        ZeroStart          := false;
        end;
      end;
    if(aFileType <> ftText)then
      RegisterSynEdit(Result, aFileType);  
  end;
