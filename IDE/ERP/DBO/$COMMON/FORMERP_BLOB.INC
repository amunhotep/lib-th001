{$DEFINE PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC}
{$IFNDEF PEAKTOP:OBJ/TXCPAGECONTROLEX.INC} {$I PEAKTOP:OBJ/TXCPAGECONTROLEX.INC} {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/TXCTABSHEET.INC}      {$I PEAKTOP:OBJ/TXCTABSHEET.INC}      {$ENDIF}
{$IFNDEF PEAKTOP:OBJ/DBINTERFACE/INTF.INC} {$I PEAKTOP:OBJ/DBINTERFACE/INTF.INC} {$ENDIF}
  //============== PEAKTOP:IDE/ERP/DBO/$COMMON/FORMERP_BLOB.INC ================
  function TERPForm_BlobInterface_ImageIndex(const aFileType:string):Integer;
  begin
    Result := -1;
         if(Pos('DOMN$BLOB_IMAGE',aFileType) = 1)then Result := 283
    else if(Pos('DOMN$BLOB_TEXT' ,aFileType) = 1)then Result := 291
    else if(Pos('DOMN$BLOB_RTF'  ,aFileType) = 1)then Result := 285 
    else if(Pos('DOMN$BLOB_BIN'  ,aFileType) = 1)then Result := 282 
    else if(Pos('DOMN$BLOB_DFM'  ,aFileType) = 1)then Result := 293
    else if(Pos('DOMN$BLOB_PAS'  ,aFileType) = 1)then Result := 289
    else if(Pos('DOMN$BLOB_SQL'  ,aFileType) = 1)then Result := 290
    else if(Pos('DOMN$BLOB_XML'  ,aFileType) = 1)then Result := 288
    else if(Pos('DOMN$BLOB_HTM'  ,aFileType) = 1)then Result := 288
    else if(Pos('DOMN$BLOB_HTML' ,aFileType) = 1)then Result := 288
    else if(Pos('DOMN$BLOB_PHP'  ,aFileType) = 1)then Result := 291
    else {BINARY DATA}                                Result := 282 
  end;
  //============================================================================
  procedure TERPForm_BlobInterface_Create(aDS:TDataSource; aPC :TxcPageControlEx; const aCaption, aFN, aFT:string; const aReadOnly:Boolean);
  var
    lkTS :TxcTabSheet;
  begin
    if(Pos('DOMN$BLOB_',aFT) <> 1)then exit;
    lkTS := CreateTxcTabSheet(aPC, '', aCaption, TERPForm_BlobInterface_ImageIndex(aFT), Amunhotep.MainForm.StyleManager.Colors.Foreground);
    DBInterfaceCreate_Intf(lkTS, lkTS, aDS, aFN, aFT, aReadOnly);
    TxcPageControlEx_ActivateDefaultPage(aPC);
  end;
