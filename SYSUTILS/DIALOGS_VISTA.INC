{$DEFINE PEAKTOP:SYSUTILS/DIALOGS_VISTA.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}    {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
const{$IFDEF LANGUAGE_UKR}
  msg_dialog_vista_btn_expand   = 'Подробно >>';
  msg_dialog_vista_btn_collapse = '<< Свернуть';
{$ENDIF}{$IFDEF LANGUAGE_RUS}
  msg_dialog_vista_btn_expand   = 'Подробнее >>';
  msg_dialog_vista_btn_collapse = '<< Свернуть';
{$ENDIF}{$IFDEF LANGUAGE_ENG}
  msg_dialog_vista_btn_expand   = 'More >>';
  msg_dialog_vista_btn_collapse = '<< Hide';
{$ENDIF}{$IFDEF LANGUAGE_DEU}
  msg_dialog_vista_btn_expand   = 'More >>';
  msg_dialog_vista_btn_collapse = '<< Hide';
{$ENDIF}
const 
  DefaultDialogsVistaFormHeight = 160;
  DefaultDialogsVistaHelpHeight = 200;
  //============================================================================
  function DialogsVista_MsgDlg_GetImagePath(const aDialogType:TMsgDlgType):string;
  begin
    Result := '';
    case aDialogType of
      mtWarning     :Result := 'PEAKTOP:IMG/ICONS/DIALOGS_WARNING_0064x0064.BMP';
      mtError       :Result := 'PEAKTOP:IMG/ICONS/DIALOGS_ERROR_0064x0064.BMP';
      mtInformation :Result := 'PEAKTOP:IMG/ICONS/DIALOGS_INFORMATION_0064x0064.BMP';
      mtConfirmation:Result := 'PEAKTOP:IMG/ICONS/DIALOGS_CONFIRMATION_0064x0064.BMP';
      mtCustom      :Result := '';
      end;
  end;
  //============================================================================
  procedure DialogsVista_MsgDlg_BtnExpand_OnClick(Sender :TObject);
  begin
    if(TForm(TComponent(Sender).Owner).Height = DefaultDialogsVistaFormHeight)then
      begin
      TForm(TComponent(Sender).Owner).Height := DefaultDialogsVistaFormHeight + DefaultDialogsVistaHelpHeight + 2;
      TxcButton(Sender).Caption              := msg_dialog_vista_btn_collapse;
      TControl(TComponent(Sender).Owner.FindComponent('MemoMgs')).Visible := true;
      end
     else
      begin
      TForm(TComponent(Sender).Owner).Height := DefaultDialogsVistaFormHeight;
      TxcButton(Sender).Caption              := msg_dialog_vista_btn_expand;
      TControl(TComponent(Sender).Owner.FindComponent('MemoMgs')).Visible := false;
      end; 
    TForm(TComponent(Sender).Owner).Position := poDesktopCenter;
  end;
  //============================================================================
  function DialogsVista_MsgDlg_Create(const aCaption, aTopBarCaption, aImagePath, aCustomText, aHelpText:string;
             const aButtonsCaptions:array of string; const aButtonsResults :array of Integer):TForm;
  var
    lkPanelTop     :TxcGradientPanelVista;
    lkImg          :TImage;
    lkPanelBottom  :TxcGradientPanel;
    lkBtns         :array of TxcButton;
    lkBmp          :TBitmap;
    lkStrm         :TMemoryStream;
    i, j, lkLeft   :Integer;
    lkImgPath      :string;
  begin
    SetArrayLength(lkBtns, High(aButtonsCaptions)+1);
    Result := TForm.Create(nil);
    with Result do
      begin
      AlphaBlendValue := 232;
      AlphaBlend      := true;
      Caption         := aCaption;
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderStyle     := bsDialog;
      BorderIcons     := [biSystemMenu];
      Position        := poDesktopCenter;
      Width           := 600;
      Height          := DefaultDialogsVistaFormHeight;
      end;
    if(Length(aTopBarCaption)<>0)then
      begin
      lkPanelTop := TxcGradientPanelVista.Create(Result);
      with lkPanelTop do
        begin
        Parent       := Result;
        Align        := alTop;
        Height       := 32;
        BorderStyle  := xbsRaized;
        StyleManager := Amunhotep.MainForm.StyleManager;
        Caption      := ' '+aTopBarCaption;
        Font.Size    := 14;
        Font.Style   := lkPanelTop.Font.Style + [fsBold];
        Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Window;
        end;
      end;
    if(StrTrimAll(aImagePath) <> '')then
      begin
      lkImg := TImage.Create(Result);
      with lkImg do
        begin
        Parent       := Result;
        Align        := alLeft;
        Width        := 64;
        Transparent  := true;
        Proportional := true;
        if(Pos('DB:',UpperCase(aImagePath)) = 1)then
          try
            lkStrm := TMemoryStream.Create;
            if StreamLoadFromFile(aImagePath, lkStrm)then
              Picture.Bitmap.LoadFromStream(lkStrm);
          finally    
            lkStrm.Free;
          end
         else
          begin
          lkImgPath := PrepareAbsoleteFileName(aImagePath);
          if FileExists(lkImgPath)then
            Picture.LoadFromFile(lkImgPath);  
          end;
        end;     
      end; 
    with TLabel.Create(Result) do
      begin
      Parent     := Result;
      Align      := alClient;
      Transparent:= true;
      Font.Name  := 'Verdana';
      Font.Size  := 7;
      Font.Style := [fsBold];
      WordWrap   := true;
      AutoSize   := false;
      Caption    := aCustomText;
      end;
    lkPanelBottom := TxcGradientPanel.Create(Result);
    with lkPanelBottom do
      begin
      Parent         := Result;
      Height         := 24;
      Width          := Result.ClientWidth;
      Align          := alBottom;
      BorderStyle    := xbsNone;
      GradientDirect := gdTopToBottom;
      StyleManager   := Amunhotep.MainForm.StyleManager;
      end;
    if(StrTrimAll(aHelpText) <> '')then
      begin
      with TMemo.Create(Result) do
        begin
        Name       := 'MemoMgs';
        Parent     := Result;
        Align      := alBottom;
        Color      := Amunhotep.MainForm.StyleManager.Colors.Foreground;
        Ctl3D      := false;
        Font.Name  := 'Verdana';
        Font.Size  := 7;
        Font.Style := [fsBold];
        Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
        ScrollBars := ssBoth;
        Lines.Text := aHelpText;
        ReadOnly   := true;
        Visible    := false;
        Top        := lkPanelBottom.Top + lkPanelBottom.Height + 1;
        Height     := DefaultDialogsVistaHelpHeight;
        end;
      with TxcButton.Create(Result) do
        begin
        Parent         := lkPanelBottom;
        Width          := 96;
        Left           := 2;
        Top            := 2;
        Height         := lkPanelBottom.Height - 4;
        Caption        := msg_dialog_vista_btn_expand;
        StyleManager   := Amunhotep.MainForm.StyleManager;
        Font.Name      := 'Verdana';
        Font.Size      := 7;
        Font.Style     := [fsBold];
        ModalResult    := mrNone;
        OnClick        := @DialogsVista_MsgDlg_BtnExpand_OnClick;
        end;
      end;
    lkBmp := TBitmap.Create;
    lkBmp.Canvas.Font.Assign(Result.Font);
    lkBmp.Canvas.Font.Style := lkBmp.Canvas.Font.Style + [fsBold];
    for i:=High(aButtonsCaptions) downto Low(aButtonsCaptions) do
      begin
      lkBtns[i] := TxcButton.Create(Result);
      with lkBtns[i] do
        begin
        Parent       := lkPanelBottom;
        Width        := lkBmp.Canvas.TextWidth(aButtonsCaptions[i]) + 16;
        lkLeft := lkPanelBottom.Width - Width - 1;
        for j:=i to High(aButtonsCaptions) do
          lkLeft := lkLeft - Width
        Left         := lkLeft;
        Top          := 2;
        Height       := lkPanelBottom.Height - 4;
        Caption      := aButtonsCaptions[i];
        StyleManager := Amunhotep.MainForm.StyleManager;
        Default      := (i = Low(aButtonsCaptions));
        Font.Name    := 'Verdana';
        Font.Size    := 7;
        Font.Style   := [fsBold];
        ModalResult  := aButtonsResults[i];
        Align        := alRight;
        end;
      end;
    lkBmp.Free;  
    Result.ActiveControl := lkBtns[Low(aButtonsCaptions)];
  end;
  //============================================================================
  function DialogsVista_MsgDlg_Execute(const aCaption, aTopBarCaption, aImagePath, aCustomText, aHelpText:string;
             const aButtonsCaptions:array of string; const aButtonsResults :array of Integer):TModalResult;
  var
    lkForm :TForm;
  begin
    try
      lkForm := DialogsVista_MsgDlg_Create(aCaption, aTopBarCaption, aImagePath, aCustomText, aHelpText, aButtonsCaptions, aButtonsResults);
      Result := lkForm.ShowModal;
    finally  
      lkForm.Free;
    end;  
  end;
