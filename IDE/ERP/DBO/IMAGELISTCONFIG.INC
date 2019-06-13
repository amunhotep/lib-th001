{$DEFINE PEAKTOP:IDE/ERP/DBO/IMAGELISTCONFIG.INC}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}           {$I PEAKTOP:OBJ/TIMAGELIST.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}  {$I ./OBJECTNAMES.INC}           {$ENDIF}
  //=================== PEAKTOP:IDE/ERP/DBO/IMAGELISTCONFIG.INC ================
  function TERPImageList_Indicies:array of Integer;
  var
    i :Integer;
  begin
    SetLength(Result, ERP_OBJECTTYPES_COUNT);
    for i:=ERP_OBJECTTYPE_UNKN to ERP_OBJECTTYPES_COUNT-1 do
      Result[i] := ERP_ObjectImageIndex(i);
  end;
  //============================================================================
  function CreateTImageListConfiguration(a_Owner:TComponent; const a_Name :string):TImageList;
  begin
    Result := CreateTImageList(a_Owner, a_Name, TERPImageList_Indicies);
  end;
