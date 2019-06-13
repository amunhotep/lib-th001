{$DEFINE PEAKTOP:SYSUTILS/DATASET2XML.INC}
  //============================================================================
  function FieldTypeToSQL(const Fld:TField):string;
  begin
    Result := '';
    case Fld.DataType of
      ftBoolean  : Result := 'fieldtype="BOOLEAN"';
      ftString   : Result := 'fieldtype="VARCHAR" size="'+IntToStr(Fld.Size)+'"';
      ftSmallint : Result := 'fieldtype="SMALLINT"';
      ftAutoInc,
      ftInteger,
      ftWord     : Result := 'fieldtype="INTEGER"';
      ftLargeint : Result := 'fieldtype="BIGINT"';
      ftFloat    : Result := 'fieldtype="FLOAT"';
      ftCurrency,
      ftBCD, 
      ftFMTBcd   : Result := 'fieldtype="NUMERIC" size="'+IntToStr(Fld.Size)+'"';
      ftDate     : Result := 'fieldtype="DATE"'; 
      ftTime     : Result := 'fieldtype="TIME"';
      ftDateTime, 
      ftTimeStamp: Result := 'fieldtype="TIMESTAMP"';
      ftBlob     : Result := 'fieldtype="BLOB"';
      ftGraphic  : Result := 'fieldtype="BLOB" sub_type="0"';
      ftMemo,
      ftFmtMemo  : Result := 'fieldtype="BLOB" sub_type="TEXT"';
    end;
  end;
  //============================================================================
  function FieldValueToSGML(const Value:string):string ;
  var
    i, j :Integer;
  begin
    Result := '';
    for i:=1 to Length(Value) do
      begin
      j := Ord(Value[i]);
      Result := Result + '&#' + FormatFloat('0000', j)+';';
      end;
  end;
  //============================================================================
  function DataSetToXML(Source :TDataSet):string;
  var
    i :Integer;
    SaveRecNo :Integer;
  begin
    Result := '<?xml version = "1.0" encoding="windows-1251" ?>' + #13#10;
    if(Source=nil)then exit;
    if not(Source.Active)then exit;
    Result := Result + '<datapacket version="3.8.12.3812">'+ #13#10;
    Result := Result + '  <metadata>'+ #13#10;
    Result := Result + '    <fields>'+ #13#10;
    for i:=0 to Source.Fields.Count-1 do
      Result := Result + '      <field name="' + AnsiUpperCase(Source.Fields[i].FieldName) + '" '+FieldTypeToSQL(Source.Fields[i])+' />' + #13#10;
    Result := Result + '    </fields>' + #13#10;
    Result := Result + '  </metadata>' + #13#10;
    Result := Result + '  <rowset>'+#13#10;
    SaveRecNo := Source.RecNo;
    Source.DisableControls;
    Source.First;
    while not Source.EOF do
      begin
      Result := Result + '    <row>'+#13#10;
      for i:=0 to Source.Fields.Count-1 do
        Result := Result + 
           '      <'+AnsiUpperCase(Source.Fields[i].FieldName) + '>'+
           FieldValueToSGML(Source.Fields[i].AsString)+
           '</'+AnsiUpperCase(Source.Fields[i].FieldName)+'>'+#13#10;
      Result := Result + '    </row>'+#13#10;
      Source.Next;
      end;
    Result := Result + '  </rowset>' + #13#10;
    Result := Result + '</datapacket>' + #13#10;
    Source.RecNo := SaveRecNo;
    Source.EnableControls;
  end;  
