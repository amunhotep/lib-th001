{$DEFINE PEAKTOP:IDE/DEVELOPMENT/EDITOR/LNGPASCAL/PREPROCESSED.INC}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                 {$I PEAKTOP:OBJ/TXCTABSHEET.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}      {$I PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/EDITOR/OBJNAMES.INC} {$I ../OBJNAMES.INC}                         {$ENDIF}
  //======== PEAKTOP:IDE/DEVELOPMENT/EDITOR/LNGPASCAL/PREPROCESSED.INC =========
  procedure Editor_PagePreprocess_Create(aOwnerForm :TAmunhotepEditorForm);
  var
    lkPC :TxcPageControlEx;
    lkTS :TxcTabSheet;
  begin
    lkPC := TxcPageControlEx(aOwnerForm.FindComponent(editor_obj_name_page_control));
    lkTS := CreateTxcTabSheet(lkPC, 'tsPreprocessed', 'Preprocessed', 26, Amunhotep.MainForm.StyleManager.Colors.Highlight)
    RegisterSynEdit(Interface_SynEdit_Create(aOwnerForm, lkTS, editor_obj_name_synedit_preprocess), ftPAS);
  end;
