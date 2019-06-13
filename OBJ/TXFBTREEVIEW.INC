{$DEFINE PEAKTOP:OBJ/TXFBTREEVIEW.INC}
  //====================== PEAKTOP:OBJ/TXFBTREEVIEW.INC ========================
  function CreateTxFBTreeView(aOwner:TComponent; aParent:TWinControl; const aName:string;
             const aLeft, aTop, aHeight, aWidth:Integer; const aAlign:TAlign):TxFBTreeView;
  var
    lkCmp :TComponent;
  begin
    lkCmp := aOwner.FindComponent(aName);
    if(lkCmp <> nil)then
      Result := TxFBTreeView(lkCmp)
     else
      Result := TxFBTreeView.Create(aOwner);
    with Result do
      begin
      if(StrTrimAll(aName) <> '')then
        Name   := aName;   
      Parent           := aParent;
      Ctl3D            := false;
      Left             := aLeft;
      Top              := aTop;
      Height           := aHeight;
      Width            := aWidth;
      Align            := aAlign;
      RightClickSelect := true;
      HideSelection    := false;
      DataBase         := FBDataBase;
      Color            := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color       := Amunhotep.MainForm.StyleManager.Colors.Border;
      end; 
  end;
