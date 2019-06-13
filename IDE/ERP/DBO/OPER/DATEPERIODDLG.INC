{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/DATEPERIODDLG.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                         {$I PEAKTOP:OBJ/TLABEL.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}        {$I ../$COMMON/FORMERP.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}   {$I ../$COMMON/FORMERP_LANG.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_CONST.INC}  {$I ../$COMMON/FORMERP_CONST.INC}              {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/OPER/DATEPERIODDLG.INC ===============
const ERP_OBJNAME_OPER_DLGDATEPERIOD = 'DLG_DATEPERIOD';
  //============================================================================
  procedure Amunhotep_DatePeriodDialog_OnResize(Sender :TObject);
  begin
    with TForm(Sender) do
      TMonthCalendar(FindComponent('MCFrom')).Width := Trunc(ClientWidth / 2); 
  end;
  //============================================================================
  function Amunhotep_DatePeriodDialog_Execute(var aDateFrom, aDateTo:TDateTime):Boolean;
  var
    lkFrm     :TForm;
    lkLastTop :Integer;
    lkMCFrom  :TMonthCalendar;
    lkMCTo    :TMonthCalendar;
  begin
    Result := false;
    lkFrm := TERPForm_Create(msg_erp_column_selectdateperiod, PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/CALENDAR0016X0016.ICO'), PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/CALENDAR0032X0032.BMP'),true, nil);
    TForm_Position_Load(lkFrm, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLGDATEPERIOD,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))), 250, 360);             
    with lkFrm do
      begin
      OnResize := @Amunhotep_DatePeriodDialog_OnResize;
      with TxcGradientPanelVista(FindComponent(obj_name_erp_topbar)) do
        begin
        StyleManager          := nil;
        Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
        Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
        lkLastTop := Top + Height;
        end;  
      end;
    lkMCFrom := TMonthCalendar.Create(lkFrm);
    with lkMCFrom do
      begin
      name   := 'MCFrom';
      Parent := lkFrm;
      Align  := alLeft;
      Height := 140;
      Width  := 200;
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
      Date           := aDateFrom;
      end;
    lkMCTo := TMonthCalendar.Create(lkFrm);
    with lkMCTo do
      begin
      name   := 'MCTo';
      Parent := lkFrm;
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
      Date           := aDateTo;
      end;
    Result := (lkFrm.ShowModal = mrOk);
    if Result then
      begin
      aDateFrom := lkMCFrom.Date;
      aDateTo   := lkMCTo.Date;
      end;
    TForm_Position_Save(lkFrm, PrepareAbsoleteFileName( ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLGDATEPERIOD,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)) ));   
    lkFrm.Free;  
  end;
