{ 
**** UBPFD *********** by kladovka.net.ru ****
>> Шифрование текстовых полей таблицы Interbase

Простенько но шустро шифрует текстовую строку VarChar в текстовую
строку VarChar, пригодную для сохранения в текстовом поле базы Interbase.
НЕ ЗАТРАГИВАЕТ ПРОБЕЛЫ!
Метод генерации (в начале) и изменения ключа (в 2-местах!) в вашей программе
лучше изменить от исходного в сторону усложнения, но не трогать "And 127" в конце. 
Для работы с Char возможно стоит добавить "Trim(S1);" в самое начало.

Зависимости: Windows, SysUtils, DB
Автор:       Vemer, Vemer@List.Ru, Петрозаводск
Copyright:   Vemer
Дата:        16 ноября 2003 г.
********************************************** }

  function CryptText( S1 :string; T:Boolean):string;
  var
    LS :Byte;//длина строки
    KB :Byte;//ключ, байт
    I  :Byte;//Счетчик
    B  :Byte;//байт строки
    W  :Smallint;//буфер для ключа
    S2 :string;//результат
  begin
    LS := Length(S1);
    S2 := '';
    KB := LS * LS; //-------Изменить/Усложнить!And 127 не трогать!
    if T = False Then // Выбор между шифрованием и дешифрованием
      begin
      For I := 1 to LS Do
        begin //шифрование
        B:= Byte(S1[I]);
        If B > 32 Then
          begin
          W := B + KB;
          If W > 255 Then W := W - 223;
          B := W;
          end;//If
        S2 := S2 + Chr(B);
        KB := (KB + (I*2)) And 127; //-(1) Изменить/Усложнить! And 127 не трогать!
        end;//For
      end
     Else
      begin//дешифровка
      For I := 1 to LS Do
        begin
        B:= Byte(S1[I]);
        If B > 32 Then
          begin
          W := B - KB;
          If W < 33 Then 
            W := W + 223;
          B := W;
          end;//If
        S2 := S2 + Chr(B);
        KB := (KB + (I*2)) And 127;//---(2) Сделать как в (1)! And 127 не трогать!
        end;//For
      end;//Else
    Result := S2;
  end;
