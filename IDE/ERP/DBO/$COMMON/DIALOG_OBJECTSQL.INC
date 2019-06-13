{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_OBJECTSQL.INC}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                    {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                         {$I PEAKTOP:OBJ/TXCTABSHEET.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}              {$I PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}             {$I ../$COMMON/FORMERP.INC}                  {$ENDIF}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_OBJECTSQL.INC ==============
const
  ERP_OBJNAME_OPER_DLG_SQL = 'DLG_SQL';
  procedure ERP_DialogSQL_Execute(aDataSet :TxFBCustomDataSet);
  var
    lkForm  :TForm;
    lkPC    :TxcPageControlEx; 
    lkTS    :TxcTabSheet;
    i       :Integer;
    lkII    :array[0..4]of Integer;
    lkCapts :array[0..4]of string;
    lkStr   :string;
  begin
    lkII[0] := 103; lkCapts[0] := 'SELECT';
    lkII[1] := 170; lkCapts[1] := 'REFRESH';
    lkII[2] := 176; lkCapts[2] := 'INSERT';
    lkII[3] := 175; lkCapts[3] := 'UPDATE';
    lkII[4] := 177; lkCapts[4] := 'DELETE';
    lkForm := TERPForm_Create('SQL  '+aDataSet.Name+' :'+aDataSet.ClassName,'PEAKTOP:IMG/CONFIG/MIME/SQL0016X0016.ICO','PEAKTOP:IMG/CONFIG/MIME/SQL0032X0032.BMP', true, nil);
    with lkForm do
      begin
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderIcons     := [biSystemMenu];
      AlphaBlendValue := 232;
      AlphaBlend      := true;
      Position        := poDesigned;
      Font.Size       := 7;
      end;
    TForm_Position_Load(lkForm, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLG_SQL,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))), 400, 300);  
    TAction(lkForm.FindComponent(obj_name_erp_actok)).Visible := false;  
    lkPC := CreateTxcPageControlEx(lkForm, lkForm, '', 0,0,200,200, alClient);
    for i:=0 to 4 do
      begin
      lkTS := CreateTxcTabSheet(lkPC, 'TS'+FormatFloat('000',i), lkCapts[i], lkII[i], Amunhotep.MainForm.StyleManager.Colors.Window);
      RegisterSynEdit(Interface_SynEdit_Create(lkForm, lkTS, 'SynEdit'+FormatFloat('000',i)), ftSQL);
      end;
    TxcPageControlEx_ActivateDefaultPage(lkPC);  
    if ObjectInheritsFrom(aDataSet, 'TxFBDataSet')then
      with TxFBDataSet(aDataSet) do
        begin  
        lkStr := 'PARAMS: '+SQLCRLF;
        if(Params.Count > 0)then
          for i:=0 to Params.Count-1 do
            lkStr := lkStr + '  '+Params[i].Name+' = "'+Params[i].AsString+'" '+SQLCRLF;  
        TSynEdit(lkForm.FindComponent('SynEdit000')).Text := SelectSQL.Text+SQLCRLF+SQLCRLF+lkStr;    
        TSynEdit(lkForm.FindComponent('SynEdit001')).Text := RefreshSQL.Text;    
        TSynEdit(lkForm.FindComponent('SynEdit002')).Text := InsertSQL.Text;    
        TSynEdit(lkForm.FindComponent('SynEdit003')).Text := ModifySQL.Text;    
        TSynEdit(lkForm.FindComponent('SynEdit004')).Text := DeleteSQL.Text;
        end
     else
      if ObjectInheritsFrom(aDataSet, 'TxFBQuery')then
        with TxFBQuery(aDataSet) do
          begin  
          lkStr := 'PARAMS: '+SQLCRLF;
          if(Params.Count > 0)then
            for i:=0 to Params.Count-1 do
              lkStr := lkStr + '  '+Params[i].Name+' = "'+Params[i].AsString+'" '+SQLCRLF;  
          TSynEdit(lkForm.FindComponent('SynEdit000')).Text := SQL.Text+SQLCRLF+SQLCRLF+lkStr;    
          end;
    lkForm.ShowModal;
    TForm_Position_Save(lkForm, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLG_SQL,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))));
    lkForm.Free;
  end;
