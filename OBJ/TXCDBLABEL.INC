{$DEFINE PEAKTOP:OBJ/TXCDBLABEL.INC}
  //====================== PEAKTOP:OBJ/TXCDBLABEL.INC ==========================
  function CreateTxcDBLabel(a_Owner :TComponent; a_Parent:TWinControl; a_DataSource :TDataSource; const a_FieldName:string; 
             const a_Left, a_Top, a_Height, a_Width:Integer; const a_Align:TAlign; const a_Alignment :TAlignment):TxcDBLabel;
  begin
    Result := TxcDBLabel.Create(a_Owner);
    with Result do
      begin
      Parent         := a_Parent;
      AutoSize       := false;
      Font.Color     := Amunhotep_MainForm_StyleManager.Colors.Border;
      HighlightColor := Amunhotep_MainForm_StyleManager.Colors.Window;
      Transparent    := true;
      FlatColor      := Amunhotep.MainForm.StyleManager.Colors.Background;
      FlyByColor     := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
      ShadowColor    := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Left           := a_Left;
      Top            := a_Top;
      Height         := a_Height;
      Width          := a_Width;
      Align          := a_Align;
      Alignment      := a_Alignment;
      Layout         := taMiddle;
      WordWrap       := true;
      DataSource     := a_DataSource;
      DataField      := a_FieldName;
      end; 
  end;
