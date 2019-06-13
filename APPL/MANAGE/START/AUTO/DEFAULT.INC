{$DEFINE PEAKTOP:APPL/MANAGE/START/AUTO/DEFAULT.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}             {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                  {$I PEAKTOP:OBJ/TACTION.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                {$I PEAKTOP:OBJ/TCOLUMNEH.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:APPL/CONFIGFILENAMES.INC}         {$I ../../../CONFIGFILENAMES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/$CUSTOM.INC}          {$I ../../$CUSTOM.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/START/AUTO/CREATE.INC}{$I ./CREATE.INC}                  {$ENDIF}
const
  msg_manageinterface_startauto             = 'Автозапуск';
  msg_manageinterface_startauto_caption     = 'Автоматически выполняемы скрипты при запуске среды';
  msg_manageinterface_startauto_filefilter  = 'AMUNHOTEP PascalScript Files (*.ps)|*.ps|Все файлы (*.*)|*.*';
  msg_manageinterface_startauto_selectfile  = 'Выберите файл...';
const
  MANAGEINTERFACE_IMAGENAME_STARTAUTO       = 'PEAKTOP:IMG/CONFIG/APP_RUN0032X0032.BMP';
  MANAGEINTERFACE_STARTAUTO_NAME_TOPBAR     = 'ManageInterface_StartAuto_TopBar';  
  MANAGEINTERFACE_STARTAUTO_NAME_TOOLBAR    = 'ManageInterface_StartAuto_ToolBar';  
  MANAGEINTERFACE_STARTAUTO_NAME_DATASET    = 'ManageInterface_StartAuto_DataSet';  
  MANAGEINTERFACE_STARTAUTO_NAME_DATASOURCE = 'ManageInterface_StartAuto_DataSource';  
  MANAGEINTERFACE_STARTAUTO_NAME_DBGRID     = 'ManageInterface_StartAuto_DbGridEh';  
  //============================================================================
  procedure ManageInterface_StartAuto_DBGridEh_ColumnBtnEdit_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkS   :string;
    lkDBG :TDBGridEh;
  begin
    Handled := true;
    lkS := '';  
    if PromptForFileName(lkS,msg_manageinterface_startauto_filefilter, 'PS', msg_manageinterface_startauto_selectfile, '', false)then
      begin
      if(Pos(StrReplaceStr(UpperCase(Amunhotep.SourcePath),'/','\'), StrReplaceStr(UpperCase(lkS), '/','\')) = 1)then
        begin
        Delete(lkS, 1, Length(Amunhotep.SourcePath));
        lkS := 'PEAKTOP:'+lkS;
        end;
      lkDBG := TDBGridEh(TComponent(Sender).Owner.Owner);
      if(lkDBG <> nil)then
        begin
        if(lkDBG.DataSource.DataSet.State = dsBrowse)then
          lkDBG.DataSource.DataSet.Edit;
        lkDBG.DataSource.DataSet.FieldByName('FILEPATH').AsString := lkS;
        try
          lkDBG.DataSource.DataSet.Post;
        except
          lkDBG.DataSource.DataSet.Cancel;
        end;  
        end;
      end;
  end;
  //============================================================================
  function ManageInterface_StartAuto_Create(aOwner:TComponent; aParent:TWinControl):TxcPanel;
  var
    lkAct     :TCustomAction;                                                                                                                                 
    lkDTS     :TxdbDataSetDelimited;
    lkDS      :TDataSource;
    lkDBG     :TDBGridEh;
    lkCol     :TColumnEh;
  begin
    Result := ManageInterface_Custom_Create(aOwner, aParent, MANAGEINTERFACE_STARTAUTO_NAME_TOPBAR, MANAGEINTERFACE_STARTAUTO_NAME_TOOLBAR, 
      msg_manageinterface_startauto_caption, PrepareAbsoleteFileName(MANAGEINTERFACE_IMAGENAME_STARTAUTO) );
    lkDTS := TxdbDataSetDelimited.Create(Result);
    with lkDTS do
      begin
      TrimSpace         := true;
      ReadOnly          := true;
      FileMustExist     := true;
      Delimiter         := '|';
      FirstLineAsSchema := false;
      Name     := MANAGEINTERFACE_STARTAUTO_NAME_DATASET;
      Schema.Clear;
      Schema.Add('FLAG_DELETE');
      Schema.Add('ID');
      Schema.Add('NAME');
      Schema.Add('FILEPATH');
      FileName := AmunhotepFileNameStartAutoGet;
      if not FileExists(FileName)then
        Amunhotep_StartAuto_Create(FileName);
      if not Active then  
        Open;
      end;
    lkDS  := TDataSource.Create(Result);
    with lkDS do
      begin
      Name    := MANAGEINTERFACE_STARTAUTO_NAME_DATASOURCE;
      DataSet := lkDTS;
      end;
    lkDBG := TDBGridEh.Create(Result);
    with lkDBG do
      begin
      Name            := MANAGEINTERFACE_STARTAUTO_NAME_DBGRID;
      Parent          := Result;
      Align           := alClient;
      DataSource      := lkDS;
      Flat            := true;
      Color           := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color      := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Style      := [fsBold];
      Font.Size       := 7;
      FixedColor      := Amunhotep.MainForm.StyleManager.Colors.Foreground;
      TitleFont.Color := Amunhotep.MainForm.StyleManager.Colors.Border;
      TitleFont.Style := [fsBold];
      //Options         := [dgTitles,dgColumnResize,dgColLines,dgRowLines,dgTabs,dgAlwaysShowSelection,dgConfirmDelete,dgCancelOnExit];
      UseMultiTitle   := true;
      Columns.Clear;
      lkCol := CreateTColumnEh(lkDBG,'FLAG_DELETE',''  , 'Акт.'      , 20,taLeftJustify);
      with lkCol do
        begin
        AlwaysShowEditButton := false;
        KeyList.Text         := '1'+#13#10+'0';
        PickList.Text        := 'X'+#13#10+'-';
        Checkboxes           := true;
        end; 
      lkCol := CreateTColumnEh(lkDBG,'ID'         ,''  , 'Приоритет' , 48,taRightJustify);
      lkCol := CreateTColumnEh(lkDBG,'NAME'       ,''  , 'Примечания',260,taLeftJustify );
      lkCol := CreateTColumnEh(lkDBG,'FILEPATH'   ,''  , 'Имя файла' ,520,taLeftJustify );
      lkCol.AlwaysShowEditButton := true;
      with lkCol.EditButtons.Add do
        begin
        Visible := true;
        Style   := ebsEllipsisEh;
        OnClick := @ManageInterface_StartAuto_DBGridEh_ColumnBtnEdit_OnClick;
        end;
      end;
  end;
