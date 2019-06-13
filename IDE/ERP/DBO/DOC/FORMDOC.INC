{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/FORMDOC.INC}
{$IFNDEF PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}              {$I PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                            {$I PEAKTOP:OBJ/TLABEL.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                         {$I PEAKTOP:OBJ/TCOLUMNEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                         {$I PEAKTOP:OBJ/TDBGRIDEH.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDATETIMEPICKER.INC}                   {$I PEAKTOP:OBJ/TDATETIMEPICKER.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}                         {$I PEAKTOP:OBJ/TMENUITEM.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                         {$I PEAKTOP:OBJ/TSPLITTER.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                  {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}             {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                          {$I PEAKTOP:OBJ/TXCPANEL.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                  {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                  {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                       {$I PEAKTOP:OBJ/TXCTABSHEET.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSCROLLBOX.INC}                        {$I PEAKTOP:OBJ/TSCROLLBOX.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                      {$I PEAKTOP:OBJ/TXFBDATASETS.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBTREEVIEW.INC}                      {$I PEAKTOP:OBJ/TXFBTREEVIEW.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}                 {$I ../SHORTCUTS.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/ACTIONS.INC}            {$I ../DBGRID/ACTIONS.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/FOOTERS_LOAD.INC}       {$I ../DBGRID/FOOTERS_LOAD.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$I ../DBGRID/GETCELLPARAMS_JRNL.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COLATTRS.INC}           {$I ../DBGRID/COLATTRS.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COLCREATE.INC}          {$I ../DBGRID/COLCREATE.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC}      {$I ../$COMMON/FORMERP_BLOB.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}      {$I ../$COMMON/FORMERP_LANG.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}     {$I ../$COMMON/FORMERP_NAMES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}           {$I ../$COMMON/FORMERP.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/INTF_COMENTS.INC}          {$I ./INTF_COMENTS.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/INTF_DATAVIEW.INC}         {$I ./INTF_DATAVIEW.INC}                     {$ENDIF}
  //=================== PEAKTOP:IDE/ERP/DBO/DOC/FORMDOC.INC ====================
  function TERPFormDoc_Create(const aDocId :string):TAmunhotepForm; forward;
  procedure TERPFormDoc_DataSetMain_DoAfterScroll(lkOwner:TComponent; aDataSet:TDataSet); forward;
  //============================================================================
  procedure TERPFormDoc_CloseDataSets(aOwner :TComponent);
  begin
    with TERPForm_DataSetMain(aOwner) do
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
  procedure TERPFormDoc_RefreshView(aOwner :TComponent);
  begin
    TERPFormDoc_CloseDataSets(aOwner);
    with TERPForm_DataSetMain(aOwner) do
      begin
      SelectSQL.Text := TERPForm_SQL(aOwner).Text;
      Prepare;
      ParamByName(ERP_DATASET_DBKEY).AsString := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_SAVERECNO];
      try
        Open;
      except
        Dialogs.MessageDlg(SelectSQL.Text, mtError, [mbOK]);
      end;
      end;
  end;
  //============================================================================
  procedure TERPFormDoc_DataSetMain_DoAfterScroll(lkOwner :TComponent; DataSet :TDataSet);
  begin
  
  end;
  //============================================================================
  procedure TERPFormDoc_DataSetMain_AfterScroll(DataSet :TDataSet);
  var
    lkOwner :TComponent;
  begin
    lkOwner := DataSet.Owner.Owner;
    TERPFormDoc_DataSetMain_DoAfterScroll(lkOwner, DataSet);
    TERPForm_SetCaption(lkOwner, DataSet.FieldByName('TYPE_ID_').AsString+'  '+DataSet.FieldByName('DOCNUMBERSTR').AsString);
    Amunhotep.MainForm.TaskBar.ButtonByForm(TForm(lkOwner)).Caption := 
      '['+DataSet.FieldByName('DOCNUMBERSTR').AsString+'] '+DataSet.FieldByName('TYPE_ID_').AsString;
    with TScrollBox(lkOwner.FindComponent(obj_name_erp_scrollboxmain)) do
      begin
      Color      := DataSet.FieldByName('COLOR_BGR').AsInteger;
      Font.Color := DataSet.FieldByName('COLOR_FRG').AsInteger;
      end;  
  end;
  //============================================================================
  procedure TERPFormDoc_actViewRefresh_OnExecute(Sender :TObject);
  begin
    TERPFormDoc_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormDoc_actDocGotoJrnl_OnExecute(Sender :TObject);
  var
    lkVar :string;
  begin
    lkVar := StrTrimAll(TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_GOTOVAR]);
    if(lkVar = '')then exit;
    SetGlobalVariable(lkVar, TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_SAVERECNO]);
    call('DB:CONFIG/DOC/'+TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_BASETYPE]+'/DEFAULT.PS');
  end;    
  //============================================================================
  procedure TERPFormDoc_evMain_OnEventAlert(Sender :TObject; EventName: string; EventCount: LongInt; var CancelAlerts: Boolean);
  begin
    with TERPForm_DataSetMain(TComponent(Sender).Owner) do
      begin
      if(Active and (State = dsBrowse) )then
        TERPFormDoc_RefreshView(TComponent(Sender).Owner);
      end; 
    CancelAlerts := false;
  end;
  //============================================================================
  procedure TERPFormDoc_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end;
  //============================================================================
  procedure TERPFormDoc_LoadAttrs(aOwner:TComponent; aQr:TxFBQuery; aPageControlBLOB :TxcPageControlEx);
  var
    lkSettings     :TStrings;
    lkSB           :TScrollBox;
    lkQrChilds     :TxFBQuery;
    lkQrParents    :TxFBQuery;
    lkDBGChilds    :TDBGridEh;
    lkDBGParents   :TDBGridEh;
    lkEvents       :TxFBEvents;
    lkCol          :TColumnEh; 
    lkILLock       :TImageList;
    lkILDelete     :TImageList;
    lkILCommit     :TImageList;
    i,j,c,k        :Integer;
    lkCapt, lkHint :string;
    lkTitle        :string;
    lkFieldType    :string;
    lkS, lkS2      :string;
    lkSQLFldName   :string;
    lkSQLFields    :string;
    lkSQLFieldsCh  :string;
    lkSQLTables    :string;
    lkSQLTablesCh  :string;
    lkSQLTablesPa  :string;
    lkSQLWhere     :string;
    lkSQLWhereCh   :string;
    lkTablesList   :TArrayStringUnique;
    lkCaption      :string;
    lkSaveTop      :Integer;
    lkLastLeft     :Integer;
    lkTop          :Integer;
    lkWidth        :Integer;
    lkDBE          :TCustomDBEditEh;
  begin
    lkSettings := TERPForm_Settings(aOwner);
    lkSB         := TScrollBox(aOwner.FindComponent(obj_name_erp_scrollboxmain));
    lkEvents     := TxFBEvents(aOwner.FindComponent(obj_name_erp_data_evmain));
    lkQrChilds   := TxFBQuery(TERPForm_DataSetMain(aOwner).FindComponent(obj_name_erp_data_qrchilds));
    lkQrParents  := TxFBQuery(TERPForm_DataSetMain(aOwner).FindComponent(obj_name_erp_data_qrparents));
    lkDBGChilds  := TDBGridEh(aOwner.FindComponent(obj_name_erp_data_dbgchilds));
    lkDBGParents := TDBGridEh(aOwner.FindComponent(obj_name_erp_data_dbgparents));
    lkILDelete   := CreateTImageList(aOwner, 'ilDelete', [300,Amunhotep.MainForm.ImageListMain.Count-1]);
    lkILLock     := CreateTImageList(aOwner, 'ilLock'  , [224,Amunhotep.MainForm.ImageListMain.Count-1]);
    lkILCommit   := CreateTImageList(aOwner, 'ilCommit', [298,Amunhotep.MainForm.ImageListMain.Count-1]);
    i := 1; 
    SetLength(lkTablesList, 0);
    lkCapt      := ERP_SQL_TABLEPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT,IndexInArrayStringUnique(lkSettings.Values[ERP_SETTINGS_TABLENAME], lkTablesList));

    lkSQLTables := lkSettings.Values[ERP_SETTINGS_TABLENAME]+' '+lkCapt;  
    lkSQLFields := lkCapt+'.ID AS '+ERP_DATASET_DBKEY+' ';
    lkSQLWhere  := 'WHERE ('+lkCapt+'.ID = ?'+ERP_DATASET_DBKEY+') '+SQLCRLF;
    lkSQLTablesCh := 
      '(WITH RECURSIVE DOCTREE AS( '+SQLCRLF+
      '                SELECT DOCTREE1.J_ID, DOCTREE1.J_CHILD_ID, CAST(''|--+'' AS DOMN$PSTRING_8192) AS INDENT '+SQLCRLF+
      '                FROM   (SELECT JC.J_ID, JC.J_CHILD_ID FROM TABL$J_CHILDS JC WHERE  (JC.J_ID = ?'+ERP_DATASET_DBKEY+')ORDER BY JC.J_CHILD_ID ASCENDING ) DOCTREE1 '+SQLCRLF+
      '                UNION ALL '+SQLCRLF+
      '                SELECT DOCTREE2.J_ID, DOCTREE2.J_CHILD_ID, CAST(''   ''||DOCTREE3.INDENT AS DOMN$PSTRING_8192) '+SQLCRLF+
      '                FROM   TABL$J_CHILDS DOCTREE2, DOCTREE DOCTREE3 WHERE (DOCTREE2.J_ID = DOCTREE3.J_CHILD_ID) '+SQLCRLF+
      '            )SELECT T1.J_CHILD_ID, T1.INDENT FROM DOCTREE T1 ) AS '+ERP_SQL_RELATIONPREFIX+', '+lkSettings.Values[ERP_SETTINGS_TABLENAME]+' '+lkCapt;  
    lkSQLTablesPa := 
      '(WITH RECURSIVE DOCTREE AS( '+SQLCRLF+
      '                SELECT DOCTREE1.J_ID, DOCTREE1.J_CHILD_ID, CAST(''+--|'' AS DOMN$PSTRING_8192) AS INDENT '+SQLCRLF+
      '                FROM   (SELECT JC.J_ID, JC.J_CHILD_ID FROM TABL$J_CHILDS JC WHERE (JC.J_CHILD_ID = ?'+ERP_DATASET_DBKEY+')ORDER BY JC.J_ID DESCENDING ) DOCTREE1'+SQLCRLF+
      '                UNION ALL '+SQLCRLF+
      '                SELECT DOCTREE2.J_ID, DOCTREE2.J_CHILD_ID, CAST(''   ''||DOCTREE3.INDENT AS DOMN$PSTRING_8192) '+SQLCRLF+
      '                FROM   TABL$J_CHILDS DOCTREE2, DOCTREE DOCTREE3 WHERE (DOCTREE2.J_CHILD_ID = DOCTREE3.J_ID) '+SQLCRLF+
      '            )SELECT T1.J_ID AS J_CHILD_ID, T1.INDENT FROM DOCTREE T1 ) AS '+ERP_SQL_RELATIONPREFIX+', '+lkSettings.Values[ERP_SETTINGS_TABLENAME]+' '+lkCapt;  
    lkSQLFieldsCh := 'CAST('+ERP_SQL_RELATIONPREFIX+'.'+ERP_SQL_FIELDINDENT+' AS DOMN$PSTRING_8192) AS '+ERP_SQL_FIELDINDENT+', '+lkCapt+'.ID AS '+ERP_DATASET_DBKEY;
    lkSQLWhereCh  := 'WHERE ('+lkCapt+'.ID = '+ERP_SQL_RELATIONPREFIX+'.J_CHILD_ID)';
    C := 0;
    j := 0;
    lkLastLeft  := TERPForm_DefaultControlIndent;
    aQr.First;
    while not aQr.EOF do
      begin
      //WriteLn(aQr.FieldByName('COL_INDEX').AsString+'.'+aQr.FieldByName('ID').AsString+' = "'+aQr.FieldByName('NAME').AsString+'"');
      lkFieldType := UpperCase(aQr.FieldByName('FIELD_TYPE').AsString);  


      lkTitle     := aQr.FieldByName('NAME').AsString;
      lkCapt      := StrReplaceStr(lkTitle, '|',' / '); 
      if( (StrTrimAll(aQr.FieldByName('ID').AsString) = StrTrimAll(aQr.FieldByName('REF_KEYFIELD').AsString)) and 
          (StrTrimAll(aQr.FieldByName('REF_TABLE').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME]) )then
        begin
        lkSQLWhere := lkSQLWhere +'  AND ('+
        ERP_SQL_TABLEPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT,IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.'+
        aQr.FieldByName('ID').AsString+' = '+
        ERP_SQL_TABLEPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT,IndexInArrayStringUnique(lkSettings.Values[ERP_SETTINGS_TABLENAME], lkTablesList))+'.ID) '+SQLCRLF;
        end
       else 
        begin
        if(aQr.FieldByName('CALC_SQL').AsString <> '')then
          begin
          lkS := aQr.FieldByName('CALC_SQL').AsString;
          if(Pos('?', lkS) > 0)then
            lkS := StrReplaceStr(lkS, '?', ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.');  
          lkSQLFields := lkSQLFields + SQLCRLF + '      ,('+lkS+') AS '+aQr.FieldByName('ID').AsString;
          if(StrTrimAll(aQr.FieldByName('TB_ID').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME])then
            lkSQLFieldsCh := lkSQLFieldsCh + SQLCRLF + '      ,('+lkS+') AS '+aQr.FieldByName('ID').AsString;
          end
         else
          begin 
          lkSQLFldName := ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.'+aQr.FieldByName('ID').AsString;
          lkSQLFields  := lkSQLFields + SQLCRLF + '      ,'+ lkSQLFldName;
          if(StrTrimAll(aQr.FieldByName('TB_ID').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME])then
            lkSQLFieldsCh:= lkSQLFieldsCh +SQLCRLF+'      ,'+lkSQLFldName;
          if(aQr.FieldByName('REF_TABLE').AsString <> '')then
            begin
            C := C + 1;
            lkS := aQr.FieldByName('REF_TABLE').AsString;
            if(Pos('?', lkS) > 0)then 
              lkS := StrReplaceStr(lkS, '?', ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.');
            lkS2 := '(SELECT FIRST 1 '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, C)+'.'+aQr.FieldByName('REF_FIELD').AsString+
              ' FROM '+lkS+' '+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, C);
            if(aQr.FieldByName('REF_KEYFIELD').AsString <> '')then  
              lkS2 := lkS2 +' WHERE ('+ERP_SQL_RELATIONPREFIX+FormatFloat(ERP_SQL_FIELDFORMAT, C)+'.'+aQr.FieldByName('REF_KEYFIELD').AsString+' = '+lkSQLFldName+')';
            lkS2 := lkS2 +') AS '+aQr.FieldByName('ID').AsString+ERP_SQL_FIELDSUFFIX;
            lkSQLFields := lkSQLFields + SQLCRLF + '      ,' +lkS2; 
            if(StrTrimAll(aQr.FieldByName('TB_ID').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME])then
              lkSQLFieldsCh := lkSQLFieldsCh + SQLCRLF + '      ,' + lkS2;
            end;
          end;
        if(aQr.FieldByName('FLAG_DELETE').AsInteger = 0)then
          begin
          if( (Pos('DOMN$BLOB_', StrTrimAll(aQr.FieldByName('FIELD_TYPE').AsString)) = 1) and (aPageControlBLOB <> nil))then
            begin
            lkSQLFldName := ERP_SQL_TABLEPREFIX + FormatFloat(ERP_SQL_FIELDFORMAT, IndexInArrayStringUnique(aQr.FieldByName('TB_ID').AsString, lkTablesList))+'.'+aQr.FieldByName('ID').AsString;
            lkSQLFields  := lkSQLFields + SQLCRLF + '      ,'+ lkSQLFldName;
            TERPForm_BlobInterface_Create(lkQrChilds.DataSource, aPageControlBLOB, aQr.FieldByName('NAME').AsString, aQr.FieldByName('ID').AsString, aQr.FieldByName('FIELD_TYPE').AsString, (aQr.FieldByName('ACCS_FLAG_WRITE').AsInteger = 0));
            end
           else
            begin 
            if(aQr.FieldByName('EDT_TOP').AsInteger >= 0)then
              begin
              lkHint    := aQr.FieldByName('HINT').AsString; if(StrTrimAll(lkHint) = '')then lkHint := StrReplaceStr(lkTitle, '|', #13#10);
              
              lkCaption :=  aQr.FieldByName('NAME').AsString;
              while(Pos('|', lkCaption) > 0)do
                Delete(lkCaption, 1, Pos('|', lkCaption));
              
              lkWidth    := Trunc(aQr.FieldByName('WIDTH').AsInteger * TERPForm_DefaultControlWidthMul);
              lkTop      := aQr.FieldByName('EDT_TOP').AsInteger * 2 * (TERPForm_DefaultControlHeight - TERPForm_DefaultControlIndent);
              lkLastLeft := TERPForm_DefaultControlIndent;
              for k:=0 to lkSB.ControlCount-1 do
                if(lkSB.Controls[k].Top = lkTop)then
                  lkLastLeft := MaxInteger(lkLastLeft, (lkSB.Controls[k].Left + lkSB.Controls[k].Width + TERPForm_DefaultControlIndent) ); 
              lkDBE := ERP_DBEditEh_Create(lkSB, TDataSource(TERPForm_DataSetMain(aOwner).FindComponent('DataSource'+TERPForm_DataSetMain(aOwner).Name)), 
                         aQr, lkCaption, lkLastLeft, lkTop, TERPForm_DefaultControlHeight, lkWidth, false);
              end;
            if(StrTrimAll(aQr.FieldByName('TB_ID').AsString) = lkSettings.Values[ERP_SETTINGS_TABLENAME])then
              begin
              lkCol := ERP_ColumnEh_Create(lkDBGChilds, aQr, true);
              with lkCol do
                begin
                if(aQr.FieldByName('ID').AsString = 'FLAG_DELETE')then
                  begin
                  AutoDropDown := false;
                  CheckBoxes   := false;
                  ImageList    := lkILDelete;
                  end;
                if(aQr.FieldByName('ID').AsString = 'FLAG_COMMIT')then  
                  begin
                  AutoDropDown := false;
                  CheckBoxes   := false;
                  ImageList    := lkILCommit;
                  end;
                if(aQr.FieldByName('ID').AsString = 'FLAG_LOCK')then  
                  begin
                  AutoDropDown := false;
                  CheckBoxes   := false;
                  ImageList    := lkILLock;
                  end;
                end;
              lkCol := CloneTColumnEh(lkCol, lkDBGParents);
              end;
            end;
          end;
        end;
      j := j + 1;  
      aQr.Next;
      end;
    lkDBGParents.HelpKeyWord    := lkDBGChilds.HelpKeyWord;  
    lkDBGParents.FooterRowCount := lkDBGChilds.FooterRowCount;  
    lkCol := CreateTColumnEh(lkDBGChilds, ERP_SQL_FIELDINDENT,'','',80,taLeftJustify );
    with lkCol do 
      begin
      Index     := 0;
      Font.Name := 'Courier New';
      Font.Size := 8;
      Font.Style:= [fsBold];
      Tag       := 666;
      end;
    lkCol := CreateTColumnEh(lkDBGParents,ERP_SQL_FIELDINDENT,'','',80,taLeftJustify );
    with lkCol do 
      begin
      Index     := 0;
      Font.Name := 'Courier New';
      Font.Size := 8;
      Font.Style:= [fsBold];
      Tag       := 666;
      end;
    for i:=1 to Length(lkTablesList)-1 do
      begin
      lkSQLTables := lkSQLTables+', '+lkTablesList[i]+' '+ERP_SQL_TABLEPREFIX+FormatFloat('0000', i);
      if(i < 14)then
        lkEvents.Events.Add(lkTablesList[i]);  
      end;
    TERPForm_SQL(aOwner).Text := 'SELECT '+lkSQLFields  +' '+SQLCRLF+'FROM   '+lkSQLTables  +' '+SQLCRLF+lkSQLWhere;
    lkQrChilds.SQL.Text  := 'SELECT '+lkSQLFieldsCh+' '+SQLCRLF+'FROM   '+lkSQLTablesCh+' '+SQLCRLF+lkSQLWhereCh;
    lkQrParents.SQL.Text := 'SELECT '+lkSQLFieldsCh+' '+SQLCRLF+'FROM   '+lkSQLTablesPa+' '+SQLCRLF+lkSQLWhereCh;
  end;
  //============================================================================
  function TERPFormDoc_Create(const aDocId :string):TAmunhotepForm;
  var
    lkTYPEID       :string;
    lkCreateParams :TFormERPParams;
    lkMainMenu     :TMainMenu;
    lkMIMenuMain   :TMenuItem;
    lkMIObj        :TMenuItem;
    lkMI           :TMenuItem;    
    lkToolBar      :TxcGradientPanelVista;
    lkEvents       :TxFBEvents;
    lkTrLoad       :TxFBTransaction;
    lkDSLoad       :TDataSource;
    lkQrLoad       :TxFBQuery;
    lkTr           :TxFBTransaction;
    lkDTS          :TxFBDataSet;
    lkDS           :TDataSource;
    lkSplt         :TSplitter;
    lkPC           :TxcPageControlEx;
    lkTS           :TxcTabSheet;
    lkTSData       :TxcTabSheet;
    lkPCData       :TxcPageControlEx;
    lkSB           :TScrollBox;
    lkDBGChilds    :TDBGridEh;
    lkDBGParents   :TDBGridEh;
    lkQrChilds     :TxFBQuery;
    lkQrParents    :TxFBQuery;
    lkAct          :TCustomAction;
    i              :Integer;
  begin
    with Amunhotep.MainForm do
      for i:=0 to MDIChildCount-1 do
        if(MDIChildren[i].HelpKeyWord = aDocId)then
          if(ObjectInheritsFrom(MDIChildren[i], 'TAmunhotepForm'))then
            begin
            Result := TAmunhotepForm(MDIChildren[i]);
            Result.BringToFront;
            exit;
            end; 
    CreateTxFBTransQuery(nil, '', '', '', ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTrLoad, lkQrLoad, lkDSLoad)  
    lkQrLoad.SQL.Text := StringsLoadFromFile(ERP_FILENAME_SQL_GETTABLE_JRNL);
    lkQrLoad.Prepare;
    lkQrLoad.ParamByName('Q_TYPE_ID').AsString := '4';
    try
      lkQrLoad.Open;
    except
    end;
    if not(lkQrLoad.Active)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTrLoad.Free;
      Dialogs.MessageDlg(msg_error_erpsql+' !',mtWarning,[mbOk]);
      exit;
      end; 
    lkQrLoad.First;
    if(lkQrLoad.FieldByName('TYPE_EXISTS').AsInteger <> 1)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_defined, mtError, [mbOk]);
      exit;
      end;
    if(lkQrLoad.FieldByName('TB_REL_EXISTS').AsInteger <> 1)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTrLoad.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_exists, mtError, [mbOk]);
      exit;
      end;
    GetField(FBDataBase, lkQrLoad.FieldByName('TB_ID_MAIN').AsString, 'TYPE_ID', 'ID = '''+aDocId+''' ', lkTYPEID);
    if lkTrLoad.InTransaction then
      lkTrLoad.Commit;
    lkQrLoad.Prepare;
    lkQrLoad.ParamByName('Q_TYPE_ID').AsString := lkTYPEID;
    try
      lkQrLoad.Open;
    except
    end;
    lkQrLoad.First;
    if(lkQrLoad.FieldByName('TYPE_EXISTS').AsInteger <> 1)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_defined+' "'+lkTYPEID+'"', mtError, [mbOk]);
      exit;
      end;
    if(lkQrLoad.FieldByName('TB_REL_EXISTS').AsInteger <> 1)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTrLoad.Free;
      Dialogs.MessageDlg(msg_error_erpobject_not_exists+' "'+lkTYPEID+'"', mtError, [mbOk]);
      exit;
      end;
    Result := TAmunhotepForm(TERPForm_Create(ERP_ObjectCaption(ERP_OBJECTTYPE_DOC), ERP_ObjectIcon(ERP_OBJECTTYPE_DOC), ERP_ObjectBitmap(ERP_OBJECTTYPE_DOC), false, @TERPFormDoc_OnClose));
    Result.HelpKeyWord := aDocId;
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_DOC);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_DOC);
      end;  
    with TERPForm_Settings(Result) do
      begin
      Values[ERP_SETTINGS_BOOKMARK    ] := '0';
      Values[ERP_SETTINGS_DATAMEMORY  ] := '0';
      Values[ERP_SETTINGS_SAVERECNO   ] := aDocId;
      Values[ERP_SETTINGS_BUFFERVAR   ] := lkQrLoad.FieldByName('BUFFER_VAR_MAIN').AsString;
      Values[ERP_SETTINGS_GOTOVAR     ] := StrTrimAll(lkQrLoad.FieldByName('BUFFER_VAR_MAIN').AsString+ERP_SETTINGS_GOTOVAR);
      Values[ERP_SETTINGS_TABLENAME   ] := lkQrLoad.FieldByName('TB_ID_MAIN').AsString;
      Values[ERP_SETTINGS_TABLECAPTION] := lkQrLoad.FieldByName('TYPE_NAME2').AsString;
      Values[ERP_SETTINGS_BASETYPE    ] := lkQrLoad.FieldByName('TYPE_ID').AsString;
      Values[ERP_SETTINGS_TYPESLIST   ] := lkQrLoad.FieldByName('TYPES_LIST').AsString;
      TERPForm_SetCaption(Result, Values[ERP_SETTINGS_TABLECAPTION]);
      end;
    lkMainMenu    := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIMenuMain  := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,ERP_ObjectCaption(4),'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
    lkMIObj       := CreateTMenuItem(lkMIMenuMain    ,obj_name_erp_mimainobj ,ERP_FolderObjectCaption(4) ,'','', 31,0);
    lkToolBar     := CreateTxcGradientPanelVistaToolBar(Result,Result,obj_name_erp_toolbar,'',alTop, 0,100,TERPForm_DefaultToolButtonWidth+2, 200,xbsNone);

    CreateTxFBTransDataSet(Result, obj_name_erp_data_trmain, obj_name_erp_data_dtsmain, 'DataSource'+obj_name_erp_data_dtsmain, ['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);
    with lkDTS do
      begin
      AfterOpen   := @TERPForm_OpenDataSetsChilds;
      BeforeClose := @TERPForm_CloseDataSetsChilds;
      AfterScroll := @TERPFormDoc_DataSetMain_AfterScroll;
      end;    
    lkQrChilds := TxFBQuery.Create(lkDTS);
    with lkQrChilds do
      begin
      Name        := obj_name_erp_data_qrchilds;
      Transaction := lkTr;
      DataSource  := lkDS;
      SQL.Text    := '';
      end;
    lkQrParents := TxFBQuery.Create(lkDTS);
    with lkQrParents do
      begin
      Name        := obj_name_erp_data_qrparents;
      Transaction := lkTr;
      DataSource  := lkDS;
      SQL.Text    := '';
      end;
    lkEvents := TxFBEvents.Create(Result);
    with lkEvents do
      begin
      Name         := obj_name_erp_data_evmain;
      DataBase     := FBDataBase;
      OnEventAlert := @TERPFormDoc_evMain_OnEventAlert;
      Events.Clear;
      end;
    lkSB   := CreateTScrollBox(Result, Result, obj_name_erp_scrollboxmain,0,lkToolBar.Top + lkToolBar.Height+1,200,200,alTop);
    lkSplt := CreateTSplitter(Result,Result,obj_name_erp_splitterdetail,alTop,0, lkSB.Top + lkSB.Height + 1,4,800);
    lkPC   := CreateTxcPageControlEx(Result,Result,obj_name_erp_pagecontroldetail,0,600,560,200,alClient);
    lkTSData := CreateTxcTabSheet(lkPC,'tsDocData'   ,msg_erp_tsdocdata    ,491,Amunhotep.MainForm.StyleManager.Colors.Window    ); lkPCData     := CreateTxcPageControlEx(Result,lkTSData,obj_name_erp_pagecontroldata,0,0,200,240,alClient);
    lkTS     := CreateTxcTabSheet(lkPC,'tsDocComents',msg_erp_tsdoccoments ,420,Amunhotep.MainForm.StyleManager.Colors.Background); DocComentsIntf_Create(Result, lkTS, lkDS); 
    lkTS     := CreateTxcTabSheet(lkPC,'tsDocChilds' ,msg_erp_tsdocchilds  , 42,Amunhotep.MainForm.StyleManager.Colors.Foreground); lkDBGChilds  := CreateTDBGridEh(Result,lkTS,nil,obj_name_erp_data_dbgchilds ,0,0,1,1,alClient);
    lkTS     := CreateTxcTabSheet(lkPC,'tsDocParents',msg_erp_tsdocparents , 42,Amunhotep.MainForm.StyleManager.Colors.Foreground); lkDBGParents := CreateTDBGridEh(Result,lkTS,nil,obj_name_erp_data_dbgparents,0,0,1,1,alClient);
    TxcPageControlEx_ActivateDefaultPage(lkPC);
    with lkDBGChilds do
      begin
      DataSource := TDataSource.Create(lkQrChilds);
      with DataSource do
        begin
        Name    := 'DataSource'+obj_name_erp_data_qrchilds;
        DataSet := lkQrChilds;
        end;
      HelpKeyWord      := '0';  
      Hint             := msg_erp_tsdocchilds;  
      IndicatorOptions := [gioShowRowIndicatorEh, gioShowRowselCheckboxesEh];  
      Options          := Options + [dgRowSelect, dgMultiSelect, dgAlwaysShowSelection];
      OptionsEh        := [dghFixed3D, dghFrozen3D, dghFooter3D, dghHighlightFocus, dghIncSearch, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      OnGetCellParams  := @ERP_DBGridEh_OnGetCellParams_Jrnl;
      //OnDblClick       := @TERPFormGrid_actUpdate_OnExecute;
      VTitleMargin     := 4;
      end;    
    with lkDBGParents do
      begin
      DataSource := TDataSource.Create(lkQrParents);
      with DataSource do
        begin
        Name    := 'DataSource'+obj_name_erp_data_qrparents;
        DataSet := lkQrParents;
        end;
      HelpKeyWord      := '0';  
      Hint             := msg_erp_tsdocparents;  
      IndicatorOptions := [gioShowRowIndicatorEh, gioShowRowselCheckboxesEh];  
      Options          := Options + [dgRowSelect, dgMultiSelect, dgAlwaysShowSelection];
      OptionsEh        := [dghFixed3D, dghFrozen3D, dghFooter3D, dghHighlightFocus, dghIncSearch, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      OnGetCellParams  := @ERP_DBGridEh_OnGetCellParams_Jrnl;
      //OnDblClick       := @TERPFormGrid_actUpdate_OnExecute;
      VTitleMargin     := 4;
      end;                           
    if lkTrLoad.InTransaction then
      lkTrLoad.Commit;
    lkQrLoad.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETCOLUMNS_JRNL));
    lkQrLoad.Prepare; 
    lkQrLoad.ParamByName('PQ_TYPE_ID' ).AsString := TERPForm_Settings(Result).Values[ERP_SETTINGS_BASETYPE];
    lkQrLoad.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
    lkQrLoad.Open;
    if not(lkQrLoad.Active)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTrLoad.Free;
      Dialogs.MessageDlg(msg_error_erpsql+' "'+TERPForm_Settings(Result).Values[ERP_SETTINGS_BASETYPE]+'" !',mtWarning,[mbOk]);
      exit;
      end;  
    TERPFormDoc_LoadAttrs(Result, lkQrLoad, lkPCData);
    if lkTrLoad.InTransaction then
      lkTrLoad.Commit;
    lkQrLoad.SQL.Text := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_SQL_GETTABLE_DOC));
    lkQrLoad.Prepare; 
    lkQrLoad.ParamByName('PQ_TYPE_ID' ).AsString := TERPForm_Settings(Result).Values[ERP_SETTINGS_BASETYPE];
    lkQrLoad.ParamByName('PQ_USER_VAR').AsString := ERP_GLOBALVARIABLE_USER_CURRENT;
    lkQrLoad.Open;
    if not(lkQrLoad.Active)then
      begin
      if lkTrLoad.InTransaction then
        lkTrLoad.Commit;
      lkTr.Free;
      Dialogs.MessageDlg(msg_error_erpsql+' "'+TERPForm_Settings(Result).Values[ERP_SETTINGS_BASETYPE]+'" !',mtWarning,[mbOk]);
      exit;
      end;  
    DocDataIntf_Create(Result, lkTSData, TERPForm_Settings(Result).Values[ERP_SETTINGS_TABLENAME], lkTr, lkDS, lkQrLoad);  
    if lkTrLoad.InTransaction then
      lkTrLoad.Commit;
    lkTrLoad.Free;
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewrefresh,msg_erp_actviewrefresh,msg_erp_actviewrefresh_hint,SHORTCUT_DATA_REFRESH,0,170,@TERPFormDoc_actViewRefresh_OnExecute,nil                                 ,lkToolBar,lkMIObj);
//    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewdetail ,msg_erp_actviewdetail ,msg_erp_actviewdetail_hint ,SHORTCUT_DATA_DETAIL ,0,491,@TERPFormGrid_actViewDetail_OnExecute ,@TERPFormGrid_actViewDetail_OnUpdate,lkToolBar, lkMIObj);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actdocgotojrnl,msg_erp_actdocgotojrnl,msg_erp_actdocgotojrnl_hint,SHORTCUT_DOC_GOTOJRNL,0,519,@TERPFormDoc_actDocGotoJrnl_OnExecute,nil,lkToolBar,lkMIObj)

    lkCreateParams := [
        erpGrid, erpGridGroup, erpGridNavigation
       ,erpGridEdit, erpGridEditEdt, erpGridEditDel
       ,erpGridEditMark
       ,erpGridEditCommit, erpGridEditLock, erpGridEditGotoJrnl 
       ,erpGridNoCopy
       ,erpGridExport, erpGridPrint, erpGridPrintItem];

    lkToolBar := CreateTxcGradientPanelVistaToolBar(lkDBGChilds, lkDBGChilds.Parent,lkDBGChilds.Name+'_'+obj_name_erp_toolbar,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsRaized);
    ERP_DBGridEh_EdtActions_Create(lkDBGChilds , lkCreateParams, lkToolBar, nil);
    ERP_DBGridEh_StdActions_Create(lkDBGChilds , lkCreateParams, lkToolBar, nil);                         
    lkToolBar := CreateTxcGradientPanelVistaToolBar(lkDBGParents, lkDBGParents.Parent,lkDBGParents.Name+'_'+obj_name_erp_toolbar,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsRaized);
    ERP_DBGridEh_EdtActions_Create(lkDBGParents, lkCreateParams, lkToolBar, nil);
    ERP_DBGridEh_StdActions_Create(lkDBGParents, lkCreateParams, lkToolBar, nil);                         

    Amunhotep.MainForm.xcMenu.AddMenu(lkMainMenu); lkMainMenu.OwnerDraw := true;
    Result.Menu := lkMainMenu;
    
    TERPFormDoc_RefreshView(Result);
  end;
