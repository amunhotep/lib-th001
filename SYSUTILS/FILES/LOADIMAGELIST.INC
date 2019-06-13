{$DEFINE PEAKTOP:SYSUTILS/FILES/LOADIMAGELIST.INC}
const //=============== PEAKTOP:SYSUTILS/FILES/LOADIMAGELIST.INC ===============
{$IFDEF LANGUAGE_UKR}msg_loading_images = 'Завантаження зображеннь...';{$ENDIF}
{$IFDEF LANGUAGE_RUS}msg_loading_images = 'Загрузка изображений...';   {$ENDIF}
{$IFDEF LANGUAGE_ENG}msg_loading_images = 'Loading images...';         {$ENDIF}
{$IFDEF LANGUAGE_DEU}msg_loading_images = 'Bilder werden geladen...';  {$ENDIF}
  //============================================================================
  procedure Files_LoadImagesToImageList(aDestImageList:TImageList; aImagesFileNames:TStringList; 
              const aClearDestImageList, aAutoFreeImagesFileNames, aShowProgressDialog:Boolean);
  var
    i         :Integer;
    lkBitmap  :TBitmap; 
    lkBmpEmpty:TBitmap;         
  begin
    lkBmpEmpty := TBitmap.Create;
    with lkBmpEmpty do
      begin
      Width   := aDestImageList.Width;         
      Height  := aDestImageList.Height;
      Canvas.Brush.Color := clWhite;
      Canvas.FillRect(Rect(0,0, aDestImageList.Width-1, aDestImageList.Height-1));
      end;
    if aShowProgressDialog then 
      {$IFDEF PEAKTOP:APPL/SPLASH.INC}
      Amunhotep_Splash_Progress_Set(msg_loading_images,0);
      {$ELSE}
      Dialogs.ProgressDlgShow(msg_loading_images);
      {$ENDIF}
    if aClearDestImageList then aDestImageList.Clear;
    with aImagesFileNames do
      begin        
      for i:=0 to Count-1 do
        begin
        lkBitmap := TBitmap.Create;
        if FileExists(Strings[i])then
          try
            lkBitmap.LoadFromFile(Strings[i]);
          finally
            aDestImageList.AddMasked(lkBitmap, lkBitmap.Canvas.Pixels[0,0] );
          end
         else 
          aDestImageList.AddMasked(lkBmpEmpty, lkBmpEmpty.Canvas.Pixels[0,0] );
        lkBitmap.Free;
        if aShowProgressDialog then
          if((i mod 150) = 0)then
            begin
            {$IFDEF PEAKTOP:APPL/SPLASH.INC}
            Amunhotep_Splash_Progress_Set(msg_loading_images,Trunc(i / Count * 100));
            {$ELSE}
            Dialogs.ProgressDlgSetProgress(Trunc(i / Count * 100));
            Amunhotep.ProcessMessages;
            {$ENDIF}
            end;  
        end;
      if aShowProgressDialog then 
        {$IFDEF PEAKTOP:APPL/SPLASH.INC}
        Amunhotep_Splash_Progress_Hide;
        {$ELSE}
        Dialogs.ProgressDlgHide;
        {$ENDIF}
      if aAutoFreeImagesFileNames then Free;
      end;
    lkBmpEmpty.Free;    
  end;
