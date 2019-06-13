{ **** UBPFD *********** by kladovka.net.ru ****
>> Упаковка изображения, хранимого в TBitmap, в OleVariant для передачи по COM/DCOM

Зависимости: Classes
Автор:       Бармалей, barma@amazonit.ru
Copyright:   (с) Муханов Игорь Станиславович, г.Москва, 2002 г.
Дата:        29 апреля 2002 г.
********************************************** }

function SaveBitmapToVariant(Bitmap: TBitmap): Variant;
// Сохранение изображения из TBitmap в OleVariant
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
>> Распаковка изображения из OleVariant в TBitmap, для передачи по COM/DCOM

Зависимости: Classes
Автор:       Бармалей, barma@amazonit.ru
Copyright:   (с) Муханов Игорь Станиславович, г.Москва, 2002 г.
Дата:        29 апреля 2002 г.
********************************************** }

procedure LoadBitmapFromVariant(Bitmap: TBitmap; Buffer: OleVariant);
// Загрузка изображения в TBitmap из OleVariant
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

