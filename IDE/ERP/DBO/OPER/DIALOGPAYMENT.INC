{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/DIALOGPAYMENT.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                    {$I PEAKTOP:OBJ/TLABEL.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCALC.INC}               {$I PEAKTOP:OBJ/TXCEDITCALC.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}   {$I ../$COMMON/FORMERP.INC}      {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/OPER/DIALOGPAYMENT.INC ===============
  procedure ERPDialogPayment_EdtPaySum_OnChange(Sender :TObject);
  begin
    TxcEditCalc(TComponent(Sender).Owner.FindComponent('edtRETURN')).Value := 
      TxcEditCalc(TComponent(Sender).Owner.FindComponent('edtPAYSUM')).Value -
      TxcEditCalc(TComponent(Sender).Owner.FindComponent('edtSUM')).Value;
  end;
  //============================================================================
  procedure ERPDialogPayment_EdtPaySum_OnKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  begin
    if(Key = $0D {VK_RETURN})then 
      TERPForm_actOk_OnExecute(TComponent(Sender).Owner.FindComponent(obj_name_erp_actok));
  end;
  //============================================================================
  function ERPDialogPayment_Create(const aAllowKredit:Boolean; const aSum :Extended; var aPaySum, aReturn:Extended):TForm;
  var
    lkLbl     :TLabel;
    lkEdt     :TxcEditCalc;
    lkLastTop :Integer;
  begin
    Result := TERPForm_Create('Введите сумму оплаты',  ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), true, nil);
    with Result do
      begin
      Position    := poScreenCenter;
      Width       := 424; 
      Height      := 200; 
      Tag         := ERP_OBJECTTYPE_OPER;
      end;   
    lkLastTop := 0;           
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      lkLastTop := Top + Height;
      end;  
    lkLbl := CreateTLabel(Result, Result, 'Сумма'   , 2,lkLastTop+2,32,120, alNone, taLeftJustify);
    with lkLbl do
      begin
      Font.Style := [fsBold];
      Font.Size  := 14;
      Font.Color := clBlack;
      end;
    lkEdt := CreateTxcEditCalc(Result, Result, 'edtSUM', lkLbl.Left+lkLbl.Width+2, lkLbl.Top, lkLbl.Height, 280);
    with lkEdt do
      begin
      Font.Style := [fsBold];
      Font.Size  := 16;
      Enabled    := false;
      Value      := aSum;  
      end;
    lkLbl := CreateTLabel(Result, Result, 'Получено', 2,lkLastTop+40,32,120, alNone, taLeftJustify);
    with lkLbl do
      begin
      Font.Style := [fsBold];
      Font.Size  := 14;
      Font.Color := $C04000;
      end;
    lkEdt := CreateTxcEditCalc(Result, Result, 'edtPAYSUM', lkLbl.Left+lkLbl.Width+2, lkLbl.Top, lkLbl.Height, 280);
    with lkEdt do
      begin
      Font.Style := [fsBold];
      Font.Size  := 16;
      Value      := aPaySum; 
      OnChange   := @ERPDialogPayment_EdtPaySum_OnChange; 
      OnKeyDown  := @ERPDialogPayment_EdtPaySum_OnKeyDown;
      end;
    Result.ActiveControl := lkEdt;  
    lkLbl := CreateTLabel(Result, Result, 'Сдача', 2,lkLastTop+80,32,120, alNone, taLeftJustify);
    with lkLbl do
      begin
      Font.Style := [fsBold];
      Font.Size  := 14;
      Font.Color := $0040C0;
      end;
    lkEdt := CreateTxcEditCalc(Result, Result, 'edtRETURN', lkLbl.Left+lkLbl.Width+2, lkLbl.Top, lkLbl.Height, 280);
    with lkEdt do
      begin
      Font.Style := [fsBold];
      Font.Size  := 16;
      Enabled    := false;
      Value      := aReturn;  
      end;
  end;
  //============================================================================
  function ERPDialogPayment_Execute(const aAllowKredit:Boolean; const aSum :Extended; var aPaySum, aReturn:Extended):Boolean;
  begin
    with ERPDialogPayment_Create(aAllowKredit, aSum, aPaySum, aReturn) do
      begin
      Result := (ShowModal = mrOk);
      if Result then
        begin
        aPaySum := TxcEditCalc(FindComponent('edtPAYSUM')).Value;
        aReturn := TxcEditCalc(FindComponent('edtRETURN')).Value; 
        end;
      Free;
      end;  
  end;  
