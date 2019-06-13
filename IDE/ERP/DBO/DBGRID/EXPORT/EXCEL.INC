{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/EXCEL.INC}
{$IFNDEF PEAKTOP:COM/MICROSOFT/OFFICE/EXCEL/CONST.INC} {$I PEAKTOP:COM/MICROSOFT/OFFICE/EXCEL/CONST.INC} {$ENDIF}
{$IFNDEF PEAKTOP:COM/MICROSOFT/OFFICE/EXCEL/UTILS.INC} {$I PEAKTOP:COM/MICROSOFT/OFFICE/EXCEL/UTILS.INC} {$ENDIF}
const  //==================== PEAKTOP:IDE/ERP/DBO/EXPORT/EXCEL.INC =============
  msg_erp_export_to_excel             = 'экспорт данных в Microsoft Excel';
  msg_erp_export_error_empty_data_set = 'Нечего экспортировать, обновите набор данных.';
  //============================================================================
  procedure ERP_DBGridEh_ExportToExcel(aDBG :TDBGridEh; const aWorkSheetName:string; 
              const aEntName, aEntAddr, aCaption, aFilterCaption :string);
  var
    lkExcel        :Variant;
    lkWorkBook     :Variant;
    lkWorkSheet    :Variant;
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
    Dialogs.ProgressDlgShow(msg_erp_export_to_excel+' (вызов Excel)');
    Dialogs.ProgressDlgSetProgress(0);

    lkExcel := CreateOleObject('Excel.Application');
    lkExcel.DisplayAlerts := false;
    lkExcel.Visible := False;
    lkExcel.Application.EnableEvents := False;
    Dialogs.ProgressDlgShow(msg_erp_export_to_excel+' (создание листа)');
    lkWorkBook  := lkExcel.WorkBooks.Add(-4167); // with one sheet  !!!
    if(lkWorkBook.WorkSheets.Count < 1)then
      lkWorkSheet := lkWorkBook.WorkSheets.Add()
     else 
      lkWorkSheet := lkWorkBook.WorkSheets[1];
    Dialogs.ProgressDlgShow(msg_erp_export_to_excel+' (установка параметров страницы)');
    lkWorkSheet.Name := aWorkSheetName;

    lkWorkSheet.PageSetup.Orientation  := MSEXCEL_xlLandscape;
    lkWorkSheet.PageSetup.LeftMargin   := 15;
    lkWorkSheet.PageSetup.RightMargin  := 15;
    lkWorkSheet.PageSetup.TopMargin    := 15;
    lkWorkSheet.PageSetup.BottomMargin := 15;
    lkWorkSheet.PageSetup.HeaderMargin := 0;
    lkWorkSheet.PageSetup.FooterMargin := 0;

    Dialogs.ProgressDlgShow(msg_erp_export_to_excel+' (обработка заголовков колонок)');
    lkSL := TStringList.Create; lkSLNext := TStringList.Create;
    lkTitleRowCount := 1;
    for i:=0 to aDBG.Columns.Count-1 do
      if(aDBG.Columns[i].Visible)then
        begin
        lkSL.Text := StrReplaceStr(aDBG.Columns[i].Title.Caption, '|', #13#10);
        lkTitleRowCount := MaxInteger(lkTitleRowCount, lkSL.Count);
        end;
    Dialogs.ProgressDlgShow(msg_erp_export_to_excel+' (экспорт заголовков колонок)');
    lkTopRow   := 3;
    lkColCount := 0;
    for i:=0 to aDBG.Columns.Count-1 do
      if(aDBG.Columns[i].Visible)then
        begin
        Dialogs.ProgressDlgShow(msg_erp_export_to_excel+' (обработка ['+IntToStr(i)+']'+aDBG.Columns[i].Title.Caption+')');
        Dialogs.ProgressDlgSetProgress(Trunc(i / aDBG.Columns.Count * 100));
        lkColCount := lkColCount + 1;
        lkWorkSheet.Columns[lkColCount].ColumnWidth         := (aDBG.Columns[i].Width / 7);
        lkWorkSheet.Columns[lkColCount].HorizontalAlignment := MSExcel_AlignmentToHorizontalAlignment(aDBG.Columns[i].Alignment);
        // no property lkWorkSheet.Columns[lkColCount].VerticalAlignment   := MSEXCEL_xlTop;
        lkWorkSheet.Columns[lkColCount].Interior.Color      := aDBG.Columns[i].Color; 
//        MSExcel_TFontToFont(aDBG.Columns[i].Font, lkWorkSheet.Columns[lkColCount].Font);
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
              lkRangeName := MSExcel_IntToColIndex(lkColCount)+IntToStr(lkTopRow+cc)+':'+MSExcel_IntToColIndex(lkColCount+1)+IntToStr(lkTopRow+cc);
              lkWorkSheet.Range[lkRangeName].Merge;
              lkFlag := true;
              end;
            end  
          if( (not lkFlag) and (cc = lkSL.Count-1) and (cc < lkTitleRowCount-1))then
            begin
            lkRangeName := MSExcel_IntToColIndex(lkColCount)+IntToStr(lkTopRow+cc)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(lkTopRow+lkTitleRowCount-1);
            lkWorkSheet.Range[lkRangeName].Merge;
            end
           else
            lkRangeName := MSExcel_IntToColIndex(lkColCount)+IntToStr(lkTopRow+cc)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(lkTopRow+cc);
          lkWorkSheet.Range[lkRangeName].Value := lkSL[cc];
          lkWorkSheet.Range[lkRangeName].WrapText := true;
//          lkWorkSheet.Range[lkRangeName].VerticalAlignment   := MSEXCEL_xlTop;
          with aDBG.Columns[i].Title do
            begin
            lkWorkSheet.Range[lkRangeName].HorizontalAlignment := MSExcel_AlignmentToHorizontalAlignment(Alignment);
            lkWorkSheet.Range[lkRangeName].Interior.Color      := Color; 
            MSExcel_TFontToFont(Font, lkWorkSheet.Range[lkRangeName].Font);
            end
          end
        end;
    lkTopRow := lkTopRow + lkTitleRowCount;
    lkSL.Free;
    lkSLNext.Free;
    Dialogs.ProgressDlgShow(msg_erp_export_to_excel+' (экспорт заголовков отчета)');
    // processing captions
    lkRangeName := MSExcel_IntToColIndex(2)+IntToStr(1)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(1);
    lkWorkSheet.Range[lkRangeName].Merge;
    lkWorkSheet.Range[lkRangeName].Value      := aEntName;
    lkWorkSheet.Range[lkRangeName].Font.Name  := 'Times New Roman';
    lkWorkSheet.Range[lkRangeName].Font.Size  := 12;
    lkWorkSheet.Range[lkRangeName].Font.Color := clBlack;
    lkWorkSheet.Range[lkRangeName].Font.Bold  := true;
    lkWorkSheet.Range[lkRangeName].Interior.Color := clWhite;
    lkRangeName := MSExcel_IntToColIndex(2)+IntToStr(2)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(2);
    lkWorkSheet.Range[lkRangeName].Merge;
    lkWorkSheet.Range[lkRangeName].Value       := aEntName;
    lkWorkSheet.Range[lkRangeName].Font.Name   := 'Times New Roman';
    lkWorkSheet.Range[lkRangeName].Font.Size   := 8;
    lkWorkSheet.Range[lkRangeName].Font.Color  := clBlack;
    lkWorkSheet.Range[lkRangeName].Font.Italic := true;
    lkWorkSheet.Range[lkRangeName].Interior.Color := clWhite;
    lkRangeName := MSExcel_IntToColIndex(1)+IntToStr(3)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(3);

    lkRangeName := MSExcel_IntToColIndex(1)+IntToStr(1)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(1);

    lkWorkSheet.Range[lkRangeName].Merge;
    lkWorkSheet.Range[lkRangeName].Value          := aCaption;
    lkWorkSheet.Range[lkRangeName].Interior.Color := clBlack
    lkWorkSheet.Range[lkRangeName].Font.Name      := 'Verdana';
    lkWorkSheet.Range[lkRangeName].Font.Size      := 14;
    lkWorkSheet.Range[lkRangeName].Font.Color     := clWhite;
    lkWorkSheet.Range[lkRangeName].Font.Bold      := true;
    lkWorkSheet.Range[lkRangeName].HorizontalAlignment := MSExcel_AlignmentToHorizontalAlignment(taLeftJustify);
    lkRangeName := MSExcel_IntToColIndex(1)+IntToStr(2)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(2);
    lkWorkSheet.Range[lkRangeName].Merge;
    lkWorkSheet.Range[lkRangeName].Value      := aFilterCaption;
    lkWorkSheet.Range[lkRangeName].Font.Name  := 'Verdana';
    lkWorkSheet.Range[lkRangeName].Font.Size  := 6;
    lkWorkSheet.Range[lkRangeName].Font.Color := clBlack;
    lkWorkSheet.Range[lkRangeName].Font.Bold  := true;
    lkWorkSheet.Range[lkRangeName].Interior.Color := clWhite;
    Dialogs.ProgressDlgShow(msg_erp_export_to_excel+' (выгрузка данных)');
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
          lkColCount := lkColCount + 1;
          lkWorkSheet.Cells[lkTopRow+j, lkColCount].Value := aDBG.Columns[i].DisplayText;
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
            lkColCount  := lkColCount + 1;
            lkRangeName := MSExcel_IntToColIndex(lkColCount)+IntToStr(lkTopRow)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(lkTopRow+j-1);
                 if(ValueType = fvtSum       )then lkWorkSheet.Cells[lkTopRow+j,lkColCount].Value := '= СУММ('+lkRangeName+')'
            else if(ValueType = fvtAvg       )then lkWorkSheet.Cells[lkTopRow+j,lkColCount].Value := '= СРЗНАЧ('+lkRangeName+')'
            else if(ValueType = fvtCount     )then lkWorkSheet.Cells[lkTopRow+j,lkColCount].Value := '= ЧСТРОК('+lkRangeName+')'
            else if(ValueType = fvtFieldValue)then lkWorkSheet.Cells[lkTopRow+j,lkColCount].Value := aDBG.DataSource.DataSet.FieldByName(FieldName).AsString
            else if(ValueType = fvtStaticText)then lkWorkSheet.Cells[lkTopRow+j,lkColCount].Value := Value
            ;
            lkWorkSheet.Cells[lkTopRow+j,lkColCount].Interior.Color := Color;
            MSExcel_TFontToFont(Font, lkWorkSheet.Cells[lkTopRow+j,lkColCount].Font);
            Amunhotep.ProcessMessages;
            end;
      j := j + 1;
      end;      
    lkRangeName := MSExcel_IntToColIndex(1)+IntToStr(lkTopRow-lkTitleRowCount)+':'+MSExcel_IntToColIndex(lkColCount)+IntToStr(lkTopRow+j-1);
    MSExcel_DrawGridByRange(lkRangeName, lkWorkSheet);
    aDBG.RestoreBookMark;
    aDBG.DataSource.DataSet.EnableControls;
    Dialogs.ProgressDlgHide;
    Amunhotep.ProcessMessages;
    lkExcel.Application.EnableEvents := true;
    lkExcel.Visible := true;
  end;
