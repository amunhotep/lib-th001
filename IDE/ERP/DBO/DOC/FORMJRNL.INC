{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID.INC}       {$I ../$COMMON/FORMERPGRID.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COLATTRS.INC}           {$I ../DBGRID/COLATTRS.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$I ../DBGRID/GETCELLPARAMS_JRNL.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCOLUMNS.INC}   {$I ../REF/FORMREF_LOADCOLUMNS.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCHILDS.INC}    {$I ../REF/FORMREF_LOADCHILDS.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/ACTIONS.INC}               {$I ./ACTIONS.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/INTF_COMENTS.INC}          {$I ./INTF_COMENTS.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/INTF_DATAVIEW.INC}         {$I ./INTF_DATAVIEW.INC}              {$ENDIF}
  //============================================================================
  function Journal_Create(const aTypeId:string):TForm;    forward;
  function Journal_Execute(const aTypeId:string):Boolean; forward;
  //============================================================================
  function TERPFormGrid_PrintGrid(aOwner :TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  function TERPFormGrid_PrintItem(aOwner :TComponent):Boolean;
  begin
    Result := false; // default handler
    // на переходный период перекроем обработчик печати на старый
    Result := true;
    with TERPForm_ActiveDataSet(aOwner) do
      begin
      if not Active then exit;
      if(not(RecordCount>0))then exit;
      if(FindField('TYPE_ID') <> nil)then
        begin
        SetGlobalVariable(TERPForm_Settings(aOwner).Values[ERP_SETTINGS_BUFFERVAR], FieldByName(ERP_DATASET_DBKEY).AsString);
        call('DB:CONFIG/DOC/'+FieldByName('TYPE_ID').AsString+'/PRINT.PS');
        end;
      end;
  end;
  //============================================================================
  procedure TERPFormGrid_RefreshView(aOwner :TComponent);
  var
    lkSQL     :string;
    lkOrderBy :string;
    lkGoToId  :string;
    i         :Integer;
  begin  
    TERPFormGrid_CloseDataSets(aOwner);
    TERPFormGrid_RefreshingNow := True;
    lkSQL     := TERPFormGrid_SQL(aOwner).Text;
    if((TERPForm_DBGridMain(aOwner).Tag <> 1) and TERPFormGrid_dtpDateFrom(aOwner).Parent.Visible)then
      lkSQL := lkSQL+'  AND ('+ERP_SQL_TABLEPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT,0)+'.FLAG_DELETE <> 1)'+SQLCRLF;
    with TERPForm_DBGridMain(aOwner) do
      begin
      lkOrderBy := '';
      if(Columns.Count > 0)then
        for i:=0 to Columns.Count-1 do
          begin
          if(Columns[i].Title.SortMarker <> smNoneEh)then
            begin
            if(StrTrimAll(lkOrderBy) <> '')then
              lkOrderBy := lkOrderBy + ', ';
            lkOrderBy := lkOrderBy + Columns[i].FieldName;
            if(Columns[i].Title.SortMarker = smUpEh)then
              lkOrderBy := lkOrderBy + ' ASCENDING '
             else  
              lkOrderBy := lkOrderBy + ' DESCENDING ';
            end;
          end;  
      if(StrTrimAll(lkOrderBy) = '')then
        lkOrderBy := ERP_DATASET_DBKEY + ' ASCENDING ';
      end;  
    with TERPForm_DataSetMain(aOwner) do
      begin
      SelectSQL.Text := lkSQL + 'ORDER BY ' + lkOrderBy;
      if TERPFormGrid_dtpDateFrom(aOwner).Parent.Visible then
        begin
        Prepare;
        ParamByName(ERP_SQL_FIELDDATEFROM).AsDate := TERPFormGrid_dtpDateFrom(aOwner).Date;  
        ParamByName(ERP_SQL_FIELDDATETO  ).AsDate := TERPFormGrid_dtpDateTo(aOwner).Date+1;
        end;
      Open;
      TERPFormGrid_RefreshingNow := False;
      if not Active then exit;
      end;  
    with TERPForm_Settings(aOwner) do 
      begin
      lkGoToId := GetGlobalVariable(Values[ERP_SETTINGS_GOTOVAR]);
      if( (Values[ERP_SETTINGS_DATAMEMORY] = '1') and (Values[ERP_SETTINGS_BOOKMARK] = '1') and ( (StrTrimAll(lkGoToId) = '0') or (UpperCase(lkGoToId) = 'NULL') ) )then  
        begin
        TERPForm_DBGridMain(aOwner).DataSource.DataSet.RecNo := StrToInt(Values[ERP_SETTINGS_SAVERECNO]);
        Values[ERP_SETTINGS_SAVERECNO] := '0';
        Values[ERP_SETTINGS_BOOKMARK ] := '0';
        end;
      end;  
  end;
  //============================================================================
  procedure TERPFormGrid_PanelLeft_OnShowHide(aOwner :TComponent);
  begin
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_AfterScroll(DataSet :TDataSet);
  var
    i    :Integer;
    lkPC :TxcPageControlEx;
    lkSB :TScrollBox;
  begin
    lkPC := TxcPageControlEx(DataSet.Owner.Owner.FindComponent(obj_name_erp_pagecontroldetail));
    TERPFormGrid_PCDetail_OnChange(lkPC);
    lkSB := TScrollBox(DataSet.Owner.Owner.FindComponent(obj_name_erp_scrollboxmain));
    if(not(DataSet.RecordCount > 0))then exit;
    if(not lkPC.Visible)then exit;
    if(DataSet.FindField('COLOR_BGR') = nil)then exit;
    if(DataSet.FindField('COLOR_FRG') = nil)then exit;
    lkSB.Color              := DataSet.FieldByName('COLOR_BGR').AsInteger;
    lkSB.Font.Color         := DataSet.FieldByName('COLOR_FRG').AsInteger;
    lkPC.Pages[0].Color     := DataSet.FieldByName('COLOR_BGR').AsInteger; 
    lkPC.Pages[0].Font.Color:= DataSet.FieldByName('COLOR_FRG').AsInteger; 
    lkPC.Pages[4].Color     := DataSet.FieldByName('COLOR_BGR').AsInteger; 
    lkPC.Pages[4].Font.Color:= DataSet.FieldByName('COLOR_FRG').AsInteger; 
    with DataSet.Owner.Owner do
      for i:=0 to ComponentCount-1 do
        if(ObjectInheritsFrom(Components[i], 'TDBGridEh') and (Pos(obj_name_erp_data_dbgdata,Components[i].Name) = 1) )then
          with TDBGridEh(Components[i]) do
            begin
            Color     := DataSet.FieldByName('COLOR_BGR').AsInteger;
            Font.Color:= DataSet.FieldByName('COLOR_FRG').AsInteger;
            end;
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_OnNewRecord(DataSet :TDataSet);
  begin
  end;
  //============================================================================
  function TERPFormGrid_ExportGetCaption(aOwner :TComponent):string;
  begin
    Result := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION];
    if(TERPForm_ActiveDBGrid(aOwner) <> TERPForm_DBGridMain(aOwner))then
      Result := Result + ' / '+TERPForm_ActiveDBGrid(aOwner).Hint;  
  end;
  //============================================================================
  function TERPFormGrid_ExportGetFilter(aOwner :TComponent):string;
  begin
    if(TERPForm_ActiveDBGrid(aOwner) = TERPForm_DBGridMain(aOwner))then
      Result := msg_erp_filter+': '+msg_erp_lbldatefrom+' '+FormatDateTime('dd.mm.yyyy', TERPFormGrid_dtpDateFrom(aOwner).Date)+
          ' '+msg_erp_lbldateto  +' '+FormatDateTime('dd.mm.yyyy', TERPFormGrid_dtpDateTo(aOwner).Date)
     else
      Result := msg_erp_filter+': '+msg_erp_fordocid+' '+TERPForm_DBGridMain(aOwner).DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString;    
  end;
  //============================================================================
  function TERPFormGrid_ExportGetFileName(aOwner :TComponent):string;
  begin
    Result := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION];
  end;                   
  //============================================================================
  procedure TERPFormGrid_LoadDBGridColumnsJrnl(aQr:TxFBQuery; aDBG:TDBGridEh; const aDocListId:string);
  var
    lkSettings     :TStrings;
    lkSB           :TScrollBox;
    lkQrChilds     :TxFBQuery;
    lkQrParents    :TxFBQuery;
    lkDBGChilds    :TDBGridEh;
    lkDBGParents   :TDBGridEh;
    lkEvents       :TxFBEvents;
    lkCol          :TColumnEh; 
    lkColC,lkColP  :TColumnEh; 
    lkLbl          :TLabel;
    lkILLock       :TImageList;
    lkILDelete     :TImageList;
    lkILCommit     :TImageList;
    i,j,c,ii, k,idx:Integer;
    lkLastTop      :Integer; 
    lkCapt, lkHint :string;
    lkTitle        :string;
    lkS, lkS2      :string;
    lkSQLFldName   :string;
    lkSQLFields    :string;
    lkSQLFieldsCh  :string;
    lkSQLTables    :string;
    lkSQLTablesCh  :string;
    lkSQLTablesPa  :string;
    lkSQLWhere     :string;
    lkSQLWhereCh   :string;
    lkTablesList   :TArrayStringUnique;
    lkTablesWhere  :TArrayStringUnique;
    lkCaption      :string;
    lkLastLeft     :Integer;
    lkTop          :Integer;
    lkWidth        :Integer;
    lkDBE          :TCustomDBEditEh;
  begin
    lkSettings := TERPForm_Settings(aDBG.Owner);
    aDBG.Visible := false;
    aDBG.Columns.Clear;
    lkSB         := TScrollBox(aDBG.Owner.FindComponent(obj_name_erp_scrollboxmain));
    lkEvents     := TxFBEvents(aDBG.Owner.FindComponent(obj_name_erp_data_evmain));
    lkQrChilds   := TxFBQuery(aDBG.DataSource.DataSet.FindComponent(obj_name_erp_data_qrchilds));
    lkQrParents  := TxFBQuery(aDBG.DataSource.DataSet.FindComponent(obj_name_erp_data_qrparents));
    lkDBGChilds  := TDBGridEh(aDBG.Owner.FindComponent(obj_name_erp_data_dbgchilds));
    lkDBGParents := TDBGridEh(aDBG.Owner.FindComponent(obj_name_erp_data_dbgparents));
    lkILDelete   := CreateTImageList(aDBG.Owner, 'ilDelete', [300,Amunhotep.MainForm.ImageListMain.Count-1]);
    lkILLock     := CreateTImageList(aDBG.Owner, 'ilLock'  , [224,Amunhotep.MainForm.ImageListMain.Count-1]);
    lkILCommit   := CreateTImageList(aDBG.Owner, 'ilCommit', [298,Amunhotep.MainForm.ImageListMain.Count-1]);
    i := 1; 
    lkLastTop := 0;
    SetLength(lkTablesList , 0);
    lkCapt := ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(lkSettings.Values[ERP_SETTINGS_TABLENAME], lkTablesList) );
    lkSQLTables := lkSettings.Values[ERP_SETTINGS_TABLENAME]+' '+lkCapt;  
    lkSQLFields := //lkCapt+'.ID AS '+ERP_DATASET_DBKEY+' ';
      lkCapt+'.ID AS '+ERP_DATASET_DBKEY+' '+SQLCRLF+
      '      ,IIF((SELECT COALESCE(COUNT(I1.ID),0) FROM TABL$_IMG I1 WHERE (I1.OBJ_ID = '''+lkSettings.Values[ERP_SETTINGS_TABLENAME]+''') AND (I1.REC_ID = '+lkCapt+'.ID))>0, 1, 0) AS '+ERP_SQL_FIELD_IMAGES+' '+SQLCRLF;
    lkSQLWhere  := 'WHERE ('+lkCapt+'.DATE_COMMIT BETWEEN  ?'+ERP_SQL_FIELDDATEFROM+' AND  ?'+ERP_SQL_FIELDDATETO+') '+SQLCRLF+
                   '  AND ('''+lkSettings.Values[ERP_SETTINGS_TYPESLIST]+''' CONTAINING ''~''||'+lkCapt+'.TYPE_ID||''~'') '+SQLCRLF;
    if(StrTrimAll(aDocListId) <> '')then
      lkSQLWhere:= 'WHERE ('+lkCapt+'.ID = '+ERP_SQL_RELATIONPREFIX+'.J_CHILD_ID) '+SQLCRLF;
    lkSQLTablesCh := 
      '(WITH RECURSIVE DOCTREE AS( '+SQLCRLF+
      '                SELECT DOCTREE1.J_ID, DOCTREE1.J_CHILD_ID, CAST(''|--+'' AS DOMN$PSTRING_8192) AS INDENT '+SQLCRLF+
      '                FROM   (SELECT JC.J_ID, JC.J_CHILD_ID FROM TABL$J_CHILDS JC WHERE  (JC.J_ID = ?'+ERP_DATASET_DBKEY+')ORDER BY JC.J_CHILD_ID ASCENDING ) DOCTREE1 '+SQLCRLF+
      '                UNION ALL '+SQLCRLF+
      '                SELECT DOCTREE2.J_ID, DOCTREE2.J_CHILD_ID, CAST(''   ''||DOCTREE3.INDENT AS DOMN$PSTRING_8192) '+SQLCRLF+
      '                FROM   TABL$J_CHILDS DOCTREE2, DOCTREE DOCTREE3 WHERE (DOCTREE2.J_ID = DOCTREE3.J_CHILD_ID) '+SQLCRLF+
      '            )SELECT T1.J_CHILD_ID, T1.INDENT FROM DOCTREE T1 ) AS '+ERP_SQL_RELATIONPREFIX+', '+lkSettings.Values[ERP_SETTINGS_TABLENAME]+' '+lkCapt;  
    lkSQLTablesPa := 
      '(WITH RECURSIVE DOCTREE AS( '+SQLCRLF+
      '                SELECT DOCTREE1.J_ID, DOCTREE1.J_CHILD_ID, CAST(''+--|'' AS DOMN$PSTRING_8192) AS INDENT '+SQLCRLF+
      '                FROM   (SELECT JC.J_ID, JC.J_CHILD_ID FROM TABL$J_CHILDS JC WHERE (JC.J_CHILD_ID = ?'+ERP_DATASET_DBKEY+')ORDER BY JC.J_ID DESCENDING ) DOCTREE1'+SQLCRLF+
      '                UNION ALL '+SQLCRLF+
      '                SELECT DOCTREE2.J_ID, DOCTREE2.J_CHILD_ID, CAST(''   ''||DOCTREE3.INDENT AS DOMN$PSTRING_8192) '+SQLCRLF+
      '                FROM   TABL$J_CHILDS DOCTREE2, DOCTREE DOCTREE3 WHERE (DOCTREE2.J_CHILD_ID = DOCTREE3.J_ID) '+SQLCRLF+
      '            )SELECT T1.J_ID AS J_CHILD_ID, T1.INDENT FROM DOCTREE T1 ) AS '+ERP_SQL_RELATIONPREFIX+', '+lkSettings.Values[ERP_SETTINGS_TABLENAME]+' '+lkCapt;  
    lkSQLFieldsCh := 'CAST('+ERP_SQL_RELATIONPREFIX+'.'+ERP_SQL_FIELDINDENT+' AS DOMN$PSTRING_8192) AS '+ERP_SQL_FIELDINDENT+', '+lkCapt+'.ID AS '+ERP_DATASET_DBKEY;
    lkSQLWhereCh  := 'WHERE ('+lkCapt+'.ID = '+ERP_SQL_RELATIONPREFIX+'.J_CHILD_ID)';
    C := 0;
    j := 0;
    lkLastLeft  := TERPForm_DefaultControlIndent;
    aQr.First;
    while not aQr.EOF do
      begin
      lkTitle := aQr.FieldByName('NAME').AsString;
      lkCapt  := StrReplaceStr(lkTitle, '|',' / '); 
      if TERPFormGrid_DataSetFilter_Exists(aQr.FieldByName('ID').AsString) then
        lkSQLWhere := lkSQLWhere +'  AND ('+TERPFormGrid_DataSetFilter[TERPFormGrid_DataSetFilter_Index(aQr.FieldByName('ID').AsString)].FilterStr+') '+SQLCRLF; 
      if( (StrTrimAll(aQr.FieldByName('ID').AsString) = StrTrimAll(aQr.FieldByName('REF_KEYFIELD').AsString)) and 
          (StrTrimAll(aQr.FieldByName('REF_TABLE').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME]) )then
        begin
        idx := IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList);
        SetLength(lkTablesWhere, Length(lkTablesList) );
        lkTablesWhere[idx] := 'ON ('+ERP_SQL_TABLEPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT,idx)+'.'+aQr.FieldByName('ID').AsString+' = '+
          ERP_SQL_TABLEPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT,IndexInArrayStringUnique(lkSettings.Values[ERP_SETTINGS_TABLENAME], lkTablesList))+'.ID)';
        end
       else 
        begin
        if(aQr.FieldByName('CALC_SQL').AsString <> '')then
          begin
          lkS := aQr.FieldByName('CALC_SQL').AsString;
          if(Pos('?', lkS) > 0)then
            lkS := StrReplaceStr(lkS, '?', ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.');  
          lkSQLFields := lkSQLFields + SQLCRLF + '      ,('+lkS+') AS '+aQr.FieldByName('ID').AsString;
          if(StrTrimAll(aQr.FieldByName('TB_ID').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME])then
            lkSQLFieldsCh := lkSQLFieldsCh + SQLCRLF + '      ,('+lkS+') AS '+aQr.FieldByName('ID').AsString;
          end
         else
          begin 
          lkSQLFldName := ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.'+aQr.FieldByName('ID').AsString;
          lkSQLFields  := lkSQLFields + SQLCRLF + '      ,'+ lkSQLFldName;
          if(StrTrimAll(aQr.FieldByName('TB_ID').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME])then
            lkSQLFieldsCh:= lkSQLFieldsCh +SQLCRLF+'      ,'+lkSQLFldName;
          if(aQr.FieldByName('REF_TABLE').AsString <> '')then
            begin
            C := C + 1;
            lkS := aQr.FieldByName('REF_TABLE').AsString;
            if(Pos('?', lkS) > 0)then 
              lkS := StrReplaceStr(lkS, '?', ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.');
            lkS2 := '(SELECT FIRST 1 '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, C)+'.'+aQr.FieldByName('REF_FIELD').AsString+
              ' FROM '+lkS+' '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, C);
            if(aQr.FieldByName('REF_KEYFIELD').AsString <> '')then  
              lkS2 := lkS2 +' WHERE ('+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, C)+'.'+aQr.FieldByName('REF_KEYFIELD').AsString+' = '+lkSQLFldName+')';
            lkS2 := lkS2 +') AS '+aQr.FieldByName('ID').AsString+ERP_SQL_FIELDSUFFIX;
            lkSQLFields := lkSQLFields + SQLCRLF + '      ,' +lkS2; 
            if(StrTrimAll(aQr.FieldByName('TB_ID').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME])then
              lkSQLFieldsCh := lkSQLFieldsCh + SQLCRLF + '      ,' + lkS2;
            end;
          end;
        if(aQr.FieldByName('FLAG_DELETE').AsInteger = 0)then
          begin
          if(Pos('DOMN$BLOB_', StrTrimAll(aQr.FieldByName('FIELD_TYPE').AsString)) = 1)then
            begin
            lkSQLFldName := ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.'+aQr.FieldByName('ID').AsString;
            lkSQLFields  := lkSQLFields + SQLCRLF + '      ,'+ lkSQLFldName;
            TERPForm_BlobInterface_Create(aDBG.DataSource, TxcPageControlEx(aDBG.Owner.FindComponent(obj_name_erp_pagecontroldata)), aQr.FieldByName('NAME').AsString, aQr.FieldByName('ID').AsString, aQr.FieldByName('FIELD_TYPE').AsString, true);
            end
           else
            begin 
            lkHint    := aQr.FieldByName('HINT').AsString; if(StrTrimAll(lkHint) = '')then lkHint := StrReplaceStr(lkTitle, '|', #13#10);
            if(aQr.FieldByName('EDT_TOP').AsInteger >= 0)then
              begin
              lkCaption := aQr.FieldByName('NAME').AsString;
              if(Pos('|', lkCaption) > 0)then
                Delete(lkCaption, 1, Pos('|', lkCaption));
              lkCaption := StrReplaceStr(lkCaption, '|', '/');
              lkWidth    := Trunc(aQr.FieldByName('WIDTH').AsInteger * TERPForm_DefaultControlWidthMul);
              lkTop      := aQr.FieldByName('EDT_TOP').AsInteger * 2 * (TERPForm_DefaultControlHeight - TERPForm_DefaultControlIndent);
              lkLastLeft := TERPForm_DefaultControlIndent;
              for k:=0 to lkSB.ControlCount-1 do
                if(lkSB.Controls[k].Top = lkTop)then
                  lkLastLeft := MaxInteger(lkLastLeft, (lkSB.Controls[k].Left + lkSB.Controls[k].Width + TERPForm_DefaultControlIndent) ); 
              lkDBE := ERP_DBEditEh_Create(lkSB, aDBG.DataSource, aQr, lkCaption, lkLastLeft, lkTop, TERPForm_DefaultControlHeight, lkWidth, true);
              lkLastLeft := lkLastLeft + lkWidth + TERPForm_DefaultControlIndent;   
              end;
            lkCol := CreateTColumnEh2(aDBG, aQr.FieldByName('ID').AsString, aQr.FieldByName('FORMAT').AsString,
                       lkTitle, lkHint, aQr.FieldByName('WIDTH').AsInteger, aDBG.Columns.Count, aQr.FieldByName('ALIGNMENT').AsInteger, aDBG.Color, 
                       aQr.FieldByName('KEY_LIST').AsString, aQr.FieldByName('PICK_LIST').AsString, []);
            with lkCol do
              begin           
              Title.Orientation := IntToTTextOrientationEh(aQr.FieldByName('ORIENTATION').AsInteger);
              with ColParams do
                begin
                Clear;
                for i:=0 to ERP_COL_INDEX__COUNT-1 do
                  Add(aQr.FieldByName(ERP_COL_INDEX__FIELDS(i)).AsString);
                end;
              if(Pos('DOMN$BOOLEAN', StrTrimAll(aQr.FieldByName('FIELD_TYPE').AsString)) <> 1)then
                CheckBoxes := false;
              if(aQr.FieldByName('ID').AsString = 'FLAG_DELETE')then
                begin
                AutoDropDown := false;
                CheckBoxes   := false;
                ImageList    := lkILDelete;
                end;
              if(aQr.FieldByName('ID').AsString = 'FLAG_COMMIT')then  
                begin
                AutoDropDown := false;
                CheckBoxes   := false;
                ImageList    := lkILCommit;
                end;
              if(aQr.FieldByName('ID').AsString = 'FLAG_LOCK')then  
                begin
                AutoDropDown := false;
                CheckBoxes   := false;
                ImageList    := lkILLock;
                end;
              if(aQr.FieldByName('REF_TABLE').AsString <> '')then
                begin
                FieldName := FieldName + ERP_SQL_FIELDSUFFIX;
                end;
              end;
            if(aQr.FieldByName('FLAG_FOOTER').AsInteger <> 0)then
              begin
              aDBG.HelpKeyWord := IntToStr(MaxInteger(StrToInt(aDBG.HelpKeyWord), aQr.FieldByName('FOOTER_COUNT').AsInteger));
              ERP_DBGridEh_Column_FootersLoad(lkCol, aQr.Transaction, aQr.FieldByName('TB_ID').AsString, aQr.FieldByName('ID').AsString);
              end;           
            if(StrTrimAll(aQr.FieldByName('TB_ID').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME])then
              begin
              lkColC := CloneTColumnEh(lkCol, lkDBGChilds );
              lkColP := CloneTColumnEh(lkCol, lkDBGParents);
              end;
            end;
          end;
        end;
      j := j + 1;  
      aQr.Next;
      end;
    // inherited columns  
    lkCol := CreateTColumnEh(aDBG, ERP_SQL_FIELD_IMAGES,'',' артинка', 18, taLeftJustify);
    with lkCol do
      begin
      Index             := 0;
      Color             := Amunhotep.MainForm.StyleManager.Colors.Foreground or $A0A0A0;
      Title.Hint        := 'ѕризнак того, что у данного элемента есть прив€занные к нему изображени€';
      KeyList.Clear ; KeyList.Add ('0'); KeyList.Add ('1');
      PickList.Clear; PickList.Add(' '); PickList.Add('K');
      ShowImageAndText  := false;
      NotInKeyListIndex := 0;
      ImageList         := CreateTImageList(aDBG, 'il'+ERP_SQL_FIELD_IMAGES, [Amunhotep.MainForm.ImageListMain.Count-1, 283]);
      ReadOnly          := true;
      end;
    lkDBGChilds.HelpKeyWord  := aDBG.HelpKeyWord;  
    lkDBGParents.HelpKeyWord := aDBG.HelpKeyWord;  
    if(StrTrimAll(aDocListId) <> '')then
      begin
      lkCol := CreateTColumnEh(aDBG,ERP_SQL_FIELDINDENT,'','',80,taLeftJustify );
      with lkCol do 
        begin
        Index     := 0;
        Font.Name := 'Courier New';
        Font.Size := 8;
        Font.Style:= [fsBold];
        Tag       := 666;
        end;
      end;
    lkColC := CreateTColumnEh(lkDBGChilds ,ERP_SQL_FIELDINDENT,'','',80,taLeftJustify );
    with lkColC do 
      begin
      Index     := 0;
      Font.Name := 'Courier New';
      Font.Size := 8;
      Font.Style:= [fsBold];
      Tag       := 666;
      end;
    lkColP := CreateTColumnEh(lkDBGParents,ERP_SQL_FIELDINDENT,'','',80,taLeftJustify );
    with lkColP do 
      begin
      Index     := 0;
      Font.Name := 'Courier New';
      Font.Size := 8;
      Font.Style:= [fsBold];
      Tag       := 666;
      end;
    for i:=1 to Length(lkTablesList)-1 do
      begin
      lkSQLTables := lkSQLTables+' '+SQLCRLF+
       '       LEFT OUTER JOIN '+lkTablesList[i]+' '+ERP_SQL_TABLEPREFIX+FormatFloat('0000', i)+' '+lkTablesWhere[i];
      if(i < 14)then
        lkEvents.Events.Add(lkTablesList[i]);  
      end;
    if(StrTrimAll(aDocListId) <> '')then
      TERPFormGrid_SQL(aDBG.Owner).Text := 
      'SELECT '+lkSQLFields+', '+ERP_SQL_RELATIONPREFIX+'.INDENT '+SQLCRLF+'FROM '+
      '(WITH RECURSIVE DOCTREE AS( '+SQLCRLF+
      '                SELECT FIRST 1 '+aDocListId+' AS J_ID, '+aDocListId+' AS J_CHILD_ID, CAST(''|--+'' AS DOMN$PSTRING_8192) AS INDENT '+SQLCRLF+
      '                FROM RDB$DATABASE '+SQLCRLF+
      '                UNION ALL '+SQLCRLF+
      '                SELECT DOCTREE2.J_ID, DOCTREE2.J_CHILD_ID, CAST(''   ''||DOCTREE3.INDENT AS DOMN$PSTRING_8192) '+SQLCRLF+
      '                FROM   TABL$J_CHILDS DOCTREE2, DOCTREE DOCTREE3 WHERE (DOCTREE2.J_ID = DOCTREE3.J_CHILD_ID) '+SQLCRLF+
      '            )SELECT T1.J_CHILD_ID, T1.INDENT FROM DOCTREE T1 ) AS '+ERP_SQL_RELATIONPREFIX+', '+lkSQLTables  +' '+SQLCRLF+lkSQLWhere
     else
      TERPFormGrid_SQL(aDBG.Owner).Text := 'SELECT '+lkSQLFields  +' '+SQLCRLF+'FROM   '+lkSQLTables  +' '+SQLCRLF+lkSQLWhere;
    lkQrChilds.SQL.Text  := 'SELECT '+lkSQLFieldsCh+' '+SQLCRLF+'FROM   '+lkSQLTablesCh+' '+SQLCRLF+lkSQLWhereCh;
    lkQrParents.SQL.Text := 'SELECT '+lkSQLFieldsCh+' '+SQLCRLF+'FROM   '+lkSQLTablesPa+' '+SQLCRLF+lkSQLWhereCh;
    aDBG.Visible := true;
  end;
  //============================================================================
  function TERPFormGridJrnl_Create(const aTypeId:string;const aModalForm:Boolean):TForm;
  var
    lkVar, lkStr, lkS :string;
    lkJ_GOTO_ID    :string;
    lkFlagHistory  :Boolean;
    lkSettings     :TStrings;
    lkCreateParams :TFormERPParams;
    lkTr           :TxFBTransaction;
    lkQr           :TxFBQuery;
    lkDS           :TDataSource;
    lkAct          :TCustomAction;
    lkMainMenu     :TMainMenu;
    lkMIMenuMain   :TMenuItem;
    lkMIView       :TMenuItem;
    lkMIObj        :TMenuItem;
    lkMIItem       :TMenuItem;
    lkMI           :TMenuItem;
    lkPanelClient  :TxcPanel;
    lkPC           :TxcPageControlEx;
    lkPCData       :TxcPageControlEx;
    lkTS           :TxcTabSheet;
    lkTSData       :TxcTabSheet;
    lkToolBar      :TxcGradientPanelVista;
    lkToolBarItem  :TxcGradientPanelVista;
    lkEvents       :TxFBEvents;
    lkSB           :TScrollBox;
    lkDBGChilds    :TDBGridEh;
    lkDBGParents   :TDBGridEh;
    lkQrChilds     :TxFBQuery;
    lkQrParents    :TxFBQuery;
  begin
    if(UpperCase(StrTrimAll(GetGlobalVariable('DATABASE_USER'))) = 'MANAGER')then
      TERPFormGrid_DataSetFilter_Add('FIRM_ID', '(FIRM_ID = 0)');
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQr, lkDS)  
    lkCreateParams := [ erpDatePeriod, erpDatePeriodAutoRefresh, erpGrid, erpGridGroup, erpEvents, erpGridNavigation, erpDetail, erpDetailExternal
                       ,erpGridEdit, erpGridEditMark, erpGridEditCommit, erpGridEditLock, erpGridEditDel];
    if not aModalForm then
      lkCreateParams := lkCreateParams + [erpGridEditEdt, erpGridEditGotoJrnl];  
    lkQr.SQL.Text := StringsLoadFromFile(ERP_FILENAME_SQL_GETTABLE_JRNL);
    lkQr.Prepare;
    lkQr.ParamByName('Q_TYPE_ID').AsString := aTypeId;
    try  
      lkQr.Open;
    except
    end;
    if not(lkQr.Active)then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpsql+' "'+aTypeId+'" !',mtWarning,[mbOk]);
      exit;
      end;  
    lkQr.First;
    if(lkQr.FieldByName('TYPE_EXISTS').AsInteger <> 1)then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_defined+' "'+aTypeId+'"', mtError, [mbOk]);
      exit;
      end;
    if(lkQr.FieldByName('TB_REL_EXISTS').AsInteger <> 1)then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_exists+' "'+aTypeId+'"', mtError, [mbOk]);
      exit;
      end;
    if ERP_ObjectExtension_FileExists(aTypeId, ERP_OBJECTTYPE_JRNL)then  
      lkCreateParams := lkCreateParams + [erpDetail, erpDetailExtensions];
    if((not aModalForm) {and (lkQr.FieldByName('TB_ACCS_PRN_CNT').AsInteger > 0) })then
      lkCreateParams := lkCreateParams + [erpGridExport, erpGridPrint, erpGridPrintItem];
//    lkCreateParams := lkCreateParams - [erpGridGroup];  
    Result := TERPFormGrid_Create(lkQr.FieldByName('TYPE_NAME').AsString, ERP_ObjectCaption(ERP_OBJECTTYPE_JRNL), ERP_ObjectIcon(ERP_OBJECTTYPE_JRNL), ERP_ObjectBitmap(ERP_OBJECTTYPE_JRNL),aModalForm,lkCreateParams);
    with Result do
      begin
      HelpKeyWord := aTypeId;
      if aModalForm then
        TForm_Position_Load(Result, 
          PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_JRNL,StrToInt(aTypeId),'',GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))), 
          MaxInteger(Trunc(Screen.Height * 4 / 5),600), MaxInteger(Trunc(Screen.Width * 4/5),800));
      end;  
    with TxFBTransaction(Result.FindComponent(obj_name_erp_data_trmain)).Params do
      begin
      Clear;
      Add('isc_tpb_read_committed');
      Add('isc_tpb_read');
      Add('isc_tpb_rec_version');
      Add('isc_tpb_nowait');
      end;  
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_JRNL);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_JRNL);
      end;  
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_BUFFERVAR   ] := lkQr.FieldByName('BUFFER_VAR_MAIN').AsString;
      Values[ERP_SETTINGS_GOTOVAR     ] := StrTrimAll(lkQr.FieldByName('BUFFER_VAR_MAIN').AsString+ERP_SETTINGS_GOTOVAR);
      Values[ERP_SETTINGS_TABLENAME   ] := lkQr.FieldByName('TB_ID_MAIN').AsString;
      Values[ERP_SETTINGS_TABLECAPTION] := lkQr.FieldByName('TYPE_NAME').AsString;
      Values[ERP_SETTINGS_TYPESLIST   ] := lkQr.FieldByName('TYPES_LIST').AsString;
      Values[ERP_SETTINGS_BASETYPE    ] := IntToStr(ERP_OBJECTTYPE_DOC);
      Values[ERP_SETTINGS_DOCTYPE     ] := aTypeId;
      Values[ERP_SETTINGS_TEMPFILENAME] := ERP_ObjectTempFileName(ERP_OBJECTTYPE_JRNL,StrToInt(aTypeId),'',GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));
      WriteLn(Values[ERP_SETTINGS_TEMPFILENAME]);
      end;
    // users recent menu
    if aModalForm then
      begin
//      ExecSQL(FBDataBase, 'EXECUTE PROCEDURE PROC$_USERS_LOG_INS(1000020, '''+lkQr.FieldByName('TB_ID_MAIN').AsString+''', '''+aTypeId+''', NULL, NULL);');  
      end
     else
      begin 
      ExecSQL(FBDataBase, 
        'EXECUTE BLOCK AS DECLARE VARIABLE P DOMN$INTEGER; '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  IF(NOT(EXISTS(SELECT R.RDB$RELATION_ID FROM RDB$RELATIONS R WHERE(TRIM(R.RDB$RELATION_NAME)=''TABL$_USERS_RCNT''))))THEN EXIT; '+SQLCRLF+
        '  EXECUTE STATEMENT ''UPDATE OR INSERT INTO TABL$_USERS_RCNT(NAME, USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME)VALUES('''''+Result.Caption+''''', '''''+
         GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''''', 0, '''''+aTypeId+''''', '''''+ScriptName+''''')MATCHING(USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME);''; '+SQLCRLF+    
        '  /* SELECT MAX(P.ID) FROM PROC$_USERS_LOG_INS(1000018, '''+lkQr.FieldByName('TB_ID_MAIN').AsString+''', '''+aTypeId+''', NULL, NULL) P INTO :P; */ '+SQLCRLF+
        'END');
      end;      
    lkFlagHistory := false;
    lkJ_GOTO_ID   := '';  
    lkVar := lkSettings.Values[ERP_SETTINGS_GOTOVAR];
    lkJ_GOTO_ID := UpperCase(StrTrimAll(GetGlobalVariable(lkVar)));
    if( (lkJ_GOTO_ID <> 'NULL') and (lkJ_GOTO_ID <> '0'))then
      begin
      lkStr := FormatDateTime('dd.mm.yyyy', TERPFormGrid_dtpDateFrom(Result).Date)+' 00:00:00';
      if GetField(FBDataBase, lkQr.FieldByName('TB_ID_MAIN').AsString, 'DATE_COMMIT', 'ID = '+lkJ_GOTO_ID, lkStr)then
        begin
        lkStr := StrReplaceStr(lkStr,'/','.');
        lkStr := StrReplaceStr(lkStr,'\','.');
        TERPFormGrid_dtpDateFrom(Result).Date := StrToDateTime(lkStr);
        TERPFormGrid_dtpDateTo  (Result).Date := StrToDateTime(lkStr);
        end;
      lkStr := StrCiphersOnlyInt(GetGlobalVariable(ERP_SETTINGS_FLAGHISTORY));
      SetGlobalVariable(ERP_SETTINGS_FLAGHISTORY, '0');
      lkFlagHistory := (lkStr = '1');
      if lkFlagHistory then
        begin
        TERPFormGrid_dtpDateFrom(Result).Enabled := not lkFlagHistory;
        TERPFormGrid_dtpDateTo  (Result).Enabled := not lkFlagHistory;
        TERPFormGrid_dtpDateFrom(Result).Parent.Visible := not lkFlagHistory;
        GetField(FBDataBase, lkQr.FieldByName('TB_ID_MAIN').AsString, 'TYPE_ID', 'ID = '+lkJ_GOTO_ID, lkStr);
        GetField(FBDataBase, 'TABL$_TB_TYPES', 'NAME2', 'ID = '+lkStr, lkS);
        GetField(FBDataBase, lkQr.FieldByName('TB_ID_MAIN').AsString, 'DOCNUMBERSTR', 'ID = '+lkJ_GOTO_ID, lkStr);
        TERPForm_SetCaption(Result, msg_erp_tsdocchilds+' '+lkS +' '+lkStr);
        end; 
      end;
    if not lkFlagHistory then lkJ_GOTO_ID := '';  
    lkMainMenu   := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu)); 
    lkMIMenuMain := TMenuItem(lkMainMenu.Items.FindComponent(obj_name_erp_mimainmenu));//lkMIMenuMain.Caption := ERP_ObjectCaption(2);
    lkMIItem     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainitem));lkMIItem.ImageIndex := 37; lkMIItem.Caption := ERP_ObjectCaption(ERP_OBJECTTYPE_DOC);
    lkMIObj      := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainobj)); lkMIObj.ImageIndex  := 42; lkMIObj.Caption  := ERP_ObjectCaption(ERP_OBJECTTYPE_JRNL);
    lkMIView     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainview));
    if not aModalForm then
      begin
      lkAct      := TCustomAction(Result.FindComponent(obj_name_erp_actprintitem));lkAct.ImageIndex := 235;
      lkAct      := TCustomAction(Result.FindComponent(obj_name_erp_actprintgrid));lkAct.ImageIndex := 236;
      end;
    lkPanelClient:= TxcPanel(Result.FindComponent(obj_name_erp_panelclient));
    lkToolBar    := TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbar));
    lkToolBarItem:= TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbar_item));
    lkEvents     := TxFBEvents(Result.FindComponent(obj_name_erp_data_evmain));
    lkEvents.Events.Add(lkQr.FieldByName('TB_ID_MAIN').AsString);
    lkQrChilds := TxFBQuery.Create(TERPForm_DBGridMain(Result).DataSource.DataSet);
    with lkQrChilds do
      begin
      Name        := obj_name_erp_data_qrchilds;
      Transaction := TERPForm_TransactionMain(Result);
      DataSource  := TERPForm_DBGridMain(Result).DataSource;
      SQL.Text    := '';
      end;
    lkQrParents := TxFBQuery.Create(TERPForm_DBGridMain(Result).DataSource.DataSet);
    with lkQrParents do
      begin
      Name        := obj_name_erp_data_qrparents;
      Transaction := TERPForm_TransactionMain(Result);
      DataSource  := TERPForm_DBGridMain(Result).DataSource;
      SQL.Text    := '';
      end;
    with TERPForm_DBGridMain(Result) do
      begin
      Options         := Options + [{dgRowSelect,} dgAlwaysShowSelection] - [dgMultiSelect];
      OptionsEh       := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghAutoSortMarking, dghMultiSortMarking, 
                                      {$IFNDEF AMUNHOTEP4832}dghIncSearch,{$ENDIF} dghPreferIncSearch, dghRowHighlight, 
                                      dghColumnResize, dghColumnMove,dghExtendVertLines];

      ReadOnly        := true;
      if lkFlagHistory then
        Tag           := 1;
      OnGetCellParams := @ERP_DBGridEh_OnGetCellParams_Jrnl;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkPC := TxcPageControlEx(Result.FindComponent(obj_name_erp_pagecontroldetail));
    lkTS := CreateTxcTabSheet(lkPC,'tsDocFields'  ,msg_erp_tsdocfields  , 37,Amunhotep.MainForm.StyleManager.Colors.Window    ); lkSB         := CreateTScrollBox(Result,lkTS,obj_name_erp_scrollboxmain,0,0,200,200,alClient);
    lkTS := CreateTxcTabSheet(lkPC,'tsDocComents' ,msg_erp_tsdoccoments ,420,Amunhotep.MainForm.StyleManager.Colors.Background); DocComentsIntf_Create(Result, lkTS, TERPForm_DBGridMain(Result).DataSource); 
    lkTS := CreateTxcTabSheet(lkPC,'tsDocChilds'  ,msg_erp_tsdocchilds  ,466,Amunhotep.MainForm.StyleManager.Colors.Foreground); lkDBGChilds  := CreateTDBGridEh(Result,lkTS,nil,obj_name_erp_data_dbgchilds ,0,0,1,1,alClient);
    lkTS := CreateTxcTabSheet(lkPC,'tsDocParents' ,msg_erp_tsdocparents ,466,Amunhotep.MainForm.StyleManager.Colors.Foreground); lkDBGParents := CreateTDBGridEh(Result,lkTS,nil,obj_name_erp_data_dbgparents,0,0,1,1,alClient);
    lkTSData := CreateTxcTabSheet(lkPC,'tsDocData',msg_erp_tsdocdata    ,491,Amunhotep.MainForm.StyleManager.Colors.Window    ); lkPCData     := CreateTxcPageControlEx(Result,lkTSData,obj_name_erp_pagecontroldata,0,0,200,240,alClient);
    with lkSB do
      begin
      Font.Style := Font.Style + [fsBold];
      end;
    with lkDBGChilds do
      begin
      DataSource := TDataSource.Create(lkQrChilds);
      with DataSource do
        begin
        Name    := 'DataSource'+obj_name_erp_data_qrchilds;
        DataSet := lkQrChilds;
        end;
      HelpKeyWord      := '0';  
      Hint             := msg_erp_tsdocchilds;
      IndicatorOptions := [gioShowRowIndicatorEh, gioShowRowselCheckboxesEh];  
      Options          := TERPForm_DBGridMain(Result).Options + [dgRowSelect, dgMultiSelect, dgAlwaysShowSelection];
      OptionsEh        := [dghFixed3D, dghFrozen3D, dghFooter3D, dghHighlightFocus, dghIncSearch, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      OnGetCellParams  := @ERP_DBGridEh_OnGetCellParams_Jrnl;
      VTitleMargin     := 4;
      end;                           
    with lkDBGParents do
      begin
      DataSource := TDataSource.Create(lkQrParents);
      with DataSource do
        begin
        Name    := 'DataSource'+obj_name_erp_data_qrparents;
        DataSet := lkQrParents;
        end;
      HelpKeyWord      := '0';  
      Hint             := msg_erp_tsdocparents;  
      IndicatorOptions := [gioShowRowIndicatorEh, gioShowRowselCheckboxesEh];  
      Options          := TERPForm_DBGridMain(Result).Options + [dgRowSelect, dgMultiSelect, dgAlwaysShowSelection];
      OptionsEh        := [dghFixed3D, dghFrozen3D, dghFooter3D, dghHighlightFocus, dghIncSearch, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      OnGetCellParams  := @ERP_DBGridEh_OnGetCellParams_Jrnl;
      VTitleMargin     := 4;
      end;                           
    lkQr.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETCOLUMNS_JRNL));
    lkQr.Prepare; 
    lkQr.ParamByName('PQ_TYPE_ID' ).AsString := aTypeId;
    lkQr.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
    lkQr.Open;
    if not(lkQr.Active)then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpsql+' "'+aTypeId+'" !',mtWarning,[mbOk]);
      exit;
      end;  
    TERPFormGrid_LoadDBGridColumnsJrnl(lkQr, TERPForm_DBGridMain(Result), lkJ_GOTO_ID);  
    TERPForm_GridSettingsLoad(TERPForm_DBGridMain(Result), lkSettings.Values[ERP_SETTINGS_TEMPFILENAME]);
    if lkTr.InTransaction then
      lkTr.Commit;
    lkQr.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETTABLE_DOC));
    lkQr.Prepare; 
    lkQr.ParamByName('PQ_TYPE_ID' ).AsString := aTypeId;
    lkQr.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
    lkQr.Open;
    if not(lkQr.Active)then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpsql+' "'+aTypeId+'" !',mtWarning,[mbOk]);
      exit;
      end;  
    DocDataIntf_Create(Result, lkTSData, lkSettings.Values[ERP_SETTINGS_TABLENAME], TERPForm_TransactionMain(Result), TERPForm_DBGridMain(Result).DataSource, lkQr);  
    if lkTr.InTransaction then
      lkTr.Commit;
    lkQr.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_TABLECHILD_REF));
    lkQr.Prepare;
    lkQr.ParamByName('PQ_TB_ID'   ).AsString := lkSettings.Values[ERP_SETTINGS_TABLENAME];
    lkQr.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
    try lkQr.Open; except end;
    if lkQr.Active then TERPFormItem_LoadChilds(lkQr, Result, TERPForm_DBGridMain(Result).DataSource, false);
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actdocgotoday  ,msg_erp_actdocgotoday  ,msg_erp_actdocgotoday_hint,'',0,360,@TERPFormGridJrnl_actDocGotoDay_OnExecute,nil,lkToolBarItem,lkMIItem);

    lkToolBarItem.Width := TWinControl_AutoWidth(lkToolBarItem)+2; lkToolBarItem.Visible:= (lkToolBarItem.ControlCount > 0);  

    lkMI := CreateTMenuItemIns(lkMIView,obj_name_erp_mimainview+lkDBGParents.Name,msg_erp_tsdocparents,'','',150,0,0);
    lkToolBar := CreateTxcGradientPanelVistaToolBar(lkDBGParents,lkDBGParents.Parent,lkDBGParents.Name+'_'+obj_name_erp_toolbar,'',alTop,0,0,TERPForm_DefaultToolButtonWidth+2,200,xbsRaized);
    ERP_DBGridEh_EdtActions_Create(lkDBGParents, lkCreateParams, lkToolBar, lkMI);
    ERP_DBGridEh_StdActions_Create(lkDBGParents, [erpGrid,erpGridNavigation,erpGridExport], lkToolBar, lkMI);                         
    lkMI := CreateTMenuItemIns(lkMIView,obj_name_erp_mimainview+lkDBGChilds.Name,msg_erp_tsdocchilds,'','',150,0,0);
    lkToolBar := CreateTxcGradientPanelVistaToolBar(lkDBGChilds ,lkDBGChilds.Parent ,lkDBGChilds.Name+'_'+obj_name_erp_toolbar ,'',alTop,0,0,TERPForm_DefaultToolButtonWidth+2,200,xbsRaized);
    ERP_DBGridEh_EdtActions_Create(lkDBGChilds , lkCreateParams, lkToolBar, lkMI);
    ERP_DBGridEh_StdActions_Create(lkDBGChilds , [erpGrid,erpGridNavigation,erpGridExport], lkToolBar, lkMI);
    with TERPForm_DBGridMain(Result) do
      begin
      lkDBGChilds.OnDblClick  := @ERP_DBGridEh_DBGrid_OnDblClickEdit;
      lkDBGParents.OnDblClick := @ERP_DBGridEh_DBGrid_OnDblClickEdit;
      end;                         
    TxcPageControlEx_ActivateDefaultPage(lkPC    );
    TxcPageControlEx_ActivateDefaultPage(lkPCData);
    Result.ActiveControl := TERPForm_DBGridMain(Result); 
    TERPFormGrid_RefreshView(Result);
    if not aModalForm then
      if not lkEvents.Registered then
        lkEvents.RegisterEvents;
    SetGlobalVariable(lkSettings.Values[ERP_SETTINGS_GOTOVAR], '0'); 
  end;
  //============================================================================
  function Journal_Create(const aTypeId:string):TForm; 
  begin
    Result := TERPFormGridJrnl_Create(aTypeId, false);
    ERP_ObjectExtension_Call(Result, TxcPageControlEx(Result.FindComponent(obj_name_erp_pagecontroldetail)), TERPForm_MemTableMain(Result)); 
  end;
  //============================================================================
  function Journal_Execute(const aTypeId:string):Boolean;
  var
    lkDlg :TForm;
  begin
    Result := false;
    lkDlg := TERPFormGridJrnl_Create(aTypeId, true);
    with lkDlg do
      begin
      SetGlobalVariable(TERPForm_Settings(lkDlg).Values[ERP_SETTINGS_BUFFERVAR], 'NULL');
      Result := (ShowModal = mrOK);
      if not Result then
        SetGlobalVariable(TERPForm_Settings(lkDlg).Values[ERP_SETTINGS_BUFFERVAR], 'NULL');
      TForm_Position_Save(lkDlg, PrepareAbsoleteFileName(TERPForm_Settings(lkDlg).Values[ERP_SETTINGS_TEMPFILENAME]) );  
      Free;
      end;  
  end;
