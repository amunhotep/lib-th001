{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/IMAGELISTDLG.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}       {$I ../$COMMON/FORMERP.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}  {$I ../$COMMON/FORMERP_LANG.INC}             {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/OPER/IMAGELISTDLG.INC ==================
  procedure Amunhotep_ImageListDialog_ListView_OnDblClick(Sender :TObject);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  function Amunhotep_ImageListDialog_Execute(aImageList:TCustomImageList; var aImageIndex:Integer):Boolean;
  var
    lkFrm :TForm;
    lkLV  :TListView;
    i     :Integer;
  begin
    Result := false;
    lkFrm := TERPForm_Create(msg_erp_column_selectimageid, StrAbsolutePath('../conf/icons/bmp.ico',Amunhotep.ExeName), PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/MIME/BMP0032X0032.BMP'),true, nil);
    with lkFrm do
      begin
      Width  := Trunc(Screen.Width  * 2 / 3);
      Height := Trunc(Screen.Height * 2 / 3);
      end;
    lkLV  := TListView.Create(lkFrm);
    with lkLV do
      begin
      Parent      := lkFrm;
      Ctl3D       := false;
      Align       := alClient;
      Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color  := Amunhotep.MainForm.StyleManager.Colors.Border;
      SmallImages := aImageList;
      ViewStyle   := vsList;
      OnDblClick  := @Amunhotep_ImageListDialog_ListView_OnDblClick;
      Items.Clear;
      with Items.Add do
        begin
        Caption    := 'нет';
        ImageIndex := -1;
        if(aImageIndex = -1)then
          Selected := true;
        end;
      for i:=0 to aImageList.Count-1 do
        with Items.Add do
          begin
          Caption := FormatFloat('0000', i);
          ImageIndex := i;
          if(aImageIndex = i)then
            Selected := true;
          end;
      end;
    Result := (lkFrm.ShowModal = mrOk);
    if Result then
      aImageIndex := lkLV.Items[lkLV.ItemIndex].ImageIndex;
    lkFrm.Free;  
  end;
