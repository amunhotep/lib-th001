{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/DIALOGCOLUMNS.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                  {$I PEAKTOP:GLOBAL_VARIABLES.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                    {$I PEAKTOP:OBJ/TIMAGELIST.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}       {$I ../$COMMON/FORMERP.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC}  {$I ../$COMMON/FORMERP_LANG.INC}                {$ENDIF}
  //================ PEAKTOP:IDE/ERP/DBO/GRIDCOLUMNSDLG.INC ====================
const  
  ERP_OBJNAME_OPER_DLGCOLUMNS = 'DLG_COLUMNS';
  //============================================================================
  procedure ERP_DBGridEh_ColumnsDialog_OnClickCheck(Sender :TObject);
  var
    i :Integer;
  begin
    with TCheckListBox(Sender) do
      for i:=0 to Items.Count-1 do
        TColumnEh(Items.Objects[i]).Visible := Checked[i];
  end;
  //============================================================================
  procedure ERP_DBGridEh_ColumnsDialog_Execute(aDBGrid :TDBGridEh);
  var
    lkForm    :TForm;
    lkChLstBx :TCheckListBox;
    i         :Integer;
  begin
    lkForm := TERPForm_Create(msg_erp_column_selectcolumns,ERP_FILENAME_ICO_DBGRID,ERP_FILENAME_BMP_DBGRID, true, nil);
    with lkForm do
      begin
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderIcons     := [biSystemMenu];
      AlphaBlendValue := 232;
      AlphaBlend      := true;
      Position        := poDesigned;
      Font.Size       := 7;
      end;
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    TForm_Position_Load(lkForm, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLGCOLUMNS,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))), 400, 300);  
    TAction(lkForm.FindComponent(obj_name_erp_actok)).Visible := false;  
    lkChLstBx := TCheckListBox.Create(lkForm);
    with lkChLstBx do
      begin
      Parent       := lkForm;
      Color        := Amunhotep.MainForm.StyleManager.Colors.Window;
      Columns      := 2;
      Left         := 0;
      Align        := alClient;
      OnClickCheck := @ERP_DBGridEh_ColumnsDialog_OnClickCheck;
      Items.Clear;
      for i:=0 to aDBGrid.Columns.Count-1 do
        begin
        Items.Add(StrReplaceStr(aDBGrid.Columns[i].Title.Caption, '|', ' / '));
        Items.Objects[i] := aDBGrid.Columns[i];
        Checked[i]       := aDBGrid.Columns[i].Visible;
        end;
      end;
    lkForm.ShowModal;
    TForm_Position_Save(lkForm,  PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLGCOLUMNS,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))));
    lkForm.Free;
  end;
  //============================================================================
  procedure ERP_DBGridEh_ColumnSelect_CategoryButtons_OnButtonClicked(Sender: TObject; const Button: TButtonItem);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  function ERP_DBGridEh_ColumnSelect(aDBGrid :TDBGridEh; var aIndex:Integer):Boolean;
  var
    lkForm :TForm;
    lkCBTNS:TCategoryButtons;
    i      :Integer;
  begin
    Result := false;
    lkForm := TERPForm_Create(msg_erp_column_selectcolumn,ERP_FILENAME_ICO_DBGRID,ERP_FILENAME_BMP_DBGRID, true, nil);
    with lkForm do
      begin
      Color           := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BorderIcons     := [biSystemMenu];
      AlphaBlendValue := 232;
      AlphaBlend      := true;
      Position        := poDesigned;
      Font.Size       := 7;
      end;
    with TxcGradientPanelVista(lkForm.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    TForm_Position_Load(lkForm, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLGCOLUMNS,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))), 400, 300);  
    TAction(lkForm.FindComponent(obj_name_erp_actok)).Visible := false;  
    lkCBTNS := TCategoryButtons.Create(lkForm);
    with lkCBTNS do
      begin
      Name                        := 'CategoryButtons';
      Parent                      := lkForm;
      BorderStyle                 := bsNone;
      Align                       := alClient;
      BackgroundGradientColor     := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      BackgroundGradientDirection := gdLeftToRight; 
      ButtonFlow                  := cbfVertical;
      ButtonOptions               := [boGradientFill,boShowCaptions,boBoldCaptions,boUsePlusMinus,boCaptionOnlyBorder];
      Color                       := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Name                   := 'Verdana';
      Font.Color                  := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style                  := [fsBold];
      Font.Size                   := 10;
      GradientDirection           := gdTopToBottom;
      HotButtonColor              := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      RegularButtonColor          := clNone;
      SelectedButtonColor         := Amunhotep.MainForm.StyleManager.Colors.Highlight;
      ShowHint                    := true;
      Images                      := CreateTImageList(lkCBTNS, 'ilBtns', [403]);
      ButtonHeight                := Images.Height + 4;
      ButtonWidth                 := 320;
      OnButtonClicked             := @ERP_DBGridEh_ColumnSelect_CategoryButtons_OnButtonClicked;
      Categories.Clear;
      with Categories.Add do
        begin 
        Caption       := msg_erp_column_selectcolumn_upd;
        Color         := Amunhotep.MainForm.StyleManager.Colors.HotTrackBorder;
        GradientColor := Amunhotep.MainForm.StyleManager.Colors.Border;
        TextColor     := Amunhotep.MainForm.StyleManager.Colors.Window;
        for i:=0 to aDBGrid.Columns.Count-1 do
          with Items.Add do
            begin
            Caption    := StrReplaceStr(aDBGrid.Columns[i].Title.Caption, '|', ' / ');
            Hint       := aDBGrid.Columns[i].Title.Hint;
            ImageIndex := 0;
            end; 
        end;
      end;
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      aIndex := lkCBTNS.SelectedItem.Index;
    TForm_Position_Save(lkForm, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLGCOLUMNS,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))));
    lkForm.Free;
  end;  
