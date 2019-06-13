{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/PASSWORD_PROMT.INC}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/CUSTOM.INC}  {$I ./CUSTOM.INC}{$ENDIF}
const //========== PEAKTOP:IDE/FIREBIRD/DIALOGS/PASSWORD_PROMT.INC =============
  msg_firebird_dialog_password_promt_caption   = 'Введите имя пользователя и пароль';
  msg_firebird_dialog_password_promt_username  = 'Пользователь / User';
  msg_firebird_dialog_password_promt_password  = 'Пароль / Password';
  msg_firebird_dialog_password_promt_lang      = 'Язык интерфейса / Language';
  msg_firebird_dialog_password_promt_filial    = 'Филиал / Department';
  msg_firebird_dialog_password_promt_login     = 'Войти / Login';
  msg_firebird_dialog_password_promt_cancel    = 'Отмена / Cancel';
  //============================================================================
  function FirebirdDialog_PasswordPromtFilial_Execute(const LastUsers, LastLang, LastFilial:string; var UserName, Password, Lang, Filial:string):Boolean;
  var
    lkForm        :TForm;
    lkImg         :TImage;
    lkPanelClient :TxcGradientPanel;
    lkLabel       :TLabel;
    lkCbxUser     :TComboBox;
    lkEdtPwd      :TEdit;
    lkCbxLang     :TComboBox;
    lkCbxFilial   :TComboBox;
  begin
    Result := false;
    lkForm        := FirebirdDialog_Create(msg_firebird_dialog_password_promt_caption, msg_firebird_dialog_button_caption_login, msg_firebird_dialog_button_caption_cancel);
    lkPanelClient := TxcGradientPanel(lkForm.FindComponent('PanelClient'));
    lkImg         := TImage(lkForm.FindComponent('ImageLogo'));
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := 8;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_password_promt_username;
      Font.Name   := 'Verdana';
      Font.Size   := DefaultFirebirdDialogLabelFontHeight;
      Font.Style  := [fsBold];
      end;
    lkCbxUser := TComboBox.Create(lkForm);
    with lkCbxUser do
      begin
      Parent     := lkPanelClient;
      Ctl3d      := false;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style := [fsBold];
      Font.Name  := 'Verdana';
      Font.Size  := DefaultFirebirdDialogEditFontHeight;
      Left       := lkImg.Left + lkImg.Width + 8;
      Width      := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
      Top        := lkLabel.Top + lkLabel.Height + 4; 
      Items.Text := LastUsers;
      Text       := UserName;
      end;
    lkLabel := TLabel.Create(lkForm);
    with lkLabel do
      begin
      Parent      := lkPanelClient;
      Left        := lkImg.Left + lkImg.Width;
      Top         := lkCbxUser.Top + lkCbxUser.Height + 4;
      Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
      Height      := 20; 
      Transparent := true;
      Caption     := msg_firebird_dialog_password_promt_password;
      Font.Name   := 'Verdana';
      Font.Size   := DefaultFirebirdDialogLabelFontHeight;
      Font.Style  := [fsBold];
      end;
    lkEdtPwd := TEdit.Create(lkForm);
    with lkEdtPwd do
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
      Top          := lkLabel.Top + lkLabel.Height + 4; 
      Text         := Password;
      PasswordChar := '*';
      end;
    if(StrTrimAll(LastLang) <> '')then
      begin
      lkLabel := TLabel.Create(lkForm);
      with lkLabel do
        begin
        Parent      := lkPanelClient;
        Left        := lkImg.Left + lkImg.Width;
        Top         := lkEdtPwd.Top + lkEdtPwd.Height + 4;
        Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
        Height      := 20; 
        Transparent := true;
        Caption     := msg_firebird_dialog_password_promt_lang;
        Font.Name   := 'Verdana';
        Font.Size   := DefaultFirebirdDialogLabelFontHeight;
        Font.Style  := [fsBold];
        end;
      lkCbxLang := TComboBox.Create(lkForm);
      with lkCbxLang do
        begin
        Parent     := lkPanelClient;
        Ctl3d      := false;
        Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
        Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
        Font.Style := [fsBold];
        Font.Name  := 'Verdana';
        Font.Size  := DefaultFirebirdDialogEditFontHeight;
        Left       := lkImg.Left + lkImg.Width + 8;
        Width      := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
        Top        := lkLabel.Top + lkLabel.Height + 4; 
        Style      := csDropDownList;
        Items.Text := LastLang;
        ItemIndex  := 0;
        Enabled    := (Items.Count > 1);
        end;
      end;  
    if(StrTrimAll(LastFilial) <> '')then
      begin
      lkLabel := TLabel.Create(lkForm);
      with lkLabel do
        begin
        Parent      := lkPanelClient;
        Left        := lkImg.Left + lkImg.Width;
        Top         := lkCbxLang.Top + lkCbxLang.Height + 4;
        Width       := lkForm.Width - (lkImg.Left + lkImg.Width + 4);
        Height      := 20; 
        Transparent := true;
        Caption     := msg_firebird_dialog_password_promt_filial;
        Font.Name   := 'Verdana';
        Font.Size   := DefaultFirebirdDialogLabelFontHeight;
        Font.Style  := [fsBold];
        end;
      lkCbxFilial := TComboBox.Create(lkForm);
      with lkCbxFilial do
        begin
        Parent     := lkPanelClient;
        Ctl3d      := false;
        Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
        Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
        Font.Style := [fsBold];
        Font.Name  := 'Verdana';
        Font.Size  := DefaultFirebirdDialogEditFontHeight;
        Left       := lkImg.Left + lkImg.Width + 8;
        Width      := lkForm.Width - (lkImg.Left + lkImg.Width + 16);
        Top        := lkLabel.Top + lkLabel.Height + 4; 
        Style      := csDropDownList;
        Items.Text := LastFilial;
        ItemIndex  := 0;
        Enabled    := (Items.Count > 1);
        end;
      end;  
    lkForm.ActiveControl := lkCbxUser;   
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      UserName := lkCbxUser.Text;
      Password := lkEdtPwd.Text;
      if(StrTrimAll(LastLang)   <> '')then Lang   := lkCbxLang.Text;
      if(StrTrimAll(LastFilial) <> '')then Filial := lkCbxFilial.Text;
      end;
    lkForm.Free;
  end;
  //============================================================================
  function FirebirdDialog_PasswordPromtLocal_Execute(const LastUsers, LastLang:string; var UserName, Password, Lang:string):Boolean;
  var
    LFilial:string;
  begin
    LFilial := '';
    Result := FirebirdDialog_PasswordPromtFilial_Execute(LastUsers, LastLang, '', UserName, Password, Lang, LFilial); 
  end;
  //============================================================================
  function FirebirdDialog_PasswordPromt_Execute(const LastUsers:string; var UserName, Password:string):Boolean;
  var
    LLang:string;
  begin
    LLang := '';
    Result := FirebirdDialog_PasswordPromtLocal_Execute(LastUsers, '', UserName, Password, LLang);  
  end;  
