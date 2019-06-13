{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/INTF_DATAVIEW.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                        {$I PEAKTOP:GLOBAL_VARIABLES.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:GLOBAL_OBJECTS.INC}                          {$I PEAKTOP:GLOBAL_OBJECTS.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/DATAVIEW_GLOBALVARIABLES.INC}{$I ./DATAVIEW_GLOBALVARIABLES.INC} {$ENDIF}
  //=================== PEAKTOP:IDE/ERP/DBO/DOC/INTF_DATAVIEW.INC ==============
  procedure DocDataIntf_Create(aOwner:TComponent; aParent :TWinControl; const aMasterTableName:string;aMasterTransaction:TxFBTransaction; aMasterDataSource:TDataSource; aQr:TxFBQuery);
  begin
    GlobalObjects_Add(ERP_GLOBALVARIABLE_DOC_DATAVIEW_OBJOWNER      ,aOwner);
    GlobalObjects_Add(ERP_GLOBALVARIABLE_DOC_DATAVIEW_OBJPARENT     ,aParent);
    GlobalObjects_Add(ERP_GLOBALVARIABLE_DOC_DATAVIEW_OBJTRANSACTION,aMasterTransaction);
    GlobalObjects_Add(ERP_GLOBALVARIABLE_DOC_DATAVIEW_OBJDATASOURCE ,aMasterDataSource);
    GlobalObjects_Add(ERP_GLOBALVARIABLE_DOC_DATAVIEW_QUERY         ,aQr);
    SetGlobalVariable(ERP_GLOBALVARIABLE_DOC_DATAVIEW_MASTERTABLE   ,aMasterTableName);
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/DOC/DATAVIEW.PS'));
  end;
