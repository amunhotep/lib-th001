{$DEFINE PEAKTOP:OBJ/DBINTERFACE/INTF.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                {$I PEAKTOP:GLOBAL_VARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                  {$I PEAKTOP:GLOBAL_OBJECTS.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/DBINTERFACE/GLOBALVARIABLES.INC} {$I ./GLOBALVARIABLES.INC}        {$ENDIF}
  //=============== PEAKTOP:OBJ/DBINTERFACE/INTF.INC ===========================
  procedure DBInterfaceCreate_Intf(aOwner, aParent, aDataSource :TObject; const aDataField, aFieldType :string; const aReadOnly:Boolean);
  begin
    GlobalObjects_Add(DBINTERFACE_OBJNAME_OWNER     ,aOwner     );
    GlobalObjects_Add(DBINTERFACE_OBJNAME_PARENT    ,aParent    );
    GlobalObjects_Add(DBINTERFACE_OBJNAME_DATASOURCE,aDataSource);
    SetGlobalVariable(DBINTERFACE_DATAFIELD         ,aDataField );
    SetGlobalVariable(DBINTERFACE_DATAFIELDTYPE     ,aFieldType );
    if aReadOnly then
      SetGlobalVariable(DBINTERFACE_READONLY        ,'1'        )
     else 
      SetGlobalVariable(DBINTERFACE_READONLY        ,'0'        );
    call('PEAKTOP:OBJ/DBINTERFACE/DEFAULT.PS');
  end;  
