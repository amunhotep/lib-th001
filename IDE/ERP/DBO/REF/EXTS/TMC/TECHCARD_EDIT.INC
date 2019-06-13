{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/EXTS/TMC/TECHCARD_EDIT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/EXTS/COMMON.INC}            {$I ../COMMON.INC}                 {$ENDIF} 
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF_LOADCOLUMNS.INC}    {$I ../../FORMREF_LOADCOLUMNS.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/REF/FORMREF.INC}                {$I ../../FORMREF.INC}             {$ENDIF}
//=============== PEAKTOP:IDE/ERP/DBO/REF/EXTS/TMC/TECHCARD_EDIT.INC ===========
const
  msg_acttmclistins        = 'Добавить'; 
  msg_acttmclistins_hint   = 'Добавить в список технологическую карту'; 
  msg_acttmclistdel        = 'Удалить'; 
  msg_acttmclistdel_hint   = 'Удалить из списка технологическую карту'; 
  msg_acttmclistuse        = 'Использовать'; 
  msg_acttmclistuse_hint   = 'Использовать выделенную технологическую карту'; 
  msg_acttmclistclone      = 'Клонировать'; 
  msg_acttmclistclone_hint = 'Создать новую технологическую карту как копию текущей'; 
  msg_acttmcquantins       = 'Добавить'; 
  msg_acttmcquantins_hint  = 'Добавить ТМЦ в технологическую карту'; 
  msg_acttmcquantins2      = 'Несколько'; 
  msg_acttmcquantins2_hint = 'Добавить несколько ТМЦ в технологическую карту'; 
  msg_acttmcquantnew       = 'Создать'; 
  msg_acttmcquantnew_hint  = 'Создать запись в справочнике ТМЦ и добавить в технологическую карту'; 
  msg_acttmcquantdel       = 'Удалить'; 
  msg_acttmcquantdel_hint  = 'Удалить ТМЦ из технологической карты'; 
  msg_acttmcquantupd       = 'Редактировать'; 
  msg_acttmcquantupd_hint  = 'Редактировать ТМЦ'; 
  //============================================================================
  procedure actTMCListIns_OnUpdate(Sender :TObject);
  begin
    with TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet do
      TCustomAction(Sender).Enabled := Active;
  end;
  //============================================================================
  procedure actTMCListIns_OnExecute(Sender :TObject);
  var
    lkID       :string;
  begin 
    lkID := '0';
    with TxFBDataSet( TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet ) do
      begin
      if not Active then exit;
      lkID       := DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString;
      if Active then Close;
      TERPForm_ExecSQL([], 'INSERT INTO TABL$R_TMC_LIST (TMC_ID)VALUES('''+lkID+''')');
      if not Active then Open;
      end;  
  end;
  //============================================================================
  procedure actTMCListClone_OnExecute(Sender :TObject);
  var
    lkSQL      :string;
    lkTechCard :string;
    lkID       :string;
  begin
    lkTechCard := '0';
    lkID       := '0';
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkTechCard := FieldByName('ID').AsString;
      lkID       := DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString;
      if Active then Close;
      lkSQL := 
        'EXECUTE BLOCK AS '+SQLCRLF+
        '  DECLARE VARIABLE PP_TMC_LIST_ID DOMN$INTEGER; '+SQLCRLF+
        '  DECLARE VARIABLE PP_TMC_ID      DOMN$INTEGER; '+SQLCRLF+
        '  DECLARE VARIABLE P_TMC_LIST_ID  DOMN$INTEGER; '+SQLCRLF+
        '  DECLARE VARIABLE P_TMC_ID       DOMN$INTEGER; '+SQLCRLF+
        '  DECLARE VARIABLE P_QUANT        DOMN$FLOAT; '+SQLCRLF+
        '  DECLARE VARIABLE P_NETTO        DOMN$FLOAT; '+SQLCRLF+
        'BEGIN '+SQLCRLF+
        '  PP_TMC_LIST_ID = '''+lkTechCard+'''; '+SQLCRLF+
        '  SELECT FIRST 1 TL.TMC_ID FROM TABL$R_TMC_LIST TL WHERE (TL.ID = :PP_TMC_LIST_ID) INTO :PP_TMC_ID; '+SQLCRLF+
        '  INSERT INTO TABL$R_TMC_LIST(TMC_ID)VALUES(:PP_TMC_ID)RETURNING ID INTO :P_TMC_LIST_ID; '+SQLCRLF+
        '  FOR '+SQLCRLF+
        '    SELECT TQ.TMC_ID, TQ.QUANT, TQ.NETTO '+SQLCRLF+
        '    FROM   TABL$R_TMC_LISTQUANT TQ '+SQLCRLF+
        '    WHERE  (TQ.TMC_LIST_ID = :PP_TMC_LIST_ID) '+SQLCRLF+
        '    INTO   :P_TMC_ID, :P_QUANT, :P_NETTO '+SQLCRLF+
        '  DO '+SQLCRLF+
        '    INSERT INTO TABL$R_TMC_LISTQUANT( '+SQLCRLF+
        '      TMC_LIST_ID, TMC_ID, QUANT, NETTO, NAME '+SQLCRLF+
        '    )VALUES( '+SQLCRLF+
        '      :P_TMC_LIST_ID, :P_TMC_ID, :P_QUANT, :P_NETTO, ''Копия техкарты [''||:PP_TMC_LIST_ID||''] от ''||CURRENT_TIMESTAMP '+SQLCRLF+
        '    ); '+SQLCRLF+
        'END ';
      TERPForm_ExecSQL([], lkSQL);
      if not Active then Open;
      end;  
  end;
  //============================================================================
  procedure actTMCListDel_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin
    with TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet do
      begin
      lkEnabled := Active;
      if(lkEnabled)then
        lkEnabled := (RecordCount > 0);
      end;  
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure actTMCListDel_OnExecute(Sender :TObject);
  var
    lkTechCard :string;
  begin 
    if(Dialogs.MessageDlg(msg_acttmclistdel_hint+' ?', mtConfirmation, [mbYes, mbNo]) <> mrYes)then exit;
    lkTechCard := '0';
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkTechCard := FieldByName('ID').AsString;
      if Active then Close;
      TERPForm_ExecSQL([], 'DELETE FROM TABL$R_TMC_LIST TL WHERE (TL.ID = '''+lkTechCard+''')');
      if not Active then Open;
      end;  
  end;
  //============================================================================
  procedure actTMCListUse_OnExecute(Sender :TObject);
  var
    lkTechCard :string;
    lkID       :string;
  begin  
    lkTechCard := '0';
    lkID       := '0';
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkTechCard := FieldByName('ID').AsString;
      lkID       := DataSource.DataSet.FieldByName(ERP_DATASET_DBKEY).AsString;
      if Active then Close;
      TERPForm_ExecSQL([], 'UPDATE TABL$R_TMC T SET T.TMC_LIST_ID = '''+lkTechCard+''' WHERE (T.ID = '''+lkID+''')');
      if not Active then Open;
      end;  
  end;
  //============================================================================
  procedure actTMCQuantIns_OnExecute(Sender :TObject);
  var
    lkScript   :string;
    lkTechCard :string;
    lkID       :string;
  begin
    lkTechCard := '0';
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkTechCard := FieldByName('ID').AsString;
      end;
    GetField(FBDataBase, 'TABL$_TB', 'SC_REF_DLG', 'ID = '''+TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TABLENAME]+''' ', lkScript);
    SetGlobalVariable(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_BUFFERVAR], 'NULL');
    call(lkScript);
    lkID := GetGlobalVariable(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_BUFFERVAR]);
    if( (StrTrimAll(lkID)='') or (UpperCase(lkID)='NULL'))then exit;
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if Active then Close;
      TERPForm_ExecSQL([], 'INSERT INTO TABL$R_TMC_LISTQUANT (TMC_LIST_ID, TMC_ID, QUANT, NETTO)VALUES('''+lkTechCard+''', '''+lkID+''', 1.000, 1.000)');
      if not Active then Open;
      end;  
  end;
  //============================================================================
  var
    VactTMCQuantIns2_TechCard  :string;
    VactTMCQuantIns2_DTS       :TxFBDataSet;
    VactTMCQuantIns2_RefForm   :TForm;
  //============================================================================
  procedure actTMCQuantIns2_DBGrid_OnDblClick(Sender: TObject);
  var
    LQuant :Extended; 
    LID    :string;
  begin
    with TERPForm_DBGridMain(VactTMCQuantIns2_RefForm).DataSource.DataSet do
    begin
      if not(RecordCount > 0)then exit;
      if(FindField(ERP_DATASET_DBKEY) = nil)then exit;
      LID := FieldByName(ERP_DATASET_DBKEY).AsString
    end;
    LQuant := 1;
    if not Dialogs.InputQueryExtended(msg_acttmcquantins2_hint, 'Введите количество', LQuant) then exit;
    with VactTMCQuantIns2_DTS do
    begin
      if Active then Close;
      TERPForm_ExecSQL([], 'INSERT INTO TABL$R_TMC_LISTQUANT (TMC_LIST_ID, TMC_ID, QUANT, NETTO)VALUES('''+
        VactTMCQuantIns2_TechCard+''', '''+LID+''', '''+StrReplaceStr(FormatFloat('#0.000', LQuant), ',', '.')+''', '''+StrReplaceStr(FormatFloat('#0.000', LQuant), ',', '.')+''')');
      if not Active then Open;
    end;  
  end;
  //============================================================================
  procedure actTMCQuantIns2_DBGrid_OnKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  begin
    if(Shift = [])then
    begin
      if(Key = $0D (*VK_RETURN*) )then actTMCQuantIns2_DBGrid_OnDblClick(Sender); 
    end
    else if(Shift = [ssCtrl])then
    begin
      if(Key = $73 (*VK_F4    *) )then TERPForm_actClose_OnExecute(TComponent(Sender).Owner.FindComponent(obj_name_erp_actclose));
    end;   
  end;
  //============================================================================
  procedure actTMCQuantIns2_OnExecute(Sender :TObject);
  begin
    VactTMCQuantIns2_TechCard := '0';
    VactTMCQuantIns2_DTS := TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet);
    with VactTMCQuantIns2_DTS do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      VactTMCQuantIns2_TechCard := FieldByName('ID').AsString;
      end;
    VactTMCQuantIns2_RefForm := TERPFormGridRef_Create(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TABLENAME], true);
    with TDBGridEh(VactTMCQuantIns2_RefForm.FindComponent(obj_name_erp_data_dbgmain)) do
    begin
      Options     := Options   + [dgRowSelect, dgAlwaysShowSelection] - [dgMultiSelect]; 
      EditActions := EditActions - [geaSelectAllEh];
      OnKeyDown   := @actTMCQuantIns2_DBGrid_OnKeyDown;
      OnDblClick  := @actTMCQuantIns2_DBGrid_OnDblClick;
    end;    
    VactTMCQuantIns2_RefForm.ShowModal;
    VactTMCQuantIns2_RefForm.Free;
  end;
  //============================================================================
  procedure actTMCQuantNew_OnExecute(Sender :TObject);
  var
    lkTechCard     :string;
    lkTMC_GROUP_ID :string;
    lkTMC_GROUP    :string;
    lkSQL          :string;
  begin
    lkTechCard := '0';
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkTechCard := FieldByName('ID').AsString;
      end;
    lkTMC_GROUP_ID := '0';
    SetGlobalVariable('TMC_GROUP_ID', lkTMC_GROUP_ID);
    call('DB:CONFIG/REF/TMC_GROUP/DEFAULT_DLG.PS');
    lkTMC_GROUP_ID := GetGlobalVariable('TMC_GROUP_ID');
    if( (UpperCase(lkTMC_GROUP_ID) = 'NULL') or (lkTMC_GROUP_ID = '0'))then exit;
    GetField(FBDataBase, 'TABL$R_TMC_GROUP', 'NAME', 'ID = '''+lkTMC_GROUP_ID+''' ', lkTMC_GROUP);
    lkSQL := 
      'EXECUTE BLOCK AS '+SQLCRLF+
      '  DECLARE VARIABLE TMC_ID TYPE OF COLUMN TABL$R_TMC.ID; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  INSERT INTO TABL$R_TMC (NAME, NAME2, FLAG_DELETE, FLAG_LOCKED, ARTICLE, '+SQLCRLF+
      '    NUMSHOW, EDIZM_ID, TMC_GROUP_ID, TMC_TYPE_ID, TMC_LIST_ID, TMC_BRAND_ID, '+SQLCRLF+
      '    DEV_TMC_BRAND_ID, COUNTRY_ID, PROBE, LGTH, DIAM, MASSA, MASSA_NETTO, LIMIT, DEV_COUNTRY_ID '+SQLCRLF+
      '  )VALUES ('''+StrReplaceStr(lkTMC_GROUP, '''','"')+''', '''+StrReplaceStr(lkTMC_GROUP, '''','"')+''', 0, 0, '''', '''', 1000000, '''+
      lkTMC_GROUP_ID+''', 2, 0, 0, 0, 0, '''', 0, 0, 0, 0, 0, 0 '+SQLCRLF+
      '  )RETURNING ID INTO :TMC_ID; '+SQLCRLF+
      '  INSERT INTO TABL$R_TMC_LISTQUANT (TMC_LIST_ID, TMC_ID, QUANT, NETTO)VALUES('''+lkTechCard+''', :TMC_ID, 1.000, 1.000); '+SQLCRLF+
      'END';  
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if Active then Close;
      TERPForm_ExecSQL([], lkSQL);
      if not Active then Open;
      end;
  end;
  //============================================================================
  procedure actTMCQuantNew2_OnExecute(Sender :TObject);
  var
    lkTechCard     :string;
    lkTMC_GROUP_ID :string;
    lkTMC_GROUP    :string;
    lkSQL          :string;
  begin
    lkTechCard := '0';
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkTechCard := FieldByName('ID').AsString;
      end;
    lkTMC_GROUP_ID := '0';
    SetGlobalVariable('TMC_GROUP_ID', lkTMC_GROUP_ID);
    call('DB:CONFIG/REF/TMC_GROUP/DLG_PS_150001.PS');
    lkTMC_GROUP_ID := GetGlobalVariable('TMC_GROUP_ID');
    if( (UpperCase(lkTMC_GROUP_ID) = 'NULL') or (lkTMC_GROUP_ID = '0'))then exit;
    GetField(FBDataBase, 'TABL$R_TMC_GROUP', 'NAME', 'ID = '''+lkTMC_GROUP_ID+''' ', lkTMC_GROUP);
    lkSQL := 
      'EXECUTE BLOCK AS '+SQLCRLF+
      '  DECLARE VARIABLE TMC_ID TYPE OF COLUMN TABL$R_TMC.ID; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  INSERT INTO TABL$R_TMC (NAME, NAME2, FLAG_DELETE, FLAG_LOCKED, ARTICLE, '+SQLCRLF+
      '    NUMSHOW, EDIZM_ID, TMC_GROUP_ID, TMC_TYPE_ID, TMC_LIST_ID, TMC_BRAND_ID, '+SQLCRLF+
      '    DEV_TMC_BRAND_ID, COUNTRY_ID, PROBE, LGTH, DIAM, MASSA, MASSA_NETTO, LIMIT, DEV_COUNTRY_ID '+SQLCRLF+
      '  )VALUES ('''+StrReplaceStr(lkTMC_GROUP, '''','"')+''', '''+StrReplaceStr(lkTMC_GROUP, '''','"')+''', 0, 0, '''', '''', 1000000, '''+
      lkTMC_GROUP_ID+''', 1000001, 0, 0, 0, 0, '''', 0, 0, 0, 0, 0, 0 '+SQLCRLF+
      '  )RETURNING ID INTO :TMC_ID; '+SQLCRLF+
      '  INSERT INTO TABL$R_TMC_LISTQUANT (TMC_LIST_ID, TMC_ID, QUANT, NETTO)VALUES('''+lkTechCard+''', :TMC_ID, 1.000, 1.000); '+SQLCRLF+
      'END';  
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet) do
      begin
      if Active then Close;
      TERPForm_ExecSQL([], lkSQL);
      if not Active then Open;
      end;
  end;
  //============================================================================
  procedure actTMCQuantIns_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin
    with TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorList')).DataSource.DataSet do
      begin
      lkEnabled := Active;
      if(lkEnabled)then
        lkEnabled := (RecordCount > 0);
      end;  
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure actTMCQuantDel_OnExecute(Sender :TObject);
  var
    lkID :string;
    lkName :string;
  begin
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorQuant')).DataSource.DataSet) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      lkID   := FieldByName(ERP_DATASET_DBKEY).AsString;
      lkName := FieldByName('TMC_ID').AsString;
      GetField(FBDataBase, 'TABL$R_TMC', 'ID||''. "''||COALESCE(NAME,'''')||''"'' ', 'ID = '+lkName, lkName);
      end;
    if(Dialogs.MessageDlg(msg_acttmcquantdel_hint+' ?'+SQLCRLF+SQLCRLF+lkName, mtConfirmation, [mbYes, mbNo]) <> mrYes)then exit;
    with TxFBDataSet(TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorQuant')).DataSource.DataSet) do
      begin
      if DataSource.DataSet.Active then
        DataSource.Dataset.Close;
      TERPForm_ExecSQL([], 'DELETE FROM TABL$R_TMC_LISTQUANT TQ WHERE (TQ.ID = '''+lkID+''')');
      if not DataSource.DataSet.Active then
        DataSource.DataSet.Open;
      end;
  end;
  //============================================================================
  procedure actTMCQuantDel_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin
    with TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorQuant')).DataSource.DataSet do
      begin
      lkEnabled := Active;
      if(lkEnabled)then
        lkEnabled := (RecordCount > 0);
      end;  
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure actTMCQuantUpd_OnExecute(Sender :TObject);
  var
    lkVariable :string;
  begin
    lkVariable := TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_BUFFERVAR];
    with TDBGridEh(TComponent(Sender).Owner.FindComponent(obj_name_erp_data_dbgchilds+'CardEditorQuant')).DataSource.DataSet do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      SetGlobalVariable(lkVariable, FieldByName(lkVariable).AsString);
      call(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_ITEM_SCRIPT]);
      end;
  end;
  //============================================================================
  procedure TERPFormGridRefTMC_ExtTechCardEdit_dtsChildCardEditorList_AfterClose(DataSet :TDataSet);
  begin
    if ObjectInheritsFrom(DataSet, 'TxFBCustomDataSet') then
      with TxFBCustomDataSet(DataSet) do
        if Transaction.InTransaction then
          Transaction.Commit;
  end;
  //============================================================================
  procedure TERPFormGridRefTMC_ExtTechCardEdit_DataSet_AfterOpen(DataSet :TDataSet);
  begin
    TERPForm_OpenDataSetsChilds(DataSet);
    if(DataSet.Tag <> 0)then
      begin
      DataSet.RecNo := DataSet.Tag;
      DataSet.Tag   := 0;
      end; 
  end;
  //============================================================================
  procedure TERPFormGridRefTMC_ExtTechCardEdit_DataSet_BeforeClose(DataSet :TDataSet);
  begin
    DataSet.Tag := DataSet.RecNo; 
    TERPForm_CloseDataSetsChilds(DataSet);
  end;
  //============================================================================
  procedure TERPFormGridRefTMC_ExtTechCardEdit_Create(aOwner, aParent :TComponent; aMasterDataSet :TDataSet);
  var
    lkTS            :TxcTabSheet;
    lkTr            :TxFBTransaction;
    lkSplt          :TSplitter;
    lkPnlLeft       :TxcPanel;
    lkPnlClient     :TxcPanel;
    lkToolBarLeft   :TxcGradientPanelVista;
    lkToolBarClient :TxcGradientPanelVista;
    lkDataSetList   :TxFBDataSet; 
    lkDSList        :TDataSource; 
    lkDBGList       :TDBGridEh;          
    lkDataSetQuant  :TxFBDataSet; 
    lkDSQuant       :TDataSource; 
    lkDBGQuant      :TDBGridEh; 
    lkCol           :TColumnEh; 
    lkAct           :TCustomAction;
    lkSQLSelect, lkSQLRefresh, lkSQLInsert, lkSQLUpdate, lkSQLDelete, lkSelectFilter :string;       
    lkTrTemp        :TxFBTransaction;
    lkQrTemp        :TxFBQuery;
    lkDSTemp        :TDataSource;
    i               :Integer;
  begin
    ExecSQL(FBDataBase, 
      'EXECUTE BLOCK AS BEGIN '+SQLCRLF+
      '  IF(NOT(EXISTS( '+SQLCRLF+
      '          SELECT RF.RDB$FIELD_ID '+SQLCRLF+
      '          FROM   RDB$RELATION_FIELDS RF '+SQLCRLF+
      '          WHERE  (TRIM(RF.RDB$RELATION_NAME) = ''TABL$R_TMC_LISTQUANT'') '+SQLCRLF+
      '            AND  (TRIM(RF.RDB$FIELD_NAME)    = ''NETTO'') '+SQLCRLF+
      '  )))THEN  EXECUTE STATEMENT ''ALTER TABLE TABL$R_TMC_LISTQUANT ADD NETTO DOMN$FLOAT;''; '+SQLCRLF+
      'END '
    );
    if(aParent.FindComponent(obj_name_erp_tabsheetextension+'TechCard') <> nil)then 
      with TxcTabSheet(aParent.FindComponent(obj_name_erp_tabsheetextension+'TechCard')) do
        begin
        PageControl.ActivePageIndex := PageIndex;
        exit;
        end;
    DontAutoFree;
    lkTS := TxcTabSheet.Create(aParent);
    with lkTS do
      begin
      Name        := obj_name_erp_tabsheetextension+'TechCard';
      Parent      := TxcPageControlEx(aParent);
      PageControl := TxcPageControlEx(aParent);
      Caption     := 'Редактор тех.карт';
      ImageIndex  := 390;
      Color       := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      PageIndex   := 0;
      end;
    lkPnlLeft       := CreateTxcPanel(lkTS, lkTS, obj_name_erp_panelleft, '', alLeft, 0,0,200,340, xbsNone);
    lkSplt          := CreateTSplitter(lkTS, lkTS, '', alLeft, lkPnlLeft.Left+lkPnlLeft.Width+4, 0, 400, 4);
    lkPnlClient     := CreateTxcPanel(lkTS, lkTS, obj_name_erp_panelclient, '', alClient, lkSplt.Left+lkSplt.Width+4,0,200,400, xbsNone);
    lkToolBarLeft   := CreateTxcGradientPanelVistaToolBar(lkTS,lkPnlLeft  ,obj_name_erp_toolbar+'Left'  ,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth, 200,xbsNone);
    lkToolBarClient := CreateTxcGradientPanelVistaToolBar(lkTS,lkPnlClient,obj_name_erp_toolbar+'Client','',alTop, 0,0,TERPForm_DefaultToolButtonWidth, 200,xbsNone);
    lkTr := TxFBTransaction.Create(aOwner);
    with lkTr do
      begin
      Name            := TERPForm_TransactionMain(aOwner).Name + 'TechCard';
      DefaultDataBase := TERPForm_TransactionMain(aOwner).DefaultDataBase;
      Params.Text     := TERPForm_TransactionMain(aOwner).Params.Text;
      end;
    lkDataSetList := TxFBDataSet.Create(aMasterDataSet);
    with lkDataSetList do
      begin
      Name           := obj_name_erp_data_qrchilds+'CardEditorList';
      Transaction    := lkTr;
      DataSource     := TDataSource(aMasterDataSet.FindComponent('DataSource'+aMasterDataSet.Name));
      AfterOpen      := @TERPFormGridRefTMC_ExtTechCardEdit_DataSet_AfterOpen;
      BeforeClose    := @TERPFormGridRefTMC_ExtTechCardEdit_DataSet_BeforeClose;
      AfterClose     := @TERPFormGridRefTMC_ExtTechCardEdit_dtsChildCardEditorList_AfterClose;
      SelectSQL.Text := 
        'SELECT  TL.TMC_ID AS '+ERP_DATASET_DBKEY+', TL.TMC_ID, TL.ID, TL.NAME, TL.FLAG_DELETE, TL.DATE_CREATE '+SQLCRLF+
        '       ,(SELECT COUNT(TM.ID) FROM TABL$R_TMC TM '+SQLCRLF+
        '         WHERE (TM.ID = TL.TMC_ID)AND(TM.TMC_LIST_ID = TL.ID)) AS FLAG_DEFAULT '+SQLCRLF+
        'FROM   TABL$R_TMC_LIST TL '+SQLCRLF+
        'WHERE  (TL.TMC_ID = ?'+ERP_DATASET_DBKEY+') '+SQLCRLF+
        'ORDER BY TL.ID ';  
      end;
    lkDSList := TDataSource.Create(lkDataSetList);
    with lkDSList do
      begin
      DataSet := lkDataSetList;
      Name    := 'DataSource'+lkDataSetList.Name;
      end;
    lkDBGList := CreateTDBGridEh(aOwner, lkPnlLeft, lkDSList, obj_name_erp_data_dbgchilds+'CardEditorList', 0,0,200,200, alClient);  
    with lkDBGList do
      begin
      HelpKeyWord    := '1';
      FooterRowCount := 1;
      Options        := [dgTitles,dgColumnResize,dgColLines,dgRowLines,dgTabs,dgRowSelect,dgAlwaysShowSelection,dgConfirmDelete,dgCancelOnExit];
      SumList.Active := true;
      end;
    lkCol := CreateTColumnEh(lkDBGList,'ID'          ,'# ### ##0','Тех.карта|Код' , 60,taRightJustify);
    with lkCol.Footer do
      begin
      DisplayFormat := lkCol.DisplayFormat;
      Alignment     := lkCol.Alignment;
      FieldName     := lkCol.FieldName;
      ValueType     := fvtCOUNT;
      end;
    lkCol := CreateTColumnEh(lkDBGList,'FLAG_DEFAULT',''         ,'Тех.карта|Исп.', 20,taLeftJustify);
    with lkCol do
      begin
      AlwaysShowEditButton := false;
      KeyList.Text  := '1'+SQLCRLF+'0';
      PickList.Text := 'X'+SQLCRLF+' ';
      Checkboxes    := true;
      end; 
    lkCol := CreateTColumnEh(lkDBGList,'DATE_CREATE' ,'dd.mm.yyyy hh:nn:ss','Тех.карта|Дата',120,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBGList,'NAME'        ,''                   ,'Тех.карта|Примечание',120,taLeftJustify);

    lkDataSetQuant := TxFBDataSet.Create(lkDataSetList);
    with lkDataSetQuant do
      begin
      Name           := obj_name_erp_data_qrchilds+'CardEditorQuant';
      Transaction    := lkDataSetList.Transaction;
      DataSource     := lkDSList;
      AfterOpen      := @TERPFormGridRefTMC_ExtTechCardEdit_DataSet_AfterOpen;
      BeforeClose    := @TERPFormGridRefTMC_ExtTechCardEdit_DataSet_BeforeClose;
      end;
    lkDSQuant := TDataSource.Create(lkDataSetQuant);
    with lkDSQuant do
      begin
      DataSet := lkDataSetQuant;
      Name    := 'DataSource'+lkDataSetQuant.Name;
      end;
    lkDBGQuant := CreateTDBGridEh(aOwner, lkPnlClient, lkDSQuant, obj_name_erp_data_dbgchilds+'CardEditorQuant', 0,0,200,200, alClient);  
    with lkDBGQuant do
      begin
      HelpKeyWord    := '1';
      FooterRowCount := 1;
      AllowedOperations := [alopUpdateEh]
      SumList.Active := true;
      OnDblClick     := @actTMCQuantUpd_OnExecute;
      end;
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTrTemp, lkQrTemp, lkDSTemp);  
    TERPFormGrid_LoadDBGridColumns('TABL$R_TMC_LISTQUANT', lkQrTemp, lkDBGQuant, nil, true, false, 'TMC_LIST_ID', lkSQLSelect, lkSQLRefresh, lkSQLInsert, lkSQLUpdate, lkSQLDelete, lkSelectFilter);      
    if lkTrTemp.InTransaction then
      lkTrTemp.Commit;
    lkTrTemp.Free;
    for i:=0 to lkDBGQuant.Columns.Count-1 do
      begin
      if(AnsiUpperCase(lkDBGQuant.Columns[i].FieldName) = 'TMC_TMC_LIST_ID')then
        begin
        lkDBGQuant.Columns[i].KeyList.Text     := '0'+#13#10+'1';
        lkDBGQuant.Columns[i].PickList.Text    := 'T'+#13#10+'K';
        lkDBGQuant.Columns[i].ImageList        := CreateTImageList(lkDBGQuant, 'ilTMCLitId', [13,14]);
        lkDBGQuant.Columns[i].NotInKeyListIndex:= 1;
        end;
      end;
    with lkDBGQuant do
      begin
      SumList.Active := True;
      end;
    with lkDataSetQuant do
      begin
      SelectSQL.Text  := lkSQLSelect+' AND ('+ERP_SQL_TABLEPREFIX+'.TMC_LIST_ID = ?ID)'+SQLCRLF;
      RefreshSQL.Text := lkSQLRefresh;
      InsertSQL.Text  := lkSQLInsert;
      ModifySQL.Text  := lkSQLUpdate;
      DeleteSQL.Text  := lkSQLDelete;
      end;
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCListIns'  ,msg_acttmclistins  ,msg_acttmclistins_hint  ,'',0,176,@actTMCListIns_OnExecute  ,@actTMCListIns_OnUpdate ,lkToolBarLeft,72,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCListClone',msg_acttmclistclone,msg_acttmclistclone_hint,'',0, 68,@actTMCListClone_OnExecute,@actTMCListDel_OnUpdate ,lkToolBarLeft,88,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCListUse'  ,msg_acttmclistuse  ,msg_acttmclistuse_hint  ,'',0,391,@actTMCListUse_OnExecute  ,@actTMCListDel_OnUpdate ,lkToolBarLeft,96,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCListDel'  ,msg_acttmclistdel  ,msg_acttmclistdel_hint  ,'',0,177,@actTMCListDel_OnExecute  ,@actTMCListDel_OnUpdate ,lkToolBarLeft,68,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCQuantIns' ,msg_acttmcquantins ,msg_acttmcquantins_hint ,'',0,176,@actTMCQuantIns_OnExecute ,@actTMCQuantIns_OnUpdate,lkToolBarClient,72,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCQuantIns2',msg_acttmcquantins2,msg_acttmcquantins2_hint,'',0,176,@actTMCQuantIns2_OnExecute,@actTMCQuantIns_OnUpdate,lkToolBarClient,72,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCQuantNew' ,msg_acttmcquantnew ,msg_acttmcquantnew_hint ,'',0,181,@actTMCQuantNew_OnExecute ,@actTMCQuantIns_OnUpdate,lkToolBarClient,64,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCQuantNew2','2'                ,msg_acttmcquantnew_hint ,'',0,181,@actTMCQuantNew2_OnExecute,@actTMCQuantIns_OnUpdate,lkToolBarClient,28,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCQuantDel' ,msg_acttmcquantdel ,msg_acttmcquantdel_hint ,'',0,177,@actTMCQuantDel_OnExecute ,@actTMCQuantDel_OnUpdate,lkToolBarClient,68,nil);
    lkAct := TERPForm_CreateAction2(aOwner,'actReferenceTMCQuantUpd' ,msg_acttmcquantupd ,msg_acttmcquantupd_hint ,'',0,390,@actTMCQuantUpd_OnExecute ,@actTMCQuantDel_OnUpdate,lkToolBarClient,96,nil);
    ERP_DBGridEh_StdActions_Create(lkDBGQuant, [erpGrid, erpGridNavigation, erpGridExport], lkToolBarClient, nil);
  end;  
