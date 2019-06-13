{$DEFINE PEAKTOP:IDE/ERP/DBO/OPER/FILESYSTEM.INC}
{$IFNDEF PEAKTOP:OBJ/TACTION.INC}                      {$I PEAKTOP:OBJ/TACTION.INC}                      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGE.INC}                       {$I PEAKTOP:OBJ/TIMAGE.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TIMAGELIST.INC}                   {$I PEAKTOP:OBJ/TIMAGELIST.INC}                   {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TMENUITEM.INC}                    {$I PEAKTOP:OBJ/TMENUITEM.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TSPLITTER.INC}                    {$I PEAKTOP:OBJ/TSPLITTER.INC}                    {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCPANEL.INC}                     {$I PEAKTOP:OBJ/TXCPANEL.INC}                     {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}             {$I PEAKTOP:OBJ/TXCGRADIENTPANEL.INC}             {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}        {$I PEAKTOP:OBJ/TXCGRADIENTPANELVISTA.INC}        {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/FILES/SEARCH_UTILS.INC}      {$I PEAKTOP:SYSUTILS/FILES/SEARCH_UTILS.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTICON.INC} {$I PEAKTOP:SYSUTILS/FILES/LOADIMAGELISTICON.INC} {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/SHORTCUTS.INC}            {$I ../SHORTCUTS.INC}                             {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_NAMES.INC}{$I ../$COMMON/FORMERP_NAMES.INC}                 {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_LANG.INC} {$I ../$COMMON/FORMERP_LANG.INC}                  {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP.INC}      {$I ../$COMMON/FORMERP.INC}                       {$ENDIF}
{$IFNDEF PEAKTOP:IDE/ERP/DBO/OPER/FILESYSTEM_LANG.INC} {$I ./FILESYSTEM_LANG.INC}                        {$ENDIF}
const //==================== PEAKTOP:IDE/ERP/DBO/OPER/FILESYSTEM.INC ===========
  TERPFormOperFileSystem_IconSearchPath = '../conf/icons'; // путь относительно ядра amunhotep.exe
  //============================================================================
  function TERPFormOperFileSystem_ExtList(aOwner:TComponent):TStringList;
  begin
    with TxsStringsHolder(aOwner.FindComponent(obj_name_erp_data_settings)) do
      begin
      while(Items.Count < 3)do
        Items.Add;
      Result := TStringList(Items[2].Strings);
      end;
  end;
  //============================================================================
  function TERPFormOperFileSystem_BufferList(aOwner:TComponent):TStringList;
  begin
    with TxsStringsHolder(aOwner.FindComponent(obj_name_erp_data_settings)) do
      begin
      while(Items.Count < 4)do
        Items.Add;
      Result := TStringList(Items[3].Strings);
      end;
  end;
  //============================================================================
  function TERPFormOperFileSystem_GetImageIndex(aOwner :TComponent; const aExt:string):Integer;
  begin
    if(aExt='..')then  
      begin
      Result := 0;
      exit;
      end;
    if(aExt='~..' )then  
      begin
      Result := 1;
      exit;
      end;
    Result := TERPFormOperFileSystem_ExtList(aOwner).IndexOf( PrepareAbsoleteFileName(StrAbsolutePath(TERPFormOperFileSystem_IconSearchPath+'/'+LowerCase(aExt)+'.ico', Amunhotep.ExeName)) );
    Result := Result + 3;
  end;
  //============================================================================
  function TERPFormOperFileSystem_DefaultFileExt(const aFT:TFileType):string;
  begin
    case aFT of
      ftText  :Result := 'TXT';
      ftPas   :Result := 'PS';
      ftDfm   :Result := 'XFM'; 
      ftSQL   :Result := 'SQL'; 
      ftJava  :Result := 'JAVA';
      ftJS    :Result := 'JS';
      ftPerl  :Result := 'CONF';
      ftBat   :Result := 'BAT';
      ftHTML  :Result := 'HTML';
      ftCss   :Result := 'CSS';
      ftXML   :Result := 'XML';
      ftVB    :Result := 'VB';
      ftPython:Result := 'PY';
      ftC     :Result := 'C';
      ftPHP   :Result := 'PHP';
      ftAsm   :Result := 'ASM';
      ftRC    :Result := 'RC';
      ftRuby  :Result := 'RUBY';
      ftInno  :Result := 'ISS';
    end;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_LoadImageListFS(a_Owner :TComponent);
  var
    lkImgListFSBig   :TImageList;
    lkImgListFSSmall :TImageList;
    lkFileList       :TStringList;
  begin
    lkImgListFSBig   := CreateTImageListSimple(a_Owner,obj_name_erp_imagelistfs_big  ,32,32);
    lkImgListFSSmall := CreateTImageListSimple(a_Owner,obj_name_erp_imagelistfs_small,16,16);
    Files_LoadIconToImageList(lkImgListFSBig  ,PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/MIME/FOLDER.ICO' ) );
    Files_LoadIconToImageList(lkImgListFSSmall,PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/MIME/FOLDER.ICO' ) );
    Files_LoadIconToImageList(lkImgListFSBig  ,PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/MIME/FOLDERGREEN.ICO' ) );
    Files_LoadIconToImageList(lkImgListFSSmall,PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/MIME/FOLDERGREEN.ICO' ) );
    Files_LoadIconToImageList(lkImgListFSBig  ,PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/MIME/UNKNOWN.ICO') );
    Files_LoadIconToImageList(lkImgListFSSmall,PrepareAbsoleteFileName('PEAKTOP:IMG/CONFIG/MIME/UNKNOWN.ICO') );
    lkFileList := Files_FindFiles(ExtractFilePath(PrepareAbsoleteFileName(StrAbsolutePath(TERPFormOperFileSystem_IconSearchPath+'/DUMMY.TXT', Amunhotep.ExeName))), '*.ICO', false);
    TERPFormOperFileSystem_ExtList(a_Owner).Text := lkFileList.Text;
    Files_LoadIconsToImageList(lkImgListFSBig  , lkFileList, false, false);
    Files_LoadIconsToImageList(lkImgListFSSmall, lkFileList, false, false);
    lkFileList.Free;
  end;
  //============================================================================
  function TERPFormOperFileSystem_GetItemPath(const aFS_ID :string):string;
  var
    lkStr :string;
  begin
    Result := '/';
    if(aFS_ID = '')then exit;
    if GetField(FBDataBase, 'PROC$_FS_PATH('''+aFS_ID+''', '''')', 'PATH', '', lkStr)then
      Result := lkStr;
  end;
  //============================================================================
  function TERPFormOperFileSystem_GetSQL(const aPARENT_FS_ID:string):string;
  var
    lkRootScript :string;
    lkAddScript  :string;
    lkParentId   :Integer;
    i            :Integer; 
  begin
    lkParentId   := StrToInt(aPARENT_FS_ID);
    lkRootScript := '';
    lkAddScript  := '';
    if(aPARENT_FS_ID = '0')then
      begin
      {
      for i:=ERP_OBJECTTYPE_ATTRS to ERP_OBJECTTYPE_MENUS do
        lkAddScript := lkAddScript +
          '    UNION ALL '+SQLCRLF+
          '    SELECT FIRST 1 ''~'+ERP_ObjectCaptions(i-ERP_OBJECTTYPES_OFFSET)+''' AS NAME, ''~..'' AS EXT, NULL AS DATE_INS, NULL AS DATE_UPD, 0 AS PARENT_ID, '+IntToStr(i)+' AS ID FROM RDB$DATABASE '+SQLCRLF;
      }
      lkAddScript := lkAddScript +
        '    UNION ALL '+SQLCRLF+
        '    SELECT FIRST 1 ''~'+msg_erp_dbfs_connections+''' AS NAME, ''~..'' AS EXT, NULL AS DATE_INS, NULL AS DATE_UPD, 0 AS PARENT_ID, '+IntToStr(ERP_OBJECTTYPES_COUNT+1)+' AS ID FROM RDB$DATABASE '+SQLCRLF;
      end  
     else
      begin
      if(lkParentId > $FF)then 
        lkRootScript := 
          '    SELECT   FS0.NAME, FS0.EXT, NULL AS DATE_INS, NULL AS DATE_UPD '+SQLCRLF+
          '            ,(SELECT FIRST 1 FS01.PARENT_ID FROM TABL$_FS FS01 WHERE (FS01.ID = '''+aPARENT_FS_ID+''')) AS PARENT_ID '+SQLCRLF+
          '            ,'+aPARENT_FS_ID+' AS ID '+SQLCRLF+
          '    FROM     TABL$_FS FS0 '+SQLCRLF+
          '    WHERE (FS0.PARENT_ID=''-1'') '+SQLCRLF+
          '    GROUP BY FS0.NAME, FS0.EXT, DATE_INS, DATE_UPD, FS0.PARENT_ID, FS0.ID '+SQLCRLF+
          '    UNION ALL '+SQLCRLF
       else
        begin  
        lkRootScript := 
          '    SELECT   FS0.NAME, FS0.EXT, NULL AS DATE_INS, NULL AS DATE_UPD, 0 AS PARENT_ID, '+aPARENT_FS_ID+' AS ID '+SQLCRLF+
          '    FROM     TABL$_FS FS0 '+SQLCRLF+
          '    WHERE (FS0.PARENT_ID=''-1'') '+SQLCRLF+
          '    GROUP BY FS0.NAME, FS0.EXT, DATE_INS, DATE_UPD, PARENT_ID, ID '+SQLCRLF+
          '    UNION ALL '+SQLCRLF;
        case lkParentId of
          ERP_OBJECTTYPES_COUNT+1: lkAddScript := lkAddScript + '    UNION ALL '+SQLCRLF+
            '    SELECT (M.MON$ATTACHMENT_ID||'' ''||M.MON$SERVER_PID||''  ''||TRIM(M.MON$REMOTE_PROTOCOL)||'' ''||'+
            '      TRIM(M.MON$REMOTE_ADDRESS)||'' ''||TRIM(M.MON$ATTACHMENT_NAME)||'' ''||TRIM(M.MON$USER)||'' ''||'+
            '      TRIM(M.MON$ROLE)||'' ''||TRIM(M.MON$REMOTE_PROCESS)) AS NAME '+SQLCRLF+
            '          ,''~'+FormatFloat('000',ERP_OBJECTTYPES_COUNT+1)+''' AS EXT '+SQLCRLF+
            '          ,M.MON$TIMESTAMP AS DATE_INS, M.MON$TIMESTAMP AS DATE_UPD, 0 AS PARENT_ID, M.MON$ATTACHMENT_ID AS ID '+SQLCRLF+
            '    FROM   MON$ATTACHMENTS M '+SQLCRLF+
            '    GROUP BY NAME, EXT, DATE_INS, DATE_UPD, PARENT_ID, ID'+SQLCRLF;
          end;  
        end;  
      end;  
    Result := 
      'EXECUTE BLOCK RETURNS( '+SQLCRLF+
      '  ID        TYPE OF COLUMN TABL$_FS.ID '+SQLCRLF+
      ' ,PARENT_ID TYPE OF COLUMN TABL$_FS.PARENT_ID '+SQLCRLF+
      ' ,NAME      TYPE OF COLUMN TABL$_FS.NAME '+SQLCRLF+
      ' ,HINT      TYPE OF COLUMN TABL$_FS.NAME '+SQLCRLF+
      ' ,EXT       TYPE OF COLUMN TABL$_FS.EXT '+SQLCRLF+
      ' ,DATE_INS  TYPE OF COLUMN TABL$_FS.DATE_INS '+SQLCRLF+
      ' ,DATE_UPD  TYPE OF COLUMN TABL$_FS.DATE_UPD '+SQLCRLF+
      ' ,PATH      DOMN$PSTRING_8192 '+SQLCRLF+
      ')AS '+SQLCRLF+
      'BEGIN '+SQLCRLF+
      '  FOR '+SQLCRLF+
      lkRootScript+
      '    SELECT   FS1.NAME, FS1.EXT, FS1.DATE_INS, FS1.DATE_UPD, FS1.PARENT_ID, FS1.ID '+SQLCRLF+
      '    FROM     TABL$_FS FS1 '+SQLCRLF+ 
      '    WHERE   ((FS1.EXT=''..'')AND(FS1.PARENT_ID='''+aPARENT_FS_ID+''')) '+SQLCRLF+
      '    GROUP BY FS1.NAME, FS1.EXT, FS1.DATE_INS, FS1.DATE_UPD, FS1.PARENT_ID, FS1.ID '+SQLCRLF+ 
      '    UNION ALL '+SQLCRLF+
      '    SELECT   FS2.NAME, FS2.EXT, FS2.DATE_INS, FS2.DATE_UPD, FS2.PARENT_ID, FS2.ID '+SQLCRLF+
      '    FROM     TABL$_FS FS2 '+SQLCRLF+ 
      '    WHERE   ((FS2.EXT<>''..'')AND(FS2.PARENT_ID='''+aPARENT_FS_ID+''')) '+SQLCRLF+
      '    GROUP BY FS2.NAME, FS2.EXT, FS2.DATE_INS, FS2.DATE_UPD, FS2.PARENT_ID, FS2.ID '+SQLCRLF+ 
      lkAddScript+
      '    INTO  :NAME, :EXT, :DATE_INS, :DATE_UPD, :PARENT_ID, :ID '+SQLCRLF+
      '  DO '+SQLCRLF+
      '    BEGIN '+SQLCRLF+
      '    HINT = ''''; '+SQLCRLF+
      '    IF(:ID > 255)THEN '+SQLCRLF+
      '      BEGIN '+SQLCRLF+
      '      HINT = :NAME; '+SQLCRLF+
      '      IF(:NAME SIMILAR TO ''[[:DIGIT:]]{1,}'') THEN '+SQLCRLF+
      '        BEGIN '+SQLCRLF+
      '        SELECT FIRST 1 T.NAME FROM TABL$_TB_TYPES T WHERE (T.ID = :NAME)INTO :HINT; '+SQLCRLF+
      '        END '+SQLCRLF+
      '       ELSE '+SQLCRLF+
      '        BEGIN '+SQLCRLF+
      '             IF(EXISTS(SELECT T1.ID FROM TABL$_TB T1 WHERE(T1.ID = ''{''||:NAME||''}'')))THEN SELECT FIRST 1 T2.NAME FROM TABL$_TB T2 WHERE(T2.ID = ''{''||:NAME||''}'')INTO :HINT; '+SQLCRLF+
      '        ELSE IF(EXISTS(SELECT T1.ID FROM TABL$_TB T1 WHERE(T1.ID = ''TABL$R_''||:NAME )))THEN SELECT FIRST 1 T2.NAME FROM TABL$_TB T2 WHERE(T2.ID = ''TABL$R_''||:NAME )INTO :HINT; '+SQLCRLF+
      '        ELSE IF(EXISTS(SELECT T1.ID FROM TABL$_TB T1 WHERE(T1.ID = ''TABL$P_''||:NAME )))THEN SELECT FIRST 1 T2.NAME FROM TABL$_TB T2 WHERE(T2.ID = ''TABL$P_''||:NAME )INTO :HINT; '+SQLCRLF+
      '        ELSE IF(EXISTS(SELECT T1.ID FROM TABL$_TB T1 WHERE(T1.ID = ''TABL$''||:NAME   )))THEN SELECT FIRST 1 T2.NAME FROM TABL$_TB T2 WHERE(T2.ID = ''TABL$''||:NAME   )INTO :HINT; '+SQLCRLF+
      '        END '+SQLCRLF+
      '      END '+SQLCRLF+
      '    SUSPEND; '+SQLCRLF+
      '    END '+SQLCRLF+
      'END';
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_RefreshView(aOwner:TComponent);
  var
    lkListView :TListView;
    lkLI       :TListItem;
    lkTr       :TxFBTransaction;
    lkQr       :TxFBQuery;
  begin
    lkListView := TListView(aOwner.FindComponent(obj_name_erp_listview));
    if(lkListView = nil)then exit;
    lkListView.Items.Clear;

    lkTr := TxFBTransaction.Create(nil);
    with lkTr do
      begin
      DefaultDataBase := FBDataBase;
      Params.Clear;
      Params.Add('isc_tpb_read_committed');
      Params.Add('isc_tpb_read');
      Params.Add('isc_tpb_rec_version');
      Params.Add('isc_tpb_nowait');
      end;
    lkQr := TxFBQuery.Create(lkTr);
    with lkQr do
      begin
      DataBase    := lkTr.DefaultDataBase;
      Transaction := lkTr;
      SQL.Text    := TERPFormOperFileSystem_GetSQL(lkListView.HelpKeyWord);
      end;
    lkTr.StartTransaction;
    try
      lkQr.Open;
    except
      if lkTr.InTransaction then
        lkTr.Commit;
      lkTr.Free;
      exit;
    end;
    lkListView.Items.BeginUpdate;
    lkQr.First;
    while not lkQr.EOF do
      begin
      lkLI := lkListView.Items.Add;
      lkLI.ImageIndex := TERPFormOperFileSystem_GetImageIndex(aOwner, StrTrimAll(lkQr.FieldByName('EXT').AsString));
      if( (StrTrimAll(lkQr.FieldByName('EXT').AsString) = '..') or (StrTrimAll(lkQr.FieldByName('EXT').AsString) = '~..') )then
        begin
        lkLI.Caption := lkQr.FieldByName('NAME').AsString;
        end
       else
        begin
        lkLI.Caption := lkQr.FieldByName('NAME').AsString + '.' + lkQr.FieldByName('EXT').AsString;
        end; 
      lkLI.SubItems.Clear;
      lkLI.SubItems.Add(lkQr.FieldByName('HINT').AsString);
      lkLI.SubItems.Add('');//1  
      lkLI.SubItems.Add('');//2
      if(StrTrimAll(lkQr.FieldByName('NAME').AsString) <> '..')then
        begin
        if not(lkQr.FieldByName('DATE_INS').IsNull)then lkLI.SubItems[1] := FormatDateTime('dd.mm.yyyy hh:nn:ss',lkQr.FieldByName('DATE_INS').AsDateTime);  
        if not(lkQr.FieldByName('DATE_UPD').IsNull)then lkLI.SubItems[2] := FormatDateTime('dd.mm.yyyy hh:nn:ss',lkQr.FieldByName('DATE_UPD').AsDateTime);
        end;
      lkLI.SubItems.Add(lkQr.FieldByName('EXT').AsString);        //3
      lkLI.SubItems.Add(lkQr.FieldByName('NAME').AsString);       //4
      lkLI.SubItems.Add(lkQr.FieldByName('PARENT_ID').AsString);  //5
      lkLI.SubItems.Add(lkQr.FieldByName('ID').AsString);         //6
      lkQr.Next;
      end;
    lkListView.Items.EndUpdate;
    if(lkListView.Items.Count > 0)then
      lkListView.Items[0].Selected := true;
    if lkTr.InTransaction then
      lkTr.Commit;
    lkTr.Free;
  end;
  //============================================================================
  function TERPFormOperFileSystem_ListView_SelectedFiles(aOwner :TComponent):string;
  var
    i :Integer;
  begin
    Result := '';
    with TListView(aOwner.FindComponent(obj_name_erp_listview))do
      begin
      for i:=0 to Items.Count-1 do
        if( (Items[i].Caption<>'..') and Items[i].Selected)then
          Result := Result + '    "'+Items[i].Caption+'"'+#13#10;
      end;
  end;
  //============================================================================
  function TERPFormOperFileSystem_ListView_SelectedIds(aOwner :TComponent):string;
  var
    i :Integer;
  begin
    Result := '~';
    with TListView(aOwner.FindComponent(obj_name_erp_listview))do
      for i:=0 to Items.Count-1 do
        if( (Items[i].Caption<>'..') and Items[i].Selected)then
          Result := Result + Items[i].SubItems[6]+'~';
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_ListView_OnClick(Sender :TObject);
  begin

  end;
  //============================================================================
  procedure TERPFormOperFileSystem_ListView_OnDblClick(Sender :TObject);
  begin
    with TListView(Sender) do
      begin
      if(Selected <> nil)then
        begin
        if( (Selected.SubItems[3] = '..') or (Selected.SubItems[3] = '~..') )then
          begin
          if(Selected.Caption = '..')then
            HelpKeyWord := Selected.SubItems[5]
           else 
            HelpKeyWord := Selected.SubItems[6];
          TERPFormOperFileSystem_RefreshView(Owner);
          if( (Items.Count > 0) and (StrToInt(Selected.SubItems[6]) > 255) )then
            TxFBTreeView(Owner.FindComponent(obj_name_erp_treeview)).BuildNodeById(Selected.SubItems[6]);
          end
         else
          begin
          Amunhotep.MainForm.ProcessFile('DB:'+TERPFormOperFileSystem_GetItemPath(Selected.SubItems[6]) );
          end; 
        end
      end;  
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_ListView_OnKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  begin
    if(Key = $0D)then TERPFormOperFileSystem_ListView_OnDblClick(Sender);// VK_RETURN
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_TreeView_OnBuildNode(Sender :TObject; StateFieldValue :Variant; var StateImage :Integer);
  begin
    StateImage := 0;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_TreeView_OnClick(Sender :TObject);
  begin
    TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).HelpKeyWord := TxFBTreeView(Sender).GetId;
    TERPFormOperFileSystem_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actFileNewFile_OnExecute(Sender :TObject);
  var
    lkFileName      :string;
    lkFileExt       :string;
    lkParentFolderId:string;
    lkLI            :TListItem;
  begin
    if not(Dialogs.InputQueryString(msg_erp_actfilenewfile_hint+'  '+lkFileExt, msg_erp_dbfs_enternewfilename, lkFileName))then exit;
    if(StrTrimAll(lkFileName) = '')then exit;
    if not(Dialogs.InputQueryString(msg_erp_actfilenewfile_hint+'  '+lkFileExt, msg_erp_dbfs_enternewfileext, lkFileExt))then exit;
    if(StrTrimAll(lkFileExt) = '')then exit;
    lkFileName := UpperCase(StrReplaceStr(lkFileName,'''', ''''''));
    lkFileExt  := Copy(UpperCase(StrReplaceStr(lkFileExt ,'''', '''''')), 1, 5);
    lkLI := TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).Selected;
    if(lkLI = nil)then exit;
    if(lkLI.Caption = '..')then
      lkParentFolderId := lkLI.SubItems[6]
     else
      lkParentFolderId := lkLI.SubItems[5];
    if(lkParentFolderId = '')then 
      lkParentFolderId := '0';
    ExecSQL(FBDataBase, 'INSERT INTO TABL$_FS(PARENT_ID, NAME, EXT) VALUES ('+lkParentFolderId+', '''+lkFileName+''', '''+lkFileExt+''')');
    TERPFormOperFileSystem_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actFileNewFileExt_OnExecute(Sender :TObject);
  var
    lkFileName      :string;
    lkFileExt       :string;
    lkParentFolderId:string;
    lkLI            :TListItem;
    lkFT            :TFileType;
  begin
    lkFileExt := TERPFormOperFileSystem_DefaultFileExt(ftText);
    for lkFT:=ftText to ftInno do
      if(TComponent(Sender).Tag = Integer(lkFT))then
        begin 
        lkFileExt := TERPFormOperFileSystem_DefaultFileExt(lkFT);
        break;
        end;
    if not(Dialogs.InputQueryString(msg_erp_actfilenewfile_hint+'  '+lkFileExt, msg_erp_dbfs_enternewfilename, lkFileName))then exit;
    if(StrTrimAll(lkFileName) = '')then exit;
    lkFileName := UpperCase(StrReplaceStr(lkFileName,'''', ''''''));
    lkLI := TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).Selected;
    if(lkLI = nil)then exit;
    if(lkLI.Caption = '..')then
      lkParentFolderId := lkLI.SubItems[6]
     else
      lkParentFolderId := lkLI.SubItems[5];
    if(lkParentFolderId = '')then 
      lkParentFolderId := '0';
    ExecSQL(FBDataBase, 'INSERT INTO TABL$_FS(PARENT_ID, NAME, EXT) VALUES ('+lkParentFolderId+', '''+lkFileName+''', '''+lkFileExt+''')');
    TERPFormOperFileSystem_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actFileNewFolder_OnExecute(Sender :TObject);
  var
    lkFolderName    :string;
    lkParentFolderId:string;
    lkLI            :TListItem;
  begin
    if not(Dialogs.InputQueryString(msg_erp_actfilenewfolder_hint, msg_erp_dbfs_enternewfoldername, lkFolderName))then exit;
    if(StrTrimAll(lkFolderName) = '')then exit;
    lkFolderName := UpperCase(StrReplaceStr(lkFolderName,'''', ''''''));
    lkLI := TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).Selected;
    if(lkLI = nil)then exit;
    if(lkLI.Caption = '..')then
      lkParentFolderId := lkLI.SubItems[6]
     else
      lkParentFolderId := lkLI.SubItems[5];
    if(lkParentFolderId = '')then 
      lkParentFolderId := '0';
    ExecSQL(FBDataBase, 'INSERT INTO TABL$_FS(PARENT_ID, NAME, EXT) VALUES ('+lkParentFolderId+', '''+lkFolderName+''', ''..'')');
    TERPFormOperFileSystem_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actFileNewObjRpti_OnExecute(Sender :TObject);
  begin
    call(PrepareAbsoleteFileName('PEAKTOP:IDE/ERP/DBO/RPTI/WIZARD.PS'));
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actFileRename_OnExecute(Sender :TObject);
  var
    lkFileName:string;
  begin
    with TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)) do
      begin
      if(Selected.Caption     = '..' )then exit;
      if(Selected.SubItems[3] = '~..')then exit;
      lkFileName := Selected.SubItems[4];
      if not(Dialogs.InputQueryString(msg_erp_actfilerename_hint, msg_erp_dbfs_enternewfilename, lkFileName))then exit;
      if(StrTrimAll(lkFileName) = '')then exit;
      if(Selected.SubItems[3] <> '..')then
        Selected.Caption := UpperCase(lkFileName) + '.' + Selected.SubItems[3]
       else
        Selected.Caption := UpperCase(lkFileName); 
      lkFileName := UpperCase(StrReplaceStr(lkFileName,'''', ''''''));
      ExecSQL(FBDataBase, 'UPDATE TABL$_FS F SET F.NAME = '''+lkFileName+''' WHERE (F.ID = '''+Selected.SubItems[6]+''')');
      end;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actFileSendToFilial_OnExecute(Sender :TObject);
  var
    lkFileName:string;
    lkFilial  :string;
    lkDBPath  :string;
  begin
    with TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)) do
      begin
      if(Selected.Caption     = '..' )then exit;
      if(Selected.SubItems[3] = '~..')then exit;
      lkFileName := 'DB:'+TERPFormOperFileSystem_GetItemPath(Selected.SubItems[6]);
      if(Selected.SubItems[3] = '..')then
        lkFileName := lkFileName + '%';
      end;
    lkFilial := '';
    SetGlobalVariable('FILIAL_ID',lkFilial);
    call('DB:CONFIG/REF/FILIALS/DEFAULT_DLG.PS');
    lkFilial := GetGlobalVariable('FILIAL_ID');
    if((lkFilial = '') or (UpperCase(lkFilial)='NULL') )then exit;
    lkDBPath := '';
    GetField(FBDataBase, 'TABL$R_FILIALS','DATABASE_NAME_REMOTE', 'ID = '+lkFilial, lkDBPath);
    if GetFieldCommit(FBDataBase,'PROC$_EXCHANGE$_FS_FROMPATH('''+lkDBPath+''', ''SYSDBA'',''masterkey'',0,'''+lkFileName+''')','CNT','',lkFilial)then
      Dialogs.MessageDlg(msg_erp_dbfs_filesendtofilialsucces+lkFilial, mtInformation, [mbOk])
     else
      Dialogs.MessageDlg(msg_erp_dbfs_filesendtofilialerror+lkFileName, mtWarning, [mbOk]);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actFileRename_OnUpdate(Sender :TObject);
  begin
    with TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).Selected do
      TCustomAction(Sender).Enabled := (Caption <> '..') and (SubItems[3] <> '~..');
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actEditCut_OnExecute(Sender :TObject);
  begin
    TERPFormOperFileSystem_BufferList(TComponent(Sender).Owner).Text := TERPFormOperFileSystem_ListView_SelectedIds(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actEditCopy_OnExecute(Sender :TObject);
  begin
    TERPFormOperFileSystem_BufferList(TComponent(Sender).Owner).Text := TERPFormOperFileSystem_ListView_SelectedIds(TComponent(Sender).Owner);

  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actEditPaste_OnExecute(Sender :TObject);
  begin
    TERPFormOperFileSystem_BufferList(TComponent(Sender).Owner).Text := '';
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actEditPaste_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := (TERPFormOperFileSystem_BufferList(TComponent(Sender).Owner).Text <> '');
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actEditDelete_OnExecute(Sender :TObject);
  begin
    if(TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).Selected = nil)then exit;
    if not(Dialogs.MessageDlg(msg_erp_acteditdelete_hint+' ?'+SQLCRLF+TERPFormOperFileSystem_ListView_SelectedFiles(TComponent(Sender).Owner)+#13#10, mtWarning, [mbYes, mbNo]) = mrYes)then exit;
    ExecSQL(FBDataBase, 'DELETE FROM TABL$_FS F WHERE ('''+TERPFormOperFileSystem_ListView_SelectedIds(TComponent(Sender).Owner)+
      ''' CONTAINING ''~''||F.ID||''~'')');
    TERPFormOperFileSystem_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actEditDelete_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := (TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).Selected <> nil);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actNavBack_OnExecute(Sender :TObject);
  begin
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actNavBack_OnUpdate(Sender :TObject);
  begin
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actNavFollow_OnExecute(Sender :TObject);
  begin
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actNavFollow_OnUpdate(Sender :TObject);
  begin
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actNavUp_OnExecute(Sender :TObject);
  begin
    with TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)) do
      begin
      if(not(Items.Count > 0))then exit;
      if(Items[0].Caption <> '..')then exit;
      HelpKeyWord := Items[0].SubItems[5]; 
      TERPFormOperFileSystem_RefreshView(Owner);
      if( (Items.Count > 0) and (StrToInt(Selected.SubItems[6]) > 255) )then
        TxFBTreeView(Owner.FindComponent(obj_name_erp_treeview)).BuildNodeById(Selected.SubItems[6]);
      end;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actNavUp_OnUpdate(Sender :TObject);
  var
    lkEnabled :Boolean;
  begin
    with TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)) do
      begin
      lkEnabled := (Items.Count > 0);
      if lkEnabled then
        lkEnabled := (Items[0].Caption = '..');
      end; 
    TCustomAction(Sender).Enabled := lkEnabled;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewPanelLeft_OnExecute(Sender :TObject);
  begin
    with TxcPanel(TComponent(Sender).Owner.FindComponent(obj_name_erp_panelleft)) do
      begin
      Visible := not Visible;
      TSplitter(TComponent(Sender).Owner.FindComponent(obj_name_erp_splitterleft)).Visible := Visible;
      if Visible then
        TSplitter(TComponent(Sender).Owner.FindComponent(obj_name_erp_splitterleft)).Left := Left + Width + 1;
      end;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewPanelLeft_OnUpdate(Sender :TObject);
  var
    lkChecked :Boolean;
  begin
    lkChecked := TxcPanel(TComponent(Sender).Owner.FindComponent(obj_name_erp_panelleft)).Visible;
    TCustomAction(Sender).Checked := lkChecked;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewRefresh_OnExecute(Sender :TObject);
  begin
     TERPFormOperFileSystem_RefreshView(TComponent(Sender).Owner);
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewGrid_OnExecute(Sender :TObject);
  begin
    TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).GridLines := 
      not TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).GridLines;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewGrid_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Enabled := (TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).ViewStyle = vsReport);
    TCustomAction(Sender).Checked := TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).GridLines;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewIcon_OnExecute(Sender :TObject);
  begin
    TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).ViewStyle := vsIcon;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewIcon_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Checked := TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).ViewStyle = vsIcon;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewList_OnExecute(Sender :TObject);
  begin
    TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).ViewStyle := vsList;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewList_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Checked := TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).ViewStyle = vsList;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewDetail_OnExecute(Sender :TObject);
  begin
    TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).ViewStyle := vsReport;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_actViewDetail_OnUpdate(Sender :TObject);
  begin
    TCustomAction(Sender).Checked := TListView(TComponent(Sender).Owner.FindComponent(obj_name_erp_listview)).ViewStyle = vsReport;
  end;
  //============================================================================
  procedure TERPFormOperFileSystem_OnClose(Sender :TObject; var Action :TCloseAction);
  begin
    Action := caFree;
  end;
  //============================================================================
  function TERPFormOperFileSystem_Create(const aModalForm:Boolean):TForm;
  var
    lkPanelClient:TxcPanel;
    lkPanelLeft  :TxcPanel;
    lkSplt       :TSplitter;
    lkTreeView   :TxFBTreeView;
    lkListView   :TListView;
    lkToolBar    :TxcGradientPanelVista;
    lkToolBarFile:TxcGradientPanelVista;
    lkToolBarEdit:TxcGradientPanelVista;
    lkToolBarView:TxcGradientPanelVista;
    lkLBL        :TLabel;
    lkAct        :TCustomAction;
    lkMainMenu   :TMainMenu;
    lkMIFile     :TMenuItem;
    lkMIEdit     :TMenuItem;
    lkMIView     :TMenuItem;
    lkMI_Line    :TMenuItem;
    lkMI         :TMenuItem;
    lkFT         :TFileType;
    lkExt        :string;
  begin
    if(not FBDataBase.Connected)then
      begin
      Dialogs.MessageDlg('Потеряно соединение с базой данных!', mtError, [mbOk]);
      exit;
      end;
    Result := TERPForm_Create(msg_erp_dbfs_caption, ERP_FILENAME_ICO_DBFS, ERP_FILENAME_BMP_DBFS, aModalForm, @TERPFormOperFileSystem_OnClose);
    with TxcGradientPanelVista(Result.FindComponent(obj_name_erp_topbar)) do
      begin
      StyleManager          := nil;
      Colors.HotTrack       := ERP_ObjectColorLight(ERP_OBJECTTYPE_OPER);
      Colors.HotTrackBorder := ERP_ObjectColor(ERP_OBJECTTYPE_OPER);
      end;  
    TERPFormOperFileSystem_LoadImageListFS(Result);
    lkPanelClient := CreateTxcPanel(Result,Result,obj_name_erp_panelclient,'',alClient,1,1,600,800,xbsNone); 
    lkToolBar := CreateTxcGradientPanelVistaToolBar(Result,lkPanelClient,obj_name_erp_toolbar,'',alTop, 0,32,TERPForm_DefaultToolButtonWidth+4, 200,TERPForm_DefaultToolBarBorderStyle);
    lkToolBarFile := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_file,'',alLeft, 0,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsRaized);
    lkLBL := CreateTLabel(Result, lkToolBar,'', lkToolBarFile.Left+lkToolBarFile.Width+1,0,lkToolBar.Height,4,alLeft,taLeftJustify);
    lkToolBarEdit := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_edit,'',alLeft, lkLBL.Left+lkLBL.Width+1,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsRaized);
    lkLBL := CreateTLabel(Result, lkToolBar,'', lkToolBarEdit.Left+lkToolBarEdit.Width+1,0,lkToolBar.Height,4,alLeft,taLeftJustify);
    lkToolBarView := CreateTxcGradientPanelVistaToolBar(Result,lkToolBar,obj_name_erp_toolbar_view,'',alLeft, lkLBL.Left+lkLBL.Width+1,0,TERPForm_DefaultToolButtonWidth+2, 200,xbsRaized);
    lkMainMenu := TMainMenu(Result.FindComponent(obj_name_erp_mainmenu));
    lkMIFile := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainfile,msg_erp_mimainfile,'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN+0);
    lkMIEdit := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainedit,msg_erp_mimainedit,'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN+1);
    lkMIView := CreateTMenuItem(lkMainMenu.Items,obj_name_erp_mimainview,msg_erp_mimainview,'','', -1, ERP_MENUITEM_FORM_INDEX_BEGIN+2);

    lkPanelLeft := CreateTxcPanel(Result,Result,obj_name_erp_panelleft,'',alLeft,1,1,600,200,xbsNone); 
    lkTreeView := TxFBTreeView.Create(Result);
    with lkTreeView do
      begin
      Name          := obj_name_erp_treeview;
      Parent        := lkPanelLeft;
      Align         := alClient;
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Name     := 'Courier New';
      Font.Size     := 8;
      Font.Style    := [fsBold];
      Ctl3D         := false;
      Images        := CreateTImageList(lkTreeView, 'ilFBTreeView', [30]);;
      HideSelection := false;
      ShowOnlyRoots := false;
      Width         := 240;
      DataBase      := FBDataBase;
      with DBTreeInfo do
        begin
        FieldId       := 'ID';
        FieldName     := 'NAME';
        FieldParentId := 'PARENT_ID';
        FieldStateId  := 'ID';
        RootParentId  := '0';
        TableName     := 'TABL$_FS';
        Where         := 'EXT = ''..'' ';
        {$IFDEF AMUNHOTEP4518}
        OrderBy       := 'NAME';
        {$ENDIF}
        end;
      OnBuildNode := @TERPFormOperFileSystem_TreeView_OnBuildNode;
      OnClick     := @TERPFormOperFileSystem_TreeView_OnClick;
      BuildTree;
      if(Items.Count > 0)then
        Items[0].Selected := true;
      end;
    lkSplt := CreateTSplitter(Result,Result,obj_name_erp_splitterleft,alLeft,lkPanelLeft.Left+lkPanelLeft.Width+1,1,4,4);
    lkListView := TListView.Create(Result);
    with lkListView do
      begin
      Name          := obj_name_erp_listview;
      Parent        := lkPanelClient;
      Align         := alClient;
      Color         := Amunhotep.MainForm.StyleManager.Colors.Window;
      Font.Color    := Amunhotep.MainForm.StyleManager.Colors.Border;
      Font.Name     := 'Courier New';
      Font.Size     := 8;
      Font.Style    := [fsBold];
      Ctl3D         := false;
      HelpKeyWord   := '0';
      ViewStyle     := vsList;
      LargeImages   := TImageList(Result.FindComponent(obj_name_erp_imagelistfs_big  ));
      SmallImages   := TImageList(Result.FindComponent(obj_name_erp_imagelistfs_small));
      HideSelection := false;
      RowSelect     := true;
      MultiSelect   := false;
      GridLines     := true;
      ReadOnly      := true;
      OnClick       := @TERPFormOperFileSystem_ListView_OnClick;
      OnDblClick    := @TERPFormOperFileSystem_ListView_OnDblClick;
      OnKeyDown     := @TERPFormOperFileSystem_ListView_OnKeyDown;
      lkListView.Columns.Clear;
      with lkListView.Columns.Add do
        begin
        Caption  := 'Имя файла';
        Width    := 280;
        MinWidth := Width;
        end;
      with lkListView.Columns.Add do
        begin
        Caption  := 'Подсказка';
        Width    := 400;
        MinWidth := Width;
        end;
      with lkListView.Columns.Add do
        begin
        Caption := 'Дата создания';
        Width    := 160;
        MinWidth := Width;
        end;
      with lkListView.Columns.Add do
        begin
        Caption := 'Дата изменения';
        Width    := 160;
        MinWidth := Width;
        end;
  {
      with lkListView.Columns.Add do
        begin
        Caption := 'EXT';
        Width    := 140;
        MinWidth := Width;
        end;
      with lkListView.Columns.Add do
        begin
        Caption := 'EMPTY';
        Width    := 140;
        MinWidth := Width;
        end;
      with lkListView.Columns.Add do
        begin
        Caption := 'PARENT_ID';
        Width    := 140;
        MinWidth := Width;
        end;
      with lkListView.Columns.Add do
        begin
        Caption := 'ID';
        Width    := 140;
        MinWidth := Width;
        end;
  }
      end;
    lkMI  := CreateTMenuItem(lkMIFile,obj_name_erp_mimainfilenew,msg_erp_mimainfilenew,'','',-1,0);
    lkMI.SubMenuImages := TImageList(Result.FindComponent(obj_name_erp_imagelistfs_small));
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actfilenewfolder,msg_erp_actfilenewfolder,msg_erp_actfilenewfolder_hint,'F7'                 ,0, 80,@TERPFormOperFileSystem_actFileNewFolder_OnExecute,nil,lkToolBarFile,lkMI);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actfilenewfile  ,msg_erp_actfilenewfile  ,msg_erp_actfilenewfile_hint  ,'Ctrl+N'             ,0,181,@TERPFormOperFileSystem_actFileNewFile_OnExecute  ,nil,lkToolBarFile,lkMI);
    lkMI_Line := CreateTMenuItemLine(lkMI    ,obj_name_erp_mimainfilenew+'0001');
    for lkFT:=ftText to ftInno do
      begin
      lkExt := TERPFormOperFileSystem_DefaultFileExt(lkFT);
      lkAct := TERPForm_CreateAction(Result,obj_name_erp_actfilenewfile+lkExt,msg_erp_actfilenewfile+'  '+lkExt,msg_erp_actfilenewfile_hint+'  '+lkExt,'',0,
        TERPFormOperFileSystem_GetImageIndex(Result, lkExt),@TERPFormOperFileSystem_actFileNewFileExt_OnExecute,nil,nil,lkMI);
      lkAct.Tag := Integer(lkFT); 
      end;
    lkAct := TERPForm_CreateAction(Result,'actFileNewObjRpti'                ,'Создать отчет'         ,'Создать отчет'              ,''                   ,0,512,@TERPFormOperFileSystem_actFileNewObjRpti_OnExecute  ,nil                                           ,lkToolBarFile,lkMIFile);
    lkMI  := CreateTMenuItemLine(lkMIFile,obj_name_erp_mimainfile+'0001');
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actfilerename         ,msg_erp_actfilerename   ,msg_erp_actfilerename_hint   ,SHORTCUT_DATA_EDIT   ,0,390,@TERPFormOperFileSystem_actFileRename_OnExecute      ,@TERPFormOperFileSystem_actFileRename_OnUpdate    ,lkToolBarFile,lkMIFile);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actfilesendto+'Filial','Отправить на филиал'   ,'Отправить на филиал'        ,''                   ,0, 85,@TERPFormOperFileSystem_actFileSendToFilial_OnExecute,@TERPFormOperFileSystem_actFileRename_OnUpdate    ,lkToolBarFile,lkMIFile);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_acteditcut            ,msg_erp_acteditcut      ,msg_erp_acteditcut_hint      ,'Ctrl+X'             ,0, 69,@TERPFormOperFileSystem_actEditCut_OnExecute         ,@TERPFormOperFileSystem_actEditDelete_OnUpdate    ,lkToolBarEdit,lkMIEdit);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_acteditcopy           ,msg_erp_acteditcopy     ,msg_erp_acteditcopy_hint     ,'Ctrl+C'             ,0, 68,@TERPFormOperFileSystem_actEditCopy_OnExecute        ,@TERPFormOperFileSystem_actEditDelete_OnUpdate    ,lkToolBarEdit,lkMIEdit);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_acteditpaste          ,msg_erp_acteditpaste    ,msg_erp_acteditpaste_hint    ,'Ctrl+V'             ,0, 73,@TERPFormOperFileSystem_actEditPaste_OnExecute       ,@TERPFormOperFileSystem_actEditPaste_OnUpdate     ,lkToolBarEdit,lkMIEdit);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_acteditdelete         ,msg_erp_acteditdelete   ,msg_erp_acteditdelete_hint   ,'Ctrl+Del'           ,0, 70,@TERPFormOperFileSystem_actEditDelete_OnExecute      ,@TERPFormOperFileSystem_actEditDelete_OnUpdate    ,lkToolBarEdit,lkMIEdit);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewpanelleft      ,msg_erp_actviewpanelleft,msg_erp_actviewpanelleft_hint,SHORTCUT_DATA_LEFTBAR,0,18,@TERPFormOperFileSystem_actViewPanelLeft_OnExecute    ,@TERPFormOperFileSystem_actViewPanelLeft_OnUpdate ,lkToolBarView,lkMIView);
    lkMI  := CreateTMenuItemLine(lkMIView,obj_name_erp_mimainview+'0001');
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actnavback            ,msg_erp_actnavback      ,msg_erp_actnavback_hint      ,SHORTCUT_NAV_BACK    ,0,168,@TERPFormOperFileSystem_actNavBack_OnExecute         ,@TERPFormOperFileSystem_actNavBack_OnUpdate       ,lkToolBarView,lkMIView);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actnavfollow          ,msg_erp_actnavfollow    ,msg_erp_actnavfollow_hint    ,SHORTCUT_NAV_FOLLOW  ,0,169,@TERPFormOperFileSystem_actNavFollow_OnExecute       ,@TERPFormOperFileSystem_actNavFollow_OnUpdate     ,lkToolBarView,lkMIView);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actnavup              ,msg_erp_actnavup        ,msg_erp_actnavup_hint        ,SHORTCUT_NAV_UP      ,0, 86,@TERPFormOperFileSystem_actNavUp_OnExecute           ,@TERPFormOperFileSystem_actNavUp_OnUpdate         ,lkToolBarView,lkMIView);
    lkMI  := CreateTMenuItemLine(lkMIView,obj_name_erp_mimainview+'0002');
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewicon           ,msg_erp_actviewicon     ,msg_erp_actviewicon_hint     ,''                   ,0,149,@TERPFormOperFileSystem_actViewIcon_OnExecute        ,@TERPFormOperFileSystem_actViewIcon_OnUpdate      ,lkToolBarView,lkMIView);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewlist           ,msg_erp_actviewlist     ,msg_erp_actviewlist_hint     ,''                   ,0,151,@TERPFormOperFileSystem_actViewList_OnExecute        ,@TERPFormOperFileSystem_actViewList_OnUpdate      ,lkToolBarView,lkMIView);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewdetail         ,msg_erp_actviewdet      ,msg_erp_actviewdet_hint      ,''                   ,0,150,@TERPFormOperFileSystem_actViewDetail_OnExecute      ,@TERPFormOperFileSystem_actViewDetail_OnUpdate    ,lkToolBarView,lkMIView);
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewgrid           ,msg_erp_actviewgrid     ,msg_erp_actviewgrid_hint     ,''                   ,0,190,@TERPFormOperFileSystem_actViewGrid_OnExecute        ,@TERPFormOperFileSystem_actViewGrid_OnUpdate      ,lkToolBarView,lkMIView);
    lkMI  := CreateTMenuItemLine(lkMIView,obj_name_erp_mimainview+'0003');
    lkAct := TERPForm_CreateAction(Result,obj_name_erp_actviewrefresh        ,msg_erp_actviewrefresh  ,msg_erp_actviewrefresh_hint  ,SHORTCUT_DATA_REFRESH,0,170,@TERPFormOperFileSystem_actViewRefresh_OnExecute     ,nil                                           ,lkToolBarView,lkMIView);

    lkToolBarFile.Width := TWinControl_AutoWidth(lkToolBarFile)+2; lkToolBarFile.Visible := (lkToolBarFile.ControlCount > 0);   
    lkToolBarEdit.Width := TWinControl_AutoWidth(lkToolBarEdit)+2; lkToolBarEdit.Visible := (lkToolBarEdit.ControlCount > 0);   
    lkToolBarView.Width := TWinControl_AutoWidth(lkToolBarView)+2; lkToolBarView.Visible := (lkToolBarView.ControlCount > 0);   
    TERPFormOperFileSystem_RefreshView(Result);
  end;
