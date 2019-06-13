{$DEFINE PEAKTOP:IDE/ERP/DBO/USERS/TOPPLACEBAR.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}                {$I PEAKTOP:GLOBAL_VARIABLES.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                  {$I PEAKTOP:OBJ/TIMAGELIST.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                     {$I PEAKTOP:OBJ/TACTION.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}            {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}       {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}            {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}                 {$I PEAKTOP:OBJ/TXCTABSHEET.INC}           {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/CONTROLSNAMES.INC} {$I ./CONTROLSNAMES.INC}                   {$ENDIF}
  //============= PEAKTOP:IDE/ERP/DBO/USERS/TOPPLACEBAR.INC ====================
  function CreateTopPlaceBarRole(const aRoleId :string):TxcPageControlEx;
  begin
    Result := CreateTxcPageControlEx(Amunhotep.MainForm, Amunhotep.MainForm, ERP_POS_CONTROL_TOPPLACEBAR+aRoleId, 0,0,48,200, alTop);
    with Result do
      begin
      SoftCorners    := False;
      SortTabMenu    := False;
      TabHeight      := Amunhotep.MainForm.ImageListMain.Height + 4;
      TabOrientation := toTop;
      TabSequence    := tsStandard;
      TabStyle       := tsSquareCorners;
      end;
  end;
