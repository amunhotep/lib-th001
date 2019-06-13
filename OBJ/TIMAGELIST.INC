{$DEFINE PEAKTOP:OBJ/TIMAGELIST.INC}
  //====================== PEAKTOP:OBJ/TIMAGELIST.INC ==========================
  function CreateTImageListSimple(a_Owner:TComponent; const a_Name:string; const a_Height, a_Width:Integer):TImageList;
  begin
    if(a_Owner.FindComponent(a_Name) = nil)then
      Result  := TImageList.Create(a_Owner)
     else
      Result  := TImageList(a_Owner.FindComponent(a_Name))
    with Result do
      begin
      if(StrTrimAll(a_Name) <> '')then
        Name := a_Name;
      Height := a_Height;
      Width  := a_Width;
      Clear;
      end;
  end;
  //============================================================================
  function CreateTImageList(a_Owner:TComponent; const a_Name :string; const a_Indicies :array of Integer):TImageList;
  var
    lkCntr :Integer;
  begin
    Result := CreateTImageListSimple(a_Owner, a_Name, Amunhotep.MainForm.ImageListMain.Height, Amunhotep.MainForm.ImageListMain.Width);
    with Result do
      for lkCntr:=0 to Length(a_Indicies)-1 do
        AddImage(Amunhotep.MainForm.ImageListMain, a_Indicies[lkCntr]);
  end;
