{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/RECENT.INC}
{$IFNDEF PEAKTOP:OBJ/TXCCHECKBOX.INC}                  {$I PEAKTOP:OBJ/TXCCHECKBOX.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}          {$I ../OBJECTNAMES.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I ../$COMMON/FORMERP.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/IMAGELISTCONFIG.INC}      {$I ../IMAGELISTCONFIG.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}{$I ../USERS/GLOBALVARIABLES.INC}             {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/OPER/MAPS.INC ========================
const 
  ERP_OBJNAME_OPER_RECENT       = 'RECENT';
  msg_opers_recent              = 'Последние действия пользователя';
  msg_opers_recent_show_onstart = 'Показывать это окно при входе в базу данных';
  erp_opers_recent_itesm_count  = 25;
  erp_opers_recent_show_onstart = 'SHOW_ON_START';
  //============================================================================
  procedure TERPFormOperRecent_cbxShowOnStart_OnClick(Sender :TObject);
  var
    lkFileName :string;
  begin
    with TxcCheckBox(Sender) do
      begin
      lkFileName := PrepareAbsoleteFileName(TERPForm_Settings(Owner).Values[ERP_SETTINGS_TEMPFILENAME]);
      with TStringList.Create do
        begin
        if FileExists(lkFileName)then
          Text := StringsLoadFromFile(lkFileName);
        if Checked then
          Values[erp_opers_recent_show_onstart] := '1'
         else 
          Values[erp_opers_recent_show_onstart] := '0';
        SaveToFile(lkFileName);  
        Free;
        end;
      end;
  end;
  //============================================================================
  procedure TERPFormOperRecent_CategoryButtons_OnButtonClicked(Sender: TObject; const Button: TButtonItem);
  begin
    call(Button.CaptionSmall);
  end;
  //============================================================================
  procedure TERPFormOperRecent_FillRecent(aOwner :TComponent);
  var
    lkCBTNS   :TCategoryButtons;
    lkTr      :TxFBTransaction;
    lkQr      :TxFBQuery;
    lkQrItems :TxFBQuery;
  begin
    lkCBTNS := TCategoryButtons(aOwner.FindComponent('CategoryButtons'));
    lkCBTNS.Categories.Clear;
    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBdataBase;
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
      SQL.Text := 'SELECT DISTINCT R.BASE_TYPE_ID FROM TABL$_USERS_RCNT R '+
        'WHERE (R.USER_ID = RDB$GET_CONTEXT(''USER_SESSION'', '''+ERP_GLOBALVARIABLE_USER_CURRENT+''')) AND (R.SUBTYPE = 0) '{+
          'AND (R.BASE_TYPE_ID < '+IntToStr(ERP_OBJECTTYPE_MENU)+') '};      
      end;
    lkQrItems := TxFBQuery.Create(lkTr);
    with lkQrItems do
      begin
      Transaction := lkTr;
      end;
    lkQr.Open;
    lkQr.First;
    while not lkQr.EOF do
      begin
      if lkQrItems.Active then
        lkQrItems.Close;
      lkQrItems.SQL.Text := 
        'SELECT FIRST '+IntToStr(erp_opers_recent_itesm_count)+' R.* '+SQLCRLF+
        'FROM   TABL$_USERS_RCNT R '+SQLCRLF+
        'WHERE  (R.USER_ID = RDB$GET_CONTEXT(''USER_SESSION'', '''+ERP_GLOBALVARIABLE_USER_CURRENT+''')) '+SQLCRLF+
        '  AND  (R.SUBTYPE = 0) '+SQLCRLF+
        '  AND  (R.BASE_TYPE_ID = '+lkQr.FieldByName('BASE_TYPE_ID').AsString+') '+SQLCRLF+
        'ORDER BY R.BASE_TYPE_ID ASCENDING, R.SCOPES DESCENDING, R.NAME ASCENDING';
      if not lkQrItems.Active then
        lkQrItems.Open;
      with lkCBTNS.Categories.Add do
        begin 
        ImageIndex    := lkQr.FieldByName('BASE_TYPE_ID').AsInteger + ERP_OBJECTTYPES_OFFSET;
        Caption       := ERP_ObjectCaptions(lkQr.FieldByName('BASE_TYPE_ID').AsInteger);
        Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
        GradientColor := ERP_ObjectColor(lkQr.FieldByName('BASE_TYPE_ID').AsInteger);
        TextColor     := Amunhotep.MainForm.StyleManager.Colors.Border;
        lkQrItems.First;
        while not lkQrItems.EOF do
          begin
          with Items.Add do
            begin
            Caption     := {'['+lkQrItems.FieldByName('SCOPES').AsString+'] '+}lkQrItems.FieldByName('NAME').AsString;
            CaptionSmall:= lkQrItems.FieldByName('SCRIPT_NAME').AsString;
            Hint        := lkQrItems.FieldByName('NAME').AsString+#13#10#13#10+
              'Использовалось '+lkQrItems.FieldByName('SCOPES').AsString+' раз'+#13#10+
              'Последний раз '+FormatDateTime('dd.mm.yyyy hh:nn', lkQrItems.FieldByName('DATE_LAST').AsDateTime);
            ImageIndex  := lkQrItems.FieldByName('BASE_TYPE_ID').AsInteger
            if(lkQrItems.FieldByName('BASE_TYPE_ID').AsInteger = ERP_OBJECTTYPE_DOC)then
              ImageIndex  := ImageIndex + ERP_OBJECTTYPES_OFFSET;
            end; 
          lkQrItems.Next;
          end;
        end;
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;  
  end;
  //============================================================================
  procedure TERPFormOperRecent_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end; 
  //============================================================================
  function TERPFormOperRecent_Create(const aModalForm :Boolean):TForm;
  var
    lkUSR    :string;
    lkCBTNS  :TCategoryButtons;
    lkCBX    :TxcCheckBox;
    lkChecked:Boolean;
  begin
    lkUSR := '';
    GetField(FBDataBase, 'TABL$_USERS', 'NAME', 'ID = '''+GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT)+''' ', lkUSR);
    Result := TERPForm_Create(msg_opers_recent+' '+lkUSR, ERP_ObjectIcon(ERP_OBJECTTYPE_OPERS), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPERS), aModalForm, @TERPFormOperRecent_OnClose);
    with Result do
      begin
      
      end;
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    with TERPForm_Settings(Result) do
      begin
      Values[ERP_SETTINGS_BUFFERVAR      ] := '';
      Values[ERP_SETTINGS_TABLENAME      ] := '';
      Values[ERP_SETTINGS_TABLECAPTION   ] := Result.Caption;
      Values[ERP_SETTINGS_BASETYPE       ] := IntToStr(ERP_OBJECTTYPE_OPER);
      Values[ERP_SETTINGS_TEMPFILENAME   ] := ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_RECENT,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT));
      end;
    lkCBTNS := TCategoryButtons.Create(Result);
    with lkCBTNS do
      begin
      Name                        := 'CategoryButtons';
      Parent                      := Result;
//      Clt3D                       := false;
      BorderStyle                 := bsNone;
      Align                       := alClient;
      BackgroundGradientColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
      BackgroundGradientDirection := gdRightToLeft; 
      ButtonFlow                  := cbfVertical;
      ButtonOptions               := [boGradientFill,boShowCaptions,boBoldCaptions,boUsePlusMinus,boCaptionOnlyBorder];
      Color                       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Name                   := 'Verdana';
      Font.Size                   := 10;//DefaultFirebirdDialogLabelFontHeight;
      Font.Style                  := [fsBold];
      GradientDirection           := gdTopToBottom;
      HotButtonColor              := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      RegularButtonColor          := clNone;
      SelectedButtonColor         := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      ShowHint                    := true;
      Images                      := CreateTImageListConfiguration(lkCBTNS, 'ilConfig');
      CategoryImages              := Images;
      ButtonHeight                := Images.Height + 4;
      ButtonWidth                 := Images.Height * 14 + 4;
      OnButtonClicked             := @TERPFormOperRecent_CategoryButtons_OnButtonClicked;
      end;
    TERPFormOperRecent_FillRecent(Result);
    lkChecked := true;
    if FileExists(PrepareAbsoleteFileName(TERPForm_Settings(Result).Values[ERP_SETTINGS_TEMPFILENAME]))then
      with TStringList.Create do
        begin
        Text := StringsLoadFromFile(PrepareAbsoleteFileName(TERPForm_Settings(Result).Values[ERP_SETTINGS_TEMPFILENAME]));
        lkChecked := (Values[erp_opers_recent_show_onstart] <> '0');
        Free;
        end;
    lkCBX := CreateTxcCheckBox(Result, Result, 'cbxShowOnStart', msg_opers_recent_show_onstart, msg_opers_recent_show_onstart, alBottom, 0,1000,24,400,lkChecked);
    with lkCBX do
      begin
      Font.Style := [fsBold];
      Font.Size  := 10;
      OnClick := @TERPFormOperRecent_cbxShowOnStart_OnClick;
      end; 
    if not aModalForm then
      Result.WindowState := wsMaximized; 
  end;
