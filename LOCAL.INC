{$DEFINE PEAKTOP:LOCAL.INC}
  //========================= PEAKTOP:LOCAL.INC ================================
type 
  TAmLang = (
     lngRUS
    ,lngENG
    ,lngFRA
    ,lngDEU
    ,lngUKR
    ,lngBEL
  );
  
  function TAmunhotepLangToInt(const aLanguage :TAmLang):Integer;
  begin
    Result := 1000054;
    case aLanguage of
      lngRUS :Result := 1000054;
      lngENG :Result := 1000056;
      lngFRA :Result := 1000091;
      lngDEU :Result := 1000090;
      lngUKR :Result := 1000071;
      lngBEL :Result := 1000008;
      else    Result := 1000054;
    end;
  end; 
  
  function IntToTAmLang(const LanguageID :Integer):TAmLang;
  begin
    Result := lngRUS;
    case LanguageID of
      1000054 :Result := lngRUS;
      1000056 :Result := lngENG;
      1000091 :Result := lngFRA;
      1000090 :Result := lngDEU;
      1000071 :Result := lngUKR;
      1000008 :Result := lngBEL;
      else     Result := lngRUS;
    end;
  end; 
  
  function TAmunhotepLangToStr(const aLanguage :TAmLang):string;
  begin
    case aLanguage of
      lngRUS :Result := 'Русский';
      lngENG :Result := 'English';
      lngFRA :Result := 'Francais';
      lngDEU :Result := 'Deutsch';
      lngUKR :Result := 'Українська';
      lngBEL :Result := 'Беларуская';
    end;
  end;    
