{$DEFINE PEAKTOP:COM/ORACLE/OPENOFFICE/CALC.INC}
  //====================== PEAKTOP:COM/ORACLE/OPENOFFICE/CALC.INC ==============
type
  TOracleOpenOfficeCalcSelection = record
    StartCol :Integer;
    StartRow :Integer;
    EndCol   :Integer;
    EndRow   :Integer;
  end;
  TOracleOpenOfficeCalcBorderStyleEnum = (obsLeft,obsTop,obsRight,obsBottom);
  TOracleOpenOfficeCalcBorderStyle     = set of TOracleOpenOfficeCalcBorderStyleEnum;
  TOracleOpenOfficeCalcFontStyleEnum   = (ofsBold, ofsUnderline, ofsItalic, ofsStrikeOut);
  TOracleOpenOfficeCalcFontStyle       = set of TOracleOpenOfficeCalcFontStyleEnum;
  TOracleOpenOfficeCalcHAlignment      = (ohaDefault, ohaLeft, ohaCenter, ohaRight , ohaNone);
  TOracleOpenOfficeCalcVAlignment      = (ovaDefault, ovaTop , ovaCenter, ovaBottom, ovaNone);
  //============================================================================
  function OracleOpenOfficeCalc_IntToColIndex(const aInt :Integer):string;
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
  function TAlignmentToTOracleOpenOfficeCalcHAlignment(const aAlignment:TAlignment):TOracleOpenOfficeCalcHAlignment;
  begin
    case aAlignment of
      taLeftJustify  :Result := ohaLeft;
      taRightJustify :Result := ohaRight;
      taCenter       :Result := ohaCenter;
    end;   
  end;
  //============================================================================
  function TColorToTOracleOpenOfficeColor(const aColor :TColor):Integer;
  var 
    lkRed , lkGreen , lkBlue  :Byte; 
    lkRedI, lkGreenI, lkBlueI :Integer; 
  begin
    lkRed   := Byte(aColor); 
    lkGreen := Byte(aColor shr 8); 
    lkBlue  := Byte(aColor shr 16);
    lkRedI   := lkRed  ; lkRedI   := lkRedI   shl 16; 
    lkGreenI := lkGreen; lkGreenI := lkGreenI shl  8; 
    lkBlueI  := lkBlue ; lkBlueI  := lkBlueI  ; 
    Result  := lkRedI or lkGreenI or lkBlueI;
//    Result  := aColor; 
  end;
