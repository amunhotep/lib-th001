{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/COMBOBOX.INC}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBOX.INC}      {$I PEAKTOP:OBJ/TXCGROUPBOX.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}           {$I PEAKTOP:OBJ/TLABEL.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOMBOBOX.INC}        {$I PEAKTOP:OBJ/TCOMBOBOX.INC}        {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/INPUT/COMBOBOX.INC  ==================
  function InputIntf_ComboBox_ItemIndex(aOwner:TComponent;const aName:string):Integer;
  begin
    Result := TComboBox(aOwner.FindComponent(aName)).ItemIndex;
  end;
  //============================================================================
  procedure InputIntf_ComboBox_SetItemIndex(aOwner:TComponent;const aName:string; const aValue:Integer);
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      TComboBox(aOwner.FindComponent(aName)).ItemIndex := aValue;
  end;
  //============================================================================
  function InputIntf_ComboBox_Create(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; const aLeft, aTop, aHeight, aWidth:Integer;
             const aNameComboBox, aItems:string; const aItemIndex :Integer):TxcGroupBox;
  var
    lkCBX :TComboBox;
  begin
    Result := CreateTxcGroupBox(aOwner, aParent, aName, aCaption, alNone, aLeft, aTop, aHeight, aWidth);
    lkCBX  := CreateTComboBox(aOwner, Result, '', 4, 20, 20, aWidth-8, aItems, aItemIndex);
    with lkCBX do
      begin
      Name       := aNameComboBox;
      Style      := csDropDownList;
      Font.Style := Font.Style + [fsBold];
      end;
  end;
