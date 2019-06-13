{$DEFINE PEAKTOP:OBJ/TTOOLBAR.INC}
  //============================================================================
  function CreateTToolBar(aOwner:TComponent; aParent:TWinControl; 
             const aName, aCaption:string; const aAlign :TAlign;
             const aLeft, aTop, aHeight, aWidth :Integer):TToolBar;
  begin
    Result        := TToolBar.Create(aOwner);
    Result.Parent := aParent;
    if(aName<>'')then 
      Result.Name := aName;
    Result.AutoSize     := false;
    Result.Color        := Amunhotep.MainForm.StyleManager.Colors.Foreground; 
    Result.Font.Color   := Amunhotep.MainForm.StyleManager.Colors.Border; 
    Result.Caption      := aCaption;
    Result.Left         := aLeft;
    Result.Top          := aTop;
    Result.Height       := aHeight;
    Result.Width        := aWidth;
    Result.Align        := aAlign;
    Result.Flat         := true;
    Result.Images       := Amunhotep.MainForm.ImageListMain;
    Result.EdgeBorders  := [];
    Result.EdgeInner    := esNone;
    Result.EdgeOuter    := esNone;
    Result.ShowHint     := true;
  end;
  //============================================================================
