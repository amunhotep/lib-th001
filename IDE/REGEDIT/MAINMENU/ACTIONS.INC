{$DEFINE PEAKTOP:IDE/REGEDIT/MAINMENU/ACTIONS.INC}
  //=================== PEAKTOP:IDE/FIREBIRD/MAINMENU/ACTIONS.INC ==============
  procedure actWndList_OnExecute(Sender :TObject);
  begin
  
  end;
  //============================================================================
  procedure actWndList_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := (Amunhotep.MainForm.MDIChildCount > 0);
  end;
  //============================================================================
  procedure actWndCascade_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.Cascade;
  end;
  //============================================================================
  procedure actWndTileHor_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.TileMode := tbHorizontal;
    Amunhotep.MainForm.Tile;
  end;
  //============================================================================
  procedure actWndTileVer_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.TileMode := tbVertical;
    Amunhotep.MainForm.Tile;
  end;
  //============================================================================
  procedure actWndNext_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.Next;
  end;
  //============================================================================
  procedure actWndPrev_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.Previous;
  end;
  //============================================================================
  procedure actWndClose_OnExecute(Sender :TObject);
  begin
    if(Amunhotep.MainForm.MDIChildCount > 0)then
      Amunhotep.MainForm.MDIChildren[0].Close;
  end;
  //============================================================================
  procedure actWndCloseAll_OnExecute(Sender :TObject);
  begin
    if(not(Amunhotep.MainForm.MDIChildCount > 0))then exit;
    while(Amunhotep.MainForm.MDIChildCount > 0)do
      Amunhotep.MainForm.MDIChildren[0].Free;
  end;
  //============================================================================
  procedure actWndTaskBar_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.TaskBar.Visible := not Amunhotep.MainForm.TaskBar.Visible;
  end;
  //============================================================================
  procedure actWndTaskBar_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Checked := Amunhotep.MainForm.TaskBar.Visible;
  end;
  //============================================================================
  procedure actHelpAbout_OnExecute(Sender :TObject);
  begin
    call('PEAKTOP:APPL/ABOUT.PS');
  end;  
