{$DEFINE PEAKTOP:IDE/ERP/DBO/MENU/LOADITEMS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                   {$I PEAKTOP:GLOBAL_VARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}            {$I ../OBJECTNAMES.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}  {$I ../USERS/GLOBALVARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/CONST.INC}             {$I ./CONST.INC}                  {$ENDIF}
  //================ PEAKTOP:IDE/ERP/DBO/MENU/LOADITEMS.INC ====================
const 
  ERP_GLOBAL_VARIABLE_DBMENU_20120710 = 'ERP_GLOBAL_VARIABLE_DBMENU_20120710';
  //============================================================================
  function ERP_DBMenuItem_GetScript(const aMenuItemId :Integer):string;
  var
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
  begin
    Result := '';
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
      DataBase    := lkTr.DefaultDataBase;
      Transaction := lkTr;
      SQL.Text    := 'SELECT FIRST 1 MNU.SCRIPT_NAME FROM TABL$_MENU MNU WHERE (MNU.ID = '''+IntToStr(aMenuItemId)+''') ';
      if not Active then  
        try
          Open;
        except
          if lkTr.InTransaction then 
            lkTr.Commit;
          lkTr.Free;
          exit;
        end; 
      First;
      Result := FieldByName('SCRIPT_NAME').AsString;
      end;
    if lkTr.InTransaction then 
      lkTr.Commit;
    lkTr.Free;
  end;
  //===========================================================================
  procedure ERP_DBMenuItem_OnClick_Default(Sender :TObject);
  var
    lkScName :string;
    lkCaption:string;
  begin
    lkScName := ERP_DBMenuItem_GetScript( TComponent(Sender).Tag );
    lkCaption:= TComponent(Sender).Name;
    if ObjectInheritsFrom(Sender,'TMenuItem') then
      lkCaption := TMenuItem(Sender).Caption;
    if(lkScName = '')then exit; 
    // users recent menu
    ExecSQL(FBDataBase, 
      'EXECUTE BLOCK AS '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  IF(NOT(EXISTS(SELECT R.RDB$RELATION_ID FROM RDB$RELATIONS R WHERE(TRIM(R.RDB$RELATION_NAME)=''TABL$_USERS_RCNT''))))THEN EXIT; '+SQLCRLF+
      '  EXECUTE STATEMENT ''UPDATE OR INSERT INTO TABL$_USERS_RCNT(NAME, USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME)VALUES('''''+lkCaption+''''', '''''+
       GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''''', 0, '''''+IntToStr(ERP_OBJECTTYPE_MENU)+''''', '''''+lkScName+''''')MATCHING(USER_ID, SUBTYPE, TYPE_ID, SCRIPT_NAME);''; '+SQLCRLF+    
      'END');    
    call(lkScName);
  end;
  //==========================================================================
  function ERP_DBMenuItem_Find(aParentMenuItem:TMenuItem; const aMenuItemName:string; var aFoundedMenuItem :TMenuItem):Boolean;
  var
    i :Integer;
  begin
    Result  := false;
    aFoundedMenuItem := nil;
    if(aParentMenuItem = nil)then exit;
    for i:=0 to aParentMenuItem.Count-1 do 
      begin
      if(UpperCase(aParentMenuItem.Items[i].Name) = UpperCase(aMenuItemName))then
        begin
        aFoundedMenuItem := aParentMenuItem.Items[i];
        Result := true;
        end
       else
        begin 
        if(aParentMenuItem.Items[i].Count > 0)then
          Result := ERP_DBMenuItem_Find(aParentMenuItem.Items[i], aMenuItemName, aFoundedMenuItem);
        end;
      if Result then exit;
      end;
  end;
  //===========================================================================
  function ERP_DBMenuItem_Create(aParentMenuItem :TMenuItem;const aCaption, aShortCut:string; aId, aImageIndex, aGroupIndex :Integer):TMenuItem;
  var
    lkShortCut     :TShortCut;
    lkGroupIndex   :Integer;
    lkMenuItemName :string;
    i              :Integer;
  begin
    try lkShortCut := TextToShortCut(aShortCut); finally end;
    lkMenuItemName := UpperCase(ERP_MENUITEM_DATABASE_PREFIX+IntToStr(aId));
    lkGroupIndex   := aGroupIndex;
    if(lkGroupIndex < ERP_MENUITEM_DATABASE_INDEX_BEGIN)then lkGroupIndex := lkGroupIndex + ERP_MENUITEM_DATABASE_INDEX_BEGIN;
    if(lkGroupIndex > ERP_MENUITEM_DATABASE_INDEX_END  )then lkGroupIndex := ERP_MENUITEM_DATABASE_INDEX_END;
    if not ERP_DBMenuItem_Find(aParentMenuItem, lkMenuItemName, Result) then 
      Result := TMenuItem.Create(aParentMenuItem);
    with Result do
      begin 
      Name       := lkMenuItemName;
      if(aCaption[1] = '|')then
        begin
        aCaption := Copy(aCaption, 2, Length(aCaption)-1);
        {$IFDEF AMUNHOTEP4712}
        _Break   := mbBarBreak;
        {$ENDIF}        
        end;
      Caption    := aCaption;
      Hint       := aCaption;
      ImageIndex := aImageIndex;
      GroupIndex := lkGroupIndex;
      ShortCut   := lkShortCut;
      Tag        := aId;
      Visible    := true; 
      end;
    for i:=0 to aParentMenuItem.Count-1 do
      if(aParentMenuItem.Items[i].GroupIndex > lkGroupIndex)then
        break;  
    aParentMenuItem.Insert(i, Result);
    Amunhotep.MainForm.xcMenu.AssignMethods(Result);
  end;
  //============================================================================
  function ERP_DBMenuItems_SelectSQL(const aMenusName, aParentMenuItemId:string):string;
  begin
    // проблема производительности решена путем отключения индекса по столбцу PARENT_ID    
    Result := 
      'EXECUTE BLOCK RETURNS( '+SQLCRLF+
      '   ID          TYPE OF COLUMN TABL$_MENU.ID '+SQLCRLF+
      '  ,PARENT_ID   TYPE OF COLUMN TABL$_MENU.PARENT_ID '+SQLCRLF+
      '  ,NAME        TYPE OF COLUMN TABL$_MENU.NAME '+SQLCRLF+
      '  ,SHORTCUT    TYPE OF COLUMN TABL$_MENU.SHORTCUT '+SQLCRLF+
      '  ,IMAGE_INDEX TYPE OF COLUMN TABL$_MENU.IMAGE_INDEX '+SQLCRLF+
      '  ,GROUP_INDEX TYPE OF COLUMN TABL$_MENU.GROUP_INDEX '+SQLCRLF+
      '  ,SCRIPT_NAME TYPE OF COLUMN TABL$_MENU.SCRIPT_NAME '+SQLCRLF+
      '  ,CHILD_COUNT TYPE OF COLUMN TABL$_MENU.ID '+SQLCRLF+
      ')AS '+SQLCRLF+
      '  DECLARE VARIABLE P_COUNTRY_IDS TYPE OF COLUMN TABL$R_COUNTRIES.NAME; '+SQLCRLF+
      '  DECLARE VARIABLE P_COUNTRY_ID  TYPE OF COLUMN TABL$R_COUNTRIES.ID; '+SQLCRLF+
      '  DECLARE VARIABLE P_MENUS_ID    TYPE OF COLUMN TABL$_MENU.ID; '+SQLCRLF+
      '  DECLARE VARIABLE P_USER_ID     TYPE OF COLUMN TABL$_USERS.ID; '+SQLCRLF+
      '  DECLARE VARIABLE P_SQL         TYPE OF COLUMN TABL$_MENU.NAME; '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  P_COUNTRY_ID = GEN_ID(GENR$R_COUNTRIES_DEFAULT, 0); '+SQLCRLF+
      '  P_COUNTRY_IDS = RDB$GET_CONTEXT(''USER_SESSION'', '''+ERP_GLOBALVARIABLE_USER_LOCAL+'''); '+SQLCRLF+
      '  IF( (:P_COUNTRY_IDS IS NOT NULL) AND (TRIM(:P_COUNTRY_IDS) <> '''') )THEN '+SQLCRLF+
      '    P_COUNTRY_ID = CAST(:P_COUNTRY_IDS AS INTEGER); '+SQLCRLF+
      ' '+SQLCRLF+
      '  P_USER_ID = RDB$GET_CONTEXT(''USER_SESSION'', '''+ERP_GLOBALVARIABLE_USER_CURRENT+'''); '+SQLCRLF+
      '  SELECT FIRST 1 M.ID FROM TABL$_MENUS M WHERE(UPPER(TRIM(M.NAME)) = '''+UpperCase(aMenusName)+''')INTO :P_MENUS_ID; '+SQLCRLF+
      '  FOR '+SQLCRLF+
      '    SELECT DISTINCT MNU.GROUP_INDEX, MNU.ID, MNU.NAME, MNU.PARENT_ID, MNU.SHORTCUT, MNU.IMAGE_INDEX, MNU.SCRIPT_NAME '+SQLCRLF+
      '          ,(SELECT COUNT(MM.ID) FROM TABL$_MENU MM WHERE (MM.PARENT_ID = MNU.ID)) CHILD_COUNT '+SQLCRLF+
      '    FROM   TABL$_MENU MNU '+SQLCRLF+
      '    WHERE  ((MNU.PARENT_ID+0) = '''+aParentMenuItemId+''') '+SQLCRLF+
      '      AND  ((MNU.MENUS_ID+0) = :P_MENUS_ID) '+SQLCRLF+
      '      AND  (   (:P_USER_ID = ''PEAKTOP'') '+SQLCRLF+
      '            OR (EXISTS('+SQLCRLF+
      '                  SELECT UA.ROLE_ID  '+SQLCRLF+
      '                  FROM   TABL$_USERS_ACCS UA  '+SQLCRLF+
      '                  WHERE  (UA.USER_ID = :P_USER_ID)  '+SQLCRLF+
      '                    AND  (MNU.ACCSS CONTAINING ''~''||UA.ROLE_ID||''~'') '+SQLCRLF+
      '                )) '+SQLCRLF+
      '           ) '+SQLCRLF+
      '    ORDER BY MNU.GROUP_INDEX '+SQLCRLF+
      '    INTO   :GROUP_INDEX, :ID, :NAME, :PARENT_ID, :SHORTCUT, :IMAGE_INDEX, :SCRIPT_NAME, :CHILD_COUNT '+SQLCRLF+
      '  DO '+SQLCRLF+
      '    BEGIN '+SQLCRLF+
      '    IF(EXISTS( '+SQLCRLF+
      '        SELECT RF.RDB$RELATION_ID '+SQLCRLF+
      '        FROM   RDB$RELATIONS RF '+SQLCRLF+
      '        WHERE  (TRIM(RF.RDB$RELATION_NAME) = ''TABL$_LOCAL'') '+SQLCRLF+
      '    ))THEN '+SQLCRLF+
      '      BEGIN '+SQLCRLF+
      '      P_SQL = '+SQLCRLF+
      '        '' SELECT FIRST 1 COALESCE (L.NAME, ''''''||:NAME||'''''') ''|| '+SQLCRLF+
      '        '' FROM   TABL$_LOCAL L ''|| '+SQLCRLF+
      '        '' WHERE  (L.COUNTRY_ID = ''||:P_COUNTRY_ID||'') ''|| '+SQLCRLF+
      '        ''   AND  (L.OBJ_ID     = ''''TABL$_MENU'''') ''|| '+SQLCRLF+
//      '        ''   AND  (L.COL_ID     = ''''NAME'''') ''|| '+SQLCRLF+
      '        ''   AND  (L.REC_ID     = ''||:ID||'') '' ; '+SQLCRLF+
      '      EXECUTE STATEMENT :P_SQL INTO :NAME; '+SQLCRLF+
      '      END '+SQLCRLF+
      '    SUSPEND; '+SQLCRLF+
      '    END '+SQLCRLF+
      'END ';
  end;
  //===========================================================================
  procedure ERP_DBMenuItems_Build(aParentMenuItem :TMenuItem; const aMenusName, aParentMenuItemId:string; aOnMenuItemClick :TNotifyEvent);
  var
    lkTr :TxFBTransaction;
    lkQr :TxFBQuery;
    lkMI :TMenuItem;
  begin
    DontAutoFree; // нужно для обработчика событий пунктов меню.
    if not FBDataBase.Connected then exit;
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
      DataBase    := lkTr.DefaultDataBase;
      Transaction := lkTr;
      SQL.Text    := ERP_DBMenuItems_SelectSQL(aMenusName, aParentMenuItemId);
      try
        Open;
      except  
        if lkTr.InTransaction then 
          lkTr.Commit;
        lkTr.Free;
        exit;
      end;
      FetchAll;
      First;
      while not EOF do
        begin
        lkMI := ERP_DBMenuItem_Create(aParentMenuItem, FieldByName('NAME').AsString, FieldByName('SHORTCUT').AsString, FieldByName('ID').AsInteger, FieldByName('IMAGE_INDEX').AsInteger, FieldByName('GROUP_INDEX').AsInteger);
        if(FieldByName('CHILD_COUNT').AsInteger > 0)then
          ERP_DBMenuItems_Build(lkMI, aMenusName, FieldByName('ID').AsString, aOnMenuItemClick)
         else
          lkMI.OnClick  := aOnMenuItemClick;
        Next;
        end;
      if Active then
        Close;
      end;  
    if lkTr.InTransaction then 
      lkTr.Commit;
    lkTr.Free;
  end;
  //===========================================================================
  procedure ERP_DBMenuItems_Clear(aParentMenuItem :TMenuItem);
  var
    i :Integer;
  begin
    i := 0;
    while(i < aParentMenuItem.Count)do
      begin
      if(Pos(UpperCase(ERP_MENUITEM_DATABASE_PREFIX), UpperCase(aParentMenuItem.Items[i].Name)) = 1)then
        begin
        aParentMenuItem.Items[i].Free;
        i := i - 1;
        end;
      i := i + 1;  
      end;
  end;     
