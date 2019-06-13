{$DEFINE PEAKTOP:OBJ/TTOOLBUTTON.INC}
  //===================== PEAKTOP:OBJ/TTOOLBUTTON.INC ==========================
  function CreateTToolButton(aOwner:TComponent; aParent:TWinControl; 
             const aName, aCaption, aHint:string;
             const a_Left,a_Top,a_Height,a_Width:Integer;
             const aStyle :TToolButtonStyle):TToolButton;
  begin
    Result        := TToolButton.Create(aOwner);
    Result.Parent := aParent;
    if(aName<>'')then 
      Result.Name := aName;
    Result.Caption    := aCaption;
    Result.Hint       := aHint;
    Result.Style      := aStyle;
    Result.Left       := a_Left;
    Result.Top        := a_Top;
    Result.Height     := a_Height;
    Result.Width      := a_Width;
    Result.Visible    := true;
  end;
  //============================================================================
  function CreateTToolButton2(aOwner:TComponent; aParent:TWinControl; 
             const aName, aCaption, aHint:string;
             const a_Left,a_Top,a_Height,a_Width:Integer;
             const aStyle :TToolButtonStyle;
             a_BtnAction :TCustomAction):TToolButton;
  begin
    Result        := TToolButton.Create(aOwner);
    Result.Parent := aParent;
    if(aName<>'')then 
      Result.Name := aName;
    Result.Caption    := aCaption;
    Result.Hint       := aHint;
    Result.Style      := aStyle;
    Result.Left       := a_Left;
    Result.Top        := a_Top;
    Result.Height     := a_Height;
    Result.Width      := a_Width;
    Result.Action     := a_BtnAction;
    Result.Visible    := true;
  end;
