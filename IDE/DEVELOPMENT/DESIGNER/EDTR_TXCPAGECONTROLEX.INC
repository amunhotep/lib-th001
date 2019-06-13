{$DEFINE PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_TXCPAGECONTROLEX.INC}
  //============================================================================
  procedure actPageControlExAddPage_OnExecute(Sender :TObject);
  var
    lkTS :TxcTabSheet;
    lkPC :TxcPageControlEx;
  begin
    lkPC := TxcPageControlEx(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0]);
    lkTS := TxcTabSheet.Create(Amunhotep.MainForm.DesignManager.CurrentDesigner.DesignControl);
    with lkTS do
      begin
      Name       := Amunhotep.MainForm.DesignManager.CurrentDesigner.GetUniqueName(lkTS.ClassName);
      Parent     := lkPC;
      PageControl:= lkPC;
      end;
  end;
  //============================================================================
  procedure actPageControlExAddPage_OnUpdate(Sender :TObject);
  var
    lkVisible :Boolean;
  begin
    lkVisible := (Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.Count = 1);
    if(lkVisible)then 
      lkVisible := (AnsiUpperCase(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0].ClassName) = 'TXCPAGECONTROLEX');
    TCustomAction(Sender).Visible := lkVisible;
  end;
  //============================================================================
const
  msg_act_pagecontrolexaddpage_caption = 'Добавить TxcTabSheet';  
