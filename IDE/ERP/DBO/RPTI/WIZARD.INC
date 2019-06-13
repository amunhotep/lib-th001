{$DEFINE PEAKTOP:IDE/ERP/DBO/RPTI/WIZARD.INC}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                       {$I PEAKTOP:OBJ/TLABEL.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCEDITCOMBO.INC}                 {$I PEAKTOP:OBJ/TXCEDITCOMBO.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCCHECKBOX.INC}                  {$I PEAKTOP:OBJ/TXCCHECKBOX.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/FILENAMES_TEMPLATES.INC}  {$I ../FILENAMES_TEMPLATES.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I ../$COMMON/FORMERP.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC} {$I ../$COMMON/FORMERP_LANG.INC}  {$ENDIF}
  //====================== PEAKTOP:IDE/ERP/DBO/RPTI/WIZARD.INC =================
  procedure ERP_WizardRPTI_edtGUID_OnButtonClick(Sender :TObject);
  var 
    lkGUID :TGUID;
  begin
    CoCreateGUID(lkGUID);
    TxcEditCombo(Sender).Text := GUIDToStr(lkGUID);
  end;
  //============================================================================
  procedure ERP_WizardRPTI_edtParent_OnButtonClick(Sender :TObject);
  var
    lkStr :string;
  begin
    with TxcEditCombo(Sender) do
      begin
      SetGlobalVariable('TYPE_ID', IntToStr(Tag));
      call('PEAKTOP:IDE/ERP/DBO/RPTI/DIALOGCASEFOLDER.PS');
      lkStr := GetGlobalVariable('TYPE_ID');
      if(UpperCase(lkStr) = 'NULL')then exit;
      Tag := StrToInt(lkStr);
      GetField(FBDataBase, 'PROC$_TYPES', 'PATH', 'ID = '+lkStr, lkStr);
      Text := lkStr;
      end;
  end;
  //============================================================================
  function ERP_WizardRPTI_Execute(var aGUID, aCaption, aParentTypeId:string; var aInDataBase:Boolean):Boolean;
  var
    lkForm       :TForm;
    lkLbl        :TLabel;
    lkEdtParent  :TxcEditCombo;
    lkEdtGUID    :TxcEditCombo;
    lkEdtCaption :TxcEditCombo;
    lkCbInDB     :TxcCheckBox;
    lkStr        :string;
  begin
    lkForm := TERPForm_Create(msg_erp_mimainfilenew+' '+ERP_ObjectCaption(5),  ERP_ObjectIcon(5), ERP_ObjectBitmap(5), true, nil);
    with lkForm do
      begin
      Position    := poDesktopCenter;
      BorderStyle := bsDialog;
      Height      := 280;
      Width       := 600;
      end;
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_RPT);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_RPT);
      end;  
    lkLbl        := CreateTLabel      (lkForm,lkForm,'Тип отчета'          ,TERPForm_DefaultControlIndent,TERPForm_DefaultControlIndent+36                                ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2), alNone, taLeftJustify);
    lkEdtParent  := CreateTxcEditCombo(lkForm,lkForm,'edtParent'           ,TERPForm_DefaultControlIndent,lkLbl.Top+lkLbl.Height+TERPForm_DefaultControlIndent            ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2));
    lkLbl        := CreateTLabel      (lkForm,lkForm,'Идентификатор отчета',TERPForm_DefaultControlIndent,lkEdtParent.Top+lkEdtParent.Height+TERPForm_DefaultControlIndent,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2), alNone, taLeftJustify);
    lkEdtGUID    := CreateTxcEditCombo(lkForm,lkForm,'edtGUID'             ,TERPForm_DefaultControlIndent,lkLbl.Top+lkLbl.Height+TERPForm_DefaultControlIndent            ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2));
    lkLbl        := CreateTLabel      (lkForm,lkForm,'Название отчета'     ,TERPForm_DefaultControlIndent,lkEdtGUID.Top+lkEdtGUID.Height+TERPForm_DefaultControlIndent    ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2), alNone, taLeftJustify);
    lkEdtCaption := CreateTxcEditCombo(lkForm,lkForm,'edtCaption'          ,TERPForm_DefaultControlIndent,lkLbl.Top+lkLbl.Height+TERPForm_DefaultControlIndent            ,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2));
    lkCbInDB     := CreateTxcCheckBox (lkForm,lkForm,'cbInDataBase', 'Создать в базе данных', '',alNone,TERPForm_DefaultControlIndent,lkEdtCaption.Top+lkEdtCaption.Height+TERPForm_DefaultControlIndent,20,lkForm.ClientWidth-(TERPForm_DefaultControlIndent*2), aInDataBase);   
    with lkEdtGUID do
      begin
      Color         := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      GlyphKind     := gkEllipsis;
      ReadOnly      := true;
      AlwaysEnable  := true;
      Font.Style    := [fsBold];
      Text          := aGUID;
      OnButtonClick := @ERP_WizardRPTI_edtGUID_OnButtonClick;
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
      OnButtonClick := @ERP_WizardRPTI_edtParent_OnButtonClick;
      end;
      
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      begin
      aGUID         := lkEdtGUID.Text;
      aCaption      := lkEdtCaption.Text;
      aParentTypeId := IntToStr(lkEdtParent.Tag);
      aInDataBase   := lkCbInDB.Checked;
      end;
    lkForm.Free;
  end;
  //============================================================================
  function ERP_ObjCreate(const aGUID, aCaption, aParentTypeId:string; const aInDataBase:Boolean; var aFileNameScript:string):Boolean;
  var
    lkGUIDClear   :string;
    lkFileNameSQL :string;
    lkFileNameRes :string;
    lkFileNameName:string;
    lkFileNameFS  :string;
    lkSQL         :string;
    lkScript      :string;
  begin
    Result := false;
    lkGUIDClear := Copy(aGUID, 2, Length(aGUID)-2);
    if aInDataBase then
      begin
      aFileNameScript:= 'DB:CONFIG/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/DEFAULT.PS';
      lkFileNameSQL  := 'DB:CONFIG/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/DEFAULT.SQL';
      lkFileNameRes  := 'DB:CONFIG/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/RPT_DEFAULT.XFM';
      end
     else
      begin
      if not DirectoryExists(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/')) then
        begin
        CreateDir(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/'));
        end;
      aFileNameScript:= 'PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/DEFAULT.PS';
      lkFileNameSQL  := 'PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/DEFAULT.SQL';
      lkFileNameRes  := 'PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/RPT_DEFAULT.XFM';
      end; 
    lkScript := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_TEMPLATE_RPTI));
    lkScript := 
      '{$DEFINE '+aFileNameScript+'}'+SQLCRLF+
      lkScript+
      'begin'+SQLCRLF+
      '  TERPFormRpti_Create('''+aGUID+''');'+SQLCRLF+
      'end.';
    StringsSaveToFile(aFileNameScript, lkScript);
    lkScript := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_TEMPLATE_RPTI_RES)); StringsSaveToFile(lkFileNameRes, lkScript);
    lkScript := StringsLoadFromFile(PrepareAbsoleteFileName(ERP_FILENAME_TEMPLATE_RPTI_SQL)); StringsSaveToFile(lkFileNameSQL, lkScript);
    if not aInDataBase then
      begin
      StringsSaveToFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/NAME.TXT'), aCaption);
      StringsSaveToFile(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/DESKTOP.INI'), 
        '[.ShellClassInfo]'+#13#10+
        'InfoTip='+aCaption
      );
      FileSetAttr(ExtractFilePath(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/'+ERP_ObjectDir(ERP_OBJECTTYPE_RPT)+lkGUIDClear+'/DESKTOP.INI')), {faSysFile} 4 + {faDirectory} 16);
      end;
    lkSQL := 'UPDATE OR INSERT INTO TABL$_TB(TYPE_ID, ID, NAME, NAME2, SC_ITEM, SC_REF)VALUES('''+
       aParentTypeId+''','''+aGUID+''','''+StrReplaceStr(aCaption, '''', '''''')+''', '''+
       StrReplaceStr(aCaption, '''', '''''')+''', '''+aFileNameScript+''', '''+lkFileNameSQL+''')MATCHING(ID)';
    ExecSQL(FBDataBase, lkSQL);
    lkSQL := 
      'EXECUTE BLOCK AS '+#13#10+
      '  DECLARE VARIABLE P_ID TYPE OF COLUMN TABL$_TB_DOCSRPT.ID; '+#13#10+
      'BEGIN '+#13#10+
      '  INSERT INTO TABL$_TB_DOCSRPT(OBJ_ID,NAME,FLAG_DELETE,ORDERID,SUBTYPE,PATH,DESCR) '+#13#10+
      '    VALUES('''+aGUID+''','''+StrReplaceStr(aCaption, '''', '''''')+''',0,0,1,'''+lkFileNameRes+
      ''',''  '+StrReplaceStr(aCaption, '''', '''''')+''')RETURNING ID INTO :P_ID; '+#13#10+
      '  INSERT INTO TABL$_TB_DOCSRPTSQL(RPT_ID, NAME, PARENT, FLAG_DELETE, ORDERID, PATH) '+#13#10+
      '    VALUES(:P_ID,''qrMain'','''',0,0,'''+lkFileNameSQL+'''); '+#13#10+
      '  INSERT INTO TABL$_TB_DOCSRPTSQL(RPT_ID, NAME, PARENT, FLAG_DELETE, ORDERID, PATH) '+#13#10+
      '    VALUES(:P_ID,''qrEnt'','''',0,1,''PEAKTOP:IDE/ERP/CONFIG2/DOC/4/RPT_DEFAULT02_0.SQL''); '+#13#10+
      'END';    
    ExecSQL(FBDataBase, lkSQL);
    Result := true;
  end;
