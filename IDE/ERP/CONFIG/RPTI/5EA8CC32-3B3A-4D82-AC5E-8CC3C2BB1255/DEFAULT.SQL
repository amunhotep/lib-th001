EXECUTE BLOCK (
  Q_DATE_FROM TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_FROM
 ,Q_DATE_TO   TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_TO
 ,Q_FIRM_IDS  TYPE OF COLUMN TABL$J_4.DOCSTR      = ?FIRM_IDS
)RETURNS ( 
  DATE_FROM              TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,DATE_TO                TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,FIRM_ID                TYPE OF COLUMN TABL$J_4.DOCSTR
 ,FIRM_NAME              TYPE OF COLUMN TABL$J_4.DOCSTR
 ,J_ID_1000142           TYPE OF COLUMN TABL$J_4.ID
 ,J_DOCNUMBERSTR_1000142 TYPE OF COLUMN TABL$J_4.DOCNUMBERSTR
 ,J_DATE_COMMIT_1000142  TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,J_DOCSUM_1000142       TYPE OF COLUMN TABL$J_4.DOCSUM
 ,J_DOCSUM_1000142_NDP   TYPE OF COLUMN TABL$J_4.DOCSUM
 ,J_DOCSUM_1000142_CLR   TYPE OF COLUMN TABL$J_4.DOCSUM
 ,J_SUMSEB_1000142       TYPE OF COLUMN TABL$J_4.DOCSUM
 ,J_GESHEFT_1000142      TYPE OF COLUMN TABL$J_4.DOCSUM
 ,J_ID_1000141           TYPE OF COLUMN TABL$J_4.ID
 ,J_DOCNUMBERSTR_1000141 TYPE OF COLUMN TABL$J_4.DOCNUMBERSTR
 ,J_DATE_COMMIT_1000141  TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,J_DOCSUM_1000141       TYPE OF COLUMN TABL$J_4.DOCSUM
)AS
BEGIN 
  DATE_FROM = :Q_DATE_FROM;
  DATE_TO   = :Q_DATE_TO;
  FOR
    SELECT J.ID, J.DOCNUMBERSTR, J.DATE_COMMIT, J.DOCSUM, J.FIRM_ID
          ,J14.P_NDP, J14.P_SUM
          ,(SELECT FIRST 1 F.NAME FROM TABL$R_FIRMS F WHERE(F.ID = J.FIRM_ID)) AS FIRM_NAME
    FROM   TABL$J_4 J, TABL$J_1000014 J14
    WHERE  (J.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO)
      AND  (J.TYPE_ID = 1000142)
      AND  (J.FLAG_COMMIT = 1)
      AND  (J14.J_ID = J.ID)
    INTO   :J_ID_1000142, :J_DOCNUMBERSTR_1000142, :J_DATE_COMMIT_1000142, :J_DOCSUM_1000142, :FIRM_ID
          ,:J_DOCSUM_1000142_NDP, :J_DOCSUM_1000142_CLR
          ,:FIRM_NAME
  DO
    BEGIN 
    J_SUMSEB_1000142  = 0;
    J_GESHEFT_1000142 = 0;
    SELECT COALESCE(SUM(C.CND_VALUE),0)
    FROM   TABL$P_CND C
    WHERE  (C.J_ID = :J_ID_1000142)
      AND  ('~281~207~' CONTAINING '~'||C.ACC_ID_KRED||'~')
    INTO   :J_SUMSEB_1000142;
    J_GESHEFT_1000142 = :J_DOCSUM_1000142_CLR - :J_SUMSEB_1000142;
    J_ID_1000141           = 0;
    J_DOCNUMBERSTR_1000141 = '';
    J_DATE_COMMIT_1000141  = NULL;
    J_DOCSUM_1000141       = 0;
    SELECT FIRST 1 J4.ID, J4.DOCNUMBERSTR, J4.DATE_COMMIT, J4.DOCSUM
    FROM   TABL$J_CHILDS JC, TABL$J_4 J4
    WHERE  (JC.J_CHILD_ID = :J_ID_1000142)
      AND  (J4.ID = JC.J_ID)
      AND  (J4.TYPE_ID = 1000141)
    INTO   :J_ID_1000141, :J_DOCNUMBERSTR_1000141, :J_DATE_COMMIT_1000141, :J_DOCSUM_1000141;
    SUSPEND;
    END 
END
