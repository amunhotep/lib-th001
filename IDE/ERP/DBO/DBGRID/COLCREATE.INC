{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/COLCREATE.INC}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                           {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC}         {$I ./FOOTERS_LOAD.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COLATTRS.INC}             {$I ./COLATTRS.INC}                          {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/DBGRID/COLCREATE.INC ================
  function ERP_ColumnEh_Create(aDBG:TDBGridEh;aQrLoad :TxFBQuery; const aReadOnly:Boolean):TColumnEh;
  var
    lkFieldType :string;
    i           :Integer;
  begin
    lkFieldType := UpperCase(aQrLoad.FieldByName('FIELD_TYPE').AsString);
    Result := CreateTColumnEh2(aDBG, aQrLoad.FieldByName('ID').AsString, aQrLoad.FieldByName('FORMAT').AsString, aQrLoad.FieldByName('NAME').AsString,
      aQrLoad.FieldByName('HINT').AsString, aQrLoad.FieldByName('WIDTH').AsInteger, aQrLoad.FieldByName('COL_INDEX').AsInteger,
      aQrLoad.FieldByName('ALIGNMENT').AsInteger, aQrLoad.FieldByName('COLOR').AsInteger,
      aQrLoad.FieldByName('KEY_LIST').AsString, aQrLoad.FieldByName('PICK_LIST').AsString, []);
    with Result do
      begin
      if(Color = Font.Color)then Color := Font.Color xor $FFFFFF; // for backward compatibility
      AutoDropDown := true;
      CheckBoxes   := (Pos('DOMN$BOOLEAN', lkFieldType) = 1); 
      Title.Orientation := IntToTTextOrientationEh(aQrLoad.FieldByName('ORIENTATION').AsInteger);
      with ColParams do
        begin
        Clear;
        for i:=0 to ERP_COL_INDEX__COUNT-1 do
          Add( aQrLoad.FieldByName( ERP_COL_INDEX__FIELDS(i) ).AsString );
        end;
      if(Pos('DOMN$IMAGE_INDEX', lkFieldType) = 1)then
        begin
        ImageList        := Amunhotep.MainForm.ImageListMain;
        ShowImageAndText := true;
        NotInKeyListIndex:= -1;
        with Amunhotep.MainForm.ImageListMain do
          for i:=0 to Count-1 do
            begin
            KeyList.Add(IntToStr(i));
            PickList.Add(IntToStr(i));
            end;   
        end;  
      if(aQrLoad.FieldByName('FLAG_FOOTER').AsInteger <> 0)then
        begin
        aDBG.FooterRowCount := MaxInteger(aDBG.FooterRowCount, aQrLoad.FieldByName('FOOTER_COUNT').AsInteger);
        ERP_DBGridEh_Column_FootersLoad(Result, aQrLoad.Transaction, aQrLoad.FieldByName('TB_ID').AsString, aQrLoad.FieldByName('ID').AsString);
        end;           
      ReadOnly := aReadOnly or (aQrLoad.FieldByName('ACCS_FLAG_WRITE').AsInteger = 0);
      if( (StrTrimAll(aQrLoad.FieldByName('REF_TABLE').AsString) <> '') and (aQrLoad.FieldByName('FLAG_PERIODICAL').AsInteger <> 1) )then
        begin
        DisplayFormat := '';
        FieldName     := Result.FieldName+ERP_SQL_FIELDSUFFIX;
        end;
      if ReadOnly then
        begin
        Color := Amunhotep.MainForm.StyleManager.Colors.Foreground or $A0A0A0;
        EditButtons.Clear;
        end
       else
        begin
        if( (aQrLoad.FieldByName('FLAG_PERIODICAL').AsInteger <> 1) and (StrTrimAll(aQrLoad.FieldByName('REF_TABLE').AsString) <> '') )then
          begin
          with EditButtons.Add do
            begin
            Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN000.BMP'));
            Visible := true;
            Style   := ebsGlyphEh;
            Hint    := msg_erp_column_select;
            OnClick := @ERP_DBEditEh_ColumnBtnEdit_OnClick;
            end;
          with EditButtons.Add do
            begin
            Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN005.BMP'));
            Visible := true;
            Style   := ebsGlyphEh;
            Hint    := msg_erp_column_edititem;
            OnClick := @ERP_DBEditEh_ColumnBtnEditItem_OnClick;
            end;
          ReadOnly := true; // display for reference items
          end
         else if(aQrLoad.FieldByName('SUBKONTO_FIELD').AsString <> '')then
          begin
          with EditButtons.Add do
            begin
            Glyph.LoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/DBGRID/BTN000.BMP'));
            Visible := true;
            Style   := ebsGlyphEh;
            Hint    := msg_erp_column_select;
            OnClick := @ERP_DBEditEh_ColumnBtnSubkonto_OnClick;
            end;
          ReadOnly := false; // change subkonto manually
          end
         else
          begin
          if(Pos('DOMN$FLOAT',lkFieldType) > 0)then 
            begin
{$IFNDEF AMUNHOTEP4800}          
            ButtonStyle := cbsDropDown;
{$ENDIF}          
            end;  
          end;   
        ERP_DBEditEh_EditButtons_Add(EditButtons, lkFieldType, (aQrLoad.FieldByName('FLAG_UPDNULL').AsInteger = 1), (aQrLoad.FieldByName('FLAG_UPDDEFAULT').AsInteger = 1));
        AlwaysShowEditButton := (not CheckBoxes) or (EditButtons.Count > 0);
        end 
      end;
  end; 
