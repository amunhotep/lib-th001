{$DEFINE PEAKTOP:SYSUTILS/SQL/GETFIELDS.INC}
  //=================== PEAKTOP:SYSUTILS/SQL/GETFIELDS.INC =====================
  function GetSQLFields(aDB :TxFBDataBase; const aSQL:string; const aFieldNames:array of string; var aFieldValues :array of string):Boolean;
  var
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
    i    :Integer;
  begin
    Result := false;
    if not aDB.Connected then exit;
    if not (Length(aFieldNames)>0)then exit; 
    if(Length(aFieldNames) <> Length(aFieldValues))then exit;
    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := aDB;
      with Params do
        begin
        Clear;
        Add('isc_tpb_read_committed');
        Add('isc_tpb_write');
        Add('isc_tpb_rec_version');
        Add('isc_tpb_wait');
        end;
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQr do
      begin
      Transaction := lkTr;
      SQL.Text := aSQL;
      try
        Open;
      except
      end;
      if not Active then
        begin
        if lkTr.InTransaction then
          lkTr.Commit;
        lkTr.Free;
        exit;  
        end;
      Last;
      for i:=0 to Length(aFieldNames)-1 do
        aFieldValues[i] := FieldByName(aFieldNames[i]).AsString;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
    Result := true;  
  end;
