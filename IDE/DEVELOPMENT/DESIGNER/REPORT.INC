{$DEFINE PEAKTOP:IDE/DEVELOPMENT/DESIGNER/REPORT.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}               {$I PEAKTOP:OBJ/TACTION.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TTOOLBAR.INC}              {$I PEAKTOP:OBJ/TTOOLBAR.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.2.INC}    {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.2.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$ENDIF}
const
  msg_act_border_none                     = 'Нет границ';
  msg_act_border_all                      = 'Обвести';
  msg_act_border_left                     = 'Левая граница';
  msg_act_border_top                      = 'Верхняя граница';
  msg_act_border_right                    = 'Правая граница';
  msg_act_border_bottom                   = 'Нижняя граница';
  msg_act_border_leftright                = 'Левая и правая граница';
  msg_act_border_topbottom                = 'Верхняя и нижняя граница';
  msg_act_border_lefttop                  = 'Левая и верхняя граница';
  msg_act_border_rightbottom              = 'Правая и нижняя граница';
  msg_act_format_bold                     = 'Жирный';
  msg_act_format_italic                   = 'Курсив';
  msg_act_format_underline                = 'Подчеркивание';
  msg_act_format_strikeout                = 'Зачеркнутый';
  msg_act_fillcolor                       = 'Заливка';
  msg_act_fontcolor                       = 'Цвет шрифта';
