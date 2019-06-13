{$DEFINE PEAKTOP:SYSUTILS/PREVIEW_REPORT.INC}
  //============================================================================
  function PreviewReportByFileName(const aFileName:string):Boolean;
  var
    Prntr :TxrPrinter;
  begin
    Result := false;
    try
      Prntr      := TxrPrinter.Create(Amunhotep.MainForm);
      //Prntr.Name := 'PreviewXRPrinter'+RandomHexStr(16);
      Prntr.Load(aFileName);
    finally
      Prntr.Preview;
      Result := true;
    end;  
  end;