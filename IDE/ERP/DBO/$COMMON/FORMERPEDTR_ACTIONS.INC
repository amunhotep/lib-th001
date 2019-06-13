{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_ACTIONS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_NAMES.INC}  {$I ./FORMERPEDTR_NAMES.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_HEADER.INC} {$I ./FORMERPEDTR_HEADER.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/DIALOGCOLUMNS.INC}       {$I ../DBGRID/DIALOGCOLUMNS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/ROLES_DLG_LIST.INC}       {$I ../USERS/ROLES_DLG_LIST.INC}              {$ENDIF}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_ACTIONS.INC ===========
  procedure TERPFormEdtr_actViewRefresh_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormEdtr_actViewMenu_OnExecute(Sender :TObject);
  begin
    with TCustomAction(Sender) do
      ERP_ObjectEditor(TERPForm_ObjId(Owner), ERP_OBJECTTYPE_MENU);
  end;
  //============================================================================
  procedure TERPFormEdtr_actViewMenu_OnUpdate(Sender :TObject);
  begin
    with TCustomAction(Sender) do
      Enabled := TERPForm_DataSetMain(Owner).Active;
  end; 
  //============================================================================
  procedure TERPFormEdtr_tbbScriptGen_OnClick(Sender :TObject);
  var
    lkTemplateName :string;
    lkScriptDir    :string;
    lkScriptName   :string;
    lkScriptSrc    :string;
  begin   
    lkScriptName := '';
    with TDBEditEh(TComponent(Sender).Owner)do
      begin
           if(UpperCase(DataField)='SC_REF'     )then begin lkScriptName:='DEFAULT.PS'         ; lkTemplateName := ERP_FILENAME_TEMPLATE_REF         ; end
      else if(UpperCase(DataField)='SC_REF_DLG' )then begin lkScriptName:='DEFAULT_DLG.PS'     ; lkTemplateName := ERP_FILENAME_TEMPLATE_REF_DLG     ; end 
      else if(UpperCase(DataField)='SC_ITEM'    )then begin lkScriptName:='DEFAULT_ITEM.PS'    ; lkTemplateName := ERP_FILENAME_TEMPLATE_REF_ITEM    ; end 
      else if(UpperCase(DataField)='SC_ITEM_DLG')then begin lkScriptName:='DEFAULT_ITEM_DLG.PS'; lkTemplateName := ERP_FILENAME_TEMPLATE_REF_ITEM_DLG; end 
      else if(UpperCase(DataField)='HELPFILE'   )then begin lkScriptName:='DEFAULT.HTML'       ; lkTemplateName := ERP_FILENAME_TEMPLATE_REF_HELP    ; end
      ;
      if(StrTrimAll(lkScriptName) = '')then exit;
      lkScriptDir := TERPForm_ObjId(Owner);
      if(  (Pos('TABL$',UpperCase(lkScriptDir)) = 1)
         or(Pos('PROC$',UpperCase(lkScriptDir)) = 1)
         or(Pos('VIEW$',UpperCase(lkScriptDir)) = 1)
      )then Delete(lkScriptDir, 1, 5);
      if(  (Pos('R_',UpperCase(lkScriptDir)) = 1)
         or(Pos('O_',UpperCase(lkScriptDir)) = 1)
         or(Pos('P_',UpperCase(lkScriptDir)) = 1)
         or(Pos('D_',UpperCase(lkScriptDir)) = 1)
         or(Pos('J_',UpperCase(lkScriptDir)) = 1)
      )then Delete(lkScriptDir, 1, 2);
      lkScriptName:= 'PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(TERPForm_ObjType(Owner))+lkScriptDir+'/'+lkScriptName;
      lkScriptSrc := StringsLoadFromFile(PrepareAbsoleteFileName(lkTemplateName));
      lkScriptSrc := StrReplaceStr(lkScriptSrc, ERP_TEMPLATE_VARIABLE, TERPForm_ObjId(Owner));
      CreateDir( ExtractFilePath( PrepareAbsoleteFileName(lkScriptName) ) );
      StringsSaveToFile( PrepareAbsoleteFileName(lkScriptName), lkScriptSrc );
      if(DataSource.DataSet.State = dsBrowse)then
        DataSource.DataSet.Edit;
      DataSource.DataSet.FieldByName(DataField).AsString := lkScriptName;   
      DataSource.DataSet.Post;  
      end;
  end;  
  //============================================================================
  procedure TERPFormEdtr_tbbScriptEdit_OnClick(Sender :TObject);
  begin
    with TDBEditEh(TComponent(Sender).Owner)do
      Amunhotep.MainForm.ProcessFile(Field.AsString);
  end;  
  //============================================================================
  procedure TERPFormEdtr_tbbScriptRun_OnClick(Sender :TObject);
  begin
    with TDBEditEh(TComponent(Sender).Owner)do
      call(Field.AsString);
  end;    
  //============================================================================
  procedure TERPFormEdtr_actAttrsViewColumns_OnExecute(Sender :TObject);
  begin
    ERP_DBGridEh_ColumnsDialog_Execute(TDBGridEh(TCustomAction(Sender).Owner.FindComponent(obj_name_erp_data_dbgdata+obj_name_erp_objedtr_attrs)));
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAutoDetect_OnExecute(Sender :TObject);
  begin 
    ExecSQL(FBDataBase, 'EXECUTE PROCEDURE PROC$_TB_COLS_CHECK('''+TERPForm_ObjId(TComponent(Sender).Owner)+''') ');
    TERPFormEdtr_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsRename_OnExecute(Sender :TObject);
  var
    lkName    :string;
    lkNameNew :string;
  begin 
    lkName := TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString;
    lkNameNew := lkName;
    if not Dialogs.InputQueryString(TCustomAction(Sender).Caption, TCustomAction(Sender).Hint, lkNameNew)then exit;
    ExecSQL(FBDataBase, 'UPDATE TABL$_TB_COLS C SET C.ID = '''+lkNameNew+''' WHERE (C.TB_ID = '''+TERPForm_ObjId(TComponent(Sender).Owner)+''')AND(C.ID = '''+lkName+''') ');
    TERPFormEdtr_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormEdtr_AccsManage(aOwner:TComponent; const aRoleId:string; const aNewAccs:array of string);
  var
    i     :Integer;
    lkSQL :string;
  begin
    lkSQL := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/ACCESS_UPD.SQL');
    TERPFormEdtr_CloseDataSets(aOwner);
    TERPForm_ExecSQLParams(['isc_tpb_read_committed','isc_tpb_write','isc_tpb_rec_version','isc_tpb_nowait'], lkSQL, ['OBJ_ID', 'OBJ_TYPE', 'ROLE_ID', 'FLAG_SEL', 'FLAG_INS', 'FLAG_UPD', 'FLAG_DEL', 'FLAG_PRINT'], 
      [TERPForm_ObjId(aOwner), IntToStr(TERPForm_ObjType(aOwner)), aRoleId, aNewAccs[0], aNewAccs[1], aNewAccs[2], aNewAccs[3], aNewAccs[4]] );
    TERPFormEdtr_RefreshView(aOwner);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsRoleShr_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner, 
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_accss)).FieldByName('ROLE_ID').AsString,
      ['1','1','1','1','1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsRoleRvk_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner, 
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_accss)).FieldByName('ROLE_ID').AsString,
      ['0','0','0','0','0']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsShareAll_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['1','1','1','1','1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsShareSel_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['1','-1','-1','-1','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsShareIns_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['-1','1','-1','-1','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsShareUpd_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['-1','-1','1','-1','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsShareDel_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['-1','-1','-1','1','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsSharePrn_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['-1','-1','-1','-1','1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsRevokAll_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['0','0','0','0','0']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsRevokSel_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['0','-1','-1','-1','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsRevokIns_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['-1','0','-1','-1','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsRevokUpd_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['-1','-1','0','-1','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsRevokDel_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['-1','-1','-1','0','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAccsRevokPrn_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AccsManage(TComponent(Sender).Owner,'-1', ['-1','-1','-1','-1','0']);
  end;
  //============================================================================
  procedure TERPFormEdtr_AttrsAccsManage(aOwner:TComponent; const aRoleId, aColumnName:string; const aNewAccs:array of string);
  var
    i     :Integer;
    lkSQL :string;
  begin 
    lkSQL := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/COLULMNSACCSS_UPD.SQL');
    TERPFormEdtr_CloseDataSets(aOwner);
    TERPForm_ExecSQLParams(['isc_tpb_read_committed','isc_tpb_write','isc_tpb_rec_version','isc_tpb_nowait'], lkSQL, ['TB_ID', 'ID', 'ROLE_ID', 'FLAG_READ', 'FLAG_WRITE'], 
      [TERPForm_ObjId(aOwner), aColumnName, aRoleId, aNewAccs[0], aNewAccs[1]] );
    TERPFormEdtr_RefreshView(aOwner);
 end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAccsRoleShr_OnExecute(Sender :TObject);
  begin  
    TERPFormEdtr_AttrsAccsManage(TComponent(Sender).Owner, 
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs).FindComponent(obj_name_erp_data_dtschilds+obj_name_erp_objedtr_accss)).FieldByName('ROLE_ID').AsString,
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString,
      ['1','1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAccsRoleRvk_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AttrsAccsManage(TComponent(Sender).Owner, 
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs).FindComponent(obj_name_erp_data_dtschilds+obj_name_erp_objedtr_accss)).FieldByName('ROLE_ID').AsString,
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString,
      ['0','0']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAccsShareAll_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AttrsAccsManage(TComponent(Sender).Owner, '-1',
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString,
      ['1','1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAccsShareSel_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AttrsAccsManage(TComponent(Sender).Owner, '-1',
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString,
      ['1', '-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAccsShareUpd_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AttrsAccsManage(TComponent(Sender).Owner, '-1',
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString,
      ['-1','1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAccsRevokAll_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AttrsAccsManage(TComponent(Sender).Owner, '-1',
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString,
      ['0','0']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAccsRevokSel_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AttrsAccsManage(TComponent(Sender).Owner, '-1',
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString,
      ['0','-1']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsAccsRevokUpd_OnExecute(Sender :TObject);
  begin
    TERPFormEdtr_AttrsAccsManage(TComponent(Sender).Owner, '-1',
      TDataSet(TERPForm_DataSetMain(TComponent(Sender).Owner).FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs)).FieldByName('ID').AsString,
      ['-1','0']);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsFooterIns_OnExecute(Sender :TObject);
  var
    lkDTS :TDataSet;
    lkSQL :string;
  begin 
    lkDTS := TERPForm_DataSetMain(TComponent(Sender).Owner);
    lkDTS := TDataSet(lkDTS.FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs));
    lkSQL := 'INSERT INTO TABL$_TB_COLS_FOOTERS(TB_ID, TC_ID, ID, NAME, FLAG_DELETE, ALIGNMENT, FORMAT, VALUE_TYPE) '+SQLCRLF+
             ' VALUES('''+lkDTS.FieldByName('TB_ID').AsString+''', '''+lkDTS.FieldByName('ID').AsString+
             ''', -1, ''—ÛÏÏ‡:'', 0, 1, ''# ### ### ##0.000'', ''SUM'');'
    ExecSQL(FBDataBase, lkSQL);         
    TERPFormEdtr_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormEdtr_actAttrsFooterDel_OnExecute(Sender :TObject);
  var
    lkDTS :TDataSet;
    lkSQL :string;
  begin   
    lkDTS := TERPForm_DataSetMain(TComponent(Sender).Owner);
    lkDTS := TDataSet(lkDTS.FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_attrs));
    lkDTS := TDataSet(lkDTS.FindComponent(obj_name_erp_data_dtschilds+obj_name_erp_objedtr_footers));
    if(lkDTS.RecordCount = 0)then exit;
    if(Dialogs.MessageDlg(msg_erp_actdel_hint+' "'+lkDTS.FieldByName('ID').AsString+'.'+lkDTS.FieldByName('VALUE_TYPE').AsString+'" ?', mtConfirmation, [mbYes,mbNo]) <> mrYes)then exit;
    lkSQL := 'DELETE FROM TABL$_TB_COLS_FOOTERS F WHERE (F.ID = '''+lkDTS.FieldByName('ID').AsString+''') ';
    ExecSQL(FBDataBase, lkSQL);         
    TERPFormEdtr_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormEdtr_actLinksObjEdit_OnExecute(Sender :TObject);
  var
    lkDTS :TDataSet;
  begin   
    lkDTS := TERPForm_DataSetMain(TComponent(Sender).Owner);
    lkDTS := TDataSet(lkDTS.FindComponent(obj_name_erp_data_dtsdata+obj_name_erp_objedtr_links));
    if(lkDTS.RecordCount = 0)then exit;
    ERP_ObjectEditor(lkDTS.FieldByName('ID').AsString, lkDTS.FieldByName('BASE_TYPE_ID').AsInteger);
  end;   
