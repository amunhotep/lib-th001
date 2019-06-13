{$DEFINE PEAKTOP:IDE/$COMMON/DLG_MEMO.INC}
{$IFNDEF PEAKTOP:OBJ/TMEMO.INC}             {$I PEAKTOP:OBJ/TMEMO.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/DLG.INC}       {$I PEAKTOP:IDE/$COMMON/DLG.INC} {$ENDIF}
  //========================= PEAKTOP:IDE/$COMMON/DLG_MEMO.INC =================
  function TDlgMemo_Create(const aCaption, aPrompt, aIconFileName, aImageFileName, aValue:string):TForm;
  var
    lkToolBar :TxcGradientPanelVista;
    lkMemo    :TMemo;
  begin
    Result    := TDlg_Create(aCaption, aPrompt, aIconFileName, aImageFileName, $BFFF80, 600, 400);
    lkToolBar := CreateTxcGradientPanelVistaToolBar(Result, Result, 'ToolBar', '', alTop, 0, 80, 24, 600, xbsRaized);
    lkMemo    := CreateTMemo(Result, Result, 'Editor', 0, 100, 200, 200, alClient);
    with lkMemo do
      begin
      Font.Name := 'Courier New';
      Font.Size := 10;
      Font.Style:= [fsBold];
      ScrollBars:= ssVertical;
      Text      := aValue;
      end;
  end;
  //============================================================================
  function TDlgMemo_Execute(const aCaption, aPrompt, aIconFileName, aImageFileName:string; var aValue:string):Boolean;
  var
    lkForm :TForm;
  begin
    lkForm := TDlgMemo_Create(aCaption, aPrompt, aIconFileName, aImageFileName, aValue);
    Result := (lkForm.ShowModal = mrOK);
    if Result then
      aValue := TMemo( lkForm.FindComponent('Editor') ).Lines.Text;
    lkForm.Free;
  end;
