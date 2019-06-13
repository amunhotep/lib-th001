{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBOX.INC}      {$I PEAKTOP:OBJ/TXCGROUPBOX.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}           {$I PEAKTOP:OBJ/TLABEL.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDATETIMEPICKER.INC}  {$I PEAKTOP:OBJ/TDATETIMEPICKER.INC}  {$ENDIF}
  //============== PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC ===============
  function InputIntf_DatePeriod_Date(aOwner:TComponent;const aName:string):TDateTime;
  begin
    Result := TDateTimePicker(aOwner.FindComponent(aName)).DateTime;
  end;
  //============================================================================
  procedure InputIntf_DatePeriod_SetDate(aOwner:TComponent;const aName:string; const aValue:string);
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      TDateTimePicker(aOwner.FindComponent(aName)).DateTime := StrToDate(aValue);
  end;
  //============================================================================
  function InputIntf_DatePeriod_Create(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; const aLeft, aTop, aHeight, aWidth:Integer;
             const aNameDateFrom, aNameDateTo:string; const aInitDateForm, aInitDateTo:TDateTime):TxcGroupBox;
  var
    lkLBL :TLabel;
    lkDTP :TDateTimePicker;
  begin
    Result := CreateTxcGroupBox(aOwner, aParent, aName, aCaption,alNone,aLeft,aTop,aHeight,aWidth);
    lkLBL  := CreateTLabel(Result, Result, 'С даты', 4,16,20,48, alNone, taLeftJustify);
    lkDTP  := CreateTDateTimePicker(aOwner,Result,aNameDateFrom,lkLBL.Left+lkLBL.Width+4,lkLBL.Top,20,80,aInitDateForm);  
    lkLBL  := CreateTLabel(Result, Result, 'по дату',lkDTP.Left + lkDTP.Width + 4,lkDTP.Top,20,48, alNone, taLeftJustify);
    lkDTP  := CreateTDateTimePicker(aOwner,Result,aNameDateTo  ,lkLBL.Left+lkLBL.Width+4,lkLBL.Top,20,80,aInitDateTo);  
  end;
