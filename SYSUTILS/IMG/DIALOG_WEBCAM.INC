{$DEFINE PEAKTOP:SYSUTILS/IMG/DIALOG_WEBCAM.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC} {$I PEAKTOP:GLOBAL_VARIABLES.INC} {$ENDIF}
const  //========== PEAKTOP:SYSUTILS/IMG/DIALOG_WEBCAM_SETTINGS.INC ============
  DialogWebCam_FileNameBufferVar   = 'DIALOG_WEBCAM_IMAGEFILENAME';
  DialogWebCam_FileNameImage       = 'TMP:WEBCAM_';
  DialogWebCam_FileNameImageFormat = 'YYYYMMDD_HHNN';
  DialogWebCam_FileNameConfig      = 'TMP:DIALOG_WEBCAM.CFG';
  //============================================================================
  function DialogWebCam_Execute_GetFileName(var aFileName:string):Boolean;
  begin
    Result := false;
    SetGlobalVariable(DialogWebCam_FileNameBufferVar, aFileName);
    call('PEAKTOP:SYSUTILS/IMG/DIALOG_WEBCAM.PS');
    aFileName := GetGlobalVariable(DialogWebCam_FileNameBufferVar);
    Result := (StrTrimAll(aFileName) <> '');
  end;  
