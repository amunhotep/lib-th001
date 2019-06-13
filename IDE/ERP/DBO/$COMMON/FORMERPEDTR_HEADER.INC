{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERPEDTR_HEADER.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC}    {$I ./FORMERP_HEADER.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}     {$I ./FORMERP_NAMES.INC}   {$ENDIF}
  //============================================================================
  procedure TERPFormEdtr_FillStandardFormats(aSL :TStrings);
  begin
    aSL.Add('# ### ### ##0');
    aSL.Add('# ### ### ##0.00');
    aSL.Add('# ### ### ##0.000');
    aSL.Add('dd.mm.yyyy');
    aSL.Add('dd.mm.yyyy hh:nn:ss');
  end;
  //============================================================================
  function TERPFormEdtr_PageControlMain(aOwner :TComponent):TxcPageControlEx;
  begin
    Result := TxcPageControlEx(aOwner.FindComponent(obj_name_erp_pagecontrol));
  end;
  //============================================================================
  procedure TERPFormEdtr_CloseDataSets(aOwner :TComponent);
  begin
    with TERPForm_DataSetMain(aOwner)do
      begin
      if Active then
        begin
        if(State <> dsBrowse)then
          try Post; except Cancel; end;
        Close;
        end;
      if Transaction.InTransaction then
        Transaction.Commit;  
      end;
  end;
  //============================================================================
  procedure TERPFormEdtr_RefreshView(aOwner :TComponent);
  begin
    TERPFormEdtr_CloseDataSets(aOwner);
    with TERPForm_DataSetMain(aOwner)do
      begin
      SelectSQL.Text :=StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/MAIN_'{+FormatFloat('00',TERPForm_ObjType(aOwner))}+'02_SEL.SQL')); 
      RefreshSQL.Text:=StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/MAIN_'{+FormatFloat('00',TERPForm_ObjType(aOwner))}+'02_SEL.SQL')); 
      ModifySQL.Text :=StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/MAIN_'{+FormatFloat('00',TERPForm_ObjType(aOwner))}+'02_UPD.SQL')); 
      Prepare;
      ParamByName('OBJ_ID'  ).AsString := TERPForm_ObjId(aOwner); 
      ParamByName('OBJ_TYPE').AsString := IntToStr(TERPForm_ObjType(aOwner));
      try 
          Open;
        except
        end;
      end;
  end;  
