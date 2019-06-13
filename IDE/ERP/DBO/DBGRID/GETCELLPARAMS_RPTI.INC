{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_RPTI.INC}
  //=============== PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_REF.INC ===========
  procedure ERP_DBGridEh_OnGetCellParams_Rpti_HideZeroInt(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
   if(Column.Tag = 666)then exit;
   if(not(Column.Field.DataSet.Active))then exit;
   if(Column.Field.DataSet.RecordCount = 0)then exit;
   if(Column.Field.AsInteger=0)then 
     aFont.Color := Background;
  end;
  //============================================================================
  procedure ERP_DBGridEh_OnGetCellParams_Rpti_HideZeroFloat(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
   if(Column.Tag = 666)then exit;
   if(not(Column.Field.DataSet.Active))then exit;
   if(Column.Field.DataSet.RecordCount = 0)then exit;
   if(Column.Field.AsFloat = 0)then 
     aFont.Color := Background;
  end;  
