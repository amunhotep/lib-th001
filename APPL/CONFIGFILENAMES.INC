{$DEFINE PEAKTOP:APPL/CONFIGFILENAMES.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}     {$I PEAKTOP:GLOBAL_VARIABLES.INC}     {$ENDIF}
const
  AmunhotepFileConfigDelimiter = '|';
  AmunhotepFileNameStartAuto   = '../conf/amunhotep_startauto.conf';
  AmunhotepFileNameStartParams = '../conf/amunhotep_startparams.conf';
  AmunhotepFileNameVisualStyle = '../conf/amunhotep_visualstyle.conf';
  //============================================================================
  function AmunhotepFileNameStartAutoGet:string;
  begin
    Result := PrepareFileNameOS(StrAbsolutePath(AmunhotepFileNameStartAuto, Amunhotep.ExeName));
  end;
  //============================================================================
  function AmunhotepFileNameStartParamsGet:string;
  begin
    Result := PrepareFileNameOS(StrAbsolutePath(AmunhotepFileNameStartParams, Amunhotep.ExeName));
  end;
  //============================================================================
  function AmunhotepFileNameVisualStyleGet:string;
  begin
    Result := PrepareFileNameOS(StrAbsolutePath(AmunhotepFileNameVisualStyle, Amunhotep.ExeName));
  end;  
