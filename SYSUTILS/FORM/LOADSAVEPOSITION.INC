{$DEFINE PEAKTOP:SYSUTILS/FORM/LOADSAVEPOSITION.INC}
  //=================== PEAKTOP:SYSUTILS/FORM/LOADSAVEPOSITION.INC =============
  procedure TForm_Position_Save(aForm :TCustomForm; const aFileName :string);
  begin
    with TStringList.Create do
      begin
      if FileExists(aFileName)then
        Text := StringsLoadFromFile(aFileName); 
      Values['LEFT'  ] := IntToStr(aForm.Left  );
      Values['TOP'   ] := IntToStr(aForm.Top   );
      Values['HEIGHT'] := IntToStr(aForm.Height);
      Values['WIDTH' ] := IntToStr(aForm.Width );
      StringsSaveToFile(aFileName, Text);
      Free;
      end;
  end;
  //============================================================================
  procedure TForm_Position_Load(aForm :TForm; const aFileName :string; const aDefaultHeight, aDefaultWidth:Integer);
  begin
    with TStringList.Create do
      begin
      if FileExists(aFileName) then
        Text := StringsLoadFromFile(aFileName); 
      if(StrTrimAll(Values['HEIGHT']) = '')then Values['HEIGHT'] := IntToStr(aDefaultHeight);
      if(StrTrimAll(Values['WIDTH'] ) = '')then Values['WIDTH' ] := IntToStr(aDefaultWidth);
      if(StrTrimAll(Values['LEFT']  ) = '')then Values['LEFT'  ] := IntToStr( Trunc( (Screen.Width  - aDefaultWidth ) / 2 ) );
      if(StrTrimAll(Values['TOP']   ) = '')then Values['TOP'   ] := IntToStr( Trunc( (Screen.Height - aDefaultHeight) / 2 ) );
      with aForm do
        begin
        Position := poDesigned;
        Left     := StrToInt(Values['LEFT'  ]);
        Top      := StrToInt(Values['TOP'   ]);
        Height   := StrToInt(Values['HEIGHT']); 
        Width    := StrToInt(Values['WIDTH' ]); 
        end;
      Free;
      end; 
    TForm_Position_Save(aForm, aFileName);     
  end;
