{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_CASELISTTEM.INC}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                      {$I PEAKTOP:OBJ/TIMAGELIST.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTBITMAP.INC}  {$I PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTBITMAP.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}         {$I ./FORMERP.INC}                                   {$ENDIF}
  //========== PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.02.INC ================
  procedure ERPDialogCaseListItem_CategoryButtons_OnButtonClicked(Sender: TObject; const Button: TButtonItem);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOK;
  end;
  //============================================================================
  function ERPDialogCaseListItemInteger_Execute(const aCaption, aLabelCaption, aImageFileName, aItems:string; var aItemID:Integer):Boolean;
  var
    lkFN      :string;
    lkFrm     :TForm;
    lkTopBar  :TxcGradientPanelVista;
    lkIL32    :TImageList; 
    lkCBTNS   :TCategoryButtons;
    lkCategory:TButtonCategory;
    lkSL      :TStringList;
    i         :Integer;
  begin
    Result := false;
    if FileExists( PrepareAbsoleteFileName(aImageFileName) ) then
      lkFN := PrepareAbsoleteFileName(aImageFileName)
     else
      lkFN := ERP_ObjectBitmap(ERP_OBJECTTYPE_REF); 
    lkFrm := TERPForm_Create(aCaption, '', lkFN, true, nil);
    with lkFrm do
      begin
      AlphaBlendValue := 224;
      AlphaBlend      := true;
      Position := poDesktopCenter;
      Height   := 320;
      Width    := 480;
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
    lkIL32   := CreateTImageListSimple(lkFrm, 'il32', 32, 32); Files_LoadBitmapToImageList(lkIL32, PrepareAbsoleteFileName(lkFN) );
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
      ButtonHeight                := Images.Height + 4;
      ButtonWidth                 := lkFrm.Width - 24;
      OnButtonClicked             := @ERPDialogCaseListItem_CategoryButtons_OnButtonClicked;
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
    lkSL := TStringList.Create;
    lkSL.Text := aItems;
    for i:=0 to lkSL.Count-1 do
      begin
      with lkCategory.Items.Add do
        begin
        Caption     := lkSL[i];
        CaptionSmall:= '';
        Hint        := lkSL[i];
        ImageIndex  := 0;
        end;
      if(aItemID = i)then
        lkCBTNS.SelectedItem := lkCategory.Items[lkCategory.Items.Count - 1];
      end;
    if(lkCBTNS.SelectedItem = nil)then
      if(lkCategory.Items.Count > 0)then
        lkCBTNS.SelectedItem := lkCategory.Items[0]; 
    lkFrm.Height := 96 + (lkCBTNS.ButtonHeight * lkCategory.Items.Count);    
    lkCategory.Collapsed := false;
    Result := (lkFrm.ShowModal = mrOk);
    if Result then
      aItemID := lkCBTNS.SelectedItem.Index;
    lkFrm.Free;
  end;
