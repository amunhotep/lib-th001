{$DEFINE PEAKTOP:IDE/$COMMON/DLG.INC}
{$IFNDEF PEAKTOP:APPL/LOCAL/VARIABLE.INC}                {$I PEAKTOP:APPL/LOCAL/VARIABLE.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:APPL/LOCAL/FILE.INC}                    {$I PEAKTOP:APPL/LOCAL/FILE.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}              {$I PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}         {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}          {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}     {$ENDIF}
{$IFNDEF PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}             {$I PEAKTOP:IDE/$COMMON/FORMCOMMON.INC}        {$ENDIF}
  //========================== PEAKTOP:IDE/$COMMON/DLG.INC =====================
  function TDlg_Create(const aCaption, aPrompt, aIconFileName, aImageFileName:string; const aColor:TColor; const aWidth, aHeight:Integer):TForm;
  begin
    Result := TCommonForm_Create(aCaption, aPrompt, aIconFileName, aImageFileName, True, nil);
    with Result do
      begin
      Width  := aWidth;
      Height := aHeight;
      end;
    TCommonForm_SetTopBarColor( Result, aColor );
    with TxcGradientPanelVista( Result.FindComponent(obj_name_common_topbar) ) do
      begin
      Caption := #$20#$20#$20#$20#$20#$20+aPrompt;
      end;  
  end;
  
