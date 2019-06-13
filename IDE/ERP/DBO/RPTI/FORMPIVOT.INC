{$DEFINE PEAKTOP:IDE/ERP/DBO/RPTI/FORMPIVOT.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                      {$I PEAKTOP:GLOBAL_VARIABLES.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                            {$I PEAKTOP:OBJ/TLABEL.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}             {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}                  {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                       {$I PEAKTOP:OBJ/TXCTABSHEET.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                         {$I PEAKTOP:OBJ/TSPLITTER.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSCROLLBOX.INC}                        {$I PEAKTOP:OBJ/TSCROLLBOX.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXFBDATASETS.INC}                      {$I PEAKTOP:OBJ/TXFBDATASETS.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}            {$I PEAKTOP:OBJ/INTERFACE/SYNEDIT/INTF.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/INTERFACE/TEECHART/DEFAULT.INC}        {$I PEAKTOP:OBJ/INTERFACE/TEECHART/DEFAULT.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}                 {$I ../SHORTCUTS.INC}                           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}           {$I ../$COMMON/FORMERP.INC}                     {$ENDIF}
  //===================== PEAKTOP:IDE/ERP/DBO/RPTI/FORMPIVOT.INC ===============
  procedure TERPFormPivot_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end;
  //============================================================================
  function TERPFormPivot_Create(const aCaption:string):TForm;
  var
    lkSettings :TStrings;
    lkPC       :TxcPageControlEx;
    lkTr       :TxFBTransaction;
    lkQr       :TxFBQuery;
    lkDS       :TDataSource;
    lkCube     :TfcCube;
    lkSlice    :TfcSlice;
    lkGrid     :TfcGrid;
  begin
    Result := TERPForm_Create(aCaption, 'PEAKTOP:IMG/CONFIG/ERP/PIVOT0016X0016.ICO', 'PEAKTOP:IMG/CONFIG/ERP/PIVOT0032X0032.BMP', false, @TERPFormPivot_OnClose);
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := $80FF00;
      Colors.HotTrackBorder := $808000;
      end;
    lkSettings := TERPForm_Settings(Result);
    lkPC := CreateTxcPageControlEx(Result, Result, obj_name_erp_pagecontrol, 0,36,600,600, alClient);
    CreateTxcTabSheet(lkPC,'tsData'  ,' ”¡'   ,190,Amunhotep.MainForm.StyleManager.Colors.Window    );
    CreateTxcTabSheet(lkPC,'tsCharts','√‡ÙËÍ',376,Amunhotep.MainForm.StyleManager.Colors.Highlight );
    CreateTxcTabSheet(lkPC,'tsSQL'   ,'SQL'   ,290,Amunhotep.MainForm.StyleManager.Colors.Error     );

    CreateTxFBTransQuery(Result, obj_name_erp_data_trmain, obj_name_erp_data_qrmain, 'DataSource'+obj_name_erp_data_qrmain, ['isc_tpb_read_committed', 'isc_tpb_read', 'isc_tpb_rec_version', 'isc_tpb_nowait'], lkTr, lkQr, lkDS);  
    lkCube := TfcCube.Create(Result);
    with lkCube do
      begin
      DataSet := lkQr;
      end;
    lkSlice := TfcSlice.Create(Result);
    with lkSlice do
      begin
      Cube := lkCube;
      end;
    lkGrid := TfcGrid.Create(Result);
    with lkGrid do
      begin
      Parent     := lkPC.Pages[0];
      Slice      := lkSlice;
      Left       := 0;
      Top        := 0;
      Align      := alClient;
      PaintStyle := psFlat;
      with Styles, Amunhotep.MainForm.StyleManager.Colors do
        begin
        ActiveItem.FillColor        := Highlight;
        ActiveItem.TextColor        := Border;
        AxisCells.FillColor         := Foreground;
        AxisCells.TextColor         := Border;
        AxisCellsSelected.FillColor := Background;
        AxisCellsSelected.TextColor := Border;
        CaptionArea.FillColor       := Window;
        CaptionArea.TextColor       := Border;
        DataArea.FillColor          := Window;
        DataArea.TextColor          := Border;
        DataCells.FillColor         := Window;
        DataCells.TextColor         := Border;
        DataCellsSelected.FillColor := Highlight;
        DataCellsSelected.TextColor := Border;
        DataCellsTotals.FillColor   := Error;
        DataCellsTotals.TextColor   := Border;
        HeaderArea.FillColor        := Foreground;
        HeaderArea.TextColor        := Background;
        end;
      end;
    RegisterSynEdit(Interface_SynEdit_Create(Result, lkPC.Pages[2], 'SynEdit'), ftSQL);
    if(GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT) <> 'PEAKTOP')then
      lkPC.Pages[2].PageControl := nil;
    TxcPageControlEx_ActivateDefaultPage(lkPC);
  end;
