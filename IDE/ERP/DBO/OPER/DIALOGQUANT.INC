{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/DIALOGQUANT.INC}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                     {$I PEAKTOP:OBJ/TXCPANEL.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCSTDPANEL.INC}                  {$I PEAKTOP:OBJ/TXCSTDPANEL.INC}                        {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC}     {$I PEAKTOP:IDE/ERP/DBO/INPUT/TOUCH_EDTR.INC}           {$ENDIF}
  //=============== PEAKTOP:IDE/ERP/DBO/OPER/DIALOGQUANT.INC ===================
const ERP_OBJNAME_OPER_DLG_QUANT = 'DLG_QUANT';
  //============================================================================
  procedure ERPDialogQuant_btnOK_OnClick(Sender :TObject);
  begin
    TForm( TComponent(Sender).Owner ).ModalResult := mrOK;
  end;
  //============================================================================
  procedure ERPDialogQuant_btnCancel_OnClick(Sender :TObject);
  begin
    TForm( TComponent(Sender).Owner ).ModalResult := mrCancel;
  end;
  //============================================================================
  function ERPDialogQuant_Execute(const aCaption, aPrompt:string; const aIntegersOnly:Boolean; var aQuant:Extended):Boolean;
  var
    lkForm      :TForm;
    lkLbl       :TLabel;
    lkEdtr      :TMaskEdit;
    lkLastTop   :Integer;
    lkPnlBottom :TxcStdPanel;
  begin
    Result := False;
    lkForm := TForm.Create(nil);
    with lkForm do
      begin
      Position    := poDesktopCenter;
      BorderStyle := bsDialog;
      Caption     := aCaption;
      Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
      Width       := OBJ_NAME_TOUCHEDTR_HEIGHT*6 + 8;
      Height      := OBJ_NAME_TOUCHEDTR_HEIGHT*14;
      end; 
    lkLastTop := 0;             
    lkLbl := CreateTLabel(lkForm, lkForm, aPrompt, 0, lkLastTop+1, OBJ_NAME_TOUCHEDTR_HEIGHT*2, lkForm.Width, alTop, taLeftJustify);
    with lkLbl do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 7;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Layout        := taTop;
      lkLastTop     := Top + Height;
      end;
    lkEdtr := TTouchEditor_CreateTxcEditCalc(lkForm, lkForm, 0, lkLastTop+1, aIntegersOnly, #0, aQuant);
    lkLastTop := lkLastTop + lkEdtr.Parent.Height; 
    lkPnlBottom := CreateTxcStdPanel(lkForm, lkForm,'', '', alBottom, 0, lkLastTop, Trunc(OBJ_NAME_TOUCHEDTR_HEIGHT*1.5), OBJ_NAME_TOUCHEDTR_HEIGHT*6+2, xbsNone);
    lkLastTop := lkLastTop + lkPnlBottom.Height;
      TTouchEditor_CreateButton(lkForm, lkPnlBottom, 'btnOK', 'OK', '', '', '', alNone, taCenter, tlCenter, 
                 1, 0, lkPnlBottom.Height, Trunc(OBJ_NAME_TOUCHEDTR_HEIGHT * 3), xbsNone, $3C8E38, @ERPDialogQuant_btnOK_OnClick, true, 12);
      TTouchEditor_CreateButton(lkForm, lkPnlBottom, 'btnCancel', 'Œ“Ã≈Õ¿', '', '', '', alNone, taCenter, tlCenter, 
                 OBJ_NAME_TOUCHEDTR_HEIGHT*3 + 3, 0, lkPnlBottom.Height, Trunc(OBJ_NAME_TOUCHEDTR_HEIGHT * 3)-4, xbsNone, $5B18C2, @ERPDialogQuant_btnCancel_OnClick, true, 12);
    lkForm.Height := lkLastTop + OBJ_NAME_TOUCHEDTR_HEIGHT;    
    Result := (lkForm.ShowModal = mrOK);
    if Result then
      aQuant := StrToFloat( StrReplaceStr(lkEdtr.Text, ',', '.') );
    lkForm.Free;
  end;
  //============================================================================
  function ERPDialogQuantInt_Execute(const aCaption, aPrompt:string; var aQuant:Integer):Boolean;
  var
    lkQuant :Extended;
  begin
    lkQuant := aQuant;
    Result := ERPDialogQuant_Execute(aCaption, aPrompt, True, lkQuant);
    if Result then
      aQuant := Trunc(lkQuant); 
  end;
  //============================================================================
  function ERPDialogPwd_Execute(const aCaption, aPrompt:string; var aValue:string):Boolean;
  var
    lkForm      :TForm;
    lkLbl       :TLabel;
    lkEdtr      :TMaskEdit;
    lkPnlBottom :TxcStdPanel;
    lkLastTop   :Integer;
  begin
    Result := False;
    lkForm := TForm.Create(nil);
    with lkForm do
      begin
      Position    := poDesktopCenter;
      BorderStyle := bsDialog;
      Caption     := aCaption;
      Color       := Amunhotep.MainForm.StyleManager.Colors.Window;
      Width       := OBJ_NAME_TOUCHEDTR_HEIGHT*6 + 8;
      Height      := OBJ_NAME_TOUCHEDTR_HEIGHT*14;
      end; 
    lkLastTop := 0;             
    lkLbl := CreateTLabel(lkForm, lkForm, aPrompt, 0, lkLastTop+1, OBJ_NAME_TOUCHEDTR_HEIGHT*2, lkForm.Width, alTop, taLeftJustify);
    with lkLbl do
      begin
      Font.Style    := [fsBold];
      Font.Size     := 14;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Alignment     := taCenter;
      Layout        := taMiddle;
      lkLastTop     := Top + Height;
      end;
    lkEdtr := TTouchEditor_CreateTxcEditCalc(lkForm, lkForm, 0, lkLastTop+1, True, '*', 0);
    lkEdtr.Text := aValue;
    lkLastTop := lkLastTop + lkEdtr.Parent.Height; 
    lkPnlBottom := CreateTxcStdPanel(lkForm, lkForm,'', '', alBottom, 0, lkLastTop, Trunc(OBJ_NAME_TOUCHEDTR_HEIGHT*1.5), OBJ_NAME_TOUCHEDTR_HEIGHT*6+2, xbsNone);
    lkLastTop := lkLastTop + lkPnlBottom.Height;
      TTouchEditor_CreateButton(lkForm, lkPnlBottom, 'btnOK', 'OK', '', '', '', alNone, taCenter, tlCenter, 
                 1, 0, lkPnlBottom.Height, Trunc(OBJ_NAME_TOUCHEDTR_HEIGHT * 3), xbsNone, $3C8E38, @ERPDialogQuant_btnOK_OnClick, true, 12);
      TTouchEditor_CreateButton(lkForm, lkPnlBottom, 'btnCancel', 'Œ“Ã≈Õ¿', '', '', '', alNone, taCenter, tlCenter, 
                 OBJ_NAME_TOUCHEDTR_HEIGHT*3 + 3, 0, lkPnlBottom.Height, Trunc(OBJ_NAME_TOUCHEDTR_HEIGHT * 3)-4, xbsNone, $5B18C2, @ERPDialogQuant_btnCancel_OnClick, true, 12);
    lkForm.Height := lkLastTop + OBJ_NAME_TOUCHEDTR_HEIGHT;    
    Result := (lkForm.ShowModal = mrOK);
    if Result then
      aValue := lkEdtr.Text;
    lkForm.Free;
  end;  
