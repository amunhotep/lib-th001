{$DEFINE PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}               {$I PEAKTOP:OBJ/TACTION.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TLABEL.INC}                {$I PEAKTOP:OBJ/TLABEL.INC}                {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$ENDIF}
const //================ PEAKTOP:OBJ/DBINTERFACE/$COMMON.INC ===================
  msg_error_blobimpossible           = 'Невозможно выполнить команду ';
  msg_error_blobobjectisreadonly     = 'Объект доступен только для чтения!';
  msg_error_loadtwainmodule          = 'Не удаётся загрузить модуль сканера';
  msg_dbinterface_actload            = 'Открыть';
  msg_dbinterface_actload_hint       = 'Загрузить из внешнего файла';
  msg_dbinterface_actload2           = 'Web-камера';
  msg_dbinterface_actload2_hint      = 'Загрузить изображение из Web-камеры';
  msg_dbinterface_actload3           = 'Сканер';
  msg_dbinterface_actload3_hint      = 'Отсканировать изображение и загрузить';
  msg_dbinterface_actsave            = 'Сохранить';
  msg_dbinterface_actsave_hint       = 'Сохранить во внешний файл';
  msg_dbinterface_actcut             = 'Вырезать';
  msg_dbinterface_actcut_hint        = 'Вырезать в буфер обмена';
  msg_dbinterface_actcopy            = 'Копировать';
  msg_dbinterface_actcopy_hint       = 'Копировать в буфер обмена';
  msg_dbinterface_actpaste           = 'Вставить';
  msg_dbinterface_actpaste_hint      = 'Вставить из буфера обмена';
  msg_dbinterface_actdelete          = 'Удалить';
  msg_dbinterface_actdelete_hint     = 'Удалить выделенный фрагмент';
  msg_dbinterface_actselectall       = 'Выделить все';
  msg_dbinterface_actselectall_hint  = 'Выделить все';
  //============================================================================
  function DBInterface_CreateTAction(aOwner :TComponent; aParent:TWinControl; 
             const aName, aCaption, aHint, aShortCut:string;
             const aGroupIndex, aImageIndex :Integer;
             aOnExecute, aOnUpdate :TNotifyEvent
             ):TCustomAction;
  var
    lkTBB      :TxcToolBarButton;
    lkLastLeft :Integer;
    i          :Integer; 
  begin
    Result := CreateTAction(aOwner, aName, aCaption, aHint, aShortCut, aGroupIndex, aImageIndex); 
    Result.OnExecute := aOnExecute; 
    Result.OnUpdate  := aOnUpdate; 
    lkLastLeft := 0;
    for i:=0 to aParent.ControlCount-1 do
      lkLastLeft := MaxInteger(lkLastLeft, aParent.Controls[i].Left + aParent.Controls[i].Width + 1);
    lkTBB := CreateTxcToolBarButton2(aParent, aParent, 'TBB'+Result.Name, lkLastLeft, 1, 22, 22, alLeft, Result);
  end;
  //============================================================================
  function DBInterface_CreateTAction2(aOwner :TComponent; aParent:TWinControl;
             const aWidth:Integer; const aShowCaption:Boolean; 
             const aName, aCaption, aHint, aShortCut:string;
             const aGroupIndex, aImageIndex :Integer;
             aOnExecute, aOnUpdate :TNotifyEvent
             ):TCustomAction;
  var
    lkTBB      :TxcToolBarButton;
    lkLastLeft :Integer;
    i          :Integer; 
  begin
    Result := CreateTAction(aOwner, aName, aCaption, aHint, aShortCut, aGroupIndex, aImageIndex); 
    Result.OnExecute := aOnExecute; 
    Result.OnUpdate  := aOnUpdate; 
    lkLastLeft := 0;
    for i:=0 to aParent.ControlCount-1 do
      lkLastLeft := MaxInteger(lkLastLeft, aParent.Controls[i].Left + aParent.Controls[i].Width + 1);
    lkTBB := CreateTxcToolBarButton2(aParent, aParent, 'TBB'+Result.Name, lkLastLeft, 1, 22, aWidth, alLeft, Result);
    lkTBB.ShowCaption := aShowCaption;
  end;  
