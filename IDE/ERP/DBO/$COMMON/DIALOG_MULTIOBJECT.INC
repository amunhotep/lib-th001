{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_MULTIOBJECT.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                             {$I PEAKTOP:OBJ/TLABEL.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$I ./FORMERP.INC}            {$ENDIF}
  //============ PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_MULTIOBJECT.INC ============
  function ERP_DialogMultiObjectCreate(const aCaption, aFileNameIcon, aFileNameBitmap :string;
             const aWidth, aHeight:Integer;
             const aObjs, aObjIds, aObjNames, aObjHints, aObjCaptions, aObjImageFiles:array of string
             ):TForm;
  var
    i            :Integer;
    lkBmp        :TBitmap;
    lkStrm       :TMemoryStream;
    lkCBTNS      :TCategoryButtons;
  begin
    Result := TERPForm_Create(aCaption, aFileNameIcon, aFileNameBitmap, true, nil);
    with Result do
      begin
      Width    := aWidth;
      Height   := aHeight;
      Position := poDeskTopCenter;
      end;
    lkCBTNS := TCategoryButtons.Create(Result);
    with lkCBTNS do
      begin
      Parent                      := Result;
      Left                        := 0;
      Top                         := 100;
      Height                      := 400;
      Align                       := alClient;
      BorderStyle                 := bsNone;
      BackgroundGradientColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
      BackgroundGradientDirection := gdRightToLeft; 
      ButtonFlow                  := cbfVertical;
      ButtonHeight                := 20;
      ButtonOptions               := [boGradientFill,boFullSize,boShowCaptions,boBoldCaptions,boUsePlusMinus,boCaptionOnlyBorder];
      ButtonWidth                 := 128;
      Color                       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Name                   := 'Verdana';
      Font.Size                   := 7;//DefaultFirebirdDialogLabelFontHeight;
      Font.Style                  := [fsBold];
      GradientDirection           := gdTopToBottom;
      HotButtonColor              := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      RegularButtonColor          := clNone;
      SelectedButtonColor         := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      ShowHint                    := true;
      Images                      := TImageList.Create(lkCBTNS);
      Images.Height               := 32;
      Images.Width                := 32;
      //OnClick := @FirebirdDialog_CategoryButtons_OnDblClick; 
      Categories.Clear;
      for i:=0 to Length(aObjs)-1 do
        begin
        try
          lkBmp        := TBitmap.Create;
          lkBmp.Height := Images.Height;
          lkBmp.Width  := Images.Width;
          try
            lkStrm  := TMemoryStream.Create;
            if StreamLoadFromFile(PrepareAbsoleteFileName(aObjImageFiles[i]), lkStrm)then
              lkBmp.LoadFromStream(lkStrm);
          finally    
            lkStrm.Free;
          end;
          Images.AddMasked(lkBmp, lkBmp.Canvas.Pixels[0,0]);
        finally
          lkBmp.Free;
        end; 
        with Categories.Add do
          begin 
          ImageIndex    := i;
          Caption       := aObjCaptions[i];
          Color         := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
          GradientColor := Amunhotep.MainForm.StyleManager.Colors.Border;
          TextColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
          {
          for j:=0 to aFileConfig.Servers[i].DataBases.Count-1 do
            with Items.Add do
              begin
              Caption     := aFileConfig.Servers[i].DataBases[j].AliasName;
              CaptionSmall:= aFileConfig.Servers[i].DataBases[j].FullNameIP;
              Hint        := aFileConfig.Servers[i].DataBases[j].FullNameIP;
              ImageIndex  := 0;
              end;
          }     
          end;
        end;  
      end;
  end;
  //============================================================================
  function ERP_DialogMultiObjectExecute(const aCaption, aFileNameIcon, aFileNameBitmap :string;
             const aWidth, aHeight:Integer;
             const aObjs, aObjIds, aObjNames, aObjHints, aObjCaptions, aObjImageFiles:array of string;
             var aObjSelectedIds :array of string ):Boolean;
  var
    lkDlg :TForm;
  begin
    lkDlg := ERP_DialogMultiObjectCreate(aCaption, aFileNameIcon, aFileNameBitmap, aWidth, aHeight, aObjs, aObjIds, aObjNames, aObjHints, aObjCaptions, aObjImageFiles);
    Result := (lkDlg.ShowModal = mrOk);
    if Result then
      begin
      
      end;
    lkDlg.Free;
  end;

var
  SelectedIds :array of string; 
begin
  SetLength(SelectedIds, 2);
  if ERP_DialogMultiObjectExecute('Создать новый залог', ERP_FILENAME_ICO_DOC, ERP_FILENAME_BMP_DOC, 600, 400, 
    ['TABL$R_FIRMS','VIEW$R_TMC_GROUP_PS001'], 
    ['ID','ID'], ['NAME','NAME'], ['NAME','NAME'],
    ['Выберите фирму учета','Выберите вид залогов'], [ERP_FILENAME_BMP_REF,ERP_FILENAME_BMP_REF], SelectedIds) then
    begin
    
    end;  
end.
