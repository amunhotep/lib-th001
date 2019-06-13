{$DEFINE PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}          {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/FILENAMES.INC}     {$I ./FILENAMES.INC}               {$ENDIF}
const //================== PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC =================
  ERP_OBJECTTYPES_COUNT = 20;
  ERP_OBJECTTYPES_OFFSET= 10;                            ERP_GUID_CONFIGURATOR = '{B5A809C9-E95C-41E5-90B3-41B436DFE13F}';
  ERP_OBJECTTYPE_UNKN   =  0; ERP_OBJECTTYPE_UNKNS = 10; ERP_GUID_NONE         = '{00000000-0000-0000-0000-000000000000}';
  ERP_OBJECTTYPE_ATTR   =  1; ERP_OBJECTTYPE_ATTRS = 11; ERP_GUID_DOCUMENT     = '{83BCC358-B3DE-421A-8B89-346A979C3F91}';
  ERP_OBJECTTYPE_REF    =  2; ERP_OBJECTTYPE_REFS  = 12; ERP_GUID_REFERENCE    = '{4BCB4BD7-D9F9-4340-A973-F21D22CAF427}';
  ERP_OBJECTTYPE_OPER   =  3; ERP_OBJECTTYPE_OPERS = 13; ERP_GUID_OPERATION    = '{41D83B1B-8578-46C7-B0C0-D4325572264D}';
  ERP_OBJECTTYPE_DOC    =  4; ERP_OBJECTTYPE_JRNL  = 14; ERP_GUID_JOURNAL      = '{6CD60C96-5C82-471D-8782-87C5AD19C899}';
  ERP_OBJECTTYPE_RPT    =  5; ERP_OBJECTTYPE_RPTS  = 15; ERP_GUID_REPORT       = '{8750BC1C-4754-4EAB-8B8E-825CA1A40B2E}';
  ERP_OBJECTTYPE_REG    =  6; ERP_OBJECTTYPE_REGS  = 16; ERP_GUID_REGISTRY     = '{C0CACDB0-3390-47A5-8A52-75832FF904B4}';
  ERP_OBJECTTYPE_ROLE   =  7; ERP_OBJECTTYPE_ROLES = 17; ERP_GUID_ROLE         = '{D65E72AC-C9F3-4205-9C32-D3A2C5A0D34E}';
  ERP_OBJECTTYPE_USER   =  8; ERP_OBJECTTYPE_USERS = 18; ERP_GUID_USER         = '{71BC3134-AF4B-41F2-A317-ADBC4C2A7184}';
  ERP_OBJECTTYPE_MENU   =  9; ERP_OBJECTTYPE_MENUS = 19; ERP_GUID_MENU         = '{6D8E9C12-9AC5-46FE-8125-BBEB73B533CE}';
