{$DEFINE PEAKTOP:APPL/MANAGE/$CUSTOM.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}    {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}         {$I PEAKTOP:OBJ/TACTION.INC}       {$ENDIF}
const
  msg_manageinterface_act_close_caption = 'Закрыть';
  msg_manageinterface_act_close_hint    = 'Закрыть текущую страницу';
const
  MANAGEINTERFACE_IMAGENAME             = 'PEAKTOP:APPL/MANAGE/DEFAULT_BITMAP.BMP';
  MANAGEINTERFACE_IMAGENAME_ACTCLOSE    = 'PEAKTOP:IMG/ICONS/DIALOGS_CLOSE_0032X0032.BMP';
  MANAGEINTERFACE_IMAGENAME_ACTHELP     = 'PEAKTOP:IMG/ICONS/DIALOGS_CONFIRMATION_0032X0032.BMP';
  MANAGEINTERFACE_TOOLBARBUTTON_WIDTH   = 96;
  //============================================================================
  procedure ManageInterface_Custom_actClose_OnExecute(Sender :TObject);
  begin
    if(TComponent(Sender).Owner <> nil)then
      begin
      if(TComponent(Sender).Owner.Owner <> nil)then
        TComponent(Sender).Owner.Owner.Free
       else 
        TComponent(Sender).Owner.Free;
      end;
  end;
  //============================================================================
  function ManageInterface_Custom_Create(aOwner:TComponent; aParent:TWinControl;
           const aTopBarName, aToolBarName, aTopBarCaption, aTopBarImageFileName:string):TxcPanel;
  var
    lkTopBar :TxcGradientPanelVista;
    lkStrm   :TMemoryStream;
    lkToolBar:TxcGradientPanel;
    lkAct    :TCustomAction;
    lkFileName:string;
  begin
    DontAutoFree;
    Result := TxcPanel.Create(aOwner);
    with Result do
      begin
      Parent      := aParent;
      BorderStyle := xbsNone;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [];
      Font.Color  := Amunhotep.MainForm.StyleManager.Colors.Border; 
      StyleManager:= Amunhotep.MainForm.StyleManager;
      Align       := alClient;
      end;
    lkTopBar := TxcGradientPanelVista.Create(Result);
    with lkTopBar do
      begin
      Name        := aTopBarName;
      Parent      := Result;
      Left        := 0;
      Top         := 0;
      Height      := 34;
      Align       := alTop;
      BorderStyle := xbsRaized;
      Caption     := #$20+aTopBarCaption;
      Font.Name   := 'Verdana';
      Font.Size   := 14;
      Font.Style  := [fsBold];
      Font.Color  := Amunhotep.MainForm.StyleManager.Colors.Window; 
      StyleManager:= Amunhotep.MainForm.StyleManager;
      end;
    lkFileName := aTopBarImageFileName;  
    if(not FileExists(lkFileName))then
      lkFileName := PrepareAbsoleteFileName(MANAGEINTERFACE_IMAGENAME);
    if FileExists(lkFileName)then
      with TImage.Create(lkTopBar) do
        begin
        Parent       := lkTopBar;
        Left         := 0;
        Top          := 0;
        Width        := lkTopBar.Height;
        Height       := lkTopBar.Height;
        Align        := alLeft;
        Transparent  := true;
        Center       := true;
        Proportional := true;
        try
          lkStrm  := TMemoryStream.Create;
          if StreamLoadFromFile(lkFileName, lkStrm)then
            Picture.Bitmap.LoadFromStream(lkStrm);
        finally    
          lkStrm.Free;
          lkTopBar.Caption := #$20#$20#$20#$20 + lkTopBar.Caption;
        end;
        end;  
    lkToolBar := TxcGradientPanel.Create(Result);
    with lkToolBar do
      begin
      Name           := aToolBarName;
      Parent         := Result;
      Left           := 0;
      Top            := lkTopBar.Top + lkTopBar.Height + 1;
      Height         := 20;
      Align          := alTop;
      BorderStyle    := xbsRaized;
      Caption        := '';
      ShowCaption    := false;
      StyleManager   := Amunhotep.MainForm.StyleManager;
      GradientDirect := gdBottomToTop;
      Visible        := false;
      end;
    lkAct := CreateTAction(Result,aTopBarName+'_actClose',msg_manageinterface_act_close_caption,msg_manageinterface_act_close_hint,'Ctrl+Shift+F4',0,184); 
    lkAct.OnExecute := @ManageInterface_Custom_actClose_OnExecute;   
    with TxcToolBarButton.Create(Result) do
      begin
      Name         := 'tbb'+lkAct.Name;
      Parent       := lkTopBar;
      Left         := lkTopBar.Width;
      Width        := lkTopBar.Height + 2;
      Align        := alRight;
      Font.Name    := 'Verdana';
      Font.Size    := 7;
      Font.Style   := [fsBold];
      Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Window; 
      StyleManager := Amunhotep.MainForm.StyleManager;
      ShowHint     := true;
      ShowCaption  := false;
      Action       := lkAct;  
      if FileExists(StrReplaceStr(MANAGEINTERFACE_IMAGENAME_ACTCLOSE, 'PEAKTOP:', Amunhotep.SourcePath))then  
        try
          lkStrm  := TMemoryStream.Create;
          if StreamLoadFromFile(StrReplaceStr(MANAGEINTERFACE_IMAGENAME_ACTCLOSE, 'PEAKTOP:', Amunhotep.SourcePath),lkStrm)then
            Glyph.LoadFromStream(lkStrm);
        finally    
          lkStrm.Free;
        end;
      end;
  end;
