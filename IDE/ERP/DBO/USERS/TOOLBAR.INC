{$DEFINE PEAKTOP:IDE/ERP/DBO/USERS/TOOLBAR.INC}
{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}               {$I PEAKTOP:GLOBAL_VARIABLES.INC}          {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                 {$I PEAKTOP:OBJ/TIMAGELIST.INC}            {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                    {$I PEAKTOP:OBJ/TACTION.INC}               {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}           {$I PEAKTOP:OBJ/TXCTOOLBARBUTTON.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}      {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/USERS/CONTROLSNAMES.INC}{$I ./CONTROLSNAMES.INC}                   {$ENDIF}
  //================= PEAKTOP:IDE/ERP/DBO/USERS/TOOLBAR.INC ====================
  procedure actRef_OnExecute(Sender :TObject);
  begin
    call(StrAbsolutePath('../../REF/'+TCustomAction(Sender).HelpKeyWord+'/DEFAULT.PS', ScriptName));
  end;
  //============================================================================
  procedure actDocNew_OnExecute(Sender :TObject);
  begin
    call(StrAbsolutePath('../../DOC/'+IntToStr(TComponent(Sender).Tag)+'/NEW.PS', ScriptName));
  end;
  //============================================================================
  procedure actDocNewFirm1_OnExecute(Sender :TObject);
  begin
    call(StrAbsolutePath('../../DOC/'+IntToStr(TComponent(Sender).Tag)+'/NEW_FIRM1.PS', ScriptName));
  end;
  //============================================================================
  procedure actJrnl_OnExecute(Sender :TObject);
  begin
    call(StrAbsolutePath('../../DOC/'+IntToStr(TComponent(Sender).Tag)+'/DEFAULT.PS', ScriptName));
  end;
  //============================================================================
  procedure actRpt_OnExecute(Sender :TObject);
  begin
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG/RPTI/'+TCustomAction(Sender).HelpKeyWord+'/DEFAULT.PS'));
  end;
  //============================================================================
  procedure actRef2_OnExecute(Sender :TObject);
  begin
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/REF/'+TCustomAction(Sender).HelpKeyWord+'/DEFAULT.PS'));
  end;
  //============================================================================
  procedure actDocNew2_OnExecute(Sender :TObject);
  begin
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/DOC/'+IntToStr(TComponent(Sender).Tag)+'/NEW.PS'));
  end;
  //============================================================================
  procedure actJrnl2_OnExecute(Sender :TObject);
  begin
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/DOC/'+IntToStr(TComponent(Sender).Tag)+'/DEFAULT.PS'));
  end;
  //============================================================================
  procedure actRpt2_OnExecute(Sender :TObject);
  begin
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/CONFIG2/RPTI/'+TCustomAction(Sender).HelpKeyWord+'/DEFAULT.PS'));
  end;
  //============================================================================
  function CreateToolBarRole(const aRoleId :string):TxcGradientPanelVista;
  begin
    Result := CreateTxcGradientPanelVistaToolBar(Amunhotep.MainForm, Amunhotep.MainForm, ERP_POS_CONTROL_TOOLBAR+aRoleId, '', alTop, 1, 1, 24, 200, xbsRaized);
    with Result do
      begin
      Font.Name  := 'Verdana';
      Font.Size  := 7;
      Font.Style := [fsBold];
      end;
  end;
