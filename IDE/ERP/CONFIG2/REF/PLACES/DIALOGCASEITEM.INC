{$DEFINE PEAKTOP:IDE/ERP/CONFIG/REF/PLACES/DIALOGCASEITEM.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.INC} {$I PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.INC} {$ENDIF}
  //========== PEAKTOP:IDE/ERP/CONFIG/REF/PLACES/DIALOGCASEITEM.INC=============
  function ERPDialogCaseReferenceItem_Place_Execute(var aFirmID:string):Boolean;
  begin
    Result := ERPDialogCaseReferenceItem_Execute('TABL$R_PLACES', 'Выберите место хранения', aFirmID);
  end;  
