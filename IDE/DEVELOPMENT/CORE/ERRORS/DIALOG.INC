{$DEFINE PEAKTOP:IDE/DEVELOPMENT/CORE/ERRORS/DIALOG.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}           {$I PEAKTOP:GLOBAL_VARIABLES.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}  {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}       {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}       {$ENDIF}
const //============= PEAKTOP:IDE/DEVELOPMENT/CORE/ERRORS/DIALOG.INC ===========
  msg_pascal_run_error     = 'Ошибка выполнения скрипта';
  msg_pascal_run_error_msg = 'Не удается выполнить указанный скрипт.';
  msg_btn_expand           = 'Подробнее >>';
  msg_btn_collapse         = '<< Свернуть';
  msg_ts_message           = 'Отладочная информация';
const 
  PascalErrorDlg_DefaultFormHeight = 86;
  //============================================================================
  procedure PascalErrorDlg_BtnExpand_OnClick(Sender :TObject);
  begin
    if(TForm(TComponent(Sender).Owner).Height = PascalErrorDlg_DefaultFormHeight)then
      begin
      TForm(TComponent(Sender).Owner).Height := Trunc(Screen.Height * 2/3);
      TxcButton(Sender).Caption              := msg_btn_collapse;
      TMemo(TComponent(Sender).Owner.FindComponent('MemoMgs')).Visible := true;
      end
     else
      begin
      TForm(TComponent(Sender).Owner).Height := PascalErrorDlg_DefaultFormHeight;
      TxcButton(Sender).Caption              := msg_btn_expand;
      TMemo(TComponent(Sender).Owner.FindComponent('MemoMgs')).Visible := false;
      end; 
  end;
  //============================================================================
  procedure PascalErrorDlg_actClose_OnExecute(Sender :TObject);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  function PascalErrorDlg(const Msg:string):Boolean;
  var
    lkForm        :TForm;
    lkTopBar      :TxcGradientPanelVista;
    lkMemoMsg     :TMemo;
    lkPanelBottom :TxcStdPanel;
    lkBtnExpand   :TxcButton;
  begin
    Result := false;
    lkForm := TForm.Create(Amunhotep);
    with lkForm do
      begin
      Caption         := msg_pascal_run_error;
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderStyle     := bsDialog;
      BorderIcons     := [];
      AlphaBlendValue := 224;
      AlphaBlend      := true;
      Position        := poDesigned;
      Width           := Trunc(Screen.Width * 2 / 3);
      Height          := PascalErrorDlg_DefaultFormHeight;
      Top             := Height;
      Left            := Trunc((Screen.Width - Width)/2);
      end;
    lkTopBar := CreateTxcGradientPanelVista(lkForm,lkForm,'TopBar',#$20#$20#$20#$20#$20#$20+msg_pascal_run_error_msg,alTop, 0,0,34,34,xbsRaized);
    with CreateTxcToolBarButton(lkForm,lkTopBar,'tbbImgLogo','','',0,0,0,lkTopBar.Height+8, alLeft,-1,nil) do
      begin
      ShowHint    := true;
      ShowCaption := false;
      if FileExists(PrepareAbsoleteFileName(PrepareAbsoleteFileName('PEAKTOP:IMG/ICONS/PASCALERROR_0032X0032.BMP')))then  
        Glyph.LoadFromFile(PrepareAbsoleteFileName(PrepareAbsoleteFileName('PEAKTOP:IMG/ICONS/PASCALERROR_0032X0032.BMP')));
      end;
    with CreateTxcToolBarButton(lkForm,lkTopBar,'tbbClose','','',0,0,0,lkTopBar.Height+2, alRight,-1,nil) do
      begin
      ShowHint    := true;
      ShowCaption := false;
      if FileExists(PrepareAbsoleteFileName(PrepareAbsoleteFileName('PEAKTOP:IMG/ICONS/DIALOGS_CLOSE_0032X0032.BMP')))then  
        Glyph.LoadFromFile(PrepareAbsoleteFileName(PrepareAbsoleteFileName('PEAKTOP:IMG/ICONS/DIALOGS_CLOSE_0032X0032.BMP')));
      OnClick := @PascalErrorDlg_actClose_OnExecute;  
      end;
    lkMemoMsg := TMemo.Create(lkForm);
    with lkMemoMsg do
      begin
      Name       := 'MemoMgs';
      Parent     := lkForm;
      Align      := alClient;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Name  := 'Courier New';
      Font.Size  := 8;
      Font.Style := [fsBold];
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      ScrollBars := ssBoth;
      Lines.Text := Msg;
      ReadOnly   := true;
      Visible    := false;
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
      end;
    lkBtnExpand := TxcButton.Create(lkForm);
    with lkBtnExpand do
      begin
      Parent       := lkPanelBottom;
      Width        := 96;
      Left         := 2;
      Top          := 2;
      Height       := lkPanelBottom.Height - 4;
      Caption      := msg_btn_expand;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Font.Name    := 'Verdana';
      Font.Size    := 7;
      Font.Style   := [fsBold];
      ModalResult  := mrNone;
      OnClick      := @PascalErrorDlg_BtnExpand_OnClick;
      end;
    lkForm.ShowModal;
    lkForm.Free;
    Result := true;
  end;
