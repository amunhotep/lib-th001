{$DEFINE PEAKTOP:IDE/MAINMENU_HEADER.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}           {$I PEAKTOP:OBJ/TACTION.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}         {$I PEAKTOP:OBJ/TMENUITEM.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/MAINMENU_OBJNAMES.INC} {$I ./MAINMENU_OBJNAMES.INC}   {$ENDIF}
const //====================== PEAKTOP:IDE/MAINMENU_HEADER.INC =================
  AMUNHOTEP_MAINMENU_INDEX_START =  10;
  AMUNHOTEP_MAINMENU_INDEX_STOP  = 127;
  AMUNHOTEP_MAINMENU_INDEX_WND   = 122;
  AMUNHOTEP_MAINMENU_INDEX_HELP  = 125;
  //============================================================================
  function CreateComplexAction(aOwner :TComponent; const aName, aCaption, aHint, aShortCut:string;
             const aGroupIndex, aImageIndex :Integer; aOnExecute, aOnUpdate:TNotifyEvent; aParentMenuItem :TMenuItem):TCustomAction;
  var
    lkMI :TMenuItem;           
  begin
    if(aOwner.FindComponent(aName) <> nil)then
      Result := TAction(aOwner.FindComponent(aName))
     else 
      Result := CreateTAction(aOwner, aName, aCaption, aHint, aShortCut, aGroupIndex, aImageIndex);
    with Result do
      begin
      OnExecute := aOnExecute;
      OnUpdate  := aOnUpdate;
      end;
    if(aParentMenuItem <> nil)then
      lkMI := CreateTMenuItem2(aParentMenuItem, Result);
    if(aName = obj_name_actwndlist)then
      begin
      Amunhotep.MainForm.TaskBar.WindowsMenuItem   := lkMI;
      Amunhotep.MainForm.TaskBar.WindowsImageIndex := 256;
      end;  
  end;
