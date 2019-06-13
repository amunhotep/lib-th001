{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SETTINGS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}               {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/CUSTOM.INC}    {$I ./CUSTOM.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/$SETTINGS.INC} {$I ./$SETTINGS.INC}               {$ENDIF}
  //========= PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SETTINGS.INC ===============
  procedure FirebirdDialog_DatabaseSettings_cbServParams_OnClick(Sender :TObject);
  var
    lkOwner   :TComponent;
    lkVisible :Boolean;
  begin
    lkOwner := TComponent(Sender).Owner;
    if(lkOwner = nil)then exit;
    lkVisible := TxcCheckBox(Sender).Visible and (not TxcCheckBox(Sender).Checked);
    TControl(lkOwner.FindComponent('edtUserName') ).Visible := lkVisible;     
    TControl(lkOwner.FindComponent('edtUserPwd')  ).Visible := lkVisible;     
    TControl(lkOwner.FindComponent('edtUserRole') ).Visible := lkVisible;     
    TControl(lkOwner.FindComponent('lblUserName') ).Visible := lkVisible;     
    TControl(lkOwner.FindComponent('lblUserPwd')  ).Visible := lkVisible;     
    TControl(lkOwner.FindComponent('lblUserRole') ).Visible := lkVisible;     
  end;  
  //============================================================================
  procedure FirebirdDialog_DatabaseSettings_cbLoginPropt_OnClick(Sender :TObject);
  var
    lkOwner :TComponent;
  begin
    lkOwner := TComponent(Sender).Owner;
    if(lkOwner = nil)then exit;
    TControl(lkOwner.FindComponent('cbServParams')).Visible := not TxcCheckBox(Sender).Checked;
    FirebirdDialog_DatabaseSettings_cbServParams_OnClick(lkOwner.FindComponent('cbServParams'));     
  end;
  //============================================================================
  procedure FirebirdDialog_DatabaseSettings_EditDBFN_OnButtonClick(Sender :TObject);
  var
    lkFileName :string;
    lkEdtAlias :TEdit;
  begin
    lkFileName := TxcEditCombo(Sender).Text;
    if(PromptForFileName(lkFileName, msg_firebird_dialog_database_settings_filefilter, 'FDB', msg_firebird_dialog_database_settings_dbpath2, '', false))then
      begin
      TxcEditCombo(Sender).Text := lkFileName;
      lkEdtAlias := TEdit(TComponent(Sender).Owner.FindComponent('edtAlias'));
      if(lkEdtAlias <> nil)then
        if(StrTrimAll(lkEdtAlias.Text) = '')then
          lkEdtAlias.Text := lkFileName;
      end;
  end;
  //============================================================================
  function FirebirdDialog_DatabaseSettings_Execute(var aAliasName, aDataBaseFileName, 
             aDataBaseCodePage, aFirebirdUserName, aFirebirdUserRole, aFirebirdUserPassword :string; 
             var aLoginPrompt, aLoginWithServerParams:Boolean):Boolean;
  var
    lkForm        :TForm;
    lkImg         :TImage;
    lkPanelClient :TxcGradientPanel;
    lkLabel       :TLabel;
    lkEdtAlias    :TEdit;
    lkEdtDBFN     :TxcEditCombo;
    lkCbxCodePage :TComboBox;
    lkCbLoginPropt:TxcCheckBox;
    lkCbServParams:TxcCheckBox;
    lkEdtUserName :TEdit;
    lkEdtUserPwd  :TEdit;
    lkEdtUserRole :TEdit;
  begin
    Result := false;
    lkForm        := FirebirdDialog_Create(msg_firebird_dialog_database_settings_caption, msg_firebird_dialog_button_caption_ok, msg_firebird_dialog_button_caption_cancel);
    lkForm.Height := DefaultFirebirdDialogDBSettingsHeight;  
    lkPanelClient := TxcGradientPanel(lkForm.FindComponent('PanelClient'));
    lkImg         := TImage(lkForm.FindComponent('ImageLogo'));
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_database_settings_alias;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    lkEdtAlias := TEdit.Create(lkForm);
    with lkEdtAlias do
      begin
      Name         := 'edtAlias';
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
      Text         := aAliasName;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkEdtAlias.Top + lkEdtAlias.Height + 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_database_settings_dbpath;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    lkEdtDBFN := TxcEditCombo.Create(lkForm);
    with lkEdtDBFN do
      begin
      Parent       := lkPanelClient;
      Ctl3d        := false;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style   := [fsBold];
      Font.Name    := 'Verdana';
      Font.Size    := DefaultFirebirdDialogEditFontHeight;
      GlyphKind    := gkEllipsis;
      Left         := lkImg.Left + lkImg.Width + 8;
      Width        := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
      Top          := lkLabel.Top + lkLabel.Height; 
      Height       := 20;
      Text         := aDataBaseFileName;
      OnButtonClick:= @FirebirdDialog_DatabaseSettings_EditDBFN_OnButtonClick;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkEdtDBFN.Top + lkEdtDBFN.Height + 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_database_settings_codepage;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    if(StrTrimAll(aDataBaseCodePage) = '')then aDataBaseCodePage := 'WIN1251';
    aDataBaseCodePage := UpperCase(aDataBaseCodePage);  
    lkCbxCodePage := TComboBox.Create(lkForm);
    with lkCbxCodePage do
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
      Items.Text   := StringsLoadFromFile(PrepareAbsoleteFileName('PEAKTOP:IDE/FIREBIRD/CHARACTERSETS.TXT'));
      if(Items.Count > 0)then
        begin
        ItemIndex := Items.IndexOf(aDataBaseCodePage);
        Style     := csDropDownList;
        end;
      end;
    lkCbLoginPropt := TxcCheckBox.Create(lkForm);
    with lkCbLoginPropt do
      begin
      Name         := 'cbLoginPropt';
      Parent       := lkPanelClient;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Font.Size    := DefaultFirebirdDialogLabelFontHeight;
      Font.Style   := [fsBold];
      Left         := lkImg.Left + lkImg.Width + 8;
      Width        := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
      Top          := lkCbxCodePage.Top + lkCbxCodePage.Height + 4; 
      Height       := 20;
      Caption      := msg_firebird_dialog_database_settings_loginpromt;
      Checked      := aLoginPrompt;
      OnClick      := @FirebirdDialog_DatabaseSettings_cbLoginPropt_OnClick;
      end;
    lkCbServParams := TxcCheckBox.Create(lkForm);
    with lkCbServParams do
      begin
      Name         := 'cbServParams';
      Parent       := lkPanelClient;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Font.Size    := DefaultFirebirdDialogLabelFontHeight;
      Font.Style   := [fsBold];
      Left         := lkImg.Left + lkImg.Width + 8;
      Width        := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
      Top          := lkCbLoginPropt.Top + lkCbLoginPropt.Height; 
      Height       := 20;
      Caption      := msg_firebird_dialog_database_settings_servparams;
      Checked      := aLoginWithServerParams;
      OnClick      := @FirebirdDialog_DatabaseSettings_cbServParams_OnClick;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Name        := 'lblUserName';
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkCbServParams.Top + lkCbServParams.Height + 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_database_settings_username;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    lkEdtUserName := TEdit.Create(lkForm);
    with lkEdtUserName do
      begin
      Name         := 'edtUserName';
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
      Text         := aFirebirdUserName;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Name        := 'lblUserPwd';
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkEdtUserName.Top + lkEdtUserName.Height + 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_database_settings_userpwd;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    lkEdtUserPwd := TEdit.Create(lkForm);
    with lkEdtUserPwd do
      begin
      Name         := 'edtUserPwd';
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
      Text         := aFirebirdUserPassword;
      PasswordChar := '*';
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Name        := 'lblUserRole';
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkEdtUserPwd.Top + lkEdtUserPwd.Height + 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_database_settings_userrole;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    lkEdtUserRole := TEdit.Create(lkForm);
    with lkEdtUserRole do
      begin
      Name         := 'edtUserRole';
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
      Text         := aFirebirdUserRole;
      end;
    FirebirdDialog_DatabaseSettings_cbLoginPropt_OnClick(lkCbLoginPropt); // setting visible elements !!!
    lkForm.ActiveControl := lkEdtAlias;   
    if(lkForm.ShowModal = mrOk)then
      begin
      aAliasName             := lkEdtAlias.Text;
      aDataBaseFileName      := lkEdtDBFN.Text;
      aDataBaseCodePage      := lkCbxCodePage.Items[lkCbxCodePage.ItemIndex];
      aLoginPrompt           := lkCbLoginPropt.Checked;
      if(aLoginPrompt)then
        begin
        aLoginWithServerParams := false;
        aFirebirdUserName      := '';
        aFirebirdUserPassword  := '';
        aFirebirdUserRole      := '';
        end
       else
        begin 
        aLoginWithServerParams := lkCbServParams.Checked;
        if(aLoginWithServerParams)then
          begin
          aFirebirdUserName      := '';
          aFirebirdUserPassword  := '';
          aFirebirdUserRole      := '';
          end
         else
          begin 
          aFirebirdUserName      := lkEdtUserName.Text;
          aFirebirdUserPassword  := lkEdtUserPwd.Text;
          aFirebirdUserRole      := lkEdtUserRole.Text;
          end;
        end;
      Result := true;
      end;
    lkForm.Free;
  end;
