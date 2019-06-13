{$DEFINE PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}
  //================== PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC ====================
  function TWinControl_AutoWidth(aWinControl:TWinControl):Integer;
  var
    i :Integer;
  begin
    Result := 0;
    with aWinControl do
      for i:=0 to ControlCount-1 do
        Result := MaxInteger(Result, (Controls[i].Left + Controls[i].Width));
  end;
  //============================================================================
  function TWinControl_AutoWidth2(aWinControl:TWinControl):Integer;
  var
    i :Integer;
  begin
    Result := 0;
    with aWinControl do
      for i:=0 to ControlCount-1 do
        Result := MaxInteger(Result, (Result + Controls[i].Width));
  end;  
