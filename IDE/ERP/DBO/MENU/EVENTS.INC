{$DEFINE PEAKTOP:IDE/ERP/DBO/MENU/EVENTS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                     {$I PEAKTOP:GLOBAL_VARIABLES.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/MENU/REBUILD_MAIN_ONUSER.INC} {$I ./REBUILD_MAIN_ONUSER.INC}    {$ENDIF}
const
  obj_name_erp_events_mainmenu = 'EventsAmunhotepMenuMain';
  //============================================================================
  procedure ERP_EventsMenuMain_OnEventAlert(Sender: TObject; EventName: string; EventCount: LongInt; var CancelAlerts: Boolean);
  begin
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/MENU/REBUILD_MAIN.PS'));
    CancelAlerts := false;
  end;
  //============================================================================
  function ERP_EventsMenuMain:TxFBEvents;
  var
    lkCmp :TComponent;
  begin
    Result := nil;
    lkCmp  := nil;
    lkCmp  := FBDataBase.FindComponent(obj_name_erp_events_mainmenu);
    if(lkCmp <> nil)then
      Result := TxFBEvents(lkCmp);
  end;
  //============================================================================
  procedure ERP_EventsMenuMain_Create;
  var
    lkEventsMenuMain :TxFBEvents;
  begin
    if(ERP_EventsMenuMain <> nil)then
      lkEventsMenuMain := ERP_EventsMenuMain
     else 
      lkEventsMenuMain := TxFBEvents.Create(FBDataBase);
    with lkEventsMenuMain do
      begin  
      Name         := obj_name_erp_events_mainmenu;
      Database     := FBDataBase;
      Events.Text  := RebuildMainMenuEvent;  
      OnEventAlert := @ERP_EventsMenuMain_OnEventAlert;
      if not Registered then
        RegisterEvents;
      end;
  end;
  //============================================================================
  procedure ERP_EventsMenuMain_Free;
  begin
    if(ERP_EventsMenuMain <> nil)then
      with ERP_EventsMenuMain do
        begin
        if Registered then 
          UnRegisterEvents;
        Free;  
        end; 
  end;
