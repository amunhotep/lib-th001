{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/LZ32.DLL.INC}
const
  LZERROR_BADINHANDLE  = -1; // invalid input handle
  LZERROR_BADOUTHANDLE = -2; // invalid output handle
  LZERROR_READ         = -3; // corrupt compressed file format
  LZERROR_WRITE        = -4; // out of space for output file
  LZERROR_GLOBALLOC    = -5; // insufficient memory for LZFile struct
  LZERROR_GLOBLOCK     = -6; // bad global handle
  LZERROR_BADVALUE     = -7; // input parameter out of acceptable range
  LZERROR_UNKNOWNALG   = -8; // compression algorithm not recognized
type
  TOFStruct = record
    Bytes     :Byte;
    FixedDisk :Byte;
    ErrorCode :Word;
    Reserved1 :Word;
    Reserved2 :Word;
    PathName  :array[0..127] of Char;
  end;
function  GetExpandedName(Source, Buffer: PChar): Integer;                              external 'GetExpandedNameA@lz32.dll stdcall';
function  LZCopy(Source, Dest: Integer): LongInt;                                       external 'LZCopy@lz32.dll stdcall';
function  LZInit(Source: Integer): Integer;                                             external 'LZInit@lz32.dll stdcall';
function  LZOpenFile(FileName: PChar; var ReOpenBuff: TOFStruct; Style: Word): Integer; external 'LZOpenFileA@lz32.dll stdcall';
function  LZSeek(hFile: Integer; Offset: LongInt; Origin: Integer): LongInt;            external 'LZSeek@lz32.dll stdcall';
function  LZRead(hFile: Integer; Buffer: PChar; Count: Integer): Integer;               external 'LZRead@lz32.dll stdcall';
procedure LZClose(hFile: Integer);                                                      external 'LZClose@lz32.dll stdcall';
