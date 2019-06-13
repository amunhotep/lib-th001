{$DEFINE PEAKTOP:SYSUTILS/FILES/CHECKPATH.INC}
  //================== PEAKTOP:SYSUTILS/FILES/CHECKPATH.INC ====================
  procedure CheckFilePath(const aFileName:string);
  var
    lkSaveDir :string;
    lkPath    :string;
    lkItem    :string;
  begin
    lkPath := ExtractFilePath(aFileName);
    lkSaveDir := GetCurrentDir();
    lkItem := Copy(lkPath, 1, Pos(':', lkPath)+1); Delete(lkPath, 1, Pos(':', lkPath)+1); 
    ChDir(lkItem);
    while(Length(lkPath) > 0)do
      begin
      lkItem := Copy(lkPath, 1, Pos('\', lkPath)); Delete(lkPath, 1, Pos(':', lkPath)); 
      
      end;
    ChDir(lkSaveDir);  
  end;
