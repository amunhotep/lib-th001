{$DEFINE PEAKTOP:APPL/LOCAL/FILE.INC}
{$IFNDEF PEAKTOP:APPL/LOCAL/PARAMS.INC} {$I PEAKTOP:APPL/LOCAL/PARAMS.INC}  {$ENDIF}          
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}  {$I PEAKTOP:GLOBAL_VARIABLES.INC}   {$ENDIF} 
  //================== PEAKTOP:APPL/LOCAL/FILE.INC =============================
  function AmunhotepLocalStringsLoad(aMessageList:TStringList; const aLocal, aFileName:string):Boolean;
  var
    lkLocal      :string;
    lkFileName   :string;
    lkMsgName    :string;
    lkMsgValue   :string;
    lkJSONLoader :TlkJSONstreamed;
    lkJSONObjRoot:TlkJSONbase;
    lkJSONListMsg:TlkJSONList;
    lkJSONObjMsg :TlkJSONObject;
    lkJSONList   :TlkJSONList;
    i, j         :Integer;
  begin
    Result := False;
    if(aMessageList = nil)then exit;
    aMessageList.Clear;
    lkFileName := PrepareAbsoleteFileName(aFileName);
    if not FileExists(lkFileName)then
      begin
      Dialogs.MessageDlg('File does not exists!'+#13#10+lkFileName, mtError, [mbOK]);
      exit;
      end;
    lkLocal := aLocal;
    if(StrTrimAll(aLocal) = '')then 
      lkLocal := AmunhotepLocalizeParamDefault; 
    try
      lkJSONLoader  := TlkJSONstreamed.Create;
      lkJSONObjRoot := lkJSONLoader.LoadFromFile( lkFileName );
    finally  
      lkJSONLoader.Free;
    end;  
    lkJSONListMsg := TlkJSONList( lkJSONObjRoot.Field[AmunhotepLocalizeSection] );
    for i:=0 to lkJSONListMsg.Count-1 do
      begin
      lkJSONObjMsg := TlkJSONObject( lkJSONListMsg.Child[i] );
      lkMsgName    := lkJSONObjMsg.Field[AmunhotepLocalizeParamName].Value;
      lkJSONList   := TlkJSONList( lkJSONObjMsg.Field[AmunhotepLocalizeParamCaption] );
      lkMsgValue   := '';
      for j:=0 to lkJSONList.Count-1 do
        if( lkLocal = lkJSONList.Child[j].Field[AmunhotepLocalizeParamLang].Value )then
          begin
          lkMsgValue := lkJSONList.Child[j].Field[AmunhotepLocalizeParamValue].Value;
          break;
          end;
      if(StrTrimAll(lkMsgValue) = '')then
        for j:=0 to lkJSONList.Count-1 do
          if( AmunhotepLocalizeParamDefault = lkJSONList.Child[j].Field[AmunhotepLocalizeParamLang].Value )then
            begin
            lkMsgValue := lkJSONList.Child[j].Field[AmunhotepLocalizeParamValue].Value;
            break;
            end;
      aMessageList.Add( AnsiUpperCase(lkMsgName) + '=' + lkMsgValue );  
      end;
    lkJSONObjRoot.Free; 
    Result := True; 
  end;
  //============================================================================
  function AmunhotepLocalString(aStrList:TStringList; const aMessageName, aDefaultValue:string):string;
  var
    lkMessageName:string;
  begin
    Result := aDefaultValue;
    if(aStrList = nil)then exit;
    lkMessageName := AnsiUpperCase(aMessageName);
    if(aStrList.IndexOfName(lkMessageName) > -1)then
      Result := aStrList.Values[lkMessageName];
  end;
