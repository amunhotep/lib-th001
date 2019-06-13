{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/GLOBALVARIABLES.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}           {$I ../$COMMON/FORMERP.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/GLOBALVARIABLES_LANG.INC} {$I ./GLOBALVARIABLES_LANG.INC} {$ENDIF}
  //============ PEAKTOP:IDE/ERP/DBO/OPER/GLOBALVARIABLES.INC ==================
  function TERPFormOperGlobalVariables_Create:TForm;
  var
    lkMemo :TMemo;
  begin
    Result := TERPForm_Create(msg_erp_caption_global_variables, ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), true, nil);
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    with Result do
      begin
      Width  := MaxInteger(600, Trunc(Screen.Width * 2 / 3));
      Height := MaxInteger(400, Trunc(Screen.Height / 3));
      end;
    lkMemo := TMemo.Create(Result);
    with lkMemo do
      begin
      Parent     := Result;
      Align      := alClient;
      ScrollBars := ssBoth;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Name  := 'Courier New';
      Font.Size  := 8;
      Font.Style := [fsBold];
      ReadOnly   := true;
      WordWrap   := false;
      Lines.Text := GlobalVariables.Text;
      end;
  end;
  //============================================================================
  function TERPFormOperGlobalVariables_Execute:Boolean;
  begin
    Result := false;
    with TERPFormOperGlobalVariables_Create do
      try
        Result := (ShowModal = mrOk);
      finally
        Free;
      end;    
  end;
