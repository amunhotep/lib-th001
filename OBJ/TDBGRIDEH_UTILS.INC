{$DEFINE PEAKTOP:OBJ/TDBGRIDEH_UTILS.INC}
  //============================================================================
  function ExportDBGridEhToFormat(
             const aDBGridEh          :TDBGridEh; 
             const aFileName          :string; 
             const aSaveDialogCaption :string;
             const aExportFormat      :TdbgExportFormat
           ):Boolean;
  var
    lkFileName :string;
    lkFileExt  :string;
    lkFilter   :string;
    lkFilterExt:string;
  begin
    Result     := false;
    lkFileName := aFileName;
    case aExportFormat of
      dbgExportToTXT :
        begin 
        lkFileExt := 'TXT' ;
        {$IFDEF LANGUAGE_UKR}lkFilterExt := 'Текстовi файли';           {$ENDIF}
        {$IFDEF LANGUAGE_RUS}lkFilterExt := 'Текстовые файлы';          {$ENDIF}
        {$IFDEF LANGUAGE_ENG}lkFilterExt := 'Text files';               {$ENDIF}
        {$IFDEF LANGUAGE_DEU}lkFilterExt := 'Text files';               {$ENDIF} 
        end;
      dbgExportToCSV :
        begin 
        lkFileExt := 'CSV' ; 
        {$IFDEF LANGUAGE_UKR}lkFilterExt := 'Файлы с разделитемями';    {$ENDIF}
        {$IFDEF LANGUAGE_RUS}lkFilterExt := 'Файлы с разделитемями';    {$ENDIF}
        {$IFDEF LANGUAGE_ENG}lkFilterExt := 'CSV files';                {$ENDIF}
        {$IFDEF LANGUAGE_DEU}lkFilterExt := 'CSV files';                {$ENDIF} 
        end;
      dbgExportToHTML:
        begin 
        lkFileExt := 'HTML'; 
        {$IFDEF LANGUAGE_UKR}lkFilterExt := 'Гипертекстовые документы'; {$ENDIF}
        {$IFDEF LANGUAGE_RUS}lkFilterExt := 'Гипертекстовые документы'; {$ENDIF}
        {$IFDEF LANGUAGE_ENG}lkFilterExt := 'HTML files';               {$ENDIF}
        {$IFDEF LANGUAGE_DEU}lkFilterExt := 'HTML files';               {$ENDIF} 
        end;
      dbgExportToRTF :
        begin 
        lkFileExt := 'RTF' ; 
        {$IFDEF LANGUAGE_UKR}lkFilterExt := 'RTF-документы';            {$ENDIF}
        {$IFDEF LANGUAGE_RUS}lkFilterExt := 'RTF-документы';            {$ENDIF}
        {$IFDEF LANGUAGE_ENG}lkFilterExt := 'RTF files';                {$ENDIF}
        {$IFDEF LANGUAGE_DEU}lkFilterExt := 'RTF files';                {$ENDIF} 
        end;
      dbgExportToXLS :
        begin 
        lkFileExt := 'XLS' ; 
        {$IFDEF LANGUAGE_UKR}lkFilterExt := 'Документы Microsoft Excel';{$ENDIF}
        {$IFDEF LANGUAGE_RUS}lkFilterExt := 'Документы Microsoft Excel';{$ENDIF}
        {$IFDEF LANGUAGE_ENG}lkFilterExt := 'XLS files';                {$ENDIF}
        {$IFDEF LANGUAGE_DEU}lkFilterExt := 'XLS files';                {$ENDIF} 
        end;
      end;
    lkFileName := lkFileName+'.'+LowerCase(lkFileExt);
    lkFilter   := lkFilterExt+' (*.'+lkFileExt+')|*.'+lkFileExt+'|'+
                  {$IFDEF LANGUAGE_UKR} 'Всi файли'+ {$ENDIF}
                  {$IFDEF LANGUAGE_RUS} 'Все файлы'+ {$ENDIF}
                  {$IFDEF LANGUAGE_ENG} 'All Files'+ {$ENDIF}
                  {$IFDEF LANGUAGE_DEU} 'All Files'+ {$ENDIF} 
                  ' (*.*)|*.*';
    lkFileName := StrReplaceStr(lkFileName, '\', '_');  
    lkFileName := StrReplaceStr(lkFileName, '/', '_');  
    lkFileName := StrReplaceStr(lkFileName, ':', '_');  
    lkFileName := StrReplaceStr(lkFileName, '?', '_');  
    lkFileName := StrReplaceStr(lkFileName, '*', '_');  
    if PromptForFileName(lkFileName, lkFilter, lkFileExt, aSaveDialogCaption,'', true)then
      try
        DBGridEh_SaveToFile(aDBGridEh, aExportFormat, lkFileName);
      finally
        Result := true;
      end;
  end;
  //============================================================================
  function PrintDBGridEh(
             const aSender   :TForm;
             const aDBGridEh :TDBGridEh;
             const aSQL      :string;
             const aCaption  :string;
             const aColorDataSetIndex     :Integer;
             const aColorDataSetField     :string; 
             const aFontColorDataSetIndex :Integer;
             const aFontColorDataSetField :string 
           ):Boolean;
  var
    lkStr        :string;
    lkExprStr    :string;
    lkBmp        :TBitmap;
    lkRpt        :TxReport;
    lkPageHeader :TxrBand;
    lkDetail     :TxrBand;
    lkSummary    :TxrBand;
    lkImgLogo    :TxrImage;
    lkText       :TxrLabel;
    lkDBText     :TxrDBLabel;
    lkExpr       :TxrExpression;
    i,j          :Integer;
    lkWidth      :Integer;
    lkLastLeft   :Integer;
  begin
    lkRpt                     := TxReport.Create(aSender);
    lkRpt.AutoFree            := true;
    lkRpt.DataBase            := FBDataBase;
    lkRpt.StyleManager        := Amunhotep.MainForm.StyleManager;
    lkRpt.PrintIfEmpty        := true;
    lkRpt.PrevFormStyle       := fsMDIChild;
    lkRpt.PreviewInitialState := aSender.WindowState;
    lkRpt.PreviewHeight       := aSender.Height;
    lkRpt.PreviewWidth        := aSender.Width; 
    lkRpt.Page.Orientation    := poLandscape;
    lkRpt.Page.PaperSize      := A4;
    lkRpt.Page.LeftMargin     := 8;
    lkRpt.Page.TopMargin      := 8;
    lkRpt.Page.RightMargin    := 8;
    lkRpt.Page.BottomMargin   := 8;
    lkRpt.Font.Name           := 'Verdana';
    lkRpt.Font.Size           := 6;
    if(lkRpt.DataSets.Count <= 0)then lkRpt.DataSets.Add;
    lkRpt.DataSets[0].Name    := 'qrRef';
    lkRpt.DataSets[0].SQL.Text:= aSQL;
    lkRpt.DataSetIndex        := 0;
    lkPageHeader              := lkRpt.CreateBand(rbPageHeader);
    lkPageHeader.Height       := 128;
    lkDetail                  := lkRpt.CreateBand(rbDetail);
    lkDetail.Height           := 16;
    lkText              := TxrLabel.Create(lkRpt);
    lkText.Name         := 'lbl_Header';
    lkText.Parent       := lkPageHeader;
    lkText.Alignment    := taLeftJustify;
    lkText.Caption      := aCaption;
    lkText.Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
    lkText.Font.Size    := 12;
    lkText.Font.Style   := [fsBold];
    lkText.Left         := 0;
    lkText.Top          := 0; 
    lkText.Height       := 64;
    lkText.Width        := lkPageHeader.Width;
    lkStr := StrAbsolutePath('../conf/ent/logo.bmp', Amunhotep.ExeName);
    if(FileExists(lkStr))then
      begin
      lkImgLogo        := TxrImage.Create(lkRpt);
      lkImgLogo.Parent := lkPageHeader;
      lkImgLogo.Left   := 0;
      lkImgLogo.Top    := 0;
      lkImgLogo.Height := 64;
      lkImgLogo.Width  := 600;
      lkImgLogo.Stretch:= true;
      lkImgLogo.Center := true;
      try 
        try
          lkBmp        := TBitmap.Create;
          lkBmp.LoadFromFile(lkStr);
          lkImgLogo.Width := Round(lkImgLogo.Height * lkBmp.Width / lkBmp.Height) + 1;
        finally
          lkBmp.Free;
        end;
        lkImgLogo.Picture.LoadFromFile(lkStr); 
      finally
      end;
      lkText.Left  := lkImgLogo.Left + lkImgLogo.Width + 1;
      //lkText.Width := lkPageHeader.Width - lkText.Left - 1;
      end;
    lkWidth    := 0;  
    for i:=0 to aDBGridEh.Columns.Count-1 do
      if(aDBGridEh.Columns[i].Visible)then
        lkWidth := lkWidth + aDBGridEh.Columns[i].Width;
    lkLastLeft := 0;
    for i:=0 to aDBGridEh.Columns.Count-1 do
      if(aDBGridEh.Columns[i].Visible)then
        begin
        lkText              := TxrLabel.Create(lkRpt);
        lkText.Name         := 'lbl_'+aDBGridEh.Columns[i].FieldName;
        lkText.Parent       := lkPageHeader;
        lkText.Alignment    := taCenter;
        lkText.Caption      := StrReplaceStr(aDBGridEh.Columns[i].Title.Caption, '|', #13#10);
        lkText.Color        := Amunhotep.MainForm.StyleManager.Colors.Foreground;
        lkText.Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
        lkText.Font.Size    := 6;
        lkText.Font.Style   := [fsBold];
        lkText.Top          := 64; 
        lkText.Height       := 64;
        lkText.Left         := lkLastLeft;
        lkText.Width        := Trunc(aDBGridEh.Columns[i].Width * lkPageHeader.Width / lkWidth);
        lkText.Frame.Color  := clBlack;
        lkText.Frame.Top    := true;
        lkText.Frame.Bottom := true;
        lkText.Frame.Left   := true;
        lkText.Frame.Right  := (i = (aDBGridEh.Columns.Count-1));
        if(aDBGridEh.Columns[i].KeyList.Count>0)then
          begin
          lkExprStr := ''' ''';
          for j:=0 to aDBGridEh.Columns[i].KeyList.Count-1 do
            lkExprStr := 'IF( ('+aDBGridEh.Columns[i].FieldName+' = '''+aDBGridEh.Columns[i].KeyList[j]+
              '''), '''+aDBGridEh.Columns[i].PickList[j]+''', '+lkExprStr+')'; 
          lkExpr              := TxrExpression.Create(lkRpt);
          lkExpr.Name         := 'expr_'+aDBGridEh.Columns[i].FieldName;
          lkExpr.Parent       := lkDetail;
          lkExpr.Alignment    := aDBGridEh.Columns[i].Alignment;
          lkExpr.Expression   := lkExprStr;
          lkExpr.Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
          lkExpr.Font.Size    := 6;
          lkExpr.ColorDataSetIndex     := aColorDataSetIndex;
          lkExpr.ColorDataSetField     := aColorDataSetField;
          lkExpr.ColorFontDataSetIndex := aFontColorDataSetIndex;
          lkExpr.ColorFontDataSetField := aFontColorDataSetField;
          lkExpr.Top          := 0; 
          lkExpr.Height       := 16;
          lkExpr.Left         := lkLastLeft;
          lkExpr.Width        := lkText.Width;
          lkExpr.Frame.Color  := clBlack;
          lkExpr.Frame.Top    := false;
          lkExpr.Frame.Bottom := true;
          lkExpr.Frame.Left   := true;
          lkExpr.Frame.Right  := (i = (aDBGridEh.Columns.Count-1));
          end
         else
          begin
          lkDBText              := TxrDBLabel.Create(lkRpt);
          lkDBText.Name         := 'dblbl_'+aDBGridEh.Columns[i].FieldName;
          lkDBText.Parent       := lkDetail;
          lkDBText.Alignment    := aDBGridEh.Columns[i].Alignment;
          lkDBText.DataSetIndex := 0;
          lkDBText.DataField    := aDBGridEh.Columns[i].FieldName;
          lkDBText.Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border;
          lkDBText.Font.Size    := 6;
          lkDBText.ColorDataSetIndex     := aColorDataSetIndex;
          lkDBText.ColorDataSetField     := aColorDataSetField;
          lkDBText.ColorFontDataSetIndex := aFontColorDataSetIndex;
          lkDBText.ColorFontDataSetField := aFontColorDataSetField;
          lkDBText.Top          := 0; 
          lkDBText.Height       := 16;
          lkDBText.Left         := lkLastLeft;
          lkDBText.Width        := lkText.Width;
          lkDBText.Frame.Color  := clBlack;
          lkDBText.Frame.Top    := false;
          lkDBText.Frame.Bottom := true;
          lkDBText.Frame.Left   := true;
          lkDBText.Frame.Right  := (i = (aDBGridEh.Columns.Count-1));
          end; 
        lkLastLeft := lkLastLeft + lkText.Width;
        end;
    lkRpt.Prepare;
    lkRpt.Preview;
  end;
