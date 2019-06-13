{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/COLATTRS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC}         {$I ./COL_PROTOCOL.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/IMAGELISTDLG.INC}           {$I ../OPER/IMAGELISTDLG.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}        {$I ../$COMMON/FORMERP_LANG.INC}             {$ENDIF}
  //==================== PEAKTOP:IDE/ERP/DBO/DBGRID/COLATTRS.INC ===============
  {$IFDEF MSWINDOWS}
  function ERP_DBEditEh_ShellExecute(hWindow :LongInt; Oper, FileName, Params, Dir: PChar; ShowCmd: LongInt):LongInt; external 'ShellExecuteA@shell32.dll stdcall';
  {$ENDIF}
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnURL_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkPath:string;
  begin
    Handled := true;
    lkPath  := '';
    if ObjectInheritsFrom(TComponent(Sender).Owner, 'TCustomDBEditEh') then
      lkPath := TCustomDBEditEh(TComponent(Sender).Owner).Field.AsString
     else
      with TDBGridEh(TComponent(Sender).Owner.Owner) do
        lkPath := Columns[SelectedIndex].Field.AsString;
    if(StrTrimAll(lkPath) <> '')then      
    {$IFDEF MSWINDOWS}
    ERP_DBEditEh_ShellExecute(Amunhotep.Handle, 'open', lkPath, '', '', 5); // 5 = SW_SHOW
    {$ENDIF}
  end; 
  //============================================================================
  function ERP_DBEditEh_GetDataSetField(Sender :TObject; var aDataSet:TDataSet; var aFieldName:string):Boolean;
  begin
    Result := false;
    if ObjectInheritsFrom(TComponent(Sender).Owner, 'TCustomDBEditEh') then
      with TCustomDBEditEh(TComponent(Sender).Owner) do
        begin
        aDataSet   := DataSource.DataSet;
        aFieldName := DataField;
        Result     := true;
        end
     else
      if ObjectInheritsFrom(TComponent(Sender).Owner.Owner, 'TCustomDBGridEh') then
        with TDBGridEh(TComponent(Sender).Owner.Owner) do
          begin
          aDataSet   := DataSource.DataSet;
          aFieldName := Columns[SelectedIndex].FieldName;
          Result     := true;
          end;
  end;
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnFileName_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkDataSet   :TDataSet;
    lkFieldName :string;
    lkFileName  :string;
  begin
    Handled := true;
    if not ERP_DBEditEh_GetDataSetField(Sender, lkDataSet, lkFieldName)then exit;
    lkFileName := lkDataSet.FieldByName(lkFieldName).AsString;
    if not PromptForFileName(lkFileName, '*.*', '', msg_erp_column_selectfile, '', false)then exit;
    with lkDataSet do
      begin
      if(State <> dsEdit)then Edit;
      FieldByName(lkFieldName).AsString := lkFileName;
      end;
  end; 
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnGUID_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkGUID      :TGUID;
    lkDataSet   :TDataSet;
    lkFieldName :string;
  begin
    Handled := true;
    if not ERP_DBEditEh_GetDataSetField(Sender, lkDataSet, lkFieldName)then exit;
    CoCreateGUID(lkGUID);
    with lkDataSet do
      begin
      if(State <> dsEdit)then Edit;
      FieldByName(lkFieldName).AsString := StrTrimAll(Copy(GUIDToStr(lkGUID), 2, Length(GUIDToStr(lkGUID))-2));
      end;
  end;
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnFontName_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkFont      :string;
    lkDataSet   :TDataSet;
    lkFieldName :string;
    lkRes       :Boolean;
  begin
    Handled := true;
    if not ERP_DBEditEh_GetDataSetField(Sender, lkDataSet, lkFieldName)then exit;
    with lkDataSet do
      begin
      lkFont := FieldByName(lkFieldName).AsString;
      with TFontDialog.Create(nil) do
        begin
        Font.Name := lkFont;
        Font.Size := 10;
        Font.Style:= [fsBold];
        Device    := fdBoth;
        Options   := [fdForceFontExist, fdNoFaceSel, fdNoSizeSel, fdNoStyleSel];
        lkRes  := Execute;
        lkFont := Font.Name;
        Free;
        end;
      if not lkRes then exit;
      if(State <> dsEdit)then Edit;
      FieldByName(lkFieldName).AsString := lkFont;
      end;
  end;
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnImageIndex_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkIndx      :Integer;
    lkDataSet   :TDataSet;
    lkFieldName :string;
  begin
    Handled := true;
    if not ERP_DBEditEh_GetDataSetField(Sender, lkDataSet, lkFieldName)then exit;
    with lkDataSet do
      begin
      lkIndx := FieldByName(lkFieldName).AsInteger;
      if not Amunhotep_ImageListDialog_Execute(Amunhotep.MainForm.ImageListMain, lkIndx) then exit;
      if(State <> dsEdit)then Edit;
      FieldByName(lkFieldName).AsInteger := lkIndx;
      end;
  end; 
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnColor_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkClr       :TColor;
    lkDataSet   :TDataSet;
    lkFieldName :string;
  begin
    Handled := true;
    if not ERP_DBEditEh_GetDataSetField(Sender, lkDataSet, lkFieldName)then exit;
    with lkDataSet do
      begin
      lkClr := FieldByName(lkFieldName).AsInteger;
      if not Dialogs.SelectColor(lkClr) then exit;
      if(State <> dsEdit)then Edit;
      FieldByName(lkFieldName).AsInteger := lkClr;
      end;
  end; 
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnEdit_OnClick(Sender :TObject; var Handled :Boolean);
  var
    lkS   :string; 
    lkVal :string;
    i     :Integer;
    lkCol :TColumnEh;
    lkDBG :TDBGridEh;
  begin
    Handled := true;
    if ObjectInheritsFrom(TComponent(Sender).Owner, 'TCustomDBEditEh') then
      begin
      with TCustomDBEditEh(TComponent(Sender).Owner) do
        begin
        for i:=0 to Parent.ControlCount-1 do
          if ObjectInheritsFrom(Parent.Controls[i],'TCustomDBEditEh')then
            if(TCustomDBEditEh(Parent.Controls[i]).ColParams[ERP_COL_INDEX_REF_BUFFERVAR] <> '')then
              SetGlobalVariable(ColParams[ERP_COL_INDEX_REF_BUFFERVAR], DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString);
        SetGlobalVariable(ColParams[ERP_COL_INDEX_REF_BUFFERVAR], DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString);
        call(ColParams[ERP_COL_INDEX_REF_SCRIPTDLG]);
        lkS := GetGlobalVariable(ColParams[ERP_COL_INDEX_REF_BUFFERVAR]);
        if( (lkS<>'') and (lkS<>'NULL') )then
          begin
          if(DataSource.DataSet.State = dsBrowse)then
            begin
            if(DataSource.DataSet.RecordCount > 0)then
              DataSource.DataSet.Edit
             else
              DataSource.DataSet.Insert;
            end;
          DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString := lkS;
          //WriteLn('ID='+lkS);
          lkVal := '';
          GetField(FBDataBase, ColParams[ERP_COL_INDEX_REF_TABLE], ColParams[ERP_COL_INDEX_REF_FIELD], 
            '('+ColParams[ERP_COL_INDEX_REF_KEYFIELD]+' = '''+StrReplaceStr(lkS,'''','''''')+''')', lkVal);
          //WriteLn('VAL='+lkVal);
          DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]+ERP_SQL_FIELDSUFFIX).AsString := lkVal;
          end;
       end;
      end
     else
      begin
      lkDBG := TDBGridEh(TComponent(Sender).Owner.Owner);
      lkCol := lkDBG.Columns[lkDBG.SelectedIndex];
      if(lkCol=nil)then exit;
      for i:=0 to lkDBG.Columns.Count-1 do
        if( (lkDBG.Columns[i] <> lkCol) and (StrTrimAll(lkDBG.Columns[i].ColParams[ERP_COL_INDEX_REF_BUFFERVAR]) <> '') )then
          SetGlobalVariable(lkDBG.Columns[i].ColParams[ERP_COL_INDEX_REF_BUFFERVAR], lkDBG.DataSource.DataSet.FieldByName(lkDBG.Columns[i].ColParams[ERP_COL_INDEX_FIELD]).AsString);
      SetGlobalVariable(lkCol.ColParams[ERP_COL_INDEX_REF_BUFFERVAR], lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[1]).AsString);
      call(lkCol.ColParams[ERP_COL_INDEX_REF_SCRIPTDLG]);
      lkS := GetGlobalVariable(lkCol.ColParams[ERP_COL_INDEX_REF_BUFFERVAR]);
      if( (lkS<>'') and (lkS<>'NULL') )then
        begin
        if(lkDBG.DataSource.DataSet.State = dsBrowse)then
          begin
          if(lkDBG.DataSource.DataSet.RecordCount > 0)then
            lkDBG.DataSource.DataSet.Edit
           else
            lkDBG.DataSource.DataSet.Insert;
          end;
        lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]).AsString := lkS;
        lkVal := '';
        GetField(FBDataBase, lkCol.ColParams[ERP_COL_INDEX_REF_TABLE], lkCol.ColParams[ERP_COL_INDEX_REF_FIELD], '('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+' = '''+StrReplaceStr(lkS,'''','''''')+''')', lkVal);
        lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]+ERP_SQL_FIELDSUFFIX).AsString := lkVal;
        end;
      end;    
  end; 
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnEditItem_OnClick(Sender :TObject; var Handled :Boolean);
  var
    i     :Integer;
    lkCol :TColumnEh;
    lkDBG :TDBGridEh;
  begin
    Handled := true;
    if ObjectInheritsFrom(TComponent(Sender).Owner, 'TCustomDBEditEh') then
      begin
      with TCustomDBEditEh(TComponent(Sender).Owner) do
        begin
        for i:=0 to Parent.ControlCount-1 do
          if ObjectInheritsFrom(Parent.Controls[i],'TCustomDBEditEh')then
            if(TCustomDBEditEh(Parent.Controls[i]).ColParams[ERP_COL_INDEX_REF_BUFFERVAR] <> '')then
              SetGlobalVariable(ColParams[ERP_COL_INDEX_REF_BUFFERVAR], DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString);
        SetGlobalVariable(ColParams[ERP_COL_INDEX_REF_BUFFERVAR], DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString);
        call(ColParams[ERP_COL_INDEX_REF_SCRIPTITEMDLG]);
       end;
      end
     else
      begin
      lkDBG := TDBGridEh(TComponent(Sender).Owner.Owner);
      lkCol := lkDBG.Columns[lkDBG.SelectedIndex];
      if(lkCol=nil)then exit;
      for i:=0 to lkDBG.Columns.Count-1 do
        if( (lkDBG.Columns[i] <> lkCol) and (StrTrimAll(lkDBG.Columns[i].ColParams[ERP_COL_INDEX_REF_BUFFERVAR]) <> '') )then
          SetGlobalVariable(lkDBG.Columns[i].ColParams[ERP_COL_INDEX_REF_BUFFERVAR], lkDBG.DataSource.DataSet.FieldByName(lkDBG.Columns[i].ColParams[ERP_COL_INDEX_FIELD]).AsString);
      SetGlobalVariable(lkCol.ColParams[ERP_COL_INDEX_REF_BUFFERVAR], lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[1]).AsString);
      call(lkCol.ColParams[ERP_COL_INDEX_REF_SCRIPTITEMDLG]);
      end;    
  end; 
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnClear_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkS    :string;
    lkCol  :TColumnEh;
    lkDBG  :TDBGridEh;
  begin
    Handled := true;
    if ObjectInheritsFrom(TComponent(Sender).Owner, 'TCustomDBEditEh') then
      begin
      with TCustomDBEditEh(TComponent(Sender).Owner) do
        begin
        if(ColParams.Count < ERP_COL_INDEX__COUNT)then exit;
        if(DataSource.DataSet.State = dsBrowse)then
          begin
          if(DataSource.DataSet.RecordCount > 0)then
            DataSource.DataSet.Edit
           else
            DataSource.DataSet.Insert;
          end;
        DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString := ColParams[ERP_COL_INDEX_VALUEEMPTY];
        if(StrTrimAll(ColParams[ERP_COL_INDEX_REF_TABLE]) <> '')then
          if GetField(FBDataBase, ColParams[ERP_COL_INDEX_REF_TABLE], ColParams[ERP_COL_INDEX_REF_FIELD], 
            '('+ColParams[ERP_COL_INDEX_REF_KEYFIELD]+' = '''+DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString+''')', lkS)then
            DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]+ERP_SQL_FIELDSUFFIX).AsString := lkS;
        Handled := true;
        end;
      end
     else
      begin
      lkDBG := TDBGridEh(TComponent(Sender).Owner.Owner);
      lkCol := lkDBG.Columns[lkDBG.SelectedIndex];
      if(lkCol=nil)then exit;
      if(lkCol.ColParams.Count < ERP_COL_INDEX__COUNT)then exit;
      if(lkDBG.DataSource.DataSet.State = dsBrowse)then
        begin
        if(lkDBG.DataSource.DataSet.RecordCount > 0)then
          lkDBG.DataSource.DataSet.Edit
         else
          lkDBG.DataSource.DataSet.Insert;
        end;
      lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]).AsString := lkCol.ColParams[ERP_COL_INDEX_VALUEEMPTY];
      if(StrTrimAll(lkCol.ColParams[ERP_COL_INDEX_REF_TABLE]) <> '')then
        if GetField(FBDataBase, lkCol.ColParams[ERP_COL_INDEX_REF_TABLE], lkCol.ColParams[ERP_COL_INDEX_REF_FIELD], 
          '('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+' = '''+lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]).AsString+''')', lkS)then
          lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]+ERP_SQL_FIELDSUFFIX).AsString := lkS;
      end;    
  end; 
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnDefault_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkS    :string;
    lkCol  :TColumnEh;
    lkDBG  :TDBGridEh;
  begin
    Handled := true;
    if ObjectInheritsFrom(TComponent(Sender).Owner, 'TCustomDBEditEh') then
      begin
      with TCustomDBEditEh(TComponent(Sender).Owner) do
        begin
        if(ColParams.Count < ERP_COL_INDEX_FIELDTYPE)then exit;
        if(DataSource.DataSet.State = dsBrowse)then
          begin
          if(DataSource.DataSet.RecordCount > 0)then
            DataSource.DataSet.Edit
           else
            DataSource.DataSet.Insert;
          end;
        DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString := ColParams[ERP_COL_INDEX_VALUEDEFAULT];
        if(StrTrimAll(ColParams[ERP_COL_INDEX_REF_TABLE]) <> '')then
          if GetField(FBDataBase, ColParams[ERP_COL_INDEX_REF_TABLE], ColParams[ERP_COL_INDEX_REF_FIELD], 
            '('+ColParams[ERP_COL_INDEX_REF_KEYFIELD]+' = '''+DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString+''')', lkS)then
            DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]+ERP_SQL_FIELDSUFFIX).AsString := lkS;
        end;
      end
     else
      begin
      lkDBG := TDBGridEh(TComponent(Sender).Owner.Owner);
      lkCol := lkDBG.Columns[lkDBG.SelectedIndex];
      if(lkCol=nil)then exit;
      if(lkCol.ColParams.Count < ERP_COL_INDEX_FIELDTYPE)then exit;
      if(lkDBG.DataSource.DataSet.State = dsBrowse)then
        begin
        if(lkDBG.DataSource.DataSet.RecordCount > 0)then
          lkDBG.DataSource.DataSet.Edit
         else
          lkDBG.DataSource.DataSet.Insert;
        end;
      lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]).AsString := lkCol.ColParams[ERP_COL_INDEX_VALUEDEFAULT];
      if(StrTrimAll(lkCol.ColParams[ERP_COL_INDEX_REF_TABLE]) <> '')then
        if GetField(FBDataBase, lkCol.ColParams[ERP_COL_INDEX_REF_TABLE], lkCol.ColParams[ERP_COL_INDEX_REF_FIELD], 
          '('+lkCol.ColParams[ERP_COL_INDEX_REF_KEYFIELD]+' = '''+lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]).AsString+''')', lkS)then
          lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]+ERP_SQL_FIELDSUFFIX).AsString := lkS;
      end;     
  end;
  //============================================================================
  procedure ERP_DBEditEh_ColumnBtnSubkonto_OnClick(Sender :TObject; var Handled :Boolean);
  var
    lkAccId     :string;
    lkObjId     :string;
    lkBufferVar :string;
    lkScriptDlg :string;
    lkId        :string;
    lkCol       :TColumnEh;
    lkDBG       :TDBGridEh;
  begin
    Handled := true;
    lkObjId := '';
    if ObjectInheritsFrom(TComponent(Sender).Owner, 'TCustomDBEditEh') then
      with TCustomDBEditEh(TComponent(Sender).Owner) do
        begin
        if(ColParams[ERP_COL_INDEX_SUBKONTO_FIELD] = '')then exit;
        lkAccId := DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_SUBKONTO_FIELD]).AsString;
        GetField(FBDataBase, 'TABL$R_BUHG_ACCS','SUBKONTO', 'ID = '''+lkAccId+''' ', lkObjId);
        lkObjId := StrTrimAll(lkObjId);
        if(lkObjId = '')then
          begin
          Dialogs.MessageDlg('У бухгалтерского счета "'+lkAccId+'" в настройках не указано субконто.', mtWarning, [mbOK]);
          exit;
          end;
        GetField(FBDataBase, 'TABL$_TB', 'BUFFER_VAR', 'TRIM(ID) = '''+lkObjId+''' ', lkBufferVar);
        GetField(FBDataBase, 'TABL$_TB', 'SC_REF_DLG', 'TRIM(ID) = '''+lkObjId+''' ', lkScriptDlg);
        SetGlobalVariable(lkBufferVar, DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString);
        call(lkScriptDlg);
        lkId := GetGlobalVariable(lkBufferVar);;
        if( (StrTrimAll(lkId)='') or (UpperCase(lkId)= 'NULL') )then exit;
        if(DataSource.DataSet.State = dsBrowse)then
          begin
          if(DataSource.DataSet.RecordCount > 0)then
            DataSource.DataSet.Edit
           else
            DataSource.DataSet.Insert;
          end;
        DataSource.DataSet.FieldByName(ColParams[ERP_COL_INDEX_FIELD]).AsString := lkID;
        end
     else
      begin
      lkDBG := TDBGridEh(TComponent(Sender).Owner.Owner);
      lkCol := lkDBG.Columns[lkDBG.SelectedIndex];
      if(lkCol=nil)then exit;
      if(lkCol.ColParams[ERP_COL_INDEX_SUBKONTO_FIELD] = '')then exit;
      lkAccId := lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_SUBKONTO_FIELD]).AsString;
      GetField(FBDataBase, 'TABL$R_BUHG_ACCS','SUBKONTO', 'ID = '''+lkAccId+''' ', lkObjId);
      lkObjId := StrTrimAll(lkObjId);
      if(lkObjId = '')then
        begin
        Dialogs.MessageDlg('У бухгалтерского счета "'+lkAccId+'" в настройках не указано субконто.', mtWarning, [mbOK]);
        exit;
        end;
      GetField(FBDataBase, 'TABL$_TB', 'BUFFER_VAR', 'TRIM(ID) = '''+lkObjId+''' ', lkBufferVar);
      GetField(FBDataBase, 'TABL$_TB', 'SC_REF_DLG', 'TRIM(ID) = '''+lkObjId+''' ', lkScriptDlg);
      SetGlobalVariable(lkBufferVar, lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]).AsString);
      call(lkScriptDlg);
      lkId := GetGlobalVariable(lkBufferVar);;
      if( (StrTrimAll(lkId)='') or (UpperCase(lkId)= 'NULL') )then exit;
      if(lkDBG.DataSource.DataSet.State = dsBrowse)then
        begin
        if(lkDBG.DataSource.DataSet.RecordCount > 0)then
          lkDBG.DataSource.DataSet.Edit
         else
          lkDBG.DataSource.DataSet.Insert;
        end;
      lkDBG.DataSource.DataSet.FieldByName(lkCol.ColParams[ERP_COL_INDEX_FIELD]).AsString := lkID;
      end;    
  end; 
  //============================================================================
  procedure ERP_DBEditEh_EditButtons_Add(aEditButtons :TEditButtonsEh; const aFieldType:string; 
             const aBtnSetNULL, aBtnSetDEFAULT:Boolean);
  begin
    if(Pos('DOMN$GUID', aFieldType) = 1)then
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN007.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_genguid;
        OnClick := @ERP_DBEditEh_ColumnBtnGUID_OnClick;
        end;
    if(Pos('DOMN$FONT_NAME', aFieldType) = 1)then
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN000.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_genguid;
        OnClick := @ERP_DBEditEh_ColumnBtnFontName_OnClick;
        end;
    if(Pos('DOMN$IMAGE_INDEX', aFieldType) = 1)then
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN000.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_selectimage;
        OnClick := @ERP_DBEditEh_ColumnBtnImageIndex_OnClick;
        end;
    if(Pos('DOMN$COLOR', aFieldType) = 1)then
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN000.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_selectcolor;
        OnClick := @ERP_DBEditEh_ColumnBtnColor_OnClick;
        end;
    if(Pos('DOMN$PSTRING_URL', aFieldType)=1)then
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTNURL.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_openurl;
        OnClick := @ERP_DBEditEh_ColumnBtnURL_OnClick;
        end;
    if(Pos('DOMN$FILENAME', aFieldType) = 1)then
      begin
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTNOPEN.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_selectfile2;
        OnClick := @ERP_DBEditEh_ColumnBtnFileName_OnClick;
        end;
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTNRUN.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_openfile;
        OnClick := @ERP_DBEditEh_ColumnBtnURL_OnClick;
        end;
      end;
    if aBtnSetNULL then
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN002.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_setnull;
        OnClick := @ERP_DBEditEh_ColumnBtnClear_OnClick;
        end;
    if aBtnSetDEFAULT then
      with aEditButtons.Add do
        begin
        Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN001.BMP'));
        Visible := true;
        Style   := ebsGlyphEh;
        Hint    := msg_erp_column_setdefault;
        OnClick := @ERP_DBEditEh_ColumnBtnDefault_OnClick;
        end
  end;
  //============================================================================
  function ERP_DBEditEh_Create(aParent:TWinControl; aDataSource:TDataSource; aQrLoad :TxFBQuery; const aCaption:string;
            const aLeft, aTop, aHeight, aWidth:Integer; const aReadOnly:Boolean):TCustomDBEditEh;
  var
    lkLBL       :TLabel;
    lkFieldType :string;
    i           :Integer;
  begin
    lkFieldType := UpperCase(aQrLoad.FieldByName('FIELD_TYPE').AsString);  
    lkLBL := CreateTLabel(aParent, aParent, aCaption, aLeft, aTop, TERPForm_DefaultControlHeight-TERPForm_DefaultControlIndent, aWidth, alNone, taLeftJustify);
    with lkLBL do
      begin
      Layout     := tlBottom;
      Hint       := aQrLoad.FieldByName('HINT').AsString;
      ShowHint   := true;
      Font.Style := [fsBold];
      ParentFont := true;
      end;
    Result := nil;  
    if( (StrTrimAll(aQrLoad.FieldByName('REF_TABLE').AsString) <> '') and (aQrLoad.FieldByName('FLAG_PERIODICAL').AsInteger <> 1) )then
      begin
      Result := TDBEditEh.Create(aParent);
      with TDBEditEh(Result)do
        begin 
        DataField  := aQrLoad.FieldByName('ID').AsString + ERP_SQL_FIELDSUFFIX; 
        if not aReadOnly then
          begin
          with EditButtons.Add do
            begin
            Visible := true;
            Style   := ebsGlyphEh;
            Hint    := msg_erp_column_select;
            OnClick := @ERP_DBEditEh_ColumnBtnEdit_OnClick;
            Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN000.BMP'));
            end;
          with EditButtons.Add do
            begin
            Visible := true;
            Style   := ebsGlyphEh;
            Hint    := msg_erp_column_edititem;
            OnClick := @ERP_DBEditEh_ColumnBtnEditItem_OnClick;
            Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN005.BMP'));
            end;
          end;  
        end
      end 
     else if(StrTrimAll(aQrLoad.FieldByName('SUBKONTO_FIELD').AsString) <> '')then
      begin
      Result := TDBEditEh.Create(aParent);
      with TDBEditEh(Result)do
        begin 
        if not aReadOnly then
          begin
          with EditButtons.Add do
            begin
            Visible := true;
            Style   := ebsGlyphEh;
            Hint    := msg_erp_column_select;
            OnClick := @ERP_DBEditEh_ColumnBtnSubkonto_OnClick;
            Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN000.BMP'));
            end;
          end;  
        end
      end 
     else if(StrTrimAll(aQrLoad.FieldByName('KEY_LIST').AsString) <> '')then
      begin
      Result := TDBComboBoxEh.Create(aParent);
      with TDBComboBoxEh(Result)do
        begin 
        KeyItems.Text := aQrLoad.FieldByName('KEY_LIST').AsString;  
        Items.Text    := aQrLoad.FieldByName('PICK_LIST').AsString;  
        end
      end
     else if((Pos('DOMN$DATE', lkFieldType)=1) or (Pos('DOMN$TIME', lkFieldType)=1) or (Pos('DOMN$DATETIME', lkFieldType)=1))then 
      begin
      Result := TDBDateTimeEditEh.Create(aParent);
      with TDBDateTimeEditEh(Result)do
        begin
        Kind       := dtkCustomEh;
        EditFormat := aQrLoad.FieldByName('FORMAT').AsString;
        end;
      end
     else if(   ((Pos('DOMN$FLOAT', lkFieldType)=1) or (Pos('DOMN$INTEGER', lkFieldType)=1) or (Pos('DOMN$LONGINT', lkFieldType)=1) or (Pos('DOMN$SMALLINT', lkFieldType)=1)) 
             and(StrTrimAll(aQrLoad.FieldByName('KEY_LIST').AsString) = '') 
             and( (StrTrimAll(aQrLoad.FieldByName('REF_TABLE').AsString) = '') or (aQrLoad.FieldByName('FLAG_PERIODICAL').AsInteger = 1) )
            )then
      begin
      Result := TDBNumberEditEh.Create(aParent);
      with TDBNumberEditEh(Result)do
        begin 
        DisplayFormat := aQrLoad.FieldByName('FORMAT').AsString;
        if not aReadOnly then
          with EditButton do
            begin
            Visible := true;
            Style   := ebsGlyphEh;
            Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN000.BMP'));
            end;  
        end;
      end
     else
      Result := TDBEditEh.Create(aParent);
    if(Result <> nil)then
      with Result do
        begin
        AutoSize   := false;
        Ctl3D      := false;
        Flat       := true; 
        Parent     := aParent;
        Left       := aLeft;
        Top        := lkLBL.Top + lkLBL.Height;
        Height     := TERPForm_DefaultControlHeight - TERPForm_DefaultControlIndent;
        Width      := aWidth; 
        Color      := aQrLoad.FieldByName('COLOR').AsInteger;
        Font.Style := [fsBold];
        Hint       := aQrLoad.FieldByName('HINT').AsString;
        ShowHint   := true;
        DataSource := aDataSource;
        if(DataField = '')then
          DataField := aQrLoad.FieldByName('ID').AsString;
        with ColParams do
          begin
          Clear;
          for i:=0 to ERP_COL_INDEX__COUNT-1 do
            Add(aQrLoad.FieldByName(ERP_COL_INDEX__FIELDS(i)).AsString);
          end;
        ReadOnly := aReadOnly or (aQrLoad.FieldByName('ACCS_FLAG_WRITE').AsInteger <= 0);
        if ReadOnly then
          begin
          Color := Amunhotep.MainForm.StyleManager.Colors.Foreground;
          EditButton.Visible := false;
          EditButtons.Clear;
          end
         else
          ERP_DBEditEh_EditButtons_Add(EditButtons, lkFieldType, (aQrLoad.FieldByName('FLAG_UPDNULL').AsInteger = 1), (aQrLoad.FieldByName('FLAG_UPDDEFAULT').AsInteger = 1));
        if( (StrTrimAll(aQrLoad.FieldByName('REF_TABLE').AsString) <> '') and (aQrLoad.FieldByName('FLAG_PERIODICAL').AsInteger <> 1) )then
          ReadOnly := true; // becasue we having edit button and no need to editing manually            
        end;
  end;  
