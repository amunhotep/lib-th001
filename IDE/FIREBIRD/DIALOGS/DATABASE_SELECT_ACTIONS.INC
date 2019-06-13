{$DEFINE PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SELECT_ACTIONS.INC}
{$IFNDEF PEAKTOP:SYSUTILS/FILES/SEARCH_UTILS.INC}           {$I PEAKTOP:SYSUTILS/FILES/SEARCH_UTILS.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/SERVER_SETTINGS.INC}  {$I ./SERVER_SETTINGS.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SETTINGS.INC}{$I ./DATABASE_SETTINGS.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/FIREBIRD/DIALOGS/LANG.INC}             {$I ./LANG.INC}             {$ENDIF}
  //======= PEAKTOP:IDE/FIREBIRD/DIALOGS/DATABASE_SELECT_ACTIONS.INC ===========
  procedure FirebirdDialog_DatabaseSelect_FillCategories(aFileConfig :TxFBFileConfig; aCBTNS :TCategoryButtons);
  var
    i, j, k, l :Integer;
    lkSearchPath :string;
    lkSL       :TStringList;
    lkFlagDev  :Boolean;
    lkFlag     :Boolean;
    lkTr       :TxFBTransaction;
    lkQr       :TxFBQuery;
  begin
    lkSearchPath := 'd:\db\firebird';
    aCBTNS.Categories.Clear;
{
    lkFlagDev := FileExists(StrAbsolutePath('../conf/amunhotep-peaktop.conf', Amunhotep.ExeName));
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '127.0.0.1/3050')then
        lkFlag := false;
    if( (aFileConfig.Servers.Count = 0) or lkFlag )then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '127.0.0.1/3050';
        ServerName      := '127_000_000_001_3050';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.129/3056')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.129/3056';
        ServerName      := '192_168_001_129_3056';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.210/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.210/3050';
        ServerName      := '192_168_001_210_3050';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.150/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.150/3050';
        ServerName      := '192_168_001_150_3050 - Отделение00';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.149/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.149/3050';
        ServerName      := '192_168_001_149_3050 - Отделение01';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.154/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.154/3050';
        ServerName      := '192_168_001_154_3050 - Отделение02';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.153/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.153/3050';
        ServerName      := '192_168_001_153_3050 - Отделение03';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '193.106.201.154/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '193.106.201.154/3050';
        ServerName      := '193_106_201_154_3050 - Отделение04';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.151/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.151/3050';
        ServerName      := '192_168_001_151_3050 - Отделение05';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '193.106.201.136/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '193.106.201.136/3050';
        ServerName      := '193_106_201_136_3050 - Отделение06';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.157/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.157/3050';
        ServerName      := '192_168_001_157_3050 - Отделение07';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '193.110.112.165/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '193.110.112.165/3050';
        ServerName      := '193_110_112_165_3050 - Отделение08';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '193.110.113.194/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '193.110.113.194/3050';
        ServerName      := '193_110_113_194_3050 - Отделение09';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.163/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.163/3050';
        ServerName      := '192_168_001_163_3050 - Отделение10';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.164/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.164/3050';
        ServerName      := '192_168_001_164_3050 - Отделение11';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.155/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.155/3050';
        ServerName      := '192_168_001_155_3050 - Отделение12';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
    lkFlag    := lkFlagDev;
    for i:=0 to aFileConfig.Servers.Count-1 do
      if(aFileConfig.Servers[i].ServerIP = '192.168.1.159/3050')then
        lkFlag := false;
    if lkFlag then
      with aFileConfig.Servers.Add do
        begin
        AutoConnect     := true;
        BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
        RestorePageSize := xps8192;
        RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
        ServerIP        := '192.168.1.159/3050';
        ServerName      := '192_168_001_159_3050 - Магазин01';
        ServerProtocol  := prtTCP;
        CodePage        := 'WIN1251';
        UserName        := 'SYSDBA';
        UserPassword    := 'masterkey';
        UserRole        := '';
        end;
}
{
    if(FBDataBase.Connected and lkFlagDev)then
      begin
      lkFlag := true;
      for i:=0 to aFileConfig.Servers.Count-1 do
        if(aFileConfig.Servers[i].ServerIP = Copy(FBDataBase.DataBaseName, 1, Pos(':',FBDataBase.DataBaseName)-1) )then
          begin
          lkFlag := false;
          break;
          end;
      if lkFlag then    
        with aFileConfig.Servers.Add do
          begin
          AutoConnect     := true;
          BackupOptions   := [boIgnoreChecksums, boIgnoreLimbo, boOldMetadataDesc, boNonTransportable, boConvertExtTables];
          RestorePageSize := xps8192;
          RestoreOptions  := [roNoShadow, roNoValidityCheck, roOneRelationAtATime, roCreateNewDB, roUseAllSpace];
          ServerIP        := Copy(FBDataBase.DataBaseName, 1, Pos(':',FBDataBase.DataBaseName)-1);
          ServerName      := StrReplaceStr(ServerIP, '.', '_');
          ServerProtocol  := prtTCP;
          CodePage        := 'WIN1251';
          UserName        := 'SYSDBA';
          UserPassword    := 'masterkey';
          UserRole        := '';
          end;
      end;    
}
    for i:=0 to aFileConfig.Servers.Count-1 do
      begin  
      with aCBTNS.Categories.Add do
        begin 
        {$IFDEF AMUNHOTEP4468}
        ImageIndex    := 0;
        {$ENDIF}
        Caption       := aFileConfig.Servers[i].ServerName + ' ['+aFileConfig.Servers[i].ServerIP+']';
        Color         := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
        GradientColor := Amunhotep.MainForm.StyleManager.Colors.Border;
        TextColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
        DataObject    := aFileConfig.Servers[i]; 
        if lkFlagDev then
          begin
          if(aFileConfig.Servers[i].ServerIP = '127.0.0.1/3050')then
            begin
            j := aFileConfig.Servers[i].DataBases.Count-1;
            while(j >= 0)do
              if FileExists(aFileConfig.Servers[i].DataBases[j].DBFileName)then
                j := j - 1
               else
                begin
                aFileConfig.Servers[i].DataBases.Delete( j );
                j := aFileConfig.Servers[i].DataBases.Count-1;
                end;  
            lkSL := Files_FindFiles(lkSearchPath, '*.*DB', false);
            for l:=0 to lkSL.Count-1 do
              if not( (Pos('_BLOB.FDB', lkSL[l])>0) or (Pos('_LOG.FDB', lkSL[l])>0) or (Pos('.LOGUSERS.FDB', lkSL[l])>0) or (Pos('$', ExtractFileName(lkSL[l]))=1) )then
                begin
                lkFlag := true;
                for j:=0 to aFileConfig.Servers[i].DataBases.Count-1 do
                  if( UpperCase(aFileConfig.Servers[i].DataBases[j].DBFileName) = UpperCase(lkSL[l]) )then
                    begin
                    lkFlag := false;
                    break;
                    end;
                if lkFlag then
                  with aFileConfig.Servers[i].DataBases.Add do
                    begin
                    AliasName   := ExtractFileName(lkSL[l]);
                    DBFileName  := lkSL[l];
                    LoginPrompt := false;
                    LoginServer := true;
                    CodePage    := 'WIN1251';
                    end;    
                end;
            lkSL.Free;
            end;
          if(FBDataBase.Connected and (aFileConfig.Servers[i].ServerIP = Copy(FBDataBase.DataBaseName, 1, Pos(':',FBDataBase.DataBaseName)-1)) )then
            begin
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
            lkQr.SQL.Text := 'SELECT F.NAME, F.DATABASE_NAME FROM TABL$R_FILIALS F WHERE (F.ID > 0) AND (F.FLAG_DELETE = 0)';
            lkQr.Open;
            lkQr.First;
            while not lkQr.EOF do
              begin
              lkFlag := true;
              for j:=0 to aFileConfig.Servers[i].DataBases.Count-1 do
                if( UpperCase(aFileConfig.Servers[i].DataBases[j].DBFileName) = UpperCase(Trim(lkQr.FieldByName('DATABASE_NAME').AsString)) )then
                  begin
                  lkFlag := false;
                  break;
                  end;
              if lkFlag then
                with aFileConfig.Servers[i].DataBases.Add do
                  begin
                  AliasName   := lkQr.FieldByName('NAME').AsString;
                  DBFileName  := Trim(lkQr.FieldByName('DATABASE_NAME').AsString);
                  CodePage    := 'WIN1251';
                  LoginPrompt := false;
                  LoginServer := true;
                  UserName    := 'SYSDBA';
                  UserPassword:= 'masterkey';
                  UserRole    := '';
                  end;    
              lkQr.Next;
              end;
            if lkTr.InTransaction then
              lkTr.Commit;
            lkTr.Free;  
            end;
          end;
        for j:=0 to aFileConfig.Servers[i].DataBases.Count-1 do
          with Items.Add do
            begin
            Caption     := aFileConfig.Servers[i].DataBases[j].AliasName;
            {$IFDEF AMUNHOTEP4468}
            CaptionSmall:= aFileConfig.Servers[i].DataBases[j].FullNameIP;
            {$ENDIF}
            Hint        := aFileConfig.Servers[i].DataBases[j].FullNameIP;
            ImageIndex  := 0;
            Data        := aFileConfig.Servers[i].DataBases[j];
            end;
        end;  
      end; 
    SaveEncryptTxFBFileConfig(StrAbsolutePath('../conf/fb.conf', Amunhotep.ExeName), aFileConfig);  
  end;
  //============================================================================
  procedure FirebirdDialog_DatabaseSelect_DatabaseIns_OnClick(Sender :TObject);
  var
    lkCBTNS      :TCategoryButtons;
    lkFileConfig :TxFBFileConfig;
    lkDBItem     :TxsDataBase;
    lkSrvItem    :TxsServer;
    lkDBAlias    :string;
    lkDBFileName :string;
    lkDBCodePage :string;
    lkFBUserName :string;
    lkFBUserPwd  :string;
    lkFBUserRole :string;
    lkLoginPrompt:Boolean;
    lkLoginServer:Boolean;
  begin
    lkCBTNS      := TCategoryButtons(TComponent(Sender).Owner.FindComponent('CategoryButtons'));
    lkFileConfig := TxFBFileConfig(TComponent(Sender).Owner.FindComponent('FBFileConfig'));
    if(lkCBTNS.SelectedItem <> nil)then
      begin
      if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonItem'))then
        lkSrvItem := TxsServer(TButtonItem(lkCBTNS.SelectedItem).Category.DataObject)
       else
        if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonCategory'))then
          lkSrvItem := TxsServer(TButtonCategory(lkCBTNS.SelectedItem).DataObject)
         else
          begin
          Dialogs.MessageDlg(msg_firebird_dialog_database_select_database_ins_err, mtWarning, [mbOk]);
          exit;
          end; 
      lkDBAlias    := '';
      lkDBFileName := '';
      lkDBCodePage := 'WIN1251';
      lkFBUserName := 'SYSDBA';
      lkFBUserPwd  := 'masterkey';
      lkFBUserRole := '';
      lkLoginPrompt:= false;
      lkLoginServer:= true;
      if FirebirdDialog_DatabaseSettings_Execute(lkDBAlias, lkDBFileName, lkDBCodePage, lkFBUserName, lkFBUserRole, lkFBUserPwd, lkLoginPrompt, lkLoginServer)then
        begin
        lkDBItem              := lkSrvItem.DataBases.Add;
        lkDBItem.AliasName    := lkDBAlias;
        lkDBItem.DBFileName   := lkDBFileName;
        lkDBItem.CodePage     := lkDBCodePage;
        lkDBItem.UserName     := lkFBUserName; 
        lkDBItem.UserPassword := lkFBUserPwd;
        lkDBItem.UserRole     := lkFBUserRole;
        lkDBItem.LoginPrompt  := lkLoginPrompt;
        lkDBItem.LoginServer  := lkLoginServer;
        FirebirdDialog_DatabaseSelect_FillCategories(lkFileConfig, lkCBTNS);
        end;
      end
     else
      Dialogs.MessageDlg(msg_firebird_dialog_database_select_database_ins_err, mtWarning, [mbOk]);
  end;
  //============================================================================
  procedure FirebirdDialog_DatabaseSelect_DatabaseUpd_OnClick(Sender :TObject);
  var
    lkCBTNS      :TCategoryButtons;
    lkFileConfig :TxFBFileConfig;
    lkDBAlias    :string;
    lkDBFileName :string;
    lkDBCodePage :string;
    lkFBUserName :string;
    lkFBUserPwd  :string;
    lkFBUserRole :string;
    lkLoginPrompt:Boolean;
    lkLoginServer:Boolean;
  begin
    lkCBTNS      := TCategoryButtons(TComponent(Sender).Owner.FindComponent('CategoryButtons'));
    lkFileConfig := TxFBFileConfig(TComponent(Sender).Owner.FindComponent('FBFileConfig'));
    if(lkCBTNS.SelectedItem <> nil)then
      begin
      if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonItem'))then
        begin
        lkDBAlias    := TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).AliasName;
        lkDBFileName := TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).DBFileName;
        lkDBCodePage := TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).CodePage;
        lkFBUserName := TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).UserName;
        lkFBUserPwd  := TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).UserPassword;
        lkFBUserRole := TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).UserRole;
        lkLoginPrompt:= TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).LoginPrompt;
        lkLoginServer:= TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).LoginServer;
        if FirebirdDialog_DatabaseSettings_Execute(lkDBAlias, lkDBFileName, lkDBCodePage, lkFBUserName, lkFBUserRole, lkFBUserPwd, lkLoginPrompt, lkLoginServer)then
          begin
          TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).AliasName    := lkDBAlias;
          TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).DBFileName   := lkDBFileName;
          TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).CodePage     := lkDBCodePage;
          TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).UserName     := lkFBUserName; 
          TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).UserPassword := lkFBUserPwd;
          TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).UserRole     := lkFBUserRole;
          TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).LoginPrompt  := lkLoginPrompt;
          TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).LoginServer  := lkLoginServer;
          FirebirdDialog_DatabaseSelect_FillCategories(lkFileConfig, lkCBTNS);
          end;
        end
       else
        Dialogs.MessageDlg(msg_firebird_dialog_database_select_database_upd_err, mtWarning, [mbOk]);
      end
     else
      Dialogs.MessageDlg(msg_firebird_dialog_database_select_database_upd_err, mtWarning, [mbOk]);
  end;
  //============================================================================
  procedure FirebirdDialog_DatabaseSelect_DatabaseDel_OnClick(Sender :TObject);
  var
    lkCBTNS      :TCategoryButtons;
    lkFileConfig :TxFBFileConfig;
    lkStr        :string;
  begin
    lkCBTNS      := TCategoryButtons(TComponent(Sender).Owner.FindComponent('CategoryButtons'));
    lkFileConfig := TxFBFileConfig(TComponent(Sender).Owner.FindComponent('FBFileConfig'));
    if(lkCBTNS.SelectedItem <> nil)then
      begin
      if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonItem'))then
        begin
        lkStr := msg_firebird_dialog_database_select_database_del_hint+' ?'+#13#10+
                 TButtonItem(lkCBTNS.SelectedItem).Hint;
        if(Dialogs.MessageDlg(lkStr, mtConfirmation, [mbYes, mbNo]) = mrYes)then
          begin
          TxsServer(TButtonItem(lkCBTNS.SelectedItem).Category.DataObject).DataBases.Delete(
            TxsDataBase(TButtonItem(lkCBTNS.SelectedItem).Data).Index );
          FirebirdDialog_DatabaseSelect_FillCategories(lkFileConfig, lkCBTNS);
          end;
        end
       else
        Dialogs.MessageDlg(msg_firebird_dialog_database_select_database_del_err, mtWarning, [mbOk]);
      end
     else
      Dialogs.MessageDlg(msg_firebird_dialog_database_select_database_del_err, mtWarning, [mbOk]);
  end;
  //============================================================================
  procedure FirebirdDialog_DatabaseSelect_ServerIns_OnClick(Sender :TObject);
  var
    lkFileConfig     :TxFBFileConfig;
    lkCBTNS          :TCategoryButtons;
    lkSrvItem        :TxsServer;
    lkServerName     :string;
    lkServerIP       :string; 
    lkServerCodePage :string; 
    lkFBUserName     :string; 
    lkFBUserPassword :string; 
    lkFBUserRole     :string;
    lkAutoConnect    :Boolean;
    lkBackupOptions  :TxFBBackupOptions;
    lkRestoreOptions :TxFBRestoreOptions;
    lkRestorePageSize:TxsRestorePageSize;
  begin
    lkCBTNS      := TCategoryButtons(TComponent(Sender).Owner.FindComponent('CategoryButtons'));
    lkFileConfig := TxFBFileConfig(TComponent(Sender).Owner.FindComponent('FBFileConfig'));
    if(FirebirdDialog_ServerSettings_Execute(lkServerName, lkServerIP, lkServerCodePage, lkFBUserName, lkFBUserRole, lkFBUserPassword, lkAutoConnect, lkBackupOptions, lkRestoreOptions, lkRestorePageSize))then
      begin
      lkSrvItem                := lkFileConfig.Servers.Add;
      lkSrvItem.ServerName     := lkServerName;
      lkSrvItem.ServerIP       := lkServerIP;
      lkSrvItem.CodePage       := lkServerCodePage;
      lkSrvItem.AutoConnect    := lkAutoConnect;
      if(lkSrvItem.AutoConnect)then
        begin
        lkSrvItem.UserName     := lkFBUserName;
        lkSrvItem.UserPassword := lkFBUserPassword;
        lkSrvItem.UserRole     := lkFBUserRole;
        end
       else
        begin
        lkSrvItem.UserName     := '';
        lkSrvItem.UserPassword := '';
        lkSrvItem.UserRole     := '';
        end; 
      lkSrvItem.BackupOptions  := lkBackupOptions;
      lkSrvItem.RestoreOptions := lkRestoreOptions;
      lkSrvItem.RestorePageSize:= lkRestorePageSize;
      FirebirdDialog_DatabaseSelect_FillCategories(lkFileConfig, lkCBTNS);
      end;  
  end;
  //============================================================================
  procedure FirebirdDialog_DatabaseSelect_ServerUpd_OnClick(Sender :TObject);
  var
    lkFileConfig     :TxFBFileConfig;
    lkCBTNS          :TCategoryButtons;
    lkSrvItem        :TxsServer;
    lkServerName     :string;
    lkServerIP       :string; 
    lkServerCodePage :string; 
    lkFBUserName     :string; 
    lkFBUserPassword :string; 
    lkFBUserRole     :string;
    lkAutoConnect    :Boolean;
    lkBackupOptions  :TxFBBackupOptions;
    lkRestoreOptions :TxFBRestoreOptions;
    lkRestorePageSize:TxsRestorePageSize;
  begin
    lkCBTNS      := TCategoryButtons(TComponent(Sender).Owner.FindComponent('CategoryButtons'));
    lkFileConfig := TxFBFileConfig(TComponent(Sender).Owner.FindComponent('FBFileConfig'));
    if(not(lkCBTNS.SelectedItem <> nil))then
      begin
      Dialogs.MessageDlg(msg_firebird_dialog_database_select_server_error, mtWarning, [mbOk]);
      exit;
      end;
    if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonItem'))then
      lkSrvItem := TxsServer(TButtonItem(lkCBTNS.SelectedItem).Category.DataObject)
     else
      if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonCategory'))then
        lkSrvItem := TxsServer(TButtonCategory(lkCBTNS.SelectedItem).DataObject)
       else
        begin
        Dialogs.MessageDlg(msg_firebird_dialog_database_select_server_error, mtWarning, [mbOk]);
        exit;
        end; 
    lkServerName     := lkSrvItem.ServerName;
    lkServerIP       := lkSrvItem.ServerIP;
    lkServerCodePage := lkSrvItem.CodePage;
    lkAutoConnect    := lkSrvItem.AutoConnect;
    lkFBUserName     := lkSrvItem.UserName;
    lkFBUserPassword := lkSrvItem.UserPassword;
    lkFBUserRole     := lkSrvItem.UserRole;
    lkBackupOptions  := lkSrvItem.BackupOptions;
    lkRestoreOptions := lkSrvItem.RestoreOptions;
    lkRestorePageSize:= lkSrvItem.RestorePageSize;
    if(FirebirdDialog_ServerSettings_Execute(lkServerName, lkServerIP, lkServerCodePage, lkFBUserName, lkFBUserRole, lkFBUserPassword, lkAutoConnect, lkBackupOptions, lkRestoreOptions, lkRestorePageSize))then
      begin
      lkSrvItem.ServerName     := lkServerName;
      lkSrvItem.ServerIP       := lkServerIP;
      lkSrvItem.CodePage       := lkServerCodePage;
      lkSrvItem.AutoConnect    := lkAutoConnect;
      if(lkSrvItem.AutoConnect)then
        begin
        lkSrvItem.UserName     := lkFBUserName;
        lkSrvItem.UserPassword := lkFBUserPassword;
        lkSrvItem.UserRole     := lkFBUserRole;
        end
       else
        begin
        lkSrvItem.UserName     := '';
        lkSrvItem.UserPassword := '';
        lkSrvItem.UserRole     := '';
        end; 
      lkSrvItem.BackupOptions  := lkBackupOptions;
      lkSrvItem.RestoreOptions := lkRestoreOptions;
      lkSrvItem.RestorePageSize:= lkRestorePageSize;
      FirebirdDialog_DatabaseSelect_FillCategories(lkFileConfig, lkCBTNS);
      end;  
  end;
  //============================================================================
  procedure FirebirdDialog_DatabaseSelect_ServerDel_OnClick(Sender :TObject);
  var
    lkCBTNS      :TCategoryButtons;
    lkFileConfig :TxFBFileConfig;
    lkSrvItem    :TxsServer;
    lkStr        :string;
  begin
    lkCBTNS      := TCategoryButtons(TComponent(Sender).Owner.FindComponent('CategoryButtons'));
    lkFileConfig := TxFBFileConfig(TComponent(Sender).Owner.FindComponent('FBFileConfig'));
    if(not(lkCBTNS.SelectedItem <> nil))then
      begin
      Dialogs.MessageDlg(msg_firebird_dialog_database_select_server_error, mtWarning, [mbOk]);
      exit;
      end;
    if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonItem'))then
      lkSrvItem := TxsServer(TButtonItem(lkCBTNS.SelectedItem).Category.DataObject)
     else
      if(ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonCategory'))then
        lkSrvItem := TxsServer(TButtonCategory(lkCBTNS.SelectedItem).DataObject)
       else
        begin
        Dialogs.MessageDlg(msg_firebird_dialog_database_select_server_error, mtWarning, [mbOk]);
        exit;
        end; 
    lkStr := msg_firebird_dialog_database_select_server_del_hint+' ?'+#13#10+
             lkSrvItem.ServerName+' ['+lkSrvItem.ServerIP+']';
    if(Dialogs.MessageDlg(lkStr, mtConfirmation, [mbYes, mbNo]) = mrYes)then
      begin
      lkFileConfig.Servers.Delete(lkSrvItem.Index);
      FirebirdDialog_DatabaseSelect_FillCategories(lkFileConfig, lkCBTNS);
      end;
  end;
  //============================================================================
  procedure FirebirdDialog_DataBaseSelect_CreateToolButtons(aOwner :TComponent; aParent:TWinControl; aImages:TImageList; const aImageIndx:array of Integer);
  var
    lkToolBtn :TxcToolBarButton;
  begin
    lkToolBtn := TxcToolBarButton.Create(aOwner);
    with lkToolBtn do
      begin
      Name         := 'btnServerIns';
      Parent       := aParent;
      Height       := aImages.Height + 8;
      Top          := (aParent.ControlCount * Height) + 2;
      Align        := alTop;
      Caption      := msg_firebird_dialog_database_select_server_ins;
      Hint         := msg_firebird_dialog_database_select_server_ins_hint;
      ImageIndex   := aImageIndx[0];
      ImagesSmall  := aImages;
      ShowCaption  := true;
      ShowHint     := true;
      StyleManager := Amunhotep.MainForm.StyleManager;
      OnClick      := @FirebirdDialog_DatabaseSelect_ServerIns_OnClick;
      end;
    lkToolBtn := TxcToolBarButton.Create(aOwner);
    with lkToolBtn do
      begin
      Name         := 'btnServerUpd';
      Parent       := aParent;
      Height       := aImages.Height + 8;
      Top          := (aParent.ControlCount * Height) + 2;
      Align        := alTop;
      Caption      := msg_firebird_dialog_database_select_server_upd;
      Hint         := msg_firebird_dialog_database_select_server_upd_hint;
      ImageIndex   := aImageIndx[1];
      ImagesSmall  := aImages;
      ShowCaption  := true;
      ShowHint     := true;
      StyleManager := Amunhotep.MainForm.StyleManager;
      OnClick      := @FirebirdDialog_DatabaseSelect_ServerUpd_OnClick;
      end;
    lkToolBtn := TxcToolBarButton.Create(aOwner);
    with lkToolBtn do
      begin
      Name         := 'btnServerDel';
      Parent       := aParent;
      Height       := aImages.Height + 8;
      Top          := (aParent.ControlCount * Height) + 2;
      Align        := alTop;
      Caption      := msg_firebird_dialog_database_select_server_del;
      Hint         := msg_firebird_dialog_database_select_server_del_hint;
      ImageIndex   := aImageIndx[2];
      ImagesSmall  := aImages;
      ShowCaption  := true;
      ShowHint     := true;
      StyleManager := Amunhotep.MainForm.StyleManager;
      OnClick      := @FirebirdDialog_DatabaseSelect_ServerDel_OnClick;
      end;
    lkToolBtn := TxcToolBarButton.Create(aOwner);
    with lkToolBtn do
      begin
      Name         := 'btnDatabaseIns';
      Parent       := aParent;
      Height       := aImages.Height + 8;
      Top          := (aParent.ControlCount * Height) + 2;
      Align        := alTop;
      Caption      := msg_firebird_dialog_database_select_Database_ins;
      Hint         := msg_firebird_dialog_database_select_Database_ins_hint;
      ImageIndex   := aImageIndx[3];
      ImagesSmall  := aImages;
      ShowCaption  := true;
      ShowHint     := true;
      StyleManager := Amunhotep.MainForm.StyleManager;
      OnClick      := @FirebirdDialog_DatabaseSelect_DatabaseIns_OnClick;
      end;
    lkToolBtn := TxcToolBarButton.Create(aOwner);
    with lkToolBtn do
      begin
      Name         := 'btnDatabaseUpd';
      Parent       := aParent;
      Height       := aImages.Height + 8;
      Top          := (aParent.ControlCount * Height) + 2;
      Align        := alTop;
      Caption      := msg_firebird_dialog_database_select_Database_upd;
      Hint         := msg_firebird_dialog_database_select_Database_upd_hint;
      ImageIndex   := aImageIndx[4];
      ImagesSmall  := aImages;
      ShowCaption  := true;
      ShowHint     := true;
      StyleManager := Amunhotep.MainForm.StyleManager;
      OnClick      := @FirebirdDialog_DatabaseSelect_DatabaseUpd_OnClick;
      end;
    lkToolBtn := TxcToolBarButton.Create(aOwner);
    with lkToolBtn do
      begin
      Name         := 'btnDatabaseDel';
      Parent       := aParent;
      Height       := aImages.Height + 8;
      Top          := (aParent.ControlCount * Height) + 2;
      Align        := alTop;
      Caption      := msg_firebird_dialog_database_select_Database_del;
      Hint         := msg_firebird_dialog_database_select_Database_del_hint;
      ImageIndex   := aImageIndx[5];
      ImagesSmall  := aImages;
      ShowCaption  := true;
      ShowHint     := true;
      StyleManager := Amunhotep.MainForm.StyleManager;
      OnClick      := @FirebirdDialog_DatabaseSelect_DatabaseDel_OnClick;
      end;
  end;
