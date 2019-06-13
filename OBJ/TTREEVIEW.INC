{$DEFINE PEAKTOP:OBJ/TTREEVIEW.INC}
  //============================================================================
  function CreateTTreeView(aOwner:TComponent; aParent:TWinControl; 
             const aName:string; const aAlign :TAlign;
             const aLeft, aTop, aHeight, aWidth :Integer):TTreeView;
  begin
    Result        := TTreeView.Create(aOwner);
    Result.Parent := aParent;
    if(aName<>'')then
      Result.Name := aName;
    Result.Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
    Result.Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
    Result.Font.Name  := 'Verdana';
    Result.Font.Size  := 7;
    Result.Left       := aLeft; 
    Result.Top        := aTop; 
    Result.Height     := aHeight; 
    Result.Width      := aWidth; 
    Result.Align      := aAlign;
    Result.Ctl3D      := false; 
  end;
  //============================================================================  
