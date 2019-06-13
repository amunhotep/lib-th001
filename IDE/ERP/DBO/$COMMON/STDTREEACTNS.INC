{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/STDTREEACTNS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                   {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}              {$I ../SHORTCUTS.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}            {$I ../OBJECTNAMES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}  {$I ./FORMERP_NAMES.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}   {$I ./FORMERP_LANG.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC} {$I ./FORMERP_HEADER.INC}          {$ENDIF}
  //========= PEAKTOP:IDE/ERP/DBO/$COMMON/STDTREEACTNS.INC =====================
type
  TERPTreeAction  = (eacTreeNew,eacTreeIns,eacTreeUpd,eacTreeEdt,eacTreeDel);
  TERPTreeActions = set of TERPTreeAction;  
  //============================================================================
  procedure TERPForm_StandardTree_AfterBuildData(aFBTreeView :TxFBTreeView); forward;
  //============================================================================
  procedure TERPForm_actStdTreeIns_OnExecute(Sender :TObject);
  var
    lkNewName :string;
    lkF       :Boolean;
  begin
    with TxFBTreeView(TComponent(Sender).Owner) do
      if(Dialogs.InputQueryString(msg_erp_acttreeins_hint, msg_erp_enter_new_item_name, lkNewName))then
        begin
        lkNewName := StrReplaceStr(lkNewName, '''', '''''');
        ExecSQL(FBDataBase, 'INSERT INTO '+DBTreeInfo.TableName+' ('+DBTreeInfo.FieldName+', '+DBTreeInfo.FieldParentId+')VALUES('''+lkNewName+''', '''+GetId+''') ');
        lkF := false;  
        if(SelectedNode <> nil)then
          if(SelectedNode.Parent <> nil)then
            lkF := true;
        if lkF then
          RebuildSelected
         else
          begin
          BuildTree;
          if(Items.Count > 0)then
            Items[0].Selected := true;
          TERPForm_StandardTree_AfterBuildData(TxFBTreeView(TComponent(Sender).Owner));
          end;   
        end; 
  end;
  //============================================================================
  procedure TERPForm_actStdTreeIns_OnUpdate(Sender :TObject);
  begin 
    with TxFBTreeView(TComponent(Sender).Owner) do
      TCustomAction(Sender).Enabled := (Items.Count > 0);
  end;
  //============================================================================
  procedure TERPForm_actStdTreeNew_OnExecute(Sender :TObject);
  var
    lkNewName :string;
  begin
    with TxFBTreeView(TComponent(Sender).Owner) do
      if(Dialogs.InputQueryString(msg_erp_acttreeinsroot_hint, msg_erp_enter_new_item_name, lkNewName))then
        begin
        lkNewName := StrReplaceStr(lkNewName, '''', '''''');
        ExecSQL(FBDataBase, 'INSERT INTO '+DBTreeInfo.TableName+'('+DBTreeInfo.FieldName+', '+DBTreeInfo.FieldParentId+')VALUES('''+lkNewName+''', '''+DBTreeInfo.RootParentId+''') ');
        BuildTree;
        if(Items.Count > 0)then
          begin
          Items[0].Selected := true;
          TERPForm_StandardTree_AfterBuildData(TxFBTreeView(TComponent(Sender).Owner));
          end;
        end;
  end;
  //============================================================================
  procedure TERPForm_actStdTreeUpd_OnExecute(Sender :TObject);
  var
    lkNewName :string;
  begin
    with TxFBTreeView(TComponent(Sender).Owner) do
      begin
      lkNewName := SelectedNode.Text;
      if(Dialogs.InputQueryString(msg_erp_acttreeupd_hint, msg_erp_enter_new_item_name, lkNewName))then
        begin
        SelectedNode.Text := lkNewName;  
        lkNewName := StrReplaceStr(lkNewName, '''', '''''');
        ExecSQL(FBDataBase, 'UPDATE '+DBTreeInfo.TableName+' '+ERP_SQL_TABLEPREFIX+' SET '+ERP_SQL_TABLEPREFIX+'.'+DBTreeInfo.FieldName+' = '''+lkNewName+''' WHERE ('+ERP_SQL_TABLEPREFIX+'.'+DBTreeInfo.FieldId+' = '''+GetId+''') ');
        lkNewName := '';
        GetField(FBDataBase, DBTreeInfo.TableName, DBTreeInfo.FieldName, DBTreeInfo.FieldId+' = '''+GetId+'''',lkNewName);
        SelectedNode.Text := lkNewName;  
        end;
      end;  
  end;
  //============================================================================
  procedure TERPForm_actStdTreeEdt_OnExecute(Sender :TObject);
  var
    lkBuffVar :string;
    lkScript  :string;
    lkNewName :string;
  begin
    with TxFBTreeView(TComponent(Sender).Owner) do
      begin
      lkScript := ''; GetField(FBDataBase, 'TABL$_TB', 'SC_ITEM_DLG', 'ID = '''+DBTreeInfo.TableName+'''', lkScript ); if(lkScript = '')then exit;
      lkBuffVar:= ''; GetField(FBDataBase, 'TABL$_TB', 'BUFFER_VAR' , 'ID = '''+DBTreeInfo.TableName+'''', lkBuffVar); if(lkBuffVar = '')then exit;
      SetGlobalVariable(lkBuffVar, GetId);
      call(lkScript);
      lkNewName := '';
      GetField(FBDataBase, DBTreeInfo.TableName, DBTreeInfo.FieldName, DBTreeInfo.FieldId+' = '''+GetId+'''',lkNewName);
      SelectedNode.Text := lkNewName;  
      end;  
  end;
  //============================================================================
  procedure TERPForm_actStdTreeDel_OnExecute(Sender :TObject);
  begin
    with TxFBTreeView(TComponent(Sender).Owner) do
      if(Dialogs.MessageDlg(msg_erp_acttreedel_hint+' "'+SelectedNode.Text+'" ?', mtConfirmation, [mbYes, mbNo])=mrYes)then
        begin
        ExecSQL(FBDataBase, 'DELETE FROM '+DBTreeInfo.TableName+' '+ERP_SQL_TABLEPREFIX+' WHERE ('+ERP_SQL_TABLEPREFIX+'.'+DBTreeInfo.FieldId+' = '''+GetId+''') ');
        BuildTree;
        if(Items.Count > 0)then
          begin
          Items[0].Selected := true;
          TERPForm_StandardTree_AfterBuildData(TxFBTreeView(TComponent(Sender).Owner));
          end;  
        end;
  end;
  //============================================================================
  procedure TERPForm_StandardTree_CreateActions(aOwner:TxFBTreeView; aBar:TxcGradientPanel; aMI:TMenuItem; aActionsSet:TERPTreeActions);
  begin
    if(eacTreeNew in aActionsSet)then TERPForm_CreateAction(aOwner,obj_name_erp_acttreenew,msg_erp_acttreenew,msg_erp_acttreenew_hint,SHORTCUT_TREE_NEW   ,0,79,@TERPForm_actStdTreeNew_OnExecute,nil                             ,aBar,aMI);
    if(eacTreeIns in aActionsSet)then TERPForm_CreateAction(aOwner,obj_name_erp_acttreeins,msg_erp_acttreeins,msg_erp_acttreeins_hint,SHORTCUT_TREE_INSERT,0,82,@TERPForm_actStdTreeIns_OnExecute,@TERPForm_actStdTreeIns_OnUpdate,aBar,aMI);
    if(eacTreeUpd in aActionsSet)then TERPForm_CreateAction(aOwner,obj_name_erp_acttreeupd,msg_erp_acttreeupd,msg_erp_acttreeupd_hint,SHORTCUT_TREE_UPDATE,0,38,@TERPForm_actStdTreeUpd_OnExecute,@TERPForm_actStdTreeIns_OnUpdate,aBar,aMI);
    if(eacTreeEdt in aActionsSet)then TERPForm_CreateAction(aOwner,obj_name_erp_acttreeedt,msg_erp_acttreeedt,msg_erp_acttreeedt_hint,SHORTCUT_TREE_EDIT  ,0,78,@TERPForm_actStdTreeEdt_OnExecute,@TERPForm_actStdTreeIns_OnUpdate,aBar,aMI);
    if(eacTreeDel in aActionsSet)then TERPForm_CreateAction(aOwner,obj_name_erp_acttreedel,msg_erp_acttreedel,msg_erp_acttreedel_hint,SHORTCUT_TREE_DELETE,0,33,@TERPForm_actStdTreeDel_OnExecute,@TERPForm_actStdTreeIns_OnUpdate,aBar,aMI);
  end;
