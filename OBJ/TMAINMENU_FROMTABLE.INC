{$DEFINE PEAKTOP:OBJ/TMAINMENU_FROMTABLE.INC}
  //===========================================================================
  function GetScriptName(const MenuId :Integer):string;
  var
    FBTrans :TxFBTransaction;
    FBQr    :TxFBQuery;
  begin
    Result := '';
    FBTrans := TxFBTransaction.Create(nil);
    FBTrans.DefaultDataBase := FBDataBase;
    FBQr             := TxFBQuery.Create(FBTrans);
    FBQr.DataBase    := FBDataBase;
    FBQr.Transaction := FBTrans;
    FBQr.SQL.Text    := 'SELECT * FROM TABL$_MENU MNU WHERE (ID = '''+
       IntToStr(MenuId)+''') ';
    if not FBQr.Active then
      try
        FBQr.Open;
       finally
        FBQr.First;
        Result := FBQr.FieldByName('SCRIPT_NAME').AsString;
       end; 
    if FBTrans.InTransaction then FBTrans.Rollback;
    FBTrans.Free;
  end;
  //===========================================================================
  procedure DoMenuItem_OnClick(Sender :TObject; Id :Integer; ScName :string);forward;
  //===========================================================================
  procedure MenuItem_OnClick(Sender :TObject);
  var
    ScName :string;
  begin
    ScName := GetScriptName(TComponent(Sender).Tag);
    DoMenuItem_OnClick(Sender, TComponent(Sender).Tag, ScName);
  end;
  //==========================================================================
  function FindMenuItem(ParentItem:TMenuItem; const Name:string; 
             var Founded :TMenuItem):Boolean;
  var
    i :Integer;
  begin
    Result  := false;
    Founded := nil;
    if ParentItem=nil then exit;
    for i:=0 to ParentItem.Count-1 do
      begin
      if(AnsiUpperCase(ParentItem.Items[i].Name) = Name)then
        begin
        Founded := ParentItem.Items[i];
        Result  := true;
        end
       else
        begin 
        if(ParentItem.Items[i].Count>0)then
          Result := FindMenuItem(ParentItem.Items[i], Name, Founded);
        end;
      if Result then exit;
      end;
  end;
  //===========================================================================
  function CreateMenuItem(ParentItem :TMenuItem;const Caption, ShortCut:string; 
             Id, ImageIndex, GroupIndex :Integer):TMenuItem;
  var
    SCut     :TShortCut;
    MenuName :string;
  begin
    try SCut := TextToShortCut(ShortCut); finally end;
    MenuName := AnsiUpperCase('MENUITEM_'+IntToStr(Id));
    if FindMenuItem(Amunhotep_MainForm.Menu.Items, MenuName, Result) then exit;
    Result            := TMenuItem.Create(ParentItem);
    Result.Name       := MenuName;
    Result.Caption    := Caption;
    Result.Hint       := Caption;
    Result.ImageIndex := ImageIndex;
    Result.GroupIndex := GroupIndex;
    Result.ShortCut   := SCut;
    Result.Tag        := Id;
    Result.Visible    := true; 
    ParentItem.Add(Result);
  end;
  //===========================================================================
  procedure BuildMenuItems(const a_MenusId, a_UserName:string; const 
              a_UsePolicy:Boolean; ParentItem :TMenuItem; ParentId :Integer);
  var
    FBTrans  :TxFBTransaction;
    FBQuery  :TxFBQuery;
    FBQrTB   :TxFBQuery;
    mi       :TMenuItem;
    aCapt    :string;
    sql      :string; 
    LastLeft :Integer; 
  begin
    if not FBDataBase.Connected then exit;
    FBTrans                 := TxFBTransaction.Create(nil);
    FBTrans.DefaultDataBase := FBDataBase;
    FBTrans.Params.Clear;
    FBTrans.Params.Add('isc_tpb_read_committed'); 
    FBTrans.Params.Add('isc_tpb_read'); 
    FBTrans.Params.Add('isc_tpb_rec_version'); 
    FBTrans.Params.Add('isc_tpb_nowait'); 
    FBQuery                 := TxFBQuery.Create(FBTrans);
    FBQuery.DataBase        := FBDataBase;
    FBQuery.Transaction     := FBTrans;
    FBQrTB                  := TxFBQuery.Create(FBTrans);
    FBQrTB.DataBase         := FBDataBase;
    FBQrTB.Transaction      := FBTrans;
    sql := 
      'SELECT MNU.ID,MNU.NAME,MNU.PARENT_ID,MNU.SHORTCUT,MNU.IMAGE_INDEX,'+#13#10+
      '       MNU.GROUP_INDEX, MNU.SCRIPT_NAME, '+#13#10+
      '       (SELECT COUNT(MM.ID) FROM TABL$_MENU MM WHERE '+
                   '(MM.PARENT_ID = MNU.ID)) CHILD_COUNT, '+#13#10+
      '       COUNT(MA.ROLE_ID) ACCSS_CNT '+#13#10+
      'FROM   TABL$_MENU MNU, TABL$_MENU_ACCS MA '+#13#10+
      'WHERE  (MNU.MENUS_ID  = '+a_MenusId+') '+#13#10+
      '  AND  (MNU.PARENT_ID = '+IntToStr(ParentId)+') '+#13#10+
      '  AND  (MA.MENU_ID    = MNU.ID) '+#13#10+
      '  AND  (MA.ROLE_ID IN (SELECT UA.ROLE_ID FROM TABL$_USERS_ACCS UA '+
                             'WHERE(UA.USER_ID = '''+a_UserName+'''))) '+#13#10+
      'GROUP BY MNU.GROUP_INDEX,MNU.ID,MNU.NAME,MNU.PARENT_ID,MNU.SHORTCUT,'+
        'MNU.IMAGE_INDEX, MNU.SCRIPT_NAME, CHILD_COUNT ';
    FBQuery.SQL.Text := sql;
    //Dialogs.MessageDlg(FBQuery.SQL.Text, mtInformation, [mbOk]);
    FBQuery.Open;
    if not FBQuery.Active then exit;
    FBQuery.FetchAll;
    FBQuery.First;
    LastLeft := 0;
    while not FBQuery.EOF do
      begin
      if(a_UsePolicy and not(FBQuery.FieldByName('ACCSS_CNT').AsInteger > 0))then
        begin
        FBQuery.Next;
        continue;
        end;
      aCapt := FBQuery.FieldByName('NAME').AsString;
      mi := CreateMenuItem(ParentItem, aCapt, 
              FBQuery.FieldByName('SHORTCUT').AsString,
              FBQuery.FieldByName('ID').AsInteger, 
              FBQuery.FieldByName('IMAGE_INDEX').AsInteger, 
              FBQuery.FieldByName('GROUP_INDEX').AsInteger
            );
      if FBQuery.FieldByName('CHILD_COUNT').AsInteger>0 then
        BuildMenuItems(a_MenusId, a_UserName, a_UsePolicy, mi, 
          FBQuery.FieldByName('ID').AsInteger)
       else
        mi.OnClick  := @MenuItem_OnClick;
      Amunhotep_MainForm_xcMenu.AssignMethods(mi);
      FBQuery.Next;
      end;
    if FBQuery.Active then
      FBQuery.Close;
    FBTrans.Free;
  end;
  //============================================================================
