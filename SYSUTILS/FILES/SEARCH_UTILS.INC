{$DEFINE PEAKTOP:SYSUTILS/FILES/SEARCH_UTILS.INC}
var
  FileFoundStringList :TStringList;
  //============================================================================
  function Files_GetFileFoundList:TStringList;
  begin
    if(FileFoundStringList = nil)then
      begin
      FileFoundStringList := TStringList.Create;
      with FileFoundStringList do
        begin                                                                                           
        Clear;
        Duplicates := dupIgnore;
        Sorted     := true;
        end;
      end;
    Result := FileFoundStringList;
  end;
  //============================================================================
  procedure Files_FileSearch_OnFileFound(FileFound: TxfsFileInformations);
  begin
    with Files_GetFileFoundList do
      Add(FileFound.Path+FileFound.Name);
  end;
  //============================================================================
  function Files_FindFiles(const aRootPath, aMask:string; const aIncludeSubfolders:Boolean):TStringList;
  begin
    with TxsFileSearch.Create(nil) do
      begin
      RootPath      := aRootPath;
      OnFileFound   := @Files_FileSearch_OnFileFound;
      if not aIncludeSubfolders then
        SearchOptions := SearchOptions - [okIncludeSubfolder];
      FileNames.Clear;
      FileNames.Add(aMask);
      try
        Search;
      finally
        Free;
      end;  
      end
    Result := Files_GetFileFoundList;
  end;
