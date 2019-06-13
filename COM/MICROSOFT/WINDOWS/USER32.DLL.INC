{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/USER32.DLL.INC}
{$IFDEF MSWINDOWS}
function FindWindow   (C1, C2: PChar): Longint;                                            external 'FindWindowA@USER32.DLL stdcall';
function ShowWindow   (hWndHandle, nCmdShow: LongInt):Integer;                             external 'ShowWindow@USER32.DLL stdcall';
function SetWindowText(hWndHandle: Longint; Text: PChar): Longint;                         external 'SetWindowTextA@USER32.DLL stdcall';
function SendMessageA (hWndHandle :HWND; Msg, wParam,lParam:LongInt):LongInt;              external 'SendMessageA@USER32.DLL stdcall';
function SendMessageA_PChar(hWndHandle :HWND; Msg, wParam :LongInt; lParam:PChar):LongInt; external 'SendMessageA@USER32.DLL stdcall';
function LoadIcon  (hInstance: THandle; lpIconName  :PChar):HICON  ;                       external 'LoadIconA@USER32.DLL stdcall';
function LoadBitmap(hInstance: THandle; lpBitmapName:PChar):HBITMAP;                       external 'LoadBitmapA@USER32.DLL stdcall';
function LoadCursor(hInstance: THandle; lpCursorName:PChar):LongInt;                       external 'LoadCursorA@USER32.DLL stdcall';
function LoadCursorFromFile(lpFileName :PChar): LongInt;                                   external 'LoadCursorFromFileA@USER32.DLL stdcall';
function DestroyCursor(hCursor:HICON):LongBool;                                            external 'DestroyCursor@USER32.DLL stdcall';
function DestroyIcon  (hIcon  :HICON):LongBool;                                            external 'DestroyIcon@USER32.DLL stdcall';
{$ENDIF}
