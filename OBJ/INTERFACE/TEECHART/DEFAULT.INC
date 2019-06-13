{$DEFINE PEAKTOP:OBJ/INTERFACE/TEECHART/DEFAULT.INC}
{$IFNDEF PEAKTOP:OBJ/TDBCHART.INC}          {$I PEAKTOP:OBJ/TDBCHART.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/$COMMON.INC} {$I ../$COMMON.INC}           {$ENDIF}
const  //=========== PEAKTOP:OBJ/INTERFACE/TEECHART/DEFAULT.INC ================
  msg_interface_teechart_setup = 'Настройки';
  msg_interface_teechart_print = 'Печать';
  //============================================================================
  procedure actInterfaceTeeChart_Setup_OnExecute(Sender :TObject);
  begin
    with TChartEditor.Create(nil)do
      begin
      Chart := TCustomChart(TComponent(Sender).Owner);
      RememberPosition := true;
      Execute;
      Free;
      end;
  end;
  //============================================================================
  procedure actInterfaceTeeChart_Print_OnExecute(Sender :TObject);
  begin
    with TChartPreviewer.Create(nil)do
      begin
      Chart := TCustomChart(TComponent(Sender).Owner);
      Execute;
      Free;
      end;
  end;
  //============================================================================
  function Interface_TeeChart_Create(aOwner :TComponent; aParent :TWinControl; const aName :string):TDBChart;
  var
    lkTB :TxcGradientPanelVista;
    lkAct:TCustomAction;
    i    :Integer;
  begin
    DontAutoFree;
    lkTB := CreateTxcGradientPanelVistaToolBar(aOwner, aParent, '','',alTop,0,0,24,24,xbsRaized);
    Result := CreateTDBChart(aOwner, aParent, aName, '', 0, lkTB.Top+lkTB.Height+1, 600,600, alClient);
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntf_TeeChart_Setup',msg_interface_teechart_setup,msg_interface_teechart_setup,'',0,254,@actInterfaceTeeChart_Setup_OnExecute     ,nil);
    lkAct := Interface_CreateTAction(Result,lkTB,'actIntf_TeeChart_Print',msg_interface_teechart_print,msg_interface_teechart_print,'',0,104,@actInterfaceTeeChart_Print_OnExecute     ,nil);
    with lkTB do
      for i:=0 to ControlCount-1 do
        if(ObjectInheritsFrom(Controls[i], 'TxcToolBarButton'))then
          with TxcToolBarButton(Controls[i]) do
            begin
            Width       := 80;
            ShowCaption := true;
            end;
  end;
