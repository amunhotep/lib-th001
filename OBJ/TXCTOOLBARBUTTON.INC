{$DEFINE PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}
  //================= PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC =========================
  function CreateTxcToolBarButton(aOwner:TComponent;aParent:TWinControl; const aName, aCaption, aHint :string; const aLeft,aTop,aHeight,aWidth:Integer;
             const aAlign :TAlign; const aImageIndex :Integer; aBtnAction :TCustomAction):TxcToolBarButton;
  var
    Cmp :TComponent;
  begin
    Cmp := aOwner.FindComponent(aName);
    if(Cmp=nil)then
      begin
      Result := TxcToolBarButton.Create(aOwner);
      if(StrTrimAll(aName) <> '')then
        Result.Name := aName;
      end
     else
      Result := TxcToolBarButton(Cmp);
    with Result do
      begin  
      Parent       := aParent;
      Left         := aLeft;
      Top          := aTop;
      Height       := aHeight;
      Width        := aWidth;
      Align        := aAlign;
      Caption      := aCaption;
      Hint         := aHint;
      Margin       := 2;
      ShowHint     := true;
      ShowCaption  := false;
      ImageIndex   := aImageIndex;
      ImagesSmall  := Amunhotep.MainForm.ImageListMain;
      Style        := bstSmall;
      StyleManager := Amunhotep.MainForm.StyleManager; 
      Action       := aBtnAction;
      end;
  end;
  //============================================================================
  function CreateTxcToolBarButton2(aOwner:TComponent;aParent:TWinControl; const aName :string; const aLeft,aTop,aHeight,aWidth:Integer;
             const aAlign:TAlign; aBtnAction :TCustomAction):TxcToolBarButton;
  begin
    Result := CreateTxcToolBarButton(aOwner, aParent, aName, aBtnAction.Caption, aBtnAction.Hint, 
      aLeft, aTop, aHeight, aWidth, aAlign, aBtnAction.ImageIndex, aBtnAction);
  end;
  //============================================================================
  function CreateTxcToolBarButton3(aOwner:TComponent;aParent:TWinControl; aBtnAction :TCustomAction):TxcToolBarButton;
  begin
    Result := CreateTxcToolBarButton2(aOwner, aParent, 'tbb'+aBtnAction.Name, 1, 1, 22, 22, alLeft, aBtnAction);
  end;    
