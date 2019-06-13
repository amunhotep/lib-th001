{$DEFINE PEAKTOP:APPL/LOCAL/VARIABLE.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}  {$I PEAKTOP:GLOBAL_VARIABLES.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:APPL/LOCAL/PARAMS.INC} {$I PEAKTOP:APPL/LOCAL/PARAMS.INC}  {$ENDIF}
  //====================== PEAKTOP:APPL/LOCAL/VARIABLE.INC =====================
const AMUNHOTEP_LOCAL_VARIABLE = 'DATABASE_LOCAL';
  //============================================================================
  procedure AmunhotepLocalSet(const aValue:string);
  begin
    SetGlobalVariable( AMUNHOTEP_LOCAL_VARIABLE, aValue);
  end;  
  //============================================================================
  function AmunhotepLocalGet:string;
  begin
    Result := GetGlobalVariable( AMUNHOTEP_LOCAL_VARIABLE );
    if( StrTrimAll(Result) = '')then
      begin
      Result := AmunhotepLocalizeParamDefault;
      AmunhotepLocalSet( Result );
      end;
  end;

  
  
