{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/CALENDAR.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC} {$I ../$COMMON/FORMERP.INC}                   {$ENDIF}
const //========================================================================
  msg_captioncalendar       = 'Календарь';
  ERP_FILENAME_ICO_CALENDAR = 'PEAKTOP:IMG/CONFIG/CALENDAR0016X0016.ICO'; 
  ERP_FILENAME_BMP_CALENDAR = 'PEAKTOP:IMG/CONFIG/CALENDAR0032X0032.BMP'; 
  //============================================================================
  procedure TERPFormOperCalendar_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end; 
  //============================================================================
  function TERPFormOperCalendar_Create:TAmunhotepForm;
  var
    lkMonthCalendar :TMonthCalendar;
  begin
    DontAutoFree;
    Result := TAmunhotepForm(TERPForm_Create(msg_captioncalendar, ERP_FILENAME_ICO_CALENDAR, ERP_FILENAME_BMP_CALENDAR, false, @TERPFormOperCalendar_OnClose));
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    lkMonthCalendar := TMonthCalendar.Create(Result);
    with lkMonthCalendar do
      begin
      Name   := 'MonthCalendar';
      Parent := Result;
      Align  := alClient;
      with CalColors, Amunhotep.MainForm.StyleManager.Colors do
        begin
        BackColor         := Window;
        TextColor         := Border;
        TitleBackColor    := HotTrackBorder;
        TitleTextColor    := Window;
        MonthBackColor    := Window;
        TrailingTextColor := Background;
        end;
      WeekNumbers    := true;
      FirstDayOfWeek := dowMonday;
      end;
  end;
