{$DEFINE PEAKTOP:IDE/ERP/CONFIG2/DOC/SQLEXEC.INC}
  //============================================================================
  function DocForm_ExecSQLParams(const aTransactionParams:array of string; const aSQL:string; const aParamNames, aParamValues:array of string):Boolean;
  var
    i    :Integer;
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
  begin
    Result := false;
    if not FBDataBase.Connected then exit;
    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        if(Length(aTransactionParams) > 0)then
          for i:=0 to Length(aTransactionParams)-1 do
            Add(aTransactionParams[i])
         else
          begin
          Add('isc_tpb_read_committed');
          Add('isc_tpb_write');
          Add('isc_tpb_rec_version');
          Add('isc_tpb_nowait');
          end;   
        end;
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQR do
      begin
      Transaction := lkTr;
      SQL.Text := aSQL;
      if(Length(aParamNames) > 0)then
        begin
        Prepare;
        for i:=0 to Length(aParamNames)-1 do
          ParamByName(aParamNames[i]).AsString := aParamValues[i]; 
        end;
      try
        ExecSQL;
      except
        if lkTr.InTransaction then
          lkTr.Rollback;
        lkTr.Free;
        exit;    
      end;  
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;    
    Result := true;
  end;
  //============================================================================
  function DocForm_OpenSQLParams(const aTransactionParams:array of string; const aSQL:string; const aParamNames, aParamValues:array of string):Boolean;
  var
    i    :Integer;
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
  begin
    Result := false;
    if not FBDataBase.Connected then exit;
    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        if(Length(aTransactionParams) > 0)then
          for i:=0 to Length(aTransactionParams)-1 do
            Add(aTransactionParams[i])
         else
          begin
          Add('isc_tpb_read_committed');
          Add('isc_tpb_write');
          Add('isc_tpb_rec_version');
          Add('isc_tpb_nowait');
          end;   
        end;
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQR do
      begin
      Transaction := lkTr;
      SQL.Text := aSQL;
      if(Length(aParamNames) > 0)then
        begin
        Prepare;
        for i:=0 to Length(aParamNames)-1 do
          ParamByName(aParamNames[i]).AsString := aParamValues[i]; 
        end;
      try
        Open;
      except
        if lkTr.InTransaction then
          lkTr.Rollback;
        lkTr.Free;
        exit;    
      end;  
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;    
    Result := true;
  end;
  //============================================================================
  function DocForm_ExecSQL(const aTransactionParams:array of string; const aSQL:string):Boolean;
  begin
    Result := DocForm_ExecSQLParams(aTransactionParams, aSQL, [], []);
  end;
  //============================================================================
  function DocForm_SelectSQLParams(const aTransactionParams:array of string; const aSQL:string; const aParamNames, aParamValues, aVarNames:array of string;
              var aVarValues :array of string):Boolean;
  var
    i    :Integer;
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
  begin
    Result := false;
    if not FBDataBase.Connected then exit;
    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        if(Length(aTransactionParams) > 0)then
          for i:=0 to Length(aTransactionParams)-1 do
            Add(aTransactionParams[i])
         else
          begin
          Add('isc_tpb_read_committed');
          Add('isc_tpb_write');
          Add('isc_tpb_rec_version');
          Add('isc_tpb_nowait');
          end;   
        end;
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQR do
      begin
      Transaction := lkTr;
      SQL.Text := aSQL;
      if(Length(aParamNames) > 0)then
        begin
        Prepare;
        for i:=0 to Length(aParamNames)-1 do
          ParamByName(aParamNames[i]).AsString := aParamValues[i]; 
        end;
      try
        Open;
      except
        if lkTr.InTransaction then
          lkTr.Rollback;
        lkTr.Free;
        exit;    
      end;  
      if Active then
        begin
        Last;
        if(Length(aVarNames) > 0)then
          for i:=0 to Length(aVarNames)-1 do
            aVarValues[i] := FieldByName(aVarNames[i]).AsString;
        end;    
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;    
    Result := true;
  end;
