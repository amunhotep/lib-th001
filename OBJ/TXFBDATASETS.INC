{$DEFINE PEAKTOP:OBJ/TXFBDATASETS.INC}
  //==================== PEAKTOP:OBJ/TXFBDATASETS.INC ==========================
  procedure CreateTxFBTransDataSet(aOwner:TComponent; const aTransName, aDataSetName,aDataSourceName :string;
             const aTransactionParams:array of string; var aTr :TxFBTransaction; var aDTS:TxFBDataSet;var aDS:TDataSource);
  var
    i :Integer;
  begin
    aTr := TxFBTransaction.Create(aOwner);
    with aTr do
      begin
      if(StrTrimAll(aTransName) <> '')then
        Name := aTransName;
      DefaultDataBase := FBDataBase;
      AutoStopAction  := saNone;
      DefaultAction   := taCommit;
      with Params do
        begin
        Clear;
        for i:=0 to Length(aTransactionParams)-1 do
          Add(aTransactionParams[i]);
        end;
      end;
    aDTS := TxFBDataSet.Create(aTr);
    with aDTS do
      begin
      if(StrTrimAll(aDataSetName) <> '')then
        Name      := aDataSetName;
      DataBase    := FBDataBase;
      Transaction := aTr;
      end;    
    aDS := TDataSource.Create(aDTS);
    with aDS do
      begin
      if(StrTrimAll(aDataSourceName) <> '')then
        Name  := aDataSourceName;
      DataSet := aDTS;
      end; 
  end;
  //============================================================================
  procedure CreateTxFBTransQuery(aOwner:TComponent; const aTransName, aQueryName,aDataSourceName :string;
             const aTransactionParams:array of string; var aTr :TxFBTransaction; var aQR:TxFBQuery;var aDS:TDataSource);
  var
    i :Integer;
  begin
    aTr := TxFBTransaction.Create(aOwner);
    with aTr do
      begin
      if(StrTrimAll(aTransName) <> '')then
        Name := aTransName;
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
      if(StrTrimAll(aQueryName) <> '')then
        Name      := aQueryName;
      DataBase    := FBDataBase;
      Transaction := aTr;
      end;    
    aDS := TDataSource.Create(aQR);
    with aDS do
      begin
      if(StrTrimAll(aDataSourceName) <> '')then
        Name  := aDataSourceName;
      DataSet := aQR;
      end; 
  end;
