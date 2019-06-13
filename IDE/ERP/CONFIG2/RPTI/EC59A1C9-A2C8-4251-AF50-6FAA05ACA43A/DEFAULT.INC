{$DEFINE PEAKTOP:IDE/ERP/CONFIG/RPTI/EC59A1C9-A2C8-4251-AF50-6FAA05ACA43A/DEFAULT.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}             {$I PEAKTOP:IDE/ERP/DBO/RPTI/FORMRPTI.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REG.INC}  {$I PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REG.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}     {$I PEAKTOP:IDE/ERP/DBO/INPUT/DATEPERIOD/INTF.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}            {$I PEAKTOP:IDE/ERP/DBO/INPUT/REF/INTF.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/CHECKBOX/INTF.INC}       {$I PEAKTOP:IDE/ERP/DBO/INPUT/CHECKBOX/INTF.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                      {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC}                      {$ENDIF}
const
  objname_datefrom   = 'dtpDateFrom';
  objname_dateto     = 'dtpDateTo';
  objname_firms      = 'gbFirms';
  objname_acc        = 'edtACC';
  objname_showjrnl   = 'cbxShowJournal';
  msg_input_firms    = 'Выберите фирмы учета';
const
  DefaultColumnWidth = 80;  
  DefaultPrefix      = 'S0';
  DefaultTablePrefix = 'TMP';
  //============================================================================
  procedure TERPFormRpti_actDocEdt_OnExecute(Sender :TObject);
  begin
    with TERPForm_ActiveDataSet(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      if(FieldByName('J_ID').AsInteger = 0)then exit;
      SetGlobalVariable('J_ID', FieldByName('J_ID').AsString);
      call('DB:CONFIG/DOC/'+FieldByName('J_TYPE_ID').AsString+'/EDIT.PS');
      end;
  end;
  //============================================================================
  procedure TERPFormRpti_actJrnlGoTo_OnExecute(Sender :TObject);
  var
    lkScript :string;
  begin
    with TERPForm_ActiveDataSet(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not(RecordCount>0)then exit;
      if(FieldByName('J_ID').AsInteger = 0)then exit;
      SetGlobalVariable('J_ID'+ERP_SETTINGS_GOTOVAR, FieldByName('J_ID').AsString);
      call('DB:CONFIG/DOC/'+FieldByName('J_TYPE_ID').AsString+'/DEFAULT.PS');
      end;
  end;
  //============================================================================
  function TERPFormRpti_GetExportFilter(aOwner:TComponent):string;
  begin
    Result := 
      msg_erp_lbldatefrom+' "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+'" '+
      msg_erp_lbldateto  +' "'+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_dateto))+'" '+
      'Фирмы учета: "'+InputIntf_Ref_GetNames(aOwner.FindComponent(objname_firms))+
      '" Счет учета: "'+TxcEditCombo(aOwner.FindComponent(objname_acc)).Text+'"';
  end;
  //============================================================================
  function TERPFormRpti_OnGetSQL(aOwner:TComponent;var aSQL:string):Boolean;
  var
    lkShowJrnl:Boolean;
    lkFld     :string;
    lkFldD    :string;
    lkFldK    :string;
    lkFldI    :string;
    lkFldS    :string;
    lkSQLFlds :string;
    lkSQLSum  :string;
    lkSQLBody :string;
    lkSQLBody0:string;
    lkDocType :string;
    lkDBG     :TDBGridEh;
    lkCol     :TColumnEh;
    lkTr      :TxFBTransaction;
    lkQr      :TxFBQuery;
  begin
    Result := true;
    lkShowJrnl := (InputIntf_CheckBox_Checked(aOwner, objname_showjrnl) = '1');
    lkDBG  := TERPForm_DBGridMain(aOwner);
    lkDBG.FrozenCols := 0;
    lkDBG.Columns.Clear;
    lkDBG.RowHeight := 14;
    lkCol       := CreateTColumnEh(lkDBG,'ACC_ID','','Счет'     , 48,taLeftJustify);
    with lkCol do
      begin
      Color                := lkDBG.Color;
      HideDuplicates       := true;
      end;
    lkCol       := CreateTColumnEh(lkDBG,'SUBKONTO_ID','# ### ##0','Субконто|Код', 60,taRightJustify);
    with lkCol do
      begin
      Color                := lkDBG.Color;
      HideDuplicates       := true;
      Footer.Color         := Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtCount;
      end;
    lkCol := CreateTColumnEh(lkDBG,'SUBKONTO_NAME','','Субконто|Наименование',140,taLeftJustify );
    with lkCol do
      begin
      Color                := lkDBG.Color;
      HideDuplicates       := true;
      Footer.Color         := Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.ValueType     := fvtStaticText;
      Footer.Value         := 'ИТОГО';  
      end;
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'BEG_DEB','# ### ### ##0.00','Сальдо  входящее|Дебет',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Footer.Color         := lkDBG.FixedColor;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtSum;
      end;
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'BEG_KRD','# ### ### ##0.00','Сальдо  входящее|Кредит',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Footer.Color         := lkDBG.FixedColor;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtSum;
      end;
    lkSQLFlds  := '';
    lkFldD     := '';
    lkFldK     := '';
    lkFldI     := '';
    lkFldS     := '';
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
    lkQr.SQL.Text := 
      'SELECT DISTINCT C.ACC_ID_KRED AS ACC_ID '+SQLCRLF+
      'FROM   TABL$P_CND C '+SQLCRLF+
      'WHERE  (C.DATE_COMMIT BETWEEN '''+FormatDateTime('dd.mm.yyyy', InputIntf_DatePeriod_Date(aOwner, objname_datefrom))+' 00:00:00'' AND '''+
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
      lkFldS    := lkFldS + ',COALESCE(SUM('+DefaultTablePrefix+'.'+lkFld+'),0) AS '+lkFld;
      lkFldD    := lkFldD + '              ,IIF((C.ACC_ID_KRED = '+lkQr.FieldByName('ACC_ID').AsString+'), COALESCE(C.CND_VALUE,0),0) AS '+lkFld+SQLCRLF;
      lkFldK    := lkFldK + '              ,CAST(0 AS DOMN$FLOAT) AS '+lkFld+SQLCRLF;
      lkFldI    := lkFldI + ',:'+lkFld;
      lkSQLBody0:= lkSQLBody0 + '    '+lkFld+' = 0; '+SQLCRLF;
      lkSQLBody := lkSQLBody +
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
      '    WHERE (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO) '+SQLCRLF+
      '      AND (:FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND (C.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '      AND (C.SUBKONTO_ID_DEB = :SUBKONTO_ID) '+SQLCRLF+
      '      AND ((C.ACC_ID_KRED+0) = '+lkQr.FieldByName('ACC_ID').AsString+') '+SQLCRLF+
      '    INTO   :'+lkFld+'; '+SQLCRLF;
      lkCol := CreateTColumnEh(lkDBG,lkFld,'# ### ### ##0.00','Оборот|В дебет счета|с кредита счетов|'+lkQr.FieldByName('ACC_ID').AsString,DefaultColumnWidth,taRightJustify );
      with lkCol do
        begin
        Color                := $B0FFC0;
        Footer.Color         := Color;
        Footer.Alignment     := Alignment;
        Footer.DisplayFormat := DisplayFormat;
        Footer.FieldName     := FieldName;
        Footer.ValueType     := fvtSum;
        AlwaysShowEditButton := true;
{
        if(EditButtons.Count = 0)then
          with EditButtons.Add do
            begin
            Visible := true;
            Style   := ebsEllipsisEh;
            OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
            end; 
}
        ColParams.Clear;
        ColParams.Add('1');  
        ColParams.Add(lkQr.FieldByName('ACC_ID').AsString);  
        end;
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'_DEBET','# ### ### ##0.00','Оборот|В дебет счета|В С Е Г О',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Color := $B0FFC0;
      Font.Style           := [fsBold];
      Footer.Color         := Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtSum;
      AlwaysShowEditButton := true;
{
      if(EditButtons.Count = 0)then
        with EditButtons.Add do
          begin
          Visible := true;
          Style   := ebsEllipsisEh;
          OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
          end; 
}
      ColParams.Clear;
      ColParams.Add('1');  
      ColParams.Add('');  
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
      lkFldS    := lkFldS + ',COALESCE(SUM('+DefaultTablePrefix+'.'+lkFld+'),0) AS '+lkFld;
      lkFldK    := lkFldK + '              ,IIF((C.ACC_ID_DEB = '+lkQr.FieldByName('ACC_ID').AsString+'), COALESCE(C.CND_VALUE,0),0) AS '+lkFld+SQLCRLF;
      lkFldD    := lkFldD + '              ,CAST(0 AS DOMN$FLOAT) AS '+lkFld+SQLCRLF;
      lkFldI    := lkFldI + ',:'+lkFld;
      lkSQLBody0:= lkSQLBody0 + '    '+lkFld+' = 0; '+SQLCRLF;
      lkSQLBody := lkSQLBody +
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) FROM TABL$P_CND C '+SQLCRLF+
      '    WHERE (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO) '+SQLCRLF+
      '      AND (:FIRM_IDS CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND (C.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '      AND (C.SUBKONTO_ID_KRED = :SUBKONTO_ID) '+SQLCRLF+
      '      AND ((C.ACC_ID_DEB+0) = '+lkQr.FieldByName('ACC_ID').AsString+') '+SQLCRLF+
      '    INTO   :'+lkFld+'; '+SQLCRLF;
      lkCol := CreateTColumnEh(lkDBG,lkFld,'# ### ### ##0.00','Оборот|С кредита счета|в дебет счетов|'+lkQr.FieldByName('ACC_ID').AsString,DefaultColumnWidth,taRightJustify );
      with lkCol do
        begin
        Color                := $FFE0D0;
        Footer.Color         := Color;
        Footer.Alignment     := Alignment;
        Footer.DisplayFormat := DisplayFormat;
        Footer.FieldName     := FieldName;
        Footer.ValueType     := fvtSum;
        AlwaysShowEditButton := true;
{
        if(EditButtons.Count = 0)then
          with EditButtons.Add do
            begin
            Visible := true;
            Style   := ebsEllipsisEh;
            OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
            end; 
}
        ColParams.Clear;
        ColParams.Add('0');  
        ColParams.Add(lkQr.FieldByName('ACC_ID').AsString);  
        end;
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'_KREDIT','# ### ### ##0.00','Оборот|С кредита счета|В С Е Г О',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Color := $FFE0D0;
      Font.Style           := [fsBold];
      Footer.Color         := Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtSum;
      AlwaysShowEditButton := true;
{
      if(EditButtons.Count = 0)then
        with EditButtons.Add do
          begin
          Visible := true;
          Style   := ebsEllipsisEh;
          OnClick := @TERPFormRpti_Columns_OnEditButtonClick;
          end; 
}
      ColParams.Clear;
      ColParams.Add('0');  
      ColParams.Add('');  
      end;

    lkTr.Free;  
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'END_DEB','# ### ### ##0.00','Сальдо  исходящее|Дебет',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Color                := lkDBG.Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtSum;
      end;
    lkCol := CreateTColumnEh(lkDBG,DefaultPrefix+'END_KRD','# ### ### ##0.00','Сальдо  исходящее|Кредит',DefaultColumnWidth,taRightJustify );
    with lkCol do
      begin
      Color                := lkDBG.Color;
      Footer.Alignment     := Alignment;
      Footer.DisplayFormat := DisplayFormat;
      Footer.FieldName     := FieldName;
      Footer.ValueType     := fvtSum;
      end;
    lkCol := CreateTColumnEh(lkDBG,'J_ID'          ,'# ### ##0'          ,'Документ|код'  , 60,taRightJustify);
    lkCol := CreateTColumnEh(lkDBG,'J_TYPE_NAME'   ,''                   ,'Документ|тип'  ,180,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'J_DOCNUMBERSTR',''                   ,'Документ|номер', 96,taLeftJustify );
    lkCol := CreateTColumnEh(lkDBG,'J_DATE_COMMIT' ,'dd.mm.yyyy hh:nn:ss','Документ|дата' ,104,taLeftJustify );
    lkDBG.FrozenCols     := 5;
    if lkShowJrnl then
      lkDBG.FooterRowCount := 0
     else   
      lkDBG.FooterRowCount := 1;
    lkDBG.SumList.Active := true;
    aSQL := 
      'EXECUTE BLOCK( '+SQLCRLF+
      '   Q_DATE_FROM    TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_FROM '+SQLCRLF+
      '  ,Q_DATE_TO      TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_TO '+SQLCRLF+
      '  ,Q_FIRM_IDS     TYPE OF COLUMN TABL$J_4.DOCSTR      = ?FIRM_IDS '+SQLCRLF+
      '  ,Q_ACC_ID       TYPE OF COLUMN TABL$R_BUHG_ACCS.ID  = ?ACC_ID '+SQLCRLF+
      ')RETURNS( '+SQLCRLF+
      '   DATE_FROM      TYPE OF COLUMN TABL$J_4.DATE_COMMIT '+SQLCRLF+
      '  ,DATE_TO        TYPE OF COLUMN TABL$J_4.DATE_COMMIT '+SQLCRLF+
      '  ,FIRM_IDS       TYPE OF COLUMN TABL$J_4.DOCSTR '+SQLCRLF+
      '  ,ACC_ID         TYPE OF COLUMN TABL$R_BUHG_ACCS.ID '+SQLCRLF+
      '  ,ACC_NAME       TYPE OF COLUMN TABL$R_BUHG_ACCS.NAME '+SQLCRLF+
      '  ,SUBKONTO_ID    TYPE OF COLUMN TABL$R_BUHG_ACCS.ID '+SQLCRLF+
      '  ,SUBKONTO_NAME  TYPE OF COLUMN TABL$R_BUHG_ACCS.NAME '+SQLCRLF+
      '  ,J_ID           TYPE OF COLUMN TABL$J_4.ID '+SQLCRLF+
      '  ,J_TYPE_ID      TYPE OF COLUMN TABL$J_4.TYPE_ID '+SQLCRLF+
      '  ,J_TYPE_NAME    TYPE OF COLUMN TABL$_TB_DOCS.NAME '+SQLCRLF+
      '  ,J_DOCNUMBERSTR TYPE OF COLUMN TABL$J_4.DOCNUMBERSTR '+SQLCRLF+
      '  ,J_DATE_COMMIT  TYPE OF COLUMN TABL$J_4.DATE_COMMIT '+SQLCRLF+
      '  ,COLOR_BGR      TYPE OF COLUMN TABL$_TB_DOCS.COLOR_BGR '+SQLCRLF+
      '  ,COLOR_FRG      TYPE OF COLUMN TABL$_TB_DOCS.COLOR_FRG '+SQLCRLF+
      '  ,'+DefaultPrefix+'BEG     TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'BEG_DEB TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'BEG_KRD TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'_DEBET  TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'_KREDIT TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'END     TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'END_DEB TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      '  ,'+DefaultPrefix+'END_KRD TYPE OF COLUMN TABL$P_CND.CND_VALUE '+SQLCRLF+
      lkSQLFlds+
      ')AS '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  DATE_FROM    = :Q_DATE_FROM; '+SQLCRLF+
      '  DATE_TO      = :Q_DATE_TO; '+SQLCRLF+
      '  FIRM_IDS     = :Q_FIRM_IDS; '+SQLCRLF+
      '  ACC_ID       = :Q_ACC_ID; SELECT FIRST 1 B1.NAME FROM TABL$R_BUHG_ACCS B1 WHERE(B1.ID = :ACC_ID)INTO :ACC_NAME; '+SQLCRLF+
      '  '+DefaultPrefix+'BEG     = 0; '+DefaultPrefix+'BEG_DEB = 0; '+DefaultPrefix+'BEG_KRD = 0; '+DefaultPrefix+'_DEBET  = 0; '+SQLCRLF+
      '  '+DefaultPrefix+'END     = 0; '+DefaultPrefix+'END_DEB = 0; '+DefaultPrefix+'END_KRD = 0; '+DefaultPrefix+'_KREDIT = 0; '+SQLCRLF+
      '  IF(:DATE_FROM > :DATE_TO)THEN BEGIN SUSPEND; EXIT; END '+SQLCRLF+
      '  FOR '+SQLCRLF+
      '    SELECT SS.SUBKONTO_ID, SS.SUBKONTO_NAME '+SQLCRLF+
      '    FROM   ( '+SQLCRLF+
      '            SELECT DISTINCT TMP.SUBKONTO_ID '+SQLCRLF+
      '                  ,(SELECT FIRST 1 P.SUBKONTO_NAME FROM PROC$R_BUHG_ACCS_SUBKONTO(:ACC_ID, TMP.SUBKONTO_ID) P) AS SUBKONTO_NAME '+SQLCRLF+
      '            FROM   ( '+SQLCRLF+
      '                    SELECT CK.SUBKONTO_ID_KRED AS SUBKONTO_ID '+SQLCRLF+
      '                    FROM   TABL$P_CND CK '+SQLCRLF+
      '                    WHERE  (CK.DATE_COMMIT <= :DATE_TO) '+SQLCRLF+
      '                      AND  (:FIRM_IDS       CONTAINING ''~''||CK.FIRM_ID||''~'') '+SQLCRLF+
      '                      AND  (CK.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '                    UNION ALL '+SQLCRLF+
      '                    SELECT CD.SUBKONTO_ID_DEB AS SUBKONTO_ID '+SQLCRLF+
      '                    FROM   TABL$P_CND CD '+SQLCRLF+
      '                    WHERE  (CD.DATE_COMMIT <= :DATE_TO) '+SQLCRLF+
      '                      AND  (:FIRM_IDS      CONTAINING ''~''||CD.FIRM_ID||''~'') '+SQLCRLF+
      '                      AND  (CD.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '                   )TMP '+SQLCRLF+
      '           )SS '+SQLCRLF+
      '    ORDER BY SS.SUBKONTO_NAME '+SQLCRLF+
      '    INTO   :SUBKONTO_ID, :SUBKONTO_NAME '+SQLCRLF+
      '  DO '+SQLCRLF+
      '    BEGIN '+SQLCRLF+
      '    J_ID = 0; J_TYPE_ID = 0; J_TYPE_NAME = ''''; J_DOCNUMBERSTR = ''''; J_DATE_COMMIT = NULL; COLOR_BGR = 0XFFF0F0; COLOR_FRG = 0X000000; '+SQLCRLF+
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) '+SQLCRLF+
      '    FROM   TABL$P_CND C '+SQLCRLF+
      '    WHERE  (C.DATE_COMMIT < :DATE_FROM) '+SQLCRLF+
      '      AND  (:FIRM_IDS   CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND  (C.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '      AND  (C.SUBKONTO_ID_DEB = :SUBKONTO_ID) '+SQLCRLF+
      '    INTO   :'+DefaultPrefix+'BEG_DEB; '+SQLCRLF+
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) '+SQLCRLF+
      '    FROM   TABL$P_CND C '+SQLCRLF+
      '    WHERE  (C.DATE_COMMIT < :DATE_FROM) '+SQLCRLF+
      '      AND  (:FIRM_IDS    CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND  (C.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '      AND  (C.SUBKONTO_ID_KRED = :SUBKONTO_ID) '+SQLCRLF+
      '    INTO   :'+DefaultPrefix+'BEG_KRD; '+SQLCRLF+
      '    '+DefaultPrefix+'BEG = :'+DefaultPrefix+'BEG_DEB - :'+DefaultPrefix+'BEG_KRD; '+SQLCRLF+
      '    '+DefaultPrefix+'BEG_DEB = 0; '+DefaultPrefix+'BEG_KRD = 0; '+SQLCRLF+
      '    IF(:'+DefaultPrefix+'BEG < 0)THEN '+DefaultPrefix+'BEG_KRD = ABS(:'+DefaultPrefix+'BEG); ELSE '+DefaultPrefix+'BEG_DEB = :'+DefaultPrefix+'BEG; '+SQLCRLF+
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) '+SQLCRLF+
      '    FROM  TABL$P_CND C '+SQLCRLF+
      '    WHERE (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO) '+SQLCRLF+
      '      AND (:FIRM_IDS     CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND (C.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '      AND (C.SUBKONTO_ID_DEB = :SUBKONTO_ID) '+SQLCRLF+
      '    INTO  :'+DefaultPrefix+'_DEBET; '+SQLCRLF+
      '    SELECT COALESCE(SUM(C.CND_VALUE),0) '+SQLCRLF+
      '    FROM   TABL$P_CND C '+SQLCRLF+
      '    WHERE (C.DATE_COMMIT  BETWEEN :DATE_FROM AND :DATE_TO) '+SQLCRLF+
      '      AND (:FIRM_IDS      CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+
      '      AND (C.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
      '      AND (C.SUBKONTO_ID_KRED = :SUBKONTO_ID) '+SQLCRLF+
      '    INTO  :'+DefaultPrefix+'_KREDIT; '+SQLCRLF+
      '    '+DefaultPrefix+'END = :'+DefaultPrefix+'BEG + :'+DefaultPrefix+'_DEBET - :'+DefaultPrefix+'_KREDIT; '+SQLCRLF+
      '    '+DefaultPrefix+'END_DEB = 0; '+DefaultPrefix+'END_KRD = 0; '+SQLCRLF+
      '    IF(:'+DefaultPrefix+'END < 0)THEN '+DefaultPrefix+'END_KRD = ABS(:'+DefaultPrefix+'END); ELSE '+DefaultPrefix+'END_DEB = :'+DefaultPrefix+'END; '+SQLCRLF+
      ' '+SQLCRLF+
      lkSQLBody0+
      lkSQLBody+
      '    SUSPEND; '+SQLCRLF;
    if lkShowJrnl then
      begin
      aSQL := aSQL +  
        '  '+DefaultPrefix+'BEG = 0; '+DefaultPrefix+'BEG_DEB = 0; '+DefaultPrefix+'BEG_KRD = 0;'+SQLCRLF+
        '  '+DefaultPrefix+'END = 0; '+DefaultPrefix+'END_DEB = 0; '+DefaultPrefix+'END_KRD = 0;'+SQLCRLF+
        '  '+DefaultPrefix+'_DEBET  = 0; '+DefaultPrefix+'_KREDIT = 0;'+SQLCRLF+
        '    FOR '+SQLCRLF+
        '      SELECT '+DefaultTablePrefix+'.DATE_COMMIT, '+DefaultTablePrefix+'.J_ID '+SQLCRLF+
        '            '+lkFldS+' '+SQLCRLF+
        '      FROM   ( '+SQLCRLF+
        '        SELECT C.DATE_COMMIT, C.J_ID '+SQLCRLF+lkFldD+
        '        FROM  TABL$P_CND C '+SQLCRLF+
        '        WHERE (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO) '+SQLCRLF+ 
        '          AND (:FIRM_IDS   CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+ 
        '          AND (C.ACC_IDS_DEB CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+ 
        '          AND (C.SUBKONTO_ID_DEB = :SUBKONTO_ID) '+SQLCRLF+
        '        UNION ALL '+SQLCRLF+
        '        SELECT C.DATE_COMMIT, C.J_ID '+SQLCRLF+lkFldK+
        '        FROM  TABL$P_CND C '+SQLCRLF+
        '        WHERE (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO) '+SQLCRLF+ 
        '          AND (:FIRM_IDS    CONTAINING ''~''||C.FIRM_ID||''~'') '+SQLCRLF+ 
        '          AND (C.ACC_IDS_KRED CONTAINING ''~''||:ACC_ID||''~'') '+SQLCRLF+
        '          AND (C.SUBKONTO_ID_KRED = :SUBKONTO_ID) '+SQLCRLF+
        '      )'+DefaultTablePrefix+' '+SQLCRLF+
        '      GROUP BY '+DefaultTablePrefix+'.DATE_COMMIT, '+DefaultTablePrefix+'.J_ID '+SQLCRLF+
        '      INTO :J_DATE_COMMIT, :J_ID'+lkFldI+' '+SQLCRLF+ 
        '    DO '+SQLCRLF+
        '      BEGIN '+SQLCRLF+
        '      IF(:J_ID <> 0)THEN '+SQLCRLF+
        '        BEGIN '+SQLCRLF+
        '        J_TYPE_ID = 0; J_TYPE_NAME = ''''; J_DOCNUMBERSTR = ''''; COLOR_BGR = 0xFFF0F0; COLOR_FRG = 0x000000; '+SQLCRLF+
        '        SELECT FIRST 1 J.TYPE_ID, DD.NAME, J.DOCNUMBERSTR, DD.COLOR_FRG, DD.COLOR_BGR '+SQLCRLF+
        '        FROM   TABL$J_4 J, TABL$_TB_DOCS DD '+SQLCRLF+
        '        WHERE  (J.ID = :J_ID)AND(DD.ID = J.TYPE_ID) '+SQLCRLF+
        '        INTO   :J_TYPE_ID, :J_TYPE_NAME, :J_DOCNUMBERSTR, :COLOR_FRG, :COLOR_BGR; '+SQLCRLF+
        '        END '+SQLCRLF+
        '      SUSPEND; '+SQLCRLF+
        '      END'+SQLCRLF;
      end;
    aSQL := aSQL +  
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
      lkStr   := '361'; 
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
    with InputIntf_CheckBox_Create  (aOwner,aParent,objname_showjrnl,'Раскрывать обороты по документам',4,lkLastTop, 20,360) do
      begin  
      Checked   := true;
      lkLastTop := lkLastTop + Height;
      end;
    lkLastTop := lkLastTop + 4;
  end;
  //============================================================================
  function TERPFormRpti_OnColumnsCreate(aOwner:TComponent; aDBG:TDBGridEh):Boolean;
  begin
    Result := false; // default handler
  end;
  //============================================================================
  procedure TERPFormRpti_DBGridEh_OnGetCellParams(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
    if(Column.Tag = 666)then exit;
    if(not(Column.Field.DataSet.Active))then exit;
    if(Column.Field.DataSet.RecordCount = 0)then exit;
    if(Column.Field.DataSet.FieldByName('J_ID').AsInteger = 0)then
      begin
      aFont.Size := 8;
      aFont.Style:= aFont.Style + [fsBold];
      if(TDBGridEh(Sender).FooterRowCount = 0)then
        Background := $DFD0D0;
      end
     else  
      begin
      aFont.Size := 7;
      aFont.Style:= aFont.Style - [fsBold];
      end;
    if(Pos(DefaultPrefix, UpperCase(Column.FieldName)) = 1)then
      begin
      if(Column.Field.AsFloat = 0)then
        aFont.Color := Background
       else 
        if(Column.Field.AsFloat < 0)then
          aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Error;
      exit;
      end;   
    if(Pos('J_', UpperCase(Column.FieldName)) = 1)then
      ERP_DBGridEh_OnGetCellParams_Jrnl(Sender, Column, AFont, Background, State)
  end;  
  //============================================================================
  procedure TERPFormRpti_OnColumnsCreated(aOwner:TComponent; aDBG:TDBGridEh);
  var
    lkToolBar :TxcGradientPanelVista;
    i :Integer; 
  begin
    lkToolBar := TxcGradientPanelVista(aOwner.FindComponent(obj_name_erp_toolbar_nav));
    TERPForm_CreateAction(aOwner,'actDocEdt'   ,'Открыть'      ,'Открыть документ'          ,'',0,375,@TERPFormRpti_actDocEdt_OnExecute   ,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
    TERPForm_CreateAction(aOwner,'actJrnlGoTo' ,'В журнал'     ,'Перейти в журнал документа','',0,462,@TERPFormRpti_actJrnlGoTo_OnExecute ,@TERPFormRpti_actPrintGrid_OnUpdate,lkToolBar,nil);
    lkToolBar.Width      := TWinControl_AutoWidth(lkToolBar)+2;
    aDBG.VTitleMargin    := 4;
    aDBG.OptionsEh       := aDBG.OptionsEh - [dghAutoSortMarking, dghMultiSortMarking];
    aDBG.OnDblClick      := @TERPFormRpti_actDocEdt_OnExecute;
    aDBG.OnGetCellParams := @TERPFormRpti_DBGridEh_OnGetCellParams;
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
    lkBndGroup     :TxrGroup;
    lkBndSummary   :TxrBand;
    lkBndDetail    :TxrBand;
    lkBndColHeader :TxrBand;
    lkLBL          :TxrLabel;
    lkLBLTOTAL     :TxrLabel;
    lkExpr         :TxrExpression;
    i, lkLastLeft  :Integer;
    lkColCount     :Integer;
    lkColWidth     :Integer;
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
    lkBndGroup      := TxrGroup(lkRpt.FindComponent('bndGroup'));
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

    lkColCount := 0;
    with lkDBG do 
      for i:=0 to Columns.Count-1 do
        if(Pos(DefaultPrefix, UpperCase(Columns[i].FieldName)) = 1)then 
          lkColCount := lkColCount + 1;
    with lkRpt do
      begin
      if(lkColCount >  9)then Page.PaperSize := A3;
//      if(lkColCount > 18)then Page.PaperSize := A2;
      end;

    lkLBLTOTAL := TxrLabel(lkRpt.FindComponent('lblTOTAL'));
    lkLastLeft := lkLBLTOTAL.Left+lkLBLTOTAL.Width;  
    with lkDBG do 
      for i:=0 to Columns.Count-1 do 
        if( (Pos(DefaultPrefix, UpperCase(Columns[i].FieldName)) = 1) and (Columns[i].Visible) )then
      begin
      lkColWidth := Trunc(Columns[i].Width * 9 / 10);

      lkLBL := TxrLabel.Create(lkBndColHeader);
      with lkLBL do
        begin
        Parent := lkBndColHeader;
        Left   := lkLastLeft;
        Top    := 0;
        Height := 64;
        Width  := lkColWidth;
        Color  := FixedColor;
        Alignment := taCenter;
        //     if(Columns[i].Tag = 666)then 
        Caption := StrReplaceStr(Columns[i].Title.Caption,'|',#13#10)
        with Font do
          begin
          Color := Columns[i].Title.Font.Color;
          Name  := Columns[i].Title.Font.Name;
          Style := Columns[i].Title.Font.Style;
          Size  := 6;
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
      lkExpr := TxrExpression.Create(lkBndGroup);
      with lkExpr do
        begin
        Parent := lkBndGroup;
        Left   := lkLastLeft;
        Top    := 0;
        Height := 16;
        Width  := lkColWidth;
        Expression := 'IF(qrMain.'+Columns[i].FieldName+'<>0, qrMain.'+Columns[i].FieldName+','''')';
        Mask       := Columns[i].DisplayFormat+#$20;
        Alignment := Columns[i].Alignment;
        with Font do
          begin
          Color := Columns[i].Font.Color;
          Name  := Columns[i].Font.Name;
          Style := [fsBold];
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
      lkExpr := TxrExpression.Create(lkBndDetail);
      with lkExpr do
        begin
        Parent := lkBndDetail;
        Left   := lkLastLeft;
        Top    := 0;
        Height := 16;
        Width  := lkColWidth;
        Color  := Columns[i].Color;
        ColorDataSetIndex     := 0;
        ColorDataSetField     := 'COLOR_BGR';
        ColorFontDataSetIndex := 0;
        ColorFontDataSetField := 'COLOR_FRG';
        Expression := 'IF(qrMain.J_ID<>0, IF(qrMain.'+Columns[i].FieldName+'<>0, qrMain.'+Columns[i].FieldName+',''''), '' '')';
        Mask       := Columns[i].DisplayFormat+#$20;
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
          lkExpr := TxrExpression.Create(lkBndSummary);
          with lkExpr do
            begin
            Parent := lkBndSummary;
            Left   := lkLastLeft;
            Top    := 0;
            Height := 16;
            Width  := lkColWidth;
            Color  := FixedColor;
            Expression := 'SUM(qrMain.'+Columns[i].Footer.FieldName+')'
            Alignment := Columns[i].Footer.Alignment;
            Mask      := Columns[i].Footer.DisplayFormat+#$20;
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
              Bottom:= true;
              Right := true;
              end;
            end;
          end
         else
          begin
          lkLBL := TxrLabel.Create(lkBndSummary);
          with lkLBL do
            begin
            Parent := lkBndSummary;
            Left   := lkLastLeft;
            Top    := 0;
            Height := 16;
            Width  := lkColWidth;
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
      lkLastLeft := lkLastLeft + lkColWidth;
      end; 

    if(InputIntf_CheckBox_Checked(aOwner, objname_showjrnl) <> '1')then  
      lkBndDetail.Free;
    lkRpt.Prepare;
    lkRpt.Preview;
  end;
  //============================================================================
  procedure TERPFormRpti_BeforePreview(aOwner:TComponent; aRpt:TxReport);
  begin
    // do nothing, default handler
  end;
