{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}               {$I PEAKTOP:GLOBAL_VARIABLES.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGE.INC}                     {$I PEAKTOP:OBJ/TIMAGE.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCBUTTON.INC}                  {$I PEAKTOP:OBJ/TXCBUTTON.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}           {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}      {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}{$ENDIF}
  //============================================================================
  function ERP_DialogCommon_LastLeft(aControl :TWinControl):Integer;
  var
    i :Integer;
  begin
    Result := 0;
    for i:=0 to aControl.ControlCount-1 do
      Result := Result + aControl.Controls[i].Width + 4;
  end;
  //============================================================================
  function ERP_DialogCommonCreate(
             const aCaption, aTopBarCaption, aImgLogoFileName, aImgLeftFileName:string;
             const aWidth, aHeight, aLeftImgWidth :Integer;
             const aModalResults    :array of TModalResult;
             const aButtonsCaptions :array of TCaption
             ):TForm;
  var
    lkTopBar      :TxcGradientPanelVista;
    lkImgLogo     :TImage;
    lkImgLeft     :TImage;
    lkPanelClient :TxcGradientPanel;
    lkPanelBottom :TxcStdPanel;
    lkBtn         :TxcButton;
    lkFileName    :string; 
    lkStrm        :TMemoryStream;
    lkBmp         :TBitmap;
    i             :Integer;
  begin
    Result := TForm.Create(nil);
    with Result do
      begin
      Caption         := aCaption;
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderIcons     := [biSystemMenu];
      AlphaBlendValue := 244;
      AlphaBlend      := true;
      Width           := aWidth;
      Height          := aHeight;
      Font.Color      := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Size       := 7;
      end;
    if(aTopBarCaption <> '')then
      begin 
      lkTopBar := CreateTxcGradientPanelVista(Result, Result,'TopBar', #$20+aTopBarCaption,alTop,0,0,34,98,xbsRaized);
      if(aImgLogoFileName <> '')then
        begin
        lkFileName := PrepareAbsoleteFileName(aImgLogoFileName);
        if FileExists(lkFileName)then
          try
            lkImgLogo := CreateTImage(Result, lkTopBar, 'ImgLogo', alLeft, 0, 0, 33, 34);
            lkStrm  := TMemoryStream.Create;
            if StreamLoadFromFile(lkFileName, lkStrm)then
              if(lkStrm.Size > 0)then
                begin
                lkImgLogo.Picture.Bitmap.LoadFromStream(lkStrm);
                lkTopBar.Caption := #$20#$20#$20#$20#$20 + lkTopBar.Caption;
                end;
          finally    
            lkStrm.Free;
          end;
        end; 
      end;  
    lkPanelClient := CreateTxcGradientPanel(Result, Result,'PanelClient','',alClient,0,0,200,98,xbsNone  ,gdTopToBottom);
    if(aImgLeftFileName <> '')then
      begin  
      lkFileName := PrepareAbsoleteFileName(aImgLeftFileName);
      if FileExists(lkFileName)then
        try
          lkImgLeft := CreateTImage(Result, lkPanelClient, 'ImgLeft', alLeft, 0, 0, 1, aLeftImgWidth);
          lkStrm  := TMemoryStream.Create;
          if StreamLoadFromFile(lkFileName, lkStrm)then
            if(lkStrm.Size > 0)then
             lkImgLeft.Picture.Bitmap.LoadFromStream(lkStrm);
        finally    
          lkStrm.Free;
        end;
      end;
    lkPanelBottom := TxcStdPanel.Create(Result);
    with lkPanelBottom do
      begin
      Name         := 'PanelBottom';
      Parent       := Result;
      Height       := 24;
      Width        := Result.ClientWidth;
      Align        := alBottom;
      BorderStyle  := xbsNone;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      end;
    lkBmp := TBitmap.Create;
    with lkBmp do
      begin
      Height := lkPanelBottom.Height - 4;
      Width  := lkPanelBottom.Width;
      with Canvas do
        begin
        Font.Name  := Result.Font.Name;  
        Font.Size  := 7;
        Font.Style := [fsBold];
        end;
      end; 
    for i:=Length(aModalResults)-1 downto 0 do
      begin
      lkBtn := TxcButton.Create(Result);
      with lkBtn do
        begin
        Parent       := lkPanelBottom;
        Caption      := aButtonsCaptions[i];
        StyleManager := Amunhotep_MainForm_StyleManager;
        Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
        Font.Size    := 7;
        Font.Style   := [fsBold];
        Width        := lkBmp.Canvas.TextWidth(aButtonsCaptions[i]) + 48;
        Left         := lkPanelBottom.Width - ERP_DialogCommon_LastLeft(lkPanelBottom);
        Top          := 2;
        Height       := lkPanelBottom.Height - 4;
        Anchors      := [akRight, akBottom]  
        ModalResult  := aModalResults[i];
        Default      := (i = 0);
        Cancel       := (aModalResults[i] = mrCancel);
        if Default then
          Result.ActiveControl := lkBtn;
        end;
      end;
    lkBmp.Free;    
  end;
