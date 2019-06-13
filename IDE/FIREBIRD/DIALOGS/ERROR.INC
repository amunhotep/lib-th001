{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/ERROR.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}               {$I PEAKTOP:GLOBAL_VARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/$SETTINGS.INC} {$I ./$SETTINGS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/LANG.INC}      {$I ./LANG.INC}                   {$ENDIF}
  //============= PEAKTOP:IDE/FIREBIRD/DIALOGS/ERROR.INC =======================
  function FirebirdDialog_Error_Execute(const ErrorMessage:string):Boolean;
  var
    lkForm        :TForm;
    lkPanelClient :TxcGradientPanel;
    lkLabel       :TLabel;
    lkImg         :TImage;
    lkPanelBottom :TxcStdPanel;
    lkBtnOk       :TxcButton; 
    lkFileName    :string;
    lkStrm        :TMemoryStream;
  begin
    Result := false;
    lkForm := TForm.Create(nil);
    with lkForm do
      begin
      Caption         := msg_firebird_dialog_error_caption;
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderStyle     := bsDialog;
      BorderIcons     := [biSystemMenu];
      AlphaBlendValue := 232;
      AlphaBlend      := true;
      Position        := poScreenCenter;
      Width           := Trunc(Screen.Width * 2 / 3);
      Height          := DefaultFirebirdDialogErrorHeight;
      end;
    lkPanelClient := TxcGradientPanel.Create(lkForm);
    with lkPanelClient do
      begin
      Parent         := lkForm;
      Align          := alClient;
      Height         := 98;
      BorderStyle    := xbsNone;
      GradientDirect := gdTopToBottom;
      StyleManager   := Amunhotep.MainForm.StyleManager;
      end;
    lkFileName := PrepareAbsoleteFileName(DefaultFirebirdDialogImageLogoError);  
    lkImg := TImage.Create(lkForm);
    with lkImg do
      begin
      Parent       := lkPanelClient;
      Align        := alLeft;
      Width        := 160;
      Transparent  := true;
      Proportional := true;
      if FileExists(lkFileName)then
        try
          lkStrm  := TMemoryStream.Create;
          if StreamLoadFromFile(lkFileName, lkStrm)then
            Picture.Bitmap.LoadFromStream(lkStrm);
        finally    
          lkStrm.Free;
        end;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      Align       := alClient;
      Transparent := true;
      Caption     := ErrorMessage;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      WordWrap    := true;
      end;
    lkPanelBottom := TxcStdPanel.Create(lkForm);
    with lkPanelBottom do
      begin
      Parent       := lkForm;
      Height       := 24;
      Width        := lkForm.ClientWidth;
      Align        := alBottom;
      BorderStyle  := xbsNone;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      end;
    lkBtnOk := TxcButton.Create(lkForm); 
    with lkBtnOk do
      begin
      Parent       := lkPanelBottom;
      Width        := 96;
      Left         := lkPanelBottom.Width - lkBtnOk.Width - 2;
      Top          := 2;
      Height       := lkPanelBottom.Height - 4;
      Caption      := msg_firebird_dialog_button_caption_ok;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Default      := true;
      Font.Name    := 'Verdana';
      Font.Size    := DefaultFirebirdDialogButtonFontHeight;
      Font.Style   := [fsBold];
      ModalResult  := mrOk;
      end;
    lkForm.ShowModal;
    lkForm.Free;
    Result := true;
  end;
