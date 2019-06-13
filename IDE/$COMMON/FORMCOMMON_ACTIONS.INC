{$DEFINE PEAKTOP:IDE/$COMMON/FORMCOMMON_ACTIONS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}  {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
  //================== PEAKTOP:IDE/$COMMON/FORMCOMMON_ACTIONS.INC ==============
{$IFDEF MSWINDOWS}
  function TCommonForm_SendMessageA(hWndHandle :HWND; Msg, wParam,lParam:LongInt):LongInt; external 'SendMessageA@USER32.DLL stdcall';
{$ENDIF}
  //============================================================================
  procedure TCommonForm_OnClose(Sender :TObject; var Action :TcloseAction);
  begin
    Action := caFree;
  end;
  //============================================================================
  procedure TCommonForm_actClose_OnExecute(Sender :TObject);
  begin
    if(ObjectInheritsFrom(TComponent(Sender).Owner, 'TForm'))then
      if(TForm(TComponent(Sender).Owner).FormStyle <> fsMDIChild)then
        begin
        TForm(TComponent(Sender).Owner).ModalResult := mrCancel;
        exit;
        end      
    {$IFDEF MSWINDOWS}
    TCommonForm_SendMessageA(TForm(TComponent(Sender).Owner).Handle, $0010, 0, 0); // WM_CLOSE = $0010
    {$ELSE}
    TComponent(Sender).Owner.Free;
    {$ENDIF}
  end;
  //============================================================================
  procedure TCommonForm_actOk_OnExecute(Sender :TObject);
  begin
    if(ObjectInheritsFrom(TComponent(Sender).Owner, 'TForm'))then
      if(TForm(TComponent(Sender).Owner).FormStyle <> fsMDIChild)then
        begin
        TForm(TComponent(Sender).Owner).ModalResult := mrOk;
        exit;
        end
  end;
  //============================================================================
  procedure TCommonForm_actSourceCode_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.ProcessFile(PrepareAbsoleteFileName(ScriptName));
  end;
