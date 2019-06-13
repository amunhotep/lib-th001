{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCOLUMNS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COLCREATE.INC}            {$I ../DBGRID/COLCREATE.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC}        {$I ../$COMMON/FORMERP_BLOB.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_FILTER.INC}  {$I ../$COMMON/FORMERPGRID_FILTER.INC}       {$ENDIF}
  //================ PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCOLUMNS.INC ===========
  procedure TERPFormGrid_LoadDBGridColumns(const aTableName:string; aQr:TxFBQuery; aDBG:TDBGridEh; 
              aPageControlBLOB :TxcPageControlEx; const aFlagMaster, aFlagDateTime:Boolean; const aMasterFieldName:string;
              var aSQLSelect, aSQLRefresh, aSQLInsert, aSQLUpdate, aSQLDelete, aSelectFilter :string);
  var
    i              :Integer;
    lkFieldType    :string;
    lkSQLWhere     :string;
    lkSQLSel       :string; 
    lkSQLInsUpdVars:string; 
    lkSQLInsFlds   :string; 
    lkSQLInsVals   :string; 
    lkSQLIns       :string; 
    lkSQLUpd       :string;
    lkSQLUpdPerFlds:string; 
    lkSQLUpdPerVals:string;
    lkSQLUpdPerMtch:string;
    lkSQLUpdPerAdd :string;
    lkSQLUpdPerNULL:string;
    lkCol          :TColumnEh; 
  begin
    aSelectFilter := '';
    with aQr do
      begin
      if Active then
        Close;
      SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETCOLUMNS_REF));
      Prepare;
      ParamByName('PQ_TB_ID').AsString    := aTableName;
      ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
      try Open; except end;
      if not Active then
        begin
        Dialogs.MessageDlg(msg_error_erpsql+' "'+aTableName+'" !',mtWarning,[mbOk]);
        exit;
        end;  
      end;
    aDBG.Visible := false;
    aDBG.Columns.Clear;
    aQr.First;   
    lkSQLSel        :=         ERP_SQL_TABLEPREFIX+'.ID AS '+ERP_DATASET_DBKEY+' '+SQLCRLF+
                       '      ,IIF((SELECT COALESCE(COUNT(I1.ID),0) FROM TABL$_IMG I1 WHERE (I1.OBJ_ID = '''+aTableName+''') AND (I1.REC_ID = '+ERP_SQL_TABLEPREFIX+'.ID))>0, 1, 0) AS '+ERP_SQL_FIELD_IMAGES+' '+SQLCRLF;
    lkSQLWhere      := 'WHERE (1 = 1) '+SQLCRLF;
    if aFlagDateTime then
      lkSQLWhere    := 'WHERE ('+ERP_SQL_TABLEPREFIX+'.DATE_COMMIT BETWEEN  ?'+ERP_SQL_FIELDDATEFROM+' AND  ?'+ERP_SQL_FIELDDATETO+') '+SQLCRLF;
    lkSQLInsUpdVars := '   '+StrEndSpaces(ERP_SQL_FIELDPREFIX+ERP_DATASET_DBKEY   ,32)+' DOMN$PSTRING         = ?'+ERP_DATASET_DBKEY   +SQLCRLF+
                       '  ,'+StrEndSpaces(ERP_SQL_FIELDPREFIX+ERP_SQL_FIELD_IMAGES,32)+' DOMN$INTEGER         = ?'+ERP_SQL_FIELD_IMAGES+SQLCRLF;
    lkSQLInsFlds    := ''; 
    lkSQLInsVals    := ''; 
    lkSQLIns        := '';
    lkSQLUpd        := '';
    lkSQLUpdPerFlds := '';
    lkSQLUpdPerVals := '';
    lkSQLUpdPerMtch := '';
    lkSQLUpdPerAdd  := '';
    lkSQLUpdPerNULL := '';
//    if aFlagMaster then
//      lkSQLSel := lkSQLSel +', '+ERP_SQL_TABLEPREFIX+'.'+aMasterFieldName+' AS '+aMasterFieldName+ERP_SQL_FIELDSUFFIX+ERP_SQL_FIELDSUFFIX+' ';
    i := 0;
    while not aQr.EOF do
      begin
      if TERPFormGrid_DataSetFilter_Exists(aQr.FieldByName('ID').AsString) then
        lkSQLWhere := lkSQLWhere +'  AND ('+StrReplaceStr(TERPFormGrid_DataSetFilter[TERPFormGrid_DataSetFilter_Index(aQr.FieldByName('ID').AsString)].FilterStr, '?', ' '+ERP_SQL_TABLEPREFIX+'.')+') '+SQLCRLF;
      lkFieldType     := UpperCase(aQr.FieldByName('FIELD_TYPE').AsString);  
      lkSQLInsUpdVars := lkSQLInsUpdVars +'  ,'+StrEndSpaces(ERP_SQL_FIELDPREFIX+StrTrimAll(aQr.FieldByName('ID').AsString),32)+' '+StrEndSpaces(lkFieldType,20)+' = ?'+StrTrimAll(aQr.FieldByName('ID').AsString)+' '+SQLCRLF;   
      if(aQr.FieldByName('FLAG_PERIODICAL').AsInteger = 1)then
        begin
        lkSQLSel := lkSQLSel+SQLCRLF+
          '      ,(SELECT FIRST 1 '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+StrTrimAll(aQr.FieldByName('REF_FIELD').AsString)+
          ' FROM '+StrTrimAll(aQr.FieldByName('REF_TABLE').AsString)+' '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+
          ' WHERE (('+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+StrTrimAll(aQr.FieldByName('REF_KEYFIELD').AsString)+') = '+
          ERP_SQL_TABLEPREFIX+'.ID)AND('+
          ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, i)+'.'+ERP_SQL_PERIODICALDATEFIELD+' = '+
          ERP_SQL_TABLEPREFIX+'.'+ERP_SQL_PERIODICALDATEFIELD+' )) AS '+StrTrimAll(aQr.FieldByName('ID').AsString)+' ';
        if(StrTrimAll(lkSQLUpdPerFlds) = '')then
          begin
          lkSQLUpdPerNULL := '  P_PERIODICAL_DATE = :'+ERP_SQL_FIELDPREFIX+ERP_SQL_PERIODICALDATEFIELD+'; '+SQLCRLF+
                             '  IF(:P_PERIODICAL_DATE IS NULL)THEN P_PERIODICAL_DATE = CURRENT_TIMESTAMP; '+SQLCRLF;
          lkSQLUpdPerFlds := SQLCRLF+
                             '  UPDATE OR INSERT INTO '+StrTrimAll(aQr.FieldByName('REF_TABLE').AsString)+'('+StrTrimAll(aQr.FieldByName('REF_KEYFIELD').AsString)+', '+ERP_SQL_PERIODICALDATEFIELD;
          lkSQLUpdPerVals := '    VALUES (:'+ERP_SQL_FIELDPREFIX+ERP_DATASET_DBKEY+', :P_PERIODICAL_DATE '; 
          lkSQLUpdPerMtch := '    MATCHING ('+StrTrimAll(aQr.FieldByName('REF_KEYFIELD').AsString)+', '+ERP_SQL_PERIODICALDATEFIELD+')'+SQLCRLF+
                             '    RETURNING '+ERP_SQL_PERIODICALDATEFIELD+SQLCRLF+
                             '    INTO      :P_PERIODICAL_DATE '; 
          end;
        if( (aQr.FieldByName('ACCS_FLAG_WRITE').AsInteger > 0) and (StrTrimAll(aQr.FieldByName('ID').AsString) <> ERP_SQL_PERIODICALDATEFIELD) )then
          begin
          lkSQLUpdPerFlds := lkSQLUpdPerFlds +', '+ StrTrimAll(aQr.FieldByName('ID').AsString);  
          lkSQLUpdPerVals := lkSQLUpdPerVals +', :'+ERP_SQL_FIELDPREFIX+StrTrimAll(aQr.FieldByName('ID').AsString);
          if(StrTrimAll(lkSQLUpdPerAdd) = '')then
            lkSQLUpdPerAdd  := lkSQLUpdPerAdd  + '  UPDATE '+aTableName+' TM1 SET TM1.'+ERP_SQL_PERIODICALDATEFIELD+' = :P_PERIODICAL_DATE '+//ERP_SQL_FIELDPREFIX+ERP_SQL_PERIODICALDATEFIELD+
              ' WHERE (TM1.ID = :'+ERP_SQL_FIELDPREFIX+ERP_DATASET_DBKEY+');  '+SQLCRLF;
          end;
        end
       else 
        begin
        if(aQr.FieldByName('CALC_SQL').AsString <> '')then
          begin
          lkSQLSel := lkSQLSel+SQLCRLF+'      ,('+StrReplaceStr(aQr.FieldByName('CALC_SQL').AsString, '?', ' '+ERP_SQL_TABLEPREFIX+'.')+') AS '+StrTrimAll(aQr.FieldByName('ID').AsString)+' ';
          if( aFlagMaster and (aMasterFieldName = StrTrimAll(aQr.FieldByName('ID').AsString)) )then
            aSelectFilter := '('+StrReplaceStr(aQr.FieldByName('CALC_SQL').AsString, '?', ' '+ERP_SQL_TABLEPREFIX+'.')+')';
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
          if(StrTrimAll(lkSQLInsFlds) <> '')then
            begin
            if((i mod 8) = 0)then
              begin
              lkSQLInsFlds := lkSQLInsFlds + SQLCRLF + '    ';
              lkSQLInsVals := lkSQLInsVals + SQLCRLF + '    ';
              end;
            lkSQLInsFlds := lkSQLInsFlds + ',';
            lkSQLInsVals := lkSQLInsVals + ',';
            end;
          lkSQLInsFlds := lkSQLInsFlds + StrTrimAll(aQr.FieldByName('ID').AsString);
          lkSQLInsVals := lkSQLInsVals + ':'+ERP_SQL_FIELDPREFIX+StrTrimAll(aQr.FieldByName('ID').AsString);
          if(StrTrimAll(lkSQLUpd) <> '')then
            lkSQLUpd := lkSQLUpd + '    ,'
           else
            lkSQLUpd := lkSQLUpd + '     '; 
          lkSQLUpd := lkSQLUpd + ERP_SQL_TABLEPREFIX+'.'+StrEndSpaces(StrTrimAll(aQr.FieldByName('ID').AsString),32)+' = :'+ERP_SQL_FIELDPREFIX+StrTrimAll(aQr.FieldByName('ID').AsString)+SQLCRLF;
          end;
        end;
      if( (aQr.FieldByName('ACCS_FLAG_READ').AsInteger<=0) or (aQr.FieldByName('FLAG_DELETE').AsInteger=1) )then
        begin
        i := i + 1;
        aQr.Next;
        continue;
        end;
      if(aFlagMaster and (UpperCase(aMasterFieldName) = UpperCase(aQr.FieldByName('ID').AsString)))then // no controls for master fields !!!
        begin
        i := i + 1;
        aQr.Next;
        continue;
        end;  
      if(Pos('DOMN$BLOB_', lkFieldType)=1)then 
        begin
        if(aPageControlBLOB <> nil)then
          TERPForm_BlobInterface_Create(aDBG.DataSource, aPageControlBLOB, aQr.FieldByName('NAME').AsString, StrTrimAll(aQr.FieldByName('ID').AsString), lkFieldType, not(aQr.FieldByName('ACCS_FLAG_WRITE').AsInteger > 0));
        i := i + 1;
        aQr.Next;
        continue;
        end
      lkCol := ERP_ColumnEh_Create(aDBG, aQr, (aQr.FieldByName('ACCS_FLAG_WRITE').AsInteger = 0));
      i := i + 1;
      aQr.Next;
      end; 
    // inherited columns  
    if( ObjectInheritsFrom(aDBG.Owner, 'TAmunhotepForm') )then
      begin
      lkCol := CreateTColumnEh(aDBG, ERP_SQL_FIELD_IMAGES,'','Картинка', 18, taLeftJustify);
      with lkCol do
        begin
        with ColParams do
          begin
          Clear;
          for i:=0 to ERP_COL_INDEX__COUNT-1 do
            Add('');
          Strings[ERP_COL_INDEX_TABLE]        := aTableName; 
          Strings[ERP_COL_INDEX_FIELD]        := ERP_SQL_FIELD_IMAGES; 
          Strings[ERP_COL_INDEX_VALUEDEFAULT] := '0'; 
          Strings[ERP_COL_INDEX_FIELDTYPE   ] := 'DOMN$INTEGER'; 
          Strings[ERP_COL_INDEX_PERIODICAL]   := '0'; 
          Strings[ERP_COL_INDEX_VALUEEMPTY]   := '0'; 
          Strings[ERP_COL_INDEX_TABLEMAIN]    := aTableName; 
          Strings[ERP_COL_INDEX_MAIN_BASETYPE]:= IntToStr(ERP_OBJECTTYPE_REF);
          end;
        Index             := 0;
        Color             := Amunhotep.MainForm.StyleManager.Colors.Foreground or $A0A0A0;
        Title.Hint        := 'Признак того, что у данного элемента есть привязанные к нему изображения';
        KeyList.Clear ; KeyList.Add ('0'); KeyList.Add ('1');
        PickList.Clear; PickList.Add(' '); PickList.Add('K');
        ShowImageAndText  := false;
        NotInKeyListIndex := 0;
        ImageList         := CreateTImageList(aDBG, 'il'+ERP_SQL_FIELD_IMAGES, [Amunhotep.MainForm.ImageListMain.Count-1, 283]);
        ReadOnly          := true;
        end;
      end;  
    aSQLSelect := 'SELECT '+lkSQLSel+SQLCRLF+'FROM   '+aTableName+' '+ERP_SQL_TABLEPREFIX+'  '+SQLCRLF+lkSQLWhere;
    aSQLRefresh:= 'SELECT FIRST 1 '+lkSQLSel+SQLCRLF+'FROM '+aTableName+' '+ERP_SQL_TABLEPREFIX+' '+SQLCRLF+
                  'WHERE ('+ERP_SQL_TABLEPREFIX+'.ID = ?'+ERP_DATASET_DBKEY+')  '+SQLCRLF;
    aSQLDelete := 'DELETE FROM '+aTableName+' '+ERP_SQL_TABLEPREFIX+' WHERE ('+ERP_SQL_TABLEPREFIX+'.ID = ?'+ERP_DATASET_DBKEY+') ';
    aSQLInsert := 
      'EXECUTE BLOCK ( '+SQLCRLF+
      lkSQLInsUpdVars+
      ')AS '+SQLCRLF+
      '  DECLARE VARIABLE P_ID              DOMN$PSTRING; '+SQLCRLF+
      '  DECLARE VARIABLE P_PERIODICAL_DATE DOMN$DATETIME; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      lkSQLUpdPerNULL+SQLCRLF+
      '  INSERT INTO '+aTableName+' ( '+SQLCRLF+
      '     '+lkSQLInsFlds+' '+SQLCRLF+
      '  )VALUES( '+SQLCRLF+
      '     '+lkSQLInsVals+' '+SQLCRLF+
      '  )RETURNING ID INTO :P_ID; '+SQLCRLF;
    if(StrTrimAll(lkSQLUpdPerFlds) <> '')then
      aSQLInsert := aSQLInsert + '  '+lkSQLUpdPerFlds+') '+SQLCRLF+StrReplaceStr(lkSQLUpdPerVals, ':'+ERP_SQL_FIELDPREFIX+ERP_DATASET_DBKEY, ':P_ID')+') '+SQLCRLF+lkSQLUpdPerMtch+'; '+SQLCRLF;
    aSQLInsert := aSQLInsert +lkSQLUpdPerAdd + 'END ';
//    Dialogs.MessageDlg(aSQLInsert, mtInformation, [mbOk]);
    aSQLUpdate := 
      'EXECUTE BLOCK ( '+SQLCRLF+lkSQLInsUpdVars+')AS '+SQLCRLF+
      '  DECLARE VARIABLE P_PERIODICAL_DATE DOMN$DATETIME; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      lkSQLUpdPerNULL+SQLCRLF+
      '  UPDATE '+aTableName+' '+ERP_SQL_TABLEPREFIX+' SET '+SQLCRLF+
      lkSQLUpd+
      '  WHERE ('+ERP_SQL_TABLEPREFIX+'.ID = :'+ERP_SQL_FIELDPREFIX+ERP_DATASET_DBKEY+'); '+SQLCRLF;
    if(StrTrimAll(lkSQLUpdPerFlds)<>'')then
      aSQLUpdate := aSQLUpdate+'  '+lkSQLUpdPerFlds+') '+SQLCRLF+lkSQLUpdPerVals+') '+SQLCRLF+lkSQLUpdPerMtch+'; '+SQLCRLF;
    aSQLUpdate := aSQLUpdate +lkSQLUpdPerAdd+'END ';
    aDBG.HelpKeyWord := IntToStr(aDBG.FooterRowCount);
    aDBG.Visible := true;
  end;  
