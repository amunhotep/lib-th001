{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_HEADER.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}             {$I ../OBJECTNAMES.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC}     {$I ../DBGRID/COL_PROTOCOL.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}    {$I ./FORMERP_LANG.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC}  {$I ./FORMERP_HEADER.INC}         {$ENDIF}
  //=========== PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID_HEADER.INC =============
  procedure TERPForm_DataSetMain_AfterScroll(DataSet :TDataSet);         forward;
  procedure TERPForm_DataSetMain_OnNewRecord(DataSet :TDataSet);         forward;
  function TERPFormGrid_ExportGetCaption (aOwner :TComponent):string;    forward;
  function TERPFormGrid_ExportGetFilter  (aOwner :TComponent):string;    forward;
  function TERPFormGrid_ExportGetFileName(aOwner :TComponent):string;    forward;
  procedure TERPFormGrid_RefreshView     (aOwner :TComponent);           forward;
  procedure TERPFormGrid_PanelLeft_OnShowHide(aOwner :TComponent);       forward;
  function TERPFormGrid_PrintGrid(aOwner :TComponent):Boolean;           forward;
  function TERPFormGrid_PrintItem(aOwner :TComponent):Boolean;           forward;
  //============================================================================
  function TERPFormGrid_UserHasRights:Boolean;
  var
    lkStr :string;
  begin
    Result := false;
    GetField(FBDataBase, 'PROC$_USERS_ACCS_ROLES', 'ROLES_LIST', '', lkStr);
    Result := (Pos('~1000000~',lkStr) > 0) or (Pos('~1000004~',lkStr) > 0) or (Pos('~1000014~',lkStr) > 0);
  end;  
  //============================================================================
  function TERPFormGrid_SQL(aOwner:TComponent):TStrings;
  begin
    Result := TERPForm_SQL(aOwner);
  end;
  //============================================================================
  function TERPFormGrid_dtpDateFrom(aOwner :TComponent):TDateTimePicker;
  begin
    Result := TDateTimePicker(aOwner.FindComponent(obj_name_erp_dtpdatefrom));
  end;
  //============================================================================
  function TERPFormGrid_dtpDateTo(aOwner :TComponent):TDateTimePicker;
  begin
    Result := TDateTimePicker(aOwner.FindComponent(obj_name_erp_dtpdateto));
  end;
  //============================================================================
  procedure TERPFormGrid_CloseDataSets(aOwner :TComponent);
  var
    lkSettings :TStrings;
  begin
    lkSettings := TERPForm_Settings(aOwner);
    if(TERPForm_TransactionMain(aOwner).InTransaction)then
      begin
      with TERPForm_DataSetMain(aOwner) do
        if Active then
          begin
          if(State <> dsBrowse)then
            try
              Post;
            except
              Cancel;
            end;
          lkSettings.Values[ERP_SETTINGS_BOOKMARK] := '1';  
          if(lkSettings.Values[ERP_SETTINGS_DATAMEMORY] = '1')then  
            lkSettings.Values[ERP_SETTINGS_SAVERECNO] := IntToStr(TERPForm_MemTableMain(aOwner).RecNo)
           else
            lkSettings.Values[ERP_SETTINGS_SAVERECNO] := IntToStr(RecNo);  
          Close;   
          end;
      TERPForm_TransactionMain(aOwner).Commit;
      end;
  end;
  //============================================================================
  procedure TERPFormGrid_PCDetail_OnChange(Sender :TObject);
  begin 
    if not TxcPageControlEx(Sender).Visible then exit;
    with TERPForm_DBGridMain(TComponent(Sender).Owner).DataSource.DataSet do
      begin
      if not Active then exit;
      if(not(RecordCount > 0))then exit;
      end;
    TERPForm_OpenDataSetsChilds(TERPForm_DBGridMain(TComponent(Sender).Owner).DataSource.DataSet);  
  end;
  //============================================================================
  procedure TERPFormGrid_UpdateSelectedRecords(aOwner :TComponent; const aFieldName, aFieldValueNew:string);
  var
    lkSQL  :string;
    lkCntr :Integer;
    lkCmdNo:Integer;
    lkDBG  :TDBGridEh;
    lkCol  :TColumnEh;
    lkFlag :Boolean;
  begin  
    if not TERPFormGrid_UserHasRights then
      begin
      Dialogs.MessageDlg(msg_error_erpobject_hasnt_rights, mtWarning, [mbOk]);
      exit;
      end;
    lkDBG := TERPForm_ActiveDBGrid(aOwner);
    if(not( (lkDBG.Name = obj_name_erp_data_dbgchilds) or (lkDBG.Name = obj_name_erp_data_dbgparents)))then
      lkDBG := TERPForm_DBGridMain(aOwner);
    lkCmdNo := 0;
    lkSQL   := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
    with lkDBG do
      begin
      if not DataSource.DataSet.Active then exit;
      lkCol := nil;
      try lkCol := FieldColumns[aFieldName]; except lkCol := nil; end;
      lkFlag := false;
      if(lkCol <> nil)then
        if(lkCol.ColParams[ERP_COL_INDEX_PERIODICAL] = '1')then
          lkFlag := true;
      DataSource.DataSet.DisableControls;
      SaveBookMark; 
      if(Selection.SelectionType = gstAll)then
        begin // all selected records
        DataSource.DataSet.First;
        while not DataSource.DataSet.EOF do
          begin
          if lkFlag then
            lkSQL := lkSQL + '  UPDATE OR INSERT INTO '+lkCol.ColParams[ERP_COL_INDEX_REF_TABLE]+
              '('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE,'+lkCol.ColParams[ERP_COL_INDEX_REF_FIELD]+
              ')VALUES('''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+''',CURRENT_TIMESTAMP,'''+aFieldValueNew+
              ''') MATCHING('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE); '+SQLCRLF
           else   
            lkSQL := lkSQL + '  UPDATE '+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]+' T SET T.'+
              aFieldName+' = '''+aFieldValueNew+''' WHERE (T.ID = '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+SQLCRLF;
          lkCmdNo := lkCmdNo + 1;
          if(lkCmdNo > ERP_SQL_RECORDPACKETCOUNT)then
            begin
            lkSQL := lkSQL + 'END '; 
            ExecSQL(FBDataBase, lkSQL);
            lkCmdNo := 0;
            lkSQL   := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
            end;  
          DataSource.DataSet.Next;
          end
        end
       else
        begin  // selected manually records
        if(SelectedRows.Count > 0)then
          begin
          for lkCntr:=0 to SelectedRows.Count-1 do
            begin
            DataSource.DataSet.Bookmark := SelectedRows[lkCntr];
            if lkFlag then
              lkSQL := lkSQL + '  UPDATE OR INSERT INTO '+lkCol.ColParams[ERP_COL_INDEX_REF_TABLE]+
                '('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE,'+lkCol.ColParams[ERP_COL_INDEX_REF_FIELD]+
                ')VALUES('''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+''',CURRENT_TIMESTAMP,'''+aFieldValueNew+
                ''') MATCHING('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE); '+SQLCRLF
             else   
              lkSQL := lkSQL + '  UPDATE '+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]+' T SET T.'+
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
         else // only one record
          begin
          if lkFlag then
            lkSQL := lkSQL + '  UPDATE OR INSERT INTO '+lkCol.ColParams[ERP_COL_INDEX_REF_TABLE]+
              '('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE,'+lkCol.ColParams[ERP_COL_INDEX_REF_FIELD]+
              ')VALUES('''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+''',CURRENT_TIMESTAMP,'''+aFieldValueNew+
              ''') MATCHING('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+',VALUE_DATE); '+SQLCRLF
           else   
            lkSQL := lkSQL + '  UPDATE '+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]+' T SET T.'+
              aFieldName+' = '''+aFieldValueNew+''' WHERE (T.ID = '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+SQLCRLF;
          end;
        end;  
      RestoreBookMark; 
      DataSource.DataSet.EnableControls;
      end;
    lkSQL := lkSQL + 'END ';  
//    Dialogs.MessageDlg(lkSQL, mtInformation, [mbOk]);
    TERPFormGrid_CloseDataSets(aOwner);
    TERPForm_ExecSQLParams(['isc_tpb_read_committed','isc_tpb_write','isc_tpb_rec_version','isc_tpb_nowait'], lkSQL, [], []);
    TERPFormGrid_RefreshView(aOwner);  
  end;
  //============================================================================
  procedure TERPFormGrid_DeleteSelectedRecords(aOwner :TComponent);
  var
    lkSQL  :string;
    lkCntr :Integer;
    lkCmdNo:Integer;
    lkDBG  :TDBGridEh;
  begin  
    if not TERPFormGrid_UserHasRights then
      begin
      Dialogs.MessageDlg(msg_error_erpobject_hasnt_rights, mtWarning, [mbOk]);
      exit;
      end;
    lkDBG := TERPForm_ActiveDBGrid(aOwner);
    if(not( (lkDBG.Name = obj_name_erp_data_dbgchilds) or (lkDBG.Name = obj_name_erp_data_dbgparents)))then
      lkDBG := TERPForm_DBGridMain(aOwner);
    lkCmdNo := 0;
    lkSQL   := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
    with lkDBG do
      begin
      if not DataSource.DataSet.Active then exit;
      DataSource.DataSet.DisableControls;
      SaveBookMark; 
      if(SelectedRows.Count > 0)then
        for lkCntr:=0 to SelectedRows.Count-1 do
          begin
          DataSource.DataSet.Bookmark := SelectedRows[lkCntr];
          lkSQL := lkSQL + '  DELETE FROM '+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]+' T WHERE (T.ID = '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+SQLCRLF;
          lkCmdNo := lkCmdNo + 1;
          if(lkCmdNo > ERP_SQL_RECORDPACKETCOUNT)then
            begin
            lkSQL := lkSQL + 'END '; 
            ExecSQL(FBDataBase, lkSQL);
            lkCmdNo := 0;
            lkSQL   := 'EXECUTE BLOCK AS BEGIN '+SQLCRLF;
            end;  
          end
       else
        lkSQL := lkSQL + '  DELETE FROM '+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]+' T WHERE (T.ID = '''+DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString+'''); '+SQLCRLF;
      RestoreBookMark; 
      DataSource.DataSet.EnableControls;
      end;
    lkSQL := lkSQL + 'END ';  
//    Dialogs.MessageDlg(lkSQL, mtInformation, [mbOk]);
    TERPFormGrid_CloseDataSets(aOwner);
    TERPForm_ExecSQLParams(['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkSQL, [], []);
    TERPFormGrid_RefreshView(aOwner);  
  end;
  //============================================================================
  procedure TERPFormGrid_Destroy(aOwner :TComponent);
  begin
    TERPFormGrid_CloseDataSets(aOwner);
    if(aOwner.FindComponent(obj_name_erp_data_evmain) <> nil)then
      with TxFBEvents(aOwner.FindComponent(obj_name_erp_data_evmain)) do
        if Registered then
          UnRegisterEvents;
  end;    
