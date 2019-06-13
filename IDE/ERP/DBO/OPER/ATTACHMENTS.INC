{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/ATTACHMENTS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                    {$I PEAKTOP:GLOBAL_VARIABLES.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                    {$I PEAKTOP:OBJ/TXFBDATASETS.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                         {$I PEAKTOP:OBJ/TACTION.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                      {$I PEAKTOP:OBJ/TIMAGELIST.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                          {$I PEAKTOP:OBJ/TLABEL.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                       {$I PEAKTOP:OBJ/TCOLUMNEH.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                       {$I PEAKTOP:OBJ/TDBGRIDEH.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBEDITEH.INC}                       {$I PEAKTOP:OBJ/TDBEDITEH.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}           {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGROUPBAR.INC}                     {$I PEAKTOP:OBJ/TXCGROUPBAR.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                     {$I PEAKTOP:OBJ/TXCTABSHEET.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPGRID.INC}     {$I ../$COMMON/FORMERPGRID.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/ATTACHMENTS_CONST.INC}  {$I ./ATTACHMENTS_CONST.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/ATTACHMENTS_LANG.INC}   {$I ./ATTACHMENTS_LANG.INC}                   {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/OPER/ATTACHMENTS.INC ===================
  function TERPForm_DataSetMain_Create(aOwner :TComponent):Boolean;
  begin
    Result := true; // default handler  
  end;
  //============================================================================
  function TERPForm_DataSetMain_Insert(aOwner :TComponent):Boolean;
  begin
    Result := true; // default handler  
  end;
  //============================================================================
  function TERPForm_DataSetMain_Update(aOwner :TComponent):Boolean;
  begin
    Result := true; // default handler  
  end;
  //============================================================================
  function TERPForm_DataSetMain_Edit(aOwner :TComponent):Boolean;
  begin
    Result := true; // default handler  
  end;
  //============================================================================
  function TERPForm_DataSetMain_Delete(aOwner :TComponent):Boolean;
  begin
    Result := true; // override handler
    with TERPForm_DBGridMain(aOwner).DataSource.DataSet do
      begin
      if(not Active)then exit;
      if( not(RecordCount>0) )then exit;
      if(Dialogs.MessageDlg('Убить подключение к базе данных ?', mtWarning, [mbYes, mbNo]) <> mrYes)then exit;
      ExecSQL(FBDataBase, 'DELETE FROM MON$ATTACHMENTS RC WHERE (RC.MON$ATTACHMENT_ID = '''+FieldByName('MON$ATTACHMENT_ID').AsString+''')');
      TERPFormGrid_RefreshView(aOwner);  
      end;
  end;
  //============================================================================
  function TERPFormGrid_PrintGrid(aOwner :TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  function TERPFormGrid_PrintItem(aOwner :TComponent):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormGrid_RefreshView(aOwner :TComponent);
  begin
    TERPFormGrid_CloseDataSets(aOwner);
    with TERPForm_DataSetMain(aOwner) do
      begin
      SelectSQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_DBATTACH)); 
      Prepare;
      ParamByName('Q_USER_VAR'      ).AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
      ParamByName('Q_USER_VARLOCAL' ).AsString := ERP_GLOBALVARIABLE_USER_LOCAL;
      ParamByName('Q_USER_VARFILIAL').AsString := ERP_GLOBALVARIABLE_USER_FILIAL;
      ParamByName('Q_ERP_VERSION'   ).AsString := ERP_GLOBALVARIABLE_AMUNHOTEP_VERSION;
      Open;
      end;
    if TERPForm_MemTableMain(aOwner).Active then  
      TERPForm_OpenDataSetsChilds(TERPForm_MemTableMain(aOwner));
  end;
  //============================================================================
  procedure TERPFormGrid_PanelLeft_OnShowHide(aOwner :TComponent);
  begin
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_AfterScroll(DataSet :TDataSet);
  begin
  end;
  //============================================================================
  procedure TERPForm_DataSetMain_OnNewRecord(DataSet :TDataSet);
  begin
  end;
  //============================================================================
  function TERPFormGrid_ExportGetCaption(aOwner :TComponent):string;
  begin
    Result := msg_erp_dbattachments;
  end;
  //============================================================================
  function TERPFormGrid_ExportGetFilter(aOwner :TComponent):string;
  begin
    Result := '';
  end;
  //============================================================================
  function TERPFormGrid_ExportGetFileName(aOwner :TComponent):string;
  begin
    Result := msg_erp_dbattachments;
  end;                   
  //============================================================================
  procedure TERPFormOperAttachments_DBGridEh_OnGetCellParams(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
   if(Column.Tag=666)then exit;
   if(not(Column.Field.DataSet.Active))then exit;
   if(Column.Field.DataSet.RecordCount = 0)then exit;
   if(Column.Field.DataSet.FindField('CONNECTION_FLAG') <> nil)then
     begin
     if(Column.Field.DataSet.FieldByName('CONNECTION_FLAG').AsString = '1')then 
       aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Error;
     end;
  end;
  //============================================================================
  procedure TERPFormOperAttachments_TimerRefresh_OnTimer(Sender :TObject);
  begin
    TERPFormGrid_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  function TERPFormOperAttachments_CreateControls(aParent:TWinControl; aDataSource :TDataSource; const aFieldName, aCaption:string; const aLastTop:Integer):Integer;
  var
    lkLBL :TLabel;
    lkDBE :TDBEditEh;
  begin
    Result := aLastTop;
    lkLBL := CreateTLabel(aParent, aParent, aCaption, TERPForm_DefaultControlIndent, Result, TERPForm_DefaultControlHeight - TERPForm_DefaultControlIndent, aParent.Width - (TERPForm_DefaultControlIndent*2), alNone, taLeftJustify);
    with lkLBL do
      begin
      Anchors := [akLeft, akRight];
      Layout  := taBottom;
      Font.Style := [fsBold];
      end;
    Result := Result + lkLBL.Height;
    lkDBE := CreateTDBEditEh(aParent, '', aParent, aDataSource, aFieldName, TERPForm_DefaultControlIndent, Result, TERPForm_DefaultControlEditHeight, aParent.Width - (TERPForm_DefaultControlIndent*2));   
    with lkDBE do
      begin
      Anchors   := [akLeft, akRight];
      if(aFieldName <> 'MON$DATABASE_NAME')then
        begin
        Alignment := taRightJustify;
        EditMask  := '# ### ### ### ##0';
        end;
      end;
    Result := Result + lkDBE.Height;
  end;
  //============================================================================
  function TERPFormOperAttachments_Create:TAmunhotepForm;
  var
    lkSettings     :TStrings;
    lkCreateParams :TFormERPParams;
    lkDBG          :TDBGridEh;
    lkCol          :TColumnEh;
    lkAct          :TCustomAction;
    lkMainMenu     :TMainMenu;
    lkMIMenuMain   :TMenuItem;
    lkMIView       :TMenuItem;
    lkMIObj        :TMenuItem;
    lkMIItem       :TMenuItem;
    lkPanelLeft    :TxcPanel;
    lkPanelLeftC   :TxcGradientPanel;
    lkPanelClient  :TxcPanel;
    lkToolBar      :TxcGradientPanelVista;
    lkPC           :TxcPageControlEx;
    lkTS           :TxcTabSheet;
    lkQrTrans      :TxFBQuery;
    dbgTrans       :TDBGridEh;
    lkQrQuery      :TxFBQuery;
    dbgQuery       :TDBGridEh;
    lkSplt         :TSplitter;
    lkPnlSQL       :TxcGradientPanel;
    lkQrVars       :TxFBQuery;
    dbgVars        :TDBGridEh;
    lkQrDB         :TxFBQuery;
    lkDSQrDB       :TDataSource;
    lkLastTop      :Integer;
  begin
    DontAutoFree;
    lkCreateParams := [erpPanelLeft, erpPanelLeftShowHide,       
      erpGrid, erpGridGroup, erpGridNavigation, erpGridEdit, erpGridEditDel, erpGridNoCopy, erpGridExport, erpGridPrint, erpGridPrintItem,erpDetail];
    Result := TAmunhotepForm(TERPFormGrid_Create(msg_erp_dbattachments, msg_erp_mi_dbattachments, ERP_FILENAME_ICO_DBATTACH, ERP_FILENAME_BMP_DBATTACH, false, lkCreateParams));
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_BUFFERVAR       ] := '';
      Values[ERP_SETTINGS_TABLENAME       ] := '';
      Values[ERP_SETTINGS_TABLECAPTION    ] := msg_erp_dbattachments;
      Values[ERP_SETTINGS_REF_TREE        ] := '0';
      Values[ERP_SETTINGS_REF_TREEORGROUP ] := '0';
      Values[ERP_SETTINGS_REF_TREEFIELD   ] := '';
      Values[ERP_SETTINGS_BASETYPE        ] := IntToStr(ERP_OBJECTTYPE_OPER);
      Values[ERP_SETTINGS_TEMPFILENAME    ] := ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_ATTACHMENTS,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));
      end;
    lkMainMenu   := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu)); 
    lkMIMenuMain := TMenuItem(lkMainMenu.Items.FindComponent(obj_name_erp_mimainmenu));
    lkMIItem     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainitem));
    lkMIObj      := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainobj)); lkMIObj.ImageIndex := 195; 
    lkMIView     := TMenuItem(lkMIMenuMain.FindComponent(obj_name_erp_mimainview));
    lkAct        := TCustomAction(Result.FindComponent(obj_name_erp_actprintitem));lkAct.ImageIndex := 474;
    lkAct        := TCustomAction(Result.FindComponent(obj_name_erp_actprintgrid));lkAct.ImageIndex := 239;
    lkPanelLeft  := TxcPanel(Result.FindComponent(obj_name_erp_panelleft));
    lkPanelLeftC := CreateTxcGradientPanel(Result,lkPanelLeft,obj_name_erp_panelleft+'C','',alClient,0,0,200,200,xbsLowered,gdRightToLeft);
    lkPanelClient:= TxcPanel(Result.FindComponent(obj_name_erp_panelclient));
    lkToolBar    := TxcGradientPanelVista(Result.FindComponent(obj_name_erp_toolbar));
    lkPC         := TxcPageControlEx(Result.FindComponent(obj_name_erp_pagecontroldetail));
    lkTS         := CreateTxcTabSheet(lkPC,'tsTrans','Транзакции',19,$FFFF80);
    lkTS         := CreateTxcTabSheet(lkPC,'tsQuery','Запросы'   ,22,$FF80FF);
    lkTS         := CreateTxcTabSheet(lkPC,'tsVars' ,'Переменные',23,$80FFFF);
    TxcPageControlEx_ActivateDefaultPage(lkPC);
    lkDBG        := TERPForm_DBGridMain(Result);
    with lkDBG do
      begin
      Options         := Options + [dgRowSelect, dgAlwaysShowSelection] - [dgMultiSelect];
      OptionsEh       := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghAutoSortMarking, dghMultiSortMarking, dghIncSearch, dghRowHighlight, dghColumnResize, dghColumnMove,dghExtendVertLines];
      FooterRowCount  := 1;
      SortLocal       := true;
      ReadOnly        := true;
      OnGetCellParams := @TERPFormOperAttachments_DBGridEh_OnGetCellParams;
      end;
    lkCol := CreateTColumnEh(lkdbg,'ENGINE_VERSION'        ,''                   ,'Firebird|Версия'                   , 32,taLeftJustify );
    lkCol.HideDuplicates := true;
    lkCol := CreateTColumnEh(lkdbg,'MON$ATTACHMENT_ID'     ,'# ### ### ##0'      ,'Firebird|Код'                      , 40,taRightJustify);
    lkCol.Title.SortMarker := smDownEh;
    lkCol := CreateTColumnEh(lkdbg,'MON$SERVER_PID'        ,'# ### ### ##0'      ,'Firebird|PID'                      , 56,taRightJustify);
    lkCol := CreateTColumnEh(lkdbg,'MON$STATE'             ,''                   ,'Firebird|Состояние'                , 48,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'MON$USER',''                                 ,'Firebird|Пользователь'             , 60,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'MON$ROLE',''                                 ,'Firebird|Роль'                     , 40,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'RDB$CHARACTER_SET_NAME',''                   ,'Firebird|Кодировка'                , 60,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'MON$TIMESTAMP'         ,'dd.mm.yyyy hh:nn:ss','Firebird|Время'                    ,120,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'MON$REMOTE_ADDRESS'    ,''                   ,'Удаленные данные|Адрес'            , 96,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'MON$REMOTE_PROTOCOL'   ,''                   ,'Удаленные данные|Прото кол'        , 40,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'MON$ATTACHMENT_NAME'   ,''                   ,'Удаленные данные|Путь (псевдоним)' , 72,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'MON$REMOTE_PID'        ,'# ### ### ##0'      ,'Удаленные данные|Процесс|PID'      , 56,taRightJustify);
    lkCol := CreateTColumnEh(lkdbg,'MON$REMOTE_PROCESS'    ,''                   ,'Удаленные данные|Процесс|Имя'      ,200,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'AMUNHOTEP_VERSION'     ,''                   ,'AMUNHOTEP|Версия ядра'             ,104,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'DATABASE_USER'         ,''                   ,'AMUNHOTEP|USER'                    , 80,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'WRK_NAME'              ,''                   ,'AMUNHOTEP|Сотрудник'               ,120,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'COUNTRY_NAME'          ,''                   ,'AMUNHOTEP|Локализация'             , 80,taLeftJustify );
    lkCol := CreateTColumnEh(lkdbg,'FILIAL_NAME'           ,''                   ,'AMUNHOTEP|Филиал'                  , 96,taLeftJustify );
    TERPForm_GridSettingsLoad(lkdbg, lkSettings.Values[ERP_SETTINGS_TEMPFILENAME]);
    lkQrTrans := TxFBQuery.Create(lkDBG.DataSource.DataSet);
    with lkQrTrans do
      begin
      Name        := 'lkQrTrans';
      DataSource  := lkDBG.DataSource;
      Transaction := TERPForm_TransactionMain(Result);
      SQL.Text := 
      'SELECT  TR.MON$ATTACHMENT_ID AS '+ERP_DATASET_DBKEY+', TR.MON$ATTACHMENT_ID, TR.MON$TRANSACTION_ID, TR.MON$OLDEST_TRANSACTION, '+SQLCRLF+
      '       (SELECT FIRST 1 TP.RDB$TYPE_NAME '+SQLCRLF+
      '        FROM   RDB$TYPES TP '+SQLCRLF+
      '        WHERE  (TP.RDB$FIELD_NAME = ''MON$STATE'') '+SQLCRLF+
      '          AND  (TP.RDB$TYPE = TR.MON$STATE) '+SQLCRLF+
      '       ) AS MON$STATE, TR.MON$TIMESTAMP, TR.MON$TOP_TRANSACTION, '+SQLCRLF+
      '       (SELECT FIRST 1 TP.RDB$TYPE_NAME '+SQLCRLF+
      '        FROM   RDB$TYPES TP '+SQLCRLF+
      '        WHERE (TP.RDB$FIELD_NAME = ''MON$ISOLATION_MODE'') '+SQLCRLF+
      '          AND (TP.RDB$TYPE = TR.MON$ISOLATION_MODE) '+SQLCRLF+
      '       ) AS MON$ISOLATION_MODE, TR.MON$OLDEST_ACTIVE, '+SQLCRLF+
      '       CASE '+SQLCRLF+
      '         WHEN TR.MON$LOCK_TIMEOUT = -1 THEN ''INFINITE WAIT'' '+SQLCRLF+
      '         WHEN TR.MON$LOCK_TIMEOUT = 0 THEN ''NO WAIT'' '+SQLCRLF+
      '         WHEN TR.MON$LOCK_TIMEOUT > 0  THEN ''WAIT :'' ||TR.MON$LOCK_TIMEOUT '+SQLCRLF+
      '       END AS MON$LOCK_TIMEOUT, TR.MON$READ_ONLY, TR.MON$AUTO_COMMIT, TR.MON$AUTO_UNDO, '+SQLCRLF+
      '       R.MON$RECORD_SEQ_READS, R.MON$RECORD_IDX_READS, R.MON$RECORD_INSERTS, R.MON$RECORD_UPDATES, '+SQLCRLF+
      '       R.MON$RECORD_DELETES, R.MON$RECORD_BACKOUTS, R.MON$RECORD_PURGES, R.MON$RECORD_EXPUNGES, '+SQLCRLF+
      '       IO.MON$PAGE_READS, IO.MON$PAGE_WRITES, IO.MON$PAGE_FETCHES, IO.MON$PAGE_MARKS '+SQLCRLF+
      'FROM   MON$TRANSACTIONS TR, MON$RECORD_STATS R, MON$IO_STATS IO '+SQLCRLF+
      'WHERE  (TR.MON$ATTACHMENT_ID = ?MON$ATTACHMENT_ID) '+SQLCRLF+
      '  AND  (R.MON$STAT_ID  = TR.MON$STAT_ID) '+SQLCRLF+
      '  AND  (IO.MON$STAT_ID = TR.MON$STAT_ID) '+SQLCRLF+
      'ORDER BY 1 ';        
      end;
    dbgTrans := CreateTDBGridEh(Result, lkPC.Pages[0], nil, 'dbgTrans', 0,0,200,200,alClient);
    with dbgTrans do 
      begin 
      Color        := lkPC.Pages[0].Color;
      Options      := lkDBG.Options;
      FooterRowCount :=1;
      VTitleMargin := 2;
      SumList.Active := true;
      DataSource := TDataSource.Create(lkQrTrans);
      DataSource.Name    := 'DataSource_'+lkQrTrans.Name;
      DataSource.Dataset := lkQrTrans;
      Columns.Clear;
      lkCol := CreateTColumnEh(dbgTrans,'MON$TRANSACTION_ID'    ,'# ### ### ##0'      ,'Транзакция|Код'                           , 60, taRightJustify);
      lkCol.Title.SortMarker := smDownEh;
      with lkCol.Footer do
        begin
        Alignment     := lkCol.Alignment;
        DisplayFormat := lkCol.DisplayFormat;
        FieldName     := lkCol.FieldName;
        ValueType     := fvtCount;
        end;
      lkCol := CreateTColumnEh(dbgTrans,'MON$TOP_TRANSACTION'   ,'# ### ### ##0'      ,'Транзакция|Код пред.'                     , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$OLDEST_TRANSACTION','# ### ### ##0'      ,'Транзакция|Верхняя'                       , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$TIMESTAMP'         ,'dd.mm.yyyy hh:nn:ss','Транзакция|Стартовала'                    ,104, taLeftJustify );
      lkCol := CreateTColumnEh(dbgTrans,'MON$STATE'             ,''                   ,'Транзакция|Состояние'                     , 48, taLeftJustify );
      lkCol := CreateTColumnEh(dbgTrans,'MON$ISOLATION_MODE'    ,''                   ,'Транзакция|Изоляция'                      , 96, taLeftJustify );
      lkCol := CreateTColumnEh(dbgTrans,'MON$LOCK_TIMEOUT'      ,''                   ,'Транзакция|Таймаут'                       , 40, taLeftJustify );
      lkCol := CreateTColumnEh(dbgTrans,'MON$READ_ONLY'         ,''                   ,'Транзакция|Только чтение'                 , 20, taLeftJustify );
      lkCol.KeyList.Text  := '1'+SQLCRLF+'0'; 
      lkCol.PickList.Text := '1'+SQLCRLF+'0'; 
      lkCol.CheckBoxes    := true;
      lkCol := CreateTColumnEh(dbgTrans,'MON$AUTO_COMMIT'       ,''                   ,'Транзакция|Авто подтверждение'            , 20, taLeftJustify );
      lkCol.KeyList.Text  := '1'+SQLCRLF+'0'; 
      lkCol.PickList.Text := '1'+SQLCRLF+'0'; 
      lkCol.CheckBoxes    := true;
      lkCol := CreateTColumnEh(dbgTrans,'MON$AUTO_UNDO'         ,''                   ,'Транзакция|Автооткат'                     , 20, taLeftJustify );
      lkCol.KeyList.Text  := '1'+SQLCRLF+'0'; 
      lkCol.PickList.Text := '1'+SQLCRLF+'0'; 
      lkCol.CheckBoxes    := true;
      lkCol := CreateTColumnEh(dbgTrans,'MON$RECORD_SEQ_READS'   ,'# ### ### ##0'     ,'Записи|Чтение|без индексов'               , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$RECORD_IDX_READS'   ,'# ### ### ##0'     ,'Записи|Чтение|Индексное'                  , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$RECORD_INSERTS'     ,'# ### ### ##0'     ,'Записи|Изменения|Добавлено'               , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$RECORD_UPDATES'     ,'# ### ### ##0'     ,'Записи|Изменения|Изменено'                , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$RECORD_DELETES'     ,'# ### ### ##0'     ,'Записи|Изменения|Удалено'                 , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$RECORD_BACKOUTS'    ,'# ### ### ##0'     ,'Записи|Изменения|BACKOUTS'                , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$RECORD_PURGES'      ,'# ### ### ##0'     ,'Записи|Изменения|PURGES'                  , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$RECORD_EXPUNGES'    ,'# ### ### ##0'     ,'Записи|Изменения|EXPUNGES'                , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$PAGE_READS'         ,'# ### ### ##0'     ,'Страницы данных|Прочтено'                 , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$PAGE_WRITES'        ,'# ### ### ##0'     ,'Страницы данных|Записано'                 , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$PAGE_FETCHES'       ,'# ### ### ##0'     ,'Страницы данных|Фетчи'                    , 60, taRightJustify);
      lkCol := CreateTColumnEh(dbgTrans,'MON$PAGE_MARKS'         ,'# ### ### ##0'     ,'Страницы данных|блокировки'               , 60, taRightJustify);
      end; 
    lkQrQuery := TxFBQuery.Create(lkDBG.DataSource.DataSet);
    with lkQrQuery do
      begin
      Name        := 'lkQrQuery';
      DataSource  := lkDBG.DataSource;
      Transaction := TERPForm_TransactionMain(Result);
      SQL.Text := 
        'SELECT ST.MON$STATEMENT_ID, ST.MON$ATTACHMENT_ID, ST.MON$TRANSACTION_ID, '+SQLCRLF+
        '       (SELECT FIRST 1 TP.RDB$TYPE_NAME FROM RDB$TYPES TP '+SQLCRLF+
        '        WHERE  (TP.RDB$FIELD_NAME = ''MON$STATE'')AND(TP.RDB$TYPE = ST.MON$STATE) '+SQLCRLF+
        '       ) AS MON$STATE, ST.MON$TIMESTAMP, ST.MON$SQL_TEXT, '+SQLCRLF+
        '       R.MON$RECORD_SEQ_READS, R.MON$RECORD_IDX_READS, R.MON$RECORD_INSERTS, '+SQLCRLF+
        '       R.MON$RECORD_UPDATES, R.MON$RECORD_DELETES, R.MON$RECORD_BACKOUTS, '+SQLCRLF+
        '       R.MON$RECORD_PURGES, R.MON$RECORD_EXPUNGES, IO.MON$PAGE_READS, '+SQLCRLF+
        '       IO.MON$PAGE_WRITES, IO.MON$PAGE_FETCHES, IO.MON$PAGE_MARKS '+SQLCRLF+
        'FROM   MON$STATEMENTS ST, MON$RECORD_STATS R, MON$IO_STATS IO '+SQLCRLF+
        'WHERE  (ST.MON$ATTACHMENT_ID = ?MON$ATTACHMENT_ID) '+SQLCRLF+
        '  AND  (R.MON$STAT_ID  = ST.MON$STAT_ID) '+SQLCRLF+
        '  AND  (IO.MON$STAT_ID = ST.MON$STAT_ID) '+SQLCRLF+
        'ORDER BY ST.MON$STATEMENT_ID DESCENDING ';
      end;
    dbgQuery := CreateTDBGridEh(Result, lkPC.Pages[1], nil, 'dbgQuery', 0,0,200,200,alClient);
    with dbgQuery do 
      begin 
      Color        := lkPC.Pages[1].Color;
      Options      := lkDBG.Options;
      VTitleMargin := 2;
      DataSource := TDataSource.Create(lkQrQuery);
      DataSource.Name    := 'DataSource_'+lkQrQuery.Name;
      DataSource.Dataset := lkQrQuery;
      Columns.Clear;
      lkCol := CreateTColumnEh(dbgQuery,'MON$STATEMENT_ID'    ,'# ### ### ##0','Запрос|Код'                ,60,taRightJustify);
      lkCol.Title.SortMarker := smDownEh;
      lkCol := CreateTColumnEh(dbgQuery,'MON$STATE'           ,''             ,'Запрос|Состояние'          ,48,taLeftJustify );
      lkCol := CreateTColumnEh(dbgQuery,'MON$TRANSACTION_ID'  ,'# ### ### ##0','Запрос|Код транзакции'     ,60,taRightJustify);
      lkCol := CreateTColumnEh(dbgQuery,'MON$RECORD_SEQ_READS','# ### ### ##0','Записи|Чтение|без индексов',60,taRightJustify);
      lkCol := CreateTColumnEh(dbgQuery,'MON$RECORD_IDX_READS','# ### ### ##0','Записи|Чтение|Индексное'   ,60,taRightJustify);
      lkCol := CreateTColumnEh(dbgQuery,'MON$RECORD_INSERTS'  ,'# ### ### ##0','Записи|Изменения|Добавлено',32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$RECORD_UPDATES'  ,'# ### ### ##0','Записи|Изменения|Изменено' ,32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$RECORD_DELETES'  ,'# ### ### ##0','Записи|Изменения|Удалено'  ,32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$RECORD_BACKOUTS' ,'# ### ### ##0','Записи|Изменения|BACKOUTS' ,32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$RECORD_PURGES'   ,'# ### ### ##0','Записи|Изменения|PURGES'   ,32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$RECORD_EXPUNGES' ,'# ### ### ##0','Записи|Изменения|EXPUNGES' ,32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$PAGE_READS'      ,'# ### ### ##0','Страницы данных|Прочтено'  ,32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$PAGE_WRITES'     ,'# ### ### ##0','Страницы данных|Записано'  ,32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$PAGE_FETCHES'    ,'# ### ### ##0','Страницы данных|Фетчи'     ,32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      lkCol := CreateTColumnEh(dbgQuery,'MON$PAGE_MARKS'      ,'# ### ### ##0','Страницы данных|блокировки',32,taRightJustify); lkCol.Title.Orientation := tohVertical;
      end; 
    lkPnlSQL := CreateTxcGradientPanel(lkPC.Pages[1], lkPC.Pages[1],'','',alRight, 0,0,200,480,xbsNone,gdLeftToRight);
    lkSplt   := CreateTSplitter(lkPC.Pages[1], lkPC.Pages[1],'',alRight, lkPnlSQL.Left-4,0,200,4);
    DBInterfaceCreate_Intf(Result, lkPnlSQL, dbgQuery.DataSource, 'MON$SQL_TEXT', 'DOMN$BLOB_SQL', true);
    
    lkQrVars := TxFBQuery.Create(lkDBG.DataSource.DataSet);
    with lkQrVars do
      begin
      Name        := 'lkQrVars';
      DataSource  := lkDBG.DataSource;
      Transaction := TERPForm_TransactionMain(Result);
      SQL.Text := 
        'SELECT C.MON$ATTACHMENT_ID, C.MON$TRANSACTION_ID, C.MON$VARIABLE_NAME, C.MON$VARIABLE_VALUE '+SQLCRLF+
        'FROM   MON$CONTEXT_VARIABLES C '+SQLCRLF+
        'WHERE  (C.MON$ATTACHMENT_ID = ?MON$ATTACHMENT_ID) '+SQLCRLF+
        'ORDER BY C.MON$VARIABLE_NAME ';    
      end;
    dbgVars := CreateTDBGridEh(Result, lkPC.Pages[2], nil, 'dbgVars', 0,0,200,200,alClient);
    with dbgVars do 
      begin 
      Color        := lkPC.Pages[2].Color;
      Options      := lkDBG.Options;
      VTitleMargin := 2;
      DataSource := TDataSource.Create(lkQrVars);
      DataSource.Name    := 'DataSource_'+lkQrVars.Name;
      DataSource.Dataset := lkQrVars;
      Columns.Clear;
      lkCol := CreateTColumnEh(dbgVars,'MON$TRANSACTION_ID','# ### ### ##0','Код транзакции', 80,taRightJustify);
      lkCol := CreateTColumnEh(dbgVars,'MON$VARIABLE_NAME' ,''             ,'Имя переменной',220,taLeftJustify );
      lkCol := CreateTColumnEh(dbgVars,'MON$VARIABLE_VALUE',''             ,'Значение'      ,480,taLeftJustify );
      end; 
    lkQrDB := TxFBQuery.Create(lkDBG.DataSource.DataSet);
    with lkQrDB do
      begin
      Name        := 'lkQrDB';
      Transaction := TERPForm_TransactionMain(Result);
      SQL.Text :=  'SELECT M.*, (M.MON$PAGE_SIZE * M.MON$PAGES) / 1024 / 1024 AS FILE_SIZE, (M.MON$ODS_MAJOR||''.''||M.MON$ODS_MINOR) AS ODS FROM MON$DATABASE M ';
      end;
    lkDSQrDB := TDataSource.Create(lkQrDB);
    with lkDSQrDB do
      begin
      Name    := 'DataSource'+lkQrDB.Name;
      DataSet := lkQrDB;
      end;
    lkLastTop := TERPForm_DefaultControlIndent;
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'MON$DATABASE_NAME' ,'Имя файла базы данных'    ,lkLastTop);
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'MON$SQL_DIALECT'   ,'Диалект SQL'              ,lkLastTop);
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'ODS'               ,'Версия ODS'               ,lkLastTop);
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'MON$CREATION_DATE' ,'Дата создания'            ,lkLastTop);
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'FILE_SIZE'         ,'Размер файла в мегабайтах',lkLastTop);
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'MON$PAGE_SIZE'     ,'Размер страницы'          ,lkLastTop);
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'MON$PAGES'         ,'Всего страниц'            ,lkLastTop);
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'MON$PAGE_BUFFERS'  ,'Страниц в буфере'         ,lkLastTop);
    lkLastTop := TERPFormOperAttachments_CreateControls(lkPanelLeftC,lkDSQrDB,'MON$SWEEP_INTERVAL','Интревал сборки мусора'   ,lkLastTop);
    TERPFormGrid_RefreshView(Result);     
  end;
