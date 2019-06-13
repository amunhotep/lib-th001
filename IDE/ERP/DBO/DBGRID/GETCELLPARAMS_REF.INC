{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REF.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC}      {$I ./COL_PROTOCOL.INC}  {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REF.INC ===========
  procedure ERP_DBGridEh_OnGetCellParams_Ref(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
   if(Column.Tag = 666)then exit;
   if(not(Column.Field.DataSet.Active))then exit;
   if(Column.Field.DataSet.RecordCount = 0)then exit;
   if(Column.Field.DataSet.FindField('FLAG_DELETE') <> nil)then
     begin
     if(Column.Field.DataSet.FieldByName('FLAG_DELETE').AsInteger = 0)then 
       aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Border
      else
       aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Background;
     end;
    if(Column.ColParams.Count > ERP_COL_INDEX_FIELDTYPE)then
      if(Pos('DOMN$COLOR',Column.ColParams[ERP_COL_INDEX_FIELDTYPE]) = 1)then
        Background := Column.Field.AsInteger;
  end;  
