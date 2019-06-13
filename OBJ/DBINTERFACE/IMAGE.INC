{$DEFINE PEAKTOP:OBJ/DBINTERFACE/IMAGE.INC}
{$IFNDEF PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC}   {$I PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/IMG/DIALOG_WEBCAM.INC}{$I PEAKTOP:SYSUTILS/IMG/DIALOG_WEBCAM.INC} {$ENDIF}
const //============== PEAKTOP:OBJ/DBINTERFACE/IMAGE.INC =======================
  msg_dbinterface_image_dialog_filter = 'Файлы изображений (*.bmp;*.ico;*.jpg;*.jpeg;*.png)|*.bmp;*.ico;*.jpg;*.jpeg;*.png|Все файлы (*.*)|*.*';
  //============================================================================
  procedure actDBInterfaceImage_Load_OnExecute(Sender :TObject);
  var
    lkFileName :string;
  begin
    lkFileName := '';
    if TxcDBImage(TCustomAction(Sender).Owner).ReadOnly then 
      begin
      Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
         msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
      exit;
      end;
    if not PromptForFileName(lkFileName,msg_dbinterface_image_dialog_filter,'bmp',msg_dbinterface_actload_hint,'', false)then exit;
    with TxcDBImage(TCustomAction(Sender).Owner) do
      try
        if(DataSource.DataSet.State = dsBrowse)then
          begin
          if(DataSource.DataSet.RecordCount = 0)then
            DataSource.DataSet.Append
           else 
            DataSource.DataSet.Edit;
          end;
        if DataSource.DataSet.FieldByName(DataField).IsBlob then  
          TBlobField(DataSource.DataSet.FieldByName(DataField)).LoadFromFile(lkFileName);
      finally
      end
  end;
  //============================================================================
  procedure actDBInterfaceImage_LoadWebCam_OnExecute(Sender :TObject);
  var
    lkFileName :string;
  begin
    with TxcDBImage(TCustomAction(Sender).Owner) do
      begin
      if ReadOnly then 
        begin
        Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
           msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
        exit;
        end;
      lkFileName := PrepareAbsoleteFileName(DialogWebCam_FileNameImage+FormatDateTime(DialogWebCam_FileNameImageFormat,Now)+'_'+RandomHexStr(8)+'.JPG');
      if not DialogWebCam_Execute_GetFileName(lkFileName)then
        begin
        DeleteFile(lkFileName);
        exit;
        end;
      if(DataSource.DataSet.State = dsBrowse)then
        begin
        if(DataSource.DataSet.RecordCount = 0)then
          DataSource.DataSet.Append
         else 
          DataSource.DataSet.Edit;
        end;
      if DataSource.DataSet.FieldByName(DataField).IsBlob then  
        TBlobField(DataSource.DataSet.FieldByName(DataField)).LoadFromFile(lkFileName);
      DeleteFile(lkFileName);
      SetGlobalVariable(DialogWebCam_FileNameBufferVar, '');
      end;
  end;
  //============================================================================
  procedure actDBInterfaceImage_LoadTwain_OnExecute(Sender :TObject);
  var
    lkDlg    :TxsDialogTwain;
    lkScanner:string;
    lkJpgImg :TJPEGImage;
    lkStrm   :TMemoryStream;
    lkFlag   :Boolean;
  begin
    with TxcDBImage(TCustomAction(Sender).Owner) do
      begin
      if ReadOnly then 
        begin
        Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
           msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
        exit;
        end;
      lkDlg := TxsDialogTwain.Create(nil);
      if not lkDlg.LoadTwainModule then
        begin
        lkDlg.Free;
        Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
           msg_error_loadtwainmodule, mtWarning, [mbOk]);
        exit;
        end;
      lkFlag   := False;
      lkJpgImg := TJPEGImage.Create;  
      lkDlg.ShowHideUI := False;
      lkDlg.OpenSource;
      try
        lkDlg.OpenSourceManager;
        lkScanner := lkDlg.GetSource(false);
        WriteLn(lkScanner);
        lkDlg.SelectSource( lkScanner );
        lkDlg.OpenSource;
        lkFlag := (lkDlg.AcquireJPG(lkJpgImg, 50) = 0);
      finally
        lkDlg.CloseTwainSession;
        lkDlg.UnloadTwainModule;
        lkDlg.Free;
      end;
      if lkFlag then
        try
          lkStrm   := TMemoryStream.Create;
          lkJpgImg.SaveToStream(lkStrm);
          if(DataSource.DataSet.State = dsBrowse)then
            begin
            if(DataSource.DataSet.RecordCount = 0)then
              DataSource.DataSet.Append
             else 
              DataSource.DataSet.Edit;
            end;
          if DataSource.DataSet.FieldByName(DataField).IsBlob then 
            begin
            lkStrm.Seek(0, soFromBeginning);
            TBlobField(DataSource.DataSet.FieldByName(DataField)).LoadFromStream(lkStrm);
            end;
        finally
          lkJpgImg.Free;
          lkStrm.Free;
        end;    
      end;
  end;
  //============================================================================
  procedure actDBInterfaceImage_Save_OnExecute(Sender :TObject);
  var
    lkFileName :string;
  begin
    lkFileName := '';
    if PromptForFileName(lkFileName,msg_dbinterface_image_dialog_filter,'bmp',msg_dbinterface_actsave_hint,'', true)then
      with TxcDBImage(TCustomAction(Sender).Owner) do
        Picture.SaveToFile(lkFileName);
  end;
  //============================================================================
  procedure actDBInterfaceImage_Cut_OnExecute(Sender :TObject);
  begin
    if TxcDBImage(TCustomAction(Sender).Owner).ReadOnly then 
      begin
      Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
         msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
      exit;
      end;
    with TxcDBImage(TCustomAction(Sender).Owner) do  
      try 
        DataSource.DataSet.Edit;
        CutToClipboard;
      finally
      end;  
  end;
  //============================================================================
  procedure actDBInterfaceImage_Copy_OnExecute(Sender :TObject);
  begin
    TxcDBImage(TCustomAction(Sender).Owner).CopyToClipboard;
  end;
  //============================================================================
  procedure actDBInterfaceImage_CutCopy_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := not TxcDBImage(TCustomAction(Sender).Owner).Picture.Graphic.Empty;  
  end;
  //============================================================================
  procedure actDBInterfaceImage_Paste_OnExecute(Sender :TObject);
  begin
    if TxcDBImage(TCustomAction(Sender).Owner).ReadOnly then 
      begin
      Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
         msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
      exit;
      end;
    with TxcDBImage(TCustomAction(Sender).Owner) do  
      try 
        DataSource.DataSet.Edit;
        PasteFromClipboard;
      finally
      end;  
  end;
  //============================================================================
  procedure actDBInterfaceImage_Paste_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := not TxcDBImage(TCustomAction(Sender).Owner).ReadOnly;  
  end;
  //============================================================================
  procedure actDBInterfaceImage_Delete_OnExecute(Sender :TObject);
  begin
    if TxcDBImage(TCustomAction(Sender).Owner).ReadOnly then 
      begin
      Dialogs.MessageDlg(msg_error_blobimpossible+' "'+AnsiLowerCase(TCustomAction(Sender).Hint)+'".'+#13#10+
         msg_error_blobobjectisreadonly, mtWarning, [mbOk]);
      exit;
      end;
    with TxcDBImage(TCustomAction(Sender).Owner) do
      try
        DataSource.DataSet.Edit;
        DataSource.DataSet.FieldByName(DataField).Clear;
      finally
      end;
  end;
  //============================================================================
  procedure actDBInterfaceImage_Delete_OnUpdate(Sender :TObject);
  var
    lkEnabled:Boolean;
  begin
    with TxcDBImage(TCustomAction(Sender).Owner) do 
      begin
      lkEnabled := not ReadOnly;
      if lkEnabled then
        lkEnabled := not Picture.Graphic.Empty;
      TCustomAction(Sender).Enabled := lkEnabled;  
      end;
  end;
  //============================================================================
  procedure actDBInterfaceImage_AfterPictureLoaded(Sender :TObject);
  begin
    exit;
    with TxcDBImage(Sender) do
      if Picture.Graphic.Empty then
        begin
        Height := 1;
        Width  := 1;
        end
       else 
        begin
        Height := Picture.Height;
        Width  := Picture.Width;
        end;
  end;
  //============================================================================
  procedure DBInterfaceCreateImage(
             aOwner      :TComponent;   // Owner component
             aParent     :TWinControl;  // Parent Control for interface
             aDataSource :TDataSource;  // Data source for db-aware controls
             aDataField  :string;       // Data field for db-aware controls
             aReadOnly   :Boolean       // Read-only access to data field
           );
  var
    lkSB :TScrollBox;
    lkTB :TxcGradientPanelVista;
    lkAct:TCustomAction;
    lkImg:TxcDBImage;  
    lkLbl:TLabel;       
  begin
    DontAutoFree;
    lkTB := CreateTxcGradientPanelVistaToolBar(aOwner, aParent, '','',alTop,0,0,24,24,xbsRaized);
    lkSB := TScrollBox.Create(aOwner);
    with lkSB do
      begin
      Parent := aParent;
      Color  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Ctl3D  := false;
      Left   := 0;
      Top    := lkTB.Top+lkTB.Height+4;
      Height := 200;
      Width  := 200;
      Align  := alClient;
      end;
    lkImg:= TxcDBImage.Create(aOwner);
    with lkImg do
      begin
      Parent     := lkSB;
      Align      := alNone;
      Left       := 1;
      Top        := 1;
      Height     := 400;
      Width      := 600;
      DataSource := aDataSource;
      DataField  := aDataField;
      Stretch    := true;
      AfterPictureLoaded := @actDBInterfaceImage_AfterPictureLoaded;
      end; 
    lkAct := DBInterface_CreateTAction2(lkImg,lkTB,68,true ,'actDBIntf_Image_Load'  ,msg_dbinterface_actload  ,msg_dbinterface_actload_hint  ,'', 0, 30,@actDBInterfaceImage_Load_OnExecute      ,@actDBInterfaceImage_Paste_OnUpdate);
    lkAct := DBInterface_CreateTAction2(lkImg,lkTB,88,true ,'actDBIntf_Image_Load2' ,msg_dbinterface_actload2 ,msg_dbinterface_actload2_hint ,'', 0,488,@actDBInterfaceImage_LoadWebCam_OnExecute,@actDBInterfaceImage_Paste_OnUpdate);
    lkAct := DBInterface_CreateTAction2(lkImg,lkTB,60,true ,'actDBIntf_Image_Load3' ,msg_dbinterface_actload3 ,msg_dbinterface_actload3_hint ,'', 0, 61,@actDBInterfaceImage_LoadTwain_OnExecute ,@actDBInterfaceImage_Paste_OnUpdate);
    lkAct := DBInterface_CreateTAction2(lkImg,lkTB,76,true ,'actDBIntf_Image_Save'  ,msg_dbinterface_actsave  ,msg_dbinterface_actsave_hint  ,'', 0,107,@actDBInterfaceImage_Save_OnExecute      ,@actDBInterfaceImage_CutCopy_OnUpdate);
    lkLbl:=CreateTLabel(lkImg, lkTB, '|', lkTB.ControlCount * 80, 1, lkTB.Height, 8, alLeft, taCenter);
    lkAct := DBInterface_CreateTAction2(lkImg,lkTB,72,true ,'actDBIntf_Image_Cut'   ,msg_dbinterface_actcut   ,msg_dbinterface_actcut_hint   ,'', 0, 69,@actDBInterfaceImage_Cut_OnExecute       ,@actDBInterfaceImage_CutCopy_OnUpdate);
    lkAct := DBInterface_CreateTAction2(lkImg,lkTB,80,true ,'actDBIntf_Image_Copy'  ,msg_dbinterface_actcopy  ,msg_dbinterface_actcopy_hint  ,'', 0, 68,@actDBInterfaceImage_Copy_OnExecute      ,@actDBInterfaceImage_CutCopy_OnUpdate);
    lkAct := DBInterface_CreateTAction2(lkImg,lkTB,68,true ,'actDBIntf_Image_Paste' ,msg_dbinterface_actpaste ,msg_dbinterface_actpaste_hint ,'', 0, 73,@actDBInterfaceImage_Paste_OnExecute     ,@actDBInterfaceImage_Paste_OnUpdate);
    lkAct := DBInterface_CreateTAction2(lkImg,lkTB,64,true ,'actDBIntf_Image_Delete',msg_dbinterface_actdelete,msg_dbinterface_actdelete_hint,'', 0, 70,@actDBInterfaceImage_Delete_OnExecute    ,@actDBInterfaceImage_Delete_OnUpdate);
  end;
