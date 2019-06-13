{$DEFINE PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTICON.INC}
  //================== PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTICON.INC ============
  procedure Files_LoadIconToImageList(aDestImageList :TImageList; const a_FileName:string);
  var
    lkIcon  :TIcon;
  begin
    if not FileExists(a_FileName) then exit;
    lkIcon := TIcon.Create;
    with lkIcon do
      begin
      Height := aDestImageList.Height;
      Width  := aDestImageList.Width;
        try
          LoadFromFile(a_FileName);
        finally  
          aDestImageList.AddIcon(lkIcon);
        end;     
      Free;
      end;  
  end;
  //============================================================================
  procedure Files_LoadIconsToImageList(aDestImageList:TImageList; aImagesFileNames:TStringList; const aClearDestImageList, aAutoFreeImagesFileNames:Boolean);
  var
    i :Integer;
  begin
    if aClearDestImageList then aDestImageList.Clear;
    for i:=0 to aImagesFileNames.Count-1 do
      Files_LoadIconToImageList(aDestImageList, aImagesFileNames[i]);
    if aAutoFreeImagesFileNames then aImagesFileNames.Free;
  end;
