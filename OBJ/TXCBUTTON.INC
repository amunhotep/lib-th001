{$DEFINE PEAKTOP:OBJ/TXCBUTTON.INC}
  //==================== PEAKTOP:OBJ/TXCBUTTON.INC =============================
  function CreateTxcButton(a_Owner :TComponent; a_Parent:TWinControl;
              const a_Name, a_Caption:string; const a_Left, a_Top, a_Height, a_Width:Integer;
              const a_ModalResult :TModalResult; const a_Default, a_Cancel :Boolean):TxcButton;
  begin
    Result := TxcButton.Create(a_Owner);
    with Result do
      begin
      if(a_Name <> '')then
        Name       := a_Name;
      Parent       := a_Parent;
      Caption      := a_Caption;
      StyleManager := Amunhotep_MainForm_StyleManager;
      Left         := a_Left;
      Top          := a_Top;
      Height       := a_Height;
      Width        := a_Width;
      ModalResult  := a_ModalResult;
      Default      := a_Default;
      Cancel       := a_Cancel;
      end;
  end;
