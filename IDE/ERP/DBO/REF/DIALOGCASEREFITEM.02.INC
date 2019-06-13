{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.02.INC}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                      {$I PEAKTOP:OBJ/TIMAGELIST.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTBITMAP.INC}  {$I PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTBITMAP.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}         {$I PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}         {$ENDIF}
  //========== PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.02.INC ================
  procedure ERPDialogCaseReferenceItem02_CategoryButtons_OnButtonClicked(Sender: TObject; const Button: TButtonItem);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOK;
  end;
  //============================================================================
  function ERPDialogCaseItem02_Execute(const aSQL, aCaption, aLabelCaption, aIcon, aBitmap:string; var aItemID:string):Boolean;
  var
    lkFrm     :TForm;
    lkTopBar  :TxcGradientPanelVista;
    lkIL32    :TImageList; 
    lkCBTNS   :TCategoryButtons;
    lkCategory:TButtonCategory;
    lkTr      :TxFBTransaction;
    lkQr      :TxFBQuery;
  label
    loop;  
  begin
    Result := false;
    lkFrm := TERPForm_Create(aCaption, aIcon, aBitmap, true, nil);
    with lkFrm do
      begin
      AlphaBlendValue := 224;
      AlphaBlend      := true;
      Position        := poDesktopCenter;
      Height          := 320;
      Width           := 800;
      BorderStyle := bsDialog;
      end;
    with TERPForm_Settings(lkFrm) do
      begin
      Values[ERP_SETTINGS_BOOKMARK    ] := '0';
      Values[ERP_SETTINGS_DATAMEMORY  ] := '0';
      Values[ERP_SETTINGS_SAVERECNO   ] := '0';
      Values[ERP_SETTINGS_BUFFERVAR   ] := '';
      Values[ERP_SETTINGS_GOTOVAR     ] := '';
      Values[ERP_SETTINGS_TABLENAME   ] := '';
      Values[ERP_SETTINGS_TABLECAPTION] := aCaption;
      Values[ERP_SETTINGS_TYPESLIST   ] := '';
      Values[ERP_SETTINGS_BASETYPE    ] := '0';
      end;
    lkTopBar := TxcGradientPanelVista( lkFrm.FindComponent(obj_name_erp_topbar) );
    with lkTopBar do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_REF);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_REF);
      end;  
    lkIL32   := CreateTImageListSimple(lkFrm, 'il32', 32, 32); Files_LoadBitmapToImageList(lkIL32, PrepareAbsoleteFileName(aBitmap) );
    lkCBTNS  := TCategoryButtons.Create(lkFrm);
    with lkCBTNS do
      begin
      Name                        := 'CategoryButtons';
      Parent                      := lkFrm;
      BorderStyle                 := bsNone;
      Align                       := alClient;
      BackgroundGradientColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
      BackgroundGradientDirection := gdLeftToRight; 
      ButtonFlow                  := cbfVertical;
      ButtonOptions               := [boGradientFill,boShowCaptions,boBoldCaptions,boUsePlusMinus,boCaptionOnlyBorder];
      Color                       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Name                   := 'Verdana';
      Font.Color                  := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style                  := [fsBold];
      Font.Size                   := 12;
      GradientDirection           := gdTopToBottom;
      HotButtonColor              := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      RegularButtonColor          := clNone;
      SelectedButtonColor         := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
      ShowHint                    := true;
      Images                      := lkIL32;
      ButtonHeight                := Images.Height + 2;
      ButtonWidth                 := Images.Height * 6 + 4;
      OnButtonClicked             := @ERPDialogCaseReferenceItem02_CategoryButtons_OnButtonClicked;
      SelectedItem                := nil;
      end;
    lkCategory := lkCBTNS.Categories.Add;
    with lkCategory do
      begin 
      ImageIndex    := -1;
      Caption       := aLabelCaption;
      Color         := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
      GradientColor := Amunhotep.MainForm.StyleManager.Colors.Border;
      TextColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
      end;
    lkTr      := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      with Params do
        begin
        Clear;
        Add('isc_tpb_read_committed');
        Add('isc_tpb_read');
        Add('isc_tpb_rec_version');
        Add('isc_tpb_nowait');
        end;
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQr do
      begin
      Transaction := lkTr;
      SQL.Text    := aSQL;
      end;
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      with lkCategory.Items.Add do
        begin
        Caption     := lkQr.FieldByName('NAME').AsString;
        CaptionSmall:= lkQr.FieldByName('ID').AsString;
        Hint        := lkQr.FieldByName('NAME').AsString;
        ImageIndex  := 0;
        end;
      if(lkQr.FieldByName('ID').AsString = aItemID)then
        lkCBTNS.SelectedItem := lkCategory.Items[lkCategory.Items.Count - 1];
      lkQr.Next;  
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free; 
    if(lkCBTNS.SelectedItem = nil)then
      if(lkCategory.Items.Count > 0)then
        lkCBTNS.SelectedItem := lkCategory.Items[0]; 
    lkFrm.Height := Screen.Height - 96;    
    lkFrm.Width  := Screen.Width  - 32;    
  loop:          
    lkCategory.Collapsed := false;
    Result := (lkFrm.ShowModal = mrOk);
    if Result then
      begin
      aItemID := lkCBTNS.SelectedItem.CaptionSmall;
      if(StrTrimAll(aItemID) = '')then
        goto loop;
      end;
    lkFrm.Free;
  end;  
  //============================================================================
  function ERPDialogCaseReferenceItem02_Execute(const aObjId, aLabelCaption:string; var aReferenceID:string):Boolean;
  var
    lkCaption :string;
  begin
    Result := false;
    lkCaption := '';
    GetField(FBDataBase, 'TABL$_TB', 'NAME', 'TRIM(ID) = '''+aObjId+'''', lkCaption);
    Result := ERPDialogCaseItem02_Execute(
      'SELECT R.ID, R.NAME FROM '+aObjId+' R WHERE (R.FLAG_DELETE <> 1) OR (R.FLAG_DELETE IS NULL) ORDER BY R.ID ', 
      ERP_ObjectCaption(ERP_OBJECTTYPE_REF) +': '+lkCaption, 
      aLabelCaption, ERP_ObjectIcon(ERP_OBJECTTYPE_REF), ERP_ObjectBitmap(ERP_OBJECTTYPE_REF), aReferenceID);
  end;
  //============================================================================
  function ERPDialogCaseReferenceItem03_Execute(const aObjId, aWhereClause, aLabelCaption:string; var aReferenceID:string):Boolean;
  var
    lkCaption :string;
  begin
    Result := false;
    lkCaption := '';
    GetField(FBDataBase, 'TABL$_TB', 'NAME', 'TRIM(ID) = '''+aObjId+'''', lkCaption);
    Result := ERPDialogCaseItem02_Execute(
      'SELECT R.ID, R.NAME FROM '+aObjId+' R WHERE ((R.FLAG_DELETE <> 1) OR (R.FLAG_DELETE IS NULL)) AND ('+aWhereClause+') ORDER BY R.NAME ', 
      ERP_ObjectCaption(ERP_OBJECTTYPE_REF) +': '+lkCaption, 
      aLabelCaption, ERP_ObjectIcon(ERP_OBJECTTYPE_REF), ERP_ObjectBitmap(ERP_OBJECTTYPE_REF), aReferenceID);
  end;
