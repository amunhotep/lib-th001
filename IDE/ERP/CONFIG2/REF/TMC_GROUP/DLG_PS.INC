{$DEFINE DB:CONFIG/REF/TMC_GROUP/DLG_PS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}            {$I PEAKTOP:GLOBAL_VARIABLES.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGE.INC}                  {$I PEAKTOP:OBJ/TIMAGE.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}   {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}{$ENDIF}
  //============================================================================
  procedure DialogTMCGroup_ListView_OnDblClick(Sender :TObject);
  begin
    TCustomForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  procedure DialogTMCGroup_CBTNS_OnButtonClicked(Sender: TObject; const Button: TButtonItem);
  begin
    TCustomForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  function DialogTMCGroup_Execute(const aCaption, aParentGroupId:string; var aTMCGroupId:string):Boolean;
  var
    lkForm        :TForm;
    lkCBTNS       :TCategoryButtons;
    lkBmp         :TBitmap;
    lkSL          :TStringList;
    i             :Integer;
    lkStr         :string;
    lkFileName    :string;
  begin
    Result := false;
    lkStr  := ''; GetField(FBDataBase, 'TABL$R_TMC_GROUP','NAME','ID='+aParentGroupId, lkStr);

    lkForm := TForm.Create(nil);
    with lkForm do
      begin
      Caption         := 'Âûבונטעו ןנוהלוע חאכמדא';
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderStyle     := bsDialog;
      BorderIcons     := [biSystemMenu];
{$IFDEF TRANSPARENT}  
      AlphaBlendValue := 232;
      AlphaBlend      := true;
{$ENDIF}  
      Position        := poDesktopCenter;
      Width           := Trunc(Screen.Width  * 2 / 3);
      Height          := Trunc(Screen.Height * 2 / 3);
      Font.Size       := 7;
      Font.Style      := [fsBold];
      end;
    lkCBTNS  := TCategoryButtons.Create(lkForm);
    with lkCBTNS do
      begin
      Name                        := 'CategoryButtons';
      Parent                      := lkForm;
      Align                       := alClient;
      BackgroundGradientColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
      BackgroundGradientDirection := gdRightToLeft; 
      ButtonFlow                  := cbfVertical;
      ButtonHeight                := 36;
      ButtonOptions               := [boGradientFill,boShowCaptions,boBoldCaptions,boUsePlusMinus,boCaptionOnlyBorder];
      ButtonWidth                 := 160;
      Color                       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Color                  := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Name                   := 'Verdana';
      Font.Size                   := 7;
      Font.Style                  := [fsBold];
      GradientDirection           := gdTopToBottom;
      HotButtonColor              := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      RegularButtonColor          := clNone;
      SelectedButtonColor         := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      ShowHint                    := true;
      Images                      := TImageList.Create(lkCBTNS);
      Images.Height               := 32;
      Images.Width                := 32;
      Categories.Clear;
      with Categories.Add do
        begin 
        ImageIndex    := 0;
        Caption       := '['+aParentGroupId+'] '+lkStr;
        Color         := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
        GradientColor := Amunhotep.MainForm.StyleManager.Colors.Border;
        TextColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
        Items.Clear;
        end;
      lkStr := '';  
      if GetField(FBdataBase, 'TABL$R_TMC_GROUP', 'ID||''||''||NAME', 'PARENT_ID = '+aParentGroupId+' ORDER BY NAME', lkStr)then
        begin
        lkSL := TStringList.Create;
        lkSL.Text := lkStr;
        for i:=0 to lkSL.Count-1 do
          begin
          lkStr := lkSL[i];
          Delete(lkStr, 1, Pos('||',lkStr) + 1);
          
          lkBmp        := TBitmap.Create;
          lkBmp.Height := Images.Height;
          lkBmp.Width  := Images.Width;
          lkBmp.Canvas.Brush.Color := clFuchsia; 
          lkBmp.Canvas.FillRect(Rect(0,0,Height,Width));
          lkFileName := StrAbsolutePath('./IMG/CONFIG/PS/TMCGROUP'+StrCiphersOnlyInt(Copy(lkSL[i], 1, Pos('||',lkSL[i])))+'.BMP', Amunhotep.SourcePath);
          if FileExists(lkFileName)then 
            lkBmp.LoadFromFile(lkFileName)
           else
            begin
            lkFileName := StrAbsolutePath('./IMG/CONFIG/PS/TMCGROUP0'+aParentGroupId+'.BMP', Amunhotep.SourcePath);
            if FileExists(lkFileName)then lkBmp.LoadFromFile(lkFileName)
            end;  
          Images.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
          lkBmp.Free;
          
          with Categories[0].Items.Add do
            begin
            Caption     := lkStr;
            CaptionSmall:= StrCiphersOnlyInt(Copy(lkSL[i], 1, Pos('||',lkSL[i])));
            Hint        := lkStr;
            ImageIndex  := Images.Count - 1;
            end; 
          end;
        lkSL.Free;
        end;
      lkFileName := '';
      OnButtonClicked := @DialogTMCGroup_CBTNS_OnButtonClicked;
      end;
    lkForm.ActiveControl := lkCBTNS;  
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      Result := (lkCBTNS.Categories[0].Items.Count > 0);
      if Result then
        Result := ObjectInheritsFrom(lkCBTNS.SelectedItem, 'TButtonItem');
      if Result then        
        aTMCGroupId := TButtonItem(lkCBTNS.SelectedItem).CaptionSmall;
      end;
    lkForm.Free;
  end;
