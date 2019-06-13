{$DEFINE PEAKTOP:OBJ/TDBCHART.INC}
  //======================= PEAKTOP:OBJ/TDBCHART.INC ===========================
  procedure TDBChart_SetDefaultProperties(aDBChart :TDBChart);
  begin
    with aDBChart do
      begin
      BevelInner   := bvNone;
      BevelOuter   := bvNone;
      MarginLeft   := 0;
      MarginTop    := 0;
      MarginRight  := 0;
      MarginBottom := 4;
      View3D       := false;   
      with Border do
        begin
        Color   := Amunhotep.MainForm.StyleManager.Colors.Background;
        Width   := 1;
        Visible := true;
        end;
      with Gradient do
        begin
        Balance   := 80;
        Direction := gdTopBottom;
        EndColor  := Amunhotep.MainForm.StyleManager.Colors.Foreground;
        MidColor  := Amunhotep.MainForm.StyleManager.Colors.Window;
        StartColor:= Amunhotep.MainForm.StyleManager.Colors.Window;
        Visible   := true;
        end;
      with Title do
        begin
        Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
        Font.Name  := 'Verdana';
        Font.Size  := 7;
        Font.Style := [fsBold]; 
        end; 
      end;
  end;
  //============================================================================
  function CreateTDBChart(aOwner:TComponent; aParent:TWinControl; const aName, aTitle:string;
             const aLeft,aTop,aHeight,aWidth:Integer; const aAlign:TAlign):TDBChart;
  begin
    Result := TDBChart.Create(aOwner);
    with Result do
      begin
      if(aName<>'')then
        Name  := aName;
      Parent  := aParent;
      Left    := aLeft;
      Top     := aTop;
      Height  := aHeight;
      Width   := aWidth;
      Align   := aAlign;
      Title.Text.Text  := aTitle;
      end;
    TDBChart_SetDefaultProperties(Result);  
  end;
