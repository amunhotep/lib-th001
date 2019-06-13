{$DEFINE PEAKTOP:OBJ/TMEMO.INC}
  //========================== PEAKTOP:OBJ/TMEMO.INC ===========================
  function CreateTMemo(a_Owner :TComponent; a_Parent:TWinControl; const a_Name:string; const a_Left, a_Top, a_Height, a_Width:Integer; const a_Align :TAlign):TMemo;
  begin
    if(a_Owner.FindComponent(a_Name) <> nil)then
      Result := TMemo(a_Owner.FindComponent(a_Name))
     else 
      Result := TMemo.Create(a_Owner);
    with Result do
      begin  
      Name       := a_Name;
      Parent     := a_Parent;
      Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
      Font.Size  := 8;
      Font.Style := [fsBold];
      Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
      Ctl3D      := false;
      Left       := a_Left;
      Top        := a_Top;
      Height     := a_Height;
      Width      := a_Width;
      Align      := a_Align;
      Text       := '';
      WordWrap   := true;
      ScrollBars := ssBoth;
      end;
  end;
