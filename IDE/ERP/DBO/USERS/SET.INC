{$DEFINE PEAKTOP:IDE/ERP/DBO/USERS/SET.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                 {$I PEAKTOP:GLOBAL_VARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}{$I ./GLOBALVARIABLES.INC}        {$ENDIF}
  //==================== PEAKTOP:IDE/ERP/DBO/USERS/SET.INC =====================
  function ERP_User_SetCurrentToDataBase(const aUserName:string):Boolean;
  begin
    Result := ExecSQL(FBDataBase, 'EXECUTE BLOCK AS BEGIN RDB$SET_CONTEXT(''USER_SESSION'', '''+
      ERP_GLOBALVARIABLE_USER_CURRENT+''', '''+aUserName+'''); END ');
    ExecSQL(FBDataBase, 'EXECUTE BLOCK AS BEGIN RDB$SET_CONTEXT(''USER_SESSION'', '''+
      ERP_GLOBALVARIABLE_AMUNHOTEP_VERSION+''', ''AMUNHOTEP'+IntToStr(Amunhotep.Version)+'''); END ');
  end;
