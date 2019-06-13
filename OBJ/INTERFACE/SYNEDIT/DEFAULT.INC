{$DEFINE PEAKTOP:OBJ/INTERFACE/SYNEDIT/DEFAULT.INC}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/$COMMON.INC} {$I ../$COMMON.INC} {$ENDIF}
const //=========== PEAKTOP:OBJ/INTERFACE/SYNEDIT.INC ==========================
  msg_interface_synedit_dialog_filter = 'Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*';
  //============================================================================
  procedure actInterfaceSynEdit_Load_OnExecute(Sender :TObject);
  var
    lkSynEdit:TSynEdit;
    lkFileName :string;
  begin
    lkFileName := '';
    lkSynEdit  := TSynEdit(TCustomAction(Sender).Owner);
    if PromptForFileName(lkFileName,msg_Interface_synedit_dialog_filter,'txt',msg_Interface_actload_hint,'', false)then
      lkSynEdit.Lines.LoadFromFile(lkFileName);
  end;
  //============================================================================
  procedure actInterfaceSynEdit_Save_OnExecute(Sender :TObject);
  var
    lkSynEdit:TSynEdit;
    lkFileName :string;
  begin
    lkFileName := '';
    lkSynEdit := TSynEdit(TCustomAction(Sender).Owner);
    if PromptForFileName(lkFileName,msg_Interface_synedit_dialog_filter,'txt',msg_Interface_actsave_hint,'', true)then
      try
        lkSynEdit.Lines.SaveToFile(lkFileName);
      finally
      end;
  end;
  //============================================================================
  procedure actInterfaceSynEdit_Cut_OnExecute(Sender :TObject);
  begin
    TSynEdit(TCustomAction(Sender).Owner).CutToClipboard;
  end;
  //============================================================================
  procedure actInterfaceSynEdit_Copy_OnExecute(Sender :TObject);
  begin
    TSynEdit(TCustomAction(Sender).Owner).CopyToClipboard;
  end;
  //============================================================================
  procedure actInterfaceSynEdit_Paste_OnExecute(Sender :TObject);
  begin
    TSynEdit(TCustomAction(Sender).Owner).PasteFromClipboard;
  end;
  //============================================================================
  procedure actInterfaceSynEdit_Delete_OnExecute(Sender :TObject);
  begin
    TSynEdit(TCustomAction(Sender).Owner).ClearSelection;
  end;
  //============================================================================
  procedure actInterfaceSynEdit_SelectAll_OnExecute(Sender :TObject);
  begin
    TSynEdit(TCustomAction(Sender).Owner).SelectAll;
  end;
  //============================================================================
  function Interface_SynEdit_Create(aOwner :TComponent; aParent :TWinControl; const aName :string):TSynEdit;
  var
    lkTB :TxcGradientPanelVista;
    lkAct:TCustomAction;
  begin
    DontAutoFree;
    lkTB := CreateTxcGradientPanelVistaToolBar(aParent, aParent, aName+'_ToolBar','',alTop,0,0,24,24,xbsRaized);
    Result := TSynEdit.Create(aOwner);
    with Result do
      begin
      Name       := aName;
      Ctl3D      := false;
      Parent     := aParent;
      Align      := alClient;
      Lines.Text := '';
      end;
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntfSynEdit_Load'     ,msg_interface_actload     ,msg_Interface_actload_hint     ,'',0, 30,@actInterfaceSynEdit_Load_OnExecute     ,nil);
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntfSynEdit_Save'     ,msg_Interface_actsave     ,msg_Interface_actsave_hint     ,'',0,107,@actInterfaceSynEdit_Save_OnExecute     ,nil);
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntfSynEdit_Cut'      ,msg_Interface_actcut      ,msg_Interface_actcut_hint      ,'',0, 69,@actInterfaceSynEdit_Cut_OnExecute      ,nil);
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntfSynEdit_Copy'     ,msg_Interface_actcopy     ,msg_Interface_actcopy_hint     ,'',0, 68,@actInterfaceSynEdit_Copy_OnExecute     ,nil);
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntfSynEdit_Paste'    ,msg_Interface_actpaste    ,msg_Interface_actpaste_hint    ,'',0, 73,@actInterfaceSynEdit_Paste_OnExecute    ,nil);
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntfSynEdit_Delete'   ,msg_Interface_actdelete   ,msg_Interface_actdelete_hint   ,'',0, 70,@actInterfaceSynEdit_Delete_OnExecute   ,nil);
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntfSynEdit_SelectAll',msg_Interface_actselectall,msg_Interface_actselectall_hint,'',0,245,@actInterfaceSynEdit_SelectAll_OnExecute,nil);
  end;
