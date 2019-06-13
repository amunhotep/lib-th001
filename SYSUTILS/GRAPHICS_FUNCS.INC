{$DEFINE PEAKTOP:SYSUTILS/GRAPHICS_FUNCS.INC}
  //============================================================================
  function IncrementRect(const aRect :TRect; const aIncLeft, aIncTop, aIncRight, aIncBottom :Integer):TRect;
  begin
    Result.Left   := aRect.Left   + aIncLeft;
    Result.Top    := aRect.Top    + aIncTop;
    Result.Bottom := aRect.Bottom - aIncBottom;
    Result.Right  := aRect.Right  - aIncRight;
  end;
  //============================================================================
  procedure Graphics_PaintTransparentRect(aCanvas :TCanvas; aColor :TColor; aPenWidth:Integer;
              aRect :TRect);
  var
    l_BrushSt :TBrushStyle;
  begin
    aCanvas.Pen.Color   := aColor;
    aCanvas.Pen.Width   := aPenWidth;
    l_BrushSt := aCanvas.Brush.Style;
    aCanvas.Brush.Style := bsClear; 
    aCanvas.Rectangle(aRect.Left, aRect.Top, aRect.Right, aRect.Bottom);
    aCanvas.Brush.Style := l_BrushSt;
  end;
  //============================================================================
  procedure Graphics_PaintTransparentDoubleRect(aCanvas :TCanvas; aColor :TColor; aPenWidth, aRectWidth:Integer;
              aRect :TRect);
  var
    l_BrushSt :TBrushStyle;
  begin
    aCanvas.Pen.Color   := aColor;
    aCanvas.Pen.Width   := aPenWidth;
    l_BrushSt := aCanvas.Brush.Style;
    aCanvas.Brush.Style := bsClear; 
    aCanvas.Rectangle(aRect.Left           ,aRect.Top           ,aRect.Right           ,aRect.Bottom           );
    aCanvas.Rectangle(aRect.Left+aRectWidth,aRect.Top+aRectWidth,aRect.Right-aRectWidth,aRect.Bottom-aRectWidth);
    aCanvas.Brush.Style := l_BrushSt;
  end;
  //============================================================================
  procedure Graphics_PaintTransparentDoubleRectCorners(aCanvas :TCanvas; 
              aColor :TColor; aPenWidth, aRectWidth:Integer;
              aRect :TRect);
  var
    l_BrushSt :TBrushStyle;
  begin
    aCanvas.Pen.Color   := aColor;
    aCanvas.Pen.Width   := aPenWidth;
    l_BrushSt := aCanvas.Brush.Style;
    aCanvas.Brush.Style := bsClear; 
    aCanvas.Rectangle(aRect.Left           ,aRect.Top           ,aRect.Right           ,aRect.Bottom           );
    aCanvas.Rectangle(aRect.Left+aRectWidth,aRect.Top+aRectWidth,aRect.Right-aRectWidth,aRect.Bottom-aRectWidth);
    aCanvas.MoveTo(aRect.Left              ,aRect.Top                );
    aCanvas.LineTo(aRect.Left +aRectWidth  ,aRect.Top+aRectWidth     );
    aCanvas.MoveTo(aRect.Right           -1,aRect.Top                );
    aCanvas.LineTo(aRect.Right-aRectWidth-1,aRect.Top+aRectWidth     );
    aCanvas.MoveTo(aRect.Left            -1,aRect.Bottom           -1);
    aCanvas.LineTo(aRect.Left +aRectWidth-1,aRect.Bottom-aRectWidth-1);
    aCanvas.MoveTo(aRect.Right           -1,aRect.Bottom           -1);
    aCanvas.LineTo(aRect.Right-aRectWidth-1,aRect.Bottom-aRectWidth-1);
    aCanvas.Brush.Style := l_BrushSt;
  end;
  //============================================================================
  procedure Graphics_FillRect(aCanvas :TCanvas; aColor :TColor; aRect :TRect);
  var
    l_BrushSt :TBrushStyle;
  begin
    l_BrushSt := aCanvas.Brush.Style;
    aCanvas.Brush.Color := aColor;
    aCanvas.Brush.Style := bsSolid;
    aCanvas.FillRect(aRect);
    aCanvas.Brush.Style := l_BrushSt;
  end;
  //============================================================================
  procedure Graphics_PaintRazm(a_Canvas :TCanvas; a_Rect :TRect; a_Color :TColor;
              a_PenWidth, a_Indent :Integer; a_Horizontal, a_Vertical:Boolean;
              a_Caption_Hor, a_Caption_Vert :string);
  begin
    a_Canvas.Pen.Color  := a_Color;
    a_Canvas.Pen.Width  := a_PenWidth;
    a_Canvas.Font.Name  := 'Verdana';
    a_Canvas.Font.Size  := 7;
    a_Canvas.Font.Style := [fsBold];
    a_Canvas.Font.Color := a_Color;
    if(a_Vertical)then
      begin
      a_Canvas.MoveTo(a_Rect.Left+(WidthOfRect(a_Rect) div 2)- 2,a_Rect.Top       );
      a_Canvas.LineTo(a_Rect.Left - a_Indent - 8,a_Rect.Top       );
      a_Canvas.MoveTo(a_Rect.Left+(WidthOfRect(a_Rect) div 2)- 2,a_Rect.Bottom - 1);
      a_Canvas.LineTo(a_Rect.Left - a_Indent - 8,a_Rect.Bottom - 1);
      a_Canvas.MoveTo(a_Rect.Left - a_Indent    ,a_Rect.Top       );
      a_Canvas.LineTo(a_Rect.Left - a_Indent    ,a_Rect.Bottom - 1);

      a_Canvas.TextOut(
        a_Rect.Left - a_Indent - 8 - a_Canvas.TextWidth(a_Caption_Vert), 
        a_Rect.Top  + Round((HeightOfRect(a_Rect) - a_Canvas.TextHeight(a_Caption_Vert))/2), 
        a_Caption_Vert);
      end;
    if(a_Horizontal)then
      begin
      a_Canvas.MoveTo(a_Rect.Left -1,a_Rect.Bottom);
      a_Canvas.LineTo(a_Rect.Left -1,a_Rect.Bottom + a_Indent + 4);
      a_Canvas.MoveTo(a_Rect.Right-1,a_Rect.Bottom);
      a_Canvas.LineTo(a_Rect.Right-1,a_Rect.Bottom + a_Indent + 4);
      a_Canvas.MoveTo(a_Rect.Left -1,a_Rect.Bottom + a_Indent);
      a_Canvas.LineTo(a_Rect.Right-1,a_Rect.Bottom + a_Indent);
      a_Canvas.TextOut(
        a_Rect.Left + Round((WidthOfRect(a_Rect) - a_Canvas.TextWidth(a_Caption_Hor))/2), 
        a_Rect.Bottom+a_Indent+2, a_Caption_Hor);
      end;

  end;
