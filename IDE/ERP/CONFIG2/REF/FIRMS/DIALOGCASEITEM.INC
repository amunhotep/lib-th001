{$DEFINE PEAKTOP:IDE/ERP/CONFIG/REF/FIRMS/DIALOGCASEITEM.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.02.INC} {$I PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.02.INC} {$ENDIF}
  //========== PEAKTOP:IDE/ERP/CONFIG/REF/FIRMS/DIALOGCASEITEM.INC =============
  function ERPDialogCaseReferenceItem_Firm_Execute(var aFirmID:string):Boolean;
  begin
    Result := ERPDialogCaseReferenceItem02_Execute('TABL$R_FIRMS', 'Выберите фирму учета', aFirmID);
  end;  
