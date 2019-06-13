{$DEFINE PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_TXCOUTLOOK.INC}
  //============================================================================
  procedure actOutlookAddHeader_OnExecute(Sender :TObject);
  var
    lk_OH :TxcOutlookHeader;
    lk_OB :TxcOutlookBar;
  begin
    lk_OB         := TxcOutlookBar(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0]);
    lk_OH         := lk_OB.AddHeader('Header');
    lk_OH.Name    := Amunhotep.MainForm.DesignManager.CurrentDesigner.GetUniqueName('THeader');
    lk_OH.Caption := lk_OH.Name;
  end;
  //============================================================================
  procedure actOutlookAddHeader_OnUpdate(Sender :TObject);
  var
    lk_Visible :Boolean;
  begin
    lk_Visible := (Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.Count = 1);
    if(lk_Visible)then 
      lk_Visible := (AnsiUpperCase(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0].ClassName) = 'TXCOUTLOOKBAR');
    TCustomAction(Sender).Visible := lk_Visible;
  end;
  //============================================================================
  procedure actOutlookAddButton_OnExecute(Sender :TObject);
  var
    lk_OH :TxcOutlookHeader;
    lk_TBB:TxcToolBarButton;
  begin
    lk_OH          := TxcOutlookHeader(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0]);
    lk_TBB         := lk_OH.AddButton('Button');
    lk_TBB.Name    := Amunhotep.MainForm.DesignManager.CurrentDesigner.GetUniqueName('TOButton');
    lk_TBB.Caption := lk_TBB.Name;
  end;
  //============================================================================
  procedure actOutlookAddButton_OnUpdate(Sender :TObject);
  var
    lk_Visible :Boolean;
  begin
    lk_Visible := (Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.Count = 1);
    if(lk_Visible)then 
      lk_Visible := (AnsiUpperCase(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0].ClassName) = 'TXCOUTLOOKHEADER');
    TCustomAction(Sender).Visible := lk_Visible;
  end;
  //============================================================================
const
  msg_act_OutlookAddHeader_caption      = 'Добавить TxcOutlookHeader';
  msg_act_OutlookAddButton_caption      = 'Добавить TxcToolBarButton';  
