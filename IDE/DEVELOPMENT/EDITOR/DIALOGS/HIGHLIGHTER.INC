{$DEFINE PEAKTOP:IDE/DEVELOPMENT/EDITOR/DIALOGS/HIGHLIGHTER.INC}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}      {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}           {$I PEAKTOP:OBJ/TXCTABSHEET.INC}           {$ENDIF}
var
  PCMain :TxcPageControlEx;
    //======== PEAKTOP:IDE/DEVELOPMENT/EDITOR/DIALOGS/HIGHLIGHTER.INC ==========
    procedure LoadOptions(const HighIndx, AttrIndx:Integer);
    var
      SynEdit :TSynEdit;
    begin
      SynEdit  := TSynEdit(PCMain.Pages[HighIndx].FindComponent('SynEdit'));
      TxcStdPanel(PCMain.Pages[HighIndx].FindComponent('pnlForeground')).Color := 
        SynEdit.Highlighter.Attribute[AttrIndx].Foreground;
      TxcStdPanel(PCMain.Pages[HighIndx].FindComponent('pnlBackground')).Color := 
        SynEdit.Highlighter.Attribute[AttrIndx].Background;
      TxcCheckBox(PCMain.Pages[HighIndx].FindComponent('cbxBold')).Checked := 
        fsBold in SynEdit.Highlighter.Attribute[AttrIndx].Style;
      TxcCheckBox(PCMain.Pages[HighIndx].FindComponent('cbxItalic')).Checked := 
        fsItalic in SynEdit.Highlighter.Attribute[AttrIndx].Style;
      TxcCheckBox(PCMain.Pages[HighIndx].FindComponent('cbxUnderline')).Checked := 
        fsUnderline in SynEdit.Highlighter.Attribute[AttrIndx].Style;
      TxcCheckBox(PCMain.Pages[HighIndx].FindComponent('cbxStrikeOut')).Checked := 
        fsStrikeOut in SynEdit.Highlighter.Attribute[AttrIndx].Style;
    end;
    //==========================================================================
    procedure SetFontOtions(const HighIndx:Integer; const FontStyles:TFontStyles; const DoInclude:Boolean);
    var
      AttrIndx :Integer;
      SynEdit :TSynEdit;
    begin
      AttrIndx := TListBox(PCMain.Pages[HighIndx].FindComponent('lbx')).ItemIndex;
      SynEdit  := TSynEdit(PCMain.Pages[HighIndx].FindComponent('SynEdit'));
      if DoInclude then
        SynEdit.Highlighter.Attribute[AttrIndx].Style := SynEdit.Highlighter.Attribute[AttrIndx].Style + FontStyles
       else 
        SynEdit.Highlighter.Attribute[AttrIndx].Style := SynEdit.Highlighter.Attribute[AttrIndx].Style - FontStyles;
    end;
    //==========================================================================
    procedure cbxBold_OnClick(Sender :TObject);
    begin
      SetFontOtions(TComponent(Sender).Tag, [fsBold], TxcCheckBox(Sender).Checked);
    end;
    //==========================================================================
    procedure cbxItalic_OnClick(Sender :TObject);
    begin
      SetFontOtions(TComponent(Sender).Tag, [fsItalic], TxcCheckBox(Sender).Checked);
    end;
    //==========================================================================
    procedure cbxUnderline_OnClick(Sender :TObject);
    begin
      SetFontOtions(TComponent(Sender).Tag, [fsUnderLine], TxcCheckBox(Sender).Checked);
    end;
    //==========================================================================
    procedure cbxStrikeOut_OnClick(Sender :TObject);
    begin
      SetFontOtions(TComponent(Sender).Tag, [fsStrikeOut], TxcCheckBox(Sender).Checked);
    end;
    //==========================================================================
    procedure pnlForeground_OnClick(Sender :TObject);
    var
      lk_clr   :TColor;
      AttrIndx :Integer;
      HighIndx :Integer;
      SynEdit  :TSynEdit;
    begin
      HighIndx := TComponent(Sender).Tag;
      AttrIndx := TListBox(PCMain.Pages[HighIndx].FindComponent('lbx')).ItemIndex;
      SynEdit  := TSynEdit(PCMain.Pages[HighIndx].FindComponent('SynEdit'));
      lk_clr := TxcStdPanel(Sender).Color;
      if Dialogs.SelectColor(lk_clr) then
        begin
        TxcStdPanel(Sender).Color := lk_clr;
        SynEdit.Highlighter.Attribute[AttrIndx].Foreground := lk_clr;
        end;
    end;
    //==========================================================================
    procedure pnlBackground_OnClick(Sender :TObject);
    var
      lk_clr   :TColor;
      AttrIndx :Integer;
      HighIndx :Integer;
      SynEdit  :TSynEdit;
    begin
      HighIndx := TComponent(Sender).Tag;
      AttrIndx := TListBox(PCMain.Pages[HighIndx].FindComponent('lbx')).ItemIndex;
      SynEdit  := TSynEdit(PCMain.Pages[HighIndx].FindComponent('SynEdit'));
      lk_clr   := TxcStdPanel(Sender).Color;
      if Dialogs.SelectColor(lk_clr) then
        begin
        TxcStdPanel(Sender).Color := lk_clr;
        SynEdit.Highlighter.Attribute[AttrIndx].Background := lk_clr;
        end;
    end;
    //==========================================================================
    procedure lbx_OnClick(Sender :TObject);
    begin
      LoadOptions(TComponent(Sender).Tag, TListBox(Sender).ItemIndex);
    end;
    //==========================================================================
    function DlgHighlighter_Execute(Highlighters:array of TSynCustomHighlighter; ImageIndexes :array of Integer):Boolean;
    var
      lkForm       :TForm;
      lkTopBar     :TxcGradientPanelVista;
      i,j          :Integer;
      lkTS         :TxcTabSheet;
      Pnl          :TxcPanel;
      lbx          :TListBox;
      lkSynEdit    :TSynEdit;
      cbxBold      :TxcCheckBox;
      cbxItalic    :TxcCheckBox;
      cbxUnderline :TxcCheckBox;
      cbxStrikeOut :TxcCheckBox;
      pnlForeground:TxcStdPanel;
      pnlBackground:TxcStdPanel;
    begin
      Result := false;
      lkForm := TForm.Create(nil);
      with lkForm do
        begin
        BorderStyle := bsDialog;
        Height      := Trunc(Screen.Height / 2); 
        Width       := Trunc(Screen.Width  / 2);
        Position    := poDesktopCenter;
        Caption     := UpperCase(Amunhotep.Name)+' '+IntToStrRoman(Trunc(Amunhotep.Version/1000));
        Color       := Amunhotep.MainForm.StyleManager.Colors.Foreground;
        Font.Color  := Amunhotep.MainForm.StyleManager.Colors.Border;
        Font.Name   := 'Verdana';
        Font.Size   := 7;
        end;
      lkTopBar := CreateTxcGradientPanelVista(lkForm,lkForm,'',' Настройки подсветки синтаксиса',alTop, 0,0,34,34,xbsRaized);
      PCMain := CreateTxcPageControlEx(lkForm, lkForm, '', 0,0,200,200, alClient);
      for i:=0 to Length(Highlighters)-1 do
        begin
        lkTS := CreateTxcTabSheet(PCMain, '', Highlighters[i].LanguageName, ImageIndexes[i], Amunhotep.MainForm.StyleManager.Colors.Foreground);
        Pnl := TxcPanel.Create(lkTS);
        with Pnl do
          begin
          Parent       := lkTS;
          Height       := 136;
          StyleManager := Amunhotep_MainForm_StyleManager;
          Align        := alTop;
          end;  
        cbxBold := TxcCheckBox.Create(lkTS);
        with cbxBold do
          begin
          Parent      := Pnl;
          StyleManager:= Amunhotep.MainForm.StyleManager; 
          Caption     := 'Bold';
          Name        := 'cbxBold';
          Tag         := i;
          Font.Name   := 'Verdana';
          Font.Size   := 8;
          Font.Style  := [fsBold];
          Left        := 208;
          Top         := 4;
          Width       := 120;
          Height      := 20;
          OnClick     := @cbxBold_OnClick;
          end;
        cbxItalic             := TxcCheckBox.Create(lkTS);
        cbxItalic.Parent      := Pnl;
        cbxItalic.StyleManager:= Amunhotep.MainForm.StyleManager; 
        cbxItalic.Caption     := 'Italic';
        cbxItalic.Name        := 'cbxItalic';
        cbxItalic.Tag         := i;
        cbxItalic.Font.Name   := 'Verdana';
        cbxItalic.Font.Size   := 8;
        cbxItalic.Font.Style  := [fsItalic];
        cbxItalic.Left        := 208;
        cbxItalic.Top         := 24;
        cbxItalic.Width       := 120;
        cbxItalic.Height      := 20;
        cbxItalic.OnClick     := @cbxItalic_OnClick;
        cbxUnderline             := TxcCheckBox.Create(lkTS);
        cbxUnderline.Parent      := Pnl;
        cbxUnderline.StyleManager:= Amunhotep.MainForm.StyleManager; 
        cbxUnderline.Caption     := 'Underline';
        cbxUnderline.Name        := 'cbxUnderline';
        cbxUnderline.Tag         := i;
        cbxUnderline.Font.Name   := 'Verdana';
        cbxUnderline.Font.Size   := 8;
        cbxUnderline.Font.Style  := [fsUnderline];
        cbxUnderline.Left        := 208;
        cbxUnderline.Top         := 44;
        cbxUnderline.Width       := 120;
        cbxUnderline.Height      := 20;
        cbxUnderline.OnClick     := @cbxUnderline_OnClick;
        cbxStrikeOut             := TxcCheckBox.Create(lkTS);
        cbxStrikeOut.Parent      := Pnl;
        cbxStrikeOut.StyleManager:= Amunhotep.MainForm.StyleManager; 
        cbxStrikeOut.Caption     := 'StrikeOut';
        cbxStrikeOut.Name        := 'cbxStrikeOut';
        cbxStrikeOut.Tag         := i;
        cbxStrikeOut.Font.Name   := 'Verdana';
        cbxStrikeOut.Font.Size   := 8;
        cbxStrikeOut.Font.Style  := [fsStrikeOut];
        cbxStrikeOut.Left        := 208;
        cbxStrikeOut.Top         := 64;
        cbxStrikeOut.Width       := 120;
        cbxStrikeOut.Height      := 20;
        cbxStrikeOut.OnClick     := @cbxStrikeOut_OnClick;
        pnlForeground             := TxcStdPanel.Create(lkTS);
        pnlForeground.Parent      := Pnl;
        pnlForeground.StyleManager:= Amunhotep.MainForm.StyleManager;
        pnlForeground.Alignment   := taCenter;
        pnlForeground.BorderStyle := xbsLowered; 
        pnlForeground.Caption     := 'Foreground';
        pnlForeground.Name        := 'pnlForeground';
        pnlForeground.Tag         := i;
        pnlForeground.Font.Name   := 'Verdana';
        pnlForeground.Font.Size   := 8;
        pnlForeground.Font.Style  := [fsBold];
        pnlForeground.Left        := 208;
        pnlForeground.Top         := 84;
        pnlForeground.Width       := 120;
        pnlForeground.Height      := 24;
        pnlForeground.ShowCaption := true; 
        pnlForeground.OnClick     := @pnlForeground_OnClick;
        pnlBackground             := TxcStdPanel.Create(lkTS);
        pnlBackground.Parent      := Pnl;
        pnlBackground.StyleManager:= Amunhotep.MainForm.StyleManager;
        pnlBackground.Alignment   := taCenter;
        pnlBackground.BorderStyle := xbsLowered; 
        pnlBackground.Caption     := 'Background';
        pnlBackground.Name        := 'pnlBackground';
        pnlBackground.Tag         := i;
        pnlBackground.Font.Name   := 'Verdana';
        pnlBackground.Font.Size   := 8;
        pnlBackground.Font.Style  := [fsBold];
        pnlBackground.Left        := 208;
        pnlBackground.Top         := 110;
        pnlBackground.Width       := 120;
        pnlBackground.Height      := 24;
        pnlBackground.ShowCaption := true; 
        pnlBackground.OnClick     := @pnlBackground_OnClick;
        lbx                := TListBox.Create(lkTS);
        lbx.Tag            := i;
        lbx.Parent         := Pnl;
        lbx.Name           := 'lbx';
        lbx.Width          := 200; 
        lbx.Align          := alLeft;
        lbx.Ctl3D          := false;
        lbx.Color          := Amunhotep_MainForm_StyleManager.Colors.Window;
        lbx.Font.Color     := Amunhotep_MainForm_StyleManager.Colors.Border;
        lbx.OnClick        := @lbx_OnClick;
        lbx.Items.Clear;
        for j:=0 to Highlighters[i].AttrCount-1 do
          lbx.Items.Add(Highlighters[i].Attribute[j].Name);
        lbx.ItemIndex := 0;
        lkSynEdit            := TSynEdit.Create(lkTS);
        lkSynEdit.Name       := 'SynEdit';
        lkSynEdit.Parent     := lkTS;
        lkSynEdit.Align      := alClient;
        lkSynEdit.Font.Size  := 8;
        RegisterSynEdit(lkSynEdit, ftText);
        lkSynEdit.Highlighter:= Highlighters[i];
        lkSynEdit.Text       := Highlighters[i].SampleSource;
        LoadOptions(i, lbx.ItemIndex);
        end;
      TxcPageControlEx_ActivateDefaultPage(PCMain);  
      lkForm.ShowModal;
      lkForm.Free;
      Result := true;
    end;
