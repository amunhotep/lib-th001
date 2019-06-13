{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/BUGTRACK/DEFAULT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC} {$I ../../$COMMON/FORMERP.INC}                   {$ENDIF}
const //=========== PEAKTOP:IDE/ERP/DBO/OPER/BUGTRACK/DEFAULT.INC ==============
  msg_captionbugtrack       = 'BUG tracking system';
  ERP_FILENAME_ICO_BUGTRACK = 'PEAKTOP:IMG/CONFIG/BUGTRACK/MAINICON0016X0016.ICO'; 
  ERP_FILENAME_BMP_BUGTRACK = 'PEAKTOP:IMG/CONFIG/BUGTRACK/MAINICON0032X0032.BMP'; 
  //============================================================================
  procedure TERPFormOperBugtrack_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end; 
  //============================================================================
  function TERPFormOperBugtrack_Create:TAmunhotepForm;
  begin
    DontAutoFree;
    Result := TAmunhotepForm(TERPForm_Create(msg_captionbugtrack, ERP_FILENAME_ICO_BUGTRACK, ERP_FILENAME_BMP_BUGTRACK, false, @TERPFormOperBugtrack_OnClose));
  end;
