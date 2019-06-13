{$DEFINE PEAKTOP:APPL/MANAGE/DEFAULT.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                       {$I PEAKTOP:OBJ/TACTION.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/$CUSTOM.INC}               {$I ./$CUSTOM.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/START/AUTO/DEFAULT.INC}    {$I ./START/AUTO/DEFAULT.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/START/PARAMS/DEFAULT.INC}  {$I ./START/PARAMS/DEFAULT.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/STDLIB/DEFAULT.INC}        {$I ./STDLIB/DEFAULT.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/DB/ATTACHMENTS/DEFAULT.INC}{$I ./DB/ATTACHMENTS/DEFAULT.INC}{$ENDIF}
const
  msg_manageinterface_caption               = 'AMUNHOTEP:Управление параметрами';
  msg_manageinterface_category_appl_caption = 'AMUNHOTEP';
  msg_manageinterface_category_db_caption   = 'База данных';
const
  MANAGEINTERFACE_NAME_PAGECONTROL = 'ManageInterface_PageControlMain';  
  MANAGEINTERFACE_NAME_TOPBAR      = 'ManageInterface_TopBarMain';  
  MANAGEINTERFACE_NAME_TOOLBAR     = 'ManageInterface_ToolBarMain';
  MANAGEINTERFACE_TOOLBUTTONHEIGHT = 34;  
  //============================================================================
  procedure ManageInterface_actAppl_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := true;
  end;
  //============================================================================
  procedure ManageInterface_actApplStartAuto_OnExecute(Sender :TObject);
  var
    lkPC  :TxcPageControl;
    lkTS  :TTabSheet;
    lkPnl :TxcPanel;
  begin
    {$IFDEF PEAKTOP:APPL/MANAGE/START/AUTO/DEFAULT.INC}
    lkPC := TxcPageControl(TComponent(Sender).Owner.FindComponent(MANAGEINTERFACE_NAME_PAGECONTROL));
    if(lkPC <> nil)then
      begin
      lkTS := TTabSheet.Create(lkPC);
      with lkTS do
        begin
        Caption     := msg_manageinterface_startauto;
        PageControl := lkPC;
        end;
      lkPnl := ManageInterface_StartAuto_Create(lkTS, lkTS);
      end;
    {$ENDIF}
  end;
  //============================================================================
  procedure ManageInterface_actApplStartParams_OnExecute(Sender :TObject);
  var
    lkPC  :TxcPageControl;
    lkTS  :TTabSheet;
    lkPnl :TxcPanel;
  begin
    {$IFDEF PEAKTOP:APPL/MANAGE/START/PARAMS/DEFAULT.INC}
    lkPC := TxcPageControl(TComponent(Sender).Owner.FindComponent(MANAGEINTERFACE_NAME_PAGECONTROL));
    if(lkPC <> nil)then
      begin
      lkTS := TTabSheet.Create(lkPC);
      with lkTS do
        begin
        Caption     := msg_manageinterface_startparams;
        PageControl := lkPC;
        end;
      lkPnl := ManageInterface_StartParams_Create(lkTS, lkTS);
      end;
    {$ENDIF}
  end;
  //============================================================================
  procedure ManageInterface_actApplStdLib_OnExecute(Sender :TObject);
  var
    lkPC  :TxcPageControl;
    lkTS  :TTabSheet;
    lkPnl :TxcPanel;
  begin
    {$IFDEF PEAKTOP:APPL/MANAGE/STDLIB/DEFAULT.INC}
    lkPC := TxcPageControl(TComponent(Sender).Owner.FindComponent(MANAGEINTERFACE_NAME_PAGECONTROL));
    if(lkPC <> nil)then
      begin
      lkTS := TTabSheet.Create(lkPC);
      with lkTS do
        begin
        Caption     := msg_manageinterface_stdlib;
        PageControl := lkPC;
        end;
      lkPnl := ManageInterface_StdLib_Create(lkTS, lkTS);
      end;
    {$ENDIF}
  end;
  //============================================================================
  procedure ManageInterface_actApplStdLib_OnUpdate(Sender :TObject);
  begin
    {$IFDEF PEAKTOP:APPL/MANAGE/STDLIB/DEFAULT.INC}
    TCustomAction(Sender).Enabled := (Amunhotep.MainForm.FormStyle = fsMDIForm);
    {$ENDIF}
  end;
  //============================================================================
  procedure ManageInterface_actDB_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := FBDataBase.Connected;
  end;
  //============================================================================
  procedure ManageInterface_actDBAttach_OnExecute(Sender :TObject);
  var
    lkPC  :TxcPageControl;
    lkTS  :TTabSheet;
    lkPnl :TxcPanel;
  begin
    {$IFDEF PEAKTOP:APPL/MANAGE/DB/ATTACHMENTS/DEFAULT.INC}
    lkPC := TxcPageControl(TComponent(Sender).Owner.FindComponent(MANAGEINTERFACE_NAME_PAGECONTROL));
    if(lkPC <> nil)then
      begin
      lkTS := TTabSheet.Create(lkPC);
      with lkTS do
        begin
        Caption     := msg_manageinterface_dbattach;
        PageControl := lkPC;
        end;
      lkPnl := ManageInterface_DBAttachments_Create(lkTS, lkTS);
      end;
    {$ENDIF}
  end;
  //============================================================================
  function ManageInterface_CreateAction(aOwner :TComponent; const aName, aCaption, aHint, aShortCut:string;
             const aImageIndex, aGroupIndex :Integer; aProcOnExecute, aProcOnUpdate:TNotifyEvent;
             aGroupPanel:TxcGroupPanel; const aImageFileName, aDefaultImageFileName:string):TCustomAction;
  var
    lkFileName :string;
    lkStrm     :TMemoryStream;
  begin
    Result := CreateTAction(aOwner, aName, aCaption, aHint, aShortCut, aImageIndex, aGroupIndex);
    with Result do
      begin
      OnExecute := aProcOnExecute;
      OnUpdate  := aProcOnUpdate;
      end;
    with TxcToolBarButton.Create(Result) do
      begin
      Name         := 'tbb'+Result.Name;
      Parent       := aGroupPanel;
      Left         := 0;
      Top          := ( (aGroupPanel.ControlCount+1) * MANAGEINTERFACE_TOOLBUTTONHEIGHT);
      Height       := MANAGEINTERFACE_TOOLBUTTONHEIGHT;
      Align        := alTop;
      StyleManager := Amunhotep.MainForm.StyleManager;
      ShowHint     := true;
      ShowCaption  := true;
      Action       := Result;
      lkFileName := aImageFileName;  
      if(Pos('PEAKTOP:', UpperCase(lkFileName)) = 1)then
        lkFileName := StrReplaceStr(lkFileName, 'PEAKTOP:', Amunhotep.SourcePath);
      lkFileName := StrReplaceStr(lkFileName,{$IFDEF MSWINDOWS}'/'{$ENDIF}{$IFDEF LINUX}'\'{$ENDIF},{$IFDEF MSWINDOWS}'\'{$ENDIF}{$IFDEF LINUX}'/'{$ENDIF});
      if not FileExists(lkFileName)then
        begin
        lkFileName := aDefaultImageFileName;  
        if(Pos('PEAKTOP:', UpperCase(lkFileName)) = 1)then
          lkFileName := StrReplaceStr(lkFileName, 'PEAKTOP:', Amunhotep.SourcePath);
        lkFileName := StrReplaceStr(lkFileName,{$IFDEF MSWINDOWS}'/'{$ENDIF}{$IFDEF LINUX}'\'{$ENDIF},{$IFDEF MSWINDOWS}'\'{$ENDIF}{$IFDEF LINUX}'/'{$ENDIF});
        end; 
      if FileExists(lkFileName)then   
        try
          lkStrm  := TMemoryStream.Create;
          if StreamLoadFromFile(lkFileName, lkStrm)then
            Glyph.LoadFromStream(lkStrm);
        finally    
          lkStrm.Free;
        end;
      end;  
  end;
  //============================================================================
  function ManageInterface_Create(aOwner:TComponent; aParent:TWinControl):TxcPanel;
  var
    lkAct    :TCustomAction;
    lkGBar   :TxcGroupBar;
    lkGPnlApp:TxcGroupPanel;
    lkGPnlDB :TxcGroupPanel;
    lkSplt   :TSplitter;
    lkPC     :TxcPageControl;
  begin
    DontAutoFree;
    Result := ManageInterface_Custom_Create(aOwner, aParent, 
      MANAGEINTERFACE_NAME_TOPBAR, MANAGEINTERFACE_NAME_TOOLBAR, msg_manageinterface_caption,
      StrReplaceStr(MANAGEINTERFACE_IMAGENAME, 'PEAKTOP:', Amunhotep.SourcePath));
    lkGBar  := TxcGroupBar.Create(Result);
    with lkGBar do
      begin
      Name           := 'CategoryButtons';
      Parent         := Result;
      Align          := alLeft;
      Width          := 120;
      Font.Name      := 'Verdana';
      Font.Size      := 7;
      Font.Style     := [fsBold];
      Margin         := 4;
      ItemHeight     := 24;
      GradientDirect := gdLeftToRight;
      StyleManager   := Amunhotep.MainForm.StyleManager;
      lkGPnlApp      := AddGroupPanel(msg_manageinterface_category_appl_caption);
      lkGPnlDB       := AddGroupPanel(msg_manageinterface_category_db_caption);
      end;
    lkSplt := TSplitter.Create(Result);
    with lkSplt do
      begin
      Parent := Result;
      Align  := alLeft;
      Width  := 4;
      Left   := lkGBar.Left + lkGBar.Width + Width;
      Color  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      end;
    lkPC := TxcPageControl.Create(Result);
    with lkPC do
      begin
      Name         := MANAGEINTERFACE_NAME_PAGECONTROL;
      Parent       := Result;
      Left         := lkSplt.Left + lkSplt.Width;
      Top          := 0;
      Align        := alClient;
      StyleManager := Amunhotep.MainForm.StyleManager;
      end;
    {$IFDEF PEAKTOP:APPL/MANAGE/START/AUTO/DEFAULT.INC}
    lkAct := ManageInterface_CreateAction(Result,'actApplStartAuto',msg_manageinterface_startauto,msg_manageinterface_startauto_caption,'Ctrl+0',0,26, 
      @ManageInterface_actApplStartAuto_OnExecute,@ManageInterface_actAppl_OnUpdate,lkGPnlApp,MANAGEINTERFACE_IMAGENAME_STARTAUTO,MANAGEINTERFACE_IMAGENAME);
    {$ENDIF}
    {$IFDEF PEAKTOP:APPL/MANAGE/START/PARAMS/DEFAULT.INC}
    lkAct := ManageInterface_CreateAction(Result, 'actApplStartParams', msg_manageinterface_startparams, msg_manageinterface_startparams_caption, 'Ctrl+1', 0, 26,
      @ManageInterface_actApplStartParams_OnExecute, @ManageInterface_actAppl_OnUpdate,lkGPnlApp,MANAGEINTERFACE_IMAGENAME_STARTPARAMS,MANAGEINTERFACE_IMAGENAME);
    {$ENDIF}
    {$IFDEF PEAKTOP:APPL/MANAGE/STDLIB/DEFAULT.INC}
    lkAct := ManageInterface_CreateAction(Result, 'actApplStdLib', msg_manageinterface_stdlib, msg_manageinterface_stdlib_caption, 'Ctrl+2', 0, 165,
      @ManageInterface_actApplStdLib_OnExecute, @ManageInterface_actApplStdLib_OnUpdate,lkGPnlApp,MANAGEINTERFACE_IMAGENAME_STDLIB,MANAGEINTERFACE_IMAGENAME);
    {$ENDIF}
    {$IFDEF PEAKTOP:APPL/MANAGE/DB/ATTACHMENTS/DEFAULT.INC}
    lkAct := ManageInterface_CreateAction(Result, 'actDBAttach', msg_manageinterface_dbattach, msg_manageinterface_dbattach_caption, 'Ctrl+3', 0, 242, 
      @ManageInterface_actDBAttach_OnExecute, @ManageInterface_actDB_OnUpdate,lkGPnlDB,MANAGEINTERFACE_IMAGENAME_DBATTACH,MANAGEINTERFACE_IMAGENAME);
    {$ENDIF}
    lkGPnlApp.HeightExpanded := lkGBar.ItemHeight + lkGBar.Margin + (lkGPnlApp.ControlCount * MANAGEINTERFACE_TOOLBUTTONHEIGHT);
    lkGPnlDB.HeightExpanded  := lkGBar.ItemHeight + lkGBar.Margin + (lkGPnlDB.ControlCount  * MANAGEINTERFACE_TOOLBUTTONHEIGHT);
  end;
