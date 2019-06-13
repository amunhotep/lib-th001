{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADATTRS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COLATTRS.INC}             {$I ../DBGRID/COLATTRS.INC}                  {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADATTRS.INC ==============
  procedure TERPFormRefItem_LoadAttrs(aOwner:TComponent;aParent:TWinControl; aDataSource:TDataSource; const aTableName:string; aQr:TxFBQuery;  
              const aProcessBlob:Boolean; var aSQLSelect, aSQLRefresh, aSQLUpdate, aSQLDelete :string);
  var
    i, j,    lkTop :Integer;
    lkFieldType    :string;
    lkSQLWhere     :string;
    lkSQLSel       :string; 
    lkSQLInsUpdVars:string; 
    lkSQLUpd       :string;
    lkSQLUpdPerFlds:string; 
    lkSQLUpdPerVals:string;
    lkStr          :string;
    lkCaption      :string;
    lkLastLeft     :Integer;
    lkWidth        :Integer;
    lkDBE          :TCustomDBEditEh;
  begin
    with aQr do
      begin
      if Active then
        Close;
      SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETCOLUMNS_REF));
      Prepare;
      ParamByName('PQ_TB_ID').AsString    := aTableName;
      ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
      try
        Open;
      except
      end;
      if not Active then
        begin
        Dialogs.MessageDlg(msg_error_erpsql+' "'+aTableName+'" !',mtWarning,[mbOk]);
        exit;
        end;  
      end;
    aParent.Visible := false;  
    lkSQLSel        := ERP_SQL_TABLEPREFIX+'.ID AS '+ERP_DATASET_DBKEY+' ';
    lkSQLWhere      := '';
    lkSQLInsUpdVars := '  '+ERP_SQL_FIELDPREFIX+ERP_DATASET_DBKEY+'  DOMN$PSTRING = ?'+ERP_DATASET_DBKEY+SQLCRLF; 
    lkSQLUpd        := '';
    lkSQLUpdPerFlds := '';
    lkSQLUpdPerVals := '';
    lkStr           := '';
    i := 0;
    aQr.First;   
    while not aQr.EOF do
      begin
      lkFieldType     := UpperCase(aQr.FieldByName('FIELD_TYPE').AsString);  
      lkSQLInsUpdVars := lkSQLInsUpdVars +' ,'+ERP_SQL_FIELDPREFIX+StrTrimAll(aQr.FieldByName('ID').AsString)+' '+lkFieldType+' = ?'+StrTrimAll(aQr.FieldByName('ID').AsString)+' '+SQLCRLF;   
      if(aQr.FieldByName('FLAG_PERIODICAL').AsInteger = 1)then
        begin
        lkSQLSel := lkSQLSel+SQLCRLF+
          '      ,(SELECT FIRST 1 '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+StrTrimAll(aQr.FieldByName('REF_FIELD').AsString)+
          ' FROM '+StrTrimAll(aQr.FieldByName('REF_TABLE').AsString)+' '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+
          ' WHERE (('+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+StrTrimAll(aQr.FieldByName('REF_KEYFIELD').AsString)+') = '+
          ERP_SQL_TABLEPREFIX+'.ID)AND('+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.VALUE_DATE = '+ERP_SQL_TABLEPREFIX+'.VALUE_DATE )) AS '+
          StrTrimAll(aQr.FieldByName('ID').AsString)+' ';
        if(StrTrimAll(lkSQLUpdPerFlds) = '')then
          begin
          lkSQLUpdPerFlds := 'INSERT INTO '+StrTrimAll(aQr.FieldByName('REF_TABLE').AsString)+' ('+StrTrimAll(aQr.FieldByName('REF_KEYFIELD').AsString);
          lkSQLUpdPerVals := 'VALUES (:'+ERP_SQL_FIELDPREFIX+ERP_DATASET_DBKEY;  
          end;
        if(aQr.FieldByName('ACCS_FLAG_WRITE').AsInteger > 0)then
          begin
          lkSQLUpdPerFlds := lkSQLUpdPerFlds +', '+ StrTrimAll(aQr.FieldByName('ID').AsString);  
          lkSQLUpdPerVals := lkSQLUpdPerVals +', :'+ERP_SQL_FIELDPREFIX+StrTrimAll(aQr.FieldByName('ID').AsString);
          end;  
        end
       else 
        begin
        if(aQr.FieldByName('CALC_SQL').AsString <> '')then
          begin
          lkSQLSel := lkSQLSel+SQLCRLF+'      ,('+StrReplaceStr(aQr.FieldByName('CALC_SQL').AsString, '?', ' '+ERP_SQL_TABLEPREFIX+'.')+') AS '+StrTrimAll(aQr.FieldByName('ID').AsString)+' ';
          end
         else 
          begin
          lkSQLSel := lkSQLSel+SQLCRLF+'      ,'+ERP_SQL_TABLEPREFIX+'.'+StrTrimAll(aQr.FieldByName('ID').AsString)+'  ';
          if(StrTrimAll(aQr.FieldByName('REF_TABLE').AsString)<>'')then
            begin
            lkSQLSel := lkSQLSel+SQLCRLF+
              '      ,(SELECT FIRST 1 COALESCE('+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+
              StrTrimAll(aQr.FieldByName('REF_FIELD').AsString)+', '''+msg_erp_item_not_defined+''') FROM '+
              StrTrimAll(aQr.FieldByName('REF_TABLE').AsString)+' '+
              ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+' WHERE ('+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+
              StrTrimAll(aQr.FieldByName('REF_KEYFIELD').AsString)+' = '+
              ERP_SQL_TABLEPREFIX+'.'+StrTrimAll(aQr.FieldByName('ID').AsString)+
              ')) AS '+StrTrimAll(aQr.FieldByName('ID').AsString)+ERP_SQL_FIELDSUFFIX+' ';
            end;
          if(StrTrimAll(lkSQLUpd) <> '')then
            lkSQLUpd := lkSQLUpd + '    ,'
           else
            lkSQLUpd := lkSQLUpd + '     '; 
          lkSQLUpd := lkSQLUpd + ERP_SQL_TABLEPREFIX+'.'+StrTrimAll(aQr.FieldByName('ID').AsString)+' = :'+ERP_SQL_FIELDPREFIX+StrTrimAll(aQr.FieldByName('ID').AsString)+SQLCRLF;
          end;
        end;
      if( (aQr.FieldByName('ACCS_FLAG_READ').AsInteger<=0) or (aQr.FieldByName('FLAG_DELETE').AsInteger=1) )then
        begin
        i := i + 1;
        aQr.Next;
        continue;
        end;
      if(Pos('DOMN$BLOB_', lkFieldType)=1)then 
        begin
        if aProcessBlob then
          TERPForm_BlobInterface_Create(aDataSource, TxcPageControlEx(aOwner.FindComponent(obj_name_erp_pagecontroldetail)), aQr.FieldByName('NAME').AsString, StrTrimAll(aQr.FieldByName('ID').AsString), lkFieldType, not(aQr.FieldByName('ACCS_FLAG_WRITE').AsInteger > 0));
        i := i + 1;
        aQr.Next;
        continue;
        end;

      lkCaption :=  aQr.FieldByName('NAME').AsString;
      while(Pos('|', lkCaption) > 0)do
        Delete(lkCaption, 1, Pos('|', lkCaption));

      lkLastLeft := TERPForm_DefaultControlIndent;
      lkTop      := aQr.FieldByName('EDT_TOP').AsInteger * 2 * (TERPForm_DefaultControlHeight - TERPForm_DefaultControlIndent);
      for j:=0 to aParent.ControlCount-1 do
        if(ObjectInheritsFrom(aParent.Controls[j], 'TCustomLabel') and (aParent.Controls[j].Top = lkTop))then
          lkLastLeft := MaxInteger(lkLastLeft, (aParent.Controls[j].Left + aParent.Controls[j].Width + TERPForm_DefaultControlIndent));
      lkWidth := aQr.FieldByName('WIDTH').AsInteger;
      if(  (Pos('DOMN$PSTRING', lkFieldType) = 1) or (Pos('DOMN$GUID', lkFieldType) = 1) or (Pos('DOMN$DATE', lkFieldType) = 1)
         or(Pos('DOMN$TIME', lkFieldType) = 1) or(Pos('DOMN$IMAGE_INDEX', lkFieldType) = 1)
         or(StrTrimAll(aQr.FieldByName('KEY_LIST').AsString) <> '') 
         or((StrTrimAll(aQr.FieldByName('REF_TABLE').AsString) <> '') and (aQr.FieldByName('FLAG_PERIODICAL').AsInteger <> 1)))then
        lkWidth := Trunc(lkWidth * TERPForm_DefaultControlWidthMul);
      lkDBE := ERP_DBEditEh_Create(aParent, aDataSource, aQr, lkCaption, lkLastLeft, lkTop, TERPForm_DefaultControlHeight, lkWidth, (aQr.FieldByName('ACCS_FLAG_WRITE').AsInteger <= 0));
      i := i + 1;
      aQr.Next;
      end; 
    aSQLSelect := 'SELECT '+lkSQLSel+SQLCRLF+'FROM   '+aTableName+' '+ERP_SQL_TABLEPREFIX+'  '+SQLCRLF+
                  'WHERE ('+ERP_SQL_TABLEPREFIX+'.ID = '''+TERPForm_Settings(aOwner).Values[ERP_DATASET_DBKEY]+''') '+SQLCRLF+lkSQLWhere;
    aSQLRefresh:= 'SELECT FIRST 1 '+lkSQLSel+SQLCRLF+'FROM '+aTableName+' '+ERP_SQL_TABLEPREFIX+' '+SQLCRLF+
                  'WHERE ('+ERP_SQL_TABLEPREFIX+'.ID = ?'+ERP_DATASET_DBKEY+')  '+SQLCRLF;
    aSQLDelete := 'DELETE FROM '+aTableName+' '+ERP_SQL_TABLEPREFIX+' WHERE ('+ERP_SQL_TABLEPREFIX+'.ID = ?'+ERP_DATASET_DBKEY+') ';
    aSQLUpdate := 
      'EXECUTE BLOCK ( '+SQLCRLF+lkSQLInsUpdVars+')AS '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  UPDATE '+aTableName+' '+ERP_SQL_TABLEPREFIX+' SET '+SQLCRLF+lkSQLUpd+
      '  WHERE ('+ERP_SQL_TABLEPREFIX+'.ID = :'+ERP_SQL_FIELDPREFIX+ERP_DATASET_DBKEY+'); '+SQLCRLF;
    if(StrTrimAll(lkSQLUpdPerFlds)<>'')then
      aSQLUpdate := aSQLUpdate+'  '+lkSQLUpdPerFlds+') '+lkSQLUpdPerVals+'); '+SQLCRLF;
    aSQLUpdate := aSQLUpdate +'END ';
    aParent.Visible := true;  
  end;  
