{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SELECT.INC}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/CUSTOM.INC}                  {$I ./CUSTOM.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/LANG.INC}                    {$I ./LANG.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SELECT_ACTIONS.INC} {$I ./DATABASE_SELECT_ACTIONS.INC} {$ENDIF}
  //================ PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SELECT.INC ==========
  procedure FirebirdDialog_CategoryButtons_OnDblClick(Sender :TObject);
  begin
    with TCategoryButtons(Sender) do
      if(SelectedItem <> nil)then
        if(ObjectInheritsFrom(SelectedItem, 'TButtonItem'))then
          TForm(Owner).ModalResult := mrOk;
  end;
  //============================================================================
  function FirebirdDialog_DatabaseSelect_Execute(var DataBasePath, DataBaseCodePage, FirebirdUserName, FirebirdUserRole, FirebirdUserPwd:string):Boolean;
  var
    lkForm        :TForm;
    lkPanelClient :TxcGradientPanel;
    lkPanelToolBar:TxcGradientPanel;
    lkImg         :TImage;
    lkCBTNS       :TCategoryButtons;
    lkBmp         :TBitmap;
    FBFileConfig  :TxFBFileConfig;
    lkStrm        :TMemoryStream;
    i, j          :Integer;
  begin
    Result := false;
    lkForm        := FirebirdDialog_Create(msg_firebird_dialog_database_select_caption, msg_firebird_dialog_button_caption_select, msg_firebird_dialog_button_caption_cancel);
//    lkForm.Width  := lkForm.Width + 96;  
    lkPanelClient := TxcGradientPanel(lkForm.FindComponent('PanelClient'));
    lkImg         := TImage(lkForm.FindComponent('ImageLogo'));
    lkCBTNS := TCategoryButtons.Create(lkForm);
    with lkCBTNS do
      begin
      Name                        := 'CategoryButtons';
      Parent                      := lkPanelClient;
      Align                       := alClient;
      BackgroundGradientColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
      BackgroundGradientDirection := gdRightToLeft; 
      ButtonFlow                  := cbfVertical;
      ButtonHeight                := 20;
      ButtonOptions               := [boGradientFill,boFullSize,boShowCaptions,boBoldCaptions,boUsePlusMinus,boCaptionOnlyBorder];
      ButtonWidth                 := 128;
      Color                       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Name                   := 'Verdana';
      Font.Size                   := 7;//DefaultFirebirdDialogLabelFontHeight;
      Font.Style                  := [fsBold];
      GradientDirection           := gdTopToBottom;
      HotButtonColor              := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      RegularButtonColor          := clNone;
      SelectedButtonColor         := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      ShowHint                    := true;
      Images                      := TImageList.Create(lkCBTNS);
      Images.Height               := 16;
      Images.Width                := 16;
      try
        lkBmp        := TBitmap.Create;
        lkBmp.Height := Images.Height;
        lkBmp.Width  := Images.Width;
        try
          lkStrm  := TMemoryStream.Create;
          if StreamLoadFromFile(StrAbsolutePath('./IMG/FIREBIRD/LOGO_005.BMP', Amunhotep.SourcePath),lkStrm)then
            lkBmp.LoadFromStream(lkStrm);
        finally    
          lkStrm.Free;
        end;
        Images.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
      finally
        lkBmp.Free;
      end; 
      //OnClick := @FirebirdDialog_CategoryButtons_OnDblClick; 
      end;
    try
      FBFileConfig := LoadEncryptTxFBFileConfig(StrAbsolutePath('../conf/fb.conf', Amunhotep.ExeName));
    except
    end;  
    if(FBFileConfig = nil)then
      FBFileConfig := TxFBFileConfig.Create(nil);
    FBFileConfig.Name := 'FBFileConfig';
    lkForm.InsertComponent(FBFileConfig);  
    FirebirdDialog_DatabaseSelect_FillCategories(FBFileConfig, lkCBTNS);
    lkPanelToolBar := TxcGradientPanel.Create(lkForm);
    with lkPanelToolBar do
      begin
      Name           := 'PanelToolBar';
      Parent         := lkForm;
      Top            := 0;
      Height         := 200;
      Width          := 80;
      Align          := alRight;
      BorderStyle    := xbsNone;
      StyleManager   := Amunhotep.MainForm.StyleManager;
      Caption        := '';
      ShowCaption    := false;
      GradientDirect := gdRightToLeft;
      Font.Size      := 7;
      Font.Style     := [fsBold];  
      end;
    FirebirdDialog_DataBaseSelect_CreateToolButtons(lkForm, lkPanelToolBar, Amunhotep.MainForm.ImageListMain, [380, 381, 383, 199, 202, 200]);
    lkForm.ActiveControl := lkCBTNS;   
    if(lkForm.ShowModal = mrOk)then
      begin
      if(lkCBTNS.SelectedItem <> nil)then
        if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonItem'))then
          begin
          Result := true;
          with TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data) do
            begin
            DataBasePath     := FullNameIP;
            DataBaseCodePage := CodePage;
            FirebirdUserName := UserName;
            FirebirdUserRole := UserRole;
            FirebirdUserPwd  := UserPassword;
            end;
          if TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).LoginServer then
            begin
            for i:=0 to FBFileConfig.Servers.Count-1 do
              for j:=0 to FBFileConfig.Servers[i].DataBases.Count-1 do
                if(FBFileConfig.Servers[i].DataBases[j] = TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data))then
                  begin
                  FirebirdUserName := FBFileConfig.Servers[i].UserName;
                  FirebirdUserRole := FBFileConfig.Servers[i].UserRole;
                  FirebirdUserPwd  := FBFileConfig.Servers[i].UserPassword;
                  break;
                  end;
            end;    
          end; 
      end;
    lkForm.RemoveComponent(FBFileConfig);  
    lkForm.Free;
    FBFileConfig.Free;
  end;
