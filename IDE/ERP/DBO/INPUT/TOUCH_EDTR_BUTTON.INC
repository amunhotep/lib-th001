{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_BUTTON.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                           {$I PEAKTOP:OBJ/TLABEL.INC}                          {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCSTDPANEL.INC}                      {$I PEAKTOP:OBJ/TXCSTDPANEL.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_MOUSE.INC}   {$I PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_MOUSE.INC}  {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_BUTTON.INC ===========
  function TTouchEditor_CreateButton(aOwner:TComponent; aParent:TWinControl; 
             const aName, aCaption, aHint, aCaptionLeftTop, aCaptionLeftBottom:string; 
             const aAlign :TAlign; const aAlignment:TAlignment; const aLayout :TTextLayout;
             const aLeft, aTop, aHeight, aWidth :Integer; const aBorderStyle:TxcBorderStyle;
             const aColor:TColor; aOnClick :TNotifyEvent;
             const aCreateLabel:Boolean; const aFontSize:Integer):TxcStdPanel;
  begin
    Result := CreateTxcStdPanel(aOwner, aParent, aName, aCaption, aAlign, aLeft, aTop, aHeight, aWidth, aBorderStyle);
    with Result do
      begin
      StyleManager:= nil;
      Color       := aColor;
      OnClick     := aOnClick;
      OnMouseDown := @TTouchEditor_itmMouseDown;
      OnMouseUp   := @TTouchEditor_itmMouseUp;
      end;
    if aCreateLabel then  
      with CreateTLabel(Result, Result, aCaption, 1, 1, Result.Height, Result.Width, alClient, aAlignment) do
        begin
        Font.Color  := Amunhotep.MainForm.StyleManager.Colors.Window;
        Font.Size   := aFontSize;
        Font.Style  := [fsBold];
        Hint        := aHint;
        Layout      := aLayout;
        ShowHint    := True;
        Transparent := True;
        WordWrap    := True;
        OnClick     := @TTouchEditor_itmLblClick;
        OnMouseDown := @TTouchEditor_itmLblMouseDown;
        OnMouseUp   := @TTouchEditor_itmLblMouseUp;
        OnMouseMove := @TTouchEditor_itmLblMouseMove;
        OnMouseLeave:= @TTouchEditor_itmLblMouseLeave;
        end;
    if(StrTrimAll(aCaptionLeftTop)<>'')then
      with CreateTLabel(Result, Result, aCaptionLeftTop, 1, 1, 10, Result.Width, alNone, taLeftJustify) do
        begin
        Anchors     := [akLeft, akTop, akRight];
        Font.Size   := 6;
        Font.Color  := Amunhotep.MainForm.StyleManager.Colors.Window - $102020;
        OnClick     := @TTouchEditor_itmLblClick;
        OnMouseDown := @TTouchEditor_itmLblMouseDown;
        OnMouseUp   := @TTouchEditor_itmLblMouseUp;
        end;
    if(StrTrimAll(aCaptionLeftBottom)<>'')then
      with CreateTLabel(Result, Result, aCaptionLeftBottom, 1, Result.Height-14, 10, Result.Width, alNone, taLeftJustify) do
        begin
        Anchors     := [akLeft, akBottom, akRight];
        Font.Color  := Amunhotep.MainForm.StyleManager.Colors.Window - $102020;
        Font.Size   := 6;
        Font.Style  := [fsBold];
        WordWrap    := True;
        Transparent := True;
        OnClick     := @TTouchEditor_itmLblClick;
        OnMouseDown := @TTouchEditor_itmLblMouseDown;
        OnMouseUp   := @TTouchEditor_itmLblMouseUp;
        end;
  end;
