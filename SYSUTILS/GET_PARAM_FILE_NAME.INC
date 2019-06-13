{$DEFINE PEAKTOP:SYSUTILS/GET_PARAM_FILE_NAME.INC}
  //============== PEAKTOP:SYSUTILS/GET_PARAM_FILE_NAME.INC ====================
  function GetParamFileName(const FromParam:Integer):string;
  var
    i :Integer;
  begin
    Result := '';
    for i:=MaxInteger(1,FromParam) to Amunhotep.ParamCount do
      Result := Result + Amunhotep.ParamStr[i];
    i := Pos('"', Result);
    if(i > 0)then
      while(i > 0)do
        begin
        Delete(Result, i, 1);
        i := Pos('"', Result);
        end;  
  end;
