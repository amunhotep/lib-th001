{$DEFINE PEAKTOP:IDE/ERP/CONFIG/RPTI/ECDA7A07-5697-4D05-9EE4-05D645433EDE/DEFAULT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}             {$I PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$I PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}     {$I PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}            {$I PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                      {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC}                      {$ENDIF}
const
  objname_datefrom   = 'dtpDateFrom';
  objname_dateto     = 'dtpDateTo';
  objname_firms      = 'gbFirms';
  objname_acc        = 'edtACC';
  msg_input_firms    = 'Выберите фирмы учета';
  msg_debetin        = 'В дебет счёта с кредита счетов';
  msg_kreditin       = 'В кредит счёта с дебета счетов';
const
  DefaultColumnWidth = 80;  
  DefaultPrefix      = 'SALDO';
  //============================================================================
  function TERPFormRpti_GetExportFilter(aOwner:TComponent):string;
  begin
    Result := msg_erp_lbldatefrom+' "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+'" '+
      msg_erp_lbldateto  +' "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto))+'" '+SQLCRLF+
      '  Фирмы учета: "'+InputIntf_Ref_GetNames(aOwner.FindComponent(objname_firms))+'"'+SQLCRLF+
      '  Счет учета: "'+TxcEditCombo(aOwner.FindComponent(objname_acc)).Text+'"';
  end;
  //============================================================================
  procedure TERPFormRpti_Columns_OnEditButtonClick(Sender :TObject; var Handled :Boolean);
  var
    lkDBG    :TDBGridEh;
    lkCmp    :TComponent;
    lkCol    :TColumnEh;
    lkSubkonto:string;
    lkScript :string;
  begin
    Handled := true;
    lkDBG   := TDBGridEh(TComponent(Sender).Owner.Owner);
    if not lkDBG.DataSource.DataSet.Active then exit;
    lkCol   := lkDBG.Columns[lkDBG.SelectedIndex];
    if(lkCol=nil)then exit;
    lkSubkonto := '';
    if(lkCol.ColParams[0] = '1')then
      begin
      lkSubkonto := '  TERPFormGrid_DataSetFilter_Add(''ACC_ID_DEB'', ''ACC_ID_DEB = '+lkDBG.DataSource.DataSet.FieldByName('ACC_ID').AsString+' ''); '+SQLCRLF;
      if(StrTrimAll(lkCol.ColParams[1]) <> '')then
        lkSubkonto := lkSubkonto + '  TERPFormGrid_DataSetFilter_Add(''SUBKONTO_ID_KRED'', ''ACC_IDS_KRED CONTAINING ''''~'+lkCol.ColParams[1]+'~'''' ''); '+SQLCRLF;
      end
     else
      begin
      lkSubkonto := '  TERPFormGrid_DataSetFilter_Add(''ACC_ID_KRED'', ''ACC_ID_KRED = '+lkDBG.DataSource.DataSet.FieldByName('ACC_ID').AsString+' ''); '+SQLCRLF;
      if(StrTrimAll(lkCol.ColParams[1]) <> '')then
        lkSubkonto := lkSubkonto + '  TERPFormGrid_DataSetFilter_Add(''SUBKONTO_ID_DEB'', ''ACC_IDS_DEB CONTAINING ''''~'+lkCol.ColParams[1]+'~'''' ''); '+SQLCRLF;
      end; 
    if(lkCol.ColParams[2] <> '-1')then
      begin
      lkSubkonto := lkSubkonto + '  TERPFormGrid_DataSetFilter_Add(''FILIAL_ID'', ''FILIAL_ID = '+lkCol.ColParams[2]+' ''); '+SQLCRLF;
      end;
    lkScript := 
      '{$IFNDEF PEAKTOP:IDE/ERP/DBO/REG/FORMREG.INC} {$I PEAKTOP:IDE/ERP/DBO/REG/FORMREG.INC} {$ENDIF} '+SQLCRLF+
      'begin '+SQLCRLF+
      '  TERPFormGrid_DataSetFilter_DateInit := true; '+SQLCRLF+
      '  TERPFormGrid_DataSetFilter_DateFrom := StrToDate('''+FormatDateTime('dd.mm.yyyy',lkDBG.DataSource.DataSet.FieldByName('DATE_COMMIT').AsDateTime)+'''); '+SQLCRLF+ 
      '  TERPFormGrid_DataSetFilter_DateTo   := StrToDate('''+FormatDateTime('dd.mm.yyyy',lkDBG.DataSource.DataSet.FieldByName('DATE_COMMIT').AsDateTime)+'''); '+SQLCRLF+
      '  TERPFormGrid_DataSetFilter_Add(''FIRM_ID'', '' '''''+InputIntf_Ref_GetIds(lkDBG.Owner.FindComponent(objname_firms))+''''' CONTAINING ''''~''''||FIRM_ID||''''~'''' ''); '+SQLCRLF+
      lkSubkonto+
      '  Registry_Create(''TABL$P_CND''); '+SQLCRLF+ 
      'end.';
    //Dialogs.MessageDlg(lkScript, mtInformation, [mbOK]);  
    run(lkScript, 'DB:CONFIG/REG/CND/DEFAULT.PS');
  end;
  //============================================================================
  function TERPFormRpti_OnGetSQL(aOwner:TComponent;var aSQL:string):Boolean;
  var
    lkFld     :string;
    lkSQLFlds :string;
    lkSQLSum  :string;
    lkSQLBody :string;
    lkSQLBody0:string;
    lkDocType :string;
    lkDBG     :TDBGridEh;
    lkCol     :TColumnEh;
    lkTr      :TxFBTransaction;
    lkQr      :TxFBQuery;
    lkQrFilial:TxFBQuery;
  begin
    Result := true;
    lkDBG  := TERPForm_DBGridMain(aOwner);
    lkDBG.FrozenCols := 0;
    lkDBG.Columns.Clear;
{
    lkCol       := CreateTColumnEh(lkDBG,'ACC_ID','','Счет'     , 48,taLeftJustify);
    lkCol.Color := Amunhotep.MainForm.StyleManager.Colors.Foreground;
    lkCol.Tag   := 666;
}
    lkCol := CreateTColumnEh(lkDBG,'DATE_COMMIT','dd.mm.yyyy','Дата проведения',68,taLeftJustify );
    with lkCol do
      begin
      Tag                  := 666;
      Color                := lkDBG.FixedColor;
      Footer.Color         := Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.ValueType     := fvtStaticText;
      Footer.Value         := 'ИТОГО';  
      end;
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'BEG_DEB','# ### ### ##0.00','Сальдо входящее|Дебет',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Footer.Color         := clWhite;
      Footer.Alignment     := Alignment;
      end;
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'BEG_KRD','# ### ### ##0.00','Сальдо входящее|Кредит',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Footer.Color         := clWhite;
      Footer.Alignment     := Alignment;
      end;
    lkSQLFlds  := '';
    lkSQLBody  := '';
    lkSQLBody0 := '';

    lkTr := TxFBTransaction.Create(nil);
    with lkTr do 
      begin 
      DefaultDataBase := FBDataBase; 
      Params.Clear; 
      Params.Add('isc_tpb_read_committed'); 
      Params.Add('isc_tpb_read'); 
      Params.Add('isc_tpb_rec_version'); 
      Params.Add('isc_tpb_nowait'); 
      end; 
    lkQr := TxFBQuery.Create(lkTr);
    lkQr.Transaction := lkTr;
    lkQrFilial             := TxFBQuery.Create(lkTr);
    lkQrFilial.Transaction := lkTr;
    lkQrFilial.SQL.Text    := 
      'SELECT DISTINCT C.FILIAL_ID AS ID, F.NAME '+SQLCRLF+
      'FROM   TABL$P_CND C, TABL$R_FILIALS F '+SQLCRLF+
      'WHERE  (C.DATE_COMMIT BETWEEN  '''+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00'' AND '''+
        FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto))+' 23:59:59'') '+SQLCRLF+
      '  AND  ('''+InputIntf_Ref_GetIds(aOwner.FindComponent(objname_firms))+''' CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '  AND  (F.ID = C.FILIAL_ID) '+SQLCRLF+
      'ORDER BY 1 ';
    lkQrFilial.Open;
      
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'_DEBET','# ### ### ##0.00','Оборот по счету|'+msg_debetin+'|ВСЕГО',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Color := $90FFA0;
      Font.Style           := [fsBold];
      Footer.Color         := Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtSum;
      AlwaysShowEditButton := true;
      if(EditButtons.Count = 0)then
        with EditButtons.Add do
          begin
          Visible := true;
          Style   := ebsEllipsisEh;
          OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
          end; 
      ColParams.Clear;
      ColParams.Add('1');  
      ColParams.Add('');  
      ColParams.Add('-1');  
      end;
    lkQr.SQL.Text := 
      'SELECT DISTINCT C.ACC_ID_KRED AS ACC_ID '+SQLCRLF+
      'FROM   TABL$P_CND C '+SQLCRLF+
      'WHERE  (C.DATE_COMMIT BETWEEN  '''+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00'' AND '''+
        FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto))+' 23:59:59'') '+SQLCRLF+
      '  AND  ('''+InputIntf_Ref_GetIds(aOwner.FindComponent(objname_firms))+''' CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '  AND  (C.ACC_IDS_DEB CONTAINING ''~'+IntToStr(aOwner.FindComponent(objname_acc).Tag)+'~'') '+SQLCRLF+
      'ORDER BY 1';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkFld     := DefaultPrefix+'D_'+FormatFloat('00000000', lkQr.FieldByName('ACC_ID').AsInteger);
      lkSQLFlds := lkSQLFlds  + '  ,'+lkFld+' TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF;
      lkSQLBody0:= lkSQLBody0 + '    '+lkFld+' = 0; '+SQLCRLF;
      lkSQLBody := lkSQLBody +
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
      '    WHERE  (C.DATE_COMMIT BETWEEN :DATE_COMMIT AND DATEADD(1 DAY TO :DATE_COMMIT)) '+SQLCRLF+
      '      AND  (:Q_FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND  (C.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '      AND  ((C.ACC_ID_KRED+0) = '+lkQr.FieldByName('ACC_ID').AsString+') '+SQLCRLF+
      '    INTO   :'+lkFld+'; '+SQLCRLF;
      lkCol := CreateTColumnEh(lkDBG,lkFld,'# ### ### ##0.00','Оборот по счету|'+msg_debetin+'|'+lkQr.FieldByName('ACC_ID').AsString+'|ВСЕ',DefaultColumnWidth,taRightJustify );
      with lkCol do
        begin
        Color                := $B0FFC0;
        Footer.Color         := Color;
        Footer.Alignment     := Alignment;
        Footer.DisplayFormat := DisplayFormat;
        Footer.FieldName     := FieldName;
        Footer.ValueType     := fvtSum;
        AlwaysShowEditButton := true;
        if(EditButtons.Count = 0)then
          with EditButtons.Add do
            begin
            Visible := true;
            Style   := ebsEllipsisEh;
            OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
            end; 
        ColParams.Clear;
        ColParams.Add('1');  
        ColParams.Add(lkQr.FieldByName('ACC_ID').AsString);  
        ColParams.Add('-1');  
        end;
      if not lkQrFilial.Active then
        lkQrFilial.Open;  
      lkQrFilial.First;
      while not lkQrFilial.EOF do
        begin
        lkFld     := DefaultPrefix+'D_'+FormatFloat('00000000', lkQr.FieldByName('ACC_ID').AsInteger)+'_'+lkQrFilial.FieldByName('ID').AsString;
        lkSQLFlds := lkSQLFlds  + '  ,'+lkFld+' TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF;
        lkSQLBody0:= lkSQLBody0 + '    '+lkFld+' = 0; '+SQLCRLF;
        lkSQLBody := lkSQLBody +
        '    SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
        '    WHERE  (C.DATE_COMMIT BETWEEN :DATE_COMMIT AND DATEADD(1 DAY TO :DATE_COMMIT)) '+SQLCRLF+
        '      AND  (:Q_FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
        '      AND  (C.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
        '      AND  ((C.ACC_ID_KRED+0) = '+lkQr.FieldByName('ACC_ID').AsString+') '+SQLCRLF+
        '      AND  ((C.FILIAL_ID+0) = '+lkQrFilial.FieldByName('ID').AsString+') '+SQLCRLF+
        '    INTO   :'+lkFld+'; '+SQLCRLF;
        lkCol := CreateTColumnEh(lkDBG,lkFld,'# ### ### ##0.00','Оборот по счету|'+msg_debetin+'|'+lkQr.FieldByName('ACC_ID').AsString+'|'+lkQrFilial.FieldByName('NAME').AsString,DefaultColumnWidth,taRightJustify );
        with lkCol do
          begin
          Color                := $D0FFE0;
          Footer.Color         := Color;
          Footer.Alignment     := Alignment;
          Footer.DisplayFormat := DisplayFormat;
          Footer.FieldName     := FieldName;
          Footer.ValueType     := fvtSum;
          AlwaysShowEditButton := true;
          if(EditButtons.Count = 0)then
            with EditButtons.Add do
              begin
              Visible := true;
              Style   := ebsEllipsisEh;
              OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
              end; 
          ColParams.Clear;
          ColParams.Add('1');  
          ColParams.Add(lkQr.FieldByName('ACC_ID').AsString);  
          ColParams.Add(lkQrFilial.FieldByName('ID').AsString);  
          end;
        lkQrFilial.Next;
        end;  
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    
    
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'_KREDIT','# ### ### ##0.00','Оборот по счету|'+msg_kreditin+'|ВСЕГО',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Color := $FFC0B0;
      Font.Style           := [fsBold];
      Footer.Color         := Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtSum;
      AlwaysShowEditButton := true;
      if(EditButtons.Count = 0)then
        with EditButtons.Add do
          begin
          Visible := true;
          Style   := ebsEllipsisEh;
          OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
          end; 
      ColParams.Clear;
      ColParams.Add('0');  
      ColParams.Add('');  
      ColParams.Add('-1');  
      end;
    lkQr.SQL.Text := 
      'SELECT DISTINCT C.ACC_ID_DEB AS ACC_ID '+SQLCRLF+
      'FROM   TABL$P_CND C '+SQLCRLF+
      'WHERE  (C.DATE_COMMIT BETWEEN  '''+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00'' AND '''+
        FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto))+' 23:59:59'') '+SQLCRLF+
      '  AND  ('''+InputIntf_Ref_GetIds(aOwner.FindComponent(objname_firms))+''' CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '  AND  (C.ACC_IDS_KRED CONTAINING ''~'+IntToStr(aOwner.FindComponent(objname_acc).Tag)+'~'') '+SQLCRLF+
      'ORDER BY 1';
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkFld     := DefaultPrefix+'K_'+FormatFloat('00000000', lkQr.FieldByName('ACC_ID').AsInteger);
      lkSQLFlds := lkSQLFlds + '  ,'+lkFld+' TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF;
      lkSQLBody0:= lkSQLBody0 + '    '+lkFld+' = 0; '+SQLCRLF;
      lkSQLBody := lkSQLBody +
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
      '    WHERE  (C.DATE_COMMIT BETWEEN :DATE_COMMIT AND DATEADD(1 DAY TO :DATE_COMMIT)) '+SQLCRLF+
      '      AND  (:Q_FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND  (C.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '      AND  ((C.ACC_ID_DEB+0) = '+lkQr.FieldByName('ACC_ID').AsString+') '+SQLCRLF+
      '    INTO   :'+lkFld+'; '+SQLCRLF;
      lkCol := CreateTColumnEh(lkDBG,lkFld,'# ### ### ##0.00','Оборот по счету|'+msg_kreditin+'|'+lkQr.FieldByName('ACC_ID').AsString+'|ВСЕ',DefaultColumnWidth,taRightJustify );
      with lkCol do
        begin
        Color                := $FFE0D0;
        Footer.Color         := Color;
        Footer.Alignment     := Alignment;
        Footer.DisplayFormat := DisplayFormat;
        Footer.FieldName     := FieldName;
        Footer.ValueType     := fvtSum;
        AlwaysShowEditButton := true;
        if(EditButtons.Count = 0)then
          with EditButtons.Add do
            begin
            Visible := true;
            Style   := ebsEllipsisEh;
            OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
            end; 
        ColParams.Clear;
        ColParams.Add('0');  
        ColParams.Add(lkQr.FieldByName('ACC_ID').AsString);  
        ColParams.Add('-1');  
        end;
      if not lkQrFilial.Active then
        lkQrFilial.Open;  
      lkQrFilial.First;
      while not lkQrFilial.EOF do
        begin
        lkFld     := DefaultPrefix+'K_'+FormatFloat('00000000', lkQr.FieldByName('ACC_ID').AsInteger)+'_'+lkQrFilial.FieldByName('ID').AsString;
        lkSQLFlds := lkSQLFlds + '  ,'+lkFld+' TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF;
        lkSQLBody0:= lkSQLBody0 + '    '+lkFld+' = 0; '+SQLCRLF;
        lkSQLBody := lkSQLBody +
        '    SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
        '    WHERE  (C.DATE_COMMIT BETWEEN :DATE_COMMIT AND DATEADD(1 DAY TO :DATE_COMMIT)) '+SQLCRLF+
        '      AND  (:Q_FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
        '      AND  (C.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
        '      AND  ((C.ACC_ID_DEB+0) = '+lkQr.FieldByName('ACC_ID').AsString+') '+SQLCRLF+
        '      AND  ((C.FILIAL_ID+0) = '+lkQrFilial.FieldByName('ID').AsString+') '+SQLCRLF+
        '    INTO   :'+lkFld+'; '+SQLCRLF;
        lkCol := CreateTColumnEh(lkDBG,lkFld,'# ### ### ##0.00','Оборот по счету|'+msg_kreditin+'|'+lkQr.FieldByName('ACC_ID').AsString+'|'+lkQrFilial.FieldByName('NAME').AsString,DefaultColumnWidth,taRightJustify );
        with lkCol do
          begin
          Color                := $FFF0F0;
          Footer.Color         := Color;
          Footer.Alignment     := Alignment;
          Footer.DisplayFormat := DisplayFormat;
          Footer.FieldName     := FieldName;
          Footer.ValueType     := fvtSum;
          AlwaysShowEditButton := true;
          if(EditButtons.Count = 0)then
            with EditButtons.Add do
              begin
              Visible := true;
              Style   := ebsEllipsisEh;
              OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
              end; 
          ColParams.Clear;
          ColParams.Add('0');  
          ColParams.Add(lkQr.FieldByName('ACC_ID').AsString);  
          ColParams.Add(lkQrFilial.FieldByName('ID').AsString);  
          end;
        lkQrFilial.Next;
        end;
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;

    lkTr.Free;  
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'END_DEB','# ### ### ##0.00','Сальдо исходящее|Дебет',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Color                := clWhite;
      Footer.Alignment     := Alignment;
      end;
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'END_KRD','# ### ### ##0.00','Сальдо исходящее|Кредит',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Color                := clWhite;
      Footer.Alignment     := Alignment;
      end;
    lkDBG.FrozenCols     := 3;
    lkDBG.SumList.Active := true;
    lkDBG.FooterRowCount := 1;  
    aSQL := 
      'EXECUTE BLOCK( '+SQLCRLF+
      '   Q_DATE_FROM      TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_FROM '+SQLCRLF+
      '  ,Q_DATE_TO        TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_TO '+SQLCRLF+
      '  ,Q_FIRM_IDS       TYPE OF COLUMN TABL$J_4.DOCSTR      = ?FIRM_IDS '+SQLCRLF+
      '  ,Q_ACC_ID         TYPE OF COLUMN TABL$R_BUHG_ACCS.ID  = ?ACC_ID '+SQLCRLF+
      ')RETURNS( '+SQLCRLF+
      '   DATE_FROM        TYPE OF COLUMN TABL$J_4.DATE_COMMIT '+SQLCRLF+
      '  ,DATE_TO          TYPE OF COLUMN TABL$J_4.DATE_COMMIT '+SQLCRLF+
      '  ,FIRM_IDS         TYPE OF COLUMN TABL$J_4.DOCSTR '+SQLCRLF+
      '  ,DATE_COMMIT      TYPE OF COLUMN TABL$J_4.DATE_COMMIT '+SQLCRLF+
      '  ,ACC_ID           TYPE OF COLUMN TABL$R_BUHG_ACCS.ID '+SQLCRLF+
      '  ,ACC_NAME         TYPE OF COLUMN TABL$R_BUHG_ACCS.NAME '+SQLCRLF+
      '  ,'+DefaultPrefix+'BEG        TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'BEG_DEB    TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'BEG_KRD    TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'_DEBET     TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'_KREDIT    TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'END        TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'END_DEB    TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'END_KRD    TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      lkSQLFlds+
      ')AS '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  DATE_FROM    = :Q_DATE_FROM; '+SQLCRLF+
      '  DATE_TO      = :Q_DATE_TO; '+SQLCRLF+
      '  DATE_COMMIT  = NULL; '+SQLCRLF+
      '  FIRM_IDS     = :Q_FIRM_IDS; '+SQLCRLF+
      '  ACC_ID       = :Q_ACC_ID; SELECT FIRST 1 B1.NAME FROM TABL$R_BUHG_ACCS B1 WHERE(B1.ID = :ACC_ID)INTO :ACC_NAME; '+SQLCRLF+
      '  '+DefaultPrefix+'BEG     = 0; '+DefaultPrefix+'BEG_DEB = 0; '+DefaultPrefix+'BEG_KRD = 0; '+DefaultPrefix+'_DEBET  = 0; '+SQLCRLF+
      '  '+DefaultPrefix+'END     = 0; '+DefaultPrefix+'END_DEB = 0; '+DefaultPrefix+'END_KRD = 0; '+DefaultPrefix+'_KREDIT = 0; '+SQLCRLF+
      '  IF(:Q_DATE_FROM > :Q_DATE_TO)THEN BEGIN SUSPEND; EXIT; END '+SQLCRLF+
      '  SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
      '  WHERE  (C.DATE_COMMIT < :DATE_FROM) '+SQLCRLF+
      '    AND  (:Q_FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '    AND  (C.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '  INTO   :'+DefaultPrefix+'BEG_DEB; '+SQLCRLF+
      '  SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
      '  WHERE  (C.DATE_COMMIT < :DATE_FROM) '+SQLCRLF+
      '    AND  (:Q_FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '    AND  (C.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '  INTO   :'+DefaultPrefix+'BEG_KRD; '+SQLCRLF+
      '  '+DefaultPrefix+'BEG = :'+DefaultPrefix+'BEG_DEB - :'+DefaultPrefix+'BEG_KRD; '+SQLCRLF+
      '  '+DefaultPrefix+'BEG_DEB = 0; '+DefaultPrefix+'BEG_KRD = 0; '+SQLCRLF+
      '  IF(:'+DefaultPrefix+'BEG < 0)THEN '+DefaultPrefix+'BEG_KRD = ABS(:'+DefaultPrefix+'BEG); ELSE '+DefaultPrefix+'BEG_DEB = :'+DefaultPrefix+'BEG; '+SQLCRLF+
      '  '+DefaultPrefix+'END_DEB = :'+DefaultPrefix+'BEG_DEB; '+DefaultPrefix+'END_KRD = :'+DefaultPrefix+'BEG_KRD; '+DefaultPrefix+'END = :'+DefaultPrefix+'BEG; '+SQLCRLF+
      '  DATE_COMMIT = :DATE_FROM; '+SQLCRLF+
      '  WHILE(:DATE_COMMIT < :DATE_TO)DO '+SQLCRLF+
      '    BEGIN '+SQLCRLF+
      '    '+DefaultPrefix+'BEG     = :'+DefaultPrefix+'END    ; '+DefaultPrefix+'END     = 0; '+SQLCRLF+
      '    '+DefaultPrefix+'BEG_DEB = :'+DefaultPrefix+'END_DEB; '+DefaultPrefix+'END_DEB = 0; '+SQLCRLF+
      '    '+DefaultPrefix+'BEG_KRD = :'+DefaultPrefix+'END_KRD; '+DefaultPrefix+'END_KRD = 0; '+SQLCRLF+
      lkSQLBody0+
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
      '    WHERE  (C.DATE_COMMIT BETWEEN :DATE_COMMIT AND DATEADD(1 DAY TO :DATE_COMMIT)) '+SQLCRLF+
      '      AND  (:Q_FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND  (C.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '    INTO   :'+DefaultPrefix+'_DEBET; '+SQLCRLF+
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
      '    WHERE  (C.DATE_COMMIT BETWEEN :DATE_COMMIT AND DATEADD(1 DAY TO :DATE_COMMIT)) '+SQLCRLF+
      '      AND  (:Q_FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND  (C.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '    INTO   :'+DefaultPrefix+'_KREDIT; '+SQLCRLF+
      '    '+DefaultPrefix+'END = :'+DefaultPrefix+'BEG + :'+DefaultPrefix+'_DEBET - :'+DefaultPrefix+'_KREDIT; '+SQLCRLF+
      '    IF(:'+DefaultPrefix+'END < 0)THEN '+DefaultPrefix+'END_KRD = ABS(:'+DefaultPrefix+'END); ELSE '+DefaultPrefix+'END_DEB = :'+DefaultPrefix+'END; '+SQLCRLF+
      lkSQLBody+
      '    SUSPEND; '+SQLCRLF+
      '    DATE_COMMIT = DATEADD(1 DAY TO :DATE_COMMIT); '+SQLCRLF+
      '    END '+SQLCRLF+
      'END';
  end;
  //============================================================================
  procedure TERPFormRpti_OnGetSQLFileName(aOwner:TComponent;var aFileName:string);
  begin
     // do nothing, default handler
  end;
  //============================================================================
  procedure TERPFormRpti_OnProcessParams(aOwner:TComponent;aQr :TxFBQuery);
  begin
    with aQr do
      begin
      ParamByName('FIRM_IDS' ).AsString := InputIntf_Ref_GetIds(aOwner.FindComponent(objname_firms));
      ParamByName('DATE_FROM').AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00';
      ParamByName('DATE_TO'  ).AsString := FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto)+1)+' 00:00:00';
      ParamByName('ACC_ID'   ).AsString := IntToStr(aOwner.FindComponent(objname_acc).Tag);
      end;  
  end;
  //============================================================================
  procedure TERPFormRpti_OnChart(aOwner:TComponent; aParent:TWinControl);
  var
    lkPC :TxcPageControlEx;
    lkTS :TxcTabSheet;
  begin
    aParent.Free;
    exit;
    lkPC := CreateTxcPageControlEx(aOwner, aParent, 'PCCharts', 0,0,600,600, alClient);
    lkPC.MultiLine := false;
    TxcPageControlEx_ActivateDefaultPage(lkPC);
  end;
  //============================================================================
  procedure TERPFormRpti_edtACC_OnButtonClick(Sender :TObject);
  var
    lkLastTop :Integer;
    lkGrb     :TxcGroupBox;
    lkEdt     :TxcEditCombo;
    lkStr     :string;
  begin
    with TxcEditCombo(Sender) do
      begin
      SetGlobalVariable('ACC_ID', IntToStr(Tag));
      call('DB:CONFIG/REF/BUHG_ACCS/DEFAULT_DLG.PS');
      lkStr := GetGlobalVariable('ACC_ID');
      if( (UpperCase(lkStr) = 'NULL') or (StrTrimAll(lkStr)='') )then exit;
      Tag := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_BUHG_ACCS', 'NAME', 'ID = '+lkStr, lkStr);
      Text := lkStr;
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_OnTerms(aOwner:TComponent;aParent:TWinControl);
  var
    lkLastTop :Integer;
    lkGrb     :TxcGroupBox;
    lkEdt     :TxcEditCombo;
    lkStr     :string;
  begin
    lkLastTop := 4;
    lkLastTop := lkLastTop + InputIntf_DatePeriod_Create(aOwner, aParent, 'gbDatePeriod', 'Укажите период', 4, lkLastTop, 44, 360,objname_datefrom,objname_dateto,StartOfTheMonth(Now),EndOfTheMonth(Now)).Height;
    lkLastTop := lkLastTop + 4;
    lkLastTop := lkLastTop + InputIntf_Ref_Create(aOwner,aParent,objname_firms   ,msg_input_firms   ,4,lkLastTop, 0,360,'TABL$R_FIRMS',TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME]).Height;
    lkLastTop := lkLastTop + 4;
    lkGrb     := CreateTxcGroupBox(aOwner, aParent, '', 'Выберите счет учета',alNone,4,lkLastTop,48,360);
    lkLastTop := lkLastTop + lkGrb.Height + 4;
    lkStr     := GetGlobalVariable('ACC_ID');
    if(StrTrimAll(lkStr) = '')then
      lkStr   := '311'; 
    lkEdt := CreateTxcEditCombo(aOwner,lkGrb,objname_acc,TERPForm_DefaultControlIndent,20,20,lkGrb.Width-(TERPForm_DefaultControlIndent*2));
    with lkEdt do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      GlyphKind     := gkEllipsis;
      ReadOnly      := true;
      AlwaysEnable  := true;
      Font.Style    := [fsBold];
      Tag           := StrToInt(lkStr);
      GetField(FBDataBase, 'TABL$R_BUHG_ACCS', 'NAME', 'ID = '+lkStr, lkStr);
      Text          := lkStr;
      OnButtonClick := @TERPFormRpti_edtACC_OnButtonClick;
      end;
  end;
  //============================================================================
  function TERPFormRpti_OnColumnsCreate(aOwner:TComponent; aDBG:TDBGridEh):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormRpti_DBGridEhMain_OnGetCellParams(Sender: TObject; Column: TColumnEh; 
              AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
   if(not(Column.Field.DataSet.Active))then exit;
   if(not(Column.Field.DataSet.RecordCount > 0))then exit;
   if(Column.Tag=666)then exit;
   if(Pos(DefaultPrefix, Column.FieldName) = 1)then 
     begin
     if(Column.Field.AsFloat = 0)then
       aFont.Color := Background;
     end; 
  end;
  //============================================================================
  procedure TERPFormRpti_OnColumnsCreated(aOwner:TComponent; aDBG:TDBGridEh);
  begin
    aDBG.OnGetCellParams := @TERPFormRpti_DBGridEhMain_OnGetCellParams;
  end;
  //============================================================================
  procedure TERPFormRpti_OnColumnsLoad(aOwner:TComponent; aDBG:TDBGridEh);
  begin
    // do nothing, default handler
  end;
  //============================================================================
  function TERPFormRpti_OnPrint(aOwner:TComponent):Boolean;
  var
    lkStr          :string;
    lkRpt          :TxReport;
    lkImg          :TxrImage;
    lkBndSummary   :TxrBand;
    lkBndDetail    :TxrBand;
    lkBndColHeader:TxrBand;
    lkLBL          :TxrLabel;
    lkExpr         :TxrExpression;
    i, lkLastLeft  :Integer;
    lkDBG          :TDBGridEh;
  begin
    Result := true; 
    lkDBG := TERPForm_DBGridMain(aOwner);
    lkStr := StringsLoadFromFile(StrAbsolutePath('./RPT_DEFAULT.XFM', ScriptName));
    lkRpt := TxReport(StrToComponent(lkStr));
    with lkRpt do
      begin
      Title    := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION];
      DataBase := FBDataBase;
      Page.Orientation := poLandscape;
      Page.PaperSize   := A4;
      if(lkDBG.Columns.Count > 12)then Page.PaperSize := A3;
//      if(lkDBG.Columns.Count > 19)then Page.PaperSize := A2;
      while(DataSets.Count < 2)do
        DataSets.Add;
      with DataSets[0] do
        begin  
        Name     := 'qrMain';
        SQL.Text := TERPForm_QueryMain(aOwner).SQL.Text;
        Query.Prepare;
        if(Query.Params.Count > 0)then
          TERPFormRpti_OnProcessParams(aOwner, Query);
        end;
      with DataSets[1] do
        begin  
        Name     := 'qrEnt';
        SQL.Text := StringsLoadFromFile(StrAbsolutePath('../../DOC/4/RPT_DEFAULT02_0.SQL', ScriptName));
        end;  
      end;
    lkBndColHeader  := TxrBand(lkRpt.FindComponent('bndColHeader'));
    lkBndDetail     := TxrBand(lkRpt.FindComponent('bndDetail'));
    lkBndSummary    := TxrBand(lkRpt.FindComponent('bndSummary'));
    lkImg := nil;
    if(lkRpt.FindComponent('ImgLogo')   <> nil)then lkImg := TxrImage(lkRpt.FindComponent('ImgLogo'));
    if(lkRpt.FindComponent('ImageLogo') <> nil)then lkImg := TxrImage(lkRpt.FindComponent('ImageLogo'));
    if(lkImg <> nil)then
      begin
      lkStr := StrAbsolutePath('../conf/ent/logo.bmp', Amunhotep.ExeName);
      if FileExists(lkStr)then
        try lkImg.Picture.LoadFromFile(lkStr) except end;
      end;
    lkLBL := nil;
    if(lkRpt.FindComponent('lblCaption') <> nil)then lkLBL := TxrLabel(lkRpt.FindComponent('lblCaption'));
    if(lkLBL <> nil)then
      lkLBL.Caption := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLECAPTION]+#13#10#$20#$20+TERPFormRpti_GetExportFilter(aOwner);
    
    lkLastLeft := 0;  
    with lkDBG do 
      for i:=0 to Columns.Count-1 do 
        if Columns[i].Visible then
      begin
      lkLBL := TxrLabel.Create(lkRpt);
      with lkLBL do
        begin
        Parent := lkBndColHeader;
        Left   := lkLastLeft;
        Top    := 0;
        Height := 48;
        Width  := Columns[i].Width;
        Color  := FixedColor;
        Alignment := taCenter;
        //     if(Columns[i].Tag = 666)then 
        Caption := StrReplaceStr(Columns[i].Title.Caption,'|',#13#10)
        with Font do
          begin
          Color := Columns[i].Title.Font.Color;
          Name  := Columns[i].Title.Font.Name;
          Style := Columns[i].Title.Font.Style;
          Size  := Columns[i].Title.Font.Size;
          end;
        with Frame do
          begin
          Width := 1;
          Left  := (i = 0);
          Top   := true;
          Bottom:= true;
          Right := true;
          end;
        end;
      lkExpr := TxrExpression.Create(lkRpt);
      with lkExpr do
        begin
        Parent := lkBndDetail;
        Left   := lkLastLeft;
        Top    := 0;
        Height := 16;
        Width  := Columns[i].Width;
        Color  := Columns[i].Color;
        if(Columns[i].Tag <> 666)then
          begin
          Expression := 'IF(qrMain.'+Columns[i].FieldName+'<>0, qrMain.'+Columns[i].FieldName+','''')';
          Mask       := Columns[i].DisplayFormat+#$20;
          end
         else
          begin
          Expression := 'FORMATDATETIME(''dd.mm.yyyy'', qrMain.'+Columns[i].FieldName+')';
          end;
        Alignment := Columns[i].Alignment;
        with Font do
          begin
          Color := Columns[i].Font.Color;
          Name  := Columns[i].Font.Name;
          Style := Columns[i].Font.Style;
          Size  := Columns[i].Font.Size;
          end;
        with Frame do
          begin
          Width := 1;
          Left  := (i = 0);
          Bottom:= true;
          Right := true;
          end;
        end;
      if(FooterRowCount > 0)then
        begin
        if(Columns[i].Footer.FieldName <> '')then
          begin
          lkExpr := TxrExpression.Create(lkRpt);
          with lkExpr do
            begin
            Parent := lkBndSummary;
            Left   := lkLastLeft;
            Top    := 0;
            Height := 16;
            Width  := Columns[i].Width;
            Color  := Columns[i].Footer.Color;
            Expression := 'SUM(qrMain.'+Columns[i].Footer.FieldName+')'
            Alignment := Columns[i].Footer.Alignment;
            Mask      := Columns[i].Footer.DisplayFormat+#$20;
            with Font do
              begin
              Color := Columns[i].Footer.Font.Color;
              Name  := Columns[i].Footer.Font.Name;
              Style := Columns[i].Footer.Font.Style;
              Size  := Columns[i].Footer.Font.Size;
              end;
            with Frame do
              begin
              Width := 1;
              Left  := (i = 0);
              Bottom:= true;
              Right := true;
              end;
            end;
          end
         else
          begin
          lkLBL := TxrLabel.Create(lkRpt);
          with lkLBL do
            begin
            Parent := lkBndSummary;
            Left   := lkLastLeft;
            Top    := 0;
            Height := 16;
            Width  := Columns[i].Width;
            Color  := FixedColor;
            Caption:= '';
            with Font do
              begin
              Color := Columns[i].Title.Font.Color;
              Name  := Columns[i].Title.Font.Name;
              Style := Columns[i].Title.Font.Style;
              Size  := Columns[i].Title.Font.Size;
              end;
            with Frame do
              begin
              Width := 1;
              Left  := (i = 0);
              Top   := false;
              Bottom:= true;
              Right := true;
              end;
            end;
          end; 
        end;  
      lkLastLeft := lkLastLeft + lkLBL.Width;
      end; 
    lkRpt.Prepare;
    lkRpt.Preview;
  end;
  //============================================================================
  procedure TERPFormRpti_BeforePreview(aOwner:TComponent; aRpt:TxReport);
  begin
    // do nothing, default handler
  end;
