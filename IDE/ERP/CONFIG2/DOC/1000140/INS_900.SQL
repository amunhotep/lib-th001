EXECUTE BLOCK (
  Q_J_ID TYPE OF COLUMN TABL$J_4.ID = ?J_ID
)AS
  DECLARE VARIABLE P_FIRM_ID     TYPE OF COLUMN TABL$J_4.FIRM_ID;
  DECLARE VARIABLE P_DATE_COMMIT TYPE OF COLUMN TABL$J_4.DATE_COMMIT;
  DECLARE VARIABLE P_FLAG_COMMIT TYPE OF COLUMN TABL$J_4.FLAG_COMMIT;

  DECLARE VARIABLE P_ACC_ID      TYPE OF COLUMN TABL$R_BUHG_ACCS.ID;
  DECLARE VARIABLE P_ACC_ID2     TYPE OF COLUMN TABL$R_BUHG_ACCS.ID;
  DECLARE VARIABLE P_SUBKONTO_ID TYPE OF COLUMN TABL$R_BUHG_ACCS.ID;
  DECLARE VARIABLE P_SALDO       TYPE OF COLUMN TABL$P_CND.CND_VALUE;
  DECLARE VARIABLE P_DEBET       TYPE OF COLUMN TABL$P_CND.CND_VALUE;
  DECLARE VARIABLE P_KREDIT      TYPE OF COLUMN TABL$P_CND.CND_VALUE;
BEGIN
  SELECT FIRST 1 J.FIRM_ID, J.DATE_COMMIT, J.FLAG_COMMIT
  FROM    TABL$J_4 J
  WHERE  (J.ID = :Q_J_ID)
  INTO   :P_FIRM_ID, :P_DATE_COMMIT, :P_FLAG_COMMIT;
  IF(:P_FLAG_COMMIT = 1)THEN EXIT;

  P_DATE_COMMIT = DATEADD(1 MONTH TO :P_DATE_COMMIT);
  P_DATE_COMMIT = '01.'||LPAD(EXTRACT(MONTH FROM :P_DATE_COMMIT),2,'0')||'.'||LPAD(EXTRACT(YEAR FROM :P_DATE_COMMIT),4,'0')||' 23:59:59';
  P_DATE_COMMIT = DATEADD(-1 DAY TO :P_DATE_COMMIT);
  UPDATE TABL$J_4 J SET
     J.DATE_COMMIT = :P_DATE_COMMIT
    ,J.NAME        = '�������� �������'
  WHERE (J.ID = :Q_J_ID);
  DELETE FROM TABL$D_1000140 D WHERE (D.J_ID = :Q_J_ID);

  FOR SELECT DISTINCT BA.ID FROM TABL$R_BUHG_ACCS BA WHERE ('~91~92~93~' CONTAINING '~'||BA.ID||'~') INTO :P_ACC_ID DO
  FOR
    SELECT DISTINCT TMP.SUBKONTO_ID 
    FROM   ( 
            SELECT CK.SUBKONTO_ID_KRED AS SUBKONTO_ID 
            FROM   TABL$P_CND CK 
            WHERE  (CK.DATE_COMMIT <= :P_DATE_COMMIT)
              AND  ((CK.FIRM_ID+0) = :P_FIRM_ID)
              AND  (CK.ACC_IDS_KRED CONTAINING '~'||:P_ACC_ID||'~')
            UNION ALL 
            SELECT CD.SUBKONTO_ID_DEB AS SUBKONTO_ID 
            FROM   TABL$P_CND CD 
            WHERE  (CD.DATE_COMMIT <= :P_DATE_COMMIT)
              AND  ((CD.FIRM_ID+0) = :P_FIRM_ID)
              AND  (CD.ACC_IDS_DEB CONTAINING '~'||:P_ACC_ID||'~')
            )TMP 
    INTO   :P_SUBKONTO_ID
  DO 
    BEGIN 
    P_DEBET  = 0;
    P_KREDIT = 0;
    P_SALDO  = 0;
    SELECT COALESCE(SUM(C.CND_VALUE),0) 
    FROM   TABL$P_CND C 
    WHERE  (C.DATE_COMMIT    <= :P_DATE_COMMIT)
      AND  ((C.FIRM_ID+0)     = :P_FIRM_ID)
      AND  (C.SUBKONTO_ID_DEB = :P_SUBKONTO_ID)
      AND  (C.ACC_IDS_DEB CONTAINING '~'||:P_ACC_ID||'~')
    INTO   :P_DEBET;
    SELECT COALESCE(SUM(C.CND_VALUE),0) 
    FROM   TABL$P_CND C 
    WHERE  (C.DATE_COMMIT     <= :P_DATE_COMMIT)
      AND  ((C.FIRM_ID+0)      = :P_FIRM_ID)
      AND  (C.SUBKONTO_ID_KRED = :P_SUBKONTO_ID)
      AND  (C.ACC_IDS_KRED CONTAINING '~'||:P_ACC_ID||'~')
    INTO   :P_KREDIT;
    P_SALDO = :P_DEBET - :P_KREDIT;
    P_ACC_ID2 = 0;
    IF(:P_ACC_ID = 91)THEN P_ACC_ID2 = 7912;
    IF(:P_ACC_ID = 92)THEN P_ACC_ID2 = 7911;
    IF(:P_ACC_ID = 93)THEN P_ACC_ID2 = 7911;
    IF((:P_SALDO <> 0)AND(:P_ACC_ID2 <> 0))THEN
      INSERT INTO TABL$D_1000140(J_ID, NAME, ACC_ID_DEB, ACC_ID_KRED, CND_VALUE
        ,SUBKONTO_ID_DEB, SUBKONTO_ID_KRED, SUBKONTO_QUANT_DEB,  SUBKONTO_QUANT_KRED
        ,J_ID_ORD_DEB, J_ID_ORD_KRED
      )VALUES(:Q_J_ID, '', :P_ACC_ID2, :P_ACC_ID, :P_SALDO
        ,0, :P_SUBKONTO_ID, 0, 0, 0, 0
      );
    END
END
