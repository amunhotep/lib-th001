{$DEFINE PEAKTOP:IDE/ERP/DBO/USERS/RIGHTS.INC}
  //==================== PEAKTOP:IDE/ERP/DBO/USERS/RIGHTS.INC ==================
  function ERP_User_HasRights(const aUserId, aRoleId:string):Boolean ;
  var
    lkRightsList :string;
  begin
    Result := false;
    if not FBDataBase.Connected then exit;
    if GetField(FBDataBase, 'PROC$_USERS_ACCS_ROLES', 'ROLES_LIST', '', lkRightsList)then
      Result := (Pos('~'+aRoleId+'~', lkRightsList) > 0);
  end;
  //============================================================================
  function ERP_User_HasRightsAdmin(const aUserId:string):Boolean ;
  begin
    Result := (ERP_User_HasRights(aUserId, '1000000') or ERP_User_HasRights(aUserId, '1000004') or (aUserId = 'PEAKTOP'));
  end;
