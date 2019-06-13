{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REG.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REF.INC}  {$I ../DBGRID/GETCELLPARAMS_REF.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC} {$I ../DBGRID/GETCELLPARAMS_JRNL.INC} {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REG.INC ===========
  procedure ERP_DBGridEh_OnGetCellParams_Reg(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
   if(Column.Tag = 666)then exit;
   if(not(Column.Field.DataSet.Active))then exit;
   if(Column.Field.DataSet.RecordCount = 0)then exit;
   if(Pos('J_', UpperCase(Column.FieldName)) = 1)then
     ERP_DBGridEh_OnGetCellParams_Jrnl(Sender, Column, AFont, Background, State)
    else 
     ERP_DBGridEh_OnGetCellParams_Ref(Sender, Column, AFont, Background, State);
  end;  
