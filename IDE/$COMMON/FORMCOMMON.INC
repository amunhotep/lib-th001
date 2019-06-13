{$DEFINE PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                   {$I PEAKTOP:GLOBAL_VARIABLES.INC}              {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}           {$I PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                         {$I PEAKTOP:OBJ/TLABEL.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}          {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/FORM/LOADSAVEPOSITION.INC}     {$I PEAKTOP:SYSUTILS/FORM/LOADSAVEPOSITION.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}              {$I ../ERP/DBO/SHORTCUTS.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FILENAMES.INC}              {$I ./FILENAMES.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON_OBJNAMES.INC}    {$I ./FORMCOMMON_OBJNAMES.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON_HEADER.INC}      {$I ./FORMCOMMON_HEADER.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON_ACTIONS.INC}     {$I ./FORMCOMMON_ACTIONS.INC}                  {$ENDIF}
  //====================== PEAKTOP:IDE/$COMMON/FORMCOMMON.INC ==================
  function TCommonForm_Create(const aCaption, aTopBarCaption, aFileNameIcon, aFileNameBitmap :string; const aModalForm:Boolean; aOnClose :TCloseEvent):TForm;
  var
    lkAct    :TCustomAction;
    lkTopBar :TxcGradientPanelVista;
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
        BorderIcons := [biSystemMenu, biMaximize];
        Position    := poDesktopCenter;
        end; 
      end;
    if(StrTrimAll(aFileNameIcon) <> '')then  
      if FileExists(PrepareAbsoleteFileName(aFileNameIcon))then
        Result.Icon.LoadFromFile(PrepareAbsoleteFileName(aFileNameIcon));
    lkTopBar := CreateTxcGradientPanelVista(Result,Result,obj_name_common_topbar,#$20#$20#$20#$20#$20#$20+aTopBarCaption,alTop, 0,0,34,34,xbsRaized);
    lkTopBar.ShowHint := true;
    if(StrTrimAll(aFileNameBitmap) <> '')then
      with CreateTxcToolBarButton(lkTopBar,lkTopBar,'tbb'+obj_name_common_imglogo,'','',0,0,0,lkTopBar.Height+8, alLeft,-1,nil) do
        begin
        ShowHint    := true;
        ShowCaption := false;
        if FileExists(PrepareAbsoleteFileName(aFileNameBitmap))then  
          Glyph.LoadFromFile(PrepareAbsoleteFileName(aFileNameBitmap));
        end;
    lkAct := TCommonForm_CreateActionTopBar(Result,obj_name_common_actclose,'Отменить и закрыть окно',SHORTCUT_CLOSE,COMMON_FILENAME_BMP_ACTCLOSE, @TCommonForm_actClose_OnExecute, nil, lkTopBar);    
    if aModalForm then
      begin
      lkAct.SecondaryShortCuts.Add('Esc');   
      lkAct := TCommonForm_CreateActionTopBar(Result,obj_name_common_actok,'Сохранить и закрыть окно',SHORTCUT_OK,COMMON_FILENAME_BMP_ACTAPPLY, @TCommonForm_actOk_OnExecute, nil, lkTopBar);
      end    
     else
      begin  
      if FileExists(StrAbsolutePath('../conf/amunhotep-peaktop.conf',Amunhotep.ExeName)) then
        begin
        lkAct := TCommonForm_CreateActionTopBar(Result,obj_name_common_actsourcecode,'Исходный код модуля','',COMMON_FILENAME_BMP_ACTSOURCECODE,@TCommonForm_actSourceCode_OnExecute,nil,lkTopBar);
        end;    
      end;
  end;
