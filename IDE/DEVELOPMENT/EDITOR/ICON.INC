{$DEFINE PEAKTOP:IDE/DEVELOPMENT/EDITOR/ICON.INC}
{$IFNDEF PEAKTOP:SYSUTILS/FORM_ICON.INC}{$I PEAKTOP:SYSUTILS/FORM_ICON.INC} {$ENDIF}
  //==================== PEAKTOP:APPL/TOOLS_API/CORE_EDITORICON.INC ============
  function GetEditorIconFileName(const aFileName:string; const aFileType:TFileType):string;
  begin
    Result := 'txt'; 
    case aFileType of
      ftText   :Result := 'txt';
      ftPas    :begin
                     if(LowerCase(ExtractFileExt(aFileName))='.pas')then Result := 'pas'
                else if(LowerCase(ExtractFileExt(aFileName))='.inc')then Result := 'inc'
                else                                                     Result := 'ps';
                end;
      ftDfm    :begin
                     if(LowerCase(ExtractFileExt(aFileName))='.dfm')then Result := 'dfm'
                else if(LowerCase(ExtractFileExt(aFileName))='.lfm')then Result := 'lfm'
                else if(LowerCase(ExtractFileExt(aFileName))='.nfm')then Result := 'nfm'
                else                                                     Result := 'xfm';
                end;
      ftSQL    :Result := 'sql';
      ftJava   :Result := 'java';
      ftJS     :Result := 'js';
      ftPerl   :begin
                     if(LowerCase(ExtractFileExt(aFileName))='.conf')then Result := 'conf'
                else if(LowerCase(ExtractFileExt(aFileName))='.cfg' )then Result := 'cfg'
                else                                                      Result := 'pl';
                end;
      ftBat    :Result := 'editor';
      ftHTML   :Result := 'html';
      ftCss    :Result := 'css';
      ftXML    :Result := 'xml';
      ftVB     :Result := 'editor';
      ftPython :Result := 'py';
      ftC      :begin
                     if(LowerCase(ExtractFileExt(aFileName))='.cpp')then Result := 'cpp'
                else if(LowerCase(ExtractFileExt(aFileName))='.cs' )then Result := 'cs'
                else if(LowerCase(ExtractFileExt(aFileName))='.h'  )then Result := 'h'
                else if(LowerCase(ExtractFileExt(aFileName))='.hpp')then Result := 'hpp'
                else                                                     Result := 'c';
                end;
      ftPHP    :Result := 'php';
      ftAsm    :Result := 'asm';
      ftRC     :Result := 'rc';
      ftRuby   :Result := 'rb';
      ftInno   :Result := 'iss';
      else      Result := 'txt';
      end;
    Result := StrAbsolutePath('../conf/icons/'+Result+'.ico', Amunhotep.ExeName);
    {$IFDEF MSWINDOWS}Result := StrReplaceChar(Result, '/', '\');{$ENDIF}  
    {$IFDEF LINUX}    Result := StrReplaceChar(Result, '\', '/');{$ENDIF}  
  end;
  //============================================================================
  procedure SetEditorIcon(aOwnerForm :TAmunhotepEditorForm);
  var
    lkFile :string;
  begin
    lkFile := GetEditorIconFileName(aOwnerForm.FileName, aOwnerForm.FileType);
    if(lkFile = '')then exit;
    Form_SetIcon(aOwnerForm, lkFile);
    aOwnerForm.SetCaption(aOwnerForm.Caption);
  end;
