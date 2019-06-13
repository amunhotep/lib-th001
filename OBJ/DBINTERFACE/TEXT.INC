{$DEFINE PEAKTOP:OBJ/DBINTERFACE/TEXT.INC}
{$IFNDEF PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC}   {$I PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC}   {$ENDIF}
const //=================== PEAKTOP:OBJ/DBINTERFACE/TEXT.INC ===================
  msg_dbinterface_text_dialog_filter = 'Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*';
  //============================================================================
  procedure actDBInterfaceText_Load_OnExecute(Sender :TObject);
  var
    lkDBMemo   :TDBMemo;
    lkFileName :string;
  begin
    lkFileName := '';
    if TDBMemo(TCustomAction(Sender).Owner).ReadOnly then 
      begin
      Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
         msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
      exit;
      end;
    lkDBMemo   := TDBMemo(TCustomAction(Sender).Owner);
    if PromptForFileName(lkFileName,msg_dbinterface_text_dialog_filter,'txt',msg_dbinterface_actload_hint,'', false)then
      try
        lkDBMemo.DataSource.DataSet.Edit;
      finally
        lkDBMemo.Lines.LoadFromFile(lkFileName);
        lkDBMemo.DataSource.DataSet.Post;
      end
  end;
  //============================================================================
  procedure actDBInterfaceText_Save_OnExecute(Sender :TObject);
  var
    lkDBMemo   :TDBMemo;
    lkFileName :string;
  begin
    lkFileName := '';
    lkDBMemo   := TDBMemo(TCustomAction(Sender).Owner);
    if PromptForFileName(lkFileName,msg_dbinterface_text_dialog_filter,'txt',msg_dbinterface_actsave_hint,'', true)then
      try
        lkDBMemo.Lines.SaveToFile(lkFileName);
      finally
      end
  end;
  //============================================================================
  procedure actDBInterfaceText_Cut_OnExecute(Sender :TObject);
  begin
    if TDBMemo(TCustomAction(Sender).Owner).ReadOnly then 
      begin
      Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
         msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
      exit;
      end;
    try 
      TDBMemo(TCustomAction(Sender).Owner).DataSource.DataSet.Edit;
      TDBMemo(TCustomAction(Sender).Owner).CutToClipboard;
    finally
      TDBMemo(TCustomAction(Sender).Owner).DataSource.DataSet.Post;
    end;  
  end;
  //============================================================================
  procedure actDBInterfaceText_Copy_OnExecute(Sender :TObject);
  begin
    TDBMemo(TCustomAction(Sender).Owner).CopyToClipboard;
  end;
  //============================================================================
  procedure actDBInterfaceText_Paste_OnExecute(Sender :TObject);
  begin
    if TDBMemo(TCustomAction(Sender).Owner).ReadOnly then 
      begin
      Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
         msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
      exit;
      end;
    try 
      TDBMemo(TCustomAction(Sender).Owner).DataSource.DataSet.Edit;
      TDBMemo(TCustomAction(Sender).Owner).PasteFromClipboard;
    finally
      TDBMemo(TCustomAction(Sender).Owner).DataSource.DataSet.Post;
    end;  
  end;
  //============================================================================
  procedure actDBInterfaceText_Delete_OnExecute(Sender :TObject);
  begin
    if TDBMemo(TCustomAction(Sender).Owner).ReadOnly then 
      begin
      Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
         msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
      exit;
      end;
    try 
      TDBMemo(TCustomAction(Sender).Owner).DataSource.DataSet.Edit;
      TDBMemo(TCustomAction(Sender).Owner).Clear;
    finally
      TDBMemo(TCustomAction(Sender).Owner).DataSource.DataSet.Post;
    end;  
  end;
  //============================================================================
  procedure actDBInterfaceText_SelectAll_OnExecute(Sender :TObject);
  begin
    TDBMemo(TCustomAction(Sender).Owner).SelectAll;
  end;
  //============================================================================
  procedure DBInterfaceCreateText(
              aOwner      :TComponent;   // Owner component
              aParent     :TWinControl;  // Parent Control for interface
              aDataSource :TDataSource;  // Data source for db-aware controls
              aDataField  :string;       // Data field for db-aware controls
              aReadOnly   :Boolean       // Read-only access to data field
            );
  var
    lkTB :TxcGradientPanelVista;
    lkAct:TCustomAction;
    lkM  :TDBMemo;   
    lkLbl:TLabel;       
  begin
    DontAutoFree;
    lkTB := CreateTxcGradientPanelVistaToolBar(aOwner, aParent, '','',alTop,0,0,24,24,xbsRaized);
    lkM  := TDBMemo.Create(aOwner);
    with lkM do
      begin
      Parent     := aParent;
      Align      := alClient;
      Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
      Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      Ctl3D      := false;
      DataSource := aDataSource;
      DataField  := aDataField;
      ScrollBars := ssBoth;
      ReadOnly   := aReadOnly;
      WordWrap   := true;
      if aReadOnly then
        Color := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      end;
    lkAct:=DBInterface_CreateTAction2(lkM,lkTB,68,true ,'actDBIntf_Text_Load'     ,msg_dbinterface_actload     ,msg_dbinterface_actload_hint     ,'', 0, 30,@actDBInterfaceText_Load_OnExecute     , nil);
    lkAct:=DBInterface_CreateTAction2(lkM,lkTB,80,true ,'actDBIntf_Text_Save'     ,msg_dbinterface_actsave     ,msg_dbinterface_actsave_hint     ,'', 0,107,@actDBInterfaceText_Save_OnExecute     , nil);
    lkLbl:=CreateTLabel(lkM, lkTB, '|', lkTB.ControlCount * 80, 1, lkTB.Height, 8, alLeft, taCenter);
    lkAct:=DBInterface_CreateTAction2(lkM,lkTB,22,false,'actDBIntf_Text_Cut'      ,msg_dbinterface_actcut      ,msg_dbinterface_actcut_hint      ,'', 0, 69,@actDBInterfaceText_Cut_OnExecute      , nil);
    lkAct:=DBInterface_CreateTAction2(lkM,lkTB,22,false,'actDBIntf_Text_Copy'     ,msg_dbinterface_actcopy     ,msg_dbinterface_actcopy_hint     ,'', 0, 68,@actDBInterfaceText_Copy_OnExecute     , nil);
    lkAct:=DBInterface_CreateTAction2(lkM,lkTB,22,false,'actDBIntf_Text_Paste'    ,msg_dbinterface_actpaste    ,msg_dbinterface_actpaste_hint    ,'', 0, 73,@actDBInterfaceText_Paste_OnExecute    , nil);
    lkAct:=DBInterface_CreateTAction2(lkM,lkTB,22,false,'actDBIntf_Text_Delete'   ,msg_dbinterface_actdelete   ,msg_dbinterface_actdelete_hint   ,'', 0, 70,@actDBInterfaceText_Delete_OnExecute   , nil);
    lkLbl:=CreateTLabel(lkM, lkTB, '|', lkTB.ControlCount * 80, 1, lkTB.Height, 8, alLeft, taCenter);
    lkAct:=DBInterface_CreateTAction2(lkM,lkTB,96,true ,'actDBIntf_Text_SelectAll',msg_dbinterface_actselectall,msg_dbinterface_actselectall_hint,'', 0,245,@actDBInterfaceText_SelectAll_OnExecute, nil);
  end;
