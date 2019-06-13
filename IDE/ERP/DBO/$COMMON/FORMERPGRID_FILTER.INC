{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_FILTER.INC}
type //=========== PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_FILTER.INC ==========
  TERPFormGrid_DataSetFilterItem = record
    FieldName :string;
    FilterStr :string;
  end;
  TERPFormGrid_DataSetFilterArray = array of TERPFormGrid_DataSetFilterItem;
var
  TERPFormGrid_DataSetFilter          :TERPFormGrid_DataSetFilterArray;
  TERPFormGrid_DataSetFilter_DateInit :Boolean;  
  TERPFormGrid_DataSetFilter_DateFrom :TDateTime;  
  TERPFormGrid_DataSetFilter_DateTo   :TDateTime;  
  //============================================================================
  function TERPFormGrid_DataSetFilter_Count:Integer;
  begin
    Result := Length(TERPFormGrid_DataSetFilter);
  end;
  //============================================================================
  function TERPFormGrid_DataSetFilter_Index(const aFieldName:string):Integer;
  var
    i, lkCount :Integer;
  begin
    Result  := -1;
    lkCount := TERPFormGrid_DataSetFilter_Count;
    for i:=0 to lkCount-1 do
      if(TERPFormGrid_DataSetFilter[i].FieldName = aFieldName)then
        begin
        Result := i;
        exit;
        end;
  end;
  //============================================================================
  function TERPFormGrid_DataSetFilter_Exists(const aFieldName:string):Boolean;
  begin
    Result := (TERPFormGrid_DataSetFilter_Index(aFieldName) > -1);
  end;
  //============================================================================
  function TERPFormGrid_DataSetFilter_Add(const aFieldName, aFilterStr:string):Integer;
  var
    i :Integer;
  begin
    Result  := TERPFormGrid_DataSetFilter_Index(aFieldName);
    if(Result > 0)then
      begin
      TERPFormGrid_DataSetFilter[Result].FilterStr := aFilterStr; 
      Result := i;
      exit;
      end;
    Result := TERPFormGrid_DataSetFilter_Count;    
    SetLength(TERPFormGrid_DataSetFilter, Result + 1);
    TERPFormGrid_DataSetFilter[Result].FieldName := aFieldName; 
    TERPFormGrid_DataSetFilter[Result].FilterStr := aFilterStr; 
  end;
