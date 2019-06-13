{$DEFINE PEAKTOP:IDE/ERP/CONFIG/REF/FIRMS/DIALOGCASEITEM.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.02.INC} {$I PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.02.INC} {$ENDIF}
  //========== PEAKTOP:IDE/ERP/CONFIG/REF/FIRMS/DIALOGCASEITEM.INC =============
  function ERPDialogCaseReferenceItem_Firm_Execute(var aFirmID:string):Boolean;
  var
    lkCount :string;
  begin
    lkCount := '0';
    GetField(FBDataBase, 'TABL$R_FIRMS', 'COALESCE(COUNT(ID),0)', 'FLAG_DELETE = 0', lkCount);
    if(StrToInt(lkCount) <= 1)then
      begin
      GetField(FBDataBase, 'TABL$R_FIRMS', 'MIN(ID)', 'FLAG_DELETE = 0', aFirmID);
      Result := True;
      end
     else 
      Result := ERPDialogCaseReferenceItem02_Execute('TABL$R_FIRMS', 'Выберите фирму учета', aFirmID);
  end;  
