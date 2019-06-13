{$DEFINE PEAKTOP:APPL/MANAGE/START/PARAMS/CREATE.INC}
{$IFNDEF PEAKTOP:APPL/CONFIGFILENAMES.INC}         {$I ../../../CONFIGFILENAMES.INC}  {$ENDIF}
  //============= PEAKTOP:APPL/MANAGE/START/PARAMS/CREATE.INC ==================
  function Amunhotep_StartParams_Create(const aConfigFileName:string):Boolean;
  begin
    Result := false;
    with TStringList.Create do
      begin
      Clear;
      Add('1'+AmunhotepFileConfigDelimiter+'REPORT'+AmunhotepFileConfigDelimiter+'Предварительный просмотр отчета'+AmunhotepFileConfigDelimiter+'PEAKTOP:APPL/PREVIEW_REPORT.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'EDITOR'+AmunhotepFileConfigDelimiter+'Редактор кода'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/DEVELOPMENT/MAINMENU/FILE_OPEN_PARAM.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'IDEERP'+AmunhotepFileConfigDelimiter+'Среда разработки ERP-систем'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/ERP/IDE.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'DATABASE'+AmunhotepFileConfigDelimiter+'Открыть базу данных с диска в ERP-среде'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/ERP/DATABASE/CONNECTPARAM.PS');
      StringsSaveToFile(aConfigFileName, Text);
      Free;
      end;
  end;
