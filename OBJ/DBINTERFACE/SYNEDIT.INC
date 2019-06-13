{$DEFINE PEAKTOP:OBJ/DBINTERFACE/SYNEDIT.INC}
{$IFNDEF PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC}{$I PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC}{$ENDIF}
const //=========== PEAKTOP:OBJ/DBINTERFACE/SYNEDIT.INC ========================
  msg_dbinterface_synedit_dialog_filter = 'Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*';
  //============================================================================
  procedure actDBInterfaceSynEdit_Load_OnExecute(Sender :TObject);
  var
    lkDBSynEdit:TDBSynEdit;
    lkFileName :string;
  begin
    lkFileName := '';
    lkDBSynEdit  := TDBSynEdit(TCustomAction(Sender).Owner);
    if PromptForFileName(lkFileName,msg_dbinterface_synedit_dialog_filter,'txt',msg_dbinterface_actload_hint,'', false)then
      try
        lkDBSynEdit.DataSource.DataSet.Edit;
      finally
        lkDBSynEdit.Lines.LoadFromFile(lkFileName);
        lkDBSynEdit.DataSource.DataSet.Post;
      end
  end;
  //============================================================================
  procedure actDBInterfaceSynEdit_Save_OnExecute(Sender :TObject);
  var
    lkDBSynEdit:TDBSynEdit;
    lkFileName :string;
  begin
    lkFileName := '';
    lkDBSynEdit := TDBSynEdit(TCustomAction(Sender).Owner);
    if PromptForFileName(lkFileName,msg_dbinterface_synedit_dialog_filter,'txt',msg_dbinterface_actsave_hint,'', true)then
      try
        lkDBSynEdit.Lines.SaveToFile(lkFileName);
      finally
      end;
  end;
  //============================================================================
  procedure actDBInterfaceSynEdit_Cut_OnExecute(Sender :TObject);
  begin
    try 
      TDBSynEdit(TCustomAction(Sender).Owner).DataSource.DataSet.Edit;
      TDBSynEdit(TCustomAction(Sender).Owner).CutToClipboard;
    finally
      TDBSynEdit(TCustomAction(Sender).Owner).DataSource.DataSet.Post;
    end;  
  end;
  //============================================================================
  procedure actDBInterfaceSynEdit_Copy_OnExecute(Sender :TObject);
  begin
    TDBSynEdit(TCustomAction(Sender).Owner).CopyToClipboard;
  end;
  //============================================================================
  procedure actDBInterfaceSynEdit_Paste_OnExecute(Sender :TObject);
  begin
    try 
      TDBSynEdit(TCustomAction(Sender).Owner).DataSource.DataSet.Edit;
      TDBSynEdit(TCustomAction(Sender).Owner).PasteFromClipboard;
    finally
      TDBSynEdit(TCustomAction(Sender).Owner).DataSource.DataSet.Post;
    end;  
  end;
  //============================================================================
  procedure actDBInterfaceSynEdit_Delete_OnExecute(Sender :TObject);
  begin
    try 
      TDBSynEdit(TCustomAction(Sender).Owner).DataSource.DataSet.Edit;
      TDBSynEdit(TCustomAction(Sender).Owner).ClearSelection;
    finally
      TDBSynEdit(TCustomAction(Sender).Owner).DataSource.DataSet.Post;
    end;  
  end;
  //============================================================================
  procedure actDBInterfaceSynEdit_SelectAll_OnExecute(Sender :TObject);
  begin
    TDBSynEdit(TCustomAction(Sender).Owner).SelectAll;
  end;
  //============================================================================
  procedure DBInterfaceCreateSynEdit(
              aOwner      :TComponent;   // Owner component
              aParent     :TWinControl;  // Parent Control for interface
              aDataSource :TDataSource;  // Data source for db-aware controls
              aDataField  :string;       // Data field for db-aware controls
              aReadOnly   :Boolean;      // Read-only access to data field
              aFieldType  :string        // Field-type string
           );
  var
    lkSE :TDBSynEdit;
    lkTB :TxcGradientPanelVista;
    lkAct:TCustomAction;
  begin
    DontAutoFree;
    lkTB := CreateTxcGradientPanelVistaToolBar(aOwner, aParent, '','',alTop,0,0,24,24,xbsRaized);
    lkSE := TDBSynEdit.Create(aOwner);
    with lkSE do
      begin
      Parent     := aParent;
      DataSource := aDataSource;
      DataField  := aDataField;
      ReadOnly   := aReadOnly;
      Align      := alClient;
      Lines.Text := '';
      end;
    lkAct:=DBInterface_CreateTAction(lkSE,lkTB,'actDBIntf_SynEdit_Load'     ,msg_dbinterface_actload     ,msg_dbinterface_actload_hint     ,'',0, 30,@actDBInterfaceSynEdit_Load_OnExecute     ,nil);
    lkAct:=DBInterface_CreateTAction(lkSE,lkTB,'actDBIntf_SynEdit_Save'     ,msg_dbinterface_actsave     ,msg_dbinterface_actsave_hint     ,'',0,107,@actDBInterfaceSynEdit_Save_OnExecute     ,nil);
    lkAct:=DBInterface_CreateTAction(lkSE,lkTB,'actDBIntf_SynEdit_Cut'      ,msg_dbinterface_actcut      ,msg_dbinterface_actcut_hint      ,'',0, 69,@actDBInterfaceSynEdit_Cut_OnExecute      ,nil);
    lkAct:=DBInterface_CreateTAction(lkSE,lkTB,'actDBIntf_SynEdit_Copy'     ,msg_dbinterface_actcopy     ,msg_dbinterface_actcopy_hint     ,'',0, 68,@actDBInterfaceSynEdit_Copy_OnExecute     ,nil);
    lkAct:=DBInterface_CreateTAction(lkSE,lkTB,'actDBIntf_SynEdit_Paste'    ,msg_dbinterface_actpaste    ,msg_dbinterface_actpaste_hint    ,'',0, 73,@actDBInterfaceSynEdit_Paste_OnExecute    ,nil);
    lkAct:=DBInterface_CreateTAction(lkSE,lkTB,'actDBIntf_SynEdit_Delete'   ,msg_dbinterface_actdelete   ,msg_dbinterface_actdelete_hint   ,'',0, 70,@actDBInterfaceSynEdit_Delete_OnExecute   ,nil);
    lkAct:=DBInterface_CreateTAction(lkSE,lkTB,'actDBIntf_SynEdit_SelectAll',msg_dbinterface_actselectall,msg_dbinterface_actselectall_hint,'',0,245,@actDBInterfaceSynEdit_SelectAll_OnExecute,nil);
         if(UpperCase(aFieldType) = 'DOMN$BLOB_SQL' )then RegisterSynEdit(lkSE, ftSQL)
    else if(UpperCase(aFieldType) = 'DOMN$BLOB_PAS' )then RegisterSynEdit(lkSE, ftPAS)
    else if(UpperCase(aFieldType) = 'DOMN$BLOB_XFM' )then RegisterSynEdit(lkSE, ftDFM)
    else if(UpperCase(aFieldType) = 'DOMN$BLOB_PHP' )then RegisterSynEdit(lkSE, ftPHP)
    else if(UpperCase(aFieldType) = 'DOMN$BLOB_HTML')then RegisterSynEdit(lkSE, ftHTML)
    else if(UpperCase(aFieldType) = 'DOMN$BLOB_HTM' )then RegisterSynEdit(lkSE, ftHTML)
    else if(UpperCase(aFieldType) = 'DOMN$BLOB_XML' )then RegisterSynEdit(lkSE, ftXML)
    ;
    if aReadOnly then
      lkSE.Color := Amunhotep.MainForm.StyleManager.Colors.Foreground;
  end;
