{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_CASEOBJECTFOLDER.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC} {$I ./FORMERP.INC}  {$ENDIF}
  //========== PEAKTOP:IDE/ERP/DBO/$COMMON/DIALOG_CASEOBJECTFOLDER.INC =========
const ERP_OBJNAME_OPER_DLG_CASEOBJECTFOLDER = 'DLG_CASEOBJECTFOLDER';
  //============================================================================
  procedure ERPDialogCaseObjFolder_FBTreeView_OnBuildNode(Sender :TObject; StateFieldValue :Variant; var StateImage :Integer);
  begin
    StateImage := Integer(StateFieldValue);
  end;
  //============================================================================
  procedure ERPDialogCaseObjFolder_FBTreeView_OnDblClick(Sender :TObject);
  begin
    TForm(TComponent(Sender).Owner).ModalResult := mrOk;
  end;
  //============================================================================
  function ERPDialogCaseObjFolder_Create(const aObjectType:Integer):TForm;
  var
    lkFBTree  :TxFBTreeView;
  begin
    Result := TERPForm_Create('Выберите расположение объекта',  ERP_ObjectIcon(aObjectType), ERP_ObjectBitmap(aObjectType), true, nil);
    with Result do
      begin
      Position := poDesigned;
      end;            
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(aObjectType);
      Colors.HotTrackBorder := ERP_ObjectColor(aObjectType);
      end;  
    TForm_Position_Load(Result, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLG_CASEOBJECTFOLDER,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))), 400, 400);             
    lkFBTree := TxFBTreeView.Create(Result);
    with lkFBTree do
      begin
      Name      := obj_name_erp_treeview;
      Parent    := Result;
      Left      := 0;
      Top       := 0;
      Width     := 180;
      Ctl3D     := false;
      Align     := alClient;
      Color     := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color:= Amunhotep.MainForm.StyleManager.Colors.Border;
      Images    := CreateTImageListConfiguration(lkFBTree, 'ilConfig');
      DataBase  := FBDataBase;
      with DBTreeInfo do
        begin
        TableName     := 'PROC$_TYPES';
        FieldId       := 'ID';
        FieldParentId := 'PARENT_ID';
        FieldStateId  := 'IMG_IDX';
        FieldName     := 'NAME';
        Where         := '(TYPE_ID = '''+IntToStr(aObjectType)+''')';
        end;
      ShowOnlyRoots    := false;
      RightClickSelect := true;
      HideSelection    := false;
      OnBuildNode      := @ERPDialogCaseObjFolder_FBTreeView_OnBuildNode;  
      OnDblClick       := @ERPDialogCaseObjFolder_FBTreeView_OnDblClick;
      BuildTree;
      if(Items.Count > 0)then
        begin
        Items[0].Selected := true;
        Items[0].Expand(true);
        end;  
      end;
  end;
  //============================================================================
  function ERPDialogCaseObjFolder_Execute(const aObjectType:Integer; var aTypeId:string):Boolean;
  var
    lkForm :TForm;
  begin
    lkForm := ERPDialogCaseObjFolder_Create(aObjectType);
    Result := (lkForm.ShowModal = mrOk);
    if Result then
      aTypeId := TxFBTreeView(lkForm.FindComponent(obj_name_erp_treeview)).GetId;
    TForm_Position_Save(lkForm, PrepareAbsoleteFileName(ERP_ObjectTempFileName(ERP_OBJECTTYPE_OPER,ERP_OBJECTTYPE_OPER, ERP_OBJNAME_OPER_DLG_CASEOBJECTFOLDER,GetGlobalVariable(ERP_GLOBALVARIABLE_USER_CURRENT))));   
    lkForm.Free; 
  end;  
