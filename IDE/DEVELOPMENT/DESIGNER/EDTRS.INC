{$DEFINE PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTRS.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}    {$I PEAKTOP:OBJ/TACTION.INC}    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}  {$I PEAKTOP:OBJ/TMENUITEM.INC}  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_FORMTOPASCAL.INC}     {$I ./EDTR_FORMTOPASCAL.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_TXCPAGECONTROL.INC}   {$I ./EDTR_TXCPAGECONTROL.INC}   {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_TXCPAGECONTROLEX.INC} {$I ./EDTR_TXCPAGECONTROLEX.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_TXCGROUPBAR.INC}      {$I ./EDTR_TXCGROUPBAR.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_TXCOUTLOOK.INC}       {$I ./EDTR_TXCOUTLOOK.INC}       {$ENDIF}
  //============================================================================
  procedure DesignerPopupMenu_RegisterEditorsBefore(aOwner:TComponent; aDesignerPopupMenu:TPopupMenu);
  var
    lk_mi_main :TMenuItem;
    lk_act     :TCustomAction;
  begin
    //actPageControlAddPage
    lk_act            := CreateTAction(aOwner, 'actPageControlAddPage', 
                           msg_act_pagecontroladdpage_caption, 
                           msg_act_pagecontroladdpage_caption, '', 0, 361);
    lk_act.OnExecute  := @actPageControlAddPage_OnExecute;
    lk_act.OnUpdate   := @actPageControlAddPage_OnUpdate;
    lk_mi_main := CreateTMenuItem2(aDesignerPopupMenu.Items, lk_act);
    //actPageControlExAddPage
    lk_act            := CreateTAction(aOwner, 'actPageControlExAddPage', 
                           msg_act_pagecontrolexaddpage_caption, 
                           msg_act_pagecontrolexaddpage_caption, '', 0, 361);
    lk_act.OnExecute  := @actPageControlExAddPage_OnExecute;
    lk_act.OnUpdate   := @actPageControlExAddPage_OnUpdate;
    lk_mi_main := CreateTMenuItem2(aDesignerPopupMenu.Items, lk_act);
    //actGroupBarAddBar
    lk_act            := CreateTAction(aOwner, 'actGroupBarAddBar', 
                           msg_act_groupbaraddbar_caption, 
                           msg_act_groupbaraddbar_caption, '', 0, 361);
    lk_act.OnExecute  := @actGroupBarAddBar_OnExecute;
    lk_act.OnUpdate   := @actGroupBarAddBar_OnUpdate;
    lk_mi_main := CreateTMenuItem2(aDesignerPopupMenu.Items, lk_act);
    //actOutlookAddHeader
    lk_act            := CreateTAction(aOwner, 'actOutlookAddHeader', 
                           msg_act_OutlookAddHeader_caption, 
                           msg_act_OutlookAddHeader_caption, '', 0, 361);
    lk_act.OnExecute  := @actOutlookAddHeader_OnExecute;
    lk_act.OnUpdate   := @actOutlookAddHeader_OnUpdate;
    lk_mi_main := CreateTMenuItem2(aDesignerPopupMenu.Items, lk_act);
    //actOutlookAddButton
    lk_act            := CreateTAction(aOwner, 'actOutlookAddButton', 
                           msg_act_OutlookAddButton_caption, 
                           msg_act_OutlookAddButton_caption, '', 0, 361);
    lk_act.OnExecute  := @actOutlookAddButton_OnExecute;
    lk_act.OnUpdate   := @actOutlookAddButton_OnUpdate;
    lk_mi_main := CreateTMenuItem2(aDesignerPopupMenu.Items, lk_act);
  end;
  //============================================================================
  procedure DesignerPopupMenu_RegisterEditorsAfter(aOwner:TComponent; aDesignerPopupMenu:TPopupMenu);
  var
    lk_mi_main :TMenuItem;
    lk_act     :TCustomAction;
  begin
    //actPopupMenuDesigner_FormToPascal
    lk_act := CreateTAction(aOwner, 'actPopupMenuDesigner_FormToPascal', 
      msg_actpopupmenudesigner_formtopascal_caption, msg_actpopupmenudesigner_formtopascal_hint, '', 0, 26);
    lk_act.OnExecute  := @actPopupMenuDesigner_FormToPascal_OnExecute;
    lk_act.OnUpdate   := @actPopupMenuDesigner_FormToPascal_OnUpdate;
    lk_mi_main := CreateTMenuItem2(aDesignerPopupMenu.Items, lk_act);
  end;
