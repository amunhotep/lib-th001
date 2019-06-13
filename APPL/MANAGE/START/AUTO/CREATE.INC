{$DEFINE PEAKTOP:APPL/MANAGE/START/AUTO/CREATE.INC}
{$IFNDEF PEAKTOP:APPL/CONFIGFILENAMES.INC}         {$I ../../../CONFIGFILENAMES.INC}  {$ENDIF}
  //============= PEAKTOP:APPL/MANAGE/START/AUTO/CREATE.INC ====================
  function Amunhotep_StartAuto_Create(const aConfigFileName:string):Boolean;
  begin
    Result := false;
    with TStringList.Create do
      begin
      Clear;
      Add('1'+AmunhotepFileConfigDelimiter+'10'+AmunhotepFileConfigDelimiter+'Checking application folders'+AmunhotepFileConfigDelimiter+'PEAKTOP:APPL/FILEPROCESS/CHECKFOLDERS.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'20'+AmunhotepFileConfigDelimiter+'Load images to main imagelist'+AmunhotepFileConfigDelimiter+'PEAKTOP:APPL/LOADIMAGELIST.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'22'+AmunhotepFileConfigDelimiter+'Load custom colors to core'+AmunhotepFileConfigDelimiter+'PEAKTOP:APPL/LOADCOLORS.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'40'+AmunhotepFileConfigDelimiter+'Overloading file processing methods'+AmunhotepFileConfigDelimiter+'PEAKTOP:APPL/FILEPROCESS/DEFAULT.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'50'+AmunhotepFileConfigDelimiter+'Overloading error handler'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/DEVELOPMENT/CORE/ERRORS/DEFAULT.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'60'+AmunhotepFileConfigDelimiter+'Script editor extensions'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/DEVELOPMENT/EDITOR/DEFAULT.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'70'+AmunhotepFileConfigDelimiter+'Visual designer extensions'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/DEVELOPMENT/DESIGNER/DEFAULT.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'80'+AmunhotepFileConfigDelimiter+'Object inspector extensions'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/DEVELOPMENT/OBJECTINSPECTOR/DEFAULT.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'90'+AmunhotepFileConfigDelimiter+'Overloading standard Firebird dialogs'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/FIREBIRD/DIALOGS/AMUNHOTEP.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'95'+AmunhotepFileConfigDelimiter+'Create basic main menu of application'+AmunhotepFileConfigDelimiter+'PEAKTOP:IDE/MAINMENU.PS');
      Add('1'+AmunhotepFileConfigDelimiter+'99'+AmunhotepFileConfigDelimiter+'Create clock'+AmunhotepFileConfigDelimiter+'PEAKTOP:APPL/MANAGE/START/AUTO/CLOCK.PS');
      StringsSaveToFile(aConfigFileName, Text);
      Free;
      end;
    Result := true;
  end;
