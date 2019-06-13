{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                         {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC =============
  procedure ERP_DBGridEh_Column_FootersLoad(aCol:TColumnEh; aTrans:TxFBTransaction; const aTableName, aFieldName:string);
  var
    lkCntr  :Integer;
    lkFooter:TColumnFooterEh;
  begin
    with TxFBQuery.Create(aTrans) do
      begin
      Transaction := aTrans;
      SQL.Text := 'SELECT F.* FROM TABL$_TB_COLS_FOOTERS F WHERE (F.TB_ID = '''+aTableName+''')AND(F.TC_ID = '''+aFieldName+''') ORDER BY F.ID';
      Open;
      First;
      lkCntr := 0;
      while not EOF do
        begin
        if(lkCntr = 0)then
          lkFooter := aCol.Footer
         else
          lkFooter := aCol.Footers.Add;
        with lkFooter do   
          begin
          Alignment     := IntToTAlignment(FieldByName('ALIGNMENT').AsInteger);
          DisplayFormat := FieldByName('FORMAT').AsString;
          ValueType     := StrToTFooterValueType(FieldByName('VALUE_TYPE').AsString);
          if(ValueType = fvtStaticText)then Value     := FieldByName('NAME').AsString
          if(ValueType = fvtFieldValue)then FieldName := FieldByName('NAME').AsString;
          end;
        lkCntr := lkCntr + 1;
        Next;
        end;
      if Active then
        Close;
      Free;  
      end;  
  end;
