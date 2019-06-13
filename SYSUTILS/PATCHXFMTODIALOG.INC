{$DEFINE PEAKTOP:SYSUTILS/PATCHXFMTODIALOG.INC}
  //============================================================================
  function PatchXFMToDialog(const aResourceBody:string):string;
  var
    i     :Integer;
    lk_SL :TStringList;
  begin
    lk_SL      := TStringList.Create;
    lk_SL.Text := aResourceBody;
    if(Pos('TAMUNHOTEPFORM', AnsiUpperCase(lk_SL[0]))>0)then
      lk_SL[0] := StrReplaceStr(lk_SL[0], 'TAmunhotepForm', 'TForm');
    i := 1;
    while(i < lk_SL.Count)do
      begin
      if(Pos('  OBJECT ', AnsiUpperCase(lk_Sl[i]))>0)then break;
      if(lk_SL[i][3]<>#32)then
        begin
        //WriteLn(lk_SL[i]);
        if((Pos('FORMSTYLE =', AnsiUpperCase(lk_SL[i]))>0)or
           (Pos('ONCLOSE ='  , AnsiUpperCase(lk_SL[i]))>0)or
           (Pos('ONCREATE =' , AnsiUpperCase(lk_SL[i]))>0)or
           (Pos('ONCLOSE ='  , AnsiUpperCase(lk_SL[i]))>0))then
          begin
          lk_Sl.Delete(i);
          i := i - 1;
          end;
        if(Pos('VISIBLE = ', AnsiUpperCase(lk_SL[i]))>0)then
          lk_Sl[i] := '  Visible = False';
        end;  
      i := i + 1;  
      end;  
    Result := lk_SL.Text;
    lk_SL.Free;  
  end;
  //============================================================================
