{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}{$I PEAKTOP:GLOBAL_VARIABLES.INC}{$ENDIF}
{$DEFINE PEAKTOP:SYSUTILS/SQL_FUNCS.INC}
  //============================================================================
  function BooleanToSQL(const Value :Boolean):string;
  begin
    if Value then Result := '1' else Result := '0';
  end;
  //============================================================================
  function SelectFirstField(const a_TableName, a_FieldName:string; var a_Value:string):Boolean;
  var
    lk_Tr :TxFBTransaction;
    lk_Qr :TxFBQuery; 
  begin
    Result := false;
    lk_Tr := TxFBTransaction.Create(nil);
    lk_Tr.DefaultDataBase := FBDataBase;
    lk_Qr                 := TxFBQuery.Create(lk_Tr);
    lk_Qr.Transaction     := lk_Tr;
    lk_Qr.SQL.Text := 'SELECT * FROM '+a_TableName+' ';
    try
      lk_Qr.Open;
     finally
      if lk_Qr.Active then
        if(lk_Qr.RecordCount>0)then
          begin
          lk_Qr.First;
          a_Value := lk_Qr.FieldByName(a_FieldName).AsString;
          Result := true;
          if lk_Tr.InTransaction then lk_Tr.Commit; 
          end;
     end;
    if lk_Tr.InTransaction then lk_Tr.Rollback;
    lk_Tr.Free;
  end;
  //============================================================================
  function SQLRefItemInsert(const a_TableName, a_FieldNames, a_FieldValues:string; 
             var a_NewItemId :string):Boolean;
  var
    lk_Tr :TxFBTransaction;
    lk_Qr :TxFBQuery;
  begin
    Result      := false;
    a_NewItemId := '';
    lk_Tr       := TxFBTransaction.Create(nil);
    lk_Tr.DefaultDataBase := FBDataBase;
    lk_Qr                 := TxFBQuery.Create(lk_Tr);
    lk_Qr.Transaction     := lk_Tr;
    lk_Qr.SQL.Text        := 'INSERT INTO '+a_TableName+'('+a_FieldNames+')VALUES('+a_FieldValues+') ';
    lk_Qr.ParamCheck      := false;  
    lk_Tr.StartTransaction;
    try
      lk_Qr.ExecSQL;
      if lk_Qr.Active then lk_Qr.Close;
      lk_Qr.SQL.Text := 'SELECT MAX(TB.ID) AS ID FROM '+a_TableName+' TB ';
      try
        lk_Qr.Open;
       finally 
        if lk_Qr.Active then
          if(lk_Qr.RecordCount>0)then
            begin
            lk_Qr.First;
            a_NewItemId := lk_Qr.FieldByName('ID').AsString;
            Result      := true;
            if lk_Tr.InTransaction then lk_Tr.Commit; 
            end;
       end;
     except
      Dialogs.MessageDlg(lk_Qr.SQL.Text+FormatErrorMessage('0063'), mtWarning, [mbOk]);    
     end;
    if lk_Tr.InTransaction then lk_Tr.Rollback;
    lk_Tr.Free;
  end;