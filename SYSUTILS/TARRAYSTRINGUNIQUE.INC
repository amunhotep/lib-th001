{$DEFINE PEAKTOP:SYSUTILS/TARRAYSTRINGUNIQUE.INC}
type //================ PEAKTOP:SYSUTILS/TARRAYSTRINGUNIQUE.INC ================
  TArrayStringUnique = array of string;
  //============================================================================
  function IndexInArrayStringUnique(const aStr:string; var aArr:TArrayStringUnique):Integer;
  var
    i, lkCount :Integer;
  begin
    Result  := -1;
    lkCount := Length(aArr);
    for i:=0 to lkCount-1 do
      if(aArr[i] = aStr)then
        begin
        Result := i;
        exit;
        end;
    lkCount := lkCount + 1;    
    SetLength(aArr, lkCount);
    aArr[lkCount-1] := aStr; 
    Result := lkCount - 1;   
  end;