const
  ERP_SETTINGS_TABLENAME          = 'DATASET_TABLENAME';
  ERP_SETTINGS_TABLECAPTION       = 'DATASET_CAPTION';
  ERP_SETTINGS_BOOKMARK           = 'DATASET_BOOKMARK';
  ERP_SETTINGS_DATAMEMORY         = 'DATASET_INMEMORY';
  ERP_SETTINGS_SAVERECNO          = 'DATASET_SAVERECNO';
  ERP_SETTINGS_GOTOVAR            = 'DATASET_GOTO_VARIABLE';
  ERP_SETTINGS_FLAGHISTORY        = 'DATASET_FLAGHISTORY'; 
  ERP_SETTINGS_BUFFERVAR          = 'DATASET_BUFFER_VARIABLE';
  ERP_SETTINGS_TYPESLIST          = 'DATASET_TYPESLIST';
  ERP_SETTINGS_BASETYPE           = 'DATASET_BASETYPE';
  ERP_SETTINGS_DOCTYPE            = 'DATASET_DOCTYPE';
  ERP_SETTINGS_REGMOVE            = 'DATASET_REGMOVE';
  ERP_SETTINGS_TEMPFILENAME       = 'TEMPFILENAME';
  ERP_SETTINGS_ITEM_SCRIPT        = 'ITEM_SCRIPT';
  ERP_SETTINGS_ITEM_SCRIPTDLG     = 'ITEM_DIALOG';
  ERP_SETTINGS_REF_TREE           = 'REFERENCE_TREE';
  ERP_SETTINGS_REF_TREEORGROUP    = 'REFERENCE_TREEORGROUP';
  ERP_SETTINGS_REF_TREEFIELD      = 'REFERENCE_TREEFIELD';
  ERP_SETTINGS_FOOTERCOUNT        = 'DATASET_FOOTERROWCOUNT';
  ERP_DATASET_DBKEY               = 'DS$ID';
  ERP_SQL_TABLEPREFIX             = 'R';
  ERP_SQL_RELATIONPREFIX          = 'T';
  ERP_SQL_DETAILPREFIX            = 'D';
  ERP_SQL_FIELDFORMAT             = '0000';
  ERP_SQL_FIELDPREFIX             = 'Q';
  ERP_SQL_FIELDSUFFIX             = '_';
  ERP_SQL_GOTO_SUFFIX             = '_GOTO';
  ERP_SQL_RECORDPACKETCOUNT       = 100;
  ERP_SQL_FIELDINDENT             = 'INDENT';
  ERP_SQL_FIELDDATEFROM           = 'DATE_FROM';
  ERP_SQL_FIELDDATETO             = 'DATE_TO';
  ERP_SQL_FIELD_IMAGES            = 'HASIMAGES';
  ERP_SQL_PERIODICALDATEFIELD     = 'VALUE_DATE';
  ERP_SQL_CURRENT_QUERY           = 'CURRENT_QUERY';
  ERP_GLOBALVARIABLE_FILIAL_ID            = 'FILIAL_ID_DEFAULT';
  ERP_GLOBALVARIABLE_OBJ_ID               = 'ERP_GLOBALVARIABLE_OBJ_ID';
  ERP_GLOBALVARIABLE_REC_ID               = 'ERP_GLOBALVARIABLE_REC_ID';
  ERP_GLOBALVARIABLE_EXTENSION_OBJOWNER   = 'ERP_GLOBALVARIABLE_EXTENSION_OBJOWNER';
  ERP_GLOBALVARIABLE_EXTENSION_OBJPARENT  = 'ERP_GLOBALVARIABLE_EXTENSION_OBJPARENT';
  ERP_GLOBALVARIABLE_EXTENSION_OBJDATASET = 'ERP_GLOBALVARIABLE_EXTENSION_OBJDATASET';  
{$IFDEF MSWINDOWS}SQLCRLF         = #13#10;{$ENDIF}
{$IFDEF LINUX}    SQLCRLF         = #13;   {$ENDIF} 
var
  ERP_SETTINGS_REF_LITERA :Char;
  //============================================================================
  function ERP_ObjectName(const aID :Integer):string;
  begin // Important ! This function must returns pascal name of object.
    Result := 'Unknown';
    case aID of
      ERP_OBJECTTYPE_ATTR :Result := 'Domain';
      ERP_OBJECTTYPE_REF  :Result := 'Reference';
      ERP_OBJECTTYPE_OPER :Result := 'Operation';
      ERP_OBJECTTYPE_DOC  :Result := 'Document';
      ERP_OBJECTTYPE_JRNL :Result := 'Journal';
      ERP_OBJECTTYPE_RPT  :Result := 'Report';
      ERP_OBJECTTYPE_REG  :Result := 'Registry';
      ERP_OBJECTTYPE_ROLE :Result := 'Role';
      ERP_OBJECTTYPE_USER :Result := 'User';
      ERP_OBJECTTYPE_MENU :Result := 'Menu';
      else                 Result := 'Unknown';
    end;
  end;
  //============================================================================
  function ERP_ObjectCaptions(const aID :Integer):string;
  begin
    Result := 'Неизвестно';
    case aID of
      ERP_OBJECTTYPE_ATTR :Result := 'Аттрибуты';
      ERP_OBJECTTYPE_REF  :Result := 'Справочники';
      ERP_OBJECTTYPE_OPER :Result := 'Операции';
      ERP_OBJECTTYPE_DOC  :Result := 'Документы';
      ERP_OBJECTTYPE_JRNL :Result := 'Журналы';
      ERP_OBJECTTYPE_RPT  :Result := 'Отчеты';
      ERP_OBJECTTYPE_REG  :Result := 'Регистры';
      ERP_OBJECTTYPE_ROLE :Result := 'Роли';
      ERP_OBJECTTYPE_USER :Result := 'Пользователи';
      ERP_OBJECTTYPE_MENU :Result := 'Меню';
      else                 Result := 'Неизвестно';
    end;
  end;
  //============================================================================
  function ERP_ObjectCaption(const aID :Integer):string;
  begin
    Result := 'Неизвестно';
    case aID of
      ERP_OBJECTTYPE_ATTR :Result := 'Аттрибут';
      ERP_OBJECTTYPE_REF  :Result := 'Справочник';
      ERP_OBJECTTYPE_OPER :Result := 'Операция';
      ERP_OBJECTTYPE_DOC  :Result := 'Документ';
      ERP_OBJECTTYPE_JRNL :Result := 'Журнал';
      ERP_OBJECTTYPE_RPT  :Result := 'Отчет';
      ERP_OBJECTTYPE_REG  :Result := 'Регистр';
      ERP_OBJECTTYPE_ROLE :Result := 'Роль';
      ERP_OBJECTTYPE_USER :Result := 'Пользователь';
      ERP_OBJECTTYPE_MENU :Result := 'Меню';
      else                 Result := 'Неизвестно';
    end;
  end;
  //============================================================================
  function ERP_ObjectCaptionItem(const aID :Integer):string;
  begin
    case aID of
      ERP_OBJECTTYPE_REF  :Result := 'Элемент';
      ERP_OBJECTTYPE_DOC  :Result := 'Документ';
      ERP_OBJECTTYPE_JRNL :Result := 'Документ';
      ERP_OBJECTTYPE_REG  :Result := 'Запись';
      else                 Result := ERP_ObjectCaption(aID);
    end;
  end;
  //============================================================================
  function ERP_FolderObjectCaptions(const aID :Integer):string;
  begin
    Result := ERP_ObjectCaptions(aID);
  end;
  //============================================================================
  function ERP_FolderObjectCaption(const aID :Integer):string;
  begin
    Result := ERP_FolderObjectCaptions(aID);
    Delete(Result, Length(Result), 1);
    if(aID = 3)then Result := Result + 'я';
  end;
  //============================================================================
  function ERP_ObjectImageIndex(const aID :Integer):Integer;
  begin
    case aID of
      ERP_OBJECTTYPE_UNKN :Result  :=   0; ERP_OBJECTTYPE_UNKNS:Result  :=   0;
      ERP_OBJECTTYPE_ATTR :Result  := 403; ERP_OBJECTTYPE_ATTRS:Result  := 401;
      ERP_OBJECTTYPE_REF  :Result  :=  44; ERP_OBJECTTYPE_REFS :Result  :=  43;
      ERP_OBJECTTYPE_OPER :Result  :=  40; ERP_OBJECTTYPE_OPERS:Result  :=  39;
      ERP_OBJECTTYPE_DOC  :Result  :=  37; ERP_OBJECTTYPE_JRNL :Result  :=  42;
      ERP_OBJECTTYPE_RPT  :Result  :=  48; ERP_OBJECTTYPE_RPTS :Result  :=  47;
      ERP_OBJECTTYPE_REG  :Result  :=  46; ERP_OBJECTTYPE_REGS :Result  :=  45;
      ERP_OBJECTTYPE_ROLE :Result  := 244; ERP_OBJECTTYPE_ROLES:Result  := 244;
      ERP_OBJECTTYPE_USER :Result  := 191; ERP_OBJECTTYPE_USERS:Result  := 193;
      ERP_OBJECTTYPE_MENU :Result  := 446; ERP_OBJECTTYPE_MENUS:Result  := 520;
      else                 Result  :=   0;
    end;
  end;
  //============================================================================
  function ERP_ObjectColor(const aID :Integer):TColor;
  begin
    Result := Amunhotep.MainForm.StyleManager.Colors.Background;
    case aID of
      ERP_OBJECTTYPE_ATTR,ERP_OBJECTTYPE_ATTRS:Result := $000080;
      ERP_OBJECTTYPE_REF ,ERP_OBJECTTYPE_REFS :Result := $FF4040;
      ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPERS:Result := $BFFF80;
      ERP_OBJECTTYPE_DOC                      :Result := $FFA0A0;
      ERP_OBJECTTYPE_JRNL                     :Result := $FFBF00;
      ERP_OBJECTTYPE_RPT ,ERP_OBJECTTYPE_RPTS :Result := $8000BF;
      ERP_OBJECTTYPE_REG ,ERP_OBJECTTYPE_REGS :Result := $0000BF;
      ERP_OBJECTTYPE_ROLE,ERP_OBJECTTYPE_ROLES:Result := $0080FF;
      ERP_OBJECTTYPE_USER,ERP_OBJECTTYPE_USERS:Result := $008080;
      ERP_OBJECTTYPE_MENU,ERP_OBJECTTYPE_MENUS:Result := $BF0080;
    end;
  end;
  //============================================================================
  function ERP_ObjectColorLight(const aID :Integer):TColor;
  begin
    Result := ERP_ObjectColor(aID) or $A0A0A0;
  end;
  //============================================================================
  function ERP_ObjectDir(const aID :Integer):string;
  begin
    Result := '';
    case aID of
      ERP_OBJECTTYPE_REF ,ERP_OBJECTTYPE_REFS :Result := 'REF/';
      ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPERS:Result := 'OPER/';
      ERP_OBJECTTYPE_DOC ,ERP_OBJECTTYPE_JRNL :Result := 'DOC/';
      ERP_OBJECTTYPE_RPT ,ERP_OBJECTTYPE_RPTS :Result := 'RPTI/';
      ERP_OBJECTTYPE_REG ,ERP_OBJECTTYPE_REGS :Result := 'REG/';
      ERP_OBJECTTYPE_ROLE,ERP_OBJECTTYPE_ROLES:Result := 'ROLES/';
      ERP_OBJECTTYPE_USER,ERP_OBJECTTYPE_USERS:Result := 'USERS/';
      ERP_OBJECTTYPE_MENU,ERP_OBJECTTYPE_MENUS:Result := 'MENU/';
    end;
  end;
  //============================================================================
  function ERP_ObjectDirStructure(const aID :Integer):string;
  begin
    Result := ERP_DIRECTORY_SQLLOAD_STRUCTURE + ERP_ObjectDir(aID);
  end;
  //============================================================================
  function ERP_ObjectDBFolder(const aID :Integer):string;
  begin
    Result := 'DB:CONFIG/';
    case aID of
      ERP_OBJECTTYPE_REF  :Result:=Result+'REF/';
      ERP_OBJECTTYPE_OPER :Result:=Result+'OPER/';
      ERP_OBJECTTYPE_DOC  :Result:=Result+'DOC/';
      ERP_OBJECTTYPE_RPT  :Result:=Result+'RPTI/';
      ERP_OBJECTTYPE_REG  :Result:=Result+'REG/';
      ERP_OBJECTTYPE_ROLE :Result:=Result+'ROLE/';
      ERP_OBJECTTYPE_USER :Result:='DB:HOME/';
      ERP_OBJECTTYPE_REFS :Result:=Result+'REF/';
      ERP_OBJECTTYPE_OPERS:Result:=Result+'OPER/';
      ERP_OBJECTTYPE_JRNL :Result:=Result+'DOC/';
      ERP_OBJECTTYPE_RPTS :Result:=Result+'RPTI/';
      ERP_OBJECTTYPE_REGS :Result:=Result+'REG/';
      ERP_OBJECTTYPE_ROLES:Result:=Result+'ROLE/';
      ERP_OBJECTTYPE_USERS:Result:='DB:HOME/';
      else                 Result:='DB:TMP/';
    end;
  end;
  //============================================================================
  function ERP_ObjectTempFileName(const aBaseTypeId, aTypeId :Integer; const aObjId, aUserId:string):string;
  begin
    Result := 'TMP:';
    case aBaseTypeId of
      ERP_OBJECTTYPE_ATTR,ERP_OBJECTTYPE_ATTRS:Result := '';
      ERP_OBJECTTYPE_REF ,ERP_OBJECTTYPE_REFS :Result := 'TMP:'+ERP_FILENAME_CFG_DIALOG_REF+aObjId+'['+aUserId+'].CFG';
      ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPERS:Result := 'TMP:'+ERP_FILENAME_CFG_DIALOG_OPER+aObjId+'['+aUserId+'].CFG';
      ERP_OBJECTTYPE_DOC ,ERP_OBJECTTYPE_JRNL :Result := 'TMP:'+ERP_FILENAME_CFG_DIALOG_JRNL+IntToStr(aTypeId)+'['+aUserId+'].CFG';
      ERP_OBJECTTYPE_RPT ,ERP_OBJECTTYPE_RPTS :Result := 'TMP:'+ERP_FILENAME_CFG_DIALOG_RPTI+aObjId+'['+aUserId+'].CFG';
      ERP_OBJECTTYPE_REG ,ERP_OBJECTTYPE_REGS :Result := 'TMP:'+ERP_FILENAME_CFG_DIALOG_REG+aObjId+'['+aUserId+'].CFG';
      ERP_OBJECTTYPE_ROLE,ERP_OBJECTTYPE_ROLES:Result := '';
      ERP_OBJECTTYPE_USER,ERP_OBJECTTYPE_USERS:Result := '';
      ERP_OBJECTTYPE_MENU,ERP_OBJECTTYPE_MENUS:Result := '';
    end;
  end;
  //============================================================================
  function ERP_ObjectGUID(const aID :Integer):string;
  begin
    Result := ERP_GUID_NONE;
    case aID of
      ERP_OBJECTTYPE_REF  :Result := ERP_GUID_REFERENCE;
      ERP_OBJECTTYPE_OPER :Result := ERP_GUID_OPERATION;
      ERP_OBJECTTYPE_DOC  :Result := ERP_GUID_DOCUMENT;
      ERP_OBJECTTYPE_RPT  :Result := ERP_GUID_REPORT;
      ERP_OBJECTTYPE_REG  :Result := ERP_GUID_REGISTRY;
      ERP_OBJECTTYPE_JRNL :Result := ERP_GUID_JOURNAL;
      ERP_OBJECTTYPE_ROLE :Result := ERP_GUID_ROLE;
      ERP_OBJECTTYPE_USER :Result := ERP_GUID_USER;
      ERP_OBJECTTYPE_MENU :Result := ERP_GUID_MENU;
      else                 Result := ERP_GUID_NONE;
    end;
  end;
  //============================================================================
  function ERP_ObjectBitmap(const aID :Integer):string;
  begin
    Result := '';
    case aID of
      ERP_OBJECTTYPE_REF  :Result := ERP_FILENAME_BMP_REF;
      ERP_OBJECTTYPE_REFS :Result := ERP_FILENAME_BMP_REFS;
      ERP_OBJECTTYPE_OPER :Result := ERP_FILENAME_BMP_OPER;
      ERP_OBJECTTYPE_OPERS:Result := ERP_FILENAME_BMP_OPERS;
      ERP_OBJECTTYPE_DOC  :Result := ERP_FILENAME_BMP_DOC;
      ERP_OBJECTTYPE_JRNL :Result := ERP_FILENAME_BMP_JRNL;
      ERP_OBJECTTYPE_RPT  :Result := ERP_FILENAME_BMP_RPTI;
      ERP_OBJECTTYPE_RPTS :Result := ERP_FILENAME_BMP_RPTS;
      ERP_OBJECTTYPE_REG  :Result := ERP_FILENAME_BMP_REG;
      ERP_OBJECTTYPE_REGS :Result := ERP_FILENAME_BMP_REGS;
      ERP_OBJECTTYPE_MENU :Result := ERP_FILENAME_BMP_MENU;
      ERP_OBJECTTYPE_MENUS:Result := ERP_FILENAME_BMP_MENUS;
      ERP_OBJECTTYPE_ROLE :Result := ERP_FILENAME_BMP_ROLE;
      ERP_OBJECTTYPE_ROLES:Result := ERP_FILENAME_BMP_ROLES;
      ERP_OBJECTTYPE_USER :Result := ERP_FILENAME_BMP_USER;
      ERP_OBJECTTYPE_USERS:Result := ERP_FILENAME_BMP_USERS;
      else                 Result := ERP_FILENAME_BMP_DBGRID;
    end;
  end;
  //============================================================================
  function ERP_ObjectIcon(const aID :Integer):string;
  begin
    Result := '';
    case aID of
      ERP_OBJECTTYPE_REF  :Result := ERP_FILENAME_ICO_REF;
      ERP_OBJECTTYPE_REFS :Result := ERP_FILENAME_ICO_REFS;
      ERP_OBJECTTYPE_OPER :Result := ERP_FILENAME_ICO_OPER;
      ERP_OBJECTTYPE_OPERS:Result := ERP_FILENAME_ICO_OPERS;
      ERP_OBJECTTYPE_DOC  :Result := ERP_FILENAME_ICO_DOC;
      ERP_OBJECTTYPE_JRNL :Result := ERP_FILENAME_ICO_JRNL;
      ERP_OBJECTTYPE_RPT  :Result := ERP_FILENAME_ICO_RPTI;
      ERP_OBJECTTYPE_RPTS :Result := ERP_FILENAME_ICO_RPTS;
      ERP_OBJECTTYPE_REG  :Result := ERP_FILENAME_ICO_REG;
      ERP_OBJECTTYPE_REGS :Result := ERP_FILENAME_ICO_REGS;
      ERP_OBJECTTYPE_MENU :Result := ERP_FILENAME_ICO_MENU;
      ERP_OBJECTTYPE_MENUS:Result := ERP_FILENAME_ICO_MENUS;
      ERP_OBJECTTYPE_ROLE :Result := ERP_FILENAME_ICO_ROLE;
      ERP_OBJECTTYPE_ROLES:Result := ERP_FILENAME_ICO_ROLES;
      ERP_OBJECTTYPE_USER :Result := ERP_FILENAME_ICO_USER;
      ERP_OBJECTTYPE_USERS:Result := ERP_FILENAME_ICO_USERS;
      else                 Result := ERP_FILENAME_ICO_DBGRID;
    end;
  end;
  //============================================================================
  procedure ERP_ObjectHelp(const aObjectId :string; const aObjectType:Integer);
  begin
    run('{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/HELP.INC}{$I ./HELP.INC}{$ENDIF} '+SQLCRLF+
        'begin '+SQLCRLF+'  TERPFormOperHelp_Create('''', ''''); '+SQLCRLF+'end.'    
    ,'PEAKTOP:IDE/ERP/DBO/OPER/HELP.PS');
  end;
  //============================================================================
  procedure ERP_ObjectEditor(const aObjectId :string; const aObjectType:Integer);
  begin
    SetGlobalVariable(ERP_GLOBALVARIABLE_OBJ_ID, aObjectId);
    if FileExists(PrepareAbsoleteFileName(ERP_DIRECTORY_SCRIPTSDBO+ERP_ObjectDir(aObjectType)+'OBJECTEDITOR.PS')) then
      call(ERP_DIRECTORY_SCRIPTSDBO+ERP_ObjectDir(aObjectType)+'OBJECTEDITOR.PS')
     else
      Dialogs.MessageDlg('Файл не существует !'+SQLCRLF+PrepareAbsoleteFileName(ERP_DIRECTORY_SCRIPTSDBO+ERP_ObjectDir(aObjectType)+'OBJECTEDITOR.PS'),mtWarning, [mbOk]);   
  end;
  //============================================================================
  procedure ERP_ObjectWizard(const aObjectType:Integer);
  begin
    if FileExists(PrepareAbsoleteFileName(ERP_DIRECTORY_SCRIPTSDBO+ERP_ObjectDir(aObjectType)+'WIZARD.PS')) then
      call(ERP_DIRECTORY_SCRIPTSDBO+ERP_ObjectDir(aObjectType)+'WIZARD.PS')
     else
      Dialogs.MessageDlg('Файл не существует !'+SQLCRLF+PrepareAbsoleteFileName(ERP_DIRECTORY_SCRIPTSDBO+ERP_ObjectDir(aObjectType)+'WIZARD.PS'),mtWarning, [mbOk]);   
  end;
  //============================================================================
  function ERP_ObjectFolderTable(const aObjectType :Integer):string;
  begin
    Result := '';
    case aObjectType of
      ERP_OBJECTTYPE_REF, ERP_OBJECTTYPE_DOC , ERP_OBJECTTYPE_OPER,
      ERP_OBJECTTYPE_REG, ERP_OBJECTTYPE_JRNL, ERP_OBJECTTYPE_RPT , 
      ERP_OBJECTTYPE_ROLE: Result := 'TABL$_TB_TYPES';
      ERP_OBJECTTYPE_USER: Result := 'TABL$_USERS_GROUP';
      ERP_OBJECTTYPE_MENU: Result := 'PROC$_MENUS';
    end;
  end;
  //============================================================================
  function ERP_ObjectItemsSQL(const aObjectType :Integer; const aCurrentTypeId :string):string;
  begin
    Result := '';
    case aObjectType of
      ERP_OBJECTTYPE_REF, ERP_OBJECTTYPE_RPT, ERP_OBJECTTYPE_OPER,
      ERP_OBJECTTYPE_REG : Result := 'SELECT T.ID, T.NAME FROM TABL$_TB T WHERE (T.TYPE_ID = '''+aCurrentTypeId+''') ORDER BY T.NAME '; 
      ERP_OBJECTTYPE_DOC : Result := 'SELECT T.ID, T.NAME FROM TABL$_TB T WHERE (T.TYPE_ID = '''+aCurrentTypeId+''') AND (T.FLAG_MASTER = 0) ORDER BY T.NAME '; 
      ERP_OBJECTTYPE_JRNL: Result := 'SELECT T.ID, T.NAME FROM TABL$_TB T WHERE (T.TYPE_ID = '''+aCurrentTypeId+''') AND (T.FLAG_MASTER = 1) ORDER BY T.NAME ';
      ERP_OBJECTTYPE_ROLE: Result := 'SELECT R.ID, R.NAME FROM TABL$_USERS_ROLES R ORDER BY R.ID, R.NAME ';
      ERP_OBJECTTYPE_USER: Result := 'SELECT U.ID, IIF((TRIM(U.NAME)=''''),U.ID,U.NAME) AS NAME FROM TABL$_USERS U WHERE (U.GROUP_ID = '''+aCurrentTypeId+''') ORDER BY 2 ';
      ERP_OBJECTTYPE_MENU: Result := 
        'SELECT TMP.ID, TMP.NAME FROM ( '+SQLCRLF+
        '            SELECT M.NAME AS ID, M.DESCR AS NAME FROM TABL$_MENUS M WHERE (TRIM(M.NAME) = '''+aCurrentTypeId+''') '+SQLCRLF+
        '  UNION ALL SELECT M.NAME AS ID, M.DESCR AS NAME FROM TABL$_MENUS M WHERE (TRIM(M.NAME) IN (SELECT T.ID FROM TABL$_TB T WHERE (T.TYPE_ID = '''+aCurrentTypeId+'''))) '+SQLCRLF+
        '  UNION ALL SELECT M.NAME AS ID, M.DESCR AS NAME FROM TABL$_MENUS M WHERE ((M.ID = 1000000) AND (''-1'' = '''+aCurrentTypeId+''')) '+SQLCRLF+
        ')TMP ORDER BY 2 ';
    end;
  end;            
