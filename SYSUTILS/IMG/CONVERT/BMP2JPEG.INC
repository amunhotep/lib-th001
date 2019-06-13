{$DEFINE PEAKTOP:SYSUTILS/IMG/CONVERT/BMP2JPEG.INC}
  //===================== PEAKTOP:SYSUTILS/IMG/CONVERT/BMP2JPEG.INC ============
  function Image_BmpToJpeg(aBitmap :TBitmap; aJpeg:TJPEGImage):Boolean;
  begin
    Result := false;
    if(aBitmap = nil)then exit;
    if(aJpeg   = nil)then exit;
    with aJpeg do
      try
        Assign(aBitmap);
        Compress;
      finally
        Result := true;
      end; 
  end;
  //============================================================================
  function Image_BmpToJpeg_SaveToFile(aBitmap :TBitmap; const aFileName:string):Boolean;
  var
    lkJpgImg :TJPEGImage;
  begin
    Result := false;
    if(StrTrimAll(aFileName) = '')then exit;
    lkJpgImg := TJPEGImage.Create;
    Result := Image_BmpToJpeg(aBitmap, lkJpgImg);
    if Result then
      try
        lkJpgImg.SaveToFile(aFileName);
      finally
        lkJpgImg.Free;
      end; 
  end;
  //============================================================================
  function Image_BmpToJpeg_FileName(const aSrcFileName, aDestFileName:string):Boolean;
  var
    lkBitmap :TBitmap;
  begin
    Result := false;
    if(StrTrimAll(aSrcFileName) = '')then exit;
    lkBitmap := TBitmap.Create;
    with lkBitmap do
      try
        LoadFromFile(aSrcFileName);
      finally
        Result := Image_BmpToJpeg_SaveToFile(lkBitmap, aDestFileName);
        Free;
      end; 
  end;
