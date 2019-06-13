{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                      {$I PEAKTOP:GLOBAL_VARIABLES.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                           {$I PEAKTOP:OBJ/TACTION.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}                         {$I PEAKTOP:OBJ/TMENUITEM.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                  {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}              {$I PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}               {$I ../OBJECTNAMES.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_CONST.INC}     {$I ./FORMERP_CONST.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}     {$I ./FORMERP_NAMES.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC}       {$I ../DBGRID/COL_PROTOCOL.INC}          {$ENDIF}
  //============== PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC ==============
  function TERPForm_Create(const aCaption, aFileNameIcon, aFileNameBitmap :string; const aModalForm:Boolean; aOnClose :TCloseEvent):TForm; forward;
  //============================================================================
  function TERPForm_GetOwner(aCmp:TComponent):TComponent;
  begin
    Result := aCmp;
    while(Result <> nil)do
      begin
      if(ObjectInheritsFrom(Result,'TCustomForm'))then exit;
      Result := Result.Owner;
      end;
    if(not ObjectInheritsFrom(Result,'TCustomForm'))then 
      Result := nil;
  end;
  //============================================================================
  function TERPForm_Settings(aOwner:TComponent):TStringList;
  begin
    with TxsStringsHolder(aOwner.FindComponent(obj_name_erp_data_settings)) do
      begin
      while(Items.Count < 1)do
        Items.Add;
      Result := TStringList(Items[0].Strings);
      end;
  end;
  //============================================================================
  function TERPForm_Local(aOwner:TComponent):TStringList;
  begin
    with TxsStringsHolder(aOwner.FindComponent(obj_name_erp_data_settings)) do
      begin
      while(Items.Count < 2)do
        Items.Add;
      Result := TStringList(Items[1].Strings);
      Result.Duplicates := dupIgnore;
      Result.Sorted     := True;
      end;
  end;
  //============================================================================
  function TERPForm_SQL(aOwner:TComponent):TStrings;
  begin
    with TxsStringsHolder(aOwner.FindComponent(obj_name_erp_data_settings)) do
      begin
      while(Items.Count < 2)do
        Items.Add;
      Result := Items[1].Strings;
      end;
  end;
  //============================================================================
  function TERPForm_ObjId(aOwner:TComponent):string;
  begin
    Result := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME];
  end;
  //============================================================================
  function TERPForm_ObjType(aOwner:TComponent):Integer;
  begin
    Result := StrToInt(TERPForm_Settings(aOwner).Values[ERP_SETTINGS_BASETYPE]);
  end;
  //============================================================================
  procedure TERPForm_SetCaption(aOwner:TComponent; const aCaption :string);
  begin
    if ObjectInheritsFrom(aOwner,'TAmunhotepForm')then 
      TAmunhotepForm(aOwner).SetCaption(aCaption)
     else 
      if ObjectInheritsFrom(aOwner,'TCustomForm'   )then 
        TCustomForm(aOwner).Caption := aCaption;
    if(aOwner.FindComponent(obj_name_erp_topbar) <> nil)then
      TxcGradientPanelVista(aOwner.FindComponent(obj_name_erp_topbar)).Caption := #$20#$20#$20#$20#$20#$20+aCaption;
  end;
  //============================================================================
  function TERPForm_ActionListMain(aOwner:TComponent):TActionList;
  begin
    Result := TActionList( TERPForm_GetOwner(aOwner).FindComponent(obj_name_erp_actlst) );
  end;
  //============================================================================
  function TERPForm_CreateAction(aOwner:TComponent; const aActionName, aCaption, aHint, aShortCut :string; const aGroupIndex, aImageIndex :Integer;
             aOnExecute, aOnUpdate :TNotifyEvent; aToolBar :TxcGradientPanel; aParentItem :TMenuItem):TCustomAction;
  var
    lkTBB:TxcToolBarButton;
    lkMI :TMenuItem;
  begin
    Result            := CreateTAction(aOwner,aActionName,aCaption,aHint,aShortCut, aGroupIndex, aImageIndex);
    Result.OnExecute  := aOnExecute; 
    Result.OnUpdate   := aOnUpdate;
    Result.ActionList := TERPForm_ActionListMain(aOwner);
    if(aToolBar <> nil)then
      begin
      lkTBB := CreateTxcToolBarButton(aToolBar, aToolBar, 'tbb'+Result.Name, '','', aToolBar.ControlCount * TERPForm_DefaultToolButtonWidth,1,TERPForm_DefaultToolButtonWidth,TERPForm_DefaultToolButtonWidth, alLeft, -1, Result);
      lkTBB.GroupIndex := aGroupIndex;
      end;
    if(aParentItem <> nil)then  
      begin
      lkMI := CreateTMenuItem2(aParentItem, Result);
      if(aToolBar <> nil)then
        lkTBB.ImagesSmall := lkMI.GetImageList;
      end;  
  end;
  //============================================================================
  function TERPForm_CreateAction2(aOwner:TComponent; const aActionName, aCaption, aHint, aShortCut :string; const aGroupIndex, aImageIndex :Integer;
             aOnExecute, aOnUpdate :TNotifyEvent; aToolBar :TxcGradientPanel; const aToolButtonWidth:Integer; aParentItem :TMenuItem):TCustomAction;
  begin
    Result := TERPForm_CreateAction(aOwner,aActionName,aCaption,aHint,aShortCut, aGroupIndex, aImageIndex, aOnExecute, aOnUpdate, aToolBar, aParentItem);  
    if(aToolBar <> nil)then
      if(aToolBar.FindComponent('tbb'+aActionName) <> nil)then
        with TxcToolBarButton(aToolBar.FindComponent('tbb'+aActionName)) do
          begin
          ShowCaption := true;
          Width       := aToolButtonWidth;
          Left        := TWinControl_AutoWidth(Parent);
          end;
  end;
  //============================================================================
  function TERPForm_CreateActionTopBar(aOwner:TComponent; const aActionName, aHint, aShortCut, aImageFileName :string; aOnExecute, aOnUpdate :TNotifyEvent; aTopBar :TxcGradientPanel):TCustomAction;
  var
    lkTBB:TxcToolBarButton;
  begin
    Result := CreateTAction(aOwner,aActionName,'',aHint,aShortCut,0,-1);
    Result.OnExecute := aOnExecute; 
    Result.OnUpdate  := aOnUpdate; 
    if(aTopBar <> nil)then
      begin
      lkTBB := CreateTxcToolBarButton2(Result, aTopBar,'',aTopBar.Width - ((aTopBar.Height+2) + aTopBar.ControlCount),0,aTopBar.Height+2,aTopBar.Height+2, alRight, Result);
      with lkTBB do
        begin
        ShowHint    := true;
        ShowCaption := false;
        if FileExists(PrepareAbsoleteFileName(aImageFileName))then
          Glyph.LoadFromFile(PrepareAbsoleteFileName(aImageFileName));  
        end;
      end;
  end;
  //============================================================================
  function TERPForm_DBGridMain(aOwner:TComponent):TDBGridEh;
  begin
    Result := TDBGridEh(aOwner.FindComponent(obj_name_erp_data_dbgmain));
  end;
  //============================================================================
  function TERPFormGrid_DBGridMain(aOwner:TComponent):TDBGridEh;
  begin
    Result := TERPForm_DBGridMain(aOwner); // for backward compability !
  end;
  //============================================================================
  function TERPForm_ActiveDBGrid(aOwner :TComponent):TDBGridEh;
  var
    lkCtrl :TWinControl;
  begin
    lkCtrl := TForm(aOwner).ActiveControl;
    if(not ObjectInheritsFrom(lkCtrl, 'TDBGridEh'))then
      Result := TERPForm_DBGridMain(aOwner)
     else 
      Result := TDBGridEh(lkCtrl);  
  end;
  //============================================================================
  function TERPForm_TransactionMain(aOwner:TComponent):TxFBTransaction;
  begin
    Result := TxFBTransaction(aOwner.FindComponent(obj_name_erp_data_trmain));
  end;
  //============================================================================
  function TERPForm_DataSetMain(aOwner:TComponent):TxFBDataSet;
  begin
    Result := TxFBDataSet(TERPForm_TransactionMain(aOwner).FindComponent(obj_name_erp_data_dtsmain));
  end;
  //============================================================================
  function TERPForm_ActiveDataSet(aOwner :TComponent):TDataSet;
  begin
    Result := TERPForm_ActiveDBGrid(aOwner).DataSource.DataSet;
  end;
  //============================================================================
  function TERPForm_QueryMain(aOwner:TComponent):TxFBQuery;
  begin
    Result := TxFBQuery(TERPForm_TransactionMain(aOwner).FindComponent(obj_name_erp_data_qrmain));
  end;
  //============================================================================
  function TERPForm_MemTableMain(aOwner:TComponent):TMemTableEh;
  begin
    Result := TMemTableEh(TERPForm_TransactionMain(aOwner).FindComponent(obj_name_erp_data_mtmain));
  end;  
  //============================================================================
  procedure TERPForm_CloseDataSetsChilds(aDataSet :TDataSet);
  var
    i :Integer;
  begin
    for i:=0 to aDataSet.ComponentCount-1 do
      if ObjectInheritsFrom(aDataSet.Components[i], 'TDataSet')then
        with TDataSet(aDataSet.Components[i]) do
          if Active then 
            begin
            if(State <> dsBrowse)then
              try Post; except Cancel; end;
            Close;
            end;
  end;
  //============================================================================
  procedure TERPForm_OpenDataSetsChilds(aDataSet :TDataSet);
  var
    i :Integer;
  begin
    for i:=0 to aDataSet.ComponentCount-1 do
      if ObjectInheritsFrom(aDataSet.Components[i], 'TDataSet')then
        with TDataSet(aDataSet.Components[i]) do
          if not Active then 
            try 
              Open; 
            except 
              WriteLn('TERPForm_OpenDataSetsChilds: cannon open dataset "'+Name+'" :'+ClassName); 
            end;
  end;
  //============================================================================
  procedure TERPForm_GridSettingsLoad(aDBGrid :TDBGridEh; const aFileName:string);
  var
    lkFileName:string;
    lkName    :string;
    lkSortMark:Integer;
    i         :Integer;
  begin
    lkFileName := PrepareAbsoleteFileName(aFileName);
    if not FileExists(lkFileName)then exit;

    with TStringList.Create do
      begin
      LoadFromFile(lkFileName);
      lkName := aDBGrid.Name;
      if(StrTrimAll(lkName) = '')then
        lkName := aDBGrid.ClassName;
      if(StrTrimAll(Values[UpperCase(lkName+'.DataGrouping.Active')]) <> '')then
        aDBGrid.DataGrouping.Active := Values[UpperCase(lkName+'.DataGrouping.Active')] <> '0'
      aDBGrid.DataGrouping.GroupPanelVisible := aDBGrid.DataGrouping.Active;
      aDBGrid.SumList.Active := false;
      if(StrTrimAll(Values[UpperCase(lkName+'.SumList.Active')]) <> '')then
        begin
        if(StrCiphersOnlyInt(aDBGrid.HelpKeyWord) <> '')then
          aDBGrid.FooterRowCount := StrToInt(aDBGrid.HelpKeyWord)
         else
          begin
          aDBGrid.FooterRowCount := 1;
          aDBGrid.HelpKeyWord    := '1';
          end;
        aDBGrid.SumList.Active := (Values[UpperCase(lkName+'.SumList.Active')] = '1');
        end;
      if not aDBGrid.SumList.Active then
        aDBGrid.FooterRowCount := 0;  
      // TODO: временная заглушка! Нельзя так
      // Почему нельзя ? если пишешь TODO, указывай почему! 2012.11.07 PEAKTOP
      for i:=0 to aDBGrid.Columns.Count-1 do
        begin
        if(StrTrimAll(Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Width')  ]) <> '')then
          aDBGrid.Columns[i].Width   := StrToInt(Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Width')]);
        if(StrTrimAll(Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Visible')]) <> '')then
          aDBGrid.Columns[i].Visible := Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Visible')] <> '0'; 
        if(StrTrimAll(Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Title.SortMarker')  ]) <> '')then
          begin
          lkSortMark := StrToInt(Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Title.SortMarker')]);
          case lkSortMark of
            0: aDBGrid.Columns[i].Title.SortMarker := smNoneEh;
            1: aDBGrid.Columns[i].Title.SortMarker := smDownEh;
            2: aDBGrid.Columns[i].Title.SortMarker := smUpEh;
          end;   
          end;
        //aDBGrid.Columns[i].STFilter.ExpressionStr := Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].STFilter.ExpressionStr')];
        end;
      Free;
      end;  
  end;
  //============================================================================
  procedure TERPForm_GridSettingsSave(aDBGrid :TDBGridEh; const aFileName:string);
  var
    lkFileName:string;
    lkName    :string;
    i         :Integer;
  begin
    lkFileName := PrepareAbsoleteFileName(aFileName);
    if(StrTrimAll(lkFileName) = '')then exit;
    with TStringList.Create do
      begin
      if FileExists(lkFileName)then
        LoadFromFile(lkFileName);
      lkName := aDBGrid.Name;
      if(StrTrimAll(lkName) = '')then
        lkName := aDBGrid.ClassName;
      if aDBGrid.DataGrouping.Active then  
        Values[UpperCase(lkName+'.DataGrouping.Active')] := '1'
       else 
        Values[UpperCase(lkName+'.DataGrouping.Active')] := '0';
      if aDBGrid.SumList.Active then  
        Values[UpperCase(lkName+'.SumList.Active')] := '1'
       else 
        Values[UpperCase(lkName+'.SumList.Active')] := '0';
      for i:=0 to aDBGrid.Columns.Count-1 do
        if(aDBGrid.Columns[i].FieldName <> ERP_SQL_FIELD_IMAGES)then
          begin
          if aDBGrid.Columns[i].Visible then
            Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Visible')] := '1'
           else 
            Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Visible')] := '0';
          Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Width')]                  := IntToStr(aDBGrid.Columns[i].Width);
          Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].STFilter.ExpressionStr')] := aDBGrid.Columns[i].STFilter.ExpressionStr;
          Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Title.SortMarker')]       := IntToStr(Integer(aDBGrid.Columns[i].Title.SortMarker));
          Values[UpperCase(lkName+'.Columns['+aDBGrid.Columns[i].FieldName+'].Index')]                  := IntToStr(aDBGrid.Columns[i].Index);
          end;
      SaveToFile(lkFileName);  
      Free;
      end;  
  end;
  //============================================================================
  function TERPForm_ExecSQLParams(const aTransactionParams:array of string; const aSQL:string; const aParamNames, aParamValues:array of string):Boolean;
  var
    i    :Integer;
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
  begin
    Result := false;
    if not FBDataBase.Connected then exit;
    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        if(Length(aTransactionParams) > 0)then
          for i:=0 to Length(aTransactionParams)-1 do
            Add(aTransactionParams[i])
         else
          begin
          Add('isc_tpb_read_committed');
          Add('isc_tpb_write');
          Add('isc_tpb_rec_version');
          Add('isc_tpb_nowait');
          end;   
        end;
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQR do
      begin
      Transaction := lkTr;
      SQL.Text := aSQL;
      if(Length(aParamNames) > 0)then
        begin
        Prepare;
        for i:=0 to Length(aParamNames)-1 do
          ParamByName(aParamNames[i]).AsString := aParamValues[i]; 
        end;
      try
        ExecSQL;
      finally
          Result := true;
      end;  
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;    
  end;
  //============================================================================
  function TERPForm_ExecSQL(const aTransactionParams:array of string; const aSQL:string):Boolean;
  begin
    Result := TERPForm_ExecSQLParams(aTransactionParams, aSQL, [], []);
  end;
  //============================================================================
  function TERPForm_SelectSQLParams(const aTransactionParams:array of string; const aSQL:string; const aParamNames, aParamValues, aVarNames:array of string;
              var aVarValues :array of string):Boolean;
  var
    i    :Integer;
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
  begin
    Result := false;
    if not FBDataBase.Connected then exit;
    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        if(Length(aTransactionParams) > 0)then
          for i:=0 to Length(aTransactionParams)-1 do
            Add(aTransactionParams[i])
         else
          begin
          Add('isc_tpb_read_committed');
          Add('isc_tpb_write');
          Add('isc_tpb_rec_version');
          Add('isc_tpb_nowait');
          end;   
        end;
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQR do
      begin
      Transaction := lkTr;
      SQL.Text := aSQL;
      if(Length(aParamNames) > 0)then
        begin
        Prepare;
        for i:=0 to Length(aParamNames)-1 do
          ParamByName(aParamNames[i]).AsString := aParamValues[i]; 
        end;
      try
        Open;
      except
        if lkTr.InTransaction then
          lkTr.RollBack;
        lkTr.Free;
        exit;  
      end;  
      if Active then
        begin
        Last;
        if(Length(aVarNames) > 0)then
          for i:=0 to Length(aVarNames)-1 do
            aVarValues[i] := FieldByName(aVarNames[i]).AsString;
        end;    
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;  
    Result := true;  
  end;
  //============================================================================
  procedure TERPForm_DBGrid_FillValuesGrid(DataSet:TDataSet; FBDataSet :TxFBDataSet; aDBG :TDBGridEh);
  var
    i     :Integer;
    lkStr :string;
  begin
    for i:=0 to DataSet.Fields.Count-1 do
      begin
      if( (DataSet.Fields[i].FieldName = ERP_DATASET_DBKEY) or (DataSet.Fields[i].FieldName = 'ID') )then
        try DataSet.Fields[i].AsString := '-1'; except end;
      if( DataSet.Fields[i].FieldName = ERP_SQL_PERIODICALDATEFIELD )then
        try DataSet.Fields[i].AsDateTime := Now; except end;
      if(FBDataSet <> nil)then  
        if(DataSet.Fields[i].FieldName = FBDataSet.GeneratorField.Field)then
          begin
          lkStr := '0';
          if GetField(FBDataBase, 'RDB$DATABASE', 'GEN_ID('+FBDataSet.GeneratorField.Generator+', 0)', '', lkStr)then
            try 
              DataSet.Fields[i].AsString := IntToStr(StrToInt(lkStr) + FBDataSet.GeneratorField.IncrementBy); 
            finally 
              DataSet.FieldByName(ERP_DATASET_DBKEY).AsString := DataSet.Fields[i].AsString;
            end;
          end;  
      end;
    for i:=0 to aDBG.Columns.Count-1 do
      begin
      if(StrTrimAll(aDBG.Columns[i].ColParams[ERP_COL_INDEX_VALUEDEFAULT]) <> '')then
        try
          DataSet.FieldByName(aDBG.Columns[i].ColParams[ERP_COL_INDEX_FIELD]).AsString := aDBG.Columns[i].ColParams[ERP_COL_INDEX_VALUEDEFAULT];
        except
        end;
      if( (StrTrimAll(aDBG.Columns[i].ColParams[ERP_COL_INDEX_REF_TABLE]) <> '') and (StrTrimAll(aDBG.Columns[i].ColParams[ERP_COL_INDEX_PERIODICAL]) <> '1') )then
        begin
        lkStr := '';
        if GetField(FBDataBase, aDBG.Columns[i].ColParams[ERP_COL_INDEX_REF_TABLE], aDBG.Columns[i].ColParams[ERP_COL_INDEX_REF_FIELD], 
             aDBG.Columns[i].ColParams[ERP_COL_INDEX_REF_KEYFIELD]+ '='''+DataSet.FieldByName(aDBG.Columns[i].ColParams[ERP_COL_INDEX_FIELD]).AsString+''' ', 
             lkStr)then
          DataSet.FieldByName(aDBG.Columns[i].ColParams[ERP_COL_INDEX_FIELD]+ERP_SQL_FIELDSUFFIX).AsString := lkStr;
        end;
      end;  
  end;
