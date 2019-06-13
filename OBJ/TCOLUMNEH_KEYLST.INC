{$DEFINE PEAKTOP:OBJ/TCOLUMNEH_KEYLST.INC}
  //==================== PEAKTOP:OBJ/TCOLUMNEH_KEYLST.INC ======================
  procedure TColumnEh_FillKeyList(const aTableName,aKeyFieldName, aFieldName, aWhereClause:string; aKeys, aPick :TStrings);
  var
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;            
  begin
    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      Params.Clear;
      Params.Add('isc_tpb_read_committed');
      Params.Add('isc_tpb_read');
      Params.Add('isc_tpb_rec_version');
      Params.Add('isc_tpb_nowait');
      end;
    lkQr := TxFBQuery.Create(lkTr);
    lkQr.Transaction := lkTr;
    lkQr.SQL.Text := 'SELECT R.'+aKeyFieldName+', R.'+aFieldName+' FROM '+aTableName+' R ';
    if(StrTrimAll(aWhereClause) <> '')then            
      lkQr.SQL.Text := lkQr.SQL.Text + ' WHERE '+aWhereClause;
    try
      lkQr.Open;
    except
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      exit;  
    end;
    lkQr.First;
    aKeys.Clear;
    aPick.Clear;
    while not lkQr.EOF do
      begin
      aKeys.Add(lkQr.FieldByName(aKeyFieldName).AsString);
      aPick.Add(lkQr.FieldByName(aFieldName).AsString);
      lkQr.Next;
      end; 
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
  end;
