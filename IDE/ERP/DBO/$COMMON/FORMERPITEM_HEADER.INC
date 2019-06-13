{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPITEM_HEADER.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}           {$I ../OBJECTNAMES.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC}{$I ./FORMERP_HEADER.INC} {$ENDIF}
  //============================================================================
  function TERPFormItem_PrintGrid(aOwner :TComponent):Boolean; forward;
  function TERPFormItem_PrintItem(aOwner :TComponent):Boolean; forward;
  //============================================================================
  function TERPFormItem_SQL(aOwner:TComponent):TStrings;
  begin
    with TxsStringsHolder(aOwner.FindComponent(obj_name_erp_data_settings)) do
      begin
      while(Items.Count < 2)do
        Items.Add;
      Result := Items[1].Strings;
      end;
  end;
  //============================================================================
  procedure TERPFormItem_CloseDataSets(aOwner :TComponent);
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
          Close;   
          end;
      TERPForm_TransactionMain(aOwner).Commit;
      end;
  end;
  //============================================================================
  procedure TERPFormItem_RefreshView(aOwner :TComponent);
  begin
    TERPFormItem_CloseDataSets(aOwner);
    with TERPForm_DataSetMain(aOwner) do
      begin
      SelectSQL.Text := TERPFormItem_SQL(aOwner).Text; 
      try
        Open;
      except
        WriteLn('Cannot open '+Name+' :'+ClassName);
      end;  
      end;
  end;
  //============================================================================
  procedure TERPFormItem_Destroy(aOwner :TComponent);
  begin
    if(aOwner.FindComponent(obj_name_erp_data_evmain) <> nil)then
      with TxFBEvents(aOwner.FindComponent(obj_name_erp_data_evmain))do
        if Registered then
          UnRegisterEvents;
    TERPFormItem_CloseDataSets(aOwner);
  end;
