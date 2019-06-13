{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/HELP.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}   {$I ../$COMMON/FORMERP.INC}   {$ENDIF}
  //===================== PEAKTOP:IDE/ERP/DBO/HLP/FORMHLP.INC ==================
  procedure TERPFormOperHelp_OnClose(Sebder :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end;
  //============================================================================
  function TERPFormOperHelp_Create(const aCaption, aHelpFileName:string):TForm;
  var
    lkHTML :THTMLViewer;
  begin
    Result := TERPForm_Create(aCaption, ERP_FILENAME_ICO_ACTHELP, ERP_FILENAME_BMP_ACTHELP, false, @TERPFormOperHelp_OnClose);
    if(Result.FindComponent(obj_name_erp_acthelp) <> nil)then
      Result.FindComponent(obj_name_erp_acthelp).Free; // no recursive help !
    lkHTML := THTMLViewer.Create(Result);
    with lkHTML do
      begin
      Name          := obj_name_erp_htmlview;
      Parent        := Result;
      Align         := alClient;
      BorderStyle   := htNone;
      DefBackground := Amunhotep.MainForm.StyleManager.Colors.Window;
      DefFontColor  := Amunhotep.MainForm.StyleManager.Colors.Border;
      ServerRoot    := PrepareAbsoleteFileName('TMP:')+'\';
      if FileExists(PrepareAbsoleteFileName(aHelpFileName))then
        LoadFromFile(PrepareAbsoleteFileName(aHelpFileName));
      end;
  end;
