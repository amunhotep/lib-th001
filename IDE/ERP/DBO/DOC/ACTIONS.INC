{$DEFINE PEAKTOP:IDE/ERP/DBO/DOC/ACTIONS.INC}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}  {$I ../$COMMON/FORMERP.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/DOC/OPEN.INC}         {$I ./OPEN.INC}             {$ENDIF}
  //==================== PEAKTOP:IDE/ERP/DBO/DOC/ACTIONS.INC ===================
  procedure TERPFormGridJrnl_actDocGotoDay_OnExecute(Sender :TObject);
  var
    lkOwner    :TComponent;
    lkTypeId   :string;
    lkTypeChld :string;
    lkID       :string;
    lkStr      :string;
  begin
    lkOwner  := TComponent(Sender).Owner;
    lkTypeId := TForm(lkOwner).HelpKeyWord;
    if ERP_DialogDocOpen_Execute(lkTypeId, lkID)then
      begin
      lkStr := FormatDateTime('dd.mm.yyyy', TERPFormGrid_dtpDateFrom(lkOwner).Date)+' 00:00:00';
      if GetField(FBDataBase, TERPForm_Settings(lkOwner).Values[ERP_SETTINGS_TABLENAME], 'DATE_COMMIT', 'ID = '+lkID, lkStr)then
        begin
        lkStr := StrReplaceStr(lkStr,'/','.');
        lkStr := StrReplaceStr(lkStr,'\','.');
        TERPFormGrid_dtpDateFrom(lkOwner).Date := StrToDateTime(lkStr);
        TERPFormGrid_dtpDateTo  (lkOwner).Date := StrToDateTime(lkStr);
        SetGlobalVariable(TERPForm_Settings(lkOwner).Values[ERP_SETTINGS_GOTOVAR], lkID);
        TERPFormGrid_RefreshView(lkOwner);
        end;
      end;
  end;
