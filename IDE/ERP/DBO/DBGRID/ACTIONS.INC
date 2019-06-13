{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}
{$IFNDEF PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}            {$I PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}           {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}   {$I ../$COMMON/FORMERP_NAMES.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}    {$I ../$COMMON/FORMERP_LANG.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC}  {$I ../$COMMON/FORMERP_HEADER.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_OBJECTSQL.INC}{$I ../$COMMON/DIALOG_OBJECTSQL.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC}     {$I ./COL_PROTOCOL.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/DIALOGCOLUMNS.INC}    {$I ./DIALOGCOLUMNS.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/INTF.INC}      {$I ./EXPORT/INTF.INC}                    {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC ===================
  procedure ERP_DBGridEh_UpdateSelectedRecords(aDBG :TDBGridEh; const aFieldName, aFieldValueNew:string);
  var
    lkSQL  :string;
    lkCntr :Integer;
    lkCmdNo:Integer;
    lkCol  :TColumnEh;
    lkFlag :Boolean;
  begin  
    lkFlag  := false;
    lkCmdNo := 0;
    lkSQL   := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
    with aDBG do
      begin
      if not DataSource.DataSet.Active then exit;
      lkCol := nil;
      for lkCntr:=0 to Columns.Count-1 do
        if(Columns[lkCntr].ColParams.Count >= ERP_COL_INDEX__COUNT)then
          begin
          if(Columns[lkCntr].ColParams.Count > ERP_COL_INDEX_FIELD)then
            if(Columns[lkCntr].ColParams[ERP_COL_INDEX_FIELD] = aFieldName)then
              begin
              lkCol := Columns[lkCntr]; 
              break;
              end;
          end;  
      if(lkCol = nil)then 
        exit
       else     
        if(lkCol.ColParams[ERP_COL_INDEX_PERIODICAL] = '1')then
          lkFlag := true;
      DataSource.DataSet.DisableControls;
      SaveBookMark; 
      if(Selection.Rows.Count > 0)then
        begin // selected manually records
        for lkCntr:=0 to Selection.Rows.Count-1 do
          begin
          DataSource.DataSet.Bookmark := Selection.Rows[lkCntr];
          if lkFlag then
            lkSQL := lkSQL + '  UPDATE OR INSERT INTO '+lkCol.ColParams[ERP_COL_INDEX_REF_TABLE]+
              '('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE,'+lkCol.ColParams[ERP_COL_INDEX_REF_FIELD]+
              ')VALUES('''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+''',CURRENT_TIMESTAMP,'''+aFieldValueNew+
              ''') MATCHING('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE); '+SQLCRLF
           else   
            lkSQL := lkSQL + '  UPDATE '+lkCol.ColParams[ERP_COL_INDEX_TABLEMAIN]+' T SET T.'+
              aFieldName+' = '''+aFieldValueNew+''' WHERE (T.ID = '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+SQLCRLF;
          lkCmdNo := lkCmdNo + 1;
          if(lkCmdNo > ERP_SQL_RECORDPACKETCOUNT)then
            begin
            lkSQL := lkSQL + 'END '; 
            ExecSQL(FBDataBase, lkSQL);
            lkCmdNo := 0;
            lkSQL   := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
            end;  
          end
        end
       else
        begin
        if lkFlag then
          lkSQL := lkSQL + '  UPDATE OR INSERT INTO '+lkCol.ColParams[ERP_COL_INDEX_REF_TABLE]+
            '('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE,'+lkCol.ColParams[ERP_COL_INDEX_REF_FIELD]+
            ')VALUES('''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+''',CURRENT_TIMESTAMP,'''+aFieldValueNew+
            ''') MATCHING('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE); '+SQLCRLF
         else   
          lkSQL := lkSQL + '  UPDATE '+lkCol.ColParams[ERP_COL_INDEX_TABLEMAIN]+' T SET T.'+
            aFieldName+' = '''+aFieldValueNew+''' WHERE (T.ID = '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+SQLCRLF;
        end;
      RestoreBookMark; 
      DataSource.DataSet.EnableControls;
      end;
    lkSQL := lkSQL + 'END ';//  Dialogs.MessageDlg(lkSQL, mtInformation, [mbOk]);
    TERPForm_ExecSQL([], lkSQL);
  end;
  //============================================================================
  procedure  ERP_DBGridEh_DeleteSelectedRecords(aDBG :TDBGridEh);
  var
    lkSQL  :string;
    lkCntr :Integer;
    lkCmdNo:Integer;
    lkCol  :TColumnEh;
  begin 
    lkCmdNo := 0;
    lkCol   := nil;
    lkSQL   := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
    with aDBG do
      begin
      if not DataSource.DataSet.Active then exit;
      lkCol := nil;
      for lkCntr:=0 to Columns.Count-1 do
        if(Columns[lkCntr].ColParams.Count >= ERP_COL_INDEX__COUNT)then
          begin
          lkCol := Columns[lkCntr]; 
          break;
          end;  
      if(lkCol = nil)then exit;
      DataSource.DataSet.DisableControls;
      SaveBookMark; 
      if(SelectedRows.Count > 0)then
        for lkCntr:=0 to SelectedRows.Count-1 do
          begin
          DataSource.DataSet.Bookmark := SelectedRows[lkCntr];
          lkSQL := lkSQL + '  DELETE FROM '+lkCol.ColParams[ERP_COL_INDEX_TABLEMAIN]+' T WHERE (T.ID = '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+SQLCRLF;
          lkCmdNo := lkCmdNo + 1;
          if(lkCmdNo > ERP_SQL_RECORDPACKETCOUNT)then
            begin
            lkSQL := lkSQL + 'END '; 
            TERPForm_ExecSQL([], lkSQL);
            lkCmdNo := 0;
            lkSQL   := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
            end;  
          end
       else
        lkSQL := lkSQL + '  DELETE FROM '+lkCol.ColParams[ERP_COL_INDEX_TABLEMAIN]+' T WHERE (T.ID = '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+SQLCRLF;
      RestoreBookMark; 
      DataSource.DataSet.EnableControls;
      end;
    lkSQL := lkSQL + 'END '; 
    TERPForm_ExecSQL([], lkSQL);
  end;
  //============================================================================
  procedure ERP_DBGridEh_EditItem(aGrid :TDBGridEh);
  var
    lkFrm :TComponent;
    lkIndx:Integer;
  begin
    with aGrid do
      begin
      with DataSource.DataSet do
        begin
        if(not Active)then exit;
        if(not(RecordCount > 0))then exit;
        end;
      lkFrm := TERPForm_GetOwner(aGrid);
      if(lkFrm = nil)then exit;
      for lkIndx:=0 to Columns.Count-1 do
        if(Columns[lkIndx].FieldName <> ERP_SQL_FIELD_IMAGES)then
          if(Columns[lkIndx].ColParams.Count = ERP_COL_INDEX__COUNT)then
            break;
      SetGlobalVariable(Columns[lkIndx].ColParams[ERP_COL_INDEX_MAIN_BUFFERVAR], DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString);
      if(StrToInt(Columns[lkIndx].ColParams[ERP_COL_INDEX_MAIN_BASETYPE]) = ERP_OBJECTTYPE_DOC)then
        begin
        if(DataSource.DataSet.FindField('TYPE_ID') <> nil)then
          begin
          if(TForm(lkFrm).FormStyle = fsMDIChild)then
            call(StrReplaceStr(Columns[lkIndx].ColParams[ERP_COL_INDEX_MAIN_SCRIPTITEM], '<%OBJECT_TYPE%>', DataSource.DataSet.FieldByName('TYPE_ID').AsString));
          end;  
        end
       else 
        if(TForm(lkFrm).FormStyle = fsMDIChild)then
          call(Columns[lkIndx].ColParams[ERP_COL_INDEX_MAIN_SCRIPTITEM])
         else 
          call(Columns[lkIndx].ColParams[ERP_COL_INDEX_MAIN_SCRIPTITEMDLG]);
      end;  
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdViewColumns_OnExecute(Sender :TObject);
  begin
    ERP_DBGridEh_ColumnsDialog_Execute(TDBGridEh(TComponent(Sender).Owner));
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdViewGroup_OnExecute(Sender :TObject);
  var
    lkDBG :TDBGridEh;
  begin
    lkDBG := TDBGridEh(TComponent(Sender).Owner);
    if(lkDBG = nil)then exit;
    lkDBG.DataGrouping.Active            := not lkDBG.DataGrouping.Active;
    lkDBG.DataGrouping.GroupPanelVisible := lkDBG.DataGrouping.Active;
    if not lkDBG.DataGrouping.Active then
      lkDBG.DataGrouping.GroupLevels.Clear;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdViewGroup_OnUpdate(Sender :TObject);
  begin
//    TCustomAction(Sender).Checked := TDBGridEh(TComponent(Sender).Owner).DataGrouping.Active;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdViewSummary_OnExecute(Sender :TObject);
  var
    lkDBG :TDBGridEh;
  begin
    lkDBG := TDBGridEh(TComponent(Sender).Owner);
    if(lkDBG = nil)then exit;
    lkDBG.SumList.Active := not lkDBG.SumList.Active;
    if lkDBG.SumList.Active then
      lkDBG.FooterRowCount := StrToInt(TDBGridEh(TComponent(Sender).Owner).HelpKeyWord)
     else
      lkDBG.FooterRowCount := 0;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdViewSummary_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := (StrToInt(TDBGridEh(TComponent(Sender).Owner).HelpKeyWord) > 0);
    TCustomAction(Sender).Checked := TDBGridEh(TComponent(Sender).Owner).SumList.Active;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdViewSQL_OnExecute(Sender :TObject);
  var
    lkDS :TDataSet;
  begin
    lkDS := TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet;
    if not ObjectInheritsFrom(lkDS, 'TxFBCustomDataSet') then
      if ObjectInheritsFrom(lkDS, 'TMemTableEh')then
        lkDS := TDataSetDriverEh(TMemTableEh(lkDS).DataDriver).ProviderDataSet;
    if not ObjectInheritsFrom(lkDS, 'TxFBCustomDataSet') then exit;
    ERP_DialogSQL_Execute(TxFBCustomDataSet(lkDS));      
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdNavFirst_OnExecute(Sender :TObject);
  begin
    if not TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active then exit;
    TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.First;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdNavFirst_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin
    lkEnabled := TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active;
    if lkEnabled then 
      lkEnabled := not TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.BOF;
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdNavPrior_OnExecute(Sender :TObject);
  begin
    if not TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active then exit;
    TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Prior;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdNavNext_OnExecute(Sender :TObject);
  begin
    if not TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active then exit;
    TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Next;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdNavLast_OnExecute(Sender :TObject);
  begin
    if not TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active then exit;
    TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Last;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdNavLast_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin
    lkEnabled := TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active;
    if lkEnabled then lkEnabled := not TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.EOF;
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdNavFindItem_OnExecute(Sender :TObject);
  begin
    {$IFDEF AMUNHOTEP4832}
    with TDBGridEh(TComponent(Sender).Owner) do
      begin
      SearchPanel.FilterOnTyping := True;
      SearchPanel.ShortCut := TextToShortCut('Ctrl+F');
      SearchPanel.Enabled  := not SearchPanel.Enabled;
      end;
    {$ELSE}
    ExecuteDBGridEhFindDialog(TDBGridEh(TComponent(Sender).Owner), '', '', [], true);
    {$ENDIF}
  end; 
  //============================================================================
  procedure ERP_DBGridEh_actStdNavFindItem_OnUpdate(Sender :TObject);
  var
    lkEnabled : Boolean;
  begin
    lkEnabled := TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active;
    TCustomAction(Sender).Enabled := lkEnabled;
    {$IFDEF AMUNHOTEP4832}
    TCustomAction(Sender).Checked := TDBGridEh(TComponent(Sender).Owner).SearchPanel.Enabled;
    {$ENDIF}
  end; 
  //============================================================================
  procedure ERP_DBGridEh_actStdExport_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdExportOOCalc_OnExecute(Sender :TObject);
  begin
    ERP_DBGridEh_ExportToOpenOfficeCalc(TDBGridEh(TComponent(Sender).Owner), 'Sheet1', '', '', '', '');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdExportXLS_OnExecute(Sender :TObject);
  begin
    ERP_DBGridEh_ExportToExcel(TDBGridEh(TComponent(Sender).Owner), 'Sheet1', '', '', '', '');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actStdExportHTML_OnExecute(Sender :TObject);
  begin
    ERP_DBGridEh_ExportToHTML(TDBGridEh(TComponent(Sender).Owner), '', '', '', '', '');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtIns_OnExecute(Sender :TObject);
  begin
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if not Active then exit;
      if(State = dsBrowse)then
        Insert;
      end;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtIns_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin 
    lkEnabled := TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active;
    if lkEnabled then lkEnabled := (TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.State = dsBrowse);
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtUpd_OnExecute(Sender :TObject);
  begin
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if not Active then exit;
      if(State = dsBrowse)then
        Edit;
      end;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtUpdGrp_OnExecute(Sender :TObject);
  var
    lkColIndex   :Integer;
    lkInt        :Integer;
    lkFloat      :Extended;
    lkDate       :TDateTime;
    lkFieldName  :string;
    lkFieldValue :string;
    lkDoUpdate   :Boolean;
  begin
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if(not Active)then exit;
      if(not(RecordCount > 0))then exit;
      end;
    lkColIndex := 0;
    if not ERP_DBGridEh_ColumnSelect(TDBGridEh(TComponent(Sender).Owner), lkColIndex) then exit;
    lkFieldValue := '';
    lkDoUpdate   := false;
    with TDBGridEh(TComponent(Sender).Owner).Columns[lkColIndex] do
      begin
      if(ReadOnly and (ColParams[ERP_COL_INDEX_REF_TABLE] = ''))then
        begin
        Dialogs.MessageDlg(msg_error_erpobject_acces_denied2, mtError, [mbOK]);
        exit;
        end;
      lkFieldName := ColParams[ERP_COL_INDEX_FIELD];
      if( (ColParams[ERP_COL_INDEX_REF_TABLE] <> '') and (ColParams[ERP_COL_INDEX_PERIODICAL] <> '1'))then
        begin
        lkFieldValue := Field.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString;
        SetGlobalVariable(ColParams[ERP_COL_INDEX_REF_BUFFERVAR], lkFieldValue);
        call(ColParams[ERP_COL_INDEX_REF_SCRIPTDLG]);
        lkFieldValue := GetGlobalVariable(ColParams[ERP_COL_INDEX_REF_BUFFERVAR]);
        lkDoUpdate := not( (UpperCase(lkFieldValue) = 'NULL') or (StrTrimAll(lkFieldValue) = '') );
        end
       else if(StrTrimAll(KeyList.Text) <> '')then
        begin
        lkFieldValue := DisplayText;
        lkDoUpdate := Dialogs.CaseString(msg_erp_enter_new_attr_value, PickList.Text, lkFieldValue);
        if lkDoUpdate then lkFieldValue := KeyList[PickList.IndexOf(lkFieldValue)];
        end
       else
        begin 
             if(ColParams[ERP_COL_INDEX_FIELDTYPE] = 'DOMN$BOOLEAN')then 
               begin
               lkDoUpdate := (Dialogs.MessageDlg('', mtConfirmation, [mbYes, mbNo]) = mrYes);
               if lkDoUpdate then lkFieldValue := '1';
               end
        else if(  (ColParams[ERP_COL_INDEX_FIELDTYPE]='DOMN$DATE') 
                or(ColParams[ERP_COL_INDEX_FIELDTYPE]='DOMN$DATETIME') 
                or(ColParams[ERP_COL_INDEX_FIELDTYPE]='DOMN$TIME') 
             )then 
               begin
               lkDate := Field.AsDateTime;
               lkDoUpdate := Dialogs.InputQueryDateTime(msg_erp_enter_new_attr_value, Title.Hint, lkDate);
               if lkDoUpdate then lkFieldValue := FormatDateTime('dd.mm.yyyy', lkDate)+' 00:00:00';
               end
        else if(  (Pos('DOMN$INTEGER' ,ColParams[ERP_COL_INDEX_FIELDTYPE]) = 1) 
                or(Pos('DOMN$SMALLINT',ColParams[ERP_COL_INDEX_FIELDTYPE]) = 1) 
                or(Pos('DOMN$LONGINT' ,ColParams[ERP_COL_INDEX_FIELDTYPE]) = 1) 
             )then 
               begin
               lkInt := Field.AsInteger;
               lkDoUpdate := Dialogs.InputQueryInteger(msg_erp_enter_new_attr_value, Title.Hint, lkInt);
               if lkDoUpdate then lkFieldValue := IntToStr(lkInt);
               end
        else if(Pos('DOMN$FLOAT',ColParams[ERP_COL_INDEX_FIELDTYPE]) = 1)then 
               begin
               lkFloat := Field.AsFloat;
               lkDoUpdate := Dialogs.InputQueryExtended(msg_erp_enter_new_attr_value, Title.Hint, lkFloat);
               if lkDoUpdate then lkFieldValue := StrReplaceStr(FormatFloat('#0.000',lkFloat), ',', '.');
               end
        else 
               begin
               lkFieldValue := Field.AsString;
               lkDoUpdate := Dialogs.InputQueryString(msg_erp_enter_new_attr_value, Title.Hint, lkFieldValue);
               if lkDoUpdate then lkFieldValue := StrReplaceStr(lkFieldValue, '''', '''''');
               end
               ;
        end; 
      end;
    if lkDoUpdate then ERP_DBGridEh_UpdateSelectedRecords(TDBGridEh(TComponent(Sender).Owner), lkFieldName, lkFieldValue); 
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtEdt_OnExecute(Sender :TObject);
  begin
    ERP_DBGridEh_EditItem(TDBGridEh(TComponent(Sender).Owner));
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtCrt_OnExecute(Sender :TObject);
  begin
    with TDBGridEh(TComponent(Sender).Owner) do
      begin
      with DataSource.DataSet do
        begin
        if not Active then exit;
        if(State <> dsBrowse)then 
          Cancel;
        Last;
        Append;
        if(FindField('NAME') <> nil)then
          FieldByName('NAME').AsString := msg_erp_column_entername;
        end;
      try
        DataSource.DataSet.Post;
      finally
        SetGlobalVariable(Columns[0].ColParams[ERP_COL_INDEX_MAIN_BUFFERVAR], DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString);
        if(TERPForm_GetOwner(TDBGridEh(TComponent(Sender).Owner)).FindComponent(obj_name_erp_actviewrefresh) <> nil)then
          TCustomAction(TERPForm_GetOwner(TDBGridEh(TComponent(Sender).Owner)).FindComponent(obj_name_erp_actviewrefresh) ).Execute;
        if(TForm(TERPForm_GetOwner(TDBGridEh(TComponent(Sender).Owner))).FormStyle = fsMDIChild)then
          call(Columns[0].ColParams[ERP_COL_INDEX_MAIN_SCRIPTITEM])
         else
          call(Columns[0].ColParams[ERP_COL_INDEX_MAIN_SCRIPTITEMDLG]); 
      end;
      end;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtDel_OnExecute(Sender :TObject);
  begin
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if(not Active)then exit;
      if(not(RecordCount > 0))then exit;
      end;
    if(Dialogs.MessageDlg(msg_erp_actdel+' ?', mtConfirmation, [mbYes, mbNo])=mrYes)then
      ERP_DBGridEh_DeleteSelectedRecords(TDBGridEh(TComponent(Sender).Owner));
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtDel_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin 
    lkEnabled := TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active;
    if lkEnabled then lkEnabled := (TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.RecordCount > 0);
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtPost_OnExecute(Sender :TObject);
  begin
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if not Active then exit;
      if(State <> dsBrowse)then
        Post;
      end;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtPost_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin 
    lkEnabled := TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.Active;
    if lkEnabled then lkEnabled := (TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet.State <> dsBrowse);
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtCancel_OnExecute(Sender :TObject);
  begin
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if not Active then exit;
      if(State <> dsBrowse)then
        Cancel;
      end;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtMD_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actmark_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
    ERP_DBGridEh_UpdateSelectedRecords(TDBGridEh(TComponent(Sender).Owner), 'FLAG_DELETE', '1');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtUD_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actunmark_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
    ERP_DBGridEh_UpdateSelectedRecords(TDBGridEh(TComponent(Sender).Owner), 'FLAG_DELETE', '0');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtCD_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actcommit_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
    ERP_DBGridEh_UpdateSelectedRecords(TDBGridEh(TComponent(Sender).Owner), 'FLAG_COMMIT', '1');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtUC_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actuncommit_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
    ERP_DBGridEh_UpdateSelectedRecords(TDBGridEh(TComponent(Sender).Owner), 'FLAG_COMMIT', '0');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtLD_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actlock_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
    ERP_DBGridEh_UpdateSelectedRecords(TDBGridEh(TComponent(Sender).Owner), 'FLAG_LOCK', '1');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actEdtUL_OnExecute(Sender :TObject);
  begin
    if(Dialogs.MessageDlg(msg_erp_actunlock_hint+' ?', mtConfirmation,[mbYes,mbNo]) <> mrYes)then exit;
    ERP_DBGridEh_UpdateSelectedRecords(TDBGridEh(TComponent(Sender).Owner), 'FLAG_LOCK', '0');
  end;
  //============================================================================
  procedure ERP_DBGridEh_actDocCnd_OnExecute(Sender :TObject);
  begin
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if(not Active)then exit;
      if(not(RecordCount > 0))then exit;
      end;
    with TDBGridEh(TComponent(Sender).Owner) do
      begin 
      SetGlobalVariable(Columns[Columns.Count-1].ColParams[ERP_COL_INDEX_MAIN_BUFFERVAR], DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString);
      call('PEAKTOP:IDE/ERP/CONFIG/REG/CND/DEFAULT_DOC.PS');
      end;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actDocGotoJrnl_OnExecute(Sender :TObject);
  var
    lkVarName:string;
    lkScript :string;
  begin
    lkVarName := StrTrimAll(TERPForm_Settings(TComponent(Sender).Owner.Owner).Values[ERP_SETTINGS_GOTOVAR]);
    if(lkVarName = '')then exit;
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if(not Active)then exit;
      if(not(RecordCount > 0))then exit;
      if(FindField('TYPE_ID') <> nil)then
        begin
        SetGlobalVariable(lkVarName, FieldByName(ERP_DATASET_DBKEY).AsString);
        lkScript := '{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}{$I PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}{$ENDIF} '+SQLCRLF+
                    'begin '+SQLCRLF+'  Journal_Create('''+FieldByName('TYPE_ID').AsString+'''); '+SQLCRLF+'end.';        
        run(lkScript, 'DB:CONFIG/DOC/'+FieldByName('TYPE_ID').AsString+'/DEFAULT.PS');
        end;
      end;
  end;
  //============================================================================
  procedure ERP_DBGridEh_actDocChildList_OnExecute(Sender :TObject);
  var
    lkVarName:string;
    lkScript :string;
  begin  
    lkVarName := StrTrimAll(TERPForm_Settings(TComponent(Sender).Owner.Owner).Values[ERP_SETTINGS_GOTOVAR]);
    if(lkVarName = '')then exit;
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if(not Active)then exit;
      if(not(RecordCount > 0))then exit;
      SetGlobalVariable(lkVarName, FieldByName(ERP_DATASET_DBKEY).AsString);
      SetGlobalVariable(ERP_SETTINGS_FLAGHISTORY, '1');
      lkScript := '{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}{$I PEAKTOP:IDE/ERP/DBO/DOC/FORMJRNL.INC}{$ENDIF} '+SQLCRLF+
                  'begin '+SQLCRLF+'  Journal_Create(''4''); '+SQLCRLF+'end.';        
      run(lkScript, 'DB:CONFIG/DOC/4/DEFAULT.PS');
      end;
  end;  
  //============================================================================
  procedure ERP_DBGridEh_actObjImg_OnExecute(Sender :TObject);
  begin  
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if(not Active)then exit;
      if(not(RecordCount > 0))then exit;
      end;
    with TDBGridEh(TComponent(Sender).Owner) do
      begin 
      SetGlobalVariable(ERP_GLOBALVARIABLE_OBJ_ID, Columns[Columns.Count-1].ColParams[ERP_COL_INDEX_TABLEMAIN]);
      SetGlobalVariable(ERP_GLOBALVARIABLE_REC_ID, DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString);
      call('PEAKTOP:IDE/ERP/DBO/OPER/IMG/DEFAULT.PS');
      end;
  end;  
  //============================================================================
  procedure ERP_DBGridEh_actCopyToClipBoard_OnExecute(Sender :TObject);
  var
    lkSQL  :string;
    lkCntr :Integer;
  begin
    with TDBGridEh(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if(not Active)then exit;
      if(not(RecordCount > 0))then exit;
      end;
    with TDBGridEh(TComponent(Sender).Owner) do
      begin 
      if not DataSource.DataSet.Active then exit;
      DataSource.DataSet.DisableControls;
      SaveBookMark;
      lkSQL := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
      if(SelectedRows.Count > 0)then
        begin 
        for lkCntr:=0 to SelectedRows.Count-1 do
          begin 
          DataSource.DataSet.Bookmark := SelectedRows[lkCntr];
          lkSQL := lkSQL+'  INSERT INTO TABL$_BUFFER(NAME, USER_ID, OBJ_NAME, OBJ_ID)VALUES('''+
            ERP_ObjectGUID(StrToInt(Columns[0].ColParams[ERP_COL_INDEX_MAIN_BASETYPE]))+''', '''+GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''', '''+
            Columns[0].ColParams[ERP_COL_INDEX_TABLEMAIN]+''', '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+#13#10;
          end;
        end
       else
        begin
        lkSQL := lkSQL+'  INSERT INTO TABL$_BUFFER(NAME, USER_ID, OBJ_NAME, OBJ_ID)VALUES('''+
          ERP_ObjectGUID(StrToInt(Columns[0].ColParams[ERP_COL_INDEX_MAIN_BASETYPE]))+''', '''+GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''', '''+
          Columns[0].ColParams[ERP_COL_INDEX_TABLEMAIN]+''', '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+#13#10;
        end;   
      lkSQL := lkSQL+'END';
      ExecSQL(FBDataBase, lkSQL);   
      RestoreBookMark; 
      DataSource.DataSet.EnableControls;
      end;
  end;
  //============================================================================
  procedure ERP_DBGridEh_DBGrid_OnDblClickEdit(Sender: TObject);
  var
    lkFrm :TComponent;
  begin
    lkFrm := TERPForm_GetOwner(TComponent(Sender));
    if(TForm(lkFrm).FormStyle = fsMDIChild)then
      ERP_DBGridEh_EditItem( TDBGridEh(Sender) )
     else
      if(TComponent(Sender).Owner = lkFrm)then
        TForm(lkFrm).ModalResult := mrOk;
  end;
  //============================================================================
  procedure ERP_DBGridEh_DBGrid_OnDblClick(Sender: TObject);
  var
    lkFrm :TComponent;
  begin
    lkFrm := TERPForm_GetOwner(TComponent(Sender));
    with TDBGridEh(Sender) do
      begin
      if(TForm(lkFrm).FormStyle = fsMDIChild)then
        begin
        ERP_DBGridEh_EditItem( TDBGridEh(Sender) );
        end
       else
        begin
        if(Owner = lkFrm)then
          TForm(lkFrm).ModalResult := mrOk;
        end; 
      end  
  end;
  //============================================================================
  procedure ERP_DBGridEh_StdActions_Create(aDBG :TDBGridEh; const aCreateParams :TFormERPParams; aParent :TWinControl; aParentItem :TMenuItem);
  var
    lkAct     :TCustomAction;
    lkMI      :TMenuItem;
    lkSuff    :string;
    lkToolBar :TxcGradientPanelVista;
  begin
    if not(erpGrid in aCreateParams) then exit;
    DontAutoFree;
    lkSuff  := RandomHexStr(8);
    lkToolBar:= CreateTxcGradientPanelVistaToolBar(aDBG,aParent,obj_name_erp_toolbar_view+lkSuff,'',alLeft, 2000,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    lkAct   := TERPForm_CreateAction(aDBG,obj_name_erp_actviewcolumns+lkSuff,msg_erp_actviewcolumns ,msg_erp_actviewcolumns_hint,'',0,190,@ERP_DBGridEh_actStdViewColumns_OnExecute,nil                                     ,lkToolBar,aParentItem);
    lkAct   := TERPForm_CreateAction(aDBG,obj_name_erp_actviewsummary+lkSuff,msg_erp_actviewsummary ,msg_erp_actviewsummary_hint,'',0,262,@ERP_DBGridEh_actStdViewSummary_OnExecute,@ERP_DBGridEh_actStdViewSummary_OnUpdate,lkToolBar,aParentItem);
    if(erpGridGroup in aCreateParams)then
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actviewgroup  +lkSuff,msg_erp_actviewgroup   ,msg_erp_actviewgroup_hint  ,'',0, 65,@ERP_DBGridEh_actStdViewGroup_OnExecute  ,@ERP_DBGridEh_actStdViewGroup_OnUpdate  ,lkToolBar,aParentItem);
    if(erpGridNavigation in aCreateParams)then
      begin
      if(aParentItem <> nil)then  
        lkMI:= CreateTMenuItem(aParentItem,obj_name_erp_mimainobjnav_h+lkSuff,msg_erp_mimainobjnav_h,'','', -1,0); 
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actnavfirst    +lkSuff,msg_erp_actnavfirst    ,msg_erp_actnavfirst_hint   ,'',0, 54,@ERP_DBGridEh_actStdNavFirst_OnExecute   ,@ERP_DBGridEh_actStdNavFirst_OnUpdate   ,lkToolBar,aParentItem);
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actnavprior    +lkSuff,msg_erp_actnavprior    ,msg_erp_actnavprior_hint   ,'',0, 57,@ERP_DBGridEh_actStdNavPrior_OnExecute   ,@ERP_DBGridEh_actStdNavFirst_OnUpdate   ,lkToolBar,aParentItem);
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actnavnext     +lkSuff,msg_erp_actnavnext     ,msg_erp_actnavnext_hint    ,'',0, 56,@ERP_DBGridEh_actStdNavNext_OnExecute    ,@ERP_DBGridEh_actStdNavLast_OnUpdate    ,lkToolBar,aParentItem);
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actnavlast     +lkSuff,msg_erp_actnavlast     ,msg_erp_actnavlast_hint    ,'',0, 55,@ERP_DBGridEh_actStdNavLast_OnExecute    ,@ERP_DBGridEh_actStdNavLast_OnUpdate    ,lkToolBar,aParentItem);
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actnavfinditem +lkSuff,msg_erp_actnavfinditem ,msg_erp_actnavfinditem_hint,'',0,142,@ERP_DBGridEh_actStdNavFindItem_OnExecute,@ERP_DBGridEh_actStdNavFindItem_OnUpdate,lkToolBar,aParentItem);
      end;
    if(erpGridExport in aCreateParams)then
      begin
      if(aParentItem <> nil)then  
        lkMI:= CreateTMenuItem(aParentItem,obj_name_erp_mimainobjexport_h+lkSuff,msg_erp_mimainobjexport_h,'','', -1,0); 
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actexportoocalc+lkSuff ,msg_erp_actexportoocalc,msg_erp_actexportoocalc_hint,'',0,540,@ERP_DBGridEh_actStdExportOOCalc_OnExecute,@ERP_DBGridEh_actStdExport_OnUpdate ,lkToolBar,aParentItem);
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actexportxls   +lkSuff ,msg_erp_actexportxls   ,msg_erp_actexportxls_hint   ,'',0,  2,@ERP_DBGridEh_actStdExportXLS_OnExecute   ,@ERP_DBGridEh_actStdExport_OnUpdate ,lkToolBar,aParentItem);
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actexporthtml  +lkSuff ,msg_erp_actexporthtml  ,msg_erp_actexporthtml_hint  ,'',0,230,@ERP_DBGridEh_actStdExportHTML_OnExecute  ,@ERP_DBGridEh_actStdExport_OnUpdate ,lkToolBar,aParentItem);
      end;
    if(GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT) = 'PEAKTOP')then
      begin
      lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actviewsql     +lkSuff ,msg_erp_actviewsql     ,msg_erp_actviewsql_hint     ,'',0,290,@ERP_DBGridEh_actStdViewSQL_OnExecute     ,nil                                 ,lkToolBar,aParentItem);
      end;
    lkToolBar.Width  := TWinControl_AutoWidth(lkToolBar)+2; 
    lkToolBar.Visible:= (lkToolBar.ControlCount  > 0);
  end;
  //============================================================================
  procedure ERP_DBGridEh_EdtActions_Create(aDBG :TDBGridEh; const aCreateParams :TFormERPParams; aParent :TWinControl; aParentItem :TMenuItem);
  var
    lkAct     :TCustomAction;
    lkMI      :TMenuItem;
    lkSuff    :string;
    lkToolBar :TxcGradientPanelVista;
  begin
    if not(erpGrid in aCreateParams) then exit;
    DontAutoFree;
    lkSuff  := RandomHexStr(8);
    lkToolBar:= CreateTxcGradientPanelVistaToolBar(aDBG,aParent,obj_name_erp_toolbar_item+lkSuff,'',alLeft, 2000,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolBarBorderStyle);
    with aDBG do
      begin
      OnDblClick := @ERP_DBGridEh_DBGrid_OnDblClick;
      end;
    if(erpGridEdit in aCreateParams)then
      begin
      if(erpGridEditIns in aCreateParams)then
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actins+lkSuff,msg_erp_actins,msg_erp_actins_hint,SHORTCUT_DATA_INSERT,0,176,@ERP_DBGridEh_actEdtIns_OnExecute,@ERP_DBGridEh_actEdtIns_OnUpdate,lkToolBar,aParentItem)
       else
        with aDBG do
          begin   
          AllowedOperations := AllowedOperations - [alopInsertEh];
          AllowedOperations := AllowedOperations - [alopAppendEh];
          end;
      if(erpGridEditCreate in aCreateParams)then
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actcreate+lkSuff,msg_erp_actcreate,msg_erp_actcreate_hint,SHORTCUT_DATA_CREATE,0,181,@ERP_DBGridEh_actEdtCrt_OnExecute,@ERP_DBGridEh_actEdtIns_OnUpdate,lkToolBar,aParentItem)
      if(erpGridEditUpd in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actupd+lkSuff,msg_erp_actupd,msg_erp_actupd_hint,SHORTCUT_DATA_UPDATE,0,175,@ERP_DBGridEh_actEdtUpd_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
        end
       else 
        aDBG.AllowedOperations := aDBG.AllowedOperations - [alopUpdateEh];
      if(erpGridEditUpdGroup in aCreateParams)then
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actupdgroup+lkSuff,msg_erp_actupdgroup,msg_erp_actupdgroup_hint   ,'',0,405,@ERP_DBGridEh_actEdtUpdGrp_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
      if(erpGridEditEdt in aCreateParams)then
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actedt+lkSuff,msg_erp_actedt,msg_erp_actedt_hint,SHORTCUT_DATA_EDIT  ,0,390,@ERP_DBGridEh_actEdtEdt_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
      if(erpGridEditDel in aCreateParams)then
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actdel+lkSuff,msg_erp_actdel,msg_erp_actdel_hint,SHORTCUT_DATA_DELETE,0,177,@ERP_DBGridEh_actEdtDel_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem)
       else 
        aDBG.AllowedOperations := aDBG.AllowedOperations - [alopDeleteEh];
      if(aParentItem <> nil)then  
        lkMI:= CreateTMenuItem(aParentItem,'N0002' ,'-','','', -1,0); 
      if(erpGridEditPostCancel in aCreateParams)then
        begin  
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actpost  +lkSuff,msg_erp_actpost  ,msg_erp_actpost_hint  ,SHORTCUT_DATA_POST  ,0,143,@ERP_DBGridEh_actEdtPost_OnExecute  ,@ERP_DBGridEh_actEdtPost_OnUpdate,lkToolBar,aParentItem);
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actcancel+lkSuff,msg_erp_actcancel,msg_erp_actcancel_hint,SHORTCUT_DATA_CANCEL,0,171,@ERP_DBGridEh_actEdtCancel_OnExecute,@ERP_DBGridEh_actEdtPost_OnUpdate,lkToolBar,aParentItem);
        if(aParentItem <> nil)then  
          lkMI:= CreateTMenuItem(aParentItem,'N0002' ,'-','','', -1,0); 
        end;
      if(erpGridEditMark in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actmark  +lkSuff,msg_erp_actmark  ,msg_erp_actmark_hint  ,SHORTCUT_DOC_MARKDELETE  ,0,300,@ERP_DBGridEh_actEdtMD_OnExecute  ,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actunmark+lkSuff,msg_erp_actunmark,msg_erp_actunmark_hint,SHORTCUT_DOC_UNMARKDELETE,0,299,@ERP_DBGridEh_actEdtUD_OnExecute  ,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
        if(aParentItem <> nil)then  
          lkMI:= CreateTMenuItem(aParentItem,'N0003' ,'-','','', -1,0); 
        end;
      if(erpGridEditCommit in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actcommit  +lkSuff,msg_erp_actcommit  ,msg_erp_actcommit_hint  ,SHORTCUT_DOC_COMMIT  ,0,298,@ERP_DBGridEh_actEdtCD_OnExecute ,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actuncommit+lkSuff,msg_erp_actuncommit,msg_erp_actuncommit_hint,SHORTCUT_DOC_UNCOMMIT,0,297,@ERP_DBGridEh_actEdtUC_OnExecute ,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
        if(aParentItem <> nil)then  
          lkMI:= CreateTMenuItem(aParentItem,'N0004' ,'-','','', -1,0); 
        end;
      if(erpGridEditLock in aCreateParams)then
        begin
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actlock  +lkSuff,msg_erp_actlock  ,msg_erp_actlock_hint  ,'',0,224,@ERP_DBGridEh_actEdtLD_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actunlock+lkSuff,msg_erp_actunlock,msg_erp_actunlock_hint,'',0,226,@ERP_DBGridEh_actEdtUL_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
        if(aParentItem <> nil)then  
          lkMI:= CreateTMenuItem(aParentItem,'N0005' ,'-','','', -1,0); 
        end;
      if(erpGridEditCommit in aCreateParams)then
        begin
        if(erpGridEditGotoJrnl in aCreateParams)then
          begin
          lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actdocgotojrnl+lkSuff ,msg_erp_actdocgotojrnl ,msg_erp_actdocgotojrnl_hint ,SHORTCUT_DOC_GOTOJRNL,0,519,@ERP_DBGridEh_actDocGotoJrnl_OnExecute ,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
          lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actdocchildlist+lkSuff,msg_erp_actdocchildlist,msg_erp_actdocchildlist_hint,SHORTCUT_DOC_DOCLIST ,0,466,@ERP_DBGridEh_actDocChildList_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
          end;
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actdoccnd  +lkSuff,msg_erp_actdoccnd  ,msg_erp_actdoccnd_hint  ,''                   ,0, 46,@ERP_DBGridEh_actDocCnd_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
        end;
      if not(erpGridNoImages in aCreateParams)then
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actobjimg     +lkSuff,msg_erp_actobjimg     ,msg_erp_actobjimg_hint     ,'',0,283,@ERP_DBGridEh_actObjImg_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
      if not(erpGridNoCopy in aCreateParams)then
        lkAct := TERPForm_CreateAction(aDBG,obj_name_erp_actcopytoclbrd+lkSuff,msg_erp_actcopytoclbrd,msg_erp_actcopytoclbrd_hint,SHORTCUT_DATA_COPYTOCLIPBOARD,0, 68,@ERP_DBGridEh_actCopyToClipBoard_OnExecute,@ERP_DBGridEh_actEdtDel_OnUpdate,lkToolBar,aParentItem);
      end;
    lkToolBar.Width  := TWinControl_AutoWidth(lkToolBar)+2; 
    lkToolBar.Visible:= (lkToolBar.ControlCount  > 0);
  end;     
