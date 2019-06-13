{$DEFINE PEAKTOP:GLOBAL_VARIABLES.INC}       
  //================== PEAKTOP:GLOBAL_VARIABLES.INC ============================
  procedure SetGlobalVariable(const GlobalVariableName, GlobalVariableValue:string);
  var
    lkIndex :Integer;
  begin
    lkIndex := GlobalVariables.IndexOfName(UpperCase(GlobalVariableName));
    if(lkIndex > -1)then
      GlobalVariables.Values[UpperCase(GlobalVariableName)] := GlobalVariableValue
     else
      if(StrTrimAll(GlobalVariableName) <> '')then
        GlobalVariables.Add(UpperCase(GlobalVariableName) + '=' + GlobalVariableValue);
  end;
  //============================================================================
  function GetGlobalVariable(const GlobalVariableName:string):string;
  var
    lkIndex :Integer;
  begin
    Result := '';
    lkIndex := GlobalVariables.IndexOfName(UpperCase(GlobalVariableName));
    if(lkIndex > -1)then
      Result := GlobalVariables.Values[UpperCase(GlobalVariableName)]
     else
      if(StrTrimAll(GlobalVariableName) <> '')then
        SetGlobalVariable(GlobalVariableName, Result);
  end;
  //============================================================================
  function FormatErrorMessage(const LineNumber:string):string;
  begin
    Result := #13#10+#13#10+#13#10+'ScriptName: '+ScriptName+#13#10+'Line: '+LineNumber+#13#10;
  end;
  //============================================================================
  function PrepareFileNameOS(const aAbsoleteFileName:string):string;
  begin
  {$IFDEF MSWINDOWS}Result := StrReplaceStr(aAbsoleteFileName, '/', '\'); {$ENDIF}
  {$IFDEF LINUX}    Result := StrReplaceStr(aAbsoleteFileName, '\', '/'); {$ENDIF}
  end;
  //============================================================================
  function PrepareAbsoleteFileName(const aRelativeFileName:string):string;
  begin
    Result := aRelativeFileName;
    if(Pos('DB:',UpperCase(Result)) = 1)then exit;
    if(Pos('PEAKTOP:',UpperCase(Result)) = 1)then
      begin
      Delete(Result, 1, 8);
      Result := StrAbsolutePath('./'+Result, Amunhotep.SourcePath);
      end;
    if(Pos('TMP:',UpperCase(Result)) = 1)then
      begin
      Delete(Result, 1, 4);
      Result := StrAbsolutePath('../tmp/'+Result, Amunhotep.ExeName);
      end;
    Result := PrepareFileNameOS(Result);  
  end;
