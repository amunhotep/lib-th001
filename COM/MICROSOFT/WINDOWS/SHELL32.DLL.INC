{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/SHELL32.DLL.INC}
{$IFDEF MSWINDOWS}
function ShellExecute(hWindow :LongInt; Operation, FileName, Parameters, Directory: PChar; ShowCmd: LongInt):LongInt; external 'ShellExecuteA@shell32.dll stdcall';
procedure DragAcceptFiles(WindowHandle: LongInt; Accept: LongInt); external 'DragAcceptFiles@shell32.dll stdcall';
{$ENDIF}
{$IFDEF LINUX}
procedure DragAcceptFiles(WindowHandle: LongInt; Accept: LongInt); external 'DragAcceptFiles@libshell32.borland.so stdcall';
{$ENDIF}         
