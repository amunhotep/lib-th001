{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/STRUC.INC}
// Windows C/C++ structures
type
  _STARTUPINFOA = record
    cb             :LongWord;
    lpReserved     :Longword; // Pointer;
    lpDesktop      :Longword; // Pointer;
    lpTitle        :Longword; // Pointer;
    dwX            :LongWord;
    dwY            :LongWord;
    dwXSize        :LongWord;
    dwYSize        :LongWord;
    dwXCountChars  :LongWord;
    dwYCountChars  :LongWord;
    dwFillAttribute:LongWord;
    dwFlags        :LongWord;
    wShowWindow    :Word;
    cbReserved2    :Word;
    lpReserved2    :LongWord; // Pointer;
    hStdInput      :THandle;
    hStdOutput     :THandle;
    hStdError      :THandle;
  end;
  TStartupInfo = _STARTUPINFOA;

  _PROCESS_INFORMATION = record
    hProcess       :THandle;
    hThread        :THandle;
    dwProcessId    :LongWord;
    dwThreadId     :LongWord;
  end;
  TProcessInformation = _PROCESS_INFORMATION;
  
  _SECURITY_ATTRIBUTES = record
    nLength             :LongWord;
    lpSecurityDescriptor:LongWord; // Pointer;
    bInheritHandle      :LongBool;
  end;
  TSecurityAttributes = _SECURITY_ATTRIBUTES;
