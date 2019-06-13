{$DEFINE PEAKTOP:IDE/ERP/DATABASE/CONNECT.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                    {$I PEAKTOP:GLOBAL_VARIABLES.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.2.INC}                        {$I PEAKTOP:OBJ/TLABEL.2.INC}                         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/PASSWORD_PROMT.INC} {$I PEAKTOP:IDE/FIREBIRD/DIALOGS/PASSWORD_PROMT.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SELECT.INC}{$I PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SELECT.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/EVENTS.INC}             {$I ../DBO/MENU/EVENTS.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}   {$I ../DBO/USERS/GLOBALVARIABLES.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/SET.INC}               {$I ../DBO/USERS/SET.INC}                             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/RIGHTS.INC}            {$I ../DBO/USERS/RIGHTS.INC}                          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/CONTROLSNAMES.INC}     {$I ../DBO/USERS/CONTROLSNAMES.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/PANELCLIENT_OBJNAMES.INC}        {$I ../PANELCLIENT_OBJNAMES.INC}                      {$ENDIF}
  //================= PEAKTOP:IDE/ERP/CONNECTTODATABASE.INC ====================
  procedure lblDataBase_OnDblClick(Sender :TObject);
  begin
    if ERP_User_HasRightsAdmin(GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)) then
      call('PEAKTOP:IDE/ERP/DBO/OPER/ATTACHMENTS.PS');
  end;
  //============================================================================
  procedure FBDataBase_BeforeDisconnect(Sender :TObject);
  var 
    lkCmp :TComponent;
    i     :Integer;
  begin
    ERP_EventsMenuMain_Free;  
    call('PEAKTOP:IDE/ERP/DBO/MENU/CLEAR_MAIN.PS');
    with Amunhotep do
      begin
      Title                 := 'AMUNHOTEP  '+IntToStrRoman(Trunc(Amunhotep.Version/1000));
      MainForm.Caption      := Title;
      MainForm.OnCloseQuery := nil;
      end;
    with Amunhotep.MainForm.TaskBar do
      begin
      Caption     := '';
      Alignment   := taRightJustify;
      ShowCaption := false;
      end;
    lkCmp := Amunhotep.MainForm.FindComponent(obj_name_erp_amunhotepmainform_lbldbpath);  
    if(lkCmp <> nil)then
      lkCmp.Free;  
    lkCmp := Amunhotep.MainForm.FindComponent(obj_name_erp_amunhotepmainform_lblfilial);  
    if(lkCmp <> nil)then
      lkCmp.Free;  
    for i:=Amunhotep.MainForm.ControlCount-1 downto 0 do
      begin
      if(  (Pos(ERP_POS_CONTROL_TOOLBAR    , Amunhotep.MainForm.Controls[i].Name) = 1)
         or(Pos(ERP_POS_CONTROL_TOPPLACEBAR, Amunhotep.MainForm.Controls[i].Name) = 1)
         or(Pos(ERP_POS_CONTROL_LEFTBAR    , Amunhotep.MainForm.Controls[i].Name) = 1)
         or(Pos(ERP_POS_CONTROL_LEFTPANEL  , Amunhotep.MainForm.Controls[i].Name) = 1)
      )then Amunhotep.MainForm.Controls[i].Free;
      end;  
  end;
  //============================================================================
  procedure FBDataBase_AfterDisconnect(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/PANELCLIENT.PS');
    with FBDataBase do
      begin  
      AfterConnect     := nil;
      BeforeDisconnect := nil;
      AfterDisconnect  := nil;
      end; 
  end;
  //============================================================================
  procedure FBDataBase_AfterConnect(Sender :TObject);
  var
    lkTr           :TxFBTransaction;
    lkQr           :TxFBQuery;
    lkUserName     :string; 
    lkUserPwd      :string;
    lkUserPwdInBase:string; 
    lkUsersList    :string;
    lkLangIds      :TStringList;
    lkLangNames    :TStringList;
    lkFilialIds    :TStringList;
    lkFilialNames  :TStringList;
    lkLang         :string;
    lkLangId       :string;
    lkFilial       :Boolean;
    lkFilialId     :string;
    lkFilialName   :string;
    lkStr          :string;
    lkCounter      :Integer;
    lkDataBaseGUID :string;
    lkLBL          :TLabel;
  {$IFNDEF ERP_AUTOLOGIN}
  label loop;
  {$ENDIF}
  begin
    lkLangIds     := TStringList.Create; lkLangIds.Clear;
    lkLangNames   := TStringList.Create; lkLangNames.Clear;
    lkFilialIds   := TStringList.Create; lkFilialIds.Clear;
    lkFilialNames := TStringList.Create; lkFilialNames.Clear;
    lkLang        := '';
    lkLangId      := '1000054';
    lkFilial      := False;
    lkFilialId    := '';
    lkFilialName  := '';
    {$IFNDEF ERP_AUTOLOGIN}
    lkUsersList := '';
    lkTr := TxFBTransaction.Create(nil);
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
      SQL.Text    := 'SELECT US.ID FROM TABL$_USERS US WHERE (US.FLAG_DELETE = 0) ORDER BY US.ID ';
      if not Active then Open;
      First;
      while not EOF do
        begin
        lkUsersList := lkUsersList + StrTrimAll(FieldByName('ID').AsString) + #13#10;
        Next;
        end;
      if Active then Close;
      SQL.Text    := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/LOAD_LOCAL.SQL');
      if not Active then Open;
      First;
      while not EOF do
        begin
        lkLangIds.Add  ( FieldByName('LANG_ID'  ).AsString );
        lkLangNames.Add( FieldByName('LANG_NAME').AsString );
        Next;
        end;
      if Active then Close;
      SQL.Text    := StringsLoadFromFile('PEAKTOP:IDE/ERP/DBO/SQL/LOAD_FILIALS.SQL');
      if not Active then Open;
      First;
      lkFilial := (FieldByName('FILIAS').AsInteger = 1);
      if Active then Close;
      if lkFilial then
        begin
        SQL.Text    := 'SELECT F.ID, F.NAME FROM TABL$R_FILIALS F WHERE (F.FLAG_DELETE = 0) ORDER BY F.ID ';
        if not Active then Open;
        while not EOF do
          begin
          lkFilialIds.Add  ( FieldByName('ID'  ).AsString );
          lkFilialNames.Add( FieldByName('NAME').AsString );
          Next;
          end;
        end;  
      end;
    if lkTr.InTransaction then lkTr.Commit;
    lkTr.Free;
    lkUserName := '';
    lkUserPwd  := '';
    lkCounter  := 0;
  loop:
    if not FirebirdDialog_PasswordPromtFilial_Execute(lkUsersList, lkLangNames.Text, lkFilialNames.Text, lkUserName, lkUserPwd, lkLang, lkFilialName)then
      begin
      if FBDataBase.Connected then
        FBDataBase.Close;
      lkLangIds.Free;
      lkLangNames.Free;  
      lkFilialIds.Free;
      lkFilialNames.Free;
      {$IFDEF ERP_OLD_STYLE_CONNECT}
      Amunhotep.Terminate;
      {$ENDIF}
      exit;
      end;
    lkLangId    := lkLangIds[ lkLangNames.IndexOf(lkLang) ];  
    if lkFilial then
      lkFilialId := lkFilialIds[ lkFilialNames.IndexOf(lkFilialName) ];  
    lkCounter := lkCounter + 1;  
    if not FBDataBase.Connected then 
      begin
      lkLangIds.Free;
      lkLangNames.Free;  
      lkFilialIds.Free;
      lkFilialNames.Free;
      exit;
      end;
    lkTr := TxFBTransaction.Create(nil);
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
      SQL.Text    := 'SELECT U.* FROM TABL$_USERS U WHERE (U.ID = '''+UpperCase(lkUserName)+''') ';
      if not Active then Open;
      FetchAll;
      if(not(RecordCount > 0))then
        begin
        if lkTr.InTransaction then lkTr.Commit;
        lkTr.Free;
        Dialogs.MessageDlg('Ќеверно указаны им€ пользовател€ или пароль !', mtError, [mbOk]);
        if(lkCounter < 3)then
          goto loop
        {$IFDEF ERP_OLD_STYLE_CONNECT}
         else
          begin
          lkLangIds.Free;
          lkLangNames.Free;  
          lkFilialIds.Free;
          lkFilialNames.Free;
          Amunhotep.Terminate;
          end
        {$ENDIF}
        ;  
        end;
      First;
      lkUserPwdInBase := FieldByName('PWD').AsString;
      end;
    if lkTr.InTransaction then lkTr.Commit;
    lkTr.Free;
    {$ELSE}
    lkUserName      := 'PEAKTOP';
    lkUserPwd       := '';
    lkUserPwdInBase := '';
    {$ENDIF}  
    if(lkUserPwd = lkUserPwdInBase)then
      begin
      SetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT , StrTrimAll(UpperCase(lkUserName)));
      ExecSQL(FBDataBase, 'EXECUTE BLOCK AS BEGIN RDB$SET_CONTEXT(''USER_SESSION'', '''+ERP_GLOBALVARIABLE_USER_CURRENT+''', '''+StrTrimAll(UpperCase(lkUserName))+'''); END ');

      SetGlobalVariable(ERP_GLOBALVARIABLE_USER_LOCAL   , lkLangId );
      ExecSQL(FBDataBase, 'EXECUTE BLOCK AS BEGIN RDB$SET_CONTEXT(''USER_SESSION'', '''+ERP_GLOBALVARIABLE_USER_LOCAL  +''', '''+lkLangId+'''); END ');

      if lkFilial then
        begin
        SetGlobalVariable(ERP_GLOBALVARIABLE_USER_FILIAL, lkFilialId );
        ExecSQL(FBDataBase, 'EXECUTE BLOCK AS BEGIN RDB$SET_CONTEXT(''USER_SESSION'', '''+ERP_GLOBALVARIABLE_USER_FILIAL  +''', '''+lkFilialId+'''); END ');
        end;
      {$IFDEF ERP_OLD_STYLE_CONNECT}
      call('DB:ONSTART.PS');
      {$ELSE}
      FBDataBase.AfterDisconnect := @FBDataBase_AfterDisconnect;
      call('PEAKTOP:IDE/ERP/PANELCLIENT.PS');            
      call('PEAKTOP:IDE/ERP/START/DEFAULT.PS');          
      call('DB:CONFIG/START/DEFAULT.PS');                
      call('PEAKTOP:IDE/ERP/DBO/OPER/RECENT_ONSTART.PS');
      {$ENDIF}
      end
    {$IFNDEF ERP_AUTOLOGIN}
     else
      begin
      Dialogs.MessageDlg('Ќеверно указаны им€ пользовател€ или пароль !', mtError, [mbOk]);
      if(lkCounter < 3)then
        goto loop 
      {$IFDEF ERP_OLD_STYLE_CONNECT}
       else
        begin
        lkLangIds.Free;
        lkLangNames.Free;  
        lkFilialIds.Free;
        lkFilialNames.Free;
        Amunhotep.Terminate;
        end;
      {$ENDIF}
      ;  
      end;
    {$ENDIF}
    lkLangIds.Free;
    lkLangNames.Free;  
    lkFilialIds.Free;
    lkFilialNames.Free;
  end;
  //============================================================================
  function ConnectToDataBaseInternal(const aDataBasePath, aDataBaseCodePage, aFBUserName, aFBUserPwd, aFBUserRole:string):Boolean;
  begin
    Result := false;
    DontAutoFree;
    with FBDataBase do
      begin  
      AfterConnect     := @FBDataBase_AfterConnect;
      BeforeDisconnect := @FBDataBase_BeforeDisconnect; 
      DatabaseName     := aDataBasePath;
      LoginPrompt      := false;
      with Params do
        begin
        Clear;
        Add('USER_NAME='+aFBUserName);
        Add('PASSWORD='+aFBUserPwd);
        if(aDataBaseCodePage <> '')then
          Add('LC_CTYPE='+aDataBaseCodePage)
         else
          Add('LC_CTYPE=WIN1251');
        if(aFBUserRole <> '')then
          Add('SQL_ROLE_NAME='+aFBUserRole);
        end
      try 
        Open; 
      except
        exit; 
      end;
      Result := Connected;
      end;
  end;
  //============================================================================
  function ConnectToDataBase:Boolean;
  var
    lkDataBasePath     :string;
    lkDataBaseCodePage :string;
    lkFBUserName       :string; 
    lkFBUserPwd        :string;
    lkFBUserRole       :string;
  begin
    Result := FirebirdDialog_DatabaseSelect_Execute(lkDataBasePath, lkDataBaseCodePage, lkFBUserName, lkFBUserRole, lkFBUserPwd);
    if not Result then {$IFDEF ERP_OLD_STYLE_CONNECT} Amunhotep.Terminate; {$ELSE} exit; {$ENDIF}
    Result := ConnectToDataBaseInternal(lkDataBasePath, lkDataBaseCodePage, lkFBUserName, lkFBUserPwd, lkFBUserRole);
  end;
  //============================================================================
  function ConnectToDataBaseByFileName(const aFileName:string):Boolean;
  var
    lkDataBasePath     :string;
    lkDataBaseCodePage :string;
    lkFBUserName       :string; 
    lkFBUserPwd        :string;
    lkFBUserRole       :string;
  begin
    lkFBUserName       := 'SYSDBA'; 
    lkFBUserPwd        := 'masterkey';
    lkFBUserRole       := '';
    lkDataBaseCodePage := 'WIN1251';
    lkDataBasePath     := aFileName;
    if(not ( (Pos('127.0.0.1',lkDataBasePath)=1) or (Pos('localhost',LowerCase(lkDataBasePath))=1) ) )then
      begin
      {$IFDEF FIREBIRD_PORT_3056} // for some configurations use non default port !
      lkDataBasePath := '127.0.0.1/3056:'+lkDataBasePath;
      {$ELSE}
      lkDataBasePath := '127.0.0.1:'+lkDataBasePath;
      {$ENDIF}
      end;
    Result := ConnectToDataBaseInternal(lkDataBasePath, lkDataBaseCodePage, lkFBUserName, lkFBUserPwd, lkFBUserRole);
  end;
  //============================================================================
  procedure DisconnectFromDataBase;
  var
    i :Integer;
  begin 
    i := 0;
    while(i < Amunhotep.MainForm.MDIChildCount)do
      begin
      if(not ObjectInheritsFrom(Amunhotep.MainForm.MDIChildren[i], 'TAmunhotepEditorForm'))then
        begin
        Amunhotep.MainForm.MDIChildren[i].Free;
        i := i - 1;
        end
       else
        begin
        if(Pos('DB:', TAmunhotepEditorForm(Amunhotep.MainForm.MDIChildren[i]).FileName) = 1)then
          begin
          Amunhotep.MainForm.MDIChildren[i].Free;
          i := i - 1;
          end;
        end;   
      i := i + 1;
      end;
    if FBDataBase.Connected then
      FBDataBase.Close;    
    Amunhotep.MainForm.OnCloseQuery := nil;
  end;
