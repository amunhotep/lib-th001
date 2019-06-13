{$DEFINE PEAKTOP:IDE/ERP/DBO/MENU/OBJECTEDITOR.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                    {$I PEAKTOP:GLOBAL_VARIABLES.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                      {$I PEAKTOP:GLOBAL_OBJECTS.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:DBFS_DLG.INC}                            {$I PEAKTOP:DBFS_DLG.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                       {$I PEAKTOP:OBJ/TCOLUMNEH.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBGRIDEH.INC}                       {$I PEAKTOP:OBJ/TDBGRIDEH.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                          {$I PEAKTOP:OBJ/TLABEL.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBEDITEH.2.INC}                     {$I PEAKTOP:OBJ/TDBEDITEH.2.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBNUMBEREDITEH.2.INC}               {$I PEAKTOP:OBJ/TDBNUMBEREDITEH.2.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TDBCOMBOBOXEH.2.INC}                 {$I PEAKTOP:OBJ/TDBCOMBOBOXEH.2.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}                       {$I PEAKTOP:OBJ/TMENUITEM.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                       {$I PEAKTOP:OBJ/TSPLITTER.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}                {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}           {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                        {$I PEAKTOP:OBJ/TXCPANEL.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}                {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                     {$I PEAKTOP:OBJ/TXCTABSHEET.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSCROLLBOX.INC}                      {$I PEAKTOP:OBJ/TSCROLLBOX.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                    {$I PEAKTOP:OBJ/TXFBDATASETS.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBTREEVIEW.INC}                    {$I PEAKTOP:OBJ/TXFBTREEVIEW.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}               {$I ../SHORTCUTS.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}         {$I ../$COMMON/FORMERP.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}    {$I ../$COMMON/FORMERP_LANG.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/IMAGELISTDLG.INC}       {$I ../OPER/IMAGELISTDLG.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/LOCAL/INTERFACE.INC}    {$I ../OPER/LOCAL/INTERFACE.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/OBJECTEDITOR_LANG.INC}  {$I ./OBJECTEDITOR_LANG.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/OBJECTEDITOR_NAMES.INC} {$I ./OBJECTEDITOR_NAMES.INC}              {$ENDIF}
  //=================== PEAKTOP:IDE/ERP/DBO/MENU/OBJEDITOR.INC =================
  procedure TERPFormEdtrMenu_CloseDataSets(aOwner :TComponent);
  begin
    with TERPForm_DataSetMain(aOwner) do
      begin
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
      if Transaction.InTransaction then
        Transaction.Commit;  
      end;
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_RefreshView(aOwner :TComponent);
  begin
    TERPFormEdtrMenu_CloseDataSets(aOwner);
    with TERPForm_DataSetMain(aOwner) do
      begin
      SelectSQL.Text := 'SELECT FIRST 1 M.ID AS '+ERP_DATASET_DBKEY+', M.MENUS_ID, M.ID, M.NAME, M.PARENT_ID, M.FLAG_DELETE, M.SHORTCUT, M.SCRIPT_NAME, M.IMAGE_INDEX,M.GROUP_INDEX '+SQLCRLF+
                        'FROM   TABL$_MENU M WHERE  (M.ID = '''+TxFBTreeView(aOwner.FindComponent(obj_name_erp_fbtreeview)).GetId+''')';
      RefreshSQL.Text:= 'SELECT FIRST 1 M.ID AS '+ERP_DATASET_DBKEY+', M.MENUS_ID, M.ID, M.NAME, M.PARENT_ID, M.FLAG_DELETE, M.SHORTCUT, M.SCRIPT_NAME, M.IMAGE_INDEX,M.GROUP_INDEX '+SQLCRLF+
                        'FROM   TABL$_MENU M WHERE  (M.ID = ?ID)';
      ModifySQL.Text := 'UPDATE TABL$_MENU M SET '+SQLCRLF+
                        '   M.NAME        = ?NAME '+SQLCRLF+
                        '  ,M.PARENT_ID   = ?PARENT_ID '+SQLCRLF+
                        '  ,M.FLAG_DELETE = ?FLAG_DELETE '+SQLCRLF+
                        '  ,M.SHORTCUT    = ?SHORTCUT '+SQLCRLF+
                        '  ,M.SCRIPT_NAME = ?SCRIPT_NAME '+SQLCRLF+
                        '  ,M.IMAGE_INDEX = ?IMAGE_INDEX '+SQLCRLF+
                        '  ,M.GROUP_INDEX = ?GROUP_INDEX '+SQLCRLF+
                        'WHERE (M.ID = ?ID);';
      try Open; except end;                  
      end;
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_FBTreeView_OnClick(Sender :TObject);
  begin
    TERPFormEdtrMenu_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_FBTreeView_OnBuildNode(Sender :TObject; StateFieldValue :Variant; var StateImage :Integer);
  begin
    StateImage := Integer(StateFieldValue);
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_actTreeInsRoot_OnExecute(Sender :TObject);
  var
    lkStr    :string;
    lkMenusId:string;
  begin
    if not Dialogs.InputQueryString(msg_erp_acttreeinsroot_hint, msg_erp_objeditormenu_enter_name, lkStr) then exit;
    lkStr     := StrReplaceStr(lkStr,'''','''''');
    lkMenusId := TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TYPESLIST];
    ExecSQL(FBDataBase, 'INSERT INTO TABL$_MENU(MENUS_ID, NAME, PARENT_ID, IMAGE_INDEX, ACCSS)VALUES('''+lkMenusId+''','''+
      lkStr+''', ''0'', -1, (SELECT ''~''||LIST(R.ID,''~'')||''~'' FROM TABL$_USERS_ROLES R))');
    with TxFBTreeView(TComponent(Sender).Owner.FindComponent(obj_name_erp_fbtreeview)) do
      begin
      ClearTree;
      BuildTree;  
      if(Items.Count > 0)then
        begin
        Items[0].Selected := true;
        TERPFormEdtrMenu_FBTreeView_OnClick(Owner.FindComponent(obj_name_erp_fbtreeview));
        end;
      end;
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_actTreeIns_OnExecute(Sender :TObject);
  var
    lkStr    :string;
    lkMenusId:string;
  begin
    if not Dialogs.InputQueryString(msg_erp_actins_hint, msg_erp_objeditormenu_enter_name, lkStr) then exit;
    lkStr     := StrReplaceStr(lkStr,'''','''''');
    lkMenusId := TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TYPESLIST];
    with TxFBTreeView(TComponent(Sender).Owner.FindComponent(obj_name_erp_fbtreeview)) do
      begin
      ExecSQL(FBDataBase, 'INSERT INTO TABL$_MENU(MENUS_ID, NAME, PARENT_ID, IMAGE_INDEX, ACCSS)VALUES('''+lkMenusId+''','''+
        lkStr+''', '''+GetId+''', -1, (SELECT ''~''||LIST(R.ID,''~'')||''~'' FROM TABL$_USERS_ROLES R))');
      RebuildSelected;
      end;
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_actTreeDel_OnExecute(Sender :TObject);
  var
    lkMenusId:string;
  begin
    lkMenusId := TERPForm_Settings(TComponent(Sender).Owner).Values[ERP_SETTINGS_TYPESLIST];
    with TxFBTreeView(TComponent(Sender).Owner.FindComponent(obj_name_erp_fbtreeview)) do
      begin
      if(lkMenusId <> TERPForm_DataSetMain(TComponent(Sender).Owner).FieldByName('MENUS_ID').AsString)then
        begin
        Dialogs.MessageDlg(msg_erp_objeditormenu_error001, mtWarning, [mbOk]);
        exit;
        end
       else 
        begin
        if(Dialogs.MessageDlg(msg_erp_actdel_hint+' "'+SelectedNode.Text+'" ?', mtConfirmation, [mbYes, mbNo]) <> mrYes)then exit;
        end;
      ExecSQL(FBDataBase, 'DELETE FROM TABL$_MENU WHERE (ID = '''+GetId+''')');
      if(SelectedNode.Parent <> nil)then
        begin
        SelectedNode.Parent.Selected := true;
        RebuildSelected;
        TERPFormEdtrMenu_FBTreeView_OnClick(Owner.FindComponent(obj_name_erp_fbtreeview));
        end
       else
        begin 
        ClearTree;
        BuildTree;  
        if(Items.Count > 0)then
          begin
          Items[0].Selected := true;
          TERPFormEdtrMenu_FBTreeView_OnClick(Owner.FindComponent(obj_name_erp_fbtreeview));
          end;
        end;  
      end; 
  end; 
  //============================================================================
  procedure TERPFormEdtrMenu_actAccsInherit_OnExecute(Sender :TObject);
  var
    lkSQL :string;
  begin
    if(Dialogs.MessageDlg(msg_erp_actaccss_inherit_hint+' ?', mtConfirmation, [mbYes, mbNo]) <> mrYes)then exit;
    lkSQL := 
      'EXECUTE BLOCK AS '+SQLCRLF+
      '  DECLARE VARIABLE P_PARENT_MENU_ID TYPE OF COLUMN TABL$_MENU.ID; '+SQLCRLF+
      '  DECLARE VARIABLE P_MENU_ID        TYPE OF COLUMN TABL$_MENU.ID; '+SQLCRLF+
      '  DECLARE VARIABLE P_ACCSS          TYPE OF COLUMN TABL$_MENU.ACCSS; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  P_PARENT_MENU_ID = '+TxFBTreeView(TComponent(Sender).Owner.FindComponent(obj_name_erp_fbtreeview)).GetId+'; '+SQLCRLF+
      '  SELECT FIRST 1 M.ACCSS FROM TABL$_MENU M WHERE (M.ID = :P_PARENT_MENU_ID) INTO :P_ACCSS; '+SQLCRLF+
      '  FOR '+SQLCRLF+
      '    SELECT TMP.MENU_ID '+SQLCRLF+
      '    FROM   (WITH RECURSIVE MENU_TREE AS ( '+SQLCRLF+
      '              SELECT M1.ID AS MENU_ID FROM TABL$_MENU M1               WHERE(M1.PARENT_ID = :P_PARENT_MENU_ID) '+SQLCRLF+
      '              UNION ALL '+SQLCRLF+
      '              SELECT M2.ID AS MENU_ID FROM TABL$_MENU M2, MENU_TREE M3 WHERE(M2.PARENT_ID = M3.MENU_ID) '+SQLCRLF+
      '            ) SELECT T.MENU_ID FROM MENU_TREE T) TMP '+SQLCRLF+
      '    INTO   :P_MENU_ID '+SQLCRLF+
      '  DO '+SQLCRLF+
      '    UPDATE TABL$_MENU MZ SET MZ.ACCSS = :P_ACCSS WHERE (MZ.ID = :P_MENU_ID);'+SQLCRLF+
      'END ';
    ExecSQL(FBDataBase, lkSQL);
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_actAccsFill_OnExecute(Sender :TObject);
  var
    lkSQL :string;
  begin
    with TERPForm_DataSetMain(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not (RecordCount > 0)then exit;
      lkSQL := 'UPDATE TABL$_MENU M SET M.ACCSS = (SELECT ''~''||LIST(R.ID,''~'')||''~'' FROM TABL$_USERS_ROLES R ) WHERE (M.ID = '+FieldByName('ID').AsString+'); '; 
      end;
    ExecSQL(FBDataBase, lkSQL);
    TERPFormEdtrMenu_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_actAccsClear_OnExecute(Sender :TObject);
  var
    lkSQL :string;
  begin
    with TERPForm_DataSetMain(TComponent(Sender).Owner) do
      begin
      if not Active then exit;
      if not (RecordCount > 0)then exit;
      lkSQL := 'UPDATE TABL$_MENU M SET M.ACCSS = ''~'' WHERE M.ID = '''+FieldByName('ID').AsString+'''); ';
      end;
    ExecSQL(FBDataBase, lkSQL);
    TERPFormEdtrMenu_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_dbeSCRIPT_NAME_OnEditButtonsClick(Sender :TObject; var Handled :Boolean);
  var
    lkFileName :string;
    lkInitDir  :string;
  begin
    Handled := true;
    with TERPForm_DataSetMain(TComponent(Sender).Owner.Owner) do
      begin
      if not Active then exit;
      if not (RecordCount > 0)then exit;
      lkFileName := FieldByName('SCRIPT_NAME').AsString;
      end;
    if(Pos('DB:', UpperCase(lkFileName))=1)then
      begin
      lkFileName := '';
      lkInitDir  := Amunhotep.SourcePath;
      end
     else
      begin
      if(Pos('PEAKTOP:', UpperCase(lkFileName)) = 1)then
        begin
        lkInitDir := Amunhotep.SourcePath;
        Delete(lkFileName, 1, Length('PEAKTOP:'));
        lkFileName := lkInitDir+lkFileName;
        end
       else
        lkInitDir := ExtractFilePath(lkFileName); 
      end; 
    if not PromptForFileName(lkFileName, msg_erp_objeditormenu_opendialogfilter,'PS',msg_erp_objeditormenu_file_case, lkInitDir, false)then exit;
    if(Pos(AnsiUpperCase(Amunhotep.SourcePath), AnsiUpperCase(lkFileName))=1)then
      begin
      Delete(lkFileName, 1, Length(Amunhotep.SourcePath));
      lkFileName := 'PEAKTOP:'+lkFileName;
      end;
    with TERPForm_DataSetMain(TComponent(Sender).Owner.Owner) do
      begin
      if(State <> dsEdit)then Edit;
      FieldByName('SCRIPT_NAME').AsString := lkFileName;
      try Post; except Cancel; end;  
      end;
  end;
  //============================================================================
  procedure TERPFormEdtrMenu_dbeSCRIPT_NAME_OnEditButtonsClick2(Sender :TObject; var Handled :Boolean);
  var
    lkS :string;
  begin
    Handled := true;
    lkS := TERPForm_DataSetMain(TComponent(Sender).Owner.Owner).FieldByName('SCRIPT_NAME').AsString;
    SetGlobalVariable(BufferVariableDBFSId  ,'');
    SetGlobalVariable(BufferVariableDBFSPath,lkS);
    call('PEAKTOP:DBFS_DLG.PS');
    lkS := GetGlobalVariable(BufferVariableDBFSPath);
    if(StrTrimAll(lkS)='')then exit;
    with TERPForm_DataSetMain(TComponent(Sender).Owner.Owner) do
      begin
      if(State <> dsEdit)then Edit;
      FieldByName('SCRIPT_NAME').AsString := lkS;
      try Post; except Cancel; end;  
     end;  
  end;       
  //============================================================================
  procedure TERPFormEdtrMenu_dbcbxIMAGE_INDEX_OnEditButtonsClick2(Sender :TObject; var Handled :Boolean);
  var
    lkIndx :Integer;
  begin
    Handled := true;
    lkIndx := TERPForm_DataSetMain(TComponent(Sender).Owner.Owner).FieldByName('IMAGE_INDEX').AsInteger;
    if not Amunhotep_ImageListDialog_Execute(Amunhotep.MainForm.ImageListMain, lkIndx) then exit;
    with TERPForm_DataSetMain(TComponent(Sender).Owner.Owner) do
      begin
      if(State <> dsEdit)then Edit;
      FieldByName('IMAGE_INDEX').AsInteger := lkIndx;
      try Post; except Cancel; end;  
     end;  
  end;       
  //============================================================================
  procedure TERPFormEdtrMenu_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    TERPFormEdtrMenu_CloseDataSets(TComponent(Sender));
    Action := caFree;
  end;
  //============================================================================
  function TERPFormEdtrMenu_Create(const aObjId:string):TAmunhotepForm;
  var
    lkMenuId      :string;
    lkCaption     :string;
    lkMainMenu    :TMainMenu;
    lkMIMain      :TMenuItem;
    lkAct         :TCustomAction;
    lkPanelLeft   :TxcPanel;
    lkToolBarLeft :TxcGradientPanelVista;
    lkPanelClient :TxcGradientPanel;
    lkPnlCtrls    :TxcGradientPanel;
    lkToolBar     :TxcGradientPanelVista;
    lkToolBarAccss:TxcGradientPanelVista;
    lkSplt        :TSplitter;
    lkFBTreeView  :TxFBTreeView;
    lkLBL         :TLabel;
    lkDBE         :TDBEditEh;
    lkDBNE        :TDBNumberEditEh;
    lkDBCBX       :TDBComboBoxEh;
    lkTr          :TxFBTransaction;
    lkDTS         :TxFBDataSet;
    lkDTSChild    :TxFBDataSet; 
    lkDS          :TDataSource;
    lkDBG         :TDBGridEh;
    lkCol         :TColumnEh;
    lkPC          :TxcPageControlEx;
    lkTS          :TxcTabSheet;
    lkLastTop, i  :Integer;
  begin
    if not GetField(FBDataBase, 'TABL$_MENUS', 'ID', '(UPPER(TRIM(NAME))='''+aObjId+''')', lkMenuId)then
      exit;
    lkCaption := '';  
    GetField(FBDataBase, 'TABL$_MENUS', 'DESCR', 'ID = '+lkMenuId, lkCaption);
    DontAutoFree;
    Result := TAmunhotepForm(TERPForm_Create(ERP_ObjectCaption(ERP_OBJECTTYPE_MENU)+': '+lkCaption, ERP_ObjectIcon(ERP_OBJECTTYPE_MENU), ERP_ObjectBitmap(ERP_OBJECTTYPE_MENU), false, @TERPFormEdtrMenu_OnClose));
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_MENU);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_MENU);
      end;  
    with TERPForm_Settings(Result) do
      begin
      Values[ERP_SETTINGS_TABLENAME   ] := aObjId;
      Values[ERP_SETTINGS_TABLECAPTION] := '';
      Values[ERP_SETTINGS_TYPESLIST   ] := lkMenuId;
      Values[ERP_SETTINGS_BASETYPE    ] := IntToStr(ERP_OBJECTTYPE_MENU);
      end;
    lkMainMenu := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIMain   := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,ERP_ObjectCaption(ERP_OBJECTTYPE_MENU),'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
    CreateTxFBTransDataSet(Result, obj_name_erp_data_trmain, obj_name_erp_data_dtsmain, 'DataSource'+obj_name_erp_data_dtsmain, ['isc_tpb_read_committed', 'isc_tpb_write', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkDTS, lkDS);
    with lkDTS do
      begin
      AfterOpen   := @TERPForm_OpenDataSetsChilds;
      BeforeClose := @TERPForm_CloseDataSetsChilds;
      end;  
    lkPanelClient := CreateTxcGradientPanel(Result,Result,obj_name_erp_panelclient,'',alClient,1,1,600,800,xbsNone,gdRightToLeft); 
    lkToolBar     := CreateTxcGradientPanelVistaToolBar(lkPanelClient,lkPanelClient,obj_name_erp_toolbar,'',alTop, 0,0,24,200,xbsRaized);
    with lkToolBar do
      begin
      Font.Name  := 'Verdana';
      Font.Style := [fsBold];
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Size  := 12; 
      Caption    := #$20+AnsiLowerCase(msg_erp_objeditormenu_props);
      end;
    lkPnlCtrls := CreateTxcGradientPanel(Result,lkPanelClient,obj_name_erp_panelclient+obj_name_erp_paneltop,'',alTop,1,lkToolBar.Top+lkToolBar.Height+1,200,800,xbsNone,gdRightToLeft);
    lkLastTop := TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(lkPnlCtrls,lkPnlCtrls, msg_erp_objeditormenu_caption, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight,TERPForm_DefaultEditButtonWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(Result,lkPnlCtrls,lkDS, obj_name_erp_objedtrmenu_caption,'NAME', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight, 480);
    lkLastTop := lkLastTop + TERPForm_DefaultControlEditHeight + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(lkPnlCtrls,lkPnlCtrls, msg_erp_objeditormenu_script, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight,TERPForm_DefaultEditButtonWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(Result,lkPnlCtrls,lkDS, obj_name_erp_objedtrmenu_script,'SCRIPT_NAME', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight, 480);
    with lkDBE do
      begin
      with EditButtons.Add do
        begin
        Hint     := msg_erp_objeditormenu_file_case+#$20+'(Ctrl+O)';
        ShortCut := TextToShortCut('Ctrl+O');
        Style    := ebsEllipsisEh;
        Visible  := true;
        OnClick  := @TERPFormEdtrMenu_dbeSCRIPT_NAME_OnEditButtonsClick;
        end;
      with EditButtons.Add do
        begin
        Hint     := msg_erp_objeditormenu_file_casedb+#$20+'(Alt+Ctrl+O)';
        ShortCut := TextToShortCut('Alt+Ctrl+O');
        Style    := ebsEllipsisEh;
        Visible  := true;
        OnClick  := @TERPFormEdtrMenu_dbeSCRIPT_NAME_OnEditButtonsClick2;
        end;
      end;
    lkLastTop := lkLastTop + TERPForm_DefaultControlEditHeight + TERPForm_DefaultControlIndent;
    lkLBL := CreateTLabel(lkPnlCtrls,lkPnlCtrls, msg_erp_objeditormenu_shortcut, TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight,TERPForm_DefaultEditButtonWidth,alNone,taLeftJustify);
    lkDBE := CreateTDBEditEh(Result,lkPnlCtrls,lkDS, obj_name_erp_objedtrmenu_shortcut,'SHORTCUT', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight, Trunc(TERPForm_DefaultEditButtonWidth*3/2));
    with lkDBE do
      begin
      end;
    lkLBL := CreateTLabel(lkPnlCtrls,lkPnlCtrls, msg_erp_objeditormenu_groupindex, lkDBE.Left+lkDBE.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight,Trunc(TERPForm_DefaultEditButtonWidth/2),alNone,taLeftJustify);
    lkDBNE:= CreateTDBNumberEditEh(Result,lkPnlCtrls,lkDS,obj_name_erp_objedtrmenu_groupindex,'GROUP_INDEX',lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight, TERPForm_DefaultEditButtonWidth);
    with lkDBNE do
      begin
      end;
    lkLBL := CreateTLabel(lkPnlCtrls,lkPnlCtrls, msg_erp_objeditormenu_imageindex, lkDBNE.Left+lkDBNE.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight,Trunc(TERPForm_DefaultEditButtonWidth/2),alNone,taLeftJustify);
    lkDBCBX := CreateTDBComboBoxEh(Result,lkPnlCtrls,lkDS, obj_name_erp_objedtrmenu_imageindex,'IMAGE_INDEX', lkLBL.Left+lkLBL.Width+TERPForm_DefaultControlIndent, lkLastTop, TERPForm_DefaultControlEditHeight, TERPForm_DefaultEditButtonWidth);
    with lkDBCBX do
      begin
      Height := TERPForm_DefaultControlEditHeight;
      Images := Amunhotep.MainForm.ImageListMain; 
      Items.Clear;
      KeyItems.Clear;
      for i:=0 to Images.Count-1 do
        begin
        Items.Add(IntToStr(i));  
        KeyItems.Add(IntToStr(i));  
        end;
      Items.Add('-1');  
      KeyItems.Add('-1'); 
      with EditButtons.Add do
        begin
        Hint     := msg_erp_objeditormenu_image_case;
        Style    := ebsEllipsisEh;
        Visible  := true;
        OnClick  := @TERPFormEdtrMenu_dbcbxIMAGE_INDEX_OnEditButtonsClick2;
        end;
      end;
    lkLastTop := lkLastTop + TERPForm_DefaultControlEditHeight + TERPForm_DefaultControlIndent;
    lkPnlCtrls.Height := lkLastTop + 2;
    lkPanelLeft   := CreateTxcPanel(Result,Result,obj_name_erp_panelleft  ,'',alLeft  ,1,1,600,320,xbsNone); 
    lkSplt        := CreateTSplitter(Result,Result,obj_name_erp_splitterleft,alLeft,lkPanelLeft.Left+lkPanelLeft.Width+1,1,4,4);
    lkToolBarLeft := CreateTxcGradientPanelVistaToolBar(Result,lkPanelLeft,obj_name_erp_toolbarleft,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth, 200,xbsRaized);
    lkFBTreeView  := CreateTxFBTreeView(Result, lkPanelLeft, obj_name_erp_fbtreeview, 1,1,200,200,alClient);
    with lkFBTreeView do
      begin
      HelpKeyWord := '';
      Images      := Amunhotep.MainForm.ImageListMain;
      ShowItemId  := false;
      Tag         := 1;    
      OnClick     := @TERPFormEdtrMenu_FBTreeView_OnClick;
      OnBuildNode := @TERPFormEdtrMenu_FBTreeView_OnBuildNode;
      with DBTreeInfo do
        begin
        FieldId       := 'ID';
        FieldName     := 'NAME';
        FieldParentId := 'PARENT_ID';
        FieldStateId  := 'IMAGE_INDEX';
        RootParentId  := '0';
        OrderBy       := 'GROUP_INDEX';
        if(StrTrimAll(StrCiphersOnlyInt(aObjId)) = StrTrimAll(aObjId))then
          begin
          TableName   := 'PROC$_MENU_4('''+aObjId+''')';
          Where       := '';
          end
         else 
          begin
          TableName   := 'TABL$_MENU';
          Where       := 'MENUS_ID = '''+lkMenuId+''' ';
          end;
        end;
      end;
    lkPC := CreateTxcPageControlEx(Result,lkPanelClient,obj_name_erp_pagecontroldetail,0,lkPnlCtrls.Top +lkPnlCtrls.Height+1,200,200,alClient);
    lkTS := CreateTxcTabSheet(lkPC,obj_name_erp_objedtrmenu_tsaccss,msg_erp_objeditormenu_menuaccss,244,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    lkToolBarAccss := CreateTxcGradientPanelVistaToolBar(lkTS,lkTS,obj_name_erp_toolbarleft,'',alTop, 0,0,TERPForm_DefaultToolButtonWidth, 200,xbsRaized);
    lkDTSChild := TxFBDataSet.Create(lkDTS);
    with lkDTSChild do
      begin
      Name            := obj_name_erp_data_dtsdata+obj_name_erp_objedtrmenu_access;
      Transaction     := lkDTS.Transaction;
      DataSource      := lkDS;
      SelectSQL.Text  := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/MENU_ACCS_SEL.SQL'); 
      RefreshSQL.Text := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/MENU_ACCS_REF.SQL'); 
      ModifySQL.Text  := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/OBJECTEDITOR/MENU_ACCS_UPD.SQL'); 
      Tag             := 0;
      AfterOpen       := @TERPForm_OpenDataSetsChilds;
      BeforeClose     := @TERPForm_CloseDataSetsChilds;
      end; 
    lkDBG := CreateTDBGridEh(Result,lkTS,nil,obj_name_erp_data_dbgdata+obj_name_erp_objedtrmenu_access,1,lkToolBarAccss.Top+lkToolBarAccss.Height,200,200,alClient);
    with lkDBG do
      begin
      DataSource := TDataSource.Create(lkDTSChild);
      with DataSource do
        begin
        Name    := 'DataSource'+lkDTSChild.Name;
        DataSet := lkDTSChild; 
        end;
      AllowedOperations := [alopUpdateEh];
      RowHeight         := 16;
      Font.Name         := 'Verdana';
      Font.Size         := 7;
      Font.Style        := [fsBold];
      Options      := Options   + [dgAlwaysShowSelection];  
      OptionsEh    := OptionsEh + [dghFixed3D, dghFrozen3D, dghFooter3D, dghIncSearch, dghHighlightFocus, dghRowHighlight, dghColumnResize, dghExtendVertLines];
      VTitleMargin := 4;
      Columns.Clear;
      end;
    lkCol := CreateTColumnEh(lkDBG,'IMGIDX'   ,'',msg_erp_objeditormenu_dbg_role_img  , 20,taLeftJustify); lkCol.ReadOnly := true;
    with lkCol do
      begin
      KeyList.Text  := '0';
      PickList.Text := '0';
      ImageList     := CreateTImageList(lkDBG, 'ilRole', [208]);
      end;
    lkCol := CreateTColumnEh(lkDBG,'ROLE_ID'  ,'',msg_erp_objeditormenu_dbg_role_id   , 60,taRightJustify); lkCol.ReadOnly := true;
    lkCol := CreateTColumnEh(lkDBG,'ROLE_NAME','',msg_erp_objeditormenu_dbg_role_name ,280,taLeftJustify ); lkCol.ReadOnly := true;
    lkCol := CreateTColumnEh(lkDBG,'FLAG'     ,'',msg_erp_objeditormenu_dbg_role_accss, 28,taLeftJustify );
    with lkCol do
      begin
      KeyList.Text  := '1'+SQLCRLF+'0';
      PickList.Text := 'X'+SQLCRLF+'_';
      CheckBoxes    := true;
      end;
    lkDBG.FrozenCols := 3;  

    lkAct := TERPForm_CreateAction(Result,obj_name_erp_acttreeinsroot,msg_erp_acttreeinsroot,msg_erp_acttreeinsroot_hint,'',0,443,@TERPFormEdtrMenu_actTreeInsRoot_OnExecute,nil,lkToolBarLeft,lkMIMain);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_acttreeins    ,msg_erp_actins        ,msg_erp_actins_hint        ,'',0,440,@TERPFormEdtrMenu_actTreeIns_OnExecute    ,nil,lkToolBarLeft,lkMIMain);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_acttreedel    ,msg_erp_actdel        ,msg_erp_actdel_hint        ,'',0,442,@TERPFormEdtrMenu_actTreeDel_OnExecute    ,nil,lkToolBarLeft,lkMIMain);
    CreateTMenuItem(lkMIMain, lkMIMain.Name+'002', '_'+msg_erp_objeditormenu_access, '', '',244, 0);
    lkAct := TERPForm_CreateAction2(Result,obj_name_erp_objedtrmenu_actaccss_inherit,msg_erp_actaccss_inherit ,msg_erp_actaccss_inherit_hint,'',0,418,@TERPFormEdtrMenu_actAccsInherit_OnExecute,nil,lkToolBarLeft , 96,lkMIMain);
    CreateTMenuItem(lkMIMain, lkMIMain.Name+'003', '-', '', '',-1, 0);
    lkAct := TERPForm_CreateAction2(Result,obj_name_erp_objedtrmenu_actaccss_fill   ,msg_erp_actaccss_fill    ,msg_erp_actaccss_fill_hint   ,'',0,412,@TERPFormEdtrMenu_actAccsFill_OnExecute   ,nil,lkToolBarAccss, 96,lkMIMain);
    lkAct := TERPForm_CreateAction2(Result,obj_name_erp_objedtrmenu_actaccss_clear  ,msg_erp_actaccss_clear   ,msg_erp_actaccss_clear_hint  ,'',0,415,@TERPFormEdtrMenu_actAccsClear_OnExecute  ,nil,lkToolBarAccss, 96,lkMIMain);

    lkTS := CreateTxcTabSheet(lkPC,obj_name_erp_objedtrmenu_tslocal,msg_erp_objeditormenu_menulocal,599,Amunhotep.MainForm.StyleManager.Colors.Foreground);
    LocalizationIntf_Create(Result, lkTS, lkDS, 'TABL$_MENU' );

    with lkFBTreeView do
      begin
      BuildTree;  
      if(Items.Count > 0)then
        begin
        Items[0].Selected := true;
        TERPFormEdtrMenu_FBTreeView_OnClick(lkFBTreeView);
        end;
      end;

    TxcPageControlEx_ActivateDefaultPage(lkPC);
    Amunhotep.MainForm.xcMenu.AddMenu(lkMainMenu); lkMainMenu.OwnerDraw := true;
  end;
