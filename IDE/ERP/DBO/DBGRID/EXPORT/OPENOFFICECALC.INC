{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/OPENOFFICECALC.INC}
{$IFNDEF PEAKTOP:COM/ORACLE/OPENOFFICE/CALC.INC}  {$I PEAKTOP:COM/ORACLE/OPENOFFICE/CALC.INC}  {$ENDIF}
  //=========== PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/OPENOFFICECALC.INC ===========
const
  msg_erp_export_to_oocalc            = 'экспорт данных в Oracle OpenOffice Calc';
  msg_erp_export_error_empty_data_set = 'Нечего экспортировать, обновите набор данных.';
  //============================================================================
  procedure ERP_DBGridEh_ExportToOpenOfficeCalc(aDBG :TDBGridEh; const aWorkSheetName, aEntName, aEntAddr, aCaption, aFilterCaption :string);
  var
    lkServiceMgr   :Variant;
    lkDesktop      :Variant;
    lkDocument     :Variant;
    lkColumn       :Variant;
    lkCell         :Variant;
    lkRange        :Variant;
    lkBorder       :Variant;
    lkCellPos      :TOracleOpenOfficeCalcSelection;
    j, i, cc, k    :Integer;
    lkTitleRowCount:Integer;
    lkColCount     :Integer;
    lkDelta        :Integer;
    lkTopRow       :Integer;
    lkRangeName    :string;
    lkFlag         :Boolean;
    lkSL, lkSLNext :TStringList;
    lkColor        :TColor;
  begin
    if not aDBG.DataSource.DataSet.Active then
      begin
      Dialogs.MessageDlg(msg_erp_export_error_empty_data_set, mtWarning, [mbOk]);
      exit;
      end;
    Dialogs.ProgressDlgSetProgress(0);
    Dialogs.ProgressDlgShow(msg_erp_export_to_oocalc+' (вызов Calc)');
    Dialogs.ProgressDlgSetProgress(0);
    lkServiceMgr := CreateOleObject('com.sun.star.ServiceManager');
    lkDesktop    := lkServiceMgr.CreateInstance('com.sun.star.frame.Desktop');
    Dialogs.ProgressDlgShow(msg_erp_export_to_oocalc+' (создание листа)');
    lkDocument   := lkDesktop.LoadComponentFromURL('private:factory/scalc', '_blank', 0, VarArrayCreate([0, - 1], varVariant));
    lkDocument.LockControllers; // disable calc
    lkDocument.AddActionLock;   // disable calc
    Amunhotep.BringToFront;
    Dialogs.ProgressDlgShow(msg_erp_export_to_oocalc+' (обработка заголовков колонок)');
    lkSL := TStringList.Create; lkSLNext := TStringList.Create;
    lkTitleRowCount := 1;
    for i:=0 to aDBG.Columns.Count-1 do
      if(aDBG.Columns[i].Visible)then
        begin
        lkSL.Text := StrReplaceStr(aDBG.Columns[i].Title.Caption, '|', #13#10);
        lkTitleRowCount := MaxInteger(lkTitleRowCount, lkSL.Count);
        end;
    Dialogs.ProgressDlgShow(msg_erp_export_to_oocalc+' (экспорт заголовков колонок)');
    lkTopRow   := 3;
    lkColCount := 0;
    for i:=0 to aDBG.Columns.Count-1 do
      if(aDBG.Columns[i].Visible)then
        begin
        Dialogs.ProgressDlgShow(msg_erp_export_to_oocalc+' (обработка ['+IntToStr(i)+']'+aDBG.Columns[i].Title.Caption+')');
        Dialogs.ProgressDlgSetProgress(Trunc(i / aDBG.Columns.Count * 100));
        lkColumn := lkDocument.GetCurrentController.GetActiveSheet.GetColumns.GetByIndex(lkColCount);
        lkColumn.Width := Trunc( (aDBG.Columns[i].Width / 32) * 1000);

        lkColumn.CellBackColor := TColorToTOracleOpenOfficeColor(aDBG.Columns[i].Color);
        lkColumn.CharColor     := TColorToTOracleOpenOfficeColor(aDBG.Columns[i].Font.Color);
        lkColumn.CharFontName  := aDBG.Columns[i].Font.Name;
        lkColumn.CharHeight    := aDBG.Columns[i].Font.Size;
        if(fsBold in aDBG.Columns[i].Font.Style)then
          lkColumn.CharWeight  := 150
         else 
          lkColumn.CharWeight  := 0;
        lkColumn.CharUnderline := fsUnderLine in aDBG.Columns[i].Font.Style;
        lkColumn.CharPosture   := fsItalic    in aDBG.Columns[i].Font.Style;
        lkColumn.CharStrikeout := fsStrikeOut in aDBG.Columns[i].Font.Style;
        lkColumn.HoriJustify   := TAlignmentToTOracleOpenOfficeCalcHAlignment(aDBG.Columns[i].Alignment);

        lkSL.Text := StrReplaceStr(aDBG.Columns[i].Title.Caption, '|', #13#10);
        lkSLNext.Text := '';
        if(i < (aDBG.Columns.Count-1) )then
          for j:=i+1 to (aDBG.Columns.Count-1) do
            if(aDBG.Columns[j].Visible)then
              begin
              lkSLNext.Text := StrReplaceStr(aDBG.Columns[j].Title.Caption, '|', #13#10);
              break;
              end;
        for cc:=0 to lkSL.Count-1 do
          begin
          lkFlag := false;
          if((cc < lkSLNext.Count) and (cc < lkSL.Count-1))then
            begin
            if(lkSL[cc] = lkSLNext[cc])then
              begin
              lkCellPos.StartCol := lkColCount;
              lkCellPos.StartRow := lkTopRow   + cc;
              lkCellPos.EndCol   := lkColCount + 1;
              lkCellPos.EndRow   := lkTopRow   + cc;
              lkDocument.GetCurrentController.GetActiveSheet.GetCellRangeByPosition(lkColCount, lkTopRow+cc, lkColCount+1, lkTopRow+cc).Merge(true);
              lkFlag := true;
              end;
            end  
          if( (not lkFlag) and (cc = lkSL.Count-1) and (cc < lkTitleRowCount-1))then
            begin
            lkCellPos.StartCol := lkColCount;
            lkCellPos.StartRow := lkTopRow   + cc;
            lkCellPos.EndCol   := lkColCount;
            lkCellPos.EndRow   := lkTopRow + lkTitleRowCount - 1;
            lkDocument.GetCurrentController.GetActiveSheet.GetCellRangeByPosition(lkColCount, lkTopRow+cc, lkColCount, lkTopRow+lkTitleRowCount-1).Merge(true);
            end
           else
            begin
            lkCellPos.StartCol := lkColCount;
            lkCellPos.StartRow := lkTopRow + cc;
            lkCellPos.EndCol   := lkColCount;
            lkCellPos.EndRow   := lkTopRow + cc;
            end;
//          lkDocument.GetCurrentController.GetActiveSheet.GetCellRangeByPosition(lkCellPos.StartCol, lkCellPos.StartRow, lkCellPos.EndCol, lkCellPos.EndRow).SetValue(lkSL[cc]);
          lkCell := lkDocument.GetCurrentController.GetActiveSheet.GetCellByPosition(lkCellPos.StartCol, lkCellPos.StartRow);
          lkCell.SetString(lkSL[cc]);
          with aDBG.Columns[i].Title do
            begin
            lkCell.HoriJustify   := TAlignmentToTOracleOpenOfficeCalcHAlignment(Alignment);
            lkCell.CellBackColor := TColorToTOracleOpenOfficeColor(Color);
            lkCell.CharColor     := TColorToTOracleOpenOfficeColor(Font.Color);
            lkCell.CharFontName  := Font.Name;
            lkCell.CharHeight    := Font.Size;
            if(fsBold in Font.Style)then
              lkCell.CharWeight  := 150
             else 
              lkCell.CharWeight  := 0;
            lkCell.CharUnderline := fsUnderLine in Font.Style;
            lkCell.CharPosture   := fsItalic    in Font.Style;
            lkCell.CharStrikeout := fsStrikeOut in Font.Style;
            end
          end
        lkColCount := lkColCount + 1;
        end;
    lkTopRow := lkTopRow + lkTitleRowCount;
    lkSL.Free;
    lkSLNext.Free;
    Dialogs.ProgressDlgShow(msg_erp_export_to_oocalc+' (экспорт заголовков отчета)');
    lkRange := lkDocument.GetCurrentController.GetActiveSheet.GetCellRangeByPosition(0, 0, lkColCount-1, 0);   
    lkRange.Merge(true);
    lkRange.HoriJustify   := TAlignmentToTOracleOpenOfficeCalcHAlignment(taLeftJustify);
    lkRange.CellBackColor := TColorToTOracleOpenOfficeColor($000000);
    lkRange.CharColor     := TColorToTOracleOpenOfficeColor($FFFFFF);
    lkRange.CharFontName  := 'Verdana';
    lkRange.CharHeight    := 14;
    lkRange.CharWeight    := 150;
    lkDocument.GetCurrentController.GetActiveSheet.GetCellByPosition(0, 0).SetString(aCaption);
    lkRange := lkDocument.GetCurrentController.GetActiveSheet.GetCellRangeByPosition(0, 1, lkColCount-1, 2);   
    lkRange.Merge(true);
    lkRange.HoriJustify   := TAlignmentToTOracleOpenOfficeCalcHAlignment(taLeftJustify);
    lkRange.CellBackColor := TColorToTOracleOpenOfficeColor($FFFFFF);
    lkRange.CharColor     := TColorToTOracleOpenOfficeColor($000000);
    lkRange.CharFontName  := 'Verdana';
    lkRange.CharHeight    := 6;
    lkRange.CharWeight    := 150;
    lkDocument.GetCurrentController.GetActiveSheet.GetCellByPosition(1, 1).SetString(aFilterCaption);
    Dialogs.ProgressDlgShow(msg_erp_export_to_oocalc+' (выгрузка данных)');
    Dialogs.ProgressDlgSetProgress(0);
    aDBG.DataSource.DataSet.DisableControls;
    aDBG.SaveBookMark;
    aDBG.DataSource.DataSet.First;
    lkDelta := 1;
    if(aDBG.DataSource.DataSet.RecordCount > 0)then
      begin
      if(aDBG.DataSource.DataSet.RecordCount > 100)then
        lkDelta := Trunc(aDBG.DataSource.DataSet.RecordCount / 100)
       else
        lkDelta := Trunc(100 / aDBG.DataSource.DataSet.RecordCount);
      end;  
    j := 0;
    while not aDBG.DataSource.DataSet.EOF do
      begin
      lkColCount := 0;
      for i:=0 to aDBG.Columns.Count-1 do
        if(aDBG.Columns[i].Visible)then
          begin
          lkDocument.GetCurrentController.GetActiveSheet.GetCellByPosition(lkColCount, lkTopRow+j).SetString( aDBG.Columns[i].DisplayText );
          lkColCount := lkColCount + 1;
          end;
      j := j + 1;
      if((j mod lkDelta) = 0)then
        begin
        Dialogs.ProgressDlgSetProgress(Trunc(j * 100 / aDBG.DataSource.DataSet.RecordCount));
        Amunhotep.ProcessMessages;
        end;
      aDBG.DataSource.DataSet.Next;
      end;
    if(aDBG.FooterRowCount > 0)then
      begin
      lkColCount := 0;
      for i:=0 to aDBG.Columns.Count-1 do
        if aDBG.Columns[i].Visible then
          with aDBG.Columns[i].Footer do
            begin
            lkCell := lkDocument.GetCurrentController.GetActiveSheet.GetCellByPosition(lkColCount, lkTopRow+j);
            lkRangeName := OracleOpenOfficeCalc_IntToColIndex(lkColCount+1)+IntToStr(lkTopRow+1)+':'+OracleOpenOfficeCalc_IntToColIndex(lkColCount+1)+IntToStr(lkTopRow+j);
                 if(ValueType = fvtSum       )then lkCell.SetFormula('=SUM('+lkRangeName+')')
            else if(ValueType = fvtAvg       )then lkCell.SetFormula('=AVERAGE('+lkRangeName+')')
            else if(ValueType = fvtCount     )then lkCell.SetFormula('=COUNT('+lkRangeName+')')
            else if(ValueType = fvtFieldValue)then lkCell.SetString(aDBG.DataSource.DataSet.FieldByName(FieldName).AsString)
            else if(ValueType = fvtStaticText)then lkCell.SetString(Value)
            ;
            lkCell.CellBackColor := TColorToTOracleOpenOfficeColor(Color);
            lkCell.CharColor     := TColorToTOracleOpenOfficeColor(Font.Color);
            lkCell.CharFontName  := Font.Name;
            lkCell.CharHeight    := Font.Size;
            if(fsBold in Font.Style)then
              lkCell.CharWeight  := 150
             else 
              lkCell.CharWeight  := 0;
            lkCell.CharUnderline := fsUnderLine in Font.Style;
            lkCell.CharPosture   := fsItalic    in Font.Style;
            lkCell.CharStrikeout := fsStrikeOut in Font.Style;
            lkColCount  := lkColCount + 1;
            end;
      j := j + 1;
      end;     
{
    lkBorder := lkServiceMgr.Bridge_GetStruct('com.sun.star.table.BorderLine');
    lkBorder.Color          := Amunhotep.MainForm.StyleManager.Colors.Border;
    lkBorder.LineDistance   := 0;
    lkBorder.InnerLineWidth := 0;
    lkBorder.OuterLineWidth := 1; 
    lkRange := lkDocument.GetCurrentController.GetActiveSheet.GetCellRangeByPosition(1, lkTopRow - lkTitleRowCount + 1, lkColCount, lkTopRow+j-1);   
    lkRange.LeftBorder   := lkBorder;
    lkRange.TopBorder    := lkBorder;
    lkRange.RightBorder  := lkBorder;
    lkRange.BottomBorder := lkBorder;
}
    aDBG.RestoreBookMark;
    aDBG.DataSource.DataSet.EnableControls;
    Dialogs.ProgressDlgHide;
    lkDocument.UnLockControllers;
    lkDocument.RemoveActionLock;
  end;
