{$DEFINE PEAKTOP:IDE/$COMMON/FORMCOMMON_HEADER.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                 {$I PEAKTOP:GLOBAL_VARIABLES.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                      {$I PEAKTOP:OBJ/TACTION.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}                    {$I PEAKTOP:OBJ/TMENUITEM.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}             {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}         {$I PEAKTOP:OBJ/TWINCONTROL.AUTOSIZE.INC}{$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON_OBJNAMES.INC}  {$I ./FORMCOMMON_OBJNAMES.INC}           {$ENDIF}
  //================== PEAKTOP:IDE/$COMMON/FORMCOMMON_HEADER.INC ===============
  procedure TCommonForm_SetCaption(aOwner:TComponent; const aCaption :string);
  begin
    if ObjectInheritsFrom(aOwner,'TAmunhotepForm')then 
      TAmunhotepForm(aOwner).SetCaption(aCaption)
     else 
      if ObjectInheritsFrom(aOwner,'TCustomForm')then 
        TCustomForm(aOwner).Caption := aCaption;
    if(aOwner.FindComponent(obj_name_common_topbar) <> nil)then
      TxcGradientPanelVista(aOwner.FindComponent(obj_name_common_topbar)).Caption := #$20#$20#$20#$20#$20#$20+aCaption;
  end;
  //============================================================================
  procedure TCommonForm_SetTopBarColor(aOwner:TComponent; const aColor:TColor);
  begin
    with TxcGradientPanelVista( aOwner.FindComponent(obj_name_common_topbar) ) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := aColor or $A0A0A0;
      Colors.HotTrackBorder := aColor;
      end;  
  end;
  //============================================================================
  function TCommonForm_CreateAction(aOwner:TComponent; const aActionName, aCaption, aHint, aShortCut :string; const aGroupIndex, aImageIndex :Integer;
             aOnExecute, aOnUpdate :TNotifyEvent; aToolBar :TxcGradientPanel; aParentItem :TMenuItem):TCustomAction;
  var
    lkTBB:TxcToolBarButton;
    lkMI :TMenuItem;
  begin
    Result := CreateTAction(aOwner,aActionName,aCaption,aHint,aShortCut, aGroupIndex, aImageIndex);
    Result.OnExecute := aOnExecute; 
    Result.OnUpdate  := aOnUpdate;
    if(aToolBar <> nil)then
      begin
      lkTBB := CreateTxcToolBarButton(aToolBar, aToolBar, 'tbb'+Result.Name, '','', aToolBar.ControlCount * 24,1,24,24, alLeft, -1, Result);
      lkTBB.GroupIndex := aGroupIndex;
      end;
    if(aParentItem <> nil)then  
      begin
      lkMI := CreateTMenuItem2(aParentItem, Result);
      if(aToolBar <> nil)then
        lkTBB.ImagesSmall := lkMI.GetImageList;
      end;  
  end;
  //============================================================================
  function TCommonForm_CreateAction2(aOwner:TComponent; const aActionName, aCaption, aHint, aShortCut :string; const aGroupIndex, aImageIndex :Integer;
             aOnExecute, aOnUpdate :TNotifyEvent; aToolBar :TxcGradientPanel; const aToolButtonWidth:Integer; aParentItem :TMenuItem):TCustomAction;
  begin
    Result := TCommonForm_CreateAction(aOwner,aActionName,aCaption,aHint,aShortCut, aGroupIndex, aImageIndex, aOnExecute, aOnUpdate, aToolBar, aParentItem);  
    if(aToolBar <> nil)then
      if(aToolBar.FindComponent('tbb'+aActionName) <> nil)then
        with TxcToolBarButton(aToolBar.FindComponent('tbb'+aActionName)) do
          begin
          ShowCaption := true;
          Width       := aToolButtonWidth;
          Left        := TWinControl_AutoWidth(Parent);
          end;
  end;
  //============================================================================
  function TCommonForm_CreateActionTopBar(aOwner:TComponent; const aActionName, aHint, aShortCut, aImageFileName :string; aOnExecute, aOnUpdate :TNotifyEvent; aTopBar :TxcGradientPanel):TCustomAction;
  var
    lkTBB:TxcToolBarButton;
  begin
    Result := CreateTAction(aOwner,aActionName,'',aHint,aShortCut,0,-1);
    Result.OnExecute := aOnExecute; 
    Result.OnUpdate  := aOnUpdate; 
    if(aTopBar <> nil)then
      begin
      lkTBB := CreateTxcToolBarButton2(Result, aTopBar,'',aTopBar.Width - ((aTopBar.Height+2) + aTopBar.ControlCount),0,aTopBar.Height+2,aTopBar.Height+2, alRight, Result);
      with lkTBB do
        begin
        ShowHint    := true;
        ShowCaption := false;
        if FileExists(PrepareAbsoleteFileName(aImageFileName))then
          Glyph.LoadFromFile(PrepareAbsoleteFileName(aImageFileName));  
        end;
      end;
  end;  
