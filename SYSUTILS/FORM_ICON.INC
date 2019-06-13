{$DEFINE PEAKTOP:SYSUTILS/FORM_ICON.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}            {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
  //===================== PEAKTOP:SYSUTILS/FORM_ICON.INC =======================
  function Form_SetIcon(aForm :TForm;const aFileName:string):Boolean;
  var
    lkFileName :string;
    lkStrm     :TMemoryStream;
  begin
    Result := false;
    lkFileName := PrepareAbsoleteFileName(aFileName);
    if(Pos('DB:', UpperCase(lkFileName)) = 1)then
      try
        lkStrm := TMemoryStream.Create;
        if StreamLoadFromFile(lkFileName, lkStrm)then
          aForm.Icon.LoadFromStream(lkStrm);
      finally    
        lkStrm.Free;
        Result := true;
      end
     else
      begin
      Result := FileExists(lkFileName);
      if Result then
        try
          aForm.Icon.LoadFromFile(lkFileName);
        finally
          Result := true;
        end; 
      end; 
  end;
