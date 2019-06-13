{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/ADVAPI.DLL.CAPTURE.INC}
const //========== PEAKTOP:COM/MICROSOFT/WINDOWS/ADVAPI.DLL.CAPTURE.INC ========
  WM_CAP_START                  = $0400; // WM_USER
  WM_CAP_STOP                   = WM_CAP_START + 68;
  WM_CAP_DRIVER_CONNECT         = WM_CAP_START + 10;
  WM_CAP_DRIVER_DISCONNECT      = WM_CAP_START + 11;
  WM_CAP_SAVEDIB                = WM_CAP_START + 25;
  WM_CAP_GRAB_FRAME             = WM_CAP_START + 60;
  WM_CAP_SEQUENCE               = WM_CAP_START + 62;
  WM_CAP_FILE_SET_CAPTURE_FILEA = WM_CAP_START + 20;

function capCreateCaptureWindowA(lpszWindowName :PChar; dwStyle, x, y, nWidth, nHeight :LongInt; 
           ParentWin :hWND; nId :Integer):hWnd; external 'capCreateCaptureWindowA@AVICAP32.DLL stdcall';           
