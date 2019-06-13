{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_CASEOBJECT.INC}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                     {$I PEAKTOP:OBJ/TXCPANEL.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/STDTREEACTNS.INC} {$I ./STDTREEACTNS.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I ./FORMERP.INC}            {$ENDIF}
  //============= PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_CASEOBJECT.INC ============
const ERP_OBJNAME_OPER_DLG_CASEOBJECT = 'DLG_CASEOBJECT';
  //============================================================================
  procedure ERPDialogCaseObj_FBTreeView_OnBuildNode(Sender :TObject; StateFieldValue :Variant; var StateImage :Integer);
  begin
    StateImage := TComponent(Sender).Tag;
    if(StateImage < ERP_OBJECTTYPES_OFFSET)then
      StateImage := StateImage + ERP_OBJECTTYPES_OFFSET;
  end;
  //============================================================================
  procedure ERPDialogCaseObj_FBTreeView_OnClick(Sender :TObject);
  var
    lkListView:TListView;
    lkTr      :TxFBTransaction;
    lkQr      :TxFBQuery;
  begin
    lkListView := TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview));
    lkListView.Items.Clear;
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
    with lkQr do
      begin
      Transaction := lkTr;
      SQL.Text    := ERP_ObjectItemsSQL(lkListView.Owner.Tag, TxFBTreeView(Sender).GetId); 
      end;
    try
      lkQr.Open;
    except
    end;
    if not lkQr.Active then
      begin
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      exit;
      end;
    lkQr.First;
    while not lkQr.EOF do
      begin
      with lkListView.Items.Add do
        begin
        Caption    := lkQr.FieldByName('NAME').AsString;
        ImageIndex := 0;
        SubItems.Clear;
        SubItems.Add(lkQr.FieldByName('ID').AsString);
        end;
      lkQr.Next;
      end;  
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
  end;
  //============================================================================
  procedure TERPForm_StandardTree_AfterBuildData(aFBTreeView :TxFBTreeView);
  begin
    ERPDialogCaseObj_FBTreeView_OnClick(aFBTreeView);
  end;                
  //============================================================================
  procedure ERPDialogCaseObj_ListView_OnDblClick(Sender :TObject);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  function ERPDialogCaseObj_Create(const aObjectType:Integer; var aTB_ID:string):TForm;
  var
    lkPnlLeft :TxcPanel;
    lkTBLeft  :TxcGradientPanelVista;
    lkFBTree  :TxFBTreeView;
    lkListView:TListView;
    lkSplt    :TSplitter;
    lkBMP     :TBitMap;
    lkFileName:string; 
  begin
    Result := TERPForm_Create('Выберите '+ERP_ObjectCaption(aObjectType),  ERP_ObjectIcon(aObjectType), ERP_ObjectBitmap(aObjectType), true, nil);
    with Result do
      begin
      Position := poDesigned;
      Tag      := aObjectType;
      end;            
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(aObjectType);
      Colors.HotTrackBorder := ERP_ObjectColor(aObjectType);
      end;  
    TForm_Position_Load(Result, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLG_CASEOBJECT,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))), 600, 600);             
    lkPnlLeft:= CreateTxcPanel(Result,Result,obj_name_erp_panelleft,'',alLeft,0,0,200,180,xbsNone);
    lkTBLeft := CreateTxcGradientPanelVistaToolBar(Result,lkPnlLeft,'','',alTop,0,0,TERPForm_DefaultToolButtonWidth,180,xbsRaized);
    lkFBTree := TxFBTreeView.Create(Result);
    with lkFBTree do
      begin
      Name      := obj_name_erp_fbtreeview;
      Parent    := lkPnlLeft;
      Left      := 0;
      Top       := lkTBLeft.Top + lkTBLeft.Height + 1;
      Width     := 180;
      Ctl3D     := false;
      Align     := alClient;
      Color     := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color:= Amunhotep.MainForm.StyleManager.Colors.Border;
      Images    := CreateTImageListConfiguration(lkFBTree, 'ilConfig');
      Tag       := aObjectType;
      DataBase  := FBDataBase;
      with DBTreeInfo do
        begin
        TableName     := ERP_ObjectFolderTable(aObjectType);
        FieldId       := 'ID';
        FieldParentId := 'PARENT_ID';
        FieldStateId  := 'ID';
        FieldName     := 'NAME';
        RootParentId  := '0';
        if(aObjectType <> ERP_OBJECTTYPE_USER)then
          begin
          if(aObjectType < ERP_OBJECTTYPES_OFFSET)then // BUGFIX: for journal we must use document object type !
            Where := 'ROOT_ID = '+IntToStr(aObjectType)
           else 
            Where := 'ROOT_ID = '+IntToStr(aObjectType - ERP_OBJECTTYPES_OFFSET);
          end
        end;
      ShowOnlyRoots    := false;
      RightClickSelect := true;
      HideSelection    := false;
      OnBuildNode      := @ERPDialogCaseObj_FBTreeView_OnBuildNode;  
      OnClick          := @ERPDialogCaseObj_FBTreeView_OnClick;
      BuildTree;
      if(Items.Count > 0)then
        begin
        Items[0].Selected := true;
        Items[0].Expand(true);
        end;  
      end;
    lkSplt := TSplitter.Create(Result);
    with lkSplt do
      begin
      Parent := Result;
      Left   := lkPnlLeft.Left + lkPnlLeft.Width + 4;
      Top    := 0;
      Width  := 4;
      Align  := alLeft;
      Color  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      end;
    lkListView := TListView.Create(Result);
    with lkListView do
      begin
      Name          := obj_name_erp_listview;
      Parent        := Result;
      Left          := lkSplt.Left + lkSplt.Width + 4;
      Top           := 0;
      Width         := 1;
      Ctl3D         := false;
      Align         := alClient;
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      LargeImages   := CreateTImageListSimple(Result, 'ilImagesLarge', 32,32);
      SmallImages   := CreateTImageList(Result, 'ilImagesSmall', [ERP_ObjectImageIndex(aObjectType)] );
      HideSelection := false;
      GridLines     := true;
      ReadOnly      := true;
      ViewStyle     := vsReport;
      Columns.Clear;
      with Columns.Add do
        begin
        Caption     := 'Название';
        Width       := 600;
        end;
      with Columns.Add do
        begin
        Caption     := 'Имя';
        Width       := 200;
        end;
      OnDblClick    := @ERPDialogCaseObj_ListView_OnDblClick;
      end;
    lkFileName := PrepareAbsoleteFileName(ERP_ObjectBitmap(aObjectType));
    if FileExists(lkFileName)then
      try
        lkBmp := TBitmap.Create;
        lkBmp.LoadFromFile(lkFileName);
        lkListView.LargeImages.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
      finally    
        lkBmp.Free;
      end;
    lkPnlLeft.Visible:= (aObjectType <> ERP_OBJECTTYPE_ROLE);
    if((aObjectType<>ERP_OBJECTTYPE_MENU) and (aObjectType<>ERP_OBJECTTYPE_ROLE))then  
      TERPForm_StandardTree_CreateActions(lkFBTree, lkTBLeft, nil, [eacTreeIns,eacTreeUpd,eacTreeDel]);  
    ERPDialogCaseObj_FBTreeView_OnClick(lkFBTree);
  end;
  //============================================================================
  function ERPDialogCaseObj_Execute(const aObjectType:Integer; var aObjectId:string):Boolean;
  var
    lkForm :TForm;
  begin
    lkForm := ERPDialogCaseObj_Create(aObjectType, aObjectId);
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      aObjectId := TListView(lkForm.FindComponent(obj_name_erp_listview)).Selected.SubItems[0];
    TForm_Position_Save(lkForm, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLG_CASEOBJECT,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))));   
    lkForm.Free; 
  end;  
