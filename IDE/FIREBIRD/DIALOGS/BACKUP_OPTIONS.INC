{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/BACKUP_OPTIONS.INC}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/CUSTOM.INC}        {$I ./CUSTOM.INC}{$ENDIF}
  //================= PEAKTOP:IDE/FIREBIRD/DIALOGS/BACKUP_OPTIONS.INC ==========
  function FirebirdDialog_BackupOptions_Execute(var aOptions:TxFBBackupOptions):Boolean;
  var
    lkForm        :TForm;
    lkImg         :TImage;
    lkPanelClient :TxcGradientPanel;
    lkLastTop, i  :Integer;
    lkOpt         :TxFBBackupOption;
    lkCBX         :array[0..6]of TxcCheckBox;
    lkCapts       :array[0..6]of string;
  begin
    Result := false;
    lkCapts[0] := msg_firebird_dialog_backupoptions_items_000;
    lkCapts[1] := msg_firebird_dialog_backupoptions_items_001;
    lkCapts[2] := msg_firebird_dialog_backupoptions_items_002;
    lkCapts[3] := msg_firebird_dialog_backupoptions_items_003;
    lkCapts[4] := msg_firebird_dialog_backupoptions_items_004;
    lkCapts[5] := msg_firebird_dialog_backupoptions_items_005;
    lkCapts[6] := msg_firebird_dialog_backupoptions_items_006;
    lkForm := FirebirdDialog_Create(msg_firebird_dialog_backupoptions_caption, msg_firebird_dialog_button_caption_ok, msg_firebird_dialog_button_caption_cancel);
    lkPanelClient := TxcGradientPanel(lkForm.FindComponent('PanelClient'));
    lkImg := TImage(lkForm.FindComponent('ImageLogo'));
    lkLastTop := 8;
    i := 0;
    for lkOpt:=boIgnoreChecksums to boConvertExtTables do
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
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      aOptions := [];
      if(lkCBX[0].Checked)then aOptions := aOptions + [boIgnoreChecksums];
      if(lkCBX[1].Checked)then aOptions := aOptions + [boIgnoreLimbo];
      if(lkCBX[2].Checked)then aOptions := aOptions + [boMetadataOnly];
      if(lkCBX[3].Checked)then aOptions := aOptions + [boNoGarbageCollection];
      if(lkCBX[4].Checked)then aOptions := aOptions + [boOldMetadataDesc];
      if(lkCBX[5].Checked)then aOptions := aOptions + [boNonTransportable];
      if(lkCBX[6].Checked)then aOptions := aOptions + [boConvertExtTables];
      end;
    lkForm.Free;
  end;
