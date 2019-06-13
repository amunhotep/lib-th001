{$DEFINE PEAKTOP:OBJ/TMASKEDIT.INC}
  //============================================================================
  function CreateTMaskEdit(a_Owner :TComponent; a_Parent:TWinControl;
    const a_Name:string;
    const a_Left, a_Top, a_Height, a_Width:Integer
    ):TMaskEdit;
  begin
    Result            := TMaskEdit.Create(a_Owner);
    if(a_Name<>'')then
      Result.Name     := a_Name;
    Result.Parent     := a_Parent;
    Result.Color      := Amunhotep_MainForm_StyleManager.Colors.Window;
    Result.Font.Color := Amunhotep_MainForm_StyleManager.Colors.Border;
    Result.Ctl3D      := false;
    Result.Left       := a_Left;
    Result.Top        := a_Top;
    Result.Height     := a_Height;
    Result.Width      := a_Width;
    Result.Text       := '';
  end;
  //============================================================================
