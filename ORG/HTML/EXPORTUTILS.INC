{$DEFINE PEAKTOP:ORG/HTML/EXPORTUTILS.INC}
  //================= PEAKTOP:ORG/HTML/EXPORTUTILS.INC =========================
  function HTML_IfEmptyStr(const aStr:string):string;
  begin
    Result := aStr;
    if(StrTrimAll(Result) = '')then
      Result := '&nbsp;';
  end;
  //============================================================================
  function HTML_TColorToColor(const aColor:TColor):string;
  var
    lkStr :string;
  begin
    lkStr := ColorToStr(aColor);
    Result:= '#'+Copy(lkStr, 8, 2) + Copy(lkStr, 6, 2) + Copy(lkStr, 4, 2);
  end;
  //============================================================================
  function HTML_TAlignmentToAlign(const aAlignment:TAlignment):string;
  begin
    case aAlignment of
      taLeftJustify  :Result := 'left';   //2;
      taCenter       :Result := 'center'; //3;
      taRightJustify :Result := 'right';  //4;
    end; 
  end;  
