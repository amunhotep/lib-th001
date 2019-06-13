{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                 {$I PEAKTOP:GLOBAL_VARIABLES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}{$I ../../USERS/GLOBALVARIABLES.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBOX.INC}                  {$I PEAKTOP:OBJ/TXCGROUPBOX.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                    {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                    {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}        {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}             {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                 {$I PEAKTOP:OBJ/TXFBDATASETS.INC}            {$ENDIF}
const //============== PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC ==================
  ERP_FILENAME_SQL_INPUT_REF       = 'PEAKTOP:IDE/ERP/DBO/SQL/INPUT/02_';
  INPUTINTF_REF_OBJNAME_TRANS      = 'Transaction';  
  INPUTINTF_REF_OBJNAME_DATASET    = 'DataSet';  
  INPUTINTF_REF_OBJNAME_DATASOURCE = 'DataSource';  
  INPUTINTF_REF_OBJNAME_DBGRID     = 'DBGrid';  
  InputIntf_Ref_DefaultMinHeight       = 136;
  InputIntf_Ref_DefaultToolButtonWidth =  24;
  //============================================================================
  procedure InputIntf_Ref_ExecSQL(const aSQL:string);
  begin
    ExecSQL(FBDataBase, aSQL);  
  end;
  //============================================================================
  procedure InputIntf_Ref_CloseDataSets(aOwner:TComponent);
  begin
    with TxFBTransaction(aOwner.FindComponent(INPUTINTF_REF_OBJNAME_TRANS))do
      begin
      with TxFBDataSet(FindComponent(INPUTINTF_REF_OBJNAME_DATASET)) do
        if Active then
          begin
          DisableControls;
          if(State <> dsBrowse)then
            try Post; except Cancel; end;
          Close;
          end;
      if InTransaction then 
        Commit;    
      end;    
  end;
  //============================================================================
  procedure InputIntf_Ref_Refresh(aOwner:TComponent);
  begin
    InputIntf_Ref_CloseDataSets(aOwner);
    with TxFBTransaction(aOwner.FindComponent(INPUTINTF_REF_OBJNAME_TRANS))do
      with TxFBDataSet(FindComponent(INPUTINTF_REF_OBJNAME_DATASET)) do
        begin
        Prepare;
        ParamByName('PQ_OBJECT_GUID').AsString := TxcGroupBox(aOwner).HelpKeyWord;
        ParamByName('PQ_OBJECT_NAME').AsString := TDBGridEh(aOwner.FindComponent(INPUTINTF_REF_OBJNAME_DBGRID)).HelpKeyWord;
        ParamByName('PQ_USER_VAR'   ).AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
        try Open; finally FetchAll; end; 
        EnableControls;
        end;
  end;
  //============================================================================
  function InputIntf_Ref_GetIds(aOwner:TComponent):string;
  var
    lkRecNo :Integer;
  begin
    Result := '~';
    lkRecNo := 0;
    with TxFBTransaction(aOwner.FindComponent(INPUTINTF_REF_OBJNAME_TRANS))do
      with TxFBDataSet(FindComponent(INPUTINTF_REF_OBJNAME_DATASET)) do
        if Active then
          begin
          if(State = dsEdit)then
            try 
              Post;
            except
              Cancel;
            end;
          lkRecNo := RecNo;  
          DisableControls;
          First;
          while not EOF do
            begin
            if(FieldByName('FLAG_DELETE').AsInteger <> 0)then
              Result := Result + FieldByName('ID').AsString + '~';
            Next;
            end;
          if(lkRecNo > 0)then
            RecNo := lkRecNo;  
          EnableControls;
          end;
  end;
  //============================================================================
  procedure InputIntf_Ref_SetIds(aOwner:TComponent; const aValues:string);
  var
    lkSQL   :string;
  begin
    lkSQL := 
      'EXECUTE BLOCK AS '+SQLCRLF+
      '  DECLARE VARIABLE P_OBJECT_ID TYPE OF COLUMN TABL$_BUFFER.NAME; '+SQLCRLF+
      '  DECLARE VARIABLE P_ID        TYPE OF COLUMN TABL$_BUFFER.OBJ_ID; '+SQLCRLF+
      '  DECLARE VARIABLE P_B_ID      TYPE OF COLUMN TABL$_BUFFER.ID; '+SQLCRLF+
      '  DECLARE VARIABLE P_SQL_STMT  DOMN$BLOB_SQL; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  P_OBJECT_ID = '''+TDBGridEh(aOwner.FindComponent(INPUTINTF_REF_OBJNAME_DBGRID)).HelpKeyWord+'''; '+SQLCRLF+ 
      '  P_SQL_STMT  = ''SELECT T1.ID FROM ''||:P_OBJECT_ID||'' T1 ORDER BY T1.ID ''; '+SQLCRLF+
      '  FOR EXECUTE STATEMENT :P_SQL_STMT INTO :P_ID DO '+SQLCRLF+
      '    BEGIN '+SQLCRLF+
      '    UPDATE OR INSERT INTO TABL$_BUFFER(NAME, FLAG_DELETE, USER_ID, OBJ_NAME, OBJ_ID) '+SQLCRLF+
      '      VALUES('''+TxcGroupBox(aOwner).HelpKeyWord+''', 0, '''+
      GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''', :P_OBJECT_ID, :P_ID) '+SQLCRLF+
      '      MATCHING(NAME, USER_ID, OBJ_NAME, OBJ_ID) '+SQLCRLF+
      '      RETURNING ID INTO :P_B_ID; '+SQLCRLF+
      '    IF('''+aValues+''' CONTAINING ''~''||:P_ID||''~'')THEN '+SQLCRLF+
      '      UPDATE TABL$_BUFFER B SET B.FLAG_DELETE = 1 WHERE (B.ID = :P_B_ID); '+SQLCRLF+
      '    END '+SQLCRLF+
      'END';
    InputIntf_Ref_CloseDataSets(aOwner);  
    InputIntf_Ref_ExecSQL(lkSQL);  
    InputIntf_Ref_Refresh(aOwner);
  end;
  //============================================================================
  function InputIntf_Ref_GetIds_Comma(aOwner:TComponent):string;
  begin
    Result := InputIntf_Ref_GetIds(aOwner);
    Delete(Result, 1,1);
    if(Length(Result) = 0)then exit;
    Result := StrReplaceStr(Result, '~', ',');
    Delete(Result, Length(Result), 1);
  end;
  //============================================================================
  function InputIntf_Ref_GetNames(aOwner:TComponent):string;
  var
    lkRecNo :Integer;
  begin
    Result := '';
    lkRecNo := 0;
    with TxFBTransaction(aOwner.FindComponent(INPUTINTF_REF_OBJNAME_TRANS))do
      with TxFBDataSet(FindComponent(INPUTINTF_REF_OBJNAME_DATASET)) do
        if Active then
          begin
          if(State = dsEdit)then
            try 
              Post;
            except
              Cancel;
            end;
          lkRecNo := RecNo;  
          DisableControls;
          First;
          while not EOF do
            begin
            if(FieldByName('FLAG_DELETE').AsInteger <> 0)then
              Result := Result + FieldByName('NAME').AsString + ', ';
            Next;
            end;
          if(lkRecNo > 0)then
            RecNo := lkRecNo;  
          EnableControls;
          end;
  end;
  //============================================================================
  procedure InputIntf_Ref_actRefresh_OnExecute(Sender :TObject);
  begin
    InputIntf_Ref_Refresh(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure InputIntf_Ref_actSelect_OnExecute(Sender :TObject);
  var
    lkSQL :string;
  begin
    lkSQL := '';
    with TxFBTransaction(TComponent(Sender).Owner.FindComponent(INPUTINTF_REF_OBJNAME_TRANS))do
      with TxFBDataSet(FindComponent(INPUTINTF_REF_OBJNAME_DATASET)) do
        if Active then
          lkSQL := 'UPDATE TABL$_BUFFER B SET B.FLAG_DELETE = IIF(B.FLAG_DELETE=0, 1, 0) WHERE (B.ID = '''+FieldByName('B_ID').AsString+''') ';
    if(lkSQL<>'')then 
      begin
//      InputIntf_Ref_CloseDataSets(TComponent(Sender).Owner);  
      ExecSQL(FBDataBase, lkSQL);        
      InputIntf_Ref_Refresh(TComponent(Sender).Owner);
      end;
  end;
  //============================================================================
  procedure InputIntf_Ref_actSelectAll_OnExecute(Sender :TObject);
  var
    lkRecNo :Integer;
  begin
    lkRecNo := 0;
    with TxFBTransaction(TComponent(Sender).Owner.FindComponent(INPUTINTF_REF_OBJNAME_TRANS))do
      with TxFBDataSet(FindComponent(INPUTINTF_REF_OBJNAME_DATASET)) do
        if Active then
          begin
          if(State = dsEdit)then
            try 
              Post;
            except
              Cancel;
            end;
          lkRecNo := RecNo;  
          DisableControls;  
          First;
          while not EOF do
            begin
            Edit;
            FieldByName('FLAG_DELETE').AsInteger := 1;
            Post;
            Next;
            end;
          if(lkRecNo > 0)then
            RecNo := lkRecNo;  
          EnableControls;    
          end;
    InputIntf_Ref_Refresh(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure InputIntf_Ref_actUnSelectAll_OnExecute(Sender :TObject);
  var
    lkRecNo :Integer;
  begin
    lkRecNo := 0;
    with TxFBTransaction(TComponent(Sender).Owner.FindComponent(INPUTINTF_REF_OBJNAME_TRANS))do
      with TxFBDataSet(FindComponent(INPUTINTF_REF_OBJNAME_DATASET)) do
        if Active then
          begin
          if(State = dsEdit)then
            try 
              Post;
            except
              Cancel;
            end;
          lkRecNo := RecNo;  
          DisableControls;  
          First;
          while not EOF do
            begin
            Edit;
            FieldByName('FLAG_DELETE').AsInteger := 0;
            Post;
            Next;
            end;
          if(lkRecNo > 0)then
            RecNo := lkRecNo;  
          EnableControls;    
          end;
    InputIntf_Ref_Refresh(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure InputIntf_Ref_actInsert_OnExecute(Sender :TObject);
  var
    lkRefName :string;
    lkBuffVar :string;
    lkScName  :string;
    lkID      :string;
    lkSQL     :string;
  begin
    lkRefName := TDBGridEh(TComponent(Sender).Owner.FindComponent(INPUTINTF_REF_OBJNAME_DBGRID)).HelpKeyWord; 
    GetField(FBDataBase,'TABL$_TB','BUFFER_VAR','ID = '''+lkRefName+''' ',lkBuffVar);
    GetField(FBDataBase,'TABL$_TB','SC_REF_DLG','ID = '''+lkRefName+''' ',lkScName );
    lkID := 'NULL';
    SetGlobalVariable(lkBuffVar, lkID);
    call(lkScName);
    lkID := GetGlobalVariable(lkBuffVar);
    if( (StrTrimAll(lkID)='') or (lkID='NULL') )then exit;
    lkSQL := 'INSERT INTO TABL$_BUFFER(NAME, FLAG_DELETE, USER_ID, OBJ_NAME, OBJ_ID) '+
             'VALUES('''+TxcGroupBox(TComponent(Sender).Owner).HelpKeyWord+''', 1, '''+
                GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''','''+lkRefName+''','''+lkID+''')';
    ExecSQL(FBDataBase, lkSQL);  
    InputIntf_Ref_Refresh(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure InputIntf_Ref_actInsertAll_OnExecute(Sender :TObject);
  var
    lkSQL :string;
  begin
    lkSQL := 
      'EXECUTE BLOCK AS '+SQLCRLF+
      '  DECLARE VARIABLE P_OBJECT_ID TYPE OF COLUMN TABL$_BUFFER.NAME; '+SQLCRLF+
      '  DECLARE VARIABLE P_ID        TYPE OF COLUMN TABL$_BUFFER.OBJ_ID; '+SQLCRLF+
      '  DECLARE VARIABLE P_SQL_STMT  DOMN$BLOB_SQL; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  P_OBJECT_ID = '''+TDBGridEh(TComponent(Sender).Owner.FindComponent(INPUTINTF_REF_OBJNAME_DBGRID)).HelpKeyWord+'''; '+SQLCRLF+ 
      '  P_SQL_STMT  = ''SELECT T1.ID FROM ''||:P_OBJECT_ID||'' T1 ORDER BY T1.ID ''; '+SQLCRLF+
      '  FOR EXECUTE STATEMENT :P_SQL_STMT INTO :P_ID DO '+SQLCRLF+
      '    UPDATE OR INSERT INTO TABL$_BUFFER(NAME, FLAG_DELETE, USER_ID, OBJ_NAME, OBJ_ID) '+SQLCRLF+
      '      VALUES('''+TxcGroupBox(TComponent(Sender).Owner).HelpKeyWord+''', 0, '''+
      GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''', :P_OBJECT_ID, :P_ID) '+SQLCRLF+
      '      MATCHING(NAME, USER_ID, OBJ_NAME, OBJ_ID); '+SQLCRLF+
      'END';
    InputIntf_Ref_CloseDataSets(TComponent(Sender).Owner);  
    ExecSQL(FBDataBase, lkSQL);  
    InputIntf_Ref_Refresh(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure InputIntf_Ref_actDelete_OnExecute(Sender :TObject);
  var
    lkSQL :string;
  begin
    lkSQL := '';
    with TxFBTransaction(TComponent(Sender).Owner.FindComponent(INPUTINTF_REF_OBJNAME_TRANS))do
      with TxFBDataSet(FindComponent(INPUTINTF_REF_OBJNAME_DATASET)) do
        if Active then
          lkSQL := 'DELETE FROM TABL$_BUFFER B WHERE (B.ID = '''+FieldByName('B_ID').AsString+''') ';
    if(lkSQL<>'')then 
      begin
//      InputIntf_Ref_CloseDataSets(TComponent(Sender).Owner);  
      ExecSQL(FBDataBase, lkSQL);        
      InputIntf_Ref_Refresh(TComponent(Sender).Owner);
      end;
  end;
  //============================================================================
  procedure InputIntf_Ref_actDeleteAll_OnExecute(Sender :TObject);
  var
    lkSQL :string;
  begin
    lkSQL := 'DELETE FROM TABL$_BUFFER B WHERE (B.NAME = '''+TxcGroupBox(TComponent(Sender).Owner).HelpKeyWord+''')AND(B.OBJ_NAME = '''+
              TDBGridEh(TComponent(Sender).Owner.FindComponent(INPUTINTF_REF_OBJNAME_DBGRID)).HelpKeyWord+''') AND (B.USER_ID = '''+
              GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''')';
    InputIntf_Ref_CloseDataSets(TComponent(Sender).Owner);  
    ExecSQL(FBDataBase, lkSQL);  
    InputIntf_Ref_Refresh(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure InputIntf_Ref_DataSet_AfterOpen(DataSet :TDataSet);
  begin
//    if( (DataSet.Tag<>0) and (DataSet.RecordCount>0) )then
//      DataSet.RecNo := DataSet.Tag;
//    DataSet.Tag := 0;  
    TDBGridEh(DataSet.Owner.Owner.FindComponent(INPUTINTF_REF_OBJNAME_DBGRID)).RestoreBookmark; 
  end;
  //============================================================================
  procedure InputIntf_Ref_DataSet_BeforeClose(DataSet :TDataSet);
  begin
    //DataSet.Tag := DataSet.RecNo;
    TDBGridEh(DataSet.Owner.Owner.FindComponent(INPUTINTF_REF_OBJNAME_DBGRID)).SaveBookmark; 
  end;
  //============================================================================
  procedure InputIntf_Ref_DBGrid_OnCellClick(Column : TColumnEh);
  begin
    InputIntf_Ref_actSelect_OnExecute(Column.Grid);  
  end;
  //============================================================================
  function InputIntf_Ref_Create(aOwner:TComponent; aParent:TWinControl; const aName, aCaption:string; const aLeft, aTop, aHeight, aWidth:Integer;
             const aRefName, aReportGUID :string):TxcGroupBox;
  var
    lkToolBar :TxcGradientPanelVista;
    lkTr      :TxFBTransaction;
    lkDTS     :TxFBDataSet;
    lkDS      :TDataSource;
    lkDBG     :TDBGridEh;
    lkCol     :TColumnEh;
    lkFileName:string;
  begin
    Result := CreateTxcGroupBox(aOwner, aParent, aName, aCaption,alNone,aLeft,aTop,MaxInteger(aHeight,InputIntf_Ref_DefaultMinHeight),aWidth);
    Result.HelpKeyWord := aReportGUID;
    lkToolBar := CreateTxcGradientPanelVistaToolBar(aOwner,Result,'','',alTop,0,0,24,600,xbsRaized);
    CreateTxFBTransDataSet(Result,INPUTINTF_REF_OBJNAME_TRANS,INPUTINTF_REF_OBJNAME_DATASET,INPUTINTF_REF_OBJNAME_DATASOURCE, ['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);
    with lkDTS do
      begin
      Tag         := 0;
      AfterOpen   := @InputIntf_Ref_DataSet_AfterOpen;
      BeforeClose := @InputIntf_Ref_DataSet_BeforeClose;
      end;  
    lkDBG := CreateTDBGridEh(Result,Result,lkDS,INPUTINTF_REF_OBJNAME_DBGRID, 0,lkToolBar.Top+lkToolBar.Height+1,200,200,alClient);
    with lkDBG do
      begin
      HelpKeyWord  := aRefName;
      Options      := Options   + [dgRowSelect, dgAlwaysShowSelection] - [dgIndicator];  
      OptionsEh    := OptionsEh 
                      + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghColumnMove, dghExtendVertLines] 
                      - [dghAutoSortMarking, dghMultiSortMarking];
      VTitleMargin := 4;
      AllowedOperations := [alopUpdateEh];
      OnCellClick       := @InputIntf_Ref_DBGrid_OnCellClick;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBG,'FLAG_DELETE','','X'           , 16,taLeftJustify); lkCol.Checkboxes := true;
    lkCol := CreateTColumnEh(lkDBG,'ID'         ,'','код'         , 72,taLeftJustify);
    lkCol := CreateTColumnEh(lkDBG,'NAME'       ,'','имя элемента',220,taLeftJustify);
    with CreateTxcToolBarButton(Result,lkToolBar,'tbbRefresh'    ,'Обновить'    ,'Обновить список'                ,(lkToolBar.ControlCount * InputIntf_Ref_DefaultToolButtonWidth)+1,1,lkToolBar.Height-2,InputIntf_Ref_DefaultToolButtonWidth,alLeft,170,nil)do
      OnClick := @InputIntf_Ref_actRefresh_OnExecute;
    with CreateTxcToolBarButton(Result,lkToolBar,'tbbSelectAll'  ,'Выбрать все' ,'Выбрать все элементы для отчета',(lkToolBar.ControlCount * InputIntf_Ref_DefaultToolButtonWidth)+1,1,lkToolBar.Height-2,InputIntf_Ref_DefaultToolButtonWidth,alLeft,300,nil)do
      OnClick := @InputIntf_Ref_actSelectAll_OnExecute;                     
    with CreateTxcToolBarButton(Result,lkToolBar,'tbbUnSelectAll','Очистить'    ,'Очистить выбранные элементы'    ,(lkToolBar.ControlCount * InputIntf_Ref_DefaultToolButtonWidth)+1,1,lkToolBar.Height-2,InputIntf_Ref_DefaultToolButtonWidth,alLeft,299,nil)do
      OnClick := @InputIntf_Ref_actUnSelectAll_OnExecute;
    with CreateTxcToolBarButton(Result,lkToolBar,'tbbInsert'     ,'Добавить'    ,'Добавить элемент в список'      ,(lkToolBar.ControlCount * InputIntf_Ref_DefaultToolButtonWidth)+1,1,lkToolBar.Height-2,InputIntf_Ref_DefaultToolButtonWidth,alLeft,176,nil)do
      OnClick := @InputIntf_Ref_actInsert_OnExecute;
    with CreateTxcToolBarButton(Result,lkToolBar,'tbbInsertAll'  ,'Добавить все','Добавить все элементы в список' ,(lkToolBar.ControlCount * InputIntf_Ref_DefaultToolButtonWidth)+1,1,lkToolBar.Height-2,InputIntf_Ref_DefaultToolButtonWidth,alLeft, 82,nil)do
      OnClick := @InputIntf_Ref_actInsertAll_OnExecute;
    with CreateTxcToolBarButton(Result,lkToolBar,'tbbDelete'     ,'Удалить'     ,'Удалить элемент из списка'      ,(lkToolBar.ControlCount * InputIntf_Ref_DefaultToolButtonWidth)+1,1,lkToolBar.Height-2,InputIntf_Ref_DefaultToolButtonWidth,alLeft,177,nil)do
      OnClick := @InputIntf_Ref_actDelete_OnExecute;
    with CreateTxcToolBarButton(Result,lkToolBar,'tbbDeleteAll'  ,'Удалить все' ,'Удалить все элементы из списка' ,(lkToolBar.ControlCount * InputIntf_Ref_DefaultToolButtonWidth)+1,1,lkToolBar.Height-2,InputIntf_Ref_DefaultToolButtonWidth,alLeft, 33,nil)do
      OnClick := @InputIntf_Ref_actDeleteAll_OnExecute;
    lkFileName := PrepareAbsoleteFileName(ERP_FILENAME_SQL_INPUT_REF+'SEL.SQL');
    if not FileExists(lkFileName)then exit;
    lkDTS.SelectSQL.Text  := StringsLoadFromFile(lkFileName);
    lkFileName := PrepareAbsoleteFileName(ERP_FILENAME_SQL_INPUT_REF+'REF.SQL');
    if not FileExists(lkFileName)then exit;
    lkDTS.RefreshSQL.Text := StringsLoadFromFile(lkFileName);
//    lkDTS.ModifySQL.Text  := 'UPDATE TABL$_BUFFER B SET B.FLAG_DELETE = ?FLAG_DELETE WHERE (B.ID = ?B_ID)';
    InputIntf_Ref_Refresh(Result);
  end;
