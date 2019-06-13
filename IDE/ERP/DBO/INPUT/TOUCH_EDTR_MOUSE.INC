{$DEFINE PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_MOUSE.INC}
  //================= PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR_MOUSE.INC ===========
  procedure TTouchEditor_itmMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
  begin
    TxcStdPanel(Sender).BorderStyle       := xbsRaized;
    TxcStdPanel(Sender).Colors.Background := Amunhotep.MainForm.StyleManager.Colors.Border;
  end;
  //============================================================================
  procedure TTouchEditor_itmMouseLeave(Sender: TObject);
  begin
    TxcStdPanel(Sender).BorderStyle       := xbsNone;
    TxcStdPanel(Sender).Colors.Background := Amunhotep.MainForm.StyleManager.Colors.Background;
  end;
  //============================================================================
  procedure TTouchEditor_itmMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
  begin
    TxcStdPanel(Sender).BorderStyle := xbsLowered;
    TxcStdPanel(Sender).Color       := TxcStdPanel(Sender).Color xor $202020;
  end;
  //============================================================================
  procedure TTouchEditor_itmMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
  begin
    TxcStdPanel(Sender).BorderStyle := xbsNone;
    TxcStdPanel(Sender).Color       := TxcStdPanel(Sender).Color xor $202020;
  end; 
  //============================================================================
  procedure TTouchEditor_itmLblMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
  begin
    TTouchEditor_itmMouseDown(TComponent(Sender).Owner, Button, Shift, X, Y);
  end;
  //============================================================================
  procedure TTouchEditor_itmLblMouseUp(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
  begin
    TTouchEditor_itmMouseUp(TComponent(Sender).Owner, Button, Shift, X, Y);
  end;
  //============================================================================
  procedure TTouchEditor_itmLblMouseMove(Sender: TObject; Shift: TShiftState; X, Y: Integer);
  begin
    TTouchEditor_itmMouseMove(TComponent(Sender).Owner, Shift, X, Y);
  end;
  //============================================================================
  procedure TTouchEditor_itmLblMouseLeave(Sender: TObject);
  begin
    TTouchEditor_itmMouseLeave( TComponent(Sender).Owner );
  end;
  //============================================================================
  procedure TTouchEditor_itmLblClick(Sender :TObject);
  begin
    if ObjectInheritsFrom(TComponent(Sender).Owner, 'TxcStdPanel')then
      with TxcStdPanel( TComponent(Sender).Owner ) do
        if(OnClick <> nil) then
          OnClick( TComponent(Sender).Owner );
  end;
