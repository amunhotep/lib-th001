{$DEFINE PEAKTOP:OBJ/TDBCTRLGRID.INC}
  //===================== PEAKTOP:OBJ/TDBCTRLGRID.INC ==========================
  function CreateTDBCtrlGrid(aOwner:TComponent; aParent:TWinControl; const aName:string; 
    const aLeft,aTop,aHeight,aWidth:Integer; const aAlign:TAlign; const aColCount,aRowCount:Integer):TDBCtrlGrid;
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TDBCtrlGrid(aOwner.FindComponent(aName))
     else
      Result := TDBCtrlGrid.Create(aOwner);
    with Result do
      begin
      Name          := aName;
      Parent        := aParent;
      Left          := aLeft;
      Top           := aTop;
      Height        := aHeight;
      Width         := aWidth;
      Align         := aAlign;
      ColCount      := aColCount;
      RowCount      := aRowCount;
      PanelBorder   := gbNone;
      Color         := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      SelectedColor := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      end;    
  end;
