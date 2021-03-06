{ **** UBPFD *********** by kladovka.net.ru ****
>> �������� �����������, ��������� � TBitmap, � OleVariant ��� �������� �� COM/DCOM

�����������: Classes
�����:       ��������, barma@amazonit.ru
Copyright:   (�) ������� ����� �������������, �.������, 2002 �.
����:        29 ������ 2002 �.
********************************************** }

function SaveBitmapToVariant(Bitmap: TBitmap): Variant;
// ���������� ����������� �� TBitmap � OleVariant
var
  Stream: TMemoryStream;
  Buffer: Variant;
  PBuffer: pointer;
begin
  Result:=varEmpty;
  Stream:=TMemoryStream.Create;
  Bitmap.SaveToStream(Stream);

  Buffer:=VarArrayCreate([0,Stream.Size-1],VarByte);
  PBuffer:=VarArrayLock(Buffer);
  try
    Stream.Position:=0;
    Stream.Read(PBuffer^,Stream.Size);
  finally
    VarArrayUnlock(Buffer);
    Stream.Free;
  end;

  Result:=Buffer;
end;


{ **** UBPFD *********** by kladovka.net.ru ****
>> ���������� ����������� �� OleVariant � TBitmap, ��� �������� �� COM/DCOM

�����������: Classes
�����:       ��������, barma@amazonit.ru
Copyright:   (�) ������� ����� �������������, �.������, 2002 �.
����:        29 ������ 2002 �.
********************************************** }

procedure LoadBitmapFromVariant(Bitmap: TBitmap; Buffer: OleVariant);
// �������� ����������� � TBitmap �� OleVariant
var
  Stream: TMemoryStream;
  PBuffer: pointer;
begin
  if not VarIsArray(Buffer) then Exit;

  Stream:=TMemoryStream.Create;
  PBuffer:=VarArrayLock(Buffer);
  try
    Stream.Write(PBuffer^,(VarArrayHighBound(Buffer,1)-VarArrayLowBound(Buffer,1)+1));
  finally
    VarArrayUnlock(Buffer);
  end;

  Stream.Position:=0;
  Bitmap.LoadFromStream(Stream);
  Stream.Free;
end;

