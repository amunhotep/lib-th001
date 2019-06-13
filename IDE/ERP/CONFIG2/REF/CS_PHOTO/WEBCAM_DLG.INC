{$DEFINE DB:CONFIG/REF/CS_PHOTO/WEBCAM_DLG.INC}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}{$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}     {$ENDIF}
function capCreateCaptureWindowA(
           lpszWindowName :PChar;
           dwStyle        :LongInt;
           x              :Integer;
           y              :Integer;
           nWidth         :Integer;
           nHeight        :Integer;
           ParentWin      :hWND;
           nId            :Integer
         ):hWnd; external 'capCreateCaptureWindowA@AVICAP32.DLL stdcall';
function SendMessageA(
           hWndHandle     :HWND; 
           Msg            :LongInt; 
           wParam         :LongInt; 
           lParam         :LongInt
         ):LongInt; external 'SendMessageA@USER32.DLL stdcall';         
function SendMessageA_Hack(
           hWndHandle     :HWND; 
           Msg            :LongInt; 
           wParam         :LongInt; 
           lParam         :PChar
         ):LongInt; external 'SendMessageA@USER32.DLL stdcall';         
const
  WM_USER                       = $0400;
  WM_CAP_START                  = WM_USER;
  WM_CAP_STOP                   = WM_CAP_START + 68;
  WM_CAP_DRIVER_CONNECT         = WM_CAP_START + 10;
  WM_CAP_DRIVER_DISCONNECT      = WM_CAP_START + 11;
  WM_CAP_SAVEDIB                = WM_CAP_START + 25;
  WM_CAP_GRAB_FRAME             = WM_CAP_START + 60;
  WM_CAP_SEQUENCE               = WM_CAP_START + 62;
  WM_CAP_FILE_SET_CAPTURE_FILEA = WM_CAP_START + 20;
var 
  hWndCamera :THandle;
  //============================================================================
  procedure WebCamDialog_Timer_OnTimer(Sender :TObject);
  begin
    if(hWndCamera <> 0)then 
      SendMessageA(hWndCamera, WM_CAP_GRAB_FRAME, 0, 0);   
  end;
  //============================================================================
  procedure WebCamDialog_Playing_OnClick(Sender :TObject);
  var
    lkBool :Boolean;
  begin
    lkBool := (TxcToolBarButton(Sender).Tag = 1);
    TxsTimer(TComponent(Sender).Owner.FindComponent('Timer')).Enabled := lkBool;
    if lkBool then
      begin
      TxcToolBarButton(Sender).Caption    := 'Остановить';
      TxcToolBarButton(Sender).Hint       := 'Остановить воспроизведение';
      TxcToolBarButton(Sender).ImageIndex := 325;
      TxcToolBarButton(Sender).Tag        := 0;
      end
     else   
      begin
      TxcToolBarButton(Sender).Caption    := 'Запустить';
      TxcToolBarButton(Sender).Hint       := 'Запустить воспроизведение';
      TxcToolBarButton(Sender).ImageIndex := 24;
      TxcToolBarButton(Sender).Tag        := 1;
      end  
  end;
  //============================================================================
  procedure WebCamDialog_Ok_OnClick(Sender :TObject);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  procedure WebCamDialog_Cancel_OnClick(Sender :TObject);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrCancel;
  end;
  //============================================================================
  function WebCamDialog_Execute(const aFileName:string):Boolean;
  var
    lkForm     :TForm;
    lkTopBar   :TxcGradientPanelVista;
    lkToolBar  :TxcGradientPanelVista;
    lkTBB      :TxcToolBarButton;
    lkTimer    :TxsTimer;
    lkBmp      :TBitmap;
  begin
    lkForm := TForm.Create(nil);
    with lkForm do
      begin
      Caption     := Amunhotep.Title;
      Color       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderStyle := bsDialog;
      BorderIcons := [biSystemMenu];
      Position    := poDesktopCenter;
      Width       := 640;
      Height      := 480;
      Font.Size   := 7;
      end;
    lkTopBar  := CreateTxcGradientPanelVista(lkForm, lkForm,'TopBar', 'Получение изображения с WEB-камеры',alTop,0,0,34,98,xbsRaized);  
    lkToolBar := CreateTxcGradientPanelVistaToolBar(lkForm, lkForm,'ToolBar','',alBottom,0,0,24,200,xbsRaized);
    lkToolBar.Font.Style := [fsBold];  
    lkTBB     := CreateTxcToolBarButton(lkForm, lkToolBar, 'tbbPlaying','Остановить','Остановить воспроизведение',0,0,24,120,alLeft, 325, nil);
    lkTBB.ShowCaption := true;
    lkTBB.Tag         := 0;
    lkTBB.OnClick     := @WebCamDialog_Playing_OnClick;
    lkTBB             := CreateTxcToolBarButton(lkForm, lkToolBar, 'tbbOk','OK','Вставить изображение',0,0,24,60,alRight, 332, nil);
    lkTBB.ShowCaption := true;
    lkTBB.OnClick     := @WebCamDialog_Ok_OnClick;
    lkTBB             := CreateTxcToolBarButton(lkForm, lkToolBar, 'tbbCancel','Отмена','Отмена',0,0,24,60,alRight, 70, nil);
    lkTBB.ShowCaption := true;
    lkTBB.OnClick     := @WebCamDialog_Cancel_OnClick;
    hWndCamera := capCreateCaptureWindowA('AMUNHOTEP', $40000000 or $10000000 {WS_CHILD or WS_VISIBLE} ,
                   0,lkTopBar.Top+lkTopBar.Height+1,lkForm.Width-8,
                   lkForm.Height - (lkTopBar.Height + lkToolBar.Height + 40)
                   ,lkForm.Handle, 0); //создаем область для вывода получаемых в будущем картинок
    if(hWndCamera <> 0)then 
      SendMessageA(hWndCamera, WM_CAP_DRIVER_CONNECT, 0, 0);  //забираем картинку с вебкамеры
    lkTimer := TxsTimer.Create(lkForm);
    with lkTimer do
      begin
      Name     := 'Timer';
      Interval := 100;
      OnTimer  := @WebCamDialog_Timer_OnTimer;
      Enabled  := true;
      end;
    Result := (lkForm.ShowModal = mrOk);   
    if Result then
      begin
      if(hWndCamera <> 0)then
        SendMessageA_Hack(hWndCamera, WM_CAP_SAVEDIB, 0, aFileName);
      end;
    if(hWndCamera <> 0)then
      begin
      SendMessageA(hWndCamera, WM_CAP_DRIVER_DISCONNECT, 0, 0);  //"отключаемся" от веб-камеры
      hWndCamera := 0;
      end;
    lkForm.Free;
  end;
