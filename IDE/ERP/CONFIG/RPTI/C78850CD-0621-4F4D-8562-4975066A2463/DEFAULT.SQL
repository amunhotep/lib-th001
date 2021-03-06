EXECUTE BLOCK (
  Q_DATE_FROM TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_FROM
 ,Q_DATE_TO   TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_TO
 ,Q_FIRM_IDS  TYPE OF COLUMN TABL$J_4.DOCSTR      = ?FIRM_IDS
 ,Q_ACC_ID    TYPE OF COLUMN TABL$R_BUHG_ACCS.ID  = ?ACC_ID
 ,Q_DEBET     TYPE OF COLUMN TABL$J_4.FLAG_COMMIT = ?DEBET
 ,Q_SUBKONTO  TYPE OF COLUMN TABL$J_4.FLAG_COMMIT = ?SUBKONTO
)RETURNS ( 
  DATE_FROM    TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,DATE_TO      TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,FIRM_IDS     TYPE OF COLUMN TABL$J_4.DOCSTR
 ,FIRM_NAMES   TYPE OF COLUMN TABL$J_4.DOCSTR
 ,ACC_ID       TYPE OF COLUMN TABL$J_4.DOCSTR
 ,ACC_NAME     TYPE OF COLUMN TABL$R_BUHG_ACCS.NAME
 ,ACC_SUBKONTO TYPE OF COLUMN TABL$R_BUHG_ACCS.SUBKONTO
 ,KACC_TID     TYPE OF COLUMN TABL$P_CND.SUBKONTO_ID_DEB
 ,KACC_TNAME   TYPE OF COLUMN TABL$P_CND.SUBKONTO_NAME_DEB
 ,DEBET        TYPE OF COLUMN TABL$J_4.FLAG_COMMIT
 ,DEBET_NAME   TYPE OF COLUMN TABL$J_4.NAME
 ,KACC_ID      TYPE OF COLUMN TABL$R_BUHG_ACCS.ID
 ,KACC_NAME    TYPE OF COLUMN TABL$R_BUHG_ACCS.NAME
 ,KACC_VALUE   TYPE OF COLUMN TABL$J_4.DOCSUM
 ,KACC_VALUE_  TYPE OF COLUMN TABL$J_4.DOCSUM
 ,KACC_SID     TYPE OF COLUMN TABL$P_CND.SUBKONTO_ID_DEB
 ,KACC_SNAME   TYPE OF COLUMN TABL$P_CND.SUBKONTO_NAME_DEB
 ,KACC_SVALUE  TYPE OF COLUMN TABL$J_4.DOCSUM
)AS
BEGIN 
  DATE_FROM = :Q_DATE_FROM;
  DATE_TO   = :Q_DATE_TO;
  FIRM_IDS  = :Q_FIRM_IDS;
  ACC_ID    = :Q_ACC_ID;
  DEBET     = :Q_DEBET;
  IF(:DEBET = 1)THEN DEBET_NAME = '�E�ET'; ELSE DEBET_NAME = 'KPE��T';
  SELECT LIST(F.NAME,'; ') FROM TABL$R_FIRMS F WHERE (:FIRM_IDS CONTAINING '~'||F.ID||'~') INTO :FIRM_NAMES;

  SELECT FIRST 1 BA.NAME, BA.SUBKONTO
  FROM   TABL$R_BUHG_ACCS BA
  WHERE  (BA.ID = :ACC_ID)
  INTO   :ACC_NAME, :ACC_SUBKONTO;
  KACC_VALUE_ = 0;
  
  IF(:DEBET = 1)THEN
    BEGIN
    SELECT COALESCE(SUM(C.CND_VALUE),0) AS ACC_VALUE
    FROM   TABL$P_CND C
    WHERE  (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO)
      AND  (:FIRM_IDS CONTAINING '~'||C.FIRM_ID||'~')
      AND  (C.ACC_IDS_DEB CONTAINING '~'||:ACC_ID||'~')
    INTO   :KACC_VALUE_;
    FOR
      SELECT C.ACC_ID_KRED AS ACC_ID, COALESCE(SUM(C.CND_VALUE),0) AS ACC_VALUE
      FROM   TABL$P_CND C
      WHERE  (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO)
        AND  (:FIRM_IDS CONTAINING '~'||C.FIRM_ID||'~')
        AND  (C.ACC_IDS_DEB CONTAINING '~'||:ACC_ID||'~')
      GROUP BY C.ACC_ID_KRED
      INTO   :KACC_ID, :KACC_VALUE
    DO
      BEGIN
      KACC_TID     = 0;
      KACC_TNAME   = '';
      KACC_SID     = 0;
      KACC_SNAME   = '';
      KACC_SVALUE  = 0;
      SELECT FIRST 1 BA.NAME
      FROM   TABL$R_BUHG_ACCS BA
      WHERE  (BA.ID = :KACC_ID)
      INTO   :KACC_NAME;
      IF(:Q_SUBKONTO <> 1)THEN
        BEGIN
        SUSPEND;
        END
       ELSE 
        BEGIN
        FOR
          SELECT C.SUBKONTO_ID_DEB, C.SUBKONTO_NAME_DEB, C.SUBKONTO_ID_KRED, C.SUBKONTO_NAME_KRED, COALESCE(SUM(C.CND_VALUE),0) AS ACC_VALUE
          FROM   TABL$P_CND C
          WHERE  (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO)
            AND  (:FIRM_IDS CONTAINING '~'||C.FIRM_ID||'~')
            AND  (C.ACC_IDS_DEB  CONTAINING '~'||:ACC_ID||'~')
            AND  (C.ACC_IDS_KRED CONTAINING '~'||:KACC_ID||'~')
          GROUP BY C.SUBKONTO_ID_DEB, C.SUBKONTO_NAME_DEB, C.SUBKONTO_ID_KRED, C.SUBKONTO_NAME_KRED
          INTO   :KACC_TID, :KACC_TNAME, :KACC_SID, :KACC_SNAME, :KACC_SVALUE
        DO
          SUSPEND;
        END
      END
    END
   ELSE
    BEGIN
    SELECT COALESCE(SUM(C.CND_VALUE),0) AS ACC_VALUE
    FROM   TABL$P_CND C
    WHERE  (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO)
      AND  (:FIRM_IDS CONTAINING '~'||C.FIRM_ID||'~')
      AND  (C.ACC_IDS_KRED CONTAINING '~'||:ACC_ID||'~')
    INTO   :KACC_VALUE_;
    FOR
      SELECT C.ACC_ID_DEB AS ACC_ID, COALESCE(SUM(C.CND_VALUE),0) AS ACC_VALUE
      FROM   TABL$P_CND C
      WHERE  (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO)
        AND  (:FIRM_IDS CONTAINING '~'||C.FIRM_ID||'~')
        AND  (C.ACC_IDS_KRED CONTAINING '~'||:ACC_ID||'~')
      GROUP BY C.ACC_ID_DEB
      INTO   :KACC_ID, :KACC_VALUE
    DO
      BEGIN
      KACC_SID     = 0;
      KACC_SNAME   = '';
      KACC_SVALUE  = 0;
      SELECT FIRST 1 BA.NAME
      FROM   TABL$R_BUHG_ACCS BA
      WHERE  (BA.ID = :KACC_ID)
      INTO   :KACC_NAME;
      IF(:Q_SUBKONTO <> 1)THEN
        BEGIN
        SUSPEND;
        END
       ELSE 
        BEGIN
        FOR
          SELECT C.SUBKONTO_ID_KRED, C.SUBKONTO_NAME_KRED, C.SUBKONTO_ID_DEB, C.SUBKONTO_NAME_DEB, COALESCE(SUM(C.CND_VALUE),0) AS ACC_VALUE
          FROM   TABL$P_CND C
          WHERE  (C.DATE_COMMIT BETWEEN :DATE_FROM AND :DATE_TO)
            AND  (:FIRM_IDS CONTAINING '~'||C.FIRM_ID||'~')
            AND  (C.ACC_IDS_DEB  CONTAINING '~'||:KACC_ID||'~')
            AND  (C.ACC_IDS_KRED CONTAINING '~'||:ACC_ID||'~')
          GROUP BY C.SUBKONTO_ID_KRED, C.SUBKONTO_NAME_KRED, C.SUBKONTO_ID_DEB, C.SUBKONTO_NAME_DEB
          INTO   :KACC_TID, :KACC_TNAME, :KACC_SID, :KACC_SNAME, :KACC_SVALUE
        DO
          SUSPEND;
        END
      END
    END

END
