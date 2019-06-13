{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/RESTORE_OPTIONS.INC}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/CUSTOM.INC}        {$I ./CUSTOM.INC}{$ENDIF}
  //================ PEAKTOP:IDE/FIREBIRD/DIALOGS/RESTORE_OPTIONS.INC ==========
  function FirebirdDialog_RestoreOptions_Execute(var aOptions:TxFBRestoreOptions; var aPageSize:TxsRestorePageSize):Boolean;
  var
    lkForm        :TForm;
    lkImg         :TImage;
    lkPanelClient :TxcGradientPanel;
    lkLastTop, i  :Integer;
    lkOpt         :TxFBRestoreOption;
    lkCBX         :array[0..7]of TxcCheckBox;
    lkCapts       :array[0..7]of string;
    lkLabel       :TLabel;
    lkCbxPageSize :TComboBox;
  begin
    Result := false;
    lkCapts[0] := msg_firebird_dialog_restoreoptions_items_000;
    lkCapts[1] := msg_firebird_dialog_restoreoptions_items_001;
    lkCapts[2] := msg_firebird_dialog_restoreoptions_items_002;
    lkCapts[3] := msg_firebird_dialog_restoreoptions_items_003;
    lkCapts[4] := msg_firebird_dialog_restoreoptions_items_004;
    lkCapts[5] := msg_firebird_dialog_restoreoptions_items_005;
    lkCapts[6] := msg_firebird_dialog_restoreoptions_items_006;
    lkCapts[7] := msg_firebird_dialog_restoreoptions_items_007;
    lkForm := FirebirdDialog_Create(msg_firebird_dialog_restoreoptions_caption, msg_firebird_dialog_button_caption_ok, msg_firebird_dialog_button_caption_cancel);
    lkPanelClient := TxcGradientPanel(lkForm.FindComponent('PanelClient'));
    lkImg := TImage(lkForm.FindComponent('ImageLogo'));
    lkLastTop := 8;
    i := 0;
    for lkOpt:=roDeactivateIndexes to roValidationCheck do
      begin
      lkCBX[i] := TxcCheckBox.Create(lkForm);
      with lkCBX[i] do
        begin
        Name         := 'CheckBox'+FormatFloat('00',i);
        Parent       := lkPanelClient;
        StyleManager := Amunhotep.MainForm.StyleManager;
        Font.Size    := DefaultFirebirdDialogLabelFontHeight;
        Font.Style   := [fsBold];
        Left         := lkImg.Left + lkImg.Width + 8;
        Width        := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
        Top          := lkLastTop; 
        Height       := 20;
        Caption      := lkCapts[i];
        Hint         := lkCapts[i];
        ShowHint     := true; 
        Checked      := (lkOpt in aOptions);
        end;
      lkLastTop := lkLastTop + lkCBX[i].Height;
      i := i + 1;  
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkCBX[7].Top + lkCBX[7].Height + 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_restoreoptions_pagesize;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    lkCbxPageSize := TComboBox.Create(lkForm);
    with lkCbxPageSize do
      begin
      Parent       := lkPanelClient;
      Ctl3d        := false;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style   := [fsBold];
      Font.Name    := 'Verdana';
      Font.Size    := DefaultFirebirdDialogEditFontHeight;
      Left         := lkImg.Left + lkImg.Width + 8;
      Width        := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
      Top          := lkLabel.Top + lkLabel.Height; 
      Height       := 20;
      Text         := '';
      Items.Clear;
      Items.Add('1024');
      Items.Add('2048');
      Items.Add('4096');
      Items.Add('8192');
      Items.Add('16384');
      case aPageSize of
        xps1024 : ItemIndex := 0;
        xps2048 : ItemIndex := 1;
        xps4096 : ItemIndex := 2;
        xps8192 : ItemIndex := 3;
        xps16384: ItemIndex := 4;
        end;
      Style        := csDropDownList;
      end;
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      aOptions := [];
      if(lkCBX[0].Checked)then aOptions := aOptions + [roDeactivateIndexes];
      if(lkCBX[1].Checked)then aOptions := aOptions + [roNoShadow];
      if(lkCBX[2].Checked)then aOptions := aOptions + [roNoValidityCheck];
      if(lkCBX[3].Checked)then aOptions := aOptions + [roOneRelationAtATime];
      if(lkCBX[4].Checked)then aOptions := aOptions + [roReplace];
      if(lkCBX[5].Checked)then aOptions := aOptions + [roCreateNewDB];
      if(lkCBX[6].Checked)then aOptions := aOptions + [roUseAllSpace];
      if(lkCBX[7].Checked)then aOptions := aOptions + [roValidationCheck];
      case lkCbxPageSize.ItemIndex of
        0: aPageSize := xps1024;
        1: aPageSize := xps2048;
        2: aPageSize := xps4096;
        3: aPageSize := xps8192;
        4: aPageSize := xps16384;
        end;
      end;
    lkForm.Free;
  end;
