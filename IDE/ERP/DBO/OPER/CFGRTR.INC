{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/CFGRTR.INC}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                        {$I PEAKTOP:OBJ/TSPLITTER.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                         {$I PEAKTOP:OBJ/TXCPANEL.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBTREEVIEW.INC}                     {$I PEAKTOP:OBJ/TXFBTREEVIEW.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}          {$I ../$COMMON/FORMERP.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}     {$I ../$COMMON/FORMERP_LANG.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_CASEOBJECT.INC}{$I ../$COMMON/DIALOG_CASEOBJECT.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/CFGRTR_ACTIONS.INC}      {$I ./CFGRTR_ACTIONS.INC}            {$ENDIF}
  //==================== PEAKTOP:IDE/ERP/DBO/OPER/CFGRTR.INC ===================
  procedure TERPFormCONF_CategoryButtons_OnButtonClicked(Sender: TObject; const Button: TButtonItem);
  var
    lkObjId :string;
  begin
    lkObjId   := '';
    case Button.Category.Index of
      0  :ERP_ObjectWizard(StrToInt(Button.Hint));
      1  :if ERPDialogCaseObj_Execute(StrToInt(Button.Hint), lkObjId) then
            ERP_ObjectEditor(lkObjId, StrToInt(Button.Hint));
      2,3:call(Button.Hint);
    end;  
  end;
  //============================================================================
  procedure TERPFormCONF_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end;
  //============================================================================
  function TERPFormCONF_Create(const aCaption:string):TAmunhotepForm;
  var
    lkSettings :TStringList;
    lkCBTNS    :TCategoryButtons;
    lkBmp      :TBitmap;
    i,j,k      :Integer;
    lkFileName :string;
    lkDTSTools :TxdbDataSetDelimited;
  begin   
    Result := TAmunhotepForm(TERPForm_Create(aCaption, ERP_FILENAME_ICO_CONFIGURATOR, ERP_FILENAME_BMP_CONFIGURATOR, false, @TERPFormCONF_OnClose));  
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    lkSettings := TERPForm_Settings(Result);
    with lkSettings do
      begin
      Values[ERP_SETTINGS_BUFFERVAR      ]:= '';
      Values[ERP_SETTINGS_TABLENAME      ]:= '';
      Values[ERP_SETTINGS_TABLECAPTION   ]:= aCaption;
      Values[ERP_SETTINGS_REF_TREE       ]:= '1';
      Values[ERP_SETTINGS_REF_TREEORGROUP]:= '1';
      Values[ERP_SETTINGS_REF_TREEFIELD  ]:= '';
      Values[ERP_SETTINGS_BASETYPE       ]:= '0';
      end;
    lkCBTNS := TCategoryButtons.Create(Result);
    with lkCBTNS do
      begin
      Name                        := 'CategoryButtons';
      Parent                      := Result;
      BorderStyle                 := bsNone;
      Align                       := alClient;
      BackgroundGradientColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
      BackgroundGradientDirection := gdLeftToRight; 
      ButtonFlow                  := cbfVertical;
      ButtonOptions               := [boGradientFill, boShowCaptions, boBoldCaptions, boCaptionOnlyBorder];
      Color                       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Name                   := 'Verdana';
      Font.Color                  := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style                  := [fsBold];
      Font.Size                   := 10;
      GradientDirection           := gdTopToBottom;
      HotButtonColor              := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      RegularButtonColor          := clNone;
      SelectedButtonColor         := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      ShowHint                    := false;
      Images                      := TImageList.Create(lkCBTNS);
      Images.Height               := 32;
      Images.Width                := 32;
      ButtonHeight                := Trunc(Images.Height * 1.2);
      ButtonWidth                 := Trunc(Images.Height * 3.6);
      OnButtonClicked             := @TERPFormCONF_CategoryButtons_OnButtonClicked;
      Categories.Clear;
      with Categories.Add do
        begin 
        ImageIndex    := -1;
        Caption       := 'Создать новый объект';
        Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
        GradientColor := Amunhotep.MainForm.StyleManager.Colors.Foreground;
        TextColor     := Amunhotep.MainForm.StyleManager.Colors.Background;
        end;
      with Categories.Add do
        begin 
        ImageIndex    := -1;
        Caption       := 'Редактировать объекты';
        Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
        GradientColor := Amunhotep.MainForm.StyleManager.Colors.Error;
        TextColor     := Amunhotep.MainForm.StyleManager.Colors.Border;
        end;
      with Categories.Add do
        begin 
        ImageIndex    := -1;
        Caption       := 'Глобальная настройка';
        Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
        GradientColor := Amunhotep.MainForm.StyleManager.Colors.HotTrack;
        TextColor     := Amunhotep.MainForm.StyleManager.Colors.Border;
        end;
      with Categories.Add do
        begin 
        ImageIndex    := -1;
        Caption       := 'Дополнительные инструменты';
        Color         := Amunhotep.MainForm.StyleManager.Colors.Background;
        GradientColor := Amunhotep.MainForm.StyleManager.Colors.Border;
        TextColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
        end;
      k := 0;
      for i:=ERP_OBJECTTYPE_REFS to ERP_OBJECTTYPES_COUNT-1 do
        begin
        j := i - ERP_OBJECTTYPE_UNKNS;
        if(i = ERP_OBJECTTYPE_JRNL)then
          begin
          with Categories[0].Items.Add do
            begin
            Caption     := ERP_ObjectCaption(i);
            CaptionSmall:= ERP_ObjectName(i);
            Hint        := IntToStr(i);
            ImageIndex  := k;
            end;
          with Categories[1].Items.Add do
            begin
            Caption     := ERP_ObjectCaptions(i);
            CaptionSmall:= ERP_ObjectName(i)+'s';
            Hint        := IntToStr(i);
            ImageIndex  := k;
            end;
          try
            lkBmp        := TBitmap.Create;
            lkBmp.Height := Images.Height;
            lkBmp.Width  := Images.Width;
            lkBmp.LoadFromFile(PrepareAbsoleteFileName(ERP_ObjectBitmap(i)));
            Images.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
          finally
            lkBmp.Free;
          end; 
          k := k + 1;
          end;     
        with Categories[0].Items.Add do
          begin
          Caption     := ERP_ObjectCaption(j);
          CaptionSmall:= ERP_ObjectName(j);
          Hint        := IntToStr(j);
          ImageIndex  := k;
          end;
        try
          lkBmp        := TBitmap.Create;
          lkBmp.Height := Images.Height;
          lkBmp.Width  := Images.Width;
          lkBmp.LoadFromFile(PrepareAbsoleteFileName(ERP_ObjectBitmap(j)));
          Images.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
        finally
          lkBmp.Free;
        end; 
        k := k + 1;
        with Categories[1].Items.Add do
          begin
          Caption     := ERP_ObjectCaptions(j);
          CaptionSmall:= ERP_ObjectName(j)+'s';
          Hint        := IntToStr(j);
          ImageIndex  := k;
          end;
        try
          lkBmp        := TBitmap.Create;
          lkBmp.Height := Images.Height;
          lkBmp.Width  := Images.Width;
          if(i = ERP_OBJECTTYPE_JRNL)then
            lkBmp.LoadFromFile(PrepareAbsoleteFileName(ERP_ObjectBitmap(j)))
           else 
            lkBmp.LoadFromFile(PrepareAbsoleteFileName(ERP_ObjectBitmap(i)));
          Images.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
        finally
          lkBmp.Free;
        end; 
        k := k + 1;
        end;
      lkFileName := PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/OPER/CFGRTR_OPERS.CONF');
      if FileExists(lkFileName)then
        begin
        lkDTSTools := TxdbDataSetDelimited.Create(nil);
        with lkDTSTools do
          begin
          TrimSpace         := true;
          ReadOnly          := true;
          FileMustExist     := true;
          Delimiter         := '|';
          FirstLineAsSchema := false;
          Schema.Clear;
          Schema.Add('ID');
          Schema.Add('NAME');
          Schema.Add('FILEPATH');
          Schema.Add('ICONPATH');
          FileName := lkFileName;
          if not Active then  
            Open;
          First;
          while not EOF do
            begin
            with Categories[2].Items.Add do
              begin
              Caption     := FieldByName('NAME').AsString;
              CaptionSmall:= FieldByName('NAME').AsString;
              Hint        := FieldByName('FILEPATH').AsString;
              ImageIndex  := k;
              end;
            try
              lkBmp        := TBitmap.Create;
              lkBmp.Height := Images.Height;
              lkBmp.Width  := Images.Width;
              lkBmp.LoadFromFile(PrepareAbsoleteFileName(FieldByName('ICONPATH').AsString));
              Images.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
            finally
              lkBmp.Free;
            end; 
            k := k + 1;
            Next;
            end; 
          if Active then 
            Close;  
          lkDTSTools.Free;     
          end;
        end;  
      lkFileName := PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/OPER/CFGRTR_TOOLS.CONF');
      if FileExists(lkFileName)then
        begin
        lkDTSTools := TxdbDataSetDelimited.Create(nil);
        with lkDTSTools do
          begin
          TrimSpace         := true;
          ReadOnly          := true;
          FileMustExist     := true;
          Delimiter         := '|';
          FirstLineAsSchema := false;
          Schema.Clear;
          Schema.Add('ID');
          Schema.Add('NAME');
          Schema.Add('FILEPATH');
          Schema.Add('ICONPATH');
          FileName := lkFileName;
          if not Active then  
            Open;
          First;
          while not EOF do
            begin
            with Categories[3].Items.Add do
              begin
              Caption     := FieldByName('NAME').AsString;
              CaptionSmall:= FieldByName('NAME').AsString;
              Hint        := FieldByName('FILEPATH').AsString;
              ImageIndex  := k;
              end;
            try
              lkBmp        := TBitmap.Create;
              lkBmp.Height := Images.Height;
              lkBmp.Width  := Images.Width;
              lkBmp.LoadFromFile(PrepareAbsoleteFileName(FieldByName('ICONPATH').AsString));
              Images.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
            finally
              lkBmp.Free;
            end; 
            k := k + 1;
            Next;
            end; 
          if Active then 
            Close;  
          lkDTSTools.Free;     
          end;
        end;  
      end;
  end;
