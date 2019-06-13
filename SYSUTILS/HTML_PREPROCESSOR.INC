{$DEFINE PEAKTOP:SYSUTILS/HTML_PREPROCESSOR.INC}
  //======================================================================
  function HTMLProcessor_GetField(const a_FieldName:string; a_DataSets :array of TDataSet):string;
  var
    lk_field :TField;
    lk_i     :Integer;
  begin
    Result := '<font color="#FF0080"><b>'+a_FieldName+'</b></font>';
    for lk_i:=0 to GetArrayLength(a_DataSets)-1 do
      if(a_DataSets[lk_i].Active)then
        begin
        lk_Field := a_DataSets[lk_i].FindField(a_FieldName);
        if(lk_Field<>nil)then
          begin
          if((lk_Field.DataType=ftFloat)or(lk_Field.DataType=ftCurrency)or(lk_Field.DataType=ftBCD)or(lk_Field.DataType=ftFMTBcd))then 
            Result := FormatFloat('#0.00 ', lk_Field.AsFloat) 
           else 
            Result := lk_Field.AsString;
          exit;
          end;
        end;
  end;
  //============================================================================
  function HTMLProcessor_Preprocess(const a_Template:string; a_DataSets :array of TDataSet):string;
  var
    lk_i     :Integer; 
    lk_j     :Integer;
    lk_Token :string;
  begin
    Result := a_Template;
    lk_i := Pos('<%', Result);
    while(lk_i>0)do
      begin
      lk_j := Pos('%>', Result);
      if(lk_j < lk_i)then break; 
      lk_token := Copy(Result, lk_i + 2, lk_j - lk_i - 2);
      Delete(Result, lk_i, lk_j - lk_i + 2);
      Insert(HTMLProcessor_GetField(lk_token, a_DataSets), Result, lk_i); 
      lk_i := Pos('<%', Result);
      end;
  end;