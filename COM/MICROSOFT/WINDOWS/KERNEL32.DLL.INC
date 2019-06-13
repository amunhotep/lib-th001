{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/KERNEL32.DLL.INC}
//================ PEAKTOP:COM/MICROSOFT/WINDOWS/KERNEL32.DLL.INC ==============
procedure Sleep(dwMilliseconds: DWORD);                                           external 'Sleep@kernel32.dll stdcall';
function TerminateProcess  (hProcess :THandle;     uExitCode :LongInt ):LongBool; external 'TerminateProcess@kernel32.dll stdcall';
function GetExitCodeProcess(hProcess :THandle; var lpExitCode:LongWord):LongBool; external 'GetExitCodeProcess@kernel32.dll stdcall';
function WaitForSingleObject(hHandle :THandle; dwMilliseconds:LongWord):LongWord; external 'WaitForSingleObject@kernel32.dll stdcall';
function CloseHandle(hObject :THandle):LongBool;                                  external 'CloseHandle@kernel32.dll stdcall';
function SetPriorityClass(hProcess: THandle; dwPriorityClass:LongWord):LongBool;  external 'SetPriorityClass@kernel32.dll stdcall';
function GetPriorityClass(hProcess: THandle):LongBool;                            external 'GetPriorityClass@kernel32.dll stdcall';
function DeleteFile(lpFileName:PChar):LongBool;                                   external 'DeleteFileA@kernel32.dll stdcall';
function GetEnvironmentVariable(lpName, lpBuffer:PChar; nSize: LongInt):LongInt;  external 'GetEnvironmentVariableA@kernel32 stdcall';
{$IFDEF PEAKTOP:COM/MICROSOFT/WINDOWS/STRUC.INC}
function CreateFile(
           lpFileName             :PChar; 
           dwDesiredAccess        :LongWord; 
           dwShareMode            :LongWord;
           lpSecurityAttributes   :TSecurityAttributes; 
           dwCreationDisposition  :LongWord; 
           dwFlagsAndAttributes   :LongWord;
           hTemplateFile          :THandle
         ):THandle; external 'CreateFileA@kernel32.dll stdcall';
function CreateProcess(
           lpApplicationName         :PChar; 
           lpCommandLine             :PChar;
           lpProcessAttributes       :TSecurityAttributes; 
           lpThreadAttributes        :TSecurityAttributes;
           bInheritHandles           :LongBool; 
           dwCreationFlags           :LongWord; 
           lpEnvironment             :LongWord; //Pointer;
           lpCurrentDirectory        :PChar; 
           const lpStartupInfo       :TStartupInfo;
           var   lpProcessInformation:TProcessInformation
           ):LongBool; external 'CreateProcessA@kernel32.dll stdcall';
{$ENDIF}
