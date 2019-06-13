{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/CHECKBOX/INTF.INC}
{$IFNDEF PEAKTOP:OBJ/TXCCHECKBOX.INC}      {$I PEAKTOP:OBJ/TXCCHECKBOX.INC}      {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/INPUT/CHECKBOX/INTF.INC =============
  function InputIntf_CheckBox_Checked(aOwner:TComponent; const aName:string):string;
  begin
    if TxcCheckBox(aOwner.FindComponent(aName)).Checked then
      Result := '1'
     else
      Result := '0'; 
  end;
  //============================================================================
  procedure InputIntf_CheckBox_SetCheckedStr(aOwner:TComponent; const aName, aValue:string);
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      TxcCheckBox(aOwner.FindComponent(aName)).Checked := (aValue = '1');
  end;
  //============================================================================
  function InputIntf_CheckBox_Create(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; const aLeft, aTop, aHeight, aWidth:Integer):TxcCheckBox;
  begin
    Result := CreateTxcCheckBox(aOwner, aParent, aName, aCaption,aCaption, alNone,aLeft,aTop,aHeight,aWidth, false);
  end;
