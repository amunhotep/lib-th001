{$DEFINE PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC} {$I PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC} {$ENDIF}
  //========== PEAKTOP:IDE/ERP/DBO/REF/DIALOGCASEREFITEM.INC ===================
  function ERPDialogCaseReferenceItem_Execute(const aObjId, aLabelCaption:string; var aReferenceID:string):Boolean;
  var
    lkCaption :string;
    lkStr     :string;
    lkFrm     :TForm;
    lkTopBar  :TxcGradientPanelVista;
    lkLabel   :TLabel;
    lkCbx     :TComboBox;
    lkValues  :TStringList;
    lkTr      :TxFBTransaction;
    lkQr      :TxFBQuery;
  begin
    Result := false;
    lkCaption := '';
    GetField(FBDataBase, 'TABL$_TB', 'NAME', 'TRIM(ID) = '''+aObjId+'''', lkCaption);
    lkFrm := TERPForm_Create(ERP_ObjectCaption(ERP_OBJECTTYPE_REF) +': '+lkCaption, 
               ERP_ObjectIcon(ERP_OBJECTTYPE_REF), ERP_ObjectBitmap(ERP_OBJECTTYPE_REF), true, nil);
    with lkFrm do
      begin
      Position := poDesktopCenter;
      Height   := 120;
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
      Values[ERP_SETTINGS_TABLENAME   ] := aObjId;
      Values[ERP_SETTINGS_TABLECAPTION] := lkCaption;
      Values[ERP_SETTINGS_TYPESLIST   ] := '';
      Values[ERP_SETTINGS_BASETYPE    ] := IntToStr(ERP_OBJECTTYPE_REF);
      end;
    lkTopBar := TxcGradientPanelVista( lkFrm.FindComponent(obj_name_erp_topbar) );
    with lkTopBar do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_REF);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_REF);
      end;  
    lkLabel := TLabel.Create(lkFrm);
    with lkLabel do
      begin
      Parent      := lkFrm;
      Left        := 8;
      Top         := lkTopBar.Top + lkTopBar.Height + 8;
      Width       := lkFrm.Width - 24;
      Height      := 20; 
      Transparent := true;
      Caption     := aLabelCaption;
      Font.Name   := 'Verdana';
      Font.Size   := 8;
      Font.Style  := [fsBold];
      end;
    lkCbx := TComboBox.Create(lkFrm);
    with lkCbx do
      begin
      Parent     := lkFrm;
      Ctl3d      := false;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style := [fsBold];
      Font.Name  := 'Verdana';
      Font.Size  := 8;
      Left       := 8;
      Width      := lkFrm.Width - 24;
      Top        := lkLabel.Top + lkLabel.Height + 8; 
      Items.Clear;
      end;
    lkValues  := TStringList.Create;
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
      SQL.Text := 'SELECT R.ID, R.NAME FROM '+aObjId+' R WHERE (R.FLAG_DELETE <> 1) OR (R.FLAG_DELETE IS NULL) ORDER BY R.ID ';
      end;
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkCbx.Items.Add(lkQr.FieldByName('NAME').AsString);
      lkValues.Add(lkQr.FieldByName('ID').AsString);
      if(lkQr.FieldByName('ID').AsString = aReferenceID)then
        lkCbx.ItemIndex := lkCbx.Items.Count - 1;
      lkQr.Next;  
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free; 
    if(lkCbx.ItemIndex < 0)then
      if(lkCbx.Items.Count > 0)then
        lkCbx.ItemIndex := 0;   
    lkCbx.Style := csDropDownList;
    Result := (lkFrm.ShowModal = mrOk);
    if Result then
      aReferenceID := lkValues[lkCbx.ItemIndex];
    lkValues.Free;  
    lkFrm.Free;
  end;
