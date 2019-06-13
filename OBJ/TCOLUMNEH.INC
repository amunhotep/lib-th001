{$DEFINE PEAKTOP:OBJ/TCOLUMNEH.INC}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}{$I PEAKTOP:OBJ/TIMAGELIST.INC}{$ENDIF}
  //====================== PEAKTOP:OBJ/TCOLUMNEH.INC ===========================
  function IntToTAlignment(const aValue :Integer):TAlignment;
  begin
    case aValue of
      0   :Result := taLeftJustify;
      1   :Result := taRightJustify;
      2   :Result := taCenter;
      else Result := taLeftJustify;
    end;
  end;
  //============================================================================
  function IntToTTextOrientationEh(const aValue :Integer):TTextOrientationEh;
  begin
    if(aValue = 1)then
      Result := tohVertical
     else
      Result := tohHorizontal;
  end;
  //============================================================================
  function StrToTFooterValueType(const aStr:string):TFooterValueType;
  begin
    Result := fvtNon;
         if(UpperCase(aStr) = 'SUM'   )then Result := fvtSum
    else if(UpperCase(aStr) = 'AVG'   )then Result := fvtAvg 
    else if(UpperCase(aStr) = 'COUNT' )then Result := fvtCount 
    else if(UpperCase(aStr) = 'VALUE' )then Result := fvtFieldValue 
    else if(UpperCase(aStr) = 'STATIC')then Result := fvtStaticText; 
  end;
  //============================================================================
  function CreateTColumnEh2(aDBGrid:TDBGridEh; const aFieldName, aDisplayFormat, aTitleCaption, aHint:string;
             const aWidth, aColumnIndex, aAlignment, aColor:Integer; 
             const aKeyList, aPickList:string; aImageIndicies:array of Integer):TColumnEh;
  var
    j           :Integer;
    lkExistsFlag:Boolean;
  begin  
    lkExistsFlag := false;
    for j:=0 to aDBGrid.Columns.Count-1 do
      if(UpperCase(aDBGrid.Columns[j].FieldName) = UpperCase(aFieldName))then
        begin
        Result       := aDBGrid.Columns[j];
        lkExistsFlag := true;
        break;
        end;
    if not lkExistsFlag then
      Result := aDBGrid.Columns.Add;
    with Result do
      begin  
      FieldName      := aFieldName;
      ToolTips       := true;
      DisplayFormat  := aDisplayFormat;
      Alignment      := IntToTAlignment(aAlignment);
      Width          := aWidth;
      if(aColor <> clWindow)then
        Color        := aColor;
      Index          := MinInteger(aColumnIndex, aDBGrid.Columns.Count-1);
      with Title do
        begin
        Caption      := aTitleCaption;
        Hint         := StrReplaceStr(aTitleCaption, '|', #13#10#13#10);
        TitleButton  := true;
        ToolTips     := true;
        if(StrTrimAll(aHint) <> '')then
          Hint       := aHint;
        end;
      if(StrTrimAll(aKeyList) <> '')then
        begin
        KeyList.Text := aKeyList;
        PickList.Text:= aPickList;
        if(Length(aImageIndicies) > 0)then
          ImageList := CreateTImageList(aDBGrid, '', aImageIndicies)
         else 
          if( (aKeyList='0'#13#10'1') or (aKeyList='1'#13#10'0') or (aKeyList='0'#13'1') or (aKeyList='1'#13'0') )then
            CheckBoxes := true;
        AlwaysShowEditButton := not Checkboxes;
        end
      AutoDropDown := true; 
      end;   
  end;
  //============================================================================
  function CreateTColumnEh(aDBGrid :TDBGridEh; const aFieldName, aDisplayFormat, aTitleCaption:string;const aWidth:Integer; aAlignment:TAlignment):TColumnEh;
  begin
    Result := CreateTColumnEh2(aDBGrid,aFieldName,aDisplayFormat,aTitleCaption,'',aWidth,255,Integer(aAlignment),clWindow,'','',[]); 
  end;
  //============================================================================
  function CloneTColumnEh(aColumnEhSrc :TColumnEh; aDBGridEhDest :TDBGridEh):TColumnEh;
  begin
    Result := CreateTColumnEh2(aDBGridEhDest, aColumnEhSrc.FieldName, aColumnEhSrc.DisplayFormat, aColumnEhSrc.Title.Caption, aColumnEhSrc.Title.Hint, 
      aColumnEhSrc.Width, aColumnEhSrc.Index, Integer(aColumnEhSrc.Alignment), aColumnEhSrc.Color, aColumnEhSrc.KeyList.Text, aColumnEhSrc.PickList.Text, []);
    with Result do
      begin  
      ColParams.Text       := aColumnEhSrc.ColParams.Text;
      Title.Orientation    := aColumnEhSrc.Title.Orientation;
      Title.TitleButton    := true;
      ImageList            := aColumnEhSrc.ImageList;
      AlwaysShowEditButton := aColumnEhSrc.Checkboxes;
      AutoDropDown         := aColumnEhSrc.AutoDropDown; 
      ColParams.Text       := aColumnEhSrc.ColParams.Text;
      end;
  end;   
