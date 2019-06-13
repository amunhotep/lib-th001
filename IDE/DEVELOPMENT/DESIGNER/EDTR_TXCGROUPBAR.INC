{$DEFINE PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_TXCGROUPBAR.INC}
  //============================================================================
  procedure actGroupBarAddBar_OnExecute(Sender :TObject);
  var
    lk_GP :TxcGroupPanel;
    lk_GB :TxcGroupBar;
  begin
    lk_GB         := TxcGroupBar(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0]);
    lk_GP         := lk_GB.AddGroupPanel('');
    lk_GP.Name    := Amunhotep.MainForm.DesignManager.CurrentDesigner.GetUniqueName('TGroupPanel');
    lk_GP.Caption := lk_GP.Name;
  end;
  //============================================================================
  procedure actGroupBarAddBar_OnUpdate(Sender :TObject);
  var
    lk_Visible :Boolean;
  begin
    lk_Visible := (Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.Count = 1);
    if(lk_Visible)then 
      lk_Visible := (AnsiUpperCase(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0].ClassName) = 'TXCGROUPBAR');
    TCustomAction(Sender).Visible := lk_Visible;
  end;
  //============================================================================
const
  msg_act_groupbaraddbar_caption      = 'Добавить TxcGroupPanel';  
