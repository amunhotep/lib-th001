{$DEFINE PEAKTOP:APPL/MANAGE/START/PARAMS/DEFAULT.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                     {$I PEAKTOP:OBJ/TACTION.INC}       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC}                   {$I PEAKTOP:OBJ/TCOLUMNEH.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:APPL/CONFIGFILENAMES.INC}            {$I ../../../CONFIGFILENAMES.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/$CUSTOM.INC}             {$I ../../$CUSTOM.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:APPL/MANAGE/START/PARAMS/CREATE.INC} {$I ./CREATE.INC}                  {$ENDIF}
const
  msg_manageinterface_startparams            = 'Параметры';
  msg_manageinterface_startparams_caption    = 'Параметры запуска приложения';
  msg_manageinterface_startparams_filefilter = 'AMUNHOTEP PascalScript Files (*.ps)|*.ps|Все файлы (*.*)|*.*';
  msg_manageinterface_startparams_selectfile = 'Выберите файл...';
const
  MANAGEINTERFACE_IMAGENAME_STARTPARAMS       = 'PEAKTOP:IMG/CONFIG/APP_OPTIONS0032X0032.BMP';
  MANAGEINTERFACE_STARTPARAMS_NAME_TOPBAR     = 'ManageInterface_StartParams_TopBar';  
  MANAGEINTERFACE_STARTPARAMS_NAME_TOOLBAR    = 'ManageInterface_StartParams_ToolBar';  
  MANAGEINTERFACE_STARTPARAMS_NAME_DATASET    = 'ManageInterface_StartParams_DataSet';  
  MANAGEINTERFACE_STARTPARAMS_NAME_DATASOURCE = 'ManageInterface_StartParams_DataSource';  
  MANAGEINTERFACE_STARTPARAMS_NAME_DBGRID     = 'ManageInterface_StartParams_DbGridEh';  
  //============================================================================
  procedure ManageInterface_StartParams_DBGridEh_ColumnBtnEdit_OnClick(Sender :TObject; var Handled : Boolean);
  var
    lkS   :string;
    lkDBG :TDBGridEh;
  begin
    Handled := true;
    lkS := '';  
    if PromptForFileName(lkS,msg_manageinterface_startparams_filefilter, 'PS', msg_manageinterface_startparams_selectfile, '', false)then
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
  function ManageInterface_StartParams_Create(aOwner:TComponent; aParent:TWinControl):TxcPanel;
  var
    lkAct     :TCustomAction;                                                                                                                                 
    lkDTS     :TxdbDataSetDelimited;
    lkDS      :TDataSource;
    lkDBG     :TDBGridEh;
    lkCol     :TColumnEh;
  begin
    Result := ManageInterface_Custom_Create(aOwner, aParent, MANAGEINTERFACE_STARTPARAMS_NAME_TOPBAR, MANAGEINTERFACE_STARTPARAMS_NAME_TOOLBAR, 
      msg_manageinterface_startparams_caption, PrepareAbsoleteFileName(MANAGEINTERFACE_IMAGENAME_STARTPARAMS) );

    lkDTS := TxdbDataSetDelimited.Create(Result);
    with lkDTS do
      begin
      TrimSpace         := true;
      ReadOnly          := true;
      FileMustExist     := true;
      Delimiter         := '|';
      FirstLineAsSchema := false;
      Name     := MANAGEINTERFACE_STARTPARAMS_NAME_DATASET;
      Schema.Clear;
      Schema.Add('FLAG_DELETE');
      Schema.Add('ID');
      Schema.Add('NAME');
      Schema.Add('FILEPATH');
      FileName := AmunhotepFileNameStartParamsGet;
      if not FileExists(FileName)then
        Amunhotep_StartParams_Create(FileName);
      if not Active then  
        Open;
      end;
    lkDS  := TDataSource.Create(Result);
    with lkDS do
      begin
      Name    := MANAGEINTERFACE_STARTPARAMS_NAME_DATASOURCE;
      DataSet := lkDTS;
      end;
    lkDBG := TDBGridEh.Create(Result);
    with lkDBG do
      begin
      Name            := MANAGEINTERFACE_STARTPARAMS_NAME_DBGRID;
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
      lkCol := CreateTColumnEh(lkDBG,'ID'         ,'', 'Имя параметра'   ,120,taLeftJustify);
      lkCol := CreateTColumnEh(lkDBG,'NAME'       ,'', 'Примечание'      ,260,taLeftJustify);
      lkCol := CreateTColumnEh(lkDBG,'FILEPATH'   ,'', 'Выполнить скрипт',520,taLeftJustify);
      lkCol.AlwaysShowEditButton := true;
      with lkCol.EditButtons.Add do
        begin
        Visible := true;
        Style   := ebsEllipsisEh;
        OnClick := @ManageInterface_StartParams_DBGridEh_ColumnBtnEdit_OnClick;
        end;
      end;
  end;
