{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/FORMOPER.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}    {$I ../$COMMON/FORMERP.INC}       {$ENDIF}
  //===================== PEAKTOP:IDE/ERP/DBO/OPER/FORMOPER.INC ================
  //============================================================================
  procedure TERPFormOper_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end;
  //============================================================================
  function TERPFormOper_Create(const aCaption, aMenuItemCaption:string; const aModalForm:Boolean; const aCreateParams:TFormERPParams):TForm;
  var
    lkMainMenu   :TMainMenu;
    lkMIMenuMain :TMenuItem;
    lkAct        :TCustomAction;
  begin
    Result := TERPForm_Create(aCaption, ERP_ObjectIcon(ERP_OBJECTTYPE_OPER), ERP_ObjectBitmap(ERP_OBJECTTYPE_OPER), aModalForm, @TERPFormOper_OnClose);
    if( not aModalForm and (GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT) = 'PEAKTOP'))then
      begin
      lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actconfig    ,'Настройка объекта','',ERP_FILENAME_BMP_CONFIGURATOR,@TERPForm_actConfig_OnExecute    ,nil,TxcGradientPanel(Result.FindComponent(obj_name_erp_topbar)));
      lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actconfigmenu,'Настройка меню'   ,'',ERP_FILENAME_BMP_MENU        ,@TERPForm_actConfigMenu_OnExecute,nil,TxcGradientPanel(Result.FindComponent(obj_name_erp_topbar)));
      end;
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    if(aMenuItemCaption <> '')then
      begin
      lkMainMenu    := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
      lkMIMenuMain  := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainmenu,aMenuItemCaption  ,'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN);
      Amunhotep.MainForm.xcMenu.AddMenu(lkMainMenu); lkMainMenu.OwnerDraw := true;
      Result.Menu := lkMainMenu;
      end;
  end;
