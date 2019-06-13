{$DEFINE PEAKTOP:OBJ/TDATETIMEPICKER.INC}
  //=================== PEAKTOP:OBJ/TDATETIMEPICKER.INC ========================
  function CreateTDateTimePicker(aOwner :TComponent; aParent:TWinControl; const aName:string; const aLeft, aTop, aHeight, aWidth:Integer; const aInitDate:TDateTime):TDateTimePicker;
  var
    lkCmp :TComponent;  
  begin
    lkCmp := aOwner.FindComponent(aName);
    if(lkCmp <> nil)then
      Result := TDateTimePicker(lkCmp)
     else
      Result := TDateTimePicker.Create(aOwner);
    with Result do
      begin  
      if(aName <> '')then
        Name     := aName;
      Parent     := aParent;
      Left       := aLeft;
      Top        := aTop;
      Height     := aHeight;
      Width      := aWidth;
      Kind       := dtkDate;
      Date       := aInitDate;
      Font.Style := [fsBold];
      Font.Name  := 'Verdana';
      Font.Size  := 7;
      with Amunhotep.MainForm.StyleManager.Colors do
        begin 
        Color      := Window;
        Font.Color := Border;
        with CalColors do
          begin
          BackColor         := Window;
          MonthBackColor    := Window;
          TextColor         := Border;
          TitleBackColor    := HotTrackBorder;
          TitleTextColor    := Window;
          TrailingTextColor := Foreground;
          end; 
        end;
      end;
  end;  
