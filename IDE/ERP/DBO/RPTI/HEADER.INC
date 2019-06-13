{$DEFINE PEAKTOP:IDE/ERP/DBO/RPTI/HEADER.INC}
  //================ PEAKTOP:IDE/ERP/DBO/RPTI/HEADER.INC =======================
  procedure TERPFormRpti_OnChart(aOwner:TComponent;aParent:TWinControl);              forward;
  procedure TERPFormRpti_OnTerms(aOwner:TComponent;aParent:TWinControl);              forward;
  function  TERPFormRpti_Create(const aReportGUID :string):TAmunhotepForm;            forward;
  function  TERPFormRpti_OnColumnsCreate (aOwner:TComponent; aDBG:TDBGridEh):Boolean; forward;
  procedure TERPFormRpti_OnColumnsCreated(aOwner:TComponent; aDBG:TDBGridEh);         forward;
  procedure TERPFormRpti_OnColumnsLoad  (aOwner:TComponent; aDBG:TDBGridEh);          forward;
  function  TERPFormRpti_OnGetSQL(aOwner:TComponent;var aSQL:string):Boolean;         forward;
  procedure TERPFormRpti_OnGetSQLFileName(aOwner:TComponent;var aFileName:string);    forward;
  procedure TERPFormRpti_OnProcessParams(aOwner:TComponent;aQr :TxFBQuery);           forward;
  function  TERPFormRpti_GetExportFilter(aOwner:TComponent):string;                   forward;   
  function  TERPFormRpti_OnPrint(aOwner:TComponent):Boolean;                          forward;
  procedure TERPFormRpti_BeforePreview(aOwner:TComponent; aRpt:TxReport);             forward;
