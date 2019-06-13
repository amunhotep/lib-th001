{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/SERVER_SETTINGS.INC}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/CUSTOM.INC}          {$I ./CUSTOM.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/$SETTINGS.INC}       {$I ./$SETTINGS.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/BACKUP_OPTIONS.INC}  {$I ./BACKUP_OPTIONS.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/RESTORE_OPTIONS.INC} {$I ./RESTORE_OPTIONS.INC} {$ENDIF}
var 
  FirebirdDialog_ServerSettings_BackupOptions   :TxFBBackupOptions; 
  FirebirdDialog_ServerSettings_RestoreOptions  :TxFBRestoreOptions;
  FirebirdDialog_ServerSettings_RestorePageSize :TxsRestorePageSize;  
  //============================================================================
  procedure FirebirdDialog_ServerSettings_btnBackup_OnClick(Sender :TObject);
  var
    lkOpt :TxFBBackupOptions;
  begin
    lkOpt := FirebirdDialog_ServerSettings_BackupOptions;
    if FirebirdDialog_BackupOptions_Execute(lkOpt)then
      FirebirdDialog_ServerSettings_BackupOptions := lkOpt;
  end;
  //============================================================================
  procedure FirebirdDialog_ServerSettings_btnRestore_OnClick(Sender :TObject);
  begin
    FirebirdDialog_RestoreOptions_Execute(
      FirebirdDialog_ServerSettings_RestoreOptions, 
      FirebirdDialog_ServerSettings_RestorePageSize
    );
  end;
  //============================================================================
  procedure FirebirdDialog_ServerSettings_cbAutoConnect_OnClick(Sender :TObject);
  var
    lkOwner   :TComponent;
  begin
    lkOwner := TComponent(Sender).Owner;
    if(lkOwner = nil)then exit;
    TControl(lkOwner.FindComponent('edtUserName') ).Visible := TxcCheckBox(Sender).Checked;     
    TControl(lkOwner.FindComponent('edtUserPwd')  ).Visible := TxcCheckBox(Sender).Checked;     
    TControl(lkOwner.FindComponent('edtUserRole') ).Visible := TxcCheckBox(Sender).Checked;     
    TControl(lkOwner.FindComponent('lblUserName') ).Visible := TxcCheckBox(Sender).Checked;     
    TControl(lkOwner.FindComponent('lblUserPwd')  ).Visible := TxcCheckBox(Sender).Checked;     
    TControl(lkOwner.FindComponent('lblUserRole') ).Visible := TxcCheckBox(Sender).Checked;     
  end;  
  //============================================================================
  function FirebirdDialog_ServerSettings_Execute(var aServerName, aServerIP, 
             aDefaultCodePage, aFirebirdUserName, aFirebirdUserRole, aFirebirdUserPassword :string;
             var aAutoConnect:Boolean; 
             var aBackupOptions :TxFBBackupOptions; var aRestoreOptions :TxFBRestoreOptions;
             var aRestorePageSize:TxsRestorePageSize):Boolean;
  var
    lkForm         :TForm;
    lkImg          :TImage;
    lkPanelClient  :TxcGradientPanel;
    lkLabel        :TLabel;
    lkEdtServerName:TEdit;
    lkEdtServerIP  :TEdit;
    lkCbxCodePage  :TComboBox;
    lkCbAutoConnect:TxcCheckBox;
    lkEdtUserName  :TEdit;
    lkEdtUserPwd   :TEdit;
    lkEdtUserRole  :TEdit;
    lkBtnBackup    :TxcButton;
    lkBtnRestore   :TxcButton;
  begin
    Result := false;
    lkForm        := FirebirdDialog_Create(msg_firebird_dialog_server_settings_caption, msg_firebird_dialog_button_caption_ok, msg_firebird_dialog_button_caption_cancel);
    lkPanelClient := TxcGradientPanel(lkForm.FindComponent('PanelClient'));
    lkImg         := TImage(lkForm.FindComponent('ImageLogo'));
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      AutoSize    := false;
      Left        := lkImg.Left + lkImg.Width;
      Top         := 4;
      Width       := DefaultFirebirdDialogLabelWidth;
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_server_settings_servername;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    lkEdtServerName := TEdit.Create(lkForm);
    with lkEdtServerName do
      begin
      Name         := 'edtServerName';
      Parent       := lkPanelClient;
      Ctl3d        := false;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style   := [fsBold];
      Font.Name    := 'Verdana';
      Font.Size    := DefaultFirebirdDialogEditFontHeight;
      Left         := lkLabel.Left + lkLabel.Width + 8;
      Width        := lkForm.Width - (lkLabel.Left + lkLabel.Width + 16);
      Top          := lkLabel.Top; 
      Height       := lkLabel.Height;
      Text         := aServerName;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      AutoSize    := false;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkEdtServerName.Top + lkEdtServerName.Height + 4;
      Width       := DefaultFirebirdDialogLabelWidth;
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_server_settings_serverip;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    lkEdtServerIP := TEdit.Create(lkForm);
    with lkEdtServerIP do
      begin
      Name         := 'edtServerIP';
      Parent       := lkPanelClient;
      Ctl3d        := false;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style   := [fsBold];
      Font.Name    := 'Verdana';
      Font.Size    := DefaultFirebirdDialogEditFontHeight;
      Left         := lkLabel.Left + lkLabel.Width + 8;
      Width        := lkForm.Width - (lkLabel.Left + lkLabel.Width + 16);
      Top          := lkLabel.Top; 
      Height       := lkLabel.Height;
      Text         := aServerIP;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      AutoSize    := false;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkEdtServerIP.Top + lkEdtServerIP.Height + 4;
      Width       := DefaultFirebirdDialogLabelWidth;
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_server_settings_codepage;
      Font.Name   := 'Verdana';
      Font.Size   := 7;
      Font.Style  := [fsBold];
      end;
    if(StrTrimAll(aDefaultCodePage) = '')then aDefaultCodePage := 'WIN1251';
    aDefaultCodePage := UpperCase(aDefaultCodePage);  
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
      Left         := lkLabel.Left + lkLabel.Width + 8;
      Width        := lkForm.Width - (lkLabel.Left + lkLabel.Width + 16);
      Top          := lkLabel.Top; 
      Height       := lkLabel.Height;
      Text         := '';
      Items.Text   := StringsLoadFromFile(StrAbsolutePath('./IDE/FIREBIRD/CHARACTERSETS.TXT', Amunhotep.SourcePath));
      if(Items.Count > 0)then
        begin
        ItemIndex := Items.IndexOf(aDefaultCodePage);
        Style     := csDropDownList;
        end;
      end;
    lkCbAutoConnect := TxcCheckBox.Create(lkForm);
    with lkCbAutoConnect do
      begin
      Name         := 'cbAutoConnect';
      Parent       := lkPanelClient;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Font.Size    := DefaultFirebirdDialogLabelFontHeight;
      Font.Style   := [fsBold];
      Left         := lkImg.Left + lkImg.Width + 8;
      Width        := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
      Top          := lkCbxCodePage.Top + lkCbxCodePage.Height + 4; 
      Height       := 20;
      Caption      := msg_firebird_dialog_server_settings_autoconnect;
      Checked      := aAutoConnect;
      OnClick      := @FirebirdDialog_ServerSettings_cbAutoConnect_OnClick;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Name        := 'lblUserName';
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkCbAutoConnect.Top + lkCbAutoConnect.Height + 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_server_settings_username;
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
      Caption     := msg_firebird_dialog_server_settings_userpwd;
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
      Caption     := msg_firebird_dialog_server_settings_userrole;
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
    lkBtnBackup := TxcButton.Create(lkForm);
    with lkBtnBackup do
      begin
      Name         := 'btnBackup';
      Parent       := lkPanelClient;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style   := [fsBold];
      Font.Name    := 'Verdana';
      Font.Size    := DefaultFirebirdDialogButtonFontHeight;
      Left         := lkImg.Left + lkImg.Width + 8;
      Width        := DefaultFirebirdDialogButtonEtcWidth;
      Top          := lkEdtUserRole.Top + lkEdtUserRole.Height + 4; 
      Height       := 20;
      Caption      := msg_firebird_dialog_server_settings_backup_opt;
      Hint         := msg_firebird_dialog_server_settings_backup_opt_hint;
      ShowHint     := true;
      OnClick      := @FirebirdDialog_ServerSettings_btnBackup_OnClick;
      end;
    lkBtnRestore := TxcButton.Create(lkForm);
    with lkBtnRestore do
      begin
      Name         := 'btnRestore';
      Parent       := lkPanelClient;
      StyleManager := Amunhotep.MainForm.StyleManager;
      Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style   := [fsBold];
      Font.Name    := 'Verdana';
      Font.Size    := DefaultFirebirdDialogButtonFontHeight;
      Left         := lkBtnBackup.Left + lkBtnBackup.Width + 8;
      Width        := DefaultFirebirdDialogButtonEtcWidth;
      Top          := lkBtnBackup.Top; 
      Height       := lkBtnBackup.Height;
      Caption      := msg_firebird_dialog_server_settings_restore_opt;
      Hint         := msg_firebird_dialog_server_settings_restore_opt_hint;
      ShowHint     := true;
      OnClick      := @FirebirdDialog_ServerSettings_btnRestore_OnClick;
      end;
    FirebirdDialog_ServerSettings_BackupOptions   := aBackupOptions;
    FirebirdDialog_ServerSettings_RestoreOptions  := aRestoreOptions;
    FirebirdDialog_ServerSettings_RestorePageSize := aRestorePageSize;  
    FirebirdDialog_ServerSettings_cbAutoConnect_OnClick(lkCbAutoConnect);
    lkForm.ActiveControl := lkEdtServerName;   
    if(lkForm.ShowModal = mrOk)then
      begin
      aServerName           := lkEdtServerName.Text;
      aServerIP             := lkEdtServerIP.Text;
      aDefaultCodePage      := lkCbxCodePage.Text;
      aAutoConnect          := lkCbAutoConnect.Checked;
      aFirebirdUserName     := lkEdtUserName.Text;
      aFirebirdUserPassword := lkEdtUserPwd.Text;
      aFirebirdUserRole     := lkEdtUserRole.Text;
      aBackupOptions        := FirebirdDialog_ServerSettings_BackupOptions;
      aRestoreOptions       := FirebirdDialog_ServerSettings_RestoreOptions;
      aRestorePageSize      := FirebirdDialog_ServerSettings_RestorePageSize;  
      Result := true;
      end;
    lkForm.Free;
  end;
