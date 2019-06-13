{$DEFINE PEAKTOP:IDE/DEVELOPMENT/EDITOR/LNGPASCAL/CODETREE.INC}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/EDITOR/OBJNAMES.INC} {$I ../OBJNAMES.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/EDITOR/ACTIONS.INC}  {$I ../ACTIONS.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                  {$I PEAKTOP:OBJ/TIMAGELIST.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                    {$I PEAKTOP:OBJ/TXCPANEL.INC}   {$ENDIF}
  //========== PEAKTOP:IDE/DEVELOPMENT/EDITOR/LNGPASCAL/CODETREE.INC ===========
  procedure Editor_CodeTree_AddItems(aTreeView:TTreeView; aParentNode:TTreeNode; aItems:TxsCodeItems; aImageIndex :Integer);
  var
    j      :Integer;
    lkSL   :TStringList;
    lkPoint:TPoint;
  begin
    for j:=0 to aItems.Count-1 do
      begin
      lkPoint   := aItems[j].Addr;
      lkSL      := TStringList.Create;
      lkSL.Text := IntToStr(lkPoint.X)+#13#10+IntToStr(lkPoint.Y);
      with aTreeView.Items.AddChild(aParentNode, aItems[j].Caption) do
        begin
        DataObject    := lkSL;
        ImageIndex    := aImageIndex;
        SelectedIndex := aImageIndex;
        StateIndex    := aImageIndex;
        end;
      end;
  end;
  //============================================================================
  procedure Editor_CodeTree_OnParseEnd(Sender: TObject; CodeItems: TxsCodeItems);
  var
    i           :Integer;
    lkTreeView  :TTreeView;
    lkNodeMain  :TTreeNode;
  begin    
    if not(Amunhotep.MainForm.MDIChildCount>0)then exit;
    if(UpperCase(Amunhotep.MainForm.ActiveMDIChild.ClassName) <> 'TAMUNHOTEPEDITORFORM')then exit;
    lkTreeView := TTreeView(Amunhotep.MainForm.ActiveMDIChild.FindComponent(editor_obj_name_treeview_code));
    if(lkTreeView = nil)then exit;
    with lkTreeView.Items do
      begin
      BeginUpdate;
      Clear;
      for i:=0 to CodeItems.Count-1 do
        begin
        if(CodeItems[i].Caption = 'P')then
          begin
          lkNodeMain := AddChild(nil, 'procedures');
          with lkNodeMain do
            begin
            DataObject    := nil;
            ImageIndex    := 0;
            SelectedIndex := 0;
            StateIndex    := 0;
            end;
          Editor_CodeTree_AddItems(lkTreeView, lkNodeMain, CodeItems[i].Items, 3);
          end; 
        if(CodeItems[i].Caption = 'F')then
          begin
          lkNodeMain := AddChild(nil, 'functions');
          with lkNodeMain do
            begin
            DataObject    := nil;
            ImageIndex    := 0;
            SelectedIndex := 0;
            StateIndex    := 0;
            end;
          Editor_CodeTree_AddItems(lkTreeView, lkNodeMain, CodeItems[i].Items, 2);
          end; 
        if(CodeItems[i].Caption = 'I')then
          begin
          lkNodeMain := AddChild(nil, 'includes');
          with lkNodeMain do
            begin
            DataObject    := nil;
            ImageIndex    := 0;
            SelectedIndex := 0;
            StateIndex    := 0;
            end;
          Editor_CodeTree_AddItems(lkTreeView, lkNodeMain, CodeItems[i].Items, 1);
          end; 
        if(CodeItems[i].Caption = 'D')then
          begin
          lkNodeMain := AddChild(nil, 'defines');
          with lkNodeMain do
            begin
            DataObject    := nil;
            ImageIndex    := 0;
            SelectedIndex := 0;
            StateIndex    := 0;
            end;
          Editor_CodeTree_AddItems(lkTreeView, lkNodeMain, CodeItems[i].Items, 4);
          end; 
        end;
      AlphaSort(true);
      EndUpdate;
      end;
  end;
  //============================================================================
  procedure Editor_TreeViewCode_OnDeletion(Sender: TObject; Node: TTreeNode);
  begin
    if(Node.DataObject <> nil)then
      try Node.DataObject.Free; except end;  
  end;
  //============================================================================
  procedure Editor_TreeViewCode_OnDblClick(Sender :TObject);
  begin
    if(TTreeView(Sender).SelectedNode = nil)then exit;
    if(TTreeView(Sender).SelectedNode.DataObject = nil)then exit;
    with TSynEdit(TComponent(Sender).Owner.FindComponent('SynEdit')) do
      begin
      {$IFDEF CODEFOLDING}
      UncollapseAll;
      {$ENDIF}
      CaretX  := StrToInt(TStringList(TTreeView(Sender).SelectedNode.DataObject)[0]);
      CaretY  := StrToInt(TStringList(TTreeView(Sender).SelectedNode.DataObject)[1]);
      TopLine := CaretY + 1;
      end;
  end;
  //============================================================================
  procedure Editor_SynEdit_OnChange(Sender: TObject);
  var
    lkPasParser :TxsThreadParsePas;
  begin
    {$IFDEF CODEFOLDING}
    TSynEdit(Sender).ReScanForFoldRanges;
    {$ENDIF}
    TAmunhotepForm(TComponent(Sender).Owner).Modified := true;
    if TxcPanel(TComponent(Sender).Owner.FindComponent(editor_obj_name_codetree)).Visible then
      {$IFDEF CODEFOLDING}
      lkPasParser := TxsThreadParsePas.Create(TSynEdit(Sender).GetUncollapsedStrings.Text, @Editor_CodeTree_OnParseEnd);
      {$ELSE}
      lkPasParser := TxsThreadParsePas.Create(TSynEdit(Sender).Text                      , @Editor_CodeTree_OnParseEnd);
      {$ENDIF}
  end;
  //============================================================================
  procedure Editor_actViewCodeTree_OnExecute(Sender :TObject);
  var
    lkPasParser :TxsThreadParsePas;
  begin
    with TxcPanel(TComponent(Sender).Owner.FindComponent(editor_obj_name_codetree)) do
      begin
      Visible := not Visible;
      TSplitter(FindComponent(editor_obj_name_codetree_splitter)).Visible := Visible;
      if Visible then
        begin
        TSplitter(FindComponent(editor_obj_name_codetree_splitter)).Left := Left + Width + 1;
        with TSynEdit(TComponent(Sender).Owner.FindComponent('SynEdit')) do
          {$IFDEF CODEFOLDING}
          lkPasParser := TxsThreadParsePas.Create(GetUncollapsedStrings.Text, @Editor_CodeTree_OnParseEnd);
          {$ELSE}
          lkPasParser := TxsThreadParsePas.Create(Text                      , @Editor_CodeTree_OnParseEnd);
          {$ENDIF}
        end;
      end;
  end;
  //============================================================================
  procedure Editor_actViewCodeTree_OnUpdate(Sender :TObject);
  begin
    with TxcPanel(TComponent(Sender).Owner.FindComponent(editor_obj_name_codetree)) do
      TCustomAction(Sender).Checked := Visible;
  end;
  //============================================================================
  procedure Editor_CodeTree_Create(aOwnerForm :TAmunhotepEditorForm);
  var
    lkPanelLeft  :TxcPanel;
    lkSynEdit    :TSynEdit;
    lkTreeView   :TTreeView;
    lkAct        :TCustomAction;
  begin
    DontAutoFree;
    lkPanelLeft := CreateTxcPanel(aOwnerForm, aOwnerForm, editor_obj_name_codetree,'',alLeft  ,  0,0,100,280,xbsNone);
    lkPanelLeft.Visible := false;
    with TSplitter.Create(lkPanelLeft) do
      begin
      Name   := editor_obj_name_codetree_splitter;
      Visible:= lkPanelLeft.Visible;
      Parent := aOwnerForm;
      Align  := alLeft;
      Width  := 4;
      Color  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Left   := lkPanelLeft.Left + lkPanelLeft.Width + 4;
      end;
    lkTreeView := TTreeView.Create(aOwnerForm);
    with lkTreeView do
      begin
      Name       := editor_obj_name_treeview_code;
      Parent     := lkPanelLeft;
      Ctl3D      := false;
      Left       := 0;
      Top        := 0;
      Align      := alClient;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Images     := CreateTImageList(lkTreeView, 'ImageList', [30, 26, 21, 19, 29]);
      OnDblClick := @Editor_TreeViewCode_OnDblClick;
      OnDeletion := @Editor_TreeViewCode_OnDeletion;
      Items.Clear;
      end;
    lkSynEdit := TSynEdit(aOwnerForm.FindComponent('SynEdit'));
    lkSynEdit.OnChange := @Editor_SynEdit_OnChange;
    lkAct := CreateEditorAction(aOwnerForm, 'Editor_actViewCodeTree', 'Code tree', 'Code tree', 'F2', 0, 18, 
                    @Editor_actViewCodeTree_OnExecute, @Editor_actViewCodeTree_OnUpdate, 
                    true, TMenuItem(aOwnerForm.FindComponent('miEditView')), 
                    false, nil, 
                    true, TxcGradientPanel(aOwnerForm.FindComponent(editor_obj_name_toolbarmain)));
  end;
