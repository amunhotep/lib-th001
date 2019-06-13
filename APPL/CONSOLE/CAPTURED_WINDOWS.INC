{$DEFINE PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC}
{$IFDEF MSWINDOWS}
{$IFNDEF PEAKTOP:COM/MICROSOFT/WINDOWS/STRUC.INC}       {$I PEAKTOP:COM/MICROSOFT/WINDOWS/STRUC.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:COM/MICROSOFT/WINDOWS/KERNEL32.DLL.INC}{$I PEAKTOP:COM/MICROSOFT/WINDOWS/KERNEL32.DLL.INC}{$ENDIF}
{$IFNDEF PEAKTOP:COM/MICROSOFT/WINDOWS/CONST.INC}       {$I PEAKTOP:COM/MICROSOFT/WINDOWS/CONST.INC}       {$ENDIF}
  //================= PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC ================
  function RunCaptured(const aDirectory, aExeName, aCmdLine:string):string;
  var
    StartInf :TStartupInfo; 
    ProcInf  :TProcessInformation; 
    SecAttr  :TSecurityAttributes; 
    TmpSA1   :TSecurityAttributes; 
    TmpName  :string; 
    TmpHndl  :THandle; 
    TmpRslt  :Cardinal;
    ProcCreated :LongBool; 
    TmpSL    :TStrings;
  begin
    Result    := 'FAILURE';
    TmpName   := '../tmp/console/'+FormatDateTime('yyyymmdd-hhnnss-', Now)+RandomHexStr(8)+'.txt';                 
    TmpName   := StrAbsolutePath(TmpName, Amunhotep.ExeName);
    TmpName := StrReplaceStr(TmpName, '/', '\');
    SecAttr.nLength        := SizeOf(SecAttr); 
    SecAttr.bInheritHandle := True; 
    try
      TmpHndl := CreateFile(PChar(TmpName), GENERIC_WRITE, FILE_SHARE_WRITE, SecAttr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
      WriteLn('TmpHndl='+IntToStr(TmpHndl));
      try
        StartInf.cb          := SizeOf(StartInf); 
        StartInf.hStdOutput  := TmpHndl; 
        StartInf.dwFlags     := STARTF_USESTDHANDLES or STARTF_USESHOWWINDOW; 
        StartInf.wShowWindow := SW_HIDE;
        ProcCreated          := true;
        ProcCreated := CreateProcess(PChar(aExeName), PChar(aExeName+' '+aCmdLine), TmpSA1, TmpSA1, ProcCreated,0,0,PChar(aDirectory),StartInf,ProcInf);
        if(Integer(ProcCreated) = 1)then 
          begin 
          SetPriorityClass   (ProcInf.hProcess,IDLE_PRIORITY_CLASS); 
          WaitForSingleObject(ProcInf.hProcess,INFINITE); 
          GetExitCodeProcess (ProcInf.hProcess,TmpRslt); 
          CloseHandle(ProcInf.hThread); 
          CloseHandle(ProcInf.hProcess); 
          CloseHandle(TmpHndl);
          TmpSL := TStringList.Create;
          try
            TmpSL.LoadFromFile(TmpName);
           finally 
            Result := TmpSL.Text;
           end;
          TmpSL.Free;   
          DeleteFile(PChar(TmpName)); 
          end 
         else 
          Result := 'Ошибка вызова внешнего приложения:'+#13#10+'  '+ScriptName+#13#10+'  PEAKTOP:APPL/CONSOLE/CAPTURED_WINDOWS.INC; LINE:0054';
       except
       end;
     finally
      CloseHandle(TmpHndl); 
      DeleteFile(PChar(TmpName)); 
     end; 
  end;
{$ENDIF}
