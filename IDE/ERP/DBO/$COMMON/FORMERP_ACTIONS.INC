{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_ACTIONS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC}    {$I ./FORMERP_HEADER.INC}   {$ENDIF}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_ACTIONS.INC ===============
{$IFDEF MSWINDOWS}
  function TERPForm_SendMessageA(hWndHandle :HWND; Msg, wParam,lParam:LongInt):LongInt; external 'SendMessageA@USER32.DLL stdcall';
{$ENDIF}
  //============================================================================
  procedure TERPForm_actClose_OnExecute(Sender :TObject);
  begin
    if(ObjectInheritsFrom(TComponent(Sender).Owner, 'TForm'))then
      begin
      if(TForm(TComponent(Sender).Owner).FormStyle <> fsMDIChild)then
        begin
        TForm(TComponent(Sender).Owner).ModalResult := mrCancel;
        exit;
        end
      TForm(TComponent(Sender).Owner).Close;
{$IFDEF MSWINDOWS}
//    TERPForm_SendMessageA(TForm(TComponent(Sender).Owner).Handle, $0010, 0, 0); // WM_CLOSE = $0010
{$ENDIF}
      end;          
  end;
  //============================================================================
  procedure TERPForm_actOk_OnExecute(Sender :TObject);
  begin
    if(ObjectInheritsFrom(TComponent(Sender).Owner, 'TForm'))then
      if(TForm(TComponent(Sender).Owner).FormStyle <> fsMDIChild)then
        begin
        TForm(TComponent(Sender).Owner).ModalResult := mrOk;
        exit;
        end
  end;
  //============================================================================
  procedure TERPForm_actHelp_OnExecute(Sender :TObject);
  begin
    with TCustomAction(Sender) do
      ERP_ObjectHelp(TERPForm_ObjId(Owner), TERPForm_ObjType(Owner));
  end;
  //============================================================================
  procedure TERPForm_actSourceCode_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.ProcessFile(PrepareAbsoleteFileName(ScriptName));
  end; 
  //============================================================================
  procedure TERPForm_actConfig_OnExecute(Sender :TObject);
  begin
    with TCustomAction(Sender) do
      ERP_ObjectEditor(TERPForm_ObjId(Owner), TERPForm_ObjType(Owner));
  end;
  //============================================================================
  procedure TERPForm_actConfigMenu_OnExecute(Sender :TObject);
  var
    lkTypeId :Integer;
  begin
    with TCustomAction(Sender) do
      begin
      lkTypeId := TERPForm_ObjType(Owner);
      if((lkTypeId = ERP_OBJECTTYPE_REF) or (lkTypeId = ERP_OBJECTTYPE_RPT) or (lkTypeId = ERP_OBJECTTYPE_REG))then
        ERP_ObjectEditor(TERPForm_ObjId(Owner), ERP_OBJECTTYPE_MENU);
      end;
  end;     
