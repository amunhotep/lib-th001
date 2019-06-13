{$DEFINE PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTBITMAP.INC}
  //================== PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTBITMAP.INC ==========
  procedure Files_LoadBitmapToImageList(aDestImageList :TImageList; const a_FileName:string);
  var
    lkBmp :TBitmap;
  begin
    if not FileExists(a_FileName) then exit;
    lkBmp := TBitmap.Create;
    with lkBmp do
      begin
      Height := aDestImageList.Height;
      Width  := aDestImageList.Width;
        try
          LoadFromFile(a_FileName);
        finally  
          aDestImageList.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0] );
        end;     
      Free;
      end;  
  end;
