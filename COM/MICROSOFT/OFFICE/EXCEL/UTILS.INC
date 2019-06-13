{$DEFINE PEAKTOP:COM/MICROSOFT/OFFICE/EXCEL/UTILS.INC}
{$IFNDEF PEAKTOP:COM/MICROSOFT/OFFICE/EXCEL/CONST.INC}{$I ./CONST.INC} {$ENDIF}
  //================ PEAKTOP:COM/MICROSOFT/OFFICE/EXCEL/UTILS.INC ==============
  function MSExcel_IntToColIndex(const aInt :Integer):string;
  var
    lkInt, lkMod :Integer;
  begin
    Result := ''; if(aInt <= 0)then begin Result := 'A'; exit; end;
    lkInt := aInt;  
    while(lkInt <> 0)do
      begin 
      lkMod := (lkInt mod 26);
      if(lkMod = 0)then
        begin
        lkInt := (lkInt - lkMod) / 26 - 1;
        Result:= 'Z' + Result;
        end
       else
        begin
        lkInt := (lkInt - lkMod) / 26;
        Result:= Chr((Ord('A')-1) + lkMod) + Result;
        end;
      end;  
  end;
  //============================================================================
  function MSExcel_AlignmentToHorizontalAlignment(const aAlignment:TAlignment):Integer;
  begin
    case aAlignment of
      taLeftJustify  :Result := MSEXCEL_xlLeft;   //2;
      taCenter       :Result := MSEXCEL_xlCenter; //3;
      taRightJustify :Result := MSEXCEL_xlRight;  //4;
    end; 
  end;
  //============================================================================
  procedure MSExcel_TFontToFont(const aFont :TFont; aExcelFont :Variant);
  begin
    with aFont do
      begin
      aExcelFont.Color  := Color;
      aExcelFont.Name   := Name;
      aExcelFont.Size   := Size;
      if(Style = (Style + [fsBold]  ))then aExcelFont.Bold   := true;
      if(Style = (Style + [fsItalic]))then aExcelFont.Italic := true;
      end;
  end;
  //============================================================================
  procedure MSExcel_DrawGridByRange(const aRangeName:string; aExcelWorkSheet :Variant);
  begin
    aExcelWorkSheet.Range[aRangeName].Borders.LineStyle     := MSEXCEL_xlContinuous;
    aExcelWorkSheet.Range[aRangeName].Borders.Weight        := MSEXCEL_xlThin;
    aExcelWorkSheet.Range[aRangeName].Borders[MSEXCEL_xlEdgeTop   ].ColorIndex := 1;
    aExcelWorkSheet.Range[aRangeName].Borders[MSEXCEL_xlEdgeLeft  ].ColorIndex := 1;
    aExcelWorkSheet.Range[aRangeName].Borders[MSEXCEL_xlEdgeRight ].ColorIndex := 1;
    aExcelWorkSheet.Range[aRangeName].Borders[MSEXCEL_xlEdgeBottom].ColorIndex := 1;
  end;
