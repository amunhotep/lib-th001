{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/DATEMONTH/INTF.INC}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBOX.INC}      {$I PEAKTOP:OBJ/TXCGROUPBOX.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}           {$I PEAKTOP:OBJ/TLABEL.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOMBOBOX.INC}        {$I PEAKTOP:OBJ/TCOMBOBOX.INC}        {$ENDIF}
const //============== PEAKTOP:IDE/ERP/DBO/INPUT/DATEMONTH/INTF.INC ============
  InputIntf_DateMonth_DateFrom = 'InputIntf_DateMonth_DateFrom';
  InputIntf_DateMonth_Dateto   = 'InputIntf_DateMonth_DateTo';
  InputIntf_ObjName_Month      = 'cbxMonth';
  InputIntf_ObjName_Year       = 'cbxYear';
  //============================================================================
  function InputIntf_DateMonth_Date(aOwner:TComponent;const aName, aDateKind:string):TDateTime;
  var
    lkDate     :TDateTime;
    lkCmp      :TComponent;
    lkCbxMonth :TComboBox;
    lkCbxYear  :TComboBox;
  begin
    Result     := Now;
    lkCmp      := aOwner.FindComponent(aName);
    lkCbxMonth := TComboBox(lkCmp.FindComponent(InputIntf_ObjName_Month));
    lkCbxYear  := TComboBox(lkCmp.FindComponent(InputIntf_ObjName_Year ));
    lkDate     := StrToDate('02.'+FormatFloat('00', lkCbxMonth.ItemIndex+1)+'.'+lkCbxYear.Text);
         if(aDateKind = InputIntf_DateMonth_DateFrom)then Result := StartOfTheMonth(lkDate)
    else if(aDateKind = InputIntf_DateMonth_DateTo  )then Result := EndOfTheMonth  (lkDate);
  end;
  //============================================================================
  function InputIntf_DateMonth_Create(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; const aLeft, aTop, aHeight, aWidth:Integer):TxcGroupBox;
  var
    i          :Integer;
    lkLBL      :TLabel;
    lkCbxMonth :TComboBox;
    lkCbxYear  :TComboBox;
  begin
    Result := CreateTxcGroupBox(aOwner, aParent, aName, aCaption,alNone,aLeft,aTop,aHeight,aWidth);
    lkLBL  := CreateTLabel(Result, Result, '  Ã≈—ﬂ÷', 4,16,20,48, alNone, taLeftJustify);
    lkCbxMonth := CreateTComboBox(Result, Result, '', lkLBL.Left+lkLBL.Width+4,lkLBL.Top,20,96,'',-1);
    with lkCbxMonth do
      begin
      Name := InputIntf_ObjName_Month;
      Items.Clear;
      for i:=1 to 12 do
        Items.Add(FormatDateTime('mmmmm', StrToDate('02.'+FormatFloat('00',i)+'.2010')));
      ItemIndex := Items.IndexOf(FormatDateTime('mmmmm', Now));
      Style := cbsDropDown; 
      Font.Style := [fsBold];
      Font.Size  := 8; 
      end;  
    lkLBL  := CreateTLabel(Result, Result, ' √Œƒ ',lkCbxMonth.Left + lkCbxMonth.Width + 4,lkCbxMonth.Top,20,32, alNone, taLeftJustify);
    lkCbxYear := CreateTComboBox(Result, Result, '', lkLBL.Left+lkLBL.Width+4,lkLBL.Top,20,60,'',-1);
    with lkCbxYear do
      begin
      Name := InputIntf_ObjName_Year;
      for i:=2010 to StrToInt(FormatDateTime('yyyy', Now)) do
        Items.Add(FormatFloat('0000',i));
      ItemIndex := Items.IndexOf(FormatDateTime('yyyy',Now));
      Style := cbsDropDown;  
      Font.Style := [fsBold];
      Font.Size  := 8; 
      end;
  end;  