const
  ComponentNameToolBarReport = 'ToolBarReport';  
  ColorPanelMargin = 6;
  //============================================================================
  function ValidxReportComponent:Boolean;
  var
    i :Integer;
  begin
    Result := false;
    if(not(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.Count>0))then exit;
    Result := true;
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      for i:=0 to SelectedComponents.Count-1 do
        if(not(ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') or ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') ))then 
          begin
          Result := false;
          break;
          end;
  end;
  //============================================================================
  procedure SetBorder(const SetFlags, SetValues :array of Boolean);
  var
    i :Integer;
  begin
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      for i:=0 to SelectedComponents.Count-1 do
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          begin
          if(SetFlags[0])then TxrPrintable(SelectedComponents[i]).Frame.Left   := SetValues[0];
          if(SetFlags[1])then TxrPrintable(SelectedComponents[i]).Frame.Top    := SetValues[1];
          if(SetFlags[2])then TxrPrintable(SelectedComponents[i]).Frame.Right  := SetValues[2];
          if(SetFlags[3])then TxrPrintable(SelectedComponents[i]).Frame.Bottom := SetValues[3];
          end
         else 
          if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
            begin
            if(SetFlags[0])then TxrBasePanel(SelectedComponents[i]).Frame.Left   := SetValues[0];
            if(SetFlags[1])then TxrBasePanel(SelectedComponents[i]).Frame.Top    := SetValues[1];
            if(SetFlags[2])then TxrBasePanel(SelectedComponents[i]).Frame.Right  := SetValues[2];
            if(SetFlags[3])then TxrBasePanel(SelectedComponents[i]).Frame.Bottom := SetValues[3];
            end;
  end;
  //============================================================================
  procedure UpdateFonts;
  var
    lkCmbxFont      :TComboBox;
    lkCmbxFontSize  :TComboBox;
  begin
    lkCmbxFont      := TComboBox(Amunhotep.MainForm.ActiveMDIChild.FindComponent('ComboBoxFontNames'));
    lkCmbxFontSize  := TComboBox(Amunhotep.MainForm.ActiveMDIChild.FindComponent('ComboBoxFontSize'));
    if((lkCmbxFont = nil) or (lkCmbxFont = nil))then exit;
    lkCmbxFont.Enabled     := false;
    lkCmbxFont.Color       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
    lkCmbxFontSize.Enabled := false;
    lkCmbxFontSize.Color   := Amunhotep.MainForm.StyleManager.Colors.Foreground;
    if(Amunhotep.MainForm.DesignManager.CurrentDesigner = nil)then exit;
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      if(SelectedComponents.Count > 0)then
        begin
        if ObjectInheritsFrom(SelectedComponents[0],'TxrPrintable') then
          begin
          lkCmbxFont.ItemIndex   := lkCmbxFont.Items.IndexOf(TxrPrintable(SelectedComponents[0]).Font.Name);
          lkCmbxFontSize.Text    := IntToStr(TxrPrintable(SelectedComponents[0]).Font.Size);
          lkCmbxFont.Enabled     := true;
          lkCmbxFont.Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
          lkCmbxFontSize.Enabled := true;
          lkCmbxFontSize.Color   := Amunhotep.MainForm.StyleManager.Colors.Window;
          end;
        if ObjectInheritsFrom(SelectedComponents[0],'TxrCustomBand') then
          begin
          lkCmbxFont.ItemIndex   := lkCmbxFont.Items.IndexOf(TxrCustomBand(SelectedComponents[0]).Font.Name);
          lkCmbxFontSize.Text    := IntToStr(TxrCustomBand(SelectedComponents[0]).Font.Size);
          lkCmbxFont.Enabled     := true;
          lkCmbxFont.Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
          lkCmbxFontSize.Enabled := true;
          lkCmbxFontSize.Color   := Amunhotep.MainForm.StyleManager.Colors.Window;
          end;
        if ObjectInheritsFrom(SelectedComponents[0],'TCustomXReport') then
          begin
          lkCmbxFont.ItemIndex   := lkCmbxFont.Items.IndexOf(TCustomXReport(SelectedComponents[0]).Font.Name);
          lkCmbxFontSize.Text    := IntToStr(TCustomXReport(SelectedComponents[0]).Font.Size);
          lkCmbxFont.Enabled     := true;
          lkCmbxFont.Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
          lkCmbxFontSize.Enabled := true;
          lkCmbxFontSize.Color   := Amunhotep.MainForm.StyleManager.Colors.Window;
          end;
        end;
  end;
  //============================================================================
  procedure ComboBoxFontNames_OnCloseUp(Sender :TObject);
  var
    i :Integer;
  begin
    if(Amunhotep.MainForm.DesignManager.CurrentDesigner = nil)then exit;
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      for i:=0 to SelectedComponents.Count-1 do
        begin
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          TxrPrintable(SelectedComponents[i]).Font.Name := TComboBox(Sender).Items[TComboBox(Sender).ItemIndex];
        if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
          TxrCustomBand(SelectedComponents[i]).Font.Name := TComboBox(Sender).Items[TComboBox(Sender).ItemIndex];
        if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
          TCustomXReport(SelectedComponents[i]).Font.Name := TComboBox(Sender).Items[TComboBox(Sender).ItemIndex];
        end;
  end;
  //============================================================================
  procedure ComboBoxFontSize_OnCloseUp(Sender :TObject);
  var
    i :Integer;
  begin
    if(Amunhotep.MainForm.DesignManager.CurrentDesigner = nil)then exit;
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      for i:=0 to SelectedComponents.Count-1 do
        begin
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          TxrPrintable(SelectedComponents[i]).Font.Size := StrToInt(TComboBox(Sender).Items[TComboBox(Sender).ItemIndex]);
        if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
          TxrCustomBand(SelectedComponents[i]).Font.Size := StrToInt(TComboBox(Sender).Items[TComboBox(Sender).ItemIndex]);
        if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
          TCustomXReport(SelectedComponents[i]).Font.Size := StrToInt(TComboBox(Sender).Items[TComboBox(Sender).ItemIndex]);
        end;
  end;
  //============================================================================
  procedure actBorderNone_OnExecute(Sender :TObject);
  begin
    SetBorder([true,true,true,true],[false,false,false,false])
  end;
  //============================================================================
  procedure actBorderNone_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk and (not TxrPrintable(SelectedComponents[i]).Frame.AnyFrame)
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk and (not TxrBasePanel(SelectedComponents[i]).Frame.AnyFrame);
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderAll_OnExecute(Sender :TObject);
  var
    lkChk :Boolean;
  begin
    lkChk := not TCustomAction(Sender).Checked;
    SetBorder([true,true,true,true],[lkChk,lkChk,lkChk,lkChk])
  end;
  //============================================================================
  procedure actBorderAll_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            begin
            lkChk := lkChk 
               and TxrPrintable(SelectedComponents[i]).Frame.Left
               and TxrPrintable(SelectedComponents[i]).Frame.Top
               and TxrPrintable(SelectedComponents[i]).Frame.Right
               and TxrPrintable(SelectedComponents[i]).Frame.Bottom;
            end
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then
              begin 
              lkChk := lkChk 
                 and TxrBasePanel(SelectedComponents[i]).Frame.Left
                 and TxrBasePanel(SelectedComponents[i]).Frame.Top
                 and TxrBasePanel(SelectedComponents[i]).Frame.Right
                 and TxrBasePanel(SelectedComponents[i]).Frame.Bottom;
              end;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderLeft_OnExecute(Sender :TObject);
  begin
    SetBorder([true,false,false,false],[(not TCustomAction(Sender).Checked),false,false,false])
  end;
  //============================================================================
  procedure actBorderLeft_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk and TxrPrintable(SelectedComponents[i]).Frame.Left
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk and TxrBasePanel(SelectedComponents[i]).Frame.Left;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderTop_OnExecute(Sender :TObject);
  begin
    SetBorder([false,true,false,false],[false,(not TCustomAction(Sender).Checked),false,false])
  end;
  //============================================================================
  procedure actBorderTop_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk and TxrPrintable(SelectedComponents[i]).Frame.Top
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk and TxrBasePanel(SelectedComponents[i]).Frame.Top;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderRight_OnExecute(Sender :TObject);
  begin
    SetBorder([false,false,true,false],[false,false,(not TCustomAction(Sender).Checked),false])
  end;
  //============================================================================
  procedure actBorderRight_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk and TxrPrintable(SelectedComponents[i]).Frame.Right
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk and TxrBasePanel(SelectedComponents[i]).Frame.Right;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderBottom_OnExecute(Sender :TObject);
  begin
    SetBorder([false,false,false,true],[false,false,false,(not TCustomAction(Sender).Checked)])
  end;
  //============================================================================
  procedure actBorderLeftRight_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk 
              and TxrPrintable(SelectedComponents[i]).Frame.Left
              and TxrPrintable(SelectedComponents[i]).Frame.Right
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk 
                and TxrBasePanel(SelectedComponents[i]).Frame.Left
                and TxrBasePanel(SelectedComponents[i]).Frame.Right;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderLeftRight_OnExecute(Sender :TObject);
  begin
    SetBorder([true,false,true,false],[(not TCustomAction(Sender).Checked),false,(not TCustomAction(Sender).Checked),false])
  end;
  //============================================================================
  procedure actBorderTopBottom_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk 
              and TxrPrintable(SelectedComponents[i]).Frame.Top
              and TxrPrintable(SelectedComponents[i]).Frame.Bottom
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk 
                and TxrBasePanel(SelectedComponents[i]).Frame.Top
                and TxrBasePanel(SelectedComponents[i]).Frame.Bottom;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderTopBottom_OnExecute(Sender :TObject);
  begin
    SetBorder([false,true,false,true],[false,(not TCustomAction(Sender).Checked),false,(not TCustomAction(Sender).Checked)])
  end;
  //============================================================================
  procedure actBorderLeftTop_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk 
              and TxrPrintable(SelectedComponents[i]).Frame.Top
              and TxrPrintable(SelectedComponents[i]).Frame.Left
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk 
                and TxrBasePanel(SelectedComponents[i]).Frame.Top
                and TxrBasePanel(SelectedComponents[i]).Frame.Left;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderLeftTop_OnExecute(Sender :TObject);
  begin
    SetBorder([true,true,false,false],[(not TCustomAction(Sender).Checked),(not TCustomAction(Sender).Checked),false,false])
  end;
  //============================================================================
  procedure actBorderRightBottom_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk 
              and TxrPrintable(SelectedComponents[i]).Frame.Right
              and TxrPrintable(SelectedComponents[i]).Frame.Bottom
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk 
                and TxrBasePanel(SelectedComponents[i]).Frame.Right
                and TxrBasePanel(SelectedComponents[i]).Frame.Bottom;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actBorderRightBottom_OnExecute(Sender :TObject);
  begin
    SetBorder([false,false, true,true],[false,false, (not TCustomAction(Sender).Checked),(not TCustomAction(Sender).Checked)])
  end;
  //============================================================================
  procedure actBorderBottom_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := true;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk and TxrPrintable(SelectedComponents[i]).Frame.Bottom
           else 
            if ObjectInheritsFrom(SelectedComponents[i],'TxrBasePanel') then 
              lkChk := lkChk and TxrBasePanel(SelectedComponents[i]).Frame.Bottom;
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actFormatBold_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := false;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          begin
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk or (TxrPrintable(SelectedComponents[i]).Font.Style = (TxrPrintable(SelectedComponents[i]).Font.Style + [fsBold]) );
          if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
            lkChk := lkChk or (TxrCustomBand(SelectedComponents[i]).Font.Style = (TxrCustomBand(SelectedComponents[i]).Font.Style + [fsBold]) );
          if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
            lkChk := lkChk or (TCustomXReport(SelectedComponents[i]).Font.Style = (TCustomXReport(SelectedComponents[i]).Font.Style + [fsBold]) );
          end;  
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actFormatBold_OnExecute(Sender :TObject);
  var
    i :Integer;
  begin
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      for i:=0 to SelectedComponents.Count-1 do
        begin
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          begin
          if(TCustomAction(Sender).Checked)then
            TxrPrintable(SelectedComponents[i]).Font.Style := TxrPrintable(SelectedComponents[i]).Font.Style - [fsBold]
           else 
            TxrPrintable(SelectedComponents[i]).Font.Style := TxrPrintable(SelectedComponents[i]).Font.Style + [fsBold];
          end;
        if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
          begin
          if(TCustomAction(Sender).Checked)then
            TxrCustomBand(SelectedComponents[i]).Font.Style := TxrCustomBand(SelectedComponents[i]).Font.Style - [fsBold]
           else 
            TxrCustomBand(SelectedComponents[i]).Font.Style := TxrCustomBand(SelectedComponents[i]).Font.Style + [fsBold];
          end;
        if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
          begin
          if(TCustomAction(Sender).Checked)then
            TCustomXReport(SelectedComponents[i]).Font.Style := TCustomXReport(SelectedComponents[i]).Font.Style - [fsBold]
           else 
            TCustomXReport(SelectedComponents[i]).Font.Style := TCustomXReport(SelectedComponents[i]).Font.Style + [fsBold];
          end;
        end;
  end;
  //============================================================================
  procedure actFormatItalic_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := false;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          begin
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk or (TxrPrintable(SelectedComponents[i]).Font.Style = (TxrPrintable(SelectedComponents[i]).Font.Style + [fsItalic]) );
          if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
            lkChk := lkChk or (TxrCustomBand(SelectedComponents[i]).Font.Style = (TxrCustomBand(SelectedComponents[i]).Font.Style + [fsItalic]) );
          if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
            lkChk := lkChk or (TCustomXReport(SelectedComponents[i]).Font.Style = (TCustomXReport(SelectedComponents[i]).Font.Style + [fsItalic]) );
          end;  
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actFormatItalic_OnExecute(Sender :TObject);
  var
    i :Integer;
  begin
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      for i:=0 to SelectedComponents.Count-1 do
        begin
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          begin
          if(TCustomAction(Sender).Checked)then
            TxrPrintable(SelectedComponents[i]).Font.Style := TxrPrintable(SelectedComponents[i]).Font.Style - [fsItalic]
           else 
            TxrPrintable(SelectedComponents[i]).Font.Style := TxrPrintable(SelectedComponents[i]).Font.Style + [fsItalic];
          end;
        if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
          begin
          if(TCustomAction(Sender).Checked)then
            TxrCustomBand(SelectedComponents[i]).Font.Style := TxrCustomBand(SelectedComponents[i]).Font.Style - [fsItalic]
           else 
            TxrCustomBand(SelectedComponents[i]).Font.Style := TxrCustomBand(SelectedComponents[i]).Font.Style + [fsItalic];
          end;
        if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
          begin
          if(TCustomAction(Sender).Checked)then
            TCustomXReport(SelectedComponents[i]).Font.Style := TCustomXReport(SelectedComponents[i]).Font.Style - [fsItalic]
           else 
            TCustomXReport(SelectedComponents[i]).Font.Style := TCustomXReport(SelectedComponents[i]).Font.Style + [fsItalic];
          end;
        end;
  end;
  //============================================================================
  procedure actFormatUnderline_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := false;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          begin
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk or (TxrPrintable(SelectedComponents[i]).Font.Style = (TxrPrintable(SelectedComponents[i]).Font.Style + [fsUnderLine]) );
          if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
            lkChk := lkChk or (TxrCustomBand(SelectedComponents[i]).Font.Style = (TxrCustomBand(SelectedComponents[i]).Font.Style + [fsUnderLine]) );
          if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
            lkChk := lkChk or (TCustomXReport(SelectedComponents[i]).Font.Style = (TCustomXReport(SelectedComponents[i]).Font.Style + [fsUnderLine]) );
          end;  
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actFormatUnderLine_OnExecute(Sender :TObject);
  var
    i :Integer;
  begin
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      for i:=0 to SelectedComponents.Count-1 do
        begin
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          begin
          if(TCustomAction(Sender).Checked)then
            TxrPrintable(SelectedComponents[i]).Font.Style := TxrPrintable(SelectedComponents[i]).Font.Style - [fsUnderLine]
           else 
            TxrPrintable(SelectedComponents[i]).Font.Style := TxrPrintable(SelectedComponents[i]).Font.Style + [fsUnderLine];
          end;
        if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
          begin
          if(TCustomAction(Sender).Checked)then
            TxrCustomBand(SelectedComponents[i]).Font.Style := TxrCustomBand(SelectedComponents[i]).Font.Style - [fsUnderLine]
           else 
            TxrCustomBand(SelectedComponents[i]).Font.Style := TxrCustomBand(SelectedComponents[i]).Font.Style + [fsUnderLine];
          end;
        if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
          begin
          if(TCustomAction(Sender).Checked)then
            TCustomXReport(SelectedComponents[i]).Font.Style := TCustomXReport(SelectedComponents[i]).Font.Style - [fsUnderLine]
           else 
            TCustomXReport(SelectedComponents[i]).Font.Style := TCustomXReport(SelectedComponents[i]).Font.Style + [fsUnderLine];
          end;
        end;
  end;
  //============================================================================
  procedure actFormatStrikeOut_OnUpdate(Sender :TObject);
  var
    lkEnbl :Boolean;
    lkChk  :Boolean; 
    i      :Integer;
  begin
    lkEnbl := ValidxReportComponent;
    lkChk  := false;
    if lkEnbl then
      with Amunhotep.MainForm.DesignManager.CurrentDesigner do
        for i:=0 to SelectedComponents.Count-1 do
          begin
          if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
            lkChk := lkChk or (TxrPrintable(SelectedComponents[i]).Font.Style = (TxrPrintable(SelectedComponents[i]).Font.Style + [fsStrikeOut]) );
          if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
            lkChk := lkChk or (TxrCustomBand(SelectedComponents[i]).Font.Style = (TxrCustomBand(SelectedComponents[i]).Font.Style + [fsStrikeOut]) );
          if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
            lkChk := lkChk or (TCustomXReport(SelectedComponents[i]).Font.Style = (TCustomXReport(SelectedComponents[i]).Font.Style + [fsStrikeOut]) );
          end;  
    TCustomAction(Sender).Enabled := lkEnbl;  
    TCustomAction(Sender).Checked := lkChk;  
  end;
  //============================================================================
  procedure actFormatStrikeOut_OnExecute(Sender :TObject);
  var
    i :Integer;
  begin
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      for i:=0 to SelectedComponents.Count-1 do
        begin
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          begin
          if(TCustomAction(Sender).Checked)then
            TxrPrintable(SelectedComponents[i]).Font.Style := TxrPrintable(SelectedComponents[i]).Font.Style - [fsStrikeOut]
           else 
            TxrPrintable(SelectedComponents[i]).Font.Style := TxrPrintable(SelectedComponents[i]).Font.Style + [fsStrikeOut];
          end;
        if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
          begin
          if(TCustomAction(Sender).Checked)then
            TxrCustomBand(SelectedComponents[i]).Font.Style := TxrCustomBand(SelectedComponents[i]).Font.Style - [fsStrikeOut]
           else 
            TxrCustomBand(SelectedComponents[i]).Font.Style := TxrCustomBand(SelectedComponents[i]).Font.Style + [fsStrikeOut];
          end;
        if ObjectInheritsFrom(SelectedComponents[i],'TCustomXReport') then
          begin
          if(TCustomAction(Sender).Checked)then
            TCustomXReport(SelectedComponents[i]).Font.Style := TCustomXReport(SelectedComponents[i]).Font.Style - [fsStrikeOut]
           else 
            TCustomXReport(SelectedComponents[i]).Font.Style := TCustomXReport(SelectedComponents[i]).Font.Style + [fsStrikeOut];
          end;
        end;
  end;
  //============================================================================
  procedure actFillColor_OnExecute(Sender :TObject);
  var
    i     :Integer;
    lkClr :TColor;
  begin
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      begin
      lkClr := clWhite;
      if(SelectedComponents.Count > 0)then
        begin
             if ObjectInheritsFrom(SelectedComponents[0],'TxrPrintable' ) then lkClr := TxrPrintable(SelectedComponents[0]).Color
        else if ObjectInheritsFrom(SelectedComponents[0],'TxrCustomBand') then lkClr := TxrCustomBand(SelectedComponents[0]).Color
        end;
      if not Dialogs.SelectColor(lkClr)then exit;    
      for i:=0 to SelectedComponents.Count-1 do
        begin
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          TxrPrintable(SelectedComponents[0]).Color := lkClr;
        if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
          TxrCustomBand(SelectedComponents[0]).Color := lkClr;
        end;
      end;
  end;
  //============================================================================
  procedure actFillColor_OnUpdate(Sender :TObject);
  var
    lkStdPanel :TxcStdPanel;
    lkClr      :TColor;
  begin
    lkStdPanel := TxcStdPanel(TComponent(Sender).FindComponent('STDPANEL'));
    if(lkStdPanel = nil)then exit;
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      begin
      lkClr := clWhite;
      if(SelectedComponents.Count > 0)then
        begin
             if ObjectInheritsFrom(SelectedComponents[0],'TxrPrintable' ) then lkClr := TxrPrintable(SelectedComponents[0]).Color
        else if ObjectInheritsFrom(SelectedComponents[0],'TxrCustomBand') then lkClr := TxrCustomBand(SelectedComponents[0]).Color
        end;
      end;
    lkStdPanel.Color := lkClr;  
  end;
  //============================================================================
  procedure actFontColor_OnExecute(Sender :TObject);
  var
    i     :Integer;
    lkClr :TColor;
  begin
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      begin
      lkClr := clBlack;
      if(SelectedComponents.Count > 0)then
        begin
             if ObjectInheritsFrom(SelectedComponents[0],'TxrPrintable' ) then lkClr := TxrPrintable(SelectedComponents[0]).Font.Color
        else if ObjectInheritsFrom(SelectedComponents[0],'TxrCustomBand') then lkClr := TxrCustomBand(SelectedComponents[0]).Font.Color
        end;
      if not Dialogs.SelectColor(lkClr)then exit;    
      for i:=0 to SelectedComponents.Count-1 do
        begin
        if ObjectInheritsFrom(SelectedComponents[i],'TxrPrintable') then
          TxrPrintable(SelectedComponents[0]).Font.Color := lkClr;
        if ObjectInheritsFrom(SelectedComponents[i],'TxrCustomBand') then
          TxrCustomBand(SelectedComponents[0]).Font.Color := lkClr;
        end;
      end;
  end;
  //============================================================================
  procedure actFontColor_OnUpdate(Sender :TObject);
  var
    lkStdPanel :TxcStdPanel;
    lkClr      :TColor;
  begin
    lkStdPanel := TxcStdPanel(TComponent(Sender).FindComponent('STDPANEL'));
    if(lkStdPanel = nil)then exit;
    with Amunhotep.MainForm.DesignManager.CurrentDesigner do
      begin
      lkClr := clBlack;
      if(SelectedComponents.Count > 0)then
        begin
             if ObjectInheritsFrom(SelectedComponents[0],'TxrPrintable' ) then lkClr := TxrPrintable(SelectedComponents[0]).Font.Color
        else if ObjectInheritsFrom(SelectedComponents[0],'TxrCustomBand') then lkClr := TxrCustomBand(SelectedComponents[0]).Font.Color
        end;
      end;
    lkStdPanel.Color := lkClr;  
  end;
  //============================================================================
  function DesignerReportToolBarGetLastLeft(aToolBar :TxcGradientPanel):Integer;
  var
    i :Integer;
  begin
    Result := 0;
    for i:=0 to aToolBar.ControlCount-1 do
      Result := MaxInteger(Result, aToolBar.Controls[i].Left + aToolBar.Controls[i].Width);
  end;
  //============================================================================
  function DesignerReportCreateAction(aOwner :TComponent; 
             const aName, aCaption, aHint, aShortCut:string;
             const aGroupIndex, aImageIndex :Integer; 
             const aOnExecute, aOnUpdate :TNotifyEvent;
             aToolBar :TxcGradientPanel):TCustomAction;
  var
    lkTBB :TxcToolBarButton;           
  begin
    Result := CreateTAction(aOwner,aName,aCaption,aHint,aShortCut,aGroupIndex,aImageIndex); 
    with Result do
      begin
      OnExecute := aOnExecute; 
      OnUpdate  := aOnUpdate;
      end;
    lkTBB := CreateTxcToolBarButton2(aToolBar, aToolBar,'tbb'+Result.Name, DesignerReportToolBarGetLastLeft(aToolBar), 1, aToolBar.Height - 2,24,alNone,Result);
  end;
  //============================================================================
  function DesignerReportCreateSeparator(aToolBar:TxcGradientPanel):TLabel;
  begin
    Result := TLabel.Create(aToolBar);
    with Result do
      begin
      Parent       := aToolBar;
      AutoSize     := false;
      Transparent  := false;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Background;
      Left         := DesignerReportToolBarGetLastLeft(aToolBar);
      Width        := 2;
      Top          := 1;
      Height       := aToolBar.Height - 2;
      end;
  end;
  //============================================================================
  procedure DesignerReport_OnChangeSelection(Sender :TObject);
  begin
    UpdateFonts;
  end;
  //============================================================================
  procedure DesignerReportInit(Sender :TAmunhotepForm);
  var
    lkToolbar       :TxcGradientPanelVista;
    lkCmbxFont      :TComboBox;
    lkCmbxFontSize  :TComboBox;
    lkAct           :TCustomAction;
    lkSep           :TLabel;
    lkClrPnl        :TxcStdPanel;
    i               :Integer;
  begin
    lkToolBar := CreateTxcGradientPanelVistaToolBar(Sender, Sender, ComponentNameToolBarReport, '', alTop,0,0,25,20,xbsRaized);
    lkCmbxFont := TComboBox.Create(Sender);
    with lkCmbxFont do
      begin
      Name       := 'ComboBoxFontNames';
      Parent     := lkToolbar;
      Left       := 2;
      Top        := 1;
      Height     := lkToolbar.Height - 2;
      Width      := 140;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Items.Text := Screen.Fonts.Text;
      Style      := csDropDownList;
      OnCloseUp  := @ComboBoxFontNames_OnCloseUp;
      end;
    lkCmbxFontSize := TComboBox.Create(Sender);
    with lkCmbxFontSize do
      begin
      Name       := 'ComboBoxFontSize';
      Parent     := lkToolbar;
      Left       := DesignerReportToolBarGetLastLeft(lkToolBar) + 1;
      Top        := 1;
      Height     := lkToolbar.Height - 2;
      Width      := 40;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      Style      := csDropDown;
      Items.Clear;
      for i:=5 to 48 do
        Items.Add(IntToStr(i));
      OnCloseUp  := @ComboBoxFontSize_OnCloseUp;
      end;
    lkAct := DesignerReportCreateAction(Sender,'actFontColor'        ,msg_act_fontcolor         ,msg_act_fontcolor        ,''      ,0,-1,@actFontColor_OnExecute        ,@actFontColor_OnUpdate        ,lkToolBar);
    lkClrPnl := TxcStdPanel.Create(lkAct);
    with lkClrPnl do
      begin
      Name        := 'STDPANEL';
      Parent      := TWinControl(lkToolBar.FindComponent('tbb'+lkAct.Name));
      Left        := ColorPanelMargin;
      Top         := ColorPanelMargin;
      Height      := TWinControl(lkToolBar.FindComponent('tbb'+lkAct.Name)).Height - (ColorPanelMargin * 2);
      Width       := TWinControl(lkToolBar.FindComponent('tbb'+lkAct.Name)).Width  - (ColorPanelMargin * 2);
      BorderStyle := xbsLowered;
      OnClick     := lkAct.OnExecute; 
      end;
    lkSep := DesignerReportCreateSeparator(lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actFormatBold'       ,msg_act_format_bold       ,msg_act_format_bold      ,'Ctrl+B',0,122,@actFormatBold_OnExecute       ,@actFormatBold_OnUpdate       ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actFormatItalic'     ,msg_act_format_italic     ,msg_act_format_italic    ,'Ctrl+I',0,124,@actFormatItalic_OnExecute     ,@actFormatItalic_OnUpdate     ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actFormatUnderLine'  ,msg_act_format_underline  ,msg_act_format_underline ,'Ctrl+U',0,130,@actFormatUnderline_OnExecute  ,@actFormatUnderLine_OnUpdate  ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actFormatStrikeOut'  ,msg_act_format_strikeout  ,msg_act_format_strikeout ,''      ,0,229,@actFormatStrikeOut_OnExecute  ,@actFormatStrikeOut_OnUpdate  ,lkToolBar);
    lkSep := DesignerReportCreateSeparator(lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actFillColor'        ,msg_act_fillcolor         ,msg_act_fillcolor        ,''      ,0,-1,@actFillColor_OnExecute        ,@actFillColor_OnUpdate        ,lkToolBar);
    lkClrPnl := TxcStdPanel.Create(lkAct);
    with lkClrPnl do
      begin
      Name        := 'STDPANEL';
      Parent      := TWinControl(lkToolBar.FindComponent('tbb'+lkAct.Name));
      Left        := ColorPanelMargin;
      Top         := ColorPanelMargin;
      Height      := TWinControl(lkToolBar.FindComponent('tbb'+lkAct.Name)).Height - (ColorPanelMargin * 2);
      Width       := TWinControl(lkToolBar.FindComponent('tbb'+lkAct.Name)).Width  - (ColorPanelMargin * 2);
      BorderStyle := xbsLowered;
      OnClick     := lkAct.OnExecute; 
      end;
    lkSep := DesignerReportCreateSeparator(lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderNone'       ,msg_act_border_none       ,msg_act_border_none       ,'Alt+N',0,115,@actBorderNone_OnExecute       ,@actBorderNone_OnUpdate       ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderLeft'       ,msg_act_border_left       ,msg_act_border_left       ,'Alt+L',0,114,@actBorderLeft_OnExecute       ,@actBorderLeft_OnUpdate       ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderTop'        ,msg_act_border_top        ,msg_act_border_top        ,'Alt+T',0,117,@actBorderTop_OnExecute        ,@actBorderTop_OnUpdate        ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderRight'      ,msg_act_border_right      ,msg_act_border_right      ,'Alt+R',0,116,@actBorderRight_OnExecute      ,@actBorderRight_OnUpdate      ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderBottom'     ,msg_act_border_bottom     ,msg_act_border_bottom     ,'Alt+B',0,113,@actBorderBottom_OnExecute     ,@actBorderBottom_OnUpdate     ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderRightBottom',msg_act_border_rightbottom,msg_act_border_rightbottom,''     ,0,264,@actBorderRightBottom_OnExecute,@actBorderRightBottom_OnUpdate,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderLeftTop'    ,msg_act_border_lefttop    ,msg_act_border_lefttop    ,''     ,0,265,@actBorderLeftTop_OnExecute    ,@actBorderLeftTop_OnUpdate    ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderLeftRight'  ,msg_act_border_leftright  ,msg_act_border_leftright  ,''     ,0,267,@actBorderLeftRight_OnExecute  ,@actBorderLeftRight_OnUpdate  ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderTopBottom'  ,msg_act_border_topbottom  ,msg_act_border_topbottom  ,''     ,0,268,@actBorderTopBottom_OnExecute  ,@actBorderTopBottom_OnUpdate  ,lkToolBar);
    lkAct := DesignerReportCreateAction(Sender,'actBorderAll'        ,msg_act_border_all        ,msg_act_border_all        ,'Alt+A',0,112,@actBorderAll_OnExecute        ,@actBorderAll_OnUpdate        ,lkToolBar);
    lkSep := DesignerReportCreateSeparator(lkToolBar);

    Sender.Designer.OnChangeSelection := @DesignerReport_OnChangeSelection;
    UpdateFonts;
  end;
