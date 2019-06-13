{$DEFINE PEAKTOP:APPL/MANAGE/STDLIB/DEFAULT.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}    {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}         {$I PEAKTOP:OBJ/TACTION.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/$CUSTOM.INC} {$I ../$CUSTOM.INC}                {$ENDIF}
const
  msg_manageinterface_stdlib                   = 'StdLib';
  msg_manageinterface_stdlib_caption           = 'Стандартная библиотека';
const
  MANAGEINTERFACE_IMAGENAME_STDLIB             = 'PEAKTOP:IMG/CONFIG/LIBSTD0032X0032.BMP';
  MANAGEINTERFACE_ICONNAME_STDLIB              = 'PEAKTOP:IMG/CONFIG/LIBSTD0016X0016.ICO';
  MANAGEINTERFACE_STDLIB_NAME_TOPBAR           = 'ManageInterface_StdLib_TopBar';  
  MANAGEINTERFACE_STDLIB_NAME_TOOLBAR          = 'ManageInterface_StdLib_ToolBar';  
  //============================================================================
  procedure ManageInterface_StdLib_ShellListView_OnProcessFile(Sender: TObject; const FileName:TFileName; var Handled :Boolean);
  begin
    Handled := true;
    Amunhotep.MainForm.ProcessFile(FileName);
  end;
  //============================================================================
  function ManageInterface_StdLib_Create(aOwner:TComponent; aParent:TWinControl):TxcPanel;
  var
    lkSLV  :TShellListView;
    lkSTV  :TShellTreeView;
    lkSplt :TSplitter;
    lkPath :string;
  begin
    lkPath := Amunhotep.SourcePath;
    {$IFDEF LINUX}    lkPath := StrReplaceStr(lkPath,'\','/');{$ENDIF}
    {$IFDEF MSWINDOWS}lkPath := StrReplaceStr(lkPath,'/','\');{$ENDIF}
    Result := ManageInterface_Custom_Create(aOwner, aParent, MANAGEINTERFACE_STDLIB_NAME_TOPBAR, MANAGEINTERFACE_STDLIB_NAME_TOOLBAR, 
      msg_manageinterface_stdlib_caption, PrepareAbsoleteFileName(MANAGEINTERFACE_IMAGENAME_STDLIB) );
    lkSTV := TShellTreeView.Create(Result);
    with lkSTV do
      begin
      Name          := 'ShellTreeView';
      Parent        := Result;
      Align         := alLeft;
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Ctl3D         := false;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Left          := 0;
      Top           := 0;
      Width         := 140;
      HideSelection := false;
      ObjectTypes   := [otFolders, otHidden];
      Path          := Amunhotep.SourcePath;
      Root          := Amunhotep.SourcePath;
      ReadOnly      := true;
      end;
    lkSLV := TShellListView.Create(Result);
    with lkSLV do
      begin
      Name          := 'ShellListView';
      Parent        := Result;
      Left          := lkSTV.Left + lkSTV.Width;
      Top           := 0;
      Align         := alClient;
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Ctl3D         := false;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      HideSelection := false;
      ObjectTypes   := [otFolders, otNonFolders, otHidden];
      ShellTreeView := lkSTV;
      Sorted        := true;
      ViewStyle     := vsList;
      OnProcessFile := @ManageInterface_StdLib_ShellListView_OnProcessFile;
      end;
    lkSplt := TSplitter.Create(Result);
    with lkSplt do
      begin
      Name   := 'SplitterH';
      Parent := Result;
      Align  := alLeft;
      Color  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Left   := lkSTV.Left + lkSTV.Width + 1;
      Width  := 4;
      end;
    with lkSTV do
      begin
      ShellListView := lkSLV;  
      Path := lkPath;
      Root := lkPath;
      if(Items.Count > 0)then
        Items[0].Text := 'PEAKTOP:';
      end;
  end;
