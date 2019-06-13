{$DEFINE PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_TXCPAGECONTROL.INC}
  //============================================================================
  procedure actPageControlAddPage_OnExecute(Sender :TObject);
  var
    lk_TS :TTabSheet;
    lk_PC :TxcPageControl;
  begin
    lk_PC            := TxcPageControl(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0]);
    lk_TS            := TTabSheet.Create(Amunhotep.MainForm.DesignManager.CurrentDesigner.DesignControl);
    lk_TS.Name       := Amunhotep.MainForm.DesignManager.CurrentDesigner.GetUniqueName(lk_TS.ClassName);
    lk_TS.Parent     := lk_PC;
    lk_TS.PageControl:= lk_PC;
  end;
  //============================================================================
  procedure actPageControlAddPage_OnUpdate(Sender :TObject);
  var
    lk_Visible :Boolean;
  begin
    lk_Visible := (Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.Count = 1);
    if(lk_Visible)then 
      lk_Visible := (AnsiUpperCase(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0].ClassName) = 'TXCPAGECONTROL');
    TCustomAction(Sender).Visible := lk_Visible;
  end;
  //============================================================================
const
  msg_act_pagecontroladdpage_caption      = 'Добавить TTabSheet';  
