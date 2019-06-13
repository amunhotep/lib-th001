{$DEFINE PEAKTOP:IDE/DEVELOPMENT/EDITOR/ACTIONS.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                               {$I PEAKTOP:OBJ/TACTION.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                              {$I PEAKTOP:OBJ/TXCPANEL.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                      {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}                 {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}{$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                      {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSYNEDIT_KEYCOMMANDS.INC}                  {$I PEAKTOP:OBJ/TSYNEDIT_KEYCOMMANDS.INC} {$ENDIF}  
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/EDITOR/DIALOGS/SEARCH.INC}     {$I ./DIALOGS/SEARCH.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/EDITOR/OBJNAMES.INC}           {$I ./OBJNAMES.INC}                       {$ENDIF}
const  //========== PEAKTOP:APPL/TOOLS_API/LANG/CORE_EDITORACTIONS.INC =========
  msg_tabsheet_editor_caption              = 'Редактор';
  msg_mi_main_file                         = 'Файл';
  msg_mi_main_edit                         = 'Правка';
  msg_mi_main_format                       = 'Формат';
  msg_mi_main_view                         = 'Вид';
  msg_mi_main_tools                        = 'Инструменты';
  msg_act_file_save                        = 'Сохранить';             msg_act_file_save_hint                   = 'Сохранить файл';
  msg_act_file_export_html                 = 'Экспорт в гипертекст';  msg_act_file_export_html_hint            = 'Экспорт в гипертекст';
  msg_act_file_export_rtf                  = 'Экспорт в RTF';         msg_act_file_export_rtf_hint             = 'Экспорт в RTF';
  msg_act_edit_undo                        = 'Отменить';              msg_act_edit_undo_hint                   = 'Отменить последнее действие';
  msg_act_edit_redo                        = 'Вернуть';               msg_act_edit_redo_hint                   = 'Вернуть последнее действие';
  msg_act_edit_cut                         = 'Вырезать';              msg_act_edit_cut_hint                    = 'Вырезать в буфер обмена';
  msg_act_edit_copy                        = 'Копировать';            msg_act_edit_copy_hint                   = 'Копировать в буфер обмена';
  msg_act_edit_paste                       = 'Вставить';              msg_act_edit_paste_hint                  = 'Вставить из буфера обмена';
  msg_act_edit_delete                      = 'Удалить';               msg_act_edit_delete_hint                 = 'Удалить выделенный текст';
  msg_act_edit_selectall                   = 'Выделить все';          msg_act_edit_selectall_hint              = 'Выделить весь текст';
  msg_act_edit_gotolinenumber              = 'Перейти к строке № ...';msg_act_edit_gotolinenumber_hint         = 'Перейти к строке № ...';
  msg_act_search                           = 'Найти';                 msg_act_search_hint                      = 'Найти текст';
  msg_act_search_next                      = 'Найти далее';           msg_act_search_next_hint                 = 'Найти далее текст';
  msg_act_search_replace                   = 'Заменить';              msg_act_search_replace_hint              = 'Заменить текст';
  msg_act_format_indent_left               = 'Сдвиг блока влево';     msg_act_format_indent_left_hint          = 'Сдвиг выделенного блока влево';
  msg_act_format_indent_right              = 'Сдвиг блока вправо';    msg_act_format_indent_right_hint         = 'Сдвиг выделенного блока вправо';
  msg_act_format_upper_case                = 'В верхний регистр';     msg_act_format_upper_case_hint           = 'Преобразовать в верхний регистр';
  msg_act_format_lower_case                = 'В нижний регистр';      msg_act_format_lower_case_hint           = 'Преобразовать в нижний регистр';
  msg_act_format_toggle_case               = 'Инвертировать регистр'; msg_act_format_toggle_case_hint          = 'Инвертировать регистр';
  msg_act_format_folding_collapse          = 'Развернуть';            msg_act_format_folding_collapse_hint     = 'Развернуть текущий блок';
  msg_act_format_folding_collapseall       = 'Развернуть все';        msg_act_format_folding_collapseall_hint  = 'Развернуть все блоки';
  msg_act_format_folding_uncollapse        = 'Свернуть';              msg_act_format_folding_uncollapse_hint   = 'Свернуть текущий блок';
  msg_act_format_folding_uncollapseall     = 'Свернуть все';          msg_act_format_folding_uncollapseall_hint= 'Свернуть все блоки';
  msg_act_tools_preprocess                 = 'Препроцессинг';         msg_act_tools_preprocess_hint            = 'Выполнить препроцессинг скрипта';
  msg_act_tools_highlighter                = 'Подсветка синтаксиса';  msg_act_tools_highlighter_hint           = 'Настройка подсветки синтаксиса';
  msg_act_tools_caseimageindex             = 'Выбрать код картинки';  msg_act_tools_caseimageindex_hint        = 'Выбрать код картинки';
  msg_act_tools_caseimageindex_execute     = 'Выбирите картинку';     msg_act_tools_casecolor                  = 'Выбрать цвет из палитры';
  msg_act_tools_casecolor_hint             = 'Выбрать цвет';          msg_act_tools_genguid                    = 'Сгененрировать GUID';
  msg_act_tools_genguid_hint               = 'Сгененрировать GUID';   msg_act_tools_getcurrentfilename         = 'Вставить имя файла';
  msg_act_tools_getcurrentfilename_hint    = 'Вставить имя файла';    msg_act_tools_formatsrc001               = 'Преобразовать код из PSUnitImportera';
  msg_act_tools_formatsrc001_hint          = 'Преобразовать код из PSUnitImportera';
  msg_string_not_found_more                = 'Искомый текст больше не найден !';
var
  EditorSearchOptions :TSynSearchOptions;
  //============================================================================
  function Editor_SynEdit(aOwner :TComponent):TSynEdit;
  begin
    Result := TSynEdit(aOwner.FindComponent('SynEdit'));
  end;
  //============================================================================
  procedure Editor_actFileExportHTML_OnExecute(Sender :TObject);
  var
    lkFileName :string;
  begin
    lkFileName := '';
    with TSynExporterHTML.Create(nil) do
      begin
      CreateHTMLFragment := false;
      UseBackground := true;
      Color         := Editor_SynEdit(TComponent(Sender).Owner).Color;
      Font.Name     := Editor_SynEdit(TComponent(Sender).Owner).Font.Name;
      Font.Color    := Editor_SynEdit(TComponent(Sender).Owner).Font.Color;
      Font.Size     := Editor_SynEdit(TComponent(Sender).Owner).Font.Size;
      Font.Style    := Editor_SynEdit(TComponent(Sender).Owner).Font.Style;
      Highlighter   := Editor_SynEdit(TComponent(Sender).Owner).Highlighter;
      Title         := TAmunhotepForm(TComponent(Sender).Owner).FileName;
      if PromptForFileName(lkFileName, DefaultFilter, 'html', msg_act_file_export_html_hint, '', true)then
        begin
        {$IFDEF CODEFOLDING}
        ExportAll(Editor_SynEdit(TComponent(Sender).Owner).GetUncollapsedStrings);
        {$ELSE}
        ExportAll(Editor_SynEdit(TComponent(Sender).Owner).Lines); 
        {$ENDIF}
        SaveToFile(lkFileName);
        end;
      Free;
      end;
  end;
  //============================================================================
  procedure Editor_actFileExportRTF_OnExecute(Sender :TObject);
  var
    lkFileName :string;
  begin
    lkFileName := '';
    with TSynExporterRTF.Create(nil) do
      begin
      UseBackground := true;
      Color         := Editor_SynEdit(TComponent(Sender).Owner).Color;
      Font.Name     := Editor_SynEdit(TComponent(Sender).Owner).Font.Name;
      Font.Color    := Editor_SynEdit(TComponent(Sender).Owner).Font.Color;
      Font.Size     := Editor_SynEdit(TComponent(Sender).Owner).Font.Size;
      Font.Style    := Editor_SynEdit(TComponent(Sender).Owner).Font.Style;
      Highlighter   := Editor_SynEdit(TComponent(Sender).Owner).Highlighter;
      Title         := TAmunhotepForm(TComponent(Sender).Owner).FileName;
      if PromptForFileName(lkFileName, DefaultFilter, 'rtf', msg_act_file_export_rtf_hint, '', true)then
        begin
        {$IFDEF CODEFOLDING}
        ExportAll(Editor_SynEdit(TComponent(Sender).Owner).GetUncollapsedStrings);
        {$ELSE}
        ExportAll(Editor_SynEdit(TComponent(Sender).Owner).Lines); 
        {$ENDIF}
        SaveToFile(lkFileName);
        end;
      Free;
      end;
  end;
  //============================================================================
  procedure Editor_actEditGotoLineNumber_OnExecute(Sender :TObject);
  var
    lkNum :Integer;
  begin
    lkNum := Editor_SynEdit(TComponent(Sender).Owner).CaretY;
    if Dialogs.InputQueryInteger(msg_act_edit_gotolinenumber, msg_act_edit_gotolinenumber_hint, lkNum)then
      TSynEdit(TForm(TComponent(Sender).Owner).ActiveControl).TopLine := lkNum;
  end;
  //============================================================================
  procedure Editor_actEditUndo_OnExecute(Sender :TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).Undo;
  end;
  //============================================================================
  procedure Editor_actEditUndo_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := Editor_SynEdit(TComponent(Sender).Owner).CanUndo;
  end;
  //============================================================================
  procedure Editor_actEditRedo_OnExecute(Sender :TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).Redo;
  end;
  //============================================================================
  procedure Editor_actEditRedo_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := Editor_SynEdit(TComponent(Sender).Owner).CanRedo;
  end;
  //============================================================================
  procedure Editor_actEditCut_OnExecute(Sender :TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).CutToClipboard;
  end;
  //============================================================================
  procedure Editor_actEditCut_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := (Editor_SynEdit(TComponent(Sender).Owner).SelLength > 0);
  end;
  //============================================================================
  procedure Editor_actEditCopy_OnExecute(Sender :TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).CopyToClipboard;
  end;
  //============================================================================
  procedure Editor_actEditPaste_OnExecute(Sender :TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).PasteFromClipboard;
  end;
  //============================================================================
  procedure Editor_actEditPaste_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := Editor_SynEdit(TComponent(Sender).Owner).CanPaste;
  end;
  //============================================================================
  procedure Editor_actEditDelete_OnExecute(Sender :TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).ClearSelection;
  end;
  //============================================================================
  procedure Editor_actEditSelectAll_OnExecute(Sender :TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).SelectAll;
  end;
  //============================================================================
  procedure Editor_actSearch_OnExecute(Sender :TObject);
  var
    lkStr :string;
  begin
    if(Editor_SynEdit(TComponent(Sender).Owner).SelLength > 0)then
      begin
      lkStr := Editor_SynEdit(TComponent(Sender).Owner).SelText;
      EditorSearchOptions := EditorSearchOptions + [ssoSelectedOnly];         
      end
     else
      lkStr := Editor_SynEdit(TComponent(Sender).Owner).GetWordAtRowCol(Editor_SynEdit(TComponent(Sender).Owner).CaretXY);
    if(EditorSearchDialog_Execute(lkStr, EditorSearchOptions))then
      begin
      Editor_SynEdit(TComponent(Sender).Owner).HelpKeyWord := lkStr;
      if(not(Editor_SynEdit(TComponent(Sender).Owner).SearchReplace(lkStr, '', EditorSearchOptions) > 0))then
        Dialogs.MessageDlg(msg_string_not_found_more+#13#10+'"'+lkStr+'"', mtInformation, [mbOk]);
      end;
  end;
  //============================================================================
  procedure Editor_actSearchNext_OnExecute(Sender :TObject);
  var
    lkStr :string;
  begin
    lkStr := Editor_SynEdit(TComponent(Sender).Owner).HelpKeyWord;
    if(lkStr = '')then 
      Editor_actSearch_OnExecute(Sender)
     else 
      if(not(Editor_SynEdit(TComponent(Sender).Owner).SearchReplace(lkStr, '', EditorSearchOptions) > 0))then
        Dialogs.MessageDlg(msg_string_not_found_more+#13#10+'"'+lkStr+'"', mtInformation, [mbOk]);
  end;
  //============================================================================
  procedure Editor_actSearchReplace_OnExecute(Sender :TObject);
  var
    lkStr, lkStrReplace :string;
  begin
    lkStrReplace := '';
    if(Editor_SynEdit(TComponent(Sender).Owner).SelLength > 0)then
      begin
      lkStr := Editor_SynEdit(TComponent(Sender).Owner).SelText;
      EditorSearchOptions := EditorSearchOptions + [ssoSelectedOnly];         
      end
     else
      lkStr := Editor_SynEdit(TComponent(Sender).Owner).GetWordAtRowCol(Editor_SynEdit(TComponent(Sender).Owner).CaretXY);
    if(Editor_SearchReplaceDialog_Execute(true, lkStr, lkStrReplace, EditorSearchOptions))then
      begin
      Editor_SynEdit(TComponent(Sender).Owner).HelpKeyWord := lkStr;
      EditorSearchOptions := EditorSearchOptions + [ssoReplaceAll];
      if(not(Editor_SynEdit(TComponent(Sender).Owner).SearchReplace(lkStr, lkStrReplace, EditorSearchOptions) > 0))then
        Dialogs.MessageDlg(msg_string_not_found_more+#13#10+'"'+lkStr+'"', mtInformation, [mbOk]);
      EditorSearchOptions := EditorSearchOptions - [ssoReplaceAll];
      end;
  end;
  //============================================================================
  procedure Editor_actFormat_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := (Editor_SynEdit(TComponent(Sender).Owner).SelLength > 0);
  end;
  //============================================================================
  procedure Editor_actFormatIndentLeft_OnExecute(Sender: TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).DoBlockUnIndent;
  end;
  //============================================================================
  procedure Editor_actFormatIndentRight_OnExecute(Sender: TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).DoBlockIndent;
  end;
  //============================================================================
  procedure Editor_actFormatUpperCase_OnExecute(Sender: TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).DoCaseChange(ecUpperCaseBlock);
  end;
  //============================================================================
  procedure Editor_actFormatLowerCase_OnExecute(Sender: TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).DoCaseChange(ecLowerCaseBlock);
  end;
  //============================================================================
  procedure Editor_actFormatToggleCase_OnExecute(Sender: TObject);
  begin
    Editor_SynEdit(TComponent(Sender).Owner).DoCaseChange(ecToggleCaseBlock);
  end;
  //============================================================================
  procedure Editor_actFormatFoldingCollapse_OnExecute(Sender: TObject);
  begin
    {$IFDEF CODEFOLDING}
    Editor_SynEdit(TComponent(Sender).Owner).CollapseCurrent;
    {$ENDIF}
  end;
  //============================================================================
  procedure Editor_actFormatFoldingCollapseAll_OnExecute(Sender: TObject);
  begin
    {$IFDEF CODEFOLDING}
    Editor_SynEdit(TComponent(Sender).Owner).CollapseAll;
    {$ENDIF}
  end;
  //============================================================================
  procedure Editor_actFormatFoldingUnCollapse_OnExecute(Sender: TObject);
  begin
    {$IFDEF CODEFOLDING}
    Editor_SynEdit(TComponent(Sender).Owner).UncollapseLevel(0, true);
    {$ENDIF}
  end;
  //============================================================================
  procedure Editor_actFormatFoldingUnCollapseAll_OnExecute(Sender: TObject);
  begin
    {$IFDEF CODEFOLDING}
    Editor_SynEdit(TComponent(Sender).Owner).UncollapseAll;
    {$ENDIF}
  end;  
  //============================================================================
  function Editor_Preprocessor_OnNeedFile(Sender: TPSPreProcessor; const CallingFileName: String; var FileName, OutPut: String): Boolean;
  begin
    Result := Amunhotep.MainForm.OnPascalNeedFile(Sender, CallingFileName, FileName, OutPut);
  end;
  //============================================================================
  procedure Editor_actToolsPreprocess_OnExecute(Sender :TObject);
  var
    lkSynEdit :TSynEdit;
    lkRealSrc :string;
  begin
    if not ObjectInheritsFrom(TComponent(Sender).Owner, 'TAmunhotepEditorForm') then exit;
    if(TAmunhotepEditorForm(TComponent(Sender).Owner).FileType <> ftPas)then exit;
    lkSynEdit := TSynEdit(TComponent(Sender).Owner.FindComponent(editor_obj_name_synedit_preprocess));
    if(lkSynEdit = nil)then exit;
    lkSynEdit.Text := TAmunhotepForm(TComponent(Sender).Owner).FileName+#13#10+'-- starting file preporcess...';
    with TPSPreProcessor.Create(nil) do
      try
        MainFile        := StringsLoadFromFile(StrAbsolutePath('../conf/amunhotep.inc', Amunhotep.ExeName)) + Editor_SynEdit(TComponent(Sender).Owner).Text;
        MainFileName    := TAmunhotepForm(TComponent(Sender).Owner).FileName;
      finally  
        lkSynEdit.Text  := lkSynEdit.Text + #13#10 + PreProcess(MainFileName, lkRealSrc);
        TxcPageControlEx(TComponent(Sender).Owner.FindComponent(editor_obj_name_page_control)).ActivePageIndex := 2;
        Free;
      end;  
    lkSynEdit.Text := lkRealSrc;
  end;
  //============================================================================
  procedure Editor_actToolsHighlighter_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/DEVELOPMENT/EDITOR/DIALOGS/HIGHLIGHTER.PS');
  end;
  //============================================================================
  procedure Editor_actToolsGenGIUD_OnExecute(Sender :TObject);
  var
    lkGUID :TGUID;
  begin
    CoCreateGUID(lkGUID);
    Editor_SynEdit(TComponent(Sender).Owner).SelText := GUIDToStr(lkGUID);
  end;
  //============================================================================
  procedure Editor_actToolsGetCurrentFileName_OnExecute(Sender :TObject);
  var
    lkFileName :string;
  begin
    lkFileName := TAmunhotepForm(TComponent(Sender).Owner).FileName;
    if(Pos(StrReplaceStr(LowerCase(Amunhotep.SourcePath), '\', '/'), StrReplaceStr(LowerCase(lkFileName), '\', '/')) = 1)then
      begin
      Delete(lkFileName, 1, Length(Amunhotep.SourcePath));
      lkFileName := 'PEAKTOP:'+lkFileName;
      end;
    Editor_SynEdit(TComponent(Sender).Owner).SelText := lkFileName;
  end;
  //============================================================================
  procedure Editor_actToolsCaseImageIndex_OnExecute(Sender :TObject);
  var
    lkImageIndex :Integer;
  begin
    lkImageIndex := -1;
    if Dialogs.InputQueryImageIndex(msg_act_tools_caseimageindex_execute, Amunhotep.MainForm.ImageListMain, lkImageIndex)then
      Editor_SynEdit(TComponent(Sender).Owner).SelText := IntToStr(lkImageIndex);
  end;
  //============================================================================
  procedure Editor_actToolsCaseColor_OnExecute(Sender :TObject);
  var
    lkColor :TColor;
  begin
    lkColor := $FFFFFF;
    if Dialogs.SelectColor(lkColor)then
      Editor_SynEdit(TComponent(Sender).Owner).SelText := ColorToString(lkColor);
  end;
  //============================================================================
  procedure Editor_actToolsFormatSrc001_OnExecute(Sender :TObject);
  var
    lkStr1:string; 
    lkStr2:string;
    PP    :Integer;
  begin
    lkStr2    := Editor_SynEdit(TComponent(Sender).Owner).Text;
    lkStr1    := '(*----------------------------------------------------------------------------*)';
    PP := Pos(lkStr1, lkStr2);
    while(PP > 0)do
      begin
      Delete(lkStr2, PP, Length(lkStr1)+2 );
      PP := Pos(lkStr1, lkStr2);
      end;
    lkStr1 := #13#10+'begin';
    PP := Pos(lkStr1, lkStr2);
    while(PP > 0)do
      begin
      Delete(lkStr2, PP, 2);
      PP := Pos(lkStr1, lkStr2);
      end;
    lkStr1 := #13#10#13#10;
    PP := Pos(lkStr1, lkStr2);
    while(PP > 0)do
      begin
      Delete(lkStr2, PP, 2);
      PP := Pos(lkStr1, lkStr2);
      end;
    Editor_SynEdit(TComponent(Sender).Owner).Text := lkStr2;  
  end;
  //============================================================================
  procedure Editor_SynEdit_OnKeyUp(Sender: TObject; var Key: Word;Shift: TShiftState);
  var
    S    :string;
    tS   :string;
    k    :Integer;
  begin
    if( (Key = $0D {VK_RETURN}) and (Shift = [ssCtrl]) )then
      begin
      S := TSynEdit(Sender).Lines[TSynEdit(Sender).CaretY - 1];
      if( (Pos('{$I ', UpperCase(S)) > 0) or (Pos('{$INCLUDE ', UpperCase(S)) > 0) )then
        begin
        if(Pos('{$I ', UpperCase(S)) > 0)then
          begin
          Delete(S, 1, Pos('{$I ', UpperCase(S)) + 3);
          Delete(S, Pos('}', S), Length(S) - Pos('}', S) + 1);
          end
         else
          begin
          Delete(S, 1, Pos('{$INCLUDE ', UpperCase(S)) + 9);
          Delete(S, Pos('}', S), Length(S) - Pos('}', S) + 1);
          end;
        //S := TrimRight(S);
        if(Pos('PEAKTOP:', UpperCase(S))=1)then
          begin
          Delete(S, 1, 8);
          S := StrAbsolutePath(S, Amunhotep.SourcePath);
          end;
        if((Pos('../', S)=1)or(Pos('..\', S)=1)or(Pos('./', S)=1)or(Pos('.\', S)=1))then
          S := StrAbsolutePath(S, TAmunhotepForm(TComponent(Sender).Owner).FileName);
        //AmunhotepMainForm.CreateEditor(S, FileType);
        Amunhotep.MainForm.ProcessFile(S);
        end
       else
        begin
        tS := '';
        for k:=TSynEdit(Sender).CaretX to Length(S) do
          if(S[k]=#$27)then
            Break
           else
            tS := tS + S[k];
        for k:=TSynEdit(Sender).CaretX-1 downto 1 do
          if(S[k]=#$27)then
            Break
           else
            tS := S[k] + tS;
        if(Pos('PEAKTOP:', UpperCase(tS))=1)then
          begin
          Delete(tS, 1, 8);
          tS := StrAbsolutePath(tS, Amunhotep.SourcePath);
          end;
        if((Pos('../', tS)=1)or(Pos('..\', tS)=1)or(Pos('./', tS)=1)or(Pos('.\', tS)=1))then
          tS := StrAbsolutePath(tS, TAmunhotepForm(TComponent(Sender).Owner).FileName);
        Amunhotep.MainForm.ProcessFile(tS);
        end;
      end;
  end;
  //============================================================================
  function CreateEditorAction(
                   aOwnerForm           :TAmunhotepEditorForm;
             const aActionName          :string;
             const aActionCaption       :string;
             const aActionHint          :string;
             const aActionShortCut      :string;
             const aActionGroupIndex    :Integer;
             const aActionImageIndex    :Integer;
             const aActionOnExecute     :TNotifyEvent;
             const aActionOnUpdate      :TNotifyEvent;
             const aCreateMainMenuItem  :Boolean;
                   aParentMainMenuItem  :TMenuItem;
             const aCreatePopupMenuItem :Boolean;
                   aParentPopupMenuItem :TMenuItem;
             const aCreateToolBarButton :Boolean;
                   aToolBar             :TxcGradientPanel 
           ):TCustomAction;
  var
    lkMenuItemMain  :TMenuItem;
    lkMenuItemPopup :TMenuItem;         
    lkTBB           :TxcToolBarButton;
  begin
    Result           := CreateTAction(aOwnerForm, aActionName, aActionCaption, 
                          aActionHint, aActionShortCut, aActionGroupIndex, 
                          aActionImageIndex);
    Result.OnExecute := aActionOnExecute;
    Result.OnUpdate  := aActionOnUpdate;            
    if aCreateMainMenuItem then
      begin
      lkMenuItemMain        := TMenuItem.Create(aOwnerForm);
      if(StrTrimAll(Result.Name) <> '')then
        lkMenuItemMain.Name := 'mi'+Result.Name;
      lkMenuItemMain.Action := Result;
      aParentMainMenuItem.Add(lkMenuItemMain);
      Amunhotep.MainForm.xcMenu.AssignMethods(lkMenuItemMain);
      end;
    if aCreatePopupMenuItem then
      begin
      lkMenuItemPopup        := TMenuItem.Create(aOwnerForm);
      if(StrTrimAll(Result.Name) <> '')then
        lkMenuItemPopup.Name := 'pmi'+Result.Name;
      lkMenuItemPopup.Action := Result;
      aParentPopupMenuItem.Add(lkMenuItemPopup);
      Amunhotep.MainForm.xcMenu.AssignMethods(lkMenuItemPopup);
      end;
    if aCreateToolBarButton then
      begin
      lkTBB := CreateTxcToolBarButton2(aToolBar,aToolBar, 'tbb'+Result.Name, (aToolBar.ControlCount)*24,0,24,24,alLeft,Result);
      end;
  end;
  //============================================================================
  function CreateTMenuItemSeparator(aOwner :TComponent; aParentItem:TMenuItem):TMenuItem;
  begin
    Result              := TMenuItem.Create(aOwner);
    Result.Name         := 'mi'+RandomHexStr(16);
    Result.Caption      := '-';
    Amunhotep.MainForm.xcMenu.AssignMethods(Result);
    aParentItem.Add(Result);
  end;
  //============================================================================
  procedure Editor_ActionsCreate(aOwnerForm :TAmunhotepEditorForm);
  var
    lkSynEdit           :TSynEdit;
    lkToolBar           :TxcGradientPanelVista;
    lkTBB               :TxcToolBarButton;
    lkMainMenu          :TMainMenu;
    lkMenuItemMainTools :TMenuItem;
    lkMenuItemMainView  :TMenuItem;
    lkMenuItemMainFormat:TMenuItem;
    lkMenuItemMainEdit  :TMenuItem;
    lkMenuItemMainFile  :TMenuItem;
    lkMenuItem          :TMenuItem;
    lkAction            :TCustomAction;
  begin
    lkMainMenu             := aOwnerForm.Menu;
    lkSynEdit := Editor_SynEdit(aOwnerForm);
    with lkSynEdit do
      begin
      Ctl3D            := false;
      PopupMenu        := TPopupMenu.Create(aOwnerForm);
      PopupMenu.Name   := 'PopupMenuEditor';
      PopupMenu.Images := Amunhotep.MainForm.ImageListMain;
      SearchEngine     := TSynEditSearch.Create(lkSynEdit);
      OnKeyUp          := @Editor_SynEdit_OnKeyUp;
      end;
    lkToolBar := CreateTxcGradientPanelVistaToolBar(aOwnerForm, lkSynEdit.Parent,editor_obj_name_toolbarmain,'',alTop,0,0,24,100,xbsRaized);
    lkMenuItemMainTools    := TMenuItem(aOwnerForm.FindComponent('miToolsMain'));
    lkMenuItemMainTools.Caption     := msg_mi_main_tools;
    lkMenuItemMainTools.GroupIndex  := 45;
    lkMenuItemMainView              := TMenuItem.Create(aOwnerForm);
    lkMenuItemMainView.Name         := 'miEditView';
    lkMenuItemMainView.Caption      := msg_mi_main_view;
    lkMenuItemMainView.GroupIndex   := 44;
    Amunhotep.MainForm.xcMenu.AssignMethods(lkMenuItemMainView);
    lkMainMenu.Items.Insert(0, lkMenuItemMainView);
    lkMenuItemMainFormat            := TMenuItem.Create(aOwnerForm);
    lkMenuItemMainFormat.Name       := 'miFormatMain';
    lkMenuItemMainFormat.Caption    := msg_mi_main_format;
    lkMenuItemMainFormat.GroupIndex := 43;
    Amunhotep.MainForm.xcMenu.AssignMethods(lkMenuItemMainFormat);
    lkMainMenu.Items.Insert(0, lkMenuItemMainFormat);
    lkMenuItemMainEdit              := TMenuItem.Create(aOwnerForm);
    lkMenuItemMainEdit.Name         := 'miEditMain';
    lkMenuItemMainEdit.Caption      := msg_mi_main_edit;
    lkMenuItemMainEdit.GroupIndex   := 42;
    Amunhotep.MainForm.xcMenu.AssignMethods(lkMenuItemMainEdit);
    lkMainMenu.Items.Insert(0, lkMenuItemMainEdit);
    lkMenuItemMainFile              := TMenuItem.Create(aOwnerForm);
    lkMenuItemMainFile.Name         := 'miFileMain';
    lkMenuItemMainFile.Caption      := msg_mi_main_file;
    lkMenuItemMainFile.GroupIndex   := 41;
    Amunhotep.MainForm.xcMenu.AssignMethods(lkMenuItemMainFile);
    lkMainMenu.Items.Insert(0, lkMenuItemMainFile);

    // action FileSave
    lkAction := TAction(aOwnerForm.FindComponent('actFileSave'));
    with lkAction do
      begin
      ImageIndex := 107;
      Caption    := msg_act_file_save;
      Hint       := msg_act_file_save_hint;
      end;
    lkMenuItem := TMenuItem(aOwnerForm.FindComponent('miFileSave')); lkMenuItem.Free;
    lkMenuItem        := TMenuItem.Create(aOwnerForm);
    lkMenuItem.Name   := 'mi'+lkAction.Name;
    lkMenuItem.Action := lkAction;
    Amunhotep.MainForm.xcMenu.AssignMethods(lkMenuItem);
    lkMenuItemMainFile.Add(lkMenuItem);

    lkTBB := CreateTxcToolBarButton2(lkToolBar,lkToolBar, 'tbb'+lkAction.Name, (lkToolBar.ControlCount)*24,0,24,24,alLeft,lkAction);
    // create editor actions
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainFile);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFileExportHTML', msg_act_file_export_html, msg_act_file_export_html_hint, '', 0, 288, 
                    @Editor_actFileExportHTML_OnExecute, nil, true, lkMenuItemMainFile, false, nil, false, nil);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFileExportRTF', msg_act_file_export_rtf, msg_act_file_export_rtf_hint, '', 0, 4, 
                    @Editor_actFileExportRTF_OnExecute, nil, true, lkMenuItemMainFile, false, nil, false, nil);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainFile);

    
    lkAction   := CreateEditorAction(aOwnerForm, 'actEditUndo', msg_act_edit_undo, msg_act_edit_undo_hint, 'Ctrl+Z', 0, 75, 
                    @Editor_actEditUndo_OnExecute, @Editor_actEditUndo_OnUpdate, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actEditRedo', msg_act_edit_redo, msg_act_edit_redo_hint,  'Alt+Z', 0, 74, 
                    @Editor_actEditRedo_OnExecute, @Editor_actEditRedo_OnUpdate, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainEdit);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkSynEdit.PopupMenu.Items);

    lkAction   := CreateEditorAction(aOwnerForm, 'actEditCut',  msg_act_edit_cut, msg_act_edit_cut_hint,  'Shift+Del', 0, 69, 
                    @Editor_actEditCut_OnExecute, @Editor_actEditCut_OnUpdate,  true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actEditCopy', msg_act_edit_copy, msg_act_edit_copy_hint, 'Ctrl+Ins', 0, 68, 
                    @Editor_actEditCopy_OnExecute, @Editor_actEditCut_OnUpdate, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actEditPaste', msg_act_edit_paste, msg_act_edit_paste_hint, 'Shift+Ins', 0, 73, 
                    @Editor_actEditPaste_OnExecute, @Editor_actEditPaste_OnUpdate, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actEditDelete', msg_act_edit_delete, msg_act_edit_delete_hint, 'Ctrl+Del', 0, 70, 
                    @Editor_actEditDelete_OnExecute, @Editor_actEditCut_OnUpdate, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainEdit);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkSynEdit.PopupMenu.Items);
    lkAction   := CreateEditorAction(aOwnerForm, 'actEditSelectAll', msg_act_edit_selectall, msg_act_edit_selectall_hint,'Ctrl+A', 0, 245, 
                    @Editor_actEditSelectAll_OnExecute, nil, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainEdit);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkSynEdit.PopupMenu.Items);
    lkAction   := CreateEditorAction(aOwnerForm, 'actSearch', msg_act_search, msg_act_search_hint,'Ctrl+F', 0, 142, 
                    @Editor_actSearch_OnExecute, nil, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actSearchNext', msg_act_search_next, msg_act_search_next_hint,'F3', 0, 142, 
                    @Editor_actSearchNext_OnExecute, nil, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actSearchReplace', msg_act_search_replace, msg_act_search_replace_hint,'Ctrl+R', 0, 145, 
                    @Editor_actSearchReplace_OnExecute, nil, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actEditGotoLineNumber', msg_act_edit_GotoLineNumber, msg_act_edit_GotoLineNumber_hint,'Alt+G', 0, 144, 
                    @Editor_actEditGotoLineNumber_OnExecute, nil, true, lkMenuItemMainEdit, true, lkSynEdit.PopupMenu.Items, true, lkToolBar);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainEdit);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkSynEdit.PopupMenu.Items);

    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatIndentLeft', msg_act_format_indent_left, msg_act_format_indent_left_hint, 'Ctrl+Shift+U', 0, 131, 
                    @Editor_actFormatIndentLeft_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatIndentRight', msg_act_format_indent_right, msg_act_format_indent_right_hint, 'Ctrl+Shift+I', 0, 132, 
                    @Editor_actFormatIndentRight_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, true, lkToolBar);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainFormat);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatUpperCase', msg_act_format_upper_case, msg_act_format_upper_case_hint, 'Alt+Up', 0, 251, 
                    @Editor_actFormatUpperCase_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatLowerCase', msg_act_format_lower_case, msg_act_format_lower_case_hint, 'Alt+Down', 0, 252, 
                    @Editor_actFormatLowerCase_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatToggleCase', msg_act_format_toggle_case, msg_act_format_toggle_case_hint, 'Alt+Right', 0, 253, 
                    @Editor_actFormatToggleCase_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, true, lkToolBar);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainFormat);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatFoldingCollapse', msg_act_format_folding_collapse, msg_act_format_folding_collapse_hint, '', 0, -1, 
                    @Editor_actFormatFoldingCollapse_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, false, nil);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatFoldingCollapseAll', msg_act_format_folding_collapseall, msg_act_format_folding_collapseall_hint, '', 0, -1, 
                    @Editor_actFormatFoldingCollapseAll_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, false, nil);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatFoldingUnCollapse', msg_act_format_folding_uncollapse, msg_act_format_folding_uncollapse_hint, '', 0, -1, 
                    @Editor_actFormatFoldingUnCollapse_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, false, nil);
    lkAction   := CreateEditorAction(aOwnerForm, 'actFormatFoldingUnCollapseAll', msg_act_format_folding_uncollapseall, msg_act_format_folding_uncollapseall_hint, '', 0, -1, 
                    @Editor_actFormatFoldingUnCollapseAll_OnExecute, @Editor_actFormat_OnUpdate, true, lkMenuItemMainFormat, false, nil, false, nil);
    lkAction   := CreateEditorAction(aOwnerForm, 'actToolsPreprocessing', msg_act_tools_preprocess, msg_act_tools_preprocess_hint, 'Ctrl+F10', 0, 22, 
                    @Editor_actToolsPreprocess_OnExecute, nil, true, lkMenuItemMainTools, false, nil, true, lkToolBar);
    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainTools);

    lkAction   := CreateEditorAction(aOwnerForm, 'actToolsHighlighter', msg_act_tools_highlighter, msg_act_tools_highlighter_hint, '', 0, 26, 
                    @Editor_actToolsHighlighter_OnExecute, nil, true, lkMenuItemMainTools, false, nil, true, lkToolBar);

    lkAction   := CreateEditorAction(aOwnerForm, 'actToolsCaseImageIndex', msg_act_tools_caseimageindex, msg_act_tools_caseimageindex_hint, 'Ctrl+F5', 0, 283, 
                    @Editor_actToolsCaseImageIndex_OnExecute, nil, true, lkMenuItemMainTools, false, nil, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actToolsCaseColor', msg_act_tools_casecolor, msg_act_tools_casecolor_hint, 'Ctrl+F7', 0, 255, 
                    @Editor_actToolsCaseColor_OnExecute, nil, true, lkMenuItemMainTools, false, nil, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actToolsGenGUID', msg_act_tools_genguid, msg_act_tools_genguid_hint, 'Ctrl+Shift+G', 0, 19, 
                    @Editor_actToolsGenGIUD_OnExecute, nil, true, lkMenuItemMainTools, false, nil, true, lkToolBar);
    lkAction   := CreateEditorAction(aOwnerForm, 'actToolsGetCurrentFileName', msg_act_tools_getcurrentfilename, msg_act_tools_getcurrentfilename_hint, 'Ctrl+Shift+D', 0, 92, 
                    @Editor_actToolsGetCurrentFileName_OnExecute, nil, true, lkMenuItemMainTools, false, nil, true, lkToolBar);

    lkMenuItem := CreateTMenuItemSeparator(aOwnerForm, lkMenuItemMainTools);

    lkAction   := CreateEditorAction(aOwnerForm, 'actToolsFormatSrc001', msg_act_tools_formatsrc001, msg_act_tools_formatsrc001_hint, '', 0, 291, 
                    @Editor_actToolsFormatSrc001_OnExecute, nil, true, lkMenuItemMainTools, false, nil, true, lkToolBar);

    lkAction := TAction(aOwnerForm.FindComponent('actScriptRun'));
    lkAction.ImageIndex    := 24;
    lkTBB := CreateTxcToolBarButton2(lkToolBar,lkToolBar, 'tbb'+lkAction.Name, (lkToolBar.ControlCount)*24,0,24,24,alLeft,lkAction);

    Amunhotep.MainForm.xcMenu.AddMenu(lkSynEdit.PopupMenu);
  end;
