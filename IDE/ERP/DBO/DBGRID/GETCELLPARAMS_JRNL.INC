{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                      {$I PEAKTOP:GLOBAL_VARIABLES.INC}               {$ENDIF}
  //============== PEAKTOP:IDE/ERP/DBO/DBGRID/GETCELLPARAMS_JRNL.INC ===========
  procedure ERP_DBGridEh_OnGetCellParams_Jrnl(Sender: TObject; Column: TColumnEh; AFont: TFont; var Background: TColor; State: TGridDrawState);
  begin
    if(Column.Tag = 666)then exit;
    if(not(Column.Field.DataSet.Active))then exit;
    if(Column.Field.DataSet.RecordCount = 0)then exit;
    if(Column.Field.DataSet.FindField('FLAG_COMMIT') <> nil)then
      if(Column.Field.DataSet.FieldByName('FLAG_COMMIT').AsInteger = 0)then 
        aFont.Style:= aFont.Style + [fsBold];
    if(Column.Field.DataSet.FindField('COLOR_BGR') <> nil)then
      begin
      Background := Column.Field.DataSet.FieldByName('COLOR_BGR').AsInteger;
      aFont.Color:= Column.Field.DataSet.FieldByName('COLOR_FRG').AsInteger;
      end;
    if(Background  = clWhite   )then Background  := Amunhotep.MainForm.StyleManager.Colors.Window;
    if(aFont.Color = Background)then aFont.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
  end;
  //============================================================================
  procedure ERP_DBGridEh_OnGetCellParams_JrnlComments(Sender:TObject; Column:TColumnEh; AFont: TFont; var Background:TColor; State:TGridDrawState);
  begin
    if(Column.Tag = 666)then exit;
    if(not(Column.Field.DataSet.Active))then exit;
    if(Column.Field.DataSet.RecordCount = 0)then exit;
    if(Column.Field.DataSet.FieldByName('FLAG_DELETE').AsInteger = 1)then 
      aFont.Style:= aFont.Style + [fsStrikeOut];
    if(Column.Field.DataSet.FindField('USER_ID') <> nil)then
      begin
      if(UpperCase(Column.Field.DataSet.FieldByName('USER_ID').AsString) = UpperCase(GetGlobalVariable('DATABASE_USER')))then 
        aFont.Style := [fsBold]
       else 
        aFont.Style := [];
      end;
  end;  
