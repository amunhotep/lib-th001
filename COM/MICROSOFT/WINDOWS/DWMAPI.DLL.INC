{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/DWMAPI.DLL.INC}
{$IFNDEF PEAKTOP:COM/MICROSOFT/WINDOWS/TYPES.INC}     {$I ./TYPES.INC}    {$ENDIF}
  //================= PEAKTOP:COM/MICROSOFT/WINDOWS/DWMAPI.DLL.INC =============
type  
  TDWM_BLURBEHIND = packed record
    Flags                :DWORD;
    Enable               :LongBool;
    BlurRegion           :HRGN;
    TransitionOnMaximized:LongBool;
  end;
{$IFDEF MSWINDOWS}
function DwmEnableBlurBehindWindow(hWnd: hWnd; const pBlurBehind: TDWM_BLURBEHIND): HRESULT; external 'DwmEnableBlurBehindWindow@dwmapi.dll stdcall';
{$ENDIF}     
