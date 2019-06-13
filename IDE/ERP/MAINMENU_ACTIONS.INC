{$DEFINE PEAKTOP:IDE/ERP/MAINMENU_ACTIONS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                  {$I PEAKTOP:GLOBAL_VARIABLES.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC} {$I ./DBO/USERS/GLOBALVARIABLES.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/RIGHTS.INC}          {$I ./DBO/USERS/RIGHTS.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/MAINMENU_LANG.INC}             {$I ./MAINMENU_LANG.INC}            {$ENDIF}
  //=================== PEAKTOP:IDE/ERP/MAINMENU_ACTIONS.INC ===================
  function ERP_IDE_CheckRightsAdmin:Boolean;
  begin
    Result := ERP_User_HasRightsAdmin(GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));
    if not Result then
      Dialogs.MessageDlg(msg_erpide_error_accessdenied+#13#10+msg_erpide_error_userhasnotrightsadmin, mtWarning, [mbOk]);
  end;
  //============================================================================
  procedure actBaseNew_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/CREATE/DEFAULT.PS');
  end;
  //============================================================================
  procedure actBaseOpen_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/DATABASE/CONNECT.PS');
  end;
  //============================================================================
  procedure actBaseOpen_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := not FBDataBase.Connected;
  end;
  //============================================================================
  procedure actBaseClose_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/DATABASE/DISCONNECT.PS');
  end;
  //============================================================================
  procedure actBaseAtchs_OnExecute(Sender :TObject);
  begin
    if not ERP_IDE_CheckRightsAdmin then exit;
    call('PEAKTOP:IDE/ERP/DBO/OPER/ATTACHMENTS.PS');
  end;
  //============================================================================
  procedure actBaseFS_OnExecute(Sender :TObject);
  begin
    if not ERP_IDE_CheckRightsAdmin then exit;
    call('PEAKTOP:IDE/ERP/DBO/OPER/FILESYSTEM.PS');
  end;
  //============================================================================
  procedure actBaseConfig_OnExecute(Sender :TObject);
  begin
    if not ERP_IDE_CheckRightsAdmin then exit;
    call('PEAKTOP:IDE/ERP/DBO/OPER/CFGRTR.PS');
  end;
  //============================================================================
  procedure actBaseMenu_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/DBO/MENU/REBUILD_MAIN.PS');
  end;
  //============================================================================
  procedure actBaseBuffer_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/DBO/OPER/BUFFER.PS');
  end;
  //============================================================================
  procedure actBaseRecent_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/DBO/OPER/RECENT.PS');
  end;
  //============================================================================
  procedure actBasePanel_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/PANELCLIENT.PS');
  end;
  //============================================================================
  procedure actBaseStdLib_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:APPL/MANAGE/STDLIB/DEFAULT.PS');
  end;
  //============================================================================
  procedure actBaseGV_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:IDE/ERP/DBO/OPER/GLOBALVARIABLES.PS');
  end;
  //============================================================================
  procedure actBaseClose_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := FBDataBase.Connected;
  end;
  //============================================================================
  procedure actBaseExit_OnExecute(Sender :TObject);
  begin
    Amunhotep.Terminate;
  end;
