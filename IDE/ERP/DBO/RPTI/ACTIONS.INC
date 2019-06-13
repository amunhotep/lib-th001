{$DEFINE PEAKTOP:IDE/ERP/DBO/RPTI/ACTIONS.INC}
  //======================= PEAKTOP:IDE/ERP/DBO/RPTI/ACTIONS.INC ===============
  procedure TERPFormRpti_actClose_OnExecute(Sender :TObject);
  var
    lkOwner :TComponent;
  begin
    lkOwner := TComponent(Sender).Owner;
    TERPForm_GridSettingsSave(TERPForm_DBGridMain(lkOwner), TERPForm_Settings(lkOwner).Values[ERP_SETTINGS_TEMPFILENAME]);
    if(ObjectInheritsFrom(lkOwner, 'TForm'))then
      begin
      if(TForm(lkOwner).FormStyle <> fsMDIChild)then
        begin
        TForm(lkOwner).ModalResult := mrCancel;
        exit;
        end;
      end;      
    lkOwner.Free;
  end;  

