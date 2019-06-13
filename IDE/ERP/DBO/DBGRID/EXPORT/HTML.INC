{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/EXPORT/HTML.INC}
{$IFNDEF PEAKTOP:ORG/HTML/EXPORTUTILS.INC}    {$I PEAKTOP:ORG/HTML/EXPORTUTILS.INC}   {$ENDIF}
const //============= PEAKTOP:IDE/ERP/DBO/EXPORT/HTML.INC ======================
  msg_erp_export_to_html = 'экспорт данных в HTML';
  //============================================================================
  procedure ERP_DBGridEh_ExportToHTML(aDBG :TDBGridEh;const aInitFileName, aEntName, aEntAddr, aCaption, aFilterCaption :string);
  var
    lkFileName     :string;
    lkFileHandle   :THandle;
    j, i           :Integer;
    lkTitleRowCount:Integer;
    lkColCount     :Integer;
    lkDelta        :Integer;
    lkTopRow       :Integer;
    lkStr          :string;
    lkRowStr       :string;
    lkSL, lkSLNext :TStringList;
    lkFont         :TFont;
    lkColor        :TColor;
  begin
    lkFileName := aInitFileName;
    if not PromptForFileName(lkFileName, 'Гипертекстовые документы (*.html)|*.htm;*.html|Все файлы (*.*)|*.*', 'html', 
      'Сохранить файл как...', '', true)then exit;
    lkFileHandle := FileCreate(lkFileName);
    if(lkFileHandle = 0)then
      begin
      Dialogs.MessageDlg('Не удалось сохранить файл'+#13#10+'"'+lkFileName+'"', mtWarning, [mbOk]);
      exit;
      end;
    Dialogs.ProgressDlgShow(msg_erp_export_to_html+' (обработка заголовков колонок)');
    lkStr := 
      '<html>'+#13#10+
      '  <head>'+#13#10+
      '    <title></title>'+#13#10+
      '    <meta http-equiv="Content-Type" content="text/html; charset=windows-1251"/>'+#13#10+
      '    <style type="text/css">'+#13#10+
      '      .tablestyle {'+#13#10+
      '        background :'+HTML_TColorToColor(aDBG.Color)+';'+#13#10+  
      '        border-top :1px solid #000000;'+#13#10+
      '        border-left:1px solid #000000;'+#13#10+
      '        font-family:'+aDBG.Font.Name+';'+#13#10+
      '        font-size  :'+IntToStr(aDBG.Font.Size+2)+'px;'+#13#10+
      '      }'+#13#10+
      '      .tableheadercaption {'+#13#10+
      '        background   :#000000;'+#13#10+  
      '        border-right :1px solid #000000;'+#13#10+
      '        border-bottom:1px solid #000000;'+#13#10+
      '        height       :34px;'+#13#10+
      '        color        :#F0F0FF;'+#13#10+
      '        font-family  :'+aDBG.Font.Name+';'+#13#10+
      '        font-size    :16px;'+#13#10+
      '      }'+#13#10+
      '      .tablerow {'+#13#10+
      '        border-right: 1px solid #000000;'+#13#10+
      '        border-bottom:1px solid #000000;'+#13#10+
      '      }'+#13#10+
      '    </style>'+#13#10+
      '  <head>'+#13#10+
      '<body>'+#13#10+
      '  <table cellpadding="0" cellspacing="0" class="tablestyle">'+#13#10;
    FileWriteString(lkFileHandle,lkStr);    
    lkSL := TStringList.Create; lkSLNext := TStringList.Create;
    lkTitleRowCount := 1;
    for i:=0 to aDBG.Columns.Count-1 do
      if(aDBG.Columns[i].Visible)then
        begin
        lkSL.Text := StrReplaceStr(aDBG.Columns[i].Title.Caption, '|', #13#10);
        lkTitleRowCount := MaxInteger(lkTitleRowCount, lkSL.Count);
        end;
    Dialogs.ProgressDlgShow(msg_erp_export_to_html+' (экспорт заголовков колонок)');
    lkTopRow   := 5;
    lkColCount := 0;
    lkRowStr   := '    <tr>'+#13#10+'      <td class="tableheadercaption" colspan="'+IntToStr(aDBG.VisibleColumns.Count)+'"><b>'+aCaption+'</b></td>'+#13#10+'    </tr>'+#13#10;
    FileWriteString(lkFileHandle, lkRowStr);    
    lkRowStr   := '    <tr>'+#13#10;
    for i:=0 to aDBG.Columns.Count-1 do
      if(aDBG.Columns[i].Visible)then
        begin
        Dialogs.ProgressDlgShow(msg_erp_export_to_html+' (обработка ['+IntToStr(i)+']'+aDBG.Columns[i].Title.Caption+')');
        lkColCount := lkColCount + 1;
        lkRowStr := lkRowStr + '      <td class="tablerow" style="background :'+HTML_TColorToColor(aDBG.Columns[i].Title.Color)+';"><b>'+
          HTML_IfEmptyStr(StrReplaceStr(aDBG.Columns[i].Title.Caption, '|', '<br>'))+'</b></td>'+#13#10;
        end;
    lkRowStr := lkRowStr + '    </tr>'+#13#10;
    FileWriteString(lkFileHandle, lkRowStr);    
    lkTopRow := lkTopRow + lkTitleRowCount;
    lkSL.Free;
    lkSLNext.Free;
    Dialogs.ProgressDlgShow(msg_erp_export_to_html+' (выгрузка данных)');
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
    lkFont   := TFont.Create;
    while not aDBG.DataSource.DataSet.EOF do
      begin
      lkColCount := 0;
      lkRowStr := '    <tr>'+#13#10;
      for i:=0 to aDBG.Columns.Count-1 do
        if(aDBG.Columns[i].Visible)then
          begin
          lkFont.Assign(aDBG.Columns[i].Font);
          lkColor := aDBG.Columns[i].Color;
          {if assigned(LongInt(@aDBG.OnGetCellParams)) then
            begin
            lkProc  := aDBG.OnGetCellParams;
            lkProc(aDBG, aDBG.Columns[i], lkFont, lkColor, lkDummyState);
            end; }
          lkColCount := lkColCount + 1;
          lkRowStr   := lkRowStr+'      <td class="tablerow" style="background :'+HTML_TColorToColor(lkColor)+';" align="'+HTML_TAlignmentToAlign(aDBG.Columns[i].Alignment)+'" nowrap>'+HTML_IfEmptyStr(aDBG.Columns[i].DisplayText)+'</td>'+#13#10;
          end;
      lkRowStr := lkRowStr +'    </tr>'+#13#10;
      FileWriteString(lkFileHandle, lkRowStr);    
      j := j + 1;
      if((j mod lkDelta) = 0)then
        begin
        Dialogs.ProgressDlgSetProgress(Trunc(j * 100 / aDBG.DataSource.DataSet.RecordCount));
        Amunhotep.ProcessMessages;
        end;
      aDBG.DataSource.DataSet.Next;
      end;
    lkFont.Free;
    lkRowStr := '  </table>'+#13#10+'</body>'+#13#10+'</html>';   
    FileWriteString(lkFileHandle, lkRowStr);    
    FileClose(lkFileHandle);      
    Dialogs.ProgressDlgHide;
    aDBG.RestoreBookMark;
    aDBG.DataSource.DataSet.EnableControls;
  end;
