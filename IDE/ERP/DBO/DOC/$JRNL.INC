{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}{$I PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}{$ENDIF}
// DEPRECATED, FOR OLD SCRIPTS COMPABILITY !!!
var
  JrnlCaptionAdd :string;
  JrnlDateFrom   :TDateTime;
  JrnlDateTo     :TDateTime;
  JrnlDateInit   :Boolean;
  JrnlForm       :TAmunhotepForm;
  //============================================================================
  function Jrnl_HardFilter_Index(const aFieldName:string):Integer;
  begin
    Result  := TERPFormGrid_DataSetFilter_Index(aFieldName);
  end;
  //============================================================================
  function Jrnl_HardFilter_Add(const aFieldName, aFilterStr:string):Integer;
  begin
    Result := TERPFormGrid_DataSetFilter_Add(aFieldName, aFilterStr);
  end;  
  //============================================================================
  function JtnlForm_Create(const aTypeId:string):TAmunhotepForm;
  begin
    TERPFormGrid_DataSetFilter_DateInit := JrnlDateInit;
    TERPFormGrid_DataSetFilter_DateFrom := JrnlDateFrom;
    TERPFormGrid_DataSetFilter_DateTo   := JrnlDateTo;
    Result := TAmunhotepForm(Journal_Create(aTypeId));
    if(JrnlCaptionAdd <> '')then
      begin
      TAmunhotepForm(Result).SetCaption(TAmunhotepForm(Result).Caption+' ('+JrnlCaptionAdd+')');
      TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)).Caption := #$20#$20#$20#$20#$20#$20+TAmunhotepForm(Result).Caption;
      end;
  end;
