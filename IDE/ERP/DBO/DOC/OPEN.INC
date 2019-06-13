{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/OPEN.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                        {$I PEAKTOP:OBJ/TLABEL.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TEDIT.INC}                         {$I PEAKTOP:OBJ/TEDIT.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}              {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}       {$I ../$COMMON/FORMERP.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/DLG_OPEN_LANG.INC}     {$I ./DLG_OPEN_LANG.INC}              {$ENDIF}
  //=================== PEAKTOP:IDE/ERP/DBO/DOC/OPEN.INC =======================
  var erp_temporary_document_id :string;
  //============================================================================
  procedure ERP_DialogDocOpen_edtDocNumber_OnKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  begin
    if(Key = $0D {VK_RETURN})then
      TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  procedure ERP_DialogDocOpen_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caHide;
  end;
  //============================================================================
  function ERP_DialogDocOpenEx_Execute(const aTypeId :string; var aJ_ID, aDocNumberStr:string):Boolean;
  var
    lkForm      :TForm;
    lkPnl       :TxcGradientPanel;
    lkLBL       :TLabel;
    lkEdtDocNum :TEdit;
    lkTypeName  :string;
  label
    terpdialogdocopen_loop;  
  begin
    lkTypeName := '';
    aDocNumberStr := '';
    GetField(FBDataBase,'TABL$_TB_TYPES','NAME2','ID='+aTypeId,lkTypeName);
    Result := false;
    lkForm := TERPForm_Create(lkTypeName,ERP_ObjectIcon(ERP_OBJECTTYPE_DOC),ERP_ObjectBitmap(ERP_OBJECTTYPE_DOC),true,@ERP_DialogDocOpen_OnClose);
    with lkForm do
      begin
      Height := 132;
      Width  := 600;
      Caption := msg_terpdialogdocopen_open+' '+Caption;
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
      Font.Style := [fsBold];
      Font.Size  := 10;
      end;
    lkLbl := CreateTLabel(lkForm,lkPnl,msg_terpdialogdocopen_lbldocnum ,4, 8,20,lkForm.ClientWidth-8,alNone,taLeftJustify);
    lkEdtDocNum:= CreateTEdit(lkForm,lkPnl,'',4,lkLbl.Top+lkLbl.Height+4,20,lkForm.ClientWidth-8);
    with lkEdtDocNum do
      begin
      OnKeyDown := @ERP_DialogDocOpen_edtDocNumber_OnKeyDown;
      Font.Name := 'Courier New';
      Font.Size := 10;
      Font.Style:= [fsBold];
      end;
    lkForm.ActiveControl := lkEdtDocNum;
  terpdialogdocopen_loop:
    aDocNumberStr := '';
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      aDocNumberStr := StrTrimAll(lkEdtDocNum.Text);
      aJ_ID := '0';
      GetField(FBDataBase, 'TABL$J_4', 'COALESCE(MAX(ID), 0)', '(TYPE_ID = '+aTypeId+') AND (TRIM(DOCNUMBERSTR) = '''+aDocNumberStr+''')', aJ_ID);
      if(StrCiphersOnlyInt(aJ_ID) = '0') or (StrTrimAll(aJ_ID) = '')then
        begin
        Dialogs.MessageDlg('ƒокумент "'+lkTypeName+'" с номером "'+aDocNumberStr+'" не существует в базе данных !', mtWarning, [mbOk]);
        Result := false;
        goto terpdialogdocopen_loop;
        end;
      end;
    lkForm.Free;
  end;
  //============================================================================
  function ERP_DialogDocOpen_Execute(const aTypeId :string; var aJ_ID:string):Boolean;
  var
    lkDocNumberStr :string;
  begin
    Result := ERP_DialogDocOpenEx_Execute(aTypeId, aJ_ID, lkDocNumberStr);
  end;
  //============================================================================
  procedure ERP_OpenDocument(const aTypeId, aJ_ID:string);
  begin
    SetGlobalVariable('J_ID', aJ_ID);
    call('DB:CONFIG/DOC/'+aTypeId+'/EDIT.PS');
  end;
