{$DEFINE PEAKTOP:IDE/DEVELOPMENT/DESIGNER/EDTR_FORMTOPASCAL.INC}
  //============================================================================
  function AmunhotepFormToPascal(F :TAmunhotepForm):string;
  var
    i   :Integer;
    Comp:TComponent;    
    SL  :TStringList;
    src, src_var, src_find, src_find_free, src_inc :string;
    res1 :string;
    procs :string;
    ResCount :Integer;
    MaxName :Integer;
  begin
    SL  := TStringList.Create;
    SL.Text  := '';
    for i:=0 to F.ComponentCount-1 do
      if(F.Components[i].Name<>'')then
        SL.Add(F.Components[i].Name);
    MaxName := 0;
    for i:=0 to SL.Count-1 do
      if(Length(SL[i])>MaxName)then
        MaxName := Length(SL[i]);  
    src_var  := '';
    src_find := '';
    src_find_free := ''; 
    src_inc  := '{$IFNDEF PEAKTOP:GLOBAL_VARIABLES.INC}  {$I PEAKTOP:GLOBAL_VARIABLES.INC}  {$ENDIF}'+#13#10;
    res1     := '  '+StrEndSpaces('msg_caption', 64)+'= '''+F.Caption+'''; '+#13#10; 
    procs    := '';
    procs    := procs + 
     '  //============================================================================'+#13#10+
     '  procedure RefreshView;'+#13#10+
     '  begin '+#13#10+
     '  { '+#13#10+
     '    if trRef.InTransaction then '+#13#10+
     '      trRef.Commit; '+#13#10+
     '    qrRef.SQL.Text :=  '+#13#10+
     '      '' ''+#13#10+ '+#13#10+
     '      ''''; '+#13#10+
     '    try '+#13#10+
     '      qrRef.Open; '+#13#10+
     '    except '+#13#10+
     '      // Dialogs.MessageDlg(qrRef.SQL.Text, mtError, [mbOk]);'+#13#10+
     '    end;'+#13#10+
     '  }'+#13#10+
     '  end;'+#13#10;
    ResCount := 0;
    //TTABSHEET
    for i:=0 to SL.Count-1 do
      begin
      Comp := F.FindComponent(SL[i]);
      src_var  := src_var  + '  '+StrEndSpaces(SL[i], MaxName)+' :'+Comp.ClassName+'; ';
      src_find := src_find + '    '+StrEndSpaces(SL[i], MaxName+20)+' := '+Comp.ClassName+'(Result.FindComponent('''+SL[i]+'''));'+#13#10;
      if(AnsiUpperCase(Comp.ClassName) = 'TACTION')then
        begin
        src_var  := src_var  + '// may be no need ? ';
        ResCount := ResCount + 1;
        src_inc  := src_inc  + '{$IFNDEF PEAKTOP:OBJ/TACTION.INC}{$I PEAKTOP:OBJ/TACTION.INC}{$ENDIF}'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i]), 64)+'= '''+TAction(Comp).Caption+'''; '+#13#10;
        ResCount := ResCount + 1;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i])+'_hint', 64)+'= '''+TAction(Comp).Hint+'''; '+#13#10;
        src_find := src_find + '    lkAct := FindTAction(Result,'''+SL[i]+''',msg_'+AnsiLowerCase(SL[i])+',msg_'+AnsiLowerCase(SL[i])+'_hint,'''''+
          ', 0, -1); lkAct.OnExecute:=@'+Comp.Name+'_OnExecute; lkAct.OnUpdate:=@'+Comp.Name+'_OnUpdate; '+#13#10;
        procs    := procs + 
         '  //============================================================================'+#13#10+
         '  procedure '+Comp.Name+'_OnExecute(Sender :TObject);'+#13#10+
         '  begin'+#13#10+
         '  end;'+#13#10+
         '  //============================================================================'+#13#10+
         '  procedure '+Comp.Name+'_OnUpdate(Sender :TObject);'+#13#10+
         '  var'+#13#10+
         '    lkEnabled :Boolean;'+#13#10+
         '  begin'+#13#10+
         '    lkEnabled := true;'+#13#10+
         '    if(lkEnabled)then'+#13#10+
         '      lkEnabled := true;'+#13#10+
         '    TCustomAction(Sender).Enabled := lkEnabled;'+#13#10+
         '  end;'+#13#10;
        end;
      if(AnsiUpperCase(Comp.ClassName) = 'TXFBEVENTS')then
        begin
        src_find := src_find + 
          '    with '+Comp.Name+' do'+#13#10+ 
          '      begin '+#13#10+ 
          '      Events.Clear;'+#13#10+
          '      Events.Add(''TABL$R_'');'+#13#10+
          '      OnEventAlert := @'+Comp.Name+'_OnEventAlert;'+#13#10+
          '      end; '+#13#10+
          '    if not '+Comp.Name+'.Registered then '+Comp.Name+'.RegisterEvents; '+#13#10; 
        src_find_free := src_find_free + '    if '+Comp.Name+'.Registered then '+Comp.Name+'.UnRegisterEvents; '+#13#10;;
        procs    := procs + 
         '  //============================================================================'+#13#10+
         '  procedure '+Comp.Name+'_OnEventAlert(Sender :TObject; EventName: string; EventCount: LongInt; var CancelAlerts: Boolean);'+#13#10+
         '  begin'+#13#10+
         '    // RefreshView; '+#13#10+
         '    CancelAlerts := false;'+#13#10+
         '  end;'+#13#10;
        end;
      if(AnsiUpperCase(Comp.ClassName) = 'TXFBTRANSACTION')then
        begin
        src_find := src_find +
          '    with '+Comp.Name+' do '+#13#10+
          '      begin '+#13#10+
          '      DefaultDataBase := FBDataBase; '+#13#10+
          '      Params.Clear; '+#13#10+
          '      Params.Add(''isc_tpb_read_committed''); '+#13#10+
          '      Params.Add(''isc_tpb_write''); '+#13#10+
          '      Params.Add(''isc_tpb_rec_version''); '+#13#10+
          '      Params.Add(''isc_tpb_nowait''); '+#13#10+
          '      end; '+#13#10;
        end;
      if((AnsiUpperCase(Comp.ClassName) = 'TXFBQUERY')or(AnsiUpperCase(Comp.ClassName) = 'TXFBTABLE')or(AnsiUpperCase(Comp.ClassName) = 'TXFBDATASET'))then
        begin
        src_find := src_find +
          '    with '+Comp.Name+' do'+#13#10+ 
          '      begin '+#13#10+ 
          '      AfterOpen   := @'+Comp.Name+'_AfterOpen;'+#13#10+
          '      BeforeClose := @'+Comp.Name+'_BeforeClose;'+#13#10+
          '      AfterScroll := @'+Comp.Name+'_AfterScroll;'+#13#10+
          '      end '+#13#10; 
        procs    := procs + 
         '  //============================================================================'+#13#10+
         '  procedure '+Comp.Name+'_AfterOpen(DataSet :TDataSet);'+#13#10+
         '  begin'+#13#10+
         '  end;'+#13#10+
         '  //============================================================================'+#13#10+
         '  procedure '+Comp.Name+'_BeforeClose(DataSet :TDataSet);'+#13#10+
         '  begin'+#13#10+
         '  end;'+#13#10+
         '  //============================================================================'+#13#10+
         '  procedure '+Comp.Name+'_AfterScroll(DataSet :TDataSet);'+#13#10+
         '  begin'+#13#10+
         '  end;'+#13#10;
        end;
{
      if(AnsiUpperCase(Comp.ClassName) = 'TMENUITEM')then
        begin
        ResCount := ResCount + 1;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Caption', MaxName+20)+' := msg_'+AnsiLowerCase(SL[i])+' ;'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i]), 32)+'= '''+TMENUITEM(Comp).Caption+'''; '+#13#10;
        ResCount := ResCount + 1;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Hint', MaxName+20)+' := msg_'+AnsiLowerCase(SL[i])+' ;'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i]), 32)+'= '''+TMENUITEM(Comp).Hint+'''; '+#13#10;
        end;
}
      if(AnsiUpperCase(Comp.ClassName) = 'TLABEL')then
        begin
        src_var  := src_var  + '// may be no need ? ';
        ResCount := ResCount + 1;
        src_find := src_find + '    lkLbl := '+Comp.ClassName+'(Result.FindComponent('''+SL[i]+''')); lkLbl.Caption := msg_'+AnsiLowerCase(SL[i])+' ;'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i]), 64)+'= '''+TLabel(Comp).Caption+'''; '+#13#10;
        end;
      if(AnsiUpperCase(Comp.ClassName) = 'TTABSHEET')then
        begin
        src_var  := src_var  + '// may be no need ? ';
        ResCount := ResCount + 1;
        src_find := src_find + '    lkTS := '+Comp.ClassName+'(Result.FindComponent('''+SL[i]+''')); lkTS.Caption := msg_'+AnsiLowerCase(SL[i])+' ;'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i]), 64)+'= '''+TTabSheet(Comp).Caption+'''; '+#13#10;
        end;
      if(AnsiUpperCase(Comp.ClassName) = 'TXCPAGECONTROL')then
        begin
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.StyleManager', MaxName+20)+' := Amunhotep.MainForm.StyleManager;'+#13#10;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Font.Style'  , MaxName+20)+' := [fsBold]; '+#13#10;
        end;
      if(AnsiUpperCase(Comp.ClassName) = 'TXCOUTLOOKHEADER')then
        begin
        ResCount := ResCount + 1;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Caption', MaxName+20)+' := msg_'+AnsiLowerCase(SL[i])+' ;'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i]), 64)+'= '''+TxcOutLookHeader(Comp).Caption+'''; '+#13#10;
        end;
      if(AnsiUpperCase(Comp.ClassName) = 'TXCWIZARDPANEL')then
        begin
        ResCount := ResCount + 1;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Captions.Text', MaxName+20)+' := msg_'+AnsiLowerCase(SL[i])+'_captions ;'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i])+'_captions', 64)+'= '''+TxcWizardPanel(Comp).Captions.Text+'''; '+#13#10;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Comments.Text', MaxName+20)+' := msg_'+AnsiLowerCase(SL[i])+'_comments ;'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i])+'_comments', 64)+'= '''+TxcWizardPanel(Comp).Comments.Text+'''; '+#13#10;
        end;
      if(AnsiUpperCase(Comp.ClassName) = 'TDBCHECKBOXEH')then
        begin
        ResCount := ResCount + 1;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Color'     ,MaxName+20)+' := Amunhotep.MainForm.StyleManager.Colors.Foreground;'+#13#10;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Font.Color',MaxName+20)+' := Amunhotep.MainForm.StyleManager.Colors.Border;'+#13#10;
        src_find := src_find + '    '+StrEndSpaces(SL[i]+'.Caption'   ,MaxName+20)+' := msg_'+AnsiLowerCase(SL[i])+' ;'+#13#10;
        res1     := res1 + '  '+StrEndSpaces('msg_'+AnsiLowerCase(SL[i]), 64)+'= '''+TDBCheckBoxEh(Comp).Caption+'''; '+#13#10;
        end;
      if((AnsiUpperCase(Comp.ClassName) = 'TCOMBOBOX')or(AnsiUpperCase(Comp.ClassName) = 'TLISTBOX')or(AnsiUpperCase(Comp.ClassName) = 'TCHECKLISTBOX')or
         (AnsiUpperCase(Comp.ClassName) = 'TEDIT')or(AnsiUpperCase(Comp.ClassName) = 'TMEMO')or(AnsiUpperCase(Comp.ClassName) = 'TRICHEDIT')or
         (AnsiUpperCase(Comp.ClassName) = 'TDBEDIT')or(AnsiUpperCase(Comp.ClassName) = 'TDBMEMO')or(AnsiUpperCase(Comp.ClassName) = 'TDBRICHEDIT')or
         (AnsiUpperCase(Comp.ClassName) = 'TXCEDIT')or(AnsiUpperCase(Comp.ClassName) = 'TSYNEDIT')or(AnsiUpperCase(Comp.ClassName) = 'TDBSYNEDIT')or
         (AnsiUpperCase(Comp.ClassName) = 'TXCEDITCOMBO')or(AnsiUpperCase(Comp.ClassName) = 'TXCEDITCURRENCY')or(AnsiUpperCase(Comp.ClassName) = 'TXCEDITCALC')or
         (AnsiUpperCase(Comp.ClassName) = 'TTREEVIEW')or(AnsiUpperCase(Comp.ClassName) = 'TXFBTREEVIEW')or
         (AnsiUpperCase(Comp.ClassName) = 'TDBGRIDEH')or
         (AnsiUpperCase(Comp.ClassName) = 'TDBEDITEH')or(AnsiUpperCase(Comp.ClassName) = 'TDBDATETIMEEDITEH')or
         (AnsiUpperCase(Comp.ClassName) = 'TDBNUMBEREDITEH')or(AnsiUpperCase(Comp.ClassName) = 'TDBCOMBOBOXEH')or
         (AnsiUpperCase(Comp.ClassName) = 'TDBLOOKUPCOMBOBOXEH')or
         (AnsiUpperCase(Comp.ClassName) = 'TDATETIMEPICKER')or(AnsiUpperCase(Comp.ClassName) = 'TDBCTRLGRID')
         )then
        begin
        src_find := src_find + 
          '    with '+Comp.Name+' do '+#13#10+
          '      begin '+#13#10+
          '      Color      := Amunhotep.MainForm.StyleManager.Colors.Window;'+#13#10+
          '      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Border;'+#13#10;
          
        if(AnsiUpperCase(Comp.ClassName) = 'TXCEDITCOMBO')then
          begin
          src_find := src_find + 
            '      AlwaysEnable := true;'+#13#10+
            '      ReadOnly     := true;'+#13#10+
            '      Tag          := 0;'+#13#10+
            '      Text         := '''';'+#13#10+
            '      OnButtonClick:= @'+Comp.Name+'_OnButtonClick;'+#13#10;
          procs    := procs + 
            '  //============================================================================'+#13#10+
            '  procedure '+Comp.Name+'_OnButtonClick(Sender :TObject);'+#13#10+
            '  begin'+#13#10+
            '  end;'+#13#10;
          end;
        if(AnsiUpperCase(Comp.ClassName) = 'TXFBTREEVIEW')then
          begin
          src_find := src_find + 
            '      Images                   := Amunhotep.MainForm.ImageListMain;'+#13#10+
            '      ShowItemId               := false;'+#13#10+
            '      DataBase                 := FBDataBase;'+#13#10+
            '      DBTreeInfo.FieldId       := ''ID'';'+#13#10+
            '      DBTreeInfo.FieldName     := ''NAME'';'+#13#10+
            '      DBTreeInfo.FieldParentId := ''PARENT_ID'';'+#13#10+
            '      DBTreeInfo.FieldStateId  := ''ID'';'+#13#10+
            '      DBTreeInfo.RootParentId  := ''0'';'+#13#10+
            '      DBTreeInfo.TableName     := ''TABL$R_'';'+#13#10+
            '      OnBuildNode              := @'+Comp.Name+'_OnBuildNode;'+#13#10+
            '      OnClick                  := @'+Comp.Name+'_OnClick;'+#13#10+
            '      OnDragDrop               := @'+Comp.Name+'_OnDragDrop;'+#13#10+
            '      OnDragDrop               := @'+Comp.Name+'_OnDragOver;'+#13#10;
          procs    := procs + 
            '  //============================================================================'+#13#10+
            '  procedure '+Comp.Name+'_OnBuildNode(Sender :TObject; StateFieldValue :Variant; var StateImage :Integer);'+#13#10+
            '  begin'+#13#10+
            '    //if(TComponent(Sender).Tag = 1)then'+#13#10+
            '    //  StateImage := 0'+#13#10+
            '    // else'+#13#10+
            '      StateImage := Integer(StateFieldValue);'+#13#10+
            '  end;'+#13#10+
            '  //============================================================================'+#13#10+
            '  procedure '+Comp.Name+'_OnClick(Sender :TObject);'+#13#10+
            '  begin'+#13#10+
            '  end;'+#13#10+
            '  //============================================================================'+#13#10+
            '  procedure '+Comp.Name+'_OnDragDrop(Sender, Source: TObject; X, Y: Integer);'+#13#10+
            '  var'+#13#10+ 
            '    i, j :Integer;'+#13#10+
            '    msg  :string;'+#13#10+
            '    Node :TTreeNode;'+#13#10+
            '  begin'+#13#10+
            '  {'+#13#10+
            '    if not tbRef.Active then exit;'+#13#10+
            '    if(Source = dbgRef)then'+#13#10+ 
            '      begin'+#13#10+
            '      Node := FBTreeView.GetNodeAt(X, Y);'+#13#10+
            '      msg := ''''; '+#13#10+
            '      if(Dialogs.MessageDlg(msg, mtConfirmation, [mbYes, mbNo]) = mrYes)then'+#13#10+
            '        begin  //GroupByField'+#13#10+
            '        msg := '''' '+#13#10+
            '        ExecSQL(FBDataBase, msg);'+#13#10+
            '        '+Comp.Name+'_OnClick('+Comp.Name+');'+#13#10+
            '        end;'+#13#10+
            '      end;'+#13#10+
            '   }'+#13#10+
            '   end;'+#13#10+
            '  //============================================================================'+#13#10+
            '  procedure '+Comp.Name+'_OnDragOver(Sender, Source: TObject; X, Y: Integer;State: TDragState; var Accept: Boolean);'+#13#10+
            '  begin  '+#13#10+
            '    Accept := true;'+#13#10+
            '  end;'+#13#10;
          end;
        if(AnsiUpperCase(Comp.ClassName) = 'TDBEDITEH')then
          begin
          src_find := src_find +
            '      with '+Comp.Name+'.EditButtons.Add do'+#13#10+ 
            '        begin'+#13#10+ 
            '        Visible := true;'+#13#10+ 
            '        Style   := ebsEllipsisEh;'+#13#10+ 
            '        OnClick := @'+Comp.Name+'_OnEditButtonClick;'+#13#10+ 
            '        end;'+#13#10; 
          procs    := procs + 
           '  //============================================================================'+#13#10+
           '  procedure '+Comp.Name+'_OnEditButtonClick(Sender :TObject; var Handled : Boolean);'+#13#10+
           '  var'+#13#10+
           '    lkVariableName :string;'+#13#10+
           '    lkBUFFER_ID    :string;'+#13#10+
           '    lkSQL          :string;'+#13#10+
           '  begin'+#13#10+
           '  {'+#13#10+
           '     lkVariableName := ''TABLE_ID'';'+#13#10+
           '     lkBUFFER_ID := DataSet.FieldByName(''FIRM_ID'').AsString;'+#13#10+
           '     SetGlobalVariable(lkVariableName, lkBUFFER_ID);'+#13#10+
           '     call(StrAbsolutePath(''../../REF/FIRMS/DEFAULT_DLG.PS'', ScriptName));'+#13#10+
           '     lkBUFFER_ID := GetGlobalVariable(lkVariableName);'+#13#10+
           '     if( (UpperCase(lkBUFFER_ID)<>''NULL'') and (StrTrimAll(lkBUFFER_ID)<>''0'') )then'+#13#10+
           '       begin'+#13#10+
           '       lkSQL := ''UPDATE TABL$R_ TB SET TB.FIRM_ID = ''''''+lkBUFFER_ID+'''''' WHERE(TB.ID = ''''''+DocId+'''''')'';'+#13#10+
           '       CloseDataSets;'+#13#10+
           '       ExecSQL(FBDataBase, lkSQL);'+#13#10+
           '       RefreshView;'+#13#10+
           '       Handled := true; '+#13#10+
           '       end;'+#13#10+
           '  }'+#13#10+
           '  end;'+#13#10;
          
          end;  
        if(AnsiUpperCase(Comp.ClassName) = 'TDBGRIDEH')then
          begin
          src_inc  := src_inc  + '{$IFNDEF PEAKTOP:OBJ/TCOLUMNEH.INC} {$I PEAKTOP:OBJ/TCOLUMNEH.INC} {$ENDIF}'+#13#10;
          src_inc  := src_inc  + '{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}{$I PEAKTOP:OBJ/TIMAGELIST.INC}{$ENDIF}'+#13#10;
          src_find := src_find + 
            '      FixedColor      := Amunhotep.MainForm.StyleManager.Colors.Foreground;'+#13#10+
            '      TitleFont.Color := Amunhotep.MainForm.StyleManager.Colors.Border;'+#13#10+
            '      TitleFont.Style := [fsBold];'+#13#10+
            '      UseMultiTitle   := true;'+#13#10+
            '      DrawMemoText    := true; '+#13#10+
            '      FrozenCols      := 0; '+#13#10+
            '      FooterRowCount  := 0; '+#13#10+
            '      SumList.Active  := false; '+#13#10+
            '      OnGetCellParams := @'+Comp.Name+'_OnGetCellParams;'+#13#10+
            '      OnTitleClick    := @'+Comp.Name+'_OnTitleClick;'+#13#10+
            '      Columns.Clear; '+#13#10+
            '      lkCol := CreateTColumnEh('+Comp.Name+',''FIELD_NAME'',''''                   ,'''', 60,taLeftJustify ); //lkCol.Tag := 666;'+#13#10+
            '      lkCol := CreateTColumnEh('+Comp.Name+',''FIELD_NAME'',''# ### ##0.00''       ,'''', 72,taRightJustify);'+#13#10+
            '      lkCol := CreateTColumnEh('+Comp.Name+',''FIELD_NAME'',''# ### ##0''          ,'''', 60,taRightJustify);'+#13#10+
            '      lkCol := CreateTColumnEh('+Comp.Name+',''FIELD_NAME'',''dd.mm.yyyy hh:nn:ss'','''', 72,taLeftJustify );'+#13#10+
            '      with lkCol do'+#13#10+
            '        begin'+#13#10+
            '        AlwaysShowEditButton := true;'+#13#10+
            '        ButtonStyle          := cbsDropDown;'+#13#10+
            '        AutoDropDown         := true;'+#13#10+
            '        ReadOnly             := false;'+#13#10+
            '        end;'+#13#10+
            '      with lkCol.Footer do '+#13#10+
            '        begin'+#13#10+
            '        Color         := lkCol.Color;'+#13#10+
            '        Alignment     := taRightJustify;'+#13#10+
            '        DisplayFormat := lkCol.DisplayFormat;'+#13#10+
            '        Value         := '''';'+#13#10+
            '        ValueType     := fvtSum;'+#13#10+
            '        end;'+#13#10;
          procs    := procs + 
           '  //============================================================================'+#13#10+
           '  procedure '+Comp.Name+'_OnGetCellParams(Sender: TObject; Column: TColumnEh; '+#13#10+
           '              AFont: TFont; var Background: TColor; State: TGridDrawState);'+#13#10+
           '  begin'+#13#10+
           '   if(Column.Tag=666)then exit;'+#13#10+
           '   if(not(Column.Field.DataSet.Active))then exit;'+#13#10+  
           '   if(not(Column.Field.DataSet.RecordCount > 0))then exit;'+#13#10+  
           '   //if    (Column.Field.DataSet.FieldByName(''FLAG_COMMIT'').AsInteger=0)then aFont.Style:= aFont.Style + [fsBold     ];'+#13#10+ 
           '   //Background := Column.Field.DataSet.FieldByName(''COLOR_BGR'').AsInteger;'+#13#10+
           '   //aFont.Color:= Column.Field.DataSet.FieldByName(''COLOR_FRG'').AsInteger;'+#13#10+
           '   if(Background=clWhite)then Background := Amunhotep_MainForm_StyleManager.Colors.Window;'+#13#10+ 
           '   if(aFont.Color=Background)then aFont.Color := Amunhotep_MainForm_StyleManager.Colors.Border;'+#13#10+ 
           '  end;'+#13#10;
          procs    := procs + 
           '  //============================================================================'+#13#10+
           '  procedure '+Comp.Name+'_OnTitleClick(Column :TColumnEh); '+#13#10+
           '  var '+#13#10+
           '    i     :Integer; '+#13#10+
           '    lkDBG :TCustomDBGridEh; '+#13#10+
           '  begin '+#13#10+
           '    lkDBG := TDBGridColumnsEh(Column.Collection).Grid;'+#13#10+
           '    for i:=0 to lkDBG.Columns.Count-1 do '+#13#10+
           '      lkDBG.Columns[i].Title.SortMarker := smNoneEh; '+#13#10+
           '    Column.Title.SortMarker := smDownEh; '+#13#10+
           '    //todo : RefreshView '+#13#10+
           '  end; '+#13#10;
          end;
        src_find := src_find + 
          '      end; '+#13#10;
        end;
      src_var  := src_var+#13#10;  
      end;
    SL.Free;
    src :=
      src_inc+
      '{-$IFNDEF LanguageResourceFileName}'+#13#10+ 
      '{-$I LanguageResourceFileName}'+#13#10+ 
      '{-$ENDIF}'+#13#10+ 
      'const'+#13#10+ 
      '  msg_invalid_resource  = ''Неверный файл ресурсов''; '+#13#10+ 
      res1+ 
      ' '+#13#10+ 
      'var '+#13#10+
      '  '+StrEndSpaces(F.Name, MaxName)+' :TAmunhotepForm; '+#13#10+    
      src_var+#13#10+#13#10+
      procs+#13#10+
      '  //============================================================================'+#13#10+
      '  procedure '+F.Name+'_OnClose(Sender :TObject; var Action :TCloseAction);'+#13#10+
      '  begin'+#13#10+
      '    Action := caFree;'+#13#10+
      src_find_free+
      '    AutoFree; '+#13#10+
      '  end; '+#13#10+
      '  //============================================================================'+#13#10+
      '  function '+F.Name+'_Create(        // create a new instance of the form'+#13#10+
      '             const aFileName:string; // - absolute path to resource xfm-file'+#13#10+
      '             const aCaption :string  // - caption of new form'+#13#10+
      '             ):TAmunhotepForm;'+#13#10+
      '  //function '+F.Name+'_Create:TAmunhotepForm;'+#13#10+
      '  var'+#13#10+
      '    lkFileName :string;'+#13#10+
      '    lkResBody  :string;'+#13#10+
      '    lkStrm     :TMemoryStream;'+#13#10+
      '    lkLbl      :TLabel;'+#13#10+
      '    lkAct      :TAction;'+#13#10+
      '    lkTS       :TTabSheet;'+#13#10+
      '    lkPM       :TPopupMenu;'+#13#10+
      '    lkMM       :TMainMenu;'+#13#10+
      '    lkCol      :TColumnEh;'+#13#10+
      '    i          :Integer;'+#13#10+
      '  begin'+#13#10+
      '    DontAutoFree;'+#13#10+
      '    lkFileName := {aFileName; }StrAbsolutePath(''./FILENAME.XFM'', ScriptName);'+#13#10+
      '    lkResBody  := StringsLoadFromFile(lkFileName);'+#13#10+
      '    if(lkResBody = '''')then '+#13#10+
      '      begin'+#13#10+
      '      Dialogs.MessageDlg(msg_invalid_resource+#13#10+lkFileName, mtWarning, [mbOK]);'+#13#10+
      '      exit;'+#13#10+
      '      end;'+#13#10+
      '    Result          := TAmunhotepForm(StrToComponent(lkResBody));'+#13#10+
      '    Result.OnClose  := @'+F.Name+'_OnClose;'+#13#10+
      '    //Result.FileName := lkFileName;'+#13#10+
      '    {try'+#13#10+
      '      lkStrm := TMemoryStream.Create;'+#13#10+
      '      if StreamLoadFromFile(StrAbsolutePath(''./DEFAULT_ICON.ICO'', ScriptName),lkStrm)then'+#13#10+
      '        Result.Icon.LoadFromStream(lkStrm);'+#13#10+
      '    finally'+#13#10+    
      '     lkStrm.Free;'+#13#10+
      '    end; }'+#13#10+  
      '    Result.SetCaption(msg_caption);'+#13#10+
      '    { '+#13#10+  
      '    TopBar := TxcGradientPanelVista(Result.FindComponent(''TopBar'')); '+#13#10+
      '    with TopBar do '+#13#10+
      '      begin '+#13#10+
      '      Caption    := #$20#$20#$20#$20#$20#$20+msg_caption; '+#13#10+
      '      Font.Color := Amunhotep.MainForm.StyleManager.Colors.Window; '+#13#10+
      '      Font.Name  := ''Verdana''; '+#13#10+
      '      Font.Size  := 14; '+#13#10+
      '      Font.Style := [fsBold]; '+#13#10+
      '      end; '+#13#10+
      '    ImgLogo := TImage(Result.FindComponent(''ImgLogo'')); '+#13#10+
      '    try '+#13#10+
      '      lkStrm  := TMemoryStream.Create; '+#13#10+
      '      if StreamLoadFromFile(StrAbsolutePath(''./DEFAULT_BITMAP.BMP'', ScriptName), lkStrm)then '+#13#10+
      '        ImgLogo.Picture.Bitmap.LoadFromStream(lkStrm); '+#13#10+
      '    finally '+#13#10+    
      '      lkStrm.Free; '+#13#10+
      '    end; '+#13#10+  
      '    } '+#13#10+  
      src_find+#13#10+
      '    Amunhotep.MainForm.TaskBar.ButtonByForm(Result).Down := true;'+#13#10+
      '  end;'+#13#10+
      '  //============================================================================'+#13#10+
      'begin'+#13#10+
      '  '+F.Name+' := '+F.Name+'_Create; //(StrAbsolutePath(''./FILENAME.XFM'', ScriptName), '''+F.Caption+''');'+#13#10+
      'end.';
    Result := src;
  end;
  //============================================================================
  procedure actPopupMenuDesigner_FormToPascal_OnExecute(Sender :TObject);
  var
    lk_Memo :TMemo;
  begin
    lk_Memo            := TMemo.Create(nil);
    lk_Memo.Visible    := false;
    lk_Memo.Parent     := Amunhotep_MainForm;
    lk_Memo.Lines.Text := AmunhotepFormToPascal(TAmunhotepForm(Amunhotep_MainForm.ActiveMDIChild));
    lk_Memo.SelectAll;
    lk_Memo.CopyToClipboard;
    lk_Memo.Free;
    {$IFDEF LANGUAGE_UKR}Dialogs.MessageDlg('Скрипта скопiйовано до буфера обмiну',mtInformation,[mbOk]);{$ENDIF}
    {$IFDEF LANGUAGE_RUS}Dialogs.MessageDlg('Скрипт скопирован в буфер обмена'    ,mtInformation,[mbOk]);{$ENDIF}
    {$IFDEF LANGUAGE_ENG}Dialogs.MessageDlg('Script was copied to clipborad'      ,mtInformation,[mbOk]);{$ENDIF}
    {$IFDEF LANGUAGE_DEU}Dialogs.MessageDlg('Script was copied to clipborad'      ,mtInformation,[mbOk]);{$ENDIF}
  end;
  //============================================================================
  procedure actPopupMenuDesigner_FormToPascal_OnUpdate(Sender :TObject);
  var
    Res :Boolean;
  begin
    Res := (Amunhotep_MainForm.MDIChildCount>0);
    if(Res)then Res := (AnsiUpperCase(Amunhotep.MainForm.ActiveMDIChild.ClassName)='TAMUNHOTEPFORM');
    if(Res)then Res := not TAmunhotepForm(Amunhotep.MainForm.ActiveMDIChild).IsReport;
    TCustomAction(Sender).Enabled := Res;
  end;
  //============================================================================ 
const
  msg_actpopupmenudesigner_formtopascal_caption = 'Сгенерировать скрипт';
  msg_actpopupmenudesigner_formtopascal_hint    = 'Сгенерировать автоматический скрипт';   
