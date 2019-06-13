{$DEFINE PEAKTOP:IDE/$COMMON/STDLIB_GIT.INC}
{$IFNDEF PEAKTOP:APPL/LOCAL/VARIABLE.INC}               {$I PEAKTOP:APPL/LOCAL/VARIABLE.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:APPL/LOCAL/FILE.INC}                   {$I PEAKTOP:APPL/LOCAL/FILE.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMEMO.INC}                         {$I PEAKTOP:OBJ/TMEMO.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                        {$I PEAKTOP:OBJ/TLABEL.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC}     {$I PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}            {$I PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/DLG_MEMO.INC}              {$I PEAKTOP:IDE/$COMMON/DLG_MEMO.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}             {$I PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}         {$ENDIF}
  //================== PEAKTOP:IDE/$COMMON/STDLIB_GIT.INC ======================
const
  obj_name_common_memo        = 'Memo';
  obj_name_act_updaterun      = 'actUpdateRun';
  obj_name_act_updatecommit   = 'actUpdateCommit';
  obj_name_act_updatepush     = 'actUpdatePush';
  STDLIBGIT_ICON              = 'PEAKTOP:IMG/CONFIG/UPDATE0016X0016.ICO';
  STDLIBGIT_BITMAP            = 'PEAKTOP:IMG/CONFIG/UPDATE0032X0032.BMP';
  STDLIBGIT_URL               = 'github.com/amunhotep/lib.git';
var
  TStdLibGit_Local :TStringList;  
  //============================================================================
  function TStdLibGit_RunCaptured(const aWorkingDir, aExeFileName, aExeFileParams:string):string;
  var
    i    :Integer;
    lkSL :TStrings;
  begin
    {$IFDEF MSWINDOWS}
    Result := RunCaptured(aWorkingDir, aExeFileName, aExeFileParams);  
    {$ENDIF}
    lkSL := TStringList.Create;
    lkSL.Text := Result;
    for i:=0 to lkSL.Count-1 do
      lkSL[i] := #$20#$20#$20#$20+lkSL[i];
    Result := lkSL.Text;
    lkSL.Free;  
  end;
  //============================================================================
  function  TStdLibGit_GetVersion:string;
  var
    lkSL :TStringList;
    lkStr:string;
    i    :Integer;
  begin
    Result := '';
    lkSL := TStringList.Create;
    try
      lkSL.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:VERSION.INC'));
      for i:=0 to lkSL.Count-1 do
        if( Pos('AmunhotepLibraryVersion', lkSL[i]) > 0 )then
          begin
          Result := lkSL[i];
          break;
          end;
      Delete(Result, 1, Pos('=', Result) );
      i := Length(Result);
      while(i > 0)do
        begin
        if(not(Pos(Result[i], '0123456789:.-') > 0))then 
          Delete(Result, i, 1);
        i := i -1;
        end;    
    finally  
      lkSL.Free;
    end;
  end;
  //============================================================================
  function TStdLibGit_CommitFileName:string;
  begin
    Result := StrAbsolutePath( '../conf/peaktop-git.conf', Amunhotep.ExeName );
    {$IFDEF MSWINDOWS}
    Result := StrReplaceStr( Result, '/', '\' );
    {$ENDIF}
  end;
  //============================================================================
  function TStdLibGit_GetCommitParams(var aGitUser, aGitEMail, aGitPassword:string):Boolean;
  begin
    Result := FileExists( TStdLibGit_CommitFileName );
    if not Result then exit;
    with TStringList.Create do
      try
        LoadFromFile( TStdLibGit_CommitFileName );
        aGitUser     := Values['git_user']; 
        aGitEMail    := Values['git_email']; 
        aGitPassword := Values['git_password'];
      finally
        Free;
      end;  
  end;
  //============================================================================
  function TStdLibGit_CanCommit:Boolean;
  begin
    Result := FileExists( TStdLibGit_CommitFileName );
  end;
  //============================================================================
  function TStdLibGit_GetGitPath(var aExePath:string):Boolean;
  begin
    Result := false;
    aExePath := StrAbsolutePath('../../git/bin/git.exe', Amunhotep.ExeName);
    {$IFDEF MSWINDOWS}
    aExePath := StrReplaceStr(aExePath, '/', '\');
    {$ENDIF}
    if not FileExists(aExePath)then
      begin
      Dialogs.MessageDlg( AmunhotepLocalString(TStdLibGit_Local, 'MSG_ERROR_GITNOTFOUND', 'Required Git client is not found.'), mtError, [mbOk]);
      exit;
      end;
    Result := true;  
  end;
  //============================================================================
  function TStdLibGit_GetUpdateURL(var aURL:string):Boolean;
  begin
    aURL   := 'https://'+STDLIBGIT_URL;
    Result := True;
  end;
  //============================================================================
  procedure TStdLibGit_actUpdateRun_OnExecute(Sender :TObject);
  var
    lkMemo     :TMemo;
    lkGit      :string;
    lkUpdateURL:string;
    lkPath     :string;
  begin
    lkMemo := TMemo(TComponent(Sender).Owner.FindComponent(obj_name_common_memo));
    if not TStdLibGit_GetGitPath(lkGit) then exit;
    if not TStdLibGit_GetUpdateURL(lkUpdateURL)then exit;
    ChDir(Amunhotep.SourcePath);
    lkPath := ' pull';
    lkMemo.Text := lkMemo.Text +
      FormatDateTime('dd.mm.yyyy hh:nn:ss',Now)+':>>'+lkGit+lkPath+#13#10+
      TStdLibGit_RunCaptured(ExtractFilePath(Amunhotep.SourcePath), lkGit, lkPath)+#13#10+#13#10;
    TCommonForm_SetCaption(TComponent(Sender).Owner, AmunhotepLocalString(TStdLibGit_Local, 'MSG_CAPTION', 'Обновления') + ' ['+TStdLibGit_GetVersion+']' );  
  end;
  //============================================================================
  procedure TStdLibGit_actUpdateCommit_OnExecute(Sender :TObject);
  var
    lkMemo        :TMemo;
    lkGit         :string;
    lkPath        :string;
    lkComment     :string;
    lkVerSrc      :string;
    lkGitUser     :string;
    lkGitEMail    :string; 
    lkGitPassword :string;
  begin
    if not TStdLibGit_GetCommitParams(lkGitUser, lkGitEMail, lkGitPassword) then
      begin
      Dialogs.MessageDlg( AmunhotepLocalString(TStdLibGit_Local, 'MSG_ERROR_GITPARAMSNOTFOUND', 'Git commit settings is not found.'), mtError, [mbOk]);
      exit;
      end;
    lkComment := '';
    if not TDlgMemo_Execute(AmunhotepLocalString(TStdLibGit_Local, 'MSG_ACTCOMMIT_HINT', 'Commit Changes of Source Code'), 
      AmunhotepLocalString(TStdLibGit_Local, 'MSG_ACTCOMMIT_PROMPT', 'Please, Add a Comment'), STDLIBGIT_ICON, STDLIBGIT_BITMAP, lkComment)then exit;
    lkVerSrc := 
      '//=============================================================================='+#13#10+
      '// This file content is generated automatically.'+#13#10+ 
      '// Please, DO NOT to edit this file!'+#13#10+
      '//=============================================================================='+#13#10+
      '{$DEFINE PEAKTOP:VERSION.INC}'+#13#10+
      'const AmunhotepLibraryVersion = '''+FormatDateTime('yyyy.mm.dd-hhnnss', Now)+''';'+#13#10;    
    StringsSaveToFile('PEAKTOP:VERSION.INC', lkVerSrc);
    lkMemo := TMemo(TComponent(Sender).Owner.FindComponent(obj_name_common_memo));
    if not TStdLibGit_GetGitPath(lkGit) then exit;
    ChDir(Amunhotep.SourcePath);
    lkPath := ' add --all ';
    lkMemo.Text := lkMemo.Text +
      FormatDateTime('dd.mm.yyyy hh:nn:ss',Now)+':>>'+lkGit+lkPath+#13#10+
      TStdLibGit_RunCaptured(ExtractFilePath(Amunhotep.SourcePath), lkGit, lkPath)+#13#10+#13#10;
    lkPath := ' commit --author="'+lkGitUser+' <'+lkGitEMail+'>" --all ';
    if(StrTrimAll(lkComment) <> '')then
      lkPath := lkPath +' -m "'+StrReplaceStr(lkComment, '"', '`')+'"';
    lkMemo.Text := lkMemo.Text +
      FormatDateTime('dd.mm.yyyy hh:nn:ss',Now)+':>>'+lkGit+lkPath+#13#10+
      TStdLibGit_RunCaptured(ExtractFilePath(Amunhotep.SourcePath), lkGit, lkPath)+#13#10+#13#10;
    TCommonForm_SetCaption(TComponent(Sender).Owner, AmunhotepLocalString(TStdLibGit_Local, 'MSG_CAPTION', 'Обновления') + ' ['+TStdLibGit_GetVersion+']' );  
  end;
  //============================================================================
  procedure TStdLibGit_actUpdatePush_OnExecute(Sender :TObject);
  var
    lkMemo        :TMemo;
    lkGit         :string;
    lkPath        :string;
    lkGitUser     :string;
    lkGitEMail    :string; 
    lkGitPassword :string;
  begin
    if not TStdLibGit_GetCommitParams(lkGitUser, lkGitEMail, lkGitPassword) then
      begin
      Dialogs.MessageDlg( AmunhotepLocalString(TStdLibGit_Local, 'MSG_ERROR_GITPARAMSNOTFOUND', 'Git commit settings is not found.'), mtError, [mbOk]);
      exit;
      end;
    lkMemo := TMemo(TComponent(Sender).Owner.FindComponent(obj_name_common_memo));
    if not TStdLibGit_GetGitPath(lkGit) then exit;
    ChDir(Amunhotep.SourcePath);
    lkPath := ' push --all "https://'+lkGitUser+':'+lkGitPassword+'@'+STDLIBGIT_URL+'" ';
    lkMemo.Text := lkMemo.Text +
      FormatDateTime('dd.mm.yyyy hh:nn:ss',Now)+':>>'+lkGit+lkPath+#13#10+
      TStdLibGit_RunCaptured(ExtractFilePath(Amunhotep.SourcePath), lkGit, lkPath)+#13#10+#13#10;
    TCommonForm_SetCaption(TComponent(Sender).Owner, AmunhotepLocalString(TStdLibGit_Local, 'MSG_CAPTION', 'Обновления') + ' ['+TStdLibGit_GetVersion+']' );  
  end;
  //============================================================================
  procedure TStdLibGit_OnClose(Sender :TObject; var Action :TcloseAction);
  begin
    Action := caFree;
    if(TStdLibGit_Local <> nil)then
      TStdLibGit_Local.Free;
  end;
  //============================================================================
  function TStdLibGit_Create(const aModalForm:Boolean):TForm;
  var
    lkCaption:string;
    lkMemo   :TMemo;
    lkToolBar:TxcGradientPanelVista;
    lkAct    :TCustomAction;
  begin
    if(TStdLibGit_Local = nil)then
      begin
      TStdLibGit_Local            := TStringList.Create;  
      TStdLibGit_Local.Duplicates := dupIgnore;
      TStdLibGit_Local.Sorted     := True;
      end;
    AmunhotepLocalStringsLoad(TStdLibGit_Local, AmunhotepLocalGet, 'PEAKTOP:IDE/$COMMON/STDLIB_GIT.JSON' );  
    lkCaption := AmunhotepLocalString(TStdLibGit_Local, 'MSG_CAPTION', 'Обновления') + ' ['+TStdLibGit_GetVersion+']';
    Result    := TCommonForm_Create(lkCaption, lkCaption, STDLIBGIT_ICON, STDLIBGIT_BITMAP, aModalForm, @TCommonForm_OnClose);
    TCommonForm_SetTopBarColor( Result, $BFFF80 );
    lkToolBar := CreateTxcGradientPanelVistaToolBar(Result, Result, 'ToolBar', '', alTop, 0,200,24,600, xbsRaized);  
    lkMemo := CreateTMemo(Result, Result, obj_name_common_memo, 0, 200, 200, 200, alClient);
    with lkMemo do
      begin
      Color     := Amunhotep.MainForm.StyleManager.Colors.Border;
      Text      := '';
      Font.Size := 8;
      Font.Name := 'Fixedsys';
      Font.Style:= [];
      Font.Color:= TxcGradientPanelVista(Result.FindComponent(obj_name_common_topbar)).Colors.HotTrackBorder;
      ScrollBars:= ssBoth;
      WordWrap  := true;
      ReadOnly  := True;
      end; 
    lkAct := TCommonForm_CreateAction2(Result,obj_name_act_updaterun, AmunhotepLocalString(TStdLibGit_Local, 'MSG_ACTUPDATE_CAPTION', 'Обновить'),
      AmunhotepLocalString(TStdLibGit_Local, 'MSG_ACTUPDATE_HINT', 'Обновить библиотеку кода из репозитария'),SHORTCUT_DATA_REFRESH,0,192,@TStdLibGit_actUpdateRun_OnExecute,nil,lkToolBar,96,nil);
    if TStdLibGit_CanCommit then
      begin
      lkAct := TCommonForm_CreateAction2(Result,obj_name_act_updatecommit, AmunhotepLocalString(TStdLibGit_Local, 'MSG_ACTCOMMIT_CAPTION', 'Commit'),
          AmunhotepLocalString(TStdLibGit_Local, 'MSG_ACTCOMMIT_HINT', 'Commit Changes of Source Code'),SHORTCUT_DOC_COMMIT,0,547,@TStdLibGit_actUpdateCommit_OnExecute,nil,lkToolBar, 96,nil);
      lkAct := TCommonForm_CreateAction2(Result,obj_name_act_updatepush  ,AmunhotepLocalString(TStdLibGit_Local, 'MSG_ACTPUSH_CAPTION', 'Push'),
          AmunhotepLocalString(TStdLibGit_Local, 'MSG_ACTPUSH_HINT', 'Push Source Code into Repository'),SHORTCUT_DATA_POST,0,436,@TStdLibGit_actUpdatePush_OnExecute  ,nil,lkToolBar, 96,nil);
      end;
  end;
