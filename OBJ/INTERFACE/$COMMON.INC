{$DEFINE PEAKTOP:OBJ/INTERFACE/$COMMON.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}               {$I PEAKTOP:OBJ/TACTION.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$ENDIF}
const //================ PEAKTOP:OBJ/INTERFACE/$COMMON.INC =====================
  msg_interface_actload            = 'Загрузить';
  msg_interface_actload_hint       = 'Загрузить из внешнего файла';
  msg_interface_actsave            = 'Сохранить';
  msg_interface_actsave_hint       = 'Сохранить во внешний файл';
  msg_interface_actcut             = 'Вырезать';
  msg_interface_actcut_hint        = 'Вырезать в буфер обмена';
  msg_interface_actcopy            = 'Копировать';
  msg_interface_actcopy_hint       = 'Копировать в буфер обмена';
  msg_interface_actpaste           = 'Вставить';
  msg_interface_actpaste_hint      = 'Вставить из буфера обмена';
  msg_interface_actdelete          = 'Удалить';
  msg_interface_actdelete_hint     = 'Удалить выделенный фрагмент';
  msg_interface_actselectall       = 'Выделить все';
  msg_interface_actselectall_hint  = 'Выделить все';
  //============================================================================
  function Interface_CreateTAction(aOwner :TComponent; aParent:TWinControl; const aName, aCaption, aHint, aShortCut:string;
             const aGroupIndex, aImageIndex :Integer;  aOnExecute, aOnUpdate :TNotifyEvent):TCustomAction;
  var
    lkTBB :TxcToolBarButton;
  begin
    Result := CreateTAction(aOwner, aName, aCaption, aHint, aShortCut, aGroupIndex, aImageIndex); 
    Result.OnExecute := aOnExecute; 
    Result.OnUpdate  := aOnUpdate; 
    lkTBB := CreateTxcToolBarButton3(aParent, aParent, Result);
  end;
