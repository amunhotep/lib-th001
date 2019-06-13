{$DEFINE PEAKTOP:IDE/DEVELOPMENT/DESIGNER/POPUPMENU.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                    {$I PEAKTOP:OBJ/TACTION.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}                  {$I PEAKTOP:OBJ/TMENUITEM.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTRS.INC} {$I ./EDTRS.INC}               {$ENDIF}
const
  msg_act_enabled_caption              = 'Активен';
  msg_act_enabled_hint                 = 'Активен';
  msg_mi_edit_caption                  = 'Правка';
  msg_act_edit_cut_caption             = 'Вырезать';
  msg_act_edit_cut_hint                = 'Вырезать компоненты в буфер обмена';
  msg_act_edit_copy_caption            = 'Копировать';
  msg_act_edit_copy_hint               = 'Копировать компоненты в буфер обмена';
  msg_act_edit_paste_caption           = 'Вставить';
  msg_act_edit_paste_hint              = 'Вставить компоненты из буфера обмена';
  msg_act_edit_delete_caption          = 'Удалить';
  msg_act_edit_delete_hint             = 'Удалить компоненты из буфера обмена';
  msg_act_edit_selectall_caption       = 'Выделить все';
  msg_act_edit_selectall_hint          = 'Выделить все компоненты';
  msg_mi_control_caption               = 'Поместить';
  msg_act_control_aligntogrid_caption  = 'Выровнять по сетке';
  msg_act_control_aligntogrid_hint     = 'Выровнять компоненты по сетке дизайнера';
  msg_act_control_bringtofront_caption = 'На передний план';
  msg_act_control_bringtofront_hint    = 'Поместить на передний план';
  msg_act_control_sendtoback_caption   = 'На задний план';
  msg_act_control_sendtoback_hint      = 'Поместить на задний план';
const
  DesignerPopupMenuName = 'PopupMenuDesigner';
  //============================================================================
  function ValidCurrentDesigner:Boolean;
  begin
    Result := (Amunhotep.MainForm.DesignManager.CurrentDesigner <> nil);
  end;
  //============================================================================
  procedure actEnabled_OnExecute(Sender :TObject);
  begin
    TControl(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0]).Enabled := 
      not TControl(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0]).Enabled;
  end;
  //============================================================================
  procedure actEnabled_OnUpdate(Sender :TObject);
  var
    lk_Enabled :Boolean;
    lk_Checked :Boolean;
  begin
    lk_Enabled := ValidCurrentDesigner;
    if(lk_Enabled)then lk_Enabled := (Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.Count = 1);
    if(lk_Enabled)then lk_Enabled := ObjectInheritsFrom(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0], 'TControl');
    if(lk_Enabled)then 
      lk_Checked := TControl(Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents[0]).Enabled
     else
      lk_Checked := false;
    TCustomAction(Sender).Enabled := lk_Enabled;
    TCustomAction(Sender).Checked := lk_Checked;
  end;
  //============================================================================
  procedure actEditCut_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.DesignManager.CurrentDesigner.CutToClipboard;
  end;
  //============================================================================
  procedure actEditCut_OnUpdate(Sender :TObject);
  var
    lk_Enabled :Boolean;
  begin
    lk_Enabled := ValidCurrentDesigner;
    if(lk_Enabled)then lk_Enabled := Amunhotep.MainForm.DesignManager.CurrentDesigner.CanCutToClipboard;
    TCustomAction(Sender).Enabled := lk_Enabled;
  end;
  //============================================================================
  procedure actEditCopy_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.DesignManager.CurrentDesigner.CopyToClipboard;
  end;
  //============================================================================
  procedure actEditCopy_OnUpdate(Sender :TObject);
  var
    lk_Enabled :Boolean;
  begin
    lk_Enabled := ValidCurrentDesigner;
    if(lk_Enabled)then lk_Enabled := Amunhotep.MainForm.DesignManager.CurrentDesigner.CanCopyToClipboard;
    TCustomAction(Sender).Enabled := lk_Enabled;
  end;
  //============================================================================
  procedure actEditPaste_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.DesignManager.CurrentDesigner.PasteFromClipboard;
  end;
  //============================================================================
  procedure actEditPaste_OnUpdate(Sender :TObject);
  var
    lk_Enabled :Boolean;
  begin
    lk_Enabled := ValidCurrentDesigner;
    if(lk_Enabled)then lk_Enabled := Amunhotep.MainForm.DesignManager.CurrentDesigner.CanPasteFromClipboard;
    TCustomAction(Sender).Enabled := lk_Enabled;
  end;
  //============================================================================
  procedure actEditDelete_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.DesignManager.CurrentDesigner.DeleteSelectedComponents;
  end;
  //============================================================================
  procedure actEditSelectAll_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectAll;
  end;
  //============================================================================
  procedure actControl_OnUpdate(Sender :TObject);
  var
    lk_Enabled :Boolean;
  begin
    lk_Enabled := ValidCurrentDesigner;
    if(lk_Enabled)then lk_Enabled := (Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.Count > 0);
    TCustomAction(Sender).Enabled := lk_Enabled;
  end;
  //============================================================================
  procedure actControlAlignToGrid_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.AlignToGrid;
  end;
  //============================================================================
  procedure actControlBringToFront_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.BringToFront;
  end;
  //============================================================================
  procedure actControlSendToBack_OnExecute(Sender :TObject);
  begin
    Amunhotep.MainForm.DesignManager.CurrentDesigner.SelectedComponents.SendToBack;
  end;
  //============================================================================
  function DesignerPopupMenu_Create(aOwner:TComponent):TPopupMenu;
  var
    lk_mi_main :TMenuItem;
    lk_mi_sub  :TMenuItem;
    lk_act     :TCustomAction;
  begin
    Result        := TPopupMenu.Create(aOwner);
    Result.Name   := DesignerPopupMenuName;
    Result.Images := Amunhotep.MainForm.ImageListMain;
    DesignerPopupMenu_RegisterEditorsBefore(aOwner, Result);
    // -----------
    lk_mi_main := CreateTMenuItem(Result.Items,'miN0000','-','-','', -1, 0);
    // actEnabled
    lk_act            := CreateTAction(aOwner, 'actEnabled', msg_act_enabled_caption, msg_act_enabled_hint, '', 2, -1);
    lk_act.OnExecute  := @actEnabled_OnExecute;
    lk_act.OnUpdate   := @actEnabled_OnUpdate;
    lk_mi_main := CreateTMenuItem2(Result.Items, lk_act);
    // -----------
    lk_mi_main := CreateTMenuItem(Result.Items,'miN0001','-','-','', -1, 0);
    // miEdit
    lk_mi_main := CreateTMenuItem(Result.Items,'miEdit',msg_mi_edit_caption, msg_mi_edit_caption,'', -1, 0);
      // actEditCut
      lk_act           := CreateTAction(aOwner, 'actEditCut', msg_act_edit_cut_caption, msg_act_edit_cut_hint, 'Ctrl+X', 0, 69);
      lk_act.OnExecute := @actEditCut_OnExecute;
      lk_act.OnUpdate  := @actEditCut_OnUpdate;
      lk_mi_sub        := CreateTMenuItem2(lk_mi_main, lk_act);
      // actEditCopy
      lk_act           := CreateTAction(aOwner, 'actEditCopy', msg_act_edit_copy_caption, msg_act_edit_copy_hint, 'Ctrl+C', 0, 68);
      lk_act.OnExecute := @actEditCopy_OnExecute;
      lk_act.OnUpdate  := @actEditCopy_OnUpdate;
      lk_mi_sub        := CreateTMenuItem2(lk_mi_main, lk_act);
      // actEditPaste
      lk_act           := CreateTAction(aOwner, 'actEditPaste', msg_act_edit_paste_caption, msg_act_edit_paste_hint, 'Ctrl+V', 0, 73);
      lk_act.OnExecute := @actEditPaste_OnExecute;
      lk_act.OnUpdate  := @actEditPaste_OnUpdate;
      lk_mi_sub        := CreateTMenuItem2(lk_mi_main, lk_act);
      // actEditDelete
      lk_act           := CreateTAction(aOwner, 'actEditDelete', msg_act_edit_delete_caption, msg_act_edit_delete_hint, 'Ctrl+Del', 0, 70);
      lk_act.OnExecute := @actEditDelete_OnExecute;
      lk_mi_sub        := CreateTMenuItem2(lk_mi_main, lk_act);
      // -----------
      lk_mi_sub        := CreateTMenuItem(lk_mi_main,'miEditN0001','-','-','', -1, 0);
      // actEditDelete
      lk_act           := CreateTAction(aOwner, 'actEditSelectAll', msg_act_edit_selectall_caption, msg_act_edit_selectall_hint, 'Ctrl+A', 0, 245);
      lk_act.OnExecute := @actEditSelectAll_OnExecute;
      lk_mi_sub        := CreateTMenuItem2(lk_mi_main, lk_act);
    // miControl
    lk_mi_main := CreateTMenuItem(Result.Items,'miControl',msg_mi_control_caption, msg_mi_control_caption,'', -1, 0);
      //actControlBringToFront
      lk_act           := CreateTAction(aOwner, 'actControlBringToFront', msg_act_control_bringtofront_caption, msg_act_control_bringtofront_hint, '', 0, 223);
      lk_act.OnExecute := @actControlBringToFront_OnExecute;
      lk_act.OnUpdate  := @actControl_OnUpdate;
      lk_mi_sub        := CreateTMenuItem2(lk_mi_main, lk_act);
      //actControlSendToBack
      lk_act           := CreateTAction(aOwner, 'actControlSendToBack', msg_act_control_sendtoback_caption, msg_act_control_sendtoback_hint, '', 0, 225);
      lk_act.OnExecute := @actControlSendToBack_OnExecute;
      lk_act.OnUpdate  := @actControl_OnUpdate;
      lk_mi_sub        := CreateTMenuItem2(lk_mi_main, lk_act);
      // -----------
      lk_mi_sub        := CreateTMenuItem(lk_mi_main,'miControlN0001','-','-','', -1, 0);
      //actControlAlignToGrid
      lk_act           := CreateTAction(aOwner, 'actControlAlignToGrid', msg_act_control_aligntogrid_caption, msg_act_control_aligntogrid_hint, '', 0, 10);
      lk_act.OnExecute := @actControlAlignToGrid_OnExecute;
      lk_act.OnUpdate  := @actControl_OnUpdate;
      lk_mi_sub        := CreateTMenuItem2(lk_mi_main, lk_act);
    // -----------
    lk_mi_main := CreateTMenuItem(Result.Items,'miN0002','-','-','', -1, 0);
    DesignerPopupMenu_RegisterEditorsAfter(aOwner, Result);
    Amunhotep.MainForm.xcMenu.AddMenu(Result);
  end;
  //============================================================================
  function DesignerPopupMenu_Get(aOwner :TComponent):TPopupMenu;
  var
    lk_Comp :TComponent;
  begin
    lk_Comp := aOwner.FindComponent(DesignerPopupMenuName); 
    if(lk_Comp <> nil)then
      Result := TPopupMenu(lk_Comp)
     else
      Result := DesignerPopupMenu_Create(aOwner);  
  end;
