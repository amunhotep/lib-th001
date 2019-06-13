{$DEFINE PEAKTOP:IDE/DEVELOPMENT/EDITOR/LNGPASCAL/MESSAGES.INC}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                 {$I PEAKTOP:OBJ/TXCTABSHEET.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}      {$I PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/EDITOR/OBJNAMES.INC} {$I ../OBJNAMES.INC}                         {$ENDIF}
  //=========== PEAKTOP:IDE/DEVELOPMENT/EDITOR/LNGPASCAL/MESSAGES.INC ==========
  procedure Editor_PageMessages_ListView_OnDblClick(Sender :TObject);
  var
    lkLI :TListItem;
    lkPC :TxcPageControlEx;
    aCol :Integer; 
    aRow :Integer;
  begin
    with TListView(Sender) do
      begin
      lkLI := Items[ItemIndex];
      aRow := StrToInt(lkLI.SubItems[2]);
      aCol := StrToInt(lkLI.SubItems[3]);
      lkPC := TxcPageControlEx(TListView(Sender).Owner.FindComponent(editor_obj_name_page_control));
      with TSynEdit(Owner.FindComponent(editor_obj_name_synedit_preprocess)) do
        begin
        CaretX := aCol;
        CaretY := aRow;
        TopLine:= aRow;
        lkPC.ActivePageIndex := 2;
        SetFocus;
        end;
      end;
  end;
  //============================================================================
  procedure Editor_PageMessages_Create(aOwnerForm :TAmunhotepEditorForm);
  var
    lkPageControl :TxcPageControlEx;
    lkTabSheet    :TxcTabSheet;
    lkListView    :TListView;
    lkSynEdit     :TSynEdit;
  begin
    lkPageControl := TxcPageControlEx(aOwnerForm.FindComponent(editor_obj_name_page_control));
    lkTabSheet := CreateTxcTabSheet(lkPageControl, 'tsMessages', 'Messages', 150, Amunhotep.MainForm.StyleManager.Colors.Window);
    lkListView := TListView.Create(aOwnerForm);
    with lkListView do
      begin
      Name          := editor_obj_name_listview_messages;
      Parent        := lkTabSheet;
      Align         := alClient;
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Name     := 'Tahoma';
      Font.Size     := 7;
      Font.Style    := [fsBold];
      Ctl3D         := false;
      HideSelection := false; 
      MultiSelect   := false; 
      RowSelect     := true;
      ReadOnly      := true;
      ViewStyle     := vsReport;
      OnDblClick    := @Editor_PageMessages_ListView_OnDblClick;
      Columns.Clear;
      with Columns.Add do
        begin
        Caption := 'Type';
        Width   := 80;
        end;
      with Columns.Add do
        begin
        Caption := 'Message';
        Width   := 520;
        end;
      with Columns.Add do
        begin
        Caption := 'Module';
        Width   := 380;
        end;
      with Columns.Add do
        begin
        Caption := 'Row';
        Width   := 48;
        end;
      with Columns.Add do
        begin
        Caption := 'Column';
        Width   := 48;
        end;
      Items.Clear; 
      with Items.Add do
        begin
        Caption := '';
        SubItems.Clear;
        SubItems.Add('');
        SubItems.Add('');
        SubItems.Add('0000');
        SubItems.Add('0000');
        end;
      ItemIndex := 0;
      end;
    lkTabSheet := CreateTxcTabSheet(lkPageControl, 'tsMessagesText', 'Messages text', 291, Amunhotep.MainForm.StyleManager.Colors.Foreground);
    lkSynEdit := Interface_SynEdit_Create(aOwnerForm, lkTabSheet, editor_obj_name_synedit_messages);
    RegisterSynEdit(lkSynEdit, ftText);
  end;
