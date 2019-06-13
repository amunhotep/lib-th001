{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/MAPS.INC}
{$IFNDEF PEAKTOP:OBJ/TSCROLLBOX.INC}              {$I PEAKTOP:OBJ/TSCROLLBOX.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGE.INC}                  {$I PEAKTOP:OBJ/TIMAGE.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC} {$I ../$COMMON/FORMERP.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/MAPS_CONST.INC} {$I ./MAPS_CONST.INC}                         {$ENDIF}
{$IFNDEF PEAKTOP:COM/GOOGLE/MAPS/API.INC}         {$I PEAKTOP:COM/GOOGLE/MAPS/API.INC}          {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/OPER/MAPS.INC ========================
  procedure TERPFormOperMaps_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end; 
  //============================================================================
  function TERPFormOperMaps_Create:TAmunhotepForm;
  var
    lkHTTP :TxiHTTP;
    lkSB       :TScrollBox;
    lkImg      :TImage;
    lkSaveDir  :string;
    lkFileName :string;
    i :Integer;
  begin
    DontAutoFree;
    lkSaveDir := GetCurrentDir;
    ChDir(StrAbsolutePath('../tmp/', Amunhotep.ExeName));
    if not DirectoryExists(ERP_OPER_MAPS_TEMP_DIR) then
      CreateDir(ERP_OPER_MAPS_TEMP_DIR);
    ChDir(lkSaveDir);  
    lkFileName := StrAbsolutePath('../tmp/'+ERP_OPER_MAPS_TEMP_DIR+'/'+FormatDateTime('yyyymmdd_hhnnss',Now)+'_'+RandomHexStr(8)+'.jpeg', Amunhotep.ExeName);
    Result := TAmunhotepForm(TERPForm_Create(msg_captionmaps, ERP_FILENAME_ICO_MAPS, ERP_FILENAME_BMP_MAPS, false, @TERPFormOperMaps_OnClose));
    lkSB   := CreateTScrollBox(Result, Result, 'sbClient', 1,40,640,640,alClient);
    lkImg  := CreateTImage(Result,lkSB,'',alNone,1,1,640,640);
    try
      lkHTTP := TxiHTTP.Create(nil);
      lkHTTP.Host          := 'maps.google.com';
      lkHTTP.InputFileMode := true;
      lkHttp.Body          := lkFileName;
      lkHTTP.Get('http://maps.google.com/maps/api/staticmap?&zoom=15&size=640x640&maptype=hybrid&sensor=false&format=jpg&center=48.732,37.602');
    finally
      lkHTTP.Free;
    end;
    if FileExists(lkFileName)then
      lkImg.Picture.LoadFromFile(lkFileName);
  end;
