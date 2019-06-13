{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/DIALOGCASEJRNL.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC} {$I PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}              {$I PEAKTOP:OBJ/TIMAGELIST.INC}               {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASE.INC ===================
  procedure ERP_DialogCaseRef_FBTreeView_OnBuildNode(Sender :TObject; StateFieldValue :Variant; var StateImage :Integer);
  begin
    StateImage := 41;
  end;
  //============================================================================
  procedure ERP_DialogCaseRef_FBTreeView_OnClick(Sender :TObject);
  var
    lkListView:TListView;
    lkTr      :TxFBTransaction;
    lkQr      :TxFBQuery;
  begin
    lkListView := TListView(TComponent(Sender).Owner.FindComponent('ListView'));
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
      SQL.Text    := 'SELECT T.ID, T.NAME FROM TABL$_TB_TYPES T WHERE (T.PARENT_ID = '''+TxFBTreeView(Sender).GetId+''') ORDER BY T.NAME ';
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
  procedure ERP_DialogCaseRef_ListView_OnDblClick(Sender :TObject);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  function ERP_DialogCaseJrnl_Create(var aTYPE_ID:string):TForm;
  var
    lkFBTree  :TxFBTreeView;
    lkListView:TListView;
    lkSplt    :TSplitter;
    lkBMP     :TBitMap;
    lkFileName:string;
  begin
    Result := TERPForm_Create('Выберите '+ERP_FolderObjectCaption(4),  ERP_FILENAME_ICO_JRNL, ERP_FILENAME_BMP_JRNL, true, nil);
    with Result do
      begin
      Position := poDesigned;
      end; 
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_JRNL);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_JRNL);
      end;  
    TForm_Position_Load(Result, PrepareAbsoleteFileName('TMP:'+ERP_FILENAME_CFG_DIALOGCASEOBJ), 600, 600);             
    lkFBTree := TxFBTreeView.Create(Result);
    with lkFBTree do
      begin
      Parent    := Result;
      Left      := 0;
      Top       := 0;
      Width     := 180;
      Ctl3D     := false;
      Align     := alLeft;
      Color     := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color:= Amunhotep.MainForm.StyleManager.Colors.Border;
      Images    := Amunhotep.MainForm.ImageListMain;
      DataBase  := FBDataBase;
      with DBTreeInfo do
        begin
        TableName     := 'TABL$_TB_TYPES';
        FieldId       := 'ID';
        FieldParentId := 'PARENT_ID';
        FieldStateId  := 'ID';
        FieldName     := 'NAME';
        Where         := '(SELECT FIRST 1 P.ID FROM PROC$_TB_TYPES_GET_ROOT(ID) P) = 4';
        end;
      ShowOnlyRoots    := true;
      RightClickSelect := true;
      HideSelection    := false;
      OnBuildNode      := @ERP_DialogCaseRef_FBTreeView_OnBuildNode;  
      OnClick          := @ERP_DialogCaseRef_FBTreeView_OnClick;
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
      Left   := lkFBTree.Left + lkFBTree.Width + 4;
      Top    := 0;
      Width  := 4;
      Align  := alLeft;
      Color  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      end;
    lkListView := TListView.Create(Result);
    with lkListView do
      begin
      Name          := 'ListView';
      Parent        := Result;
      Left          := lkSplt.Left + lkSplt.Width + 4;
      Top           := 0;
      Width         := 1;
      Ctl3D         := false;
      Align         := alClient;
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      LargeImages   := CreateTImageListSimple(Result, 'ilImagesLarge', 32,32);
      SmallImages   := CreateTImageList(Result, 'ilImagesSmall', [42]);
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
      OnDblClick    := @ERP_DialogCaseRef_ListView_OnDblClick;
      end;
    lkFileName := PrepareAbsoleteFileName(ERP_FILENAME_BMP_JRNL);
    if FileExists(lkFileName)then
      try
        lkBmp := TBitmap.Create;
        lkBmp.LoadFromFile(lkFileName);
        lkListView.LargeImages.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
      finally    
        lkBmp.Free;
      end;
    ERP_DialogCaseRef_FBTreeView_OnClick(lkFBTree);
  end;
  //============================================================================
  function ERP_DialogCaseJrnl_Execute(var aTYPE_ID:string):Boolean;
  var
    lkForm :TForm;
  begin
    lkForm := ERP_DialogCaseJrnl_Create(aTYPE_ID);
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      aTYPE_ID := TListView(lkForm.FindComponent('ListView')).Selected.SubItems[0];
      end;
    TForm_Position_Save(lkForm, PrepareAbsoleteFileName('TMP:'+ERP_FILENAME_CFG_DIALOGCASEOBJ));  
    lkForm.Free; 
  end;
