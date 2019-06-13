{$DEFINE PEAKTOP:OBJ/TXFBQUERY.INC}
  //======================= PEAKTOP:OBJ/TXFBQUERY.INC ==========================
  procedure CreateTxFBQuery(const aTransactionParams:array of string; var aTr :TxFBTransaction; var aQr:TxFBQuery);
  var
    i :Integer;
  begin
    aTr := TxFBTransaction.Create(nil);
    with aTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        for i:=0 to Length(aTransactionParams)-1 do
          Add(aTransactionParams[i]);
        end;
      end;
    aQR := TxFBQuery.Create(aTr);
    with aQR do
      begin
      DataBase    := FBDataBase;
      Transaction := aTr;
      end;    
  end;
