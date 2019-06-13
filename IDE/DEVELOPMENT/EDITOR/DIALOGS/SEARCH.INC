{$DEFINE PEAKTOP:IDE/DEVELOPMENT/EDITOR/DIALOGS/SEARCH.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}    {$I PEAKTOP:GLOBAL_VARIABLES.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCCHECKBOX.INC}     {$I PEAKTOP:OBJ/TXCCHECKBOX.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}{$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}{$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCBUTTON.INC}       {$I PEAKTOP:OBJ/TXCBUTTON.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOMBOBOX.INC}       {$I PEAKTOP:OBJ/TCOMBOBOX.INC}       {$ENDIF}
const  //============== PEAKTOP:APPL/TOOLS_API/EDITOR_SEARCHDIALOG.INC =========
  msg_search_dialog_caption               = 'Найти';
  msg_btn_ok_caption                      = 'Найти';
  msg_btn_cancel_caption                  = 'Отмена';
  msg_search_options                      = 'Параметры поиска';
  msg_so_matchcase                        = 'С учетом регистра символов';
  msg_so_wholeword                        = 'Искать слово целиком';
  msg_so_backward                         = 'Искать назад по тексту';
  msg_so_selected                         = 'Только в выделенном фрагменте';
  EditorSearchDialog_FileName = 'TMP:AMUNHOTEP_EDITOR_SEARCH.CFG';
  //============================================================================
  function Editor_SearchReplaceDialog_Execute(const aReplaceDialog:Boolean; var aSearchStr, aReplaceStr:string; var aSO :TSynSearchOptions):Boolean;
  var
    lkStr         :string;
    lkForm        :TForm;
    lkCbx         :TComboBox;
    lkCbxReplace  :TComboBox;
    lkGrBx        :TxcGroupBox;
    lkChkMatchCase:TxcCheckBox;
    lkChkWholeWord:TxcCheckBox;
    lkChkBackward :TxcCheckBox;
    lkChkSelected :TxcCheckBox;
    lkBottomPanel :TxcGradientPanel;
    lkBtnCancel   :TxcButton; 
    lkBtnOK       :TxcButton; 
    lkLastTop     :Integer;
  begin
    lkStr := PrepareAbsoleteFileName(EditorSearchDialog_FileName); 
    if(FileExists(lkStr))then
      lkStr := StringsLoadFromFile(lkStr)
     else
      lkStr := ''; 
    lkForm  := TForm.Create(nil);
    with lkForm do
      begin
      BorderStyle := bsDialog;
      Caption     := msg_search_dialog_caption;
      Position    := poDesktopCenter;
      Width       := 240;
      Height      := 190;
      Color       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Color  := Amunhotep.MainForm.StyleManager.Colors.Border;
      end;
    lkLastTop := 2;  
    lkCbx := CreateTComboBox(lkForm,lkForm,aSearchStr,2,lkLastTop,20,lkForm.Width - 8,lkStr,-1); lkLastTop := lkLastTop + 22; 
    if aReplaceDialog then
      lkCbxReplace := CreateTComboBox(lkForm,lkForm,aReplaceStr,2,lkLastTop,20,lkForm.Width - 8,lkStr,-1); lkLastTop := lkLastTop + 22; 
    lkGrBx := TxcGroupBox.Create(lkForm);
    with lkGrBx do
      begin
      Parent       := lkForm;
      Left         := lkCbx.Left;
      Top          := lkLastTop;
      Width        := lkCbx.Width;
      Height       := 96;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Caption      := msg_search_options;
      end;
    lkChkMatchCase := CreateTxcCheckBox(lkForm,lkGrBx,'lkChkMatchCase',msg_so_matchcase,msg_so_matchcase,alNone,2,                                        16,16,lkGrBx.Width-16,((aSO + [ssoMatchCase]   ) = aSO));  
    lkChkWholeWord := CreateTxcCheckBox(lkForm,lkGrBx,'lkChkWholeWord',msg_so_wholeword,msg_so_wholeword,alNone,2,lkChkMatchCase.Top+lkChkMatchCase.Height+2,16,lkGrBx.Width-16,((aSO + [ssoWholeWord]   ) = aSO));  
    lkChkBackward  := CreateTxcCheckBox(lkForm,lkGrBx,'lkChkBackward' ,msg_so_backward ,msg_so_backward ,alNone,2,lkChkWholeWord.Top+lkChkWholeWord.Height+2,16,lkGrBx.Width-16,((aSO + [ssoBackwards]   ) = aSO));  
    lkChkSelected  := CreateTxcCheckBox(lkForm,lkGrBx,'lkChkSelected' ,msg_so_selected ,msg_so_selected ,alNone,2,lkChkBackward.Top +lkChkBackward.Height +2,16,lkGrBx.Width-16,((aSO + [ssoSelectedOnly]) = aSO));  
    lkBottomPanel  := CreateTxcGradientPanel(lkForm,lkForm,'PanelBottom','',alBottom,1,1,20,lkForm.Width,xbsNone,gdLeftToRight);
    lkBottomPanel.Font.Style   := [fsBold];
    lkBtnCancel := CreateTxcButton(lkForm,lkBottomPanel,'btnCancel',msg_btn_cancel_caption,lkBottomPanel.Width  - 65,1,lkBottomPanel.Height-2,64,mrCancel,false,true );
    lkBtnOK     := CreateTxcButton(lkForm,lkBottomPanel,'btnOK'    ,msg_btn_ok_caption    ,lkBottomPanel.Width - 130,1,lkBottomPanel.Height-2,64,mrOK    ,true ,false);
    Result := (lkForm.ShowModal = mrOk);
    if(Result)then
      begin
      aSearchStr := lkCbx.Text;
      if aReplaceDialog then
        aReplaceStr := lkCbxReplace.Text;
      if lkChkMatchCase.Checked then aSO := aSO + [ssoMatchCase   ] else aSO := aSO - [ssoMatchCase   ];
      if lkChkWholeWord.Checked then aSO := aSO + [ssoWholeWord   ] else aSO := aSO - [ssoWholeWord   ];
      if lkChkBackward.Checked  then aSO := aSO + [ssoBackwards   ] else aSO := aSO - [ssoBackwards   ];
      if lkChkSelected.Checked  then aSO := aSO + [ssoSelectedOnly] else aSO := aSO - [ssoSelectedOnly];
      if(not(lkCbx.Items.IndexOf(aSearchStr)>0))then
        lkCbx.Items.Insert(0, aSearchStr);
      lkStr := PrepareAbsoleteFileName(EditorSearchDialog_FileName); 
      StringsSaveToFile(lkStr, lkCbx.Items.Text);
      end;
    lkForm.Free;  
  end;
  //============================================================================
  function EditorSearchDialog_Execute(var aSearchStr:string; var aSO :TSynSearchOptions):Boolean;
  var
    lkDummyStr :string;
  begin
    Result := Editor_SearchReplaceDialog_Execute(false, aSearchStr, lkDummyStr, aSO);
  end;
