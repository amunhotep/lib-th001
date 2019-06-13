{$DEFINE PEAKTOP:IDE/ERP/CONFIG/DOC/EXTRACTTYPEID.INC}
  //============= PEAKTOP:IDE/ERP/CONFIG/DOC/EXTRACTTYPEID.INC =================
  function ExtractTypeIdFromCurrentScript:string;
  var
    i :Integer;
  begin
    Result := ScriptName;
    i := Length(Result);
    while(i > 1)do
      begin
      if( (Result[i] = '/') or (Result[i] = '\') )then
        break;
      i := i - 1;
      end;
    Delete(Result, i, Length(Result) - i + 1);
    i := Length(Result);
    while(i > 1)do
      begin
      if( (Result[i] = '/') or (Result[i] = '\') )then
        break;
      i := i - 1;
      end;
    Delete(Result, 1, i);
  end;
