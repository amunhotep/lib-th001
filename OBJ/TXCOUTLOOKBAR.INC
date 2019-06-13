{$DEFINE PEAKTOP:OBJ/TXCOUTLOOKBAR.INC}
  //============================================================================
  function CreateTxcOutlookBar(aOwner:TComponent; aParent :TWinControl; 
             const aName:string; 
             const aAlign :TAlign;
             const aLeft, aTop, aHeight, aWidth :Integer):TxcOutlookBar;
  begin
    Result := nil;
    if(aName<>'')then
      Result := TxcOutlookBar(aOwner.FindComponent(aName));
    if(Result=nil)then
      Result := TxcOutlookBar.Create(aOwner);
    Result.Visible := false;  
    Result.Parent  := aParent;
    if(aName<>'')then 
      Result.Name := aName;
    Result.StyleManager  := Amunhotep.MainForm.StyleManager;
    Result.Images        := Amunhotep.MainForm.ImageListMain;
    Result.Left          := aLeft;
    Result.Top           := aTop;
    Result.Height        := aHeight;
    Result.Width         := aWidth;
    Result.Align         := aAlign;
    Result.Visible       := true;  
  end;
  //============================================================================
  function CreateTxcOutlookHeader(ParentBar:TxcOutlookBar; 
             const aName, aCaption:string; 
             const aAlignment :TAlignment;
             const aImageIndex:Integer;
             const aButtonStyle:TxcButtonsStyle;
             const aGradientDirect:TxcGradientDirect):TxcOutlookHeader;
  var
    lk_i :Integer;
  begin
    Result := nil;
    if(ParentBar=nil)then exit;
    if(aName<>'')then
      for lk_i:=0 to ParentBar.HeaderCount-1 do
        if(AnsiUpperCase(ParentBar.GetHeader(lk_i).Name) = AnsiUpperCase(aName))then
          begin
          Result := ParentBar.GetHeader(lk_i);
          break;
          end;
    if(Result=nil)then
      Result := ParentBar.AddHeader(aCaption);
    if(aName='')then
      Result.Name         := aName;
    Result.Caption        := aCaption;
    Result.Alignment      := aAlignment;
    Result.ImageIndex     := aImageIndex;
    Result.ImagesSmall    := Amunhotep.MainForm.ImageListMain;
    Result.ButtonsStyle   := aButtonStyle; 
    Result.GradientDirect := aGradientDirect;
  end;
  //============================================================================
  
