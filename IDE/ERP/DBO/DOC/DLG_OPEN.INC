{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/DLG_OPEN.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                        {$I PEAKTOP:OBJ/TLABEL.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TEDIT.INC}                         {$I PEAKTOP:OBJ/TEDIT.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOMBOBOX.INC}                     {$I PEAKTOP:OBJ/TCOMBOBOX.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}              {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                  {$I PEAKTOP:OBJ/TXFBDATASETS.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}       {$I ../$COMMON/FORMERP.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/DLG_OPEN_LANG.INC}     {$I ./DLG_OPEN_LANG.INC}              {$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/DOC/DLG_OPEN.INC ====================
  procedure TERPDialogDocOpen_edtDocNumber_OnKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  begin
    if(Key = $0D {VK_RETURN})then
      TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  procedure TERPDialogDocOpen_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caHide;
  end;
  //============================================================================
  function TERPDialogDocOpen_Execute(const aChangeTypeEnabled:Boolean; var aTypeId, aDocId:string):Boolean;
  var
    lkSL        :TStringList;
    lkForm      :TForm;
    lkPnl       :TxcGradientPanel;
    lkLBL       :TLabel;
    lkListBox   :TListBox;
    lkEdtDocNum :TEdit;
    lkTr        :TxFBTransaction;
    lkQr        :TxFBQuery;
    lkDS        :TDataSource;
  label
    terpdialogdocopen_loop;  
  begin
    Result := false;
    lkForm := TERPForm_Create(msg_terpdialogdocopen_caption,ERP_ObjectIcon(ERP_OBJECTTYPE_DOC),ERP_ObjectBitmap(ERP_OBJECTTYPE_DOC),true,@TERPDialogDocOpen_OnClose);
    with lkForm do
      begin
      Height := 480;
      Width  := 520;
      end;
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_DOC);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_DOC);
      end;  
    lkPnl := CreateTxcGradientPanel(lkForm, lkForm, '', '', alClient, 0, 0, 8, 8, xbsNone, gdRightToLeft);
    with lkPnl do
      begin
      Font.Style:= [fsBold];
      end;
    lkLbl := CreateTLabel(lkForm,lkPnl,msg_terpdialogdocopen_lbldoctype,4,  4,20,lkForm.ClientWidth-8,alNone,taLeftJustify);
    lkListBox := TListBox.Create(lkForm);
    with lkListBox do
      begin
      Parent := lkPnl;
      Left   := 4;
      Top    := lkLbl.Top + lkLbl.Height + 4;
      Height := 320;
      Width  := lkForm.ClientWidth - 8;
      Ctl3D  := false;
      Font.Name := 'Courier New';
      Font.Size := 8;
      Font.Style:= [];
      Items.Clear;
      end;
    lkLbl := CreateTLabel(lkForm,lkPnl,msg_terpdialogdocopen_lbldocnum ,4,lkListBox.Top + lkListBox.Height+4,20,lkForm.ClientWidth-8,alNone,taLeftJustify);
    lkEdtDocNum:= CreateTEdit(lkForm,lkPnl,'',4,lkLbl.Top+lkLbl.Height+4,20,lkForm.ClientWidth-8);
    with lkEdtDocNum do
      begin
      OnKeyDown := @TERPDialogDocOpen_edtDocNumber_OnKeyDown;
      Font.Name := 'Courier New';
      Font.Size := 9;
      Font.Style:= [fsBold];
      end;
    CreateTxFBTransQuery(lkForm,'trDlg','qrDlg','DSqrDlg',['isc_tpb_read_committed','isc_tpb_read','isc_tpb_rec_version','isc_tpb_nowait'], lkTr, lkQr, lkDS);
    lkQr.SQL.Text := 
      'WITH RECURSIVE TTT AS( '+SQLCRLF+
      '  SELECT T1.ID, T1.PARENT_ID, T1.NAME2 AS NAME, CAST(''  '' AS DOMN$PSTRING) AS INDENT '+SQLCRLF+
      '  FROM   TABL$_TB_TYPES T1 WHERE  (T1.ID = 4) '+SQLCRLF+
      '  UNION ALL '+SQLCRLF+
      '  SELECT T2.ID, T2.PARENT_ID, T3.INDENT||T2.NAME2 AS NAME, (CAST(''  '' AS DOMN$PSTRING) || T3.INDENT) AS INDENT '+SQLCRLF+
      '  FROM   (SELECT TM.ID, TM.PARENT_ID, TM.NAME2 FROM TABL$_TB_TYPES TM ORDER BY TM.NAME2) T2, TTT T3 WHERE (T2.PARENT_ID = T3.ID) '+SQLCRLF+
      ')SELECT T.ID, T.NAME FROM TTT T';    
    lkSL := TStringList.Create;
    lkSL.Clear;
    lkListBox.Items.Clear;
    lkQr.Open;
    lkQr.First;
    while(not lkQr.EOF)do
      begin
      lkListBox.Items.Add(lkQr.FieldByName('NAME').AsString);
      lkSL.Add(lkQr.FieldByName('ID').AsString);
      lkQr.Next;
      end;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;    
    with lkListBox do
      begin
      ItemIndex := lkSL.IndexOf(aTypeId);
      Enabled   := aChangeTypeEnabled;
      if(ItemIndex > -1)then
        lkForm.ActiveControl := lkEdtDocNum;
      if not Enabled then
        TERPForm_SetCaption(lkForm, msg_terpdialogdocopen_open+Trim(lkListBox.Items[lkListBox.ItemIndex]));
      end;
  terpdialogdocopen_loop:
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      aTypeId := lkSL[lkListBox.ItemIndex];
      aDocId := '0';
      GetField(FBDataBase, 'TABL$J_4', 'COALESCE(MAX(ID), 0)', '(TYPE_ID = '+aTypeId+') AND (TRIM(DOCNUMBERSTR) = '''+StrTrimAll(lkEdtDocNum.Text)+''')', aDocId);
      if(StrCiphersOnlyInt(aDocId) = '0') or (StrTrimAll(aDocId) = '')then
        begin
        Dialogs.MessageDlg('ƒокумент "'+Trim(lkListBox.Items[lkListBox.ItemIndex])+'" с номером "'+StrTrimAll(lkEdtDocNum.Text)+'" не существует в базе данных !', mtWarning, [mbOk]);
        Result := false;
        goto terpdialogdocopen_loop;
        end;
      end;
    lkForm.Free;
    lkSL.Free;  
  end;
