{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/WIZARD.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                       {$I PEAKTOP:OBJ/TLABEL.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                 {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/FILENAMES_TEMPLATES.INC}  {$I ../FILENAMES_TEMPLATES.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I ../$COMMON/FORMERP.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC} {$I ../$COMMON/FORMERP_LANG.INC}  {$ENDIF}
  //====================== PEAKTOP:IDE/ERP/DBO/RPTI/WIZARD.INC =================
  procedure ERP_WizardOper_edtGUID_OnButtonClick(Sender :TObject);
  var 
    lkGUID :TGUID;
    lkGUIDClear  :string;
  begin
    CoCreateGUID(lkGUID);
    TxcEditCombo(Sender).Text := GUIDToStr(lkGUID);
    lkGUIDClear := Copy(GUIDToStr(lkGUID), 2, Length(GUIDToStr(lkGUID))-2);
    TxcEditCombo(TComponent(Sender).Owner.FindComponent('edtEdtFileName')).Text := 'PEAKTOP:IDE/ERP/CONFIG/OPER/'+lkGUIDClear+'/DEFAULT.PS';
  end;
  //============================================================================
  procedure ERP_WizardOper_edtParent_OnButtonClick(Sender :TObject);
  var
    lkStr :string;
  begin
    with TxcEditCombo(Sender) do
      begin
      SetGlobalVariable('TYPE_ID', IntToStr(Tag));
      call('PEAKTOP:IDE/ERP/DBO/OPER/DIALOGCASEFOLDER.PS');
      lkStr := GetGlobalVariable('TYPE_ID');
      if(UpperCase(lkStr) = 'NULL')then exit;
      Tag := StrToInt(lkStr);
      GetField(FBDataBase, 'PROC$_TYPES', 'PATH', 'ID = '+lkStr, lkStr);
      Text := lkStr;
      end;
  end;
  //============================================================================
  procedure ERP_WizardOper_edtFileName_OnButtonClick(Sender :TObject);
  var
    lkStr :string;
  begin
    lkStr := '';
    if not PromptForFileName(lkStr, 'Pascal script (*.ps)|*.ps|All files (*.*)|*.*', '*.ps', 'Открыть файл', '', false) then exit;
    if(Pos(Amunhotep.SourcePath, lkStr) = 1)then
      begin
      Delete(lkStr, 1, Length(Amunhotep.SourcePath));
      if( (lkStr[1] = '\') or (lkStr[1] = '/'))then
        Delete(lkStr, 1, 1);
      lkStr := 'PEAKTOP:'+lkStr;  
      end;
    TxcEditCombo(Sender).Text := lkStr;
  end;
  //============================================================================
  function ERP_WizardOper_Execute(var aGUID, aCaption, aParentTypeId, aFileNameScript:string):Boolean;
  var
    lkForm       :TForm;
    lkLbl        :TLabel;
    lkEdtParent  :TxcEditCombo;
    lkEdtGUID    :TxcEditCombo;
    lkEdtCaption :TxcEditCombo;
    lkEdtFileName:TxcEditCombo;
    lkGUIDClear  :string;
    lkStr        :string;
  begin
    lkGUIDClear := Copy(aGUID, 2, Length(aGUID)-2);
    lkForm := TERPForm_Create(msg_erp_mimainfilenew+' '+ERP_ObjectCaption(ERP_OBJECTTYPE_OPER),  ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), true, nil);
    with lkForm do
      begin
      Position    := poDesktopCenter;
      BorderStyle := bsDialog;
      Height      := 260;
      Width       := 600;
      end;
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    lkLbl        := CreateTLabel      (lkForm,lkForm,'Тип операции'          ,TERPForm_DefaultControlIndent,TERPForm_DefaultControlIndent+36                                  ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2), alNone, taLeftJustify);
    lkEdtParent  := CreateTxcEditCombo(lkForm,lkForm,'edtParent'             ,TERPForm_DefaultControlIndent,lkLbl.Top+lkLbl.Height+TERPForm_DefaultControlIndent              ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2));
    lkLbl        := CreateTLabel      (lkForm,lkForm,'Идентификатор операции',TERPForm_DefaultControlIndent,lkEdtParent.Top+lkEdtParent.Height+TERPForm_DefaultControlIndent  ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2), alNone, taLeftJustify);
    lkEdtGUID    := CreateTxcEditCombo(lkForm,lkForm,'edtGUID'               ,TERPForm_DefaultControlIndent,lkLbl.Top+lkLbl.Height+TERPForm_DefaultControlIndent              ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2));
    lkLbl        := CreateTLabel      (lkForm,lkForm,'Название операции'     ,TERPForm_DefaultControlIndent,lkEdtGUID.Top+lkEdtGUID.Height+TERPForm_DefaultControlIndent      ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2), alNone, taLeftJustify);
    lkEdtCaption := CreateTxcEditCombo(lkForm,lkForm,'edtCaption'            ,TERPForm_DefaultControlIndent,lkLbl.Top+lkLbl.Height+TERPForm_DefaultControlIndent              ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2));
    lkLbl        := CreateTLabel      (lkForm,lkForm,'Имя файла скрипта'     ,TERPForm_DefaultControlIndent,lkEdtCaption.Top+lkEdtCaption.Height+TERPForm_DefaultControlIndent,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2), alNone, taLeftJustify);
    lkEdtFileName:= CreateTxcEditCombo(lkForm,lkForm,'edtEdtFileName'        ,TERPForm_DefaultControlIndent,lkLbl.Top+lkLbl.Height+TERPForm_DefaultControlIndent              ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2));
    with lkEdtGUID do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      GlyphKind     := gkEllipsis;
      ReadOnly      := true;
      AlwaysEnable  := true;
      Font.Style    := [fsBold];
      Text          := aGUID;
      OnButtonClick := @ERP_WizardOper_edtGUID_OnButtonClick;
      end;
    lkEdtCaption.Text := aCaption;
    with lkEdtParent do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      GlyphKind     := gkEllipsis;
      ReadOnly      := true;
      AlwaysEnable  := true;
      Font.Style    := [fsBold];
      Tag           := StrToInt(aParentTypeId);
      GetField(FBDataBase, 'PROC$_TYPES', 'PATH', 'ID = '+aParentTypeId, lkStr);
      Text          := lkStr;
      OnButtonClick := @ERP_WizardOper_edtParent_OnButtonClick;
      end;
    with lkEdtFileName do
      begin
      GlyphKind     := gkEllipsis;
      AlwaysEnable  := true;
      Font.Style    := [fsBold];
      Text := 'PEAKTOP:IDE/ERP/CONFIG/OPER/'+lkGUIDClear+'/DEFAULT.PS';
      OnButtonClick := @ERP_WizardOper_edtFileName_OnButtonClick;
      end;  
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      aGUID          := lkEdtGUID.Text;
      aCaption       := lkEdtCaption.Text;
      aParentTypeId  := IntToStr(lkEdtParent.Tag);
      aFileNameScript:= lkEdtFileName.Text;
      end;
    lkForm.Free;
  end;
  //============================================================================
  function ERP_ObjCreateOper(const aGUID, aCaption, aParentTypeId:string; var aFileNameScript:string):Boolean;
  var
    lkGUIDClear   :string;
    lkScript      :string;
    lkSQL         :string;
  begin
    Result := false;
    if(StrTrimAll(aFileNameScript) = '')then
      begin
      lkGUIDClear := Copy(aGUID, 2, Length(aGUID)-2);
      if not DirectoryExists(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG/OPER/'+lkGUIDClear+'/')) then
        CreateDir(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG/OPER/'+lkGUIDClear+'/'));
      aFileNameScript:= 'PEAKTOP:IDE/ERP/CONFIG/OPER/'+lkGUIDClear+'/DEFAULT.PS';
      lkScript := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_TEMPLATE_OPER));
      lkScript := '{$DEFINE '+aFileNameScript+'}'+#13#10+lkScript;
      StringsSaveToFile(aFileNameScript, lkScript);
      end;
    lkSQL := 'UPDATE OR INSERT INTO TABL$_TB(TYPE_ID, ID, NAME, NAME2, SC_ITEM, SC_REF)VALUES('''+aParentTypeId+''','''+aGUID+''','''+
      StrReplaceStr(aCaption, '''', '''''')+''', '''+StrReplaceStr(aCaption, '''', '''''')+''', '''', '''+aFileNameScript+''')MATCHING(ID)';
    ExecSQL(FBDataBase, lkSQL);
    Result := true;
  end;
