{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/CUSTOM.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}               {$I PEAKTOP:GLOBAL_VARIABLES.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGE.INC}                     {$I PEAKTOP:OBJ/TIMAGE.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                     {$I PEAKTOP:OBJ/TLABEL.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCBUTTON.INC}                  {$I PEAKTOP:OBJ/TXCBUTTON.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}           {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}      {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/$SETTINGS.INC} {$I ./$SETTINGS.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/OBJNAMES.INC}  {$I ./OBJNAMES.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/LANG.INC}      {$I ./LANG.INC}                           {$ENDIF}
  //===================== PEAKTOP:IDE/FIREBIRD/DIALOGS/CUSTOM.INC ==============
  function FirebirdDialog_Create(const aCaption, aBtnOkCaption, aBtnCancelCaption:string):TForm;
  var
    lkPanelClient :TxcGradientPanel;
    lkTopBar      :TxcGradientPanelVista;
    lkImg         :TImage;
    lkPanelBottom :TxcStdPanel;
    lkLblVersion  :TLabel;
    lkBtnOk       :TxcButton; 
    lkBtnCancel   :TxcButton;
    lkFileName    :string; 
    lkStrm        :TMemoryStream;
  begin
    Result := TForm.Create(nil);
    with Result do
      begin
      Caption         := Amunhotep.Title;
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderStyle     := bsDialog;
      BorderIcons     := [biSystemMenu];
{$IFDEF TRANSPARENT}  
      AlphaBlendValue := 232;
      AlphaBlend      := true;
{$ENDIF}  
      Position        := poScreenCenter;
      Width           := DefaultFirebirdDialogWidth;
      Height          := DefaultFirebirdDialogHeight;
      Font.Size       := DefaultFirebirdDialogLabelFontHeight;
      end;
    lkTopBar      := CreateTxcGradientPanelVista(Result, Result,'PanelTop', #$20+aCaption,alTop,0,0,34,98,xbsRaized);
    with lkTopBar do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := $6060E0;
      Colors.Background     := $000020;
      Colors.Border         := $000020;
      Colors.HotTrackBorder := $0000C0;
      end;  
    lkPanelClient := CreateTxcGradientPanel(Result, Result,'PanelClient','',alClient,0,0,200,98,xbsNone  ,gdTopToBottom);  
    lkImg         := CreateTImage(Result, lkPanelClient, 'ImageLogo', alLeft, 0,0,100,160); 
    lkFileName    := PrepareAbsoleteFileName(DefaultFirebirdDialogImageLogoLeft);
    if FileExists(lkFileName)then
      try
        lkStrm  := TMemoryStream.Create;
        if StreamLoadFromFile(lkFileName, lkStrm)then
          if(lkStrm.Size > 0)then
           lkImg.Picture.Bitmap.LoadFromStream(lkStrm);
      finally    
        lkStrm.Free;
      end;
    lkPanelBottom := TxcStdPanel.Create(Result);
    with lkPanelBottom do
      begin
      Name         := 'PanelBottom';
      Parent       := Result;
      Height       := 28;
      Width        := Result.ClientWidth;
      Align        := alBottom;
      BorderStyle  := xbsNone;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      end;
    lkFileName := ' '+msg_firebird_dialog_amunhotep_version+
        IntToStr(Trunc(Amunhotep.Version / 1000))+'.'+                        // major
        FormatFloat('0'   ,Trunc(Frac(Amunhotep.Version / 1000) *  10) )+'.'+ // minor
        FormatFloat('00'  ,     (Frac(Amunhotep.Version /  100) * 100) )+'.'+ // patch
        FormatFloat('0000',Amunhotep.Version);                                // build
    lkLblVersion := CreateTLabel(Result, lkPanelBottom, lkFileName, 0,0, 20, 132,alLeft, taLeftJustify);
    lkLblVersion.AutoSize   := true;
    lkLblVersion.Font.Style := [fsBold];  
    lkBtnCancel := CreateTxcButton(Result,lkPanelBottom,'btnCancel',aBtnCancelCaption,lkPanelBottom.Width - 142,2,lkPanelBottom.Height-4,140,mrCancel,false,true );
    lkBtnCancel.Font.Style := [fsBold];
    lkBtnCancel.TabOrder   := 2;
    lkBtnCancel.Anchors    := [akRight, akBottom]  
    lkBtnOk     := CreateTxcButton(Result,lkPanelBottom,'btnOk'    ,aBtnOkCaption    ,lkBtnCancel.Left - 142   ,2,lkPanelBottom.Height-4,140,mrOk    ,true ,false);
    lkBtnOk.Font.Style     := [fsBold];
    lkBtnOk.TabOrder       := 1;
    lkBtnOk.Anchors        := [akRight, akBottom]  
  end;
