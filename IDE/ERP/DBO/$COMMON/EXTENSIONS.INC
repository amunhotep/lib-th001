{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                    {$I PEAKTOP:GLOBAL_VARIABLES.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                      {$I PEAKTOP:GLOBAL_OBJECTS.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}             {$I ../OBJECTNAMES.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC}  {$I ./FORMERP_HEADER.INC}            {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/$COMMON/EXTENSIONS.INC ==============
  function ERP_ObjectExtension_FileExists(const aObjId :string; const aObjType:Integer):Boolean;
  var
    lkFilePath :string;
  begin
    Result := false;
    lkFilePath := aObjId;
    if( (Pos('TABL$', lkFilePath) = 1) or (Pos('VIEW$', lkFilePath) = 1) or (Pos('PROC$', lkFilePath) = 1))then 
      Delete(lkFilePath, 1, 7);
    if( (aObjType = ERP_OBJECTTYPE_DOC) or (aObjType = ERP_OBJECTTYPE_JRNL) )then  
      lkFilePath := 'PEAKTOP:IDE/ERP/DBO/'+ERP_ObjectDir(aObjType)+'EXTS/'+IntToStr(ERP_OBJECTTYPE_DOC)+'/DEFAULT.PS'
     else
      lkFilePath := 'PEAKTOP:IDE/ERP/DBO/'+ERP_ObjectDir(aObjType)+'EXTS/'+lkFilePath+'/DEFAULT.PS';
    Result := FileExists( PrepareAbsoleteFileName(lkFilePath) );  
  end;
  //============================================================================
  function ERP_ObjectExtension_FilePath(aOwner:TComponent):string;
  var
    lkBaseType :Integer;
  begin
    lkBaseType := StrToInt(TERPForm_Settings(aOwner).Values[ERP_SETTINGS_BASETYPE]);
    Result := TERPForm_Settings(aOwner).Values[ERP_SETTINGS_TABLENAME];
    if( (Pos('TABL$', Result) = 1) or (Pos('VIEW$', Result) = 1) or (Pos('PROC$', Result) = 1))then 
      Delete(Result, 1, 7);
    if( (lkBaseType = ERP_OBJECTTYPE_DOC) or (lkBaseType = ERP_OBJECTTYPE_JRNL) )then  
      Result := 'PEAKTOP:IDE/ERP/DBO/'+ERP_ObjectDir(lkBaseType)+'EXTS/'+TERPForm_Settings(aOwner).Values[ERP_SETTINGS_DOCTYPE]+'/DEFAULT.PS'
     else
      Result := 'PEAKTOP:IDE/ERP/DBO/'+ERP_ObjectDir(lkBaseType)+'EXTS/'+Result+'/DEFAULT.PS';
  end;
  //============================================================================
  procedure ERP_ObjectExtension_CallScript(aOwner, aParent, aDataSet:TComponent; const aScriptName:string);
  var
    lkFileName :string;
  begin
    lkFileName := PrepareAbsoleteFileName( aScriptName );
    if not FileExists(lkFileName)then exit;
    GlobalObjects_Add(ERP_GLOBALVARIABLE_EXTENSION_OBJOWNER  ,aOwner  );
    GlobalObjects_Add(ERP_GLOBALVARIABLE_EXTENSION_OBJPARENT ,aParent );
    GlobalObjects_Add(ERP_GLOBALVARIABLE_EXTENSION_OBJDATASET,aDataSet);
    call(lkFileName);
  end;
  //============================================================================
  procedure ERP_ObjectExtension_Call(aOwner, aParent, aDataSet:TComponent);
  begin
    ERP_ObjectExtension_CallScript(aOwner, aParent, aDataSet, ERP_ObjectExtension_FilePath(aOwner) );
  end;
  //============================================================================
  function ERP_ObjectExtension_GetObjects(var aOwner, aParent, aDataSet:TComponent):Boolean;
  var
    lkObj :TObject;
  begin
    Result := false;
    lkObj := GlobalObjects_Find(ERP_GLOBALVARIABLE_EXTENSION_OBJOWNER);
      if(lkObj = nil)then exit;
      if not ObjectInheritsFrom(lkObj,'TComponent' )then exit; aOwner   := TComponent(lkObj);
    lkObj := GlobalObjects_Find(ERP_GLOBALVARIABLE_EXTENSION_OBJPARENT);
      if(lkObj = nil)then exit;
      if not ObjectInheritsFrom(lkObj,'TWinControl')then exit; aParent  := TComponent(lkObj);
    lkObj := GlobalObjects_Find(ERP_GLOBALVARIABLE_EXTENSION_OBJDATASET);
      if(lkObj = nil)then exit;
      if not ObjectInheritsFrom(lkObj,'TDataSet'   )then exit; aDataSet := TComponent(lkObj);
    GlobalObjects_Delete(ERP_GLOBALVARIABLE_EXTENSION_OBJOWNER  );
    GlobalObjects_Delete(ERP_GLOBALVARIABLE_EXTENSION_OBJPARENT );
    GlobalObjects_Delete(ERP_GLOBALVARIABLE_EXTENSION_OBJDATASET);
    Result := true;
  end;  
