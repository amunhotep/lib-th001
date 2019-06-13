{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/GDI32.DLL.INC}
{$IFNDEF PEAKTOP:COM/MICROSOFT/WINDOWS/TYPES.INC}    {$I ./TYPES.INC}   {$ENDIF}
  //================ PEAKTOP:COM/MICROSOFT/WINDOWS/GDI32.DLL.INC ===============
{$IFDEF MSWINDOWS}  
function DeleteObject(hObject :LongInt): LongBool; external 'DeleteObject@gdi32.dll stdcall';
function CreateEllipticRgn(p1, p2, p3, p4: Integer):HRGN   ; external 'CreateEllipticRgn@gdi32.dll stdcall';
function CreateEllipticRgnIndirect(const p1: TRect):HRGN   ; external 'CreateEllipticRgnIndirect@gdi32.dll stdcall';
function CombineRgn(p1, p2, p3: HRGN; p4: Integer ):Integer; external 'CombineRgn@gdi32.dll stdcall';
function CreateRectRgn(p1, p2, p3, p4: Integer): HRGN;  external 'CreateRectRgn@gdi32.dll stdcall';
function CreateRectRgnIndirect(const p1: TRect): HRGN;  external 'CreateRectRgnIndirect@gdi32.dll stdcall';
function CreateRoundRectRgn(p1, p2, p3, p4, p5, p6: Integer): HRGN; external 'CreateRoundRectRgn@gdi32.dll stdcall';
function EqualRgn(p1, p2: HRGN): LongBool;  external 'EqualRgn@gdi32.dll stdcall';
function FillRgn(DC: HDC; HR: HRGN; hbr: HBRUSH): LongBool;  external 'FillRgn@gdi32.dll stdcall';
function FrameRgn(DC: HDC; HR: HRGN; hbr: HBRUSH; Width, Height: Integer): LongBool;  external 'FrameRgn@gdi32.dll stdcall';
function GetClipRgn(DC: HDC; rgn: HRGN): Integer; external 'GetClipRgn@gdi32.dll stdcall';
function GetMetaRgn(DC: HDC; rgn: HRGN): Integer; external 'GetMetaRgn@gdi32.dll stdcall';
function GetRgnBox(RGN: HRGN; var p2: TRect): Integer; external 'GetRgnBox@gdi32.dll stdcall';
function InvertRgn(DC: HDC; p2: HRGN): LongBool;  external 'InvertRgn@gdi32.dll stdcall';
function OffsetRgn(RGN: HRGN; XOffset, YOffset: Integer):Integer; external 'OffsetRgn@gdi32.dll stdcall';
function PaintRgn(DC: HDC; RGN: HRGN): LongBool; external 'PaintRgn@gdi32.dll stdcall';
function PtInRegion(RGN: HRGN; X, Y: Integer): LongBool; external 'PtInRegion@gdi32.dll stdcall';
function RectInRegion(RGN: HRGN; const Rect: TRect): LongBool; external 'RectInRegion@gdi32.dll stdcall';
function SelectClipRgn(DC: HDC; Region: HRGN): Integer;  external 'SelectClipRgn@gdi32.dll stdcall';
function SetRectRgn(Rgn: HRgn; X1, Y1, X2, Y2: Integer): LongBool; external 'SetRectRgn@gdi32.dll stdcall';
function PathToRegion(DC: HDC): HRGN;  external 'PathToRegion@gdi32.dll stdcall';
//function CreatePolygonRgn(const Points; Count, FillMode: Integer): HRGN; stdcall;
function GetDCEx(hWnd: HWND; hrgnClip: HRGN; flags: DWORD): HDC; external 'GetDCEx@user32.dll stdcall';
function GetUpdateRgn(hWnd: HWND; hRgn: HRGN; bErase: LongBool): Integer; external 'GetUpdateRgn@user32.dll stdcall';
function SetWindowRgn(hWnd: HWND; hRgn: HRGN; bRedraw: LongBool): Integer; external 'SetWindowRgn@user32.dll stdcall';
function GetWindowRgn(hWnd: HWND; hRgn: HRGN): Integer; external 'GetWindowRgn@user32.dll stdcall';
function ExcludeUpdateRgn(hDC: HDC; hWnd: HWND): Integer;  external 'ExcludeUpdateRgn@user32.dll stdcall';
function InvalidateRgn(hWnd: HWND; hRgn: HRGN; bErase: LongBool):LongBool; external 'InvalidateRgn@user32.dll stdcall';
function ValidateRgn(hWnd: HWND; hRgn: HRGN):LongBool; external 'ValidateRgn@user32.dll stdcall';
{$ENDIF} 
