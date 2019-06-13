{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                   {$I PEAKTOP:GLOBAL_VARIABLES.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}           {$I PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                         {$I PEAKTOP:OBJ/TLABEL.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}          {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/FORM/LOADSAVEPOSITION.INC}     {$I PEAKTOP:SYSUTILS/FORM/LOADSAVEPOSITION.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/TARRAYSTRINGUNIQUE.INC}        {$I PEAKTOP:SYSUTILS/TARRAYSTRINGUNIQUE.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OBJECTNAMES.INC}            {$I ../OBJECTNAMES.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/IMAGELISTCONFIG.INC}        {$I ../IMAGELISTCONFIG.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}              {$I ../SHORTCUTS.INC}                             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/CONST.INC}             {$I ../MENU/CONST.INC}                            {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/GLOBALVARIABLES.INC}  {$I ../USERS/GLOBALVARIABLES.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_HEADER.INC} {$I ./FORMERP_HEADER.INC}                         {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_ACTIONS.INC}{$I ./FORMERP_ACTIONS.INC}                        {$ENDIF}
{$IFDEF MSWINDOWS}
  function TERPForm_SetParentWindow(hWndChild, hWndNewParent: Integer): Integer; external 'SetParent@user32.dll stdcall'; 
  function TERPForm_SetActiveWindow(hWnd: Integer): Integer; external 'SetActiveWindow@user32.dll stdcall'; 
  function TERPForm_SetForegroundWindow(hWnd: Integer): Integer; external 'SetForegroundWindow@user32.dll stdcall'; 
{$ENDIF}
  //================== PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC =================
  procedure TERPForm_OnShow(Sender :TObject);
  begin
    {$IFDEF MSWINDOWS}
    TERPForm_SetForegroundWindow(TForm(Sender).Handle);
    {$ENDIF}
  end;
  //============================================================================
  function TERPForm_Create(const aCaption, aFileNameIcon, aFileNameBitmap :string; const aModalForm:Boolean; aOnClose :TCloseEvent):TForm;
  var
    lkActnLst    :TActionList;
    lkAct        :TCustomAction;
    lkMainMenu   :TMainMenu;
    lkTopBar     :TxcGradientPanelVista;
    lkSettings   :TxsStringsHolder;
  begin
    DontAutoFree;
    if aModalForm then
      begin
      Result := TForm.Create(Amunhotep.MainForm);
      end
     else 
      Result := TAmunhotepForm.Create(Amunhotep.MainForm);
    with Result do
      begin
      Caption    := aCaption;
      Color      := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      Font.Name  := 'Verdana';
      Font.Size  := 7;
      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      OnClose    := aOnClose;
      if not aModalForm then
        begin
        TAmunhotepForm(Result).SetCaption(aCaption);
        end
       else
        begin
        TERPForm_SetParentWindow(Handle, Amunhotep.Handle);
        BorderIcons     := [biSystemMenu, biMaximize];
        Position        := poDesktopCenter;
        {$IFDEF TRANSPARENT}
        AlphaBlendValue := 232;
        AlphaBlend      := true;
        {$ENDIF}
        OnShow          := @TERPForm_OnShow;
        end; 
      end;
    if(StrTrimAll(aFileNameIcon) <> '')then  
      if FileExists(PrepareAbsoleteFileName(aFileNameIcon))then
        Result.Icon.LoadFromFile(PrepareAbsoleteFileName(aFileNameIcon));
    lkSettings := TxsStringsHolder.Create(Result);
    with lkSettings do
      begin 
      Name := obj_name_erp_data_settings;
      end;
    with TERPForm_Settings(Result) do
      begin
      Values[ERP_SETTINGS_BOOKMARK    ] := '0';
      Values[ERP_SETTINGS_DATAMEMORY  ] := '0';
      Values[ERP_SETTINGS_SAVERECNO   ] := '0';
      Values[ERP_SETTINGS_BUFFERVAR   ] := '';
      Values[ERP_SETTINGS_GOTOVAR     ] := '';
      Values[ERP_SETTINGS_TABLENAME   ] := '';
      Values[ERP_SETTINGS_TABLECAPTION] := '';
      Values[ERP_SETTINGS_TYPESLIST   ] := '';
      Values[ERP_SETTINGS_BASETYPE    ] := '0';
      end;
    lkActnLst  := TActionList.Create(Result);
    with lkActnLst do
      begin
      Name      := obj_name_erp_actlst;
      Images    := Amunhotep.MainForm.ImageListMain;
      end;
    lkMainMenu := TMainMenu.Create(Result);
    with lkMainMenu do
      begin
      Name      := obj_name_erp_mainmenu;
      Images    := Amunhotep.MainForm.ImageListMain;
      AutoMerge := not aModalForm;
      end;
    lkTopBar := CreateTxcGradientPanelVista(Result,Result,obj_name_erp_topbar,#$20#$20#$20#$20#$20#$20+aCaption,alTop, 0,0,34,34,xbsRaized);
    lkTopBar.ShowHint := true;
    if(StrTrimAll(aFileNameBitmap) <> '')then
      with CreateTxcToolBarButton(lkTopBar,lkTopBar,'tbb'+obj_name_erp_imglogo,'','',0,0,0,lkTopBar.Height+8, alLeft,-1,nil) do
        begin
        ShowHint    := true;
        ShowCaption := false;
        if FileExists(PrepareAbsoleteFileName(aFileNameBitmap))then  
          Glyph.LoadFromFile(PrepareAbsoleteFileName(aFileNameBitmap));
        end;
    lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actclose,'Отменить и закрыть окно',SHORTCUT_CLOSE,ERP_FILENAME_BMP_ACTCLOSE, @TERPForm_actClose_OnExecute, nil, lkTopBar);    
    if aModalForm then
      begin
      lkAct.SecondaryShortCuts.Add('Esc');   
      lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actok,'Сохранить и закрыть окно',SHORTCUT_OK,ERP_FILENAME_BMP_ACTAPPLY, @TERPForm_actOk_OnExecute, nil, lkTopBar);
      end    
     else
      begin  
      lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_acthelp,'Помощь по данному разделу',SHORTCUT_HELP,ERP_FILENAME_BMP_ACTHELP, @TERPForm_actHelp_OnExecute, nil, lkTopBar);    
      if(GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT) = 'PEAKTOP')then
        begin
        lkAct := TERPForm_CreateActionTopBar(Result,obj_name_erp_actsourcecode,'Исходный код модуля','',ERP_FILENAME_BMP_ACTSOURCECODE,@TERPForm_actSourceCode_OnExecute,nil,lkTopBar);
        end;    
      end;
  end;
