EXECUTE BLOCK(
  Q_COUNTRIESTP_ID TYPE OF COLUMN TABL$R_COUNTRIESTP.ID = ?ID
)RETURNS(
   COUNTRIESTP_ID   TYPE OF COLUMN TABL$R_COUNTRIESEX.COUNTRIESTP_ID
  ,COUNTRIESTP_NAME TYPE OF COLUMN TABL$R_COUNTRIESTP.NAME
  ,PROBE            TYPE OF COLUMN TABL$R_COUNTRIESEX.NAME
  ,KURS1000086      TYPE OF COLUMN TABL$R_COUNTRIESEX.KURS
  ,KURS1000087      TYPE OF COLUMN TABL$R_COUNTRIESEX.KURS
  ,KURS1000088      TYPE OF COLUMN TABL$R_COUNTRIESEX.KURS
  ,KURS1000089      TYPE OF COLUMN TABL$R_COUNTRIESEX.KURS
  ,ID1000086        TYPE OF COLUMN TABL$R_COUNTRIESEX.ID
  ,ID1000087        TYPE OF COLUMN TABL$R_COUNTRIESEX.ID
  ,ID1000088        TYPE OF COLUMN TABL$R_COUNTRIESEX.ID
  ,ID1000089        TYPE OF COLUMN TABL$R_COUNTRIESEX.ID
)AS
BEGIN
  COUNTRIESTP_ID = :Q_COUNTRIESTP_ID;
  SELECT FIRST 1 COALESCE(C1.NAME,'') FROM TABL$R_COUNTRIESTP C1 WHERE(C1.ID = :COUNTRIESTP_ID)INTO :COUNTRIESTP_NAME;
  FOR SELECT TMP.PROBE FROM (
                SELECT FIRST 1  '333' AS PROBE FROM RDB$DATABASE
      UNION ALL SELECT FIRST 1  '375' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '500' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '583' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '585' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '750' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '800' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '850' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '875' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '900' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '916' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '925' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '950' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '958' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1  '960' AS PROBE FROM RDB$DATABASE 
      UNION ALL SELECT FIRST 1 '9999' AS PROBE FROM RDB$DATABASE
  )TMP INTO :PROBE DO
    BEGIN
    -- NULLING OUTPUT PARAMS
    ID1000086   = 0; ID1000087   = 0; ID1000088   = 0; ID1000089   = 0;
    KURS1000086 = 0; KURS1000087 = 0; KURS1000088 = 0; KURS1000089 = 0;
    -- CHECKING EXISTING RECORDS
    IF(NOT(EXISTS(
        SELECT D.ID FROM TABL$R_COUNTRIESEX D
        WHERE  (D.COUNTRY_ID = 1000086)
          AND  (D.COUNTRIESTP_ID = :COUNTRIESTP_ID)
          AND  (D.NAME = :PROBE)
    )))THEN INSERT INTO TABL$R_COUNTRIESEX(COUNTRY_ID, COUNTRIESTP_ID, NAME, KURS)VALUES(1000086, :COUNTRIESTP_ID, :PROBE, 0);
    IF(NOT(EXISTS(
        SELECT D.ID FROM TABL$R_COUNTRIESEX D
        WHERE  (D.COUNTRY_ID = 1000087)
          AND  (D.COUNTRIESTP_ID = :COUNTRIESTP_ID)
          AND  (D.NAME = :PROBE)
    )))THEN INSERT INTO TABL$R_COUNTRIESEX(COUNTRY_ID, COUNTRIESTP_ID, NAME, KURS)VALUES(1000087, :COUNTRIESTP_ID, :PROBE, 0);
    IF(NOT(EXISTS(
        SELECT D.ID FROM TABL$R_COUNTRIESEX D
        WHERE  (D.COUNTRY_ID = 1000088)
          AND  (D.COUNTRIESTP_ID = :COUNTRIESTP_ID)
          AND  (D.NAME = :PROBE)
    )))THEN INSERT INTO TABL$R_COUNTRIESEX(COUNTRY_ID, COUNTRIESTP_ID, NAME, KURS)VALUES(1000088, :COUNTRIESTP_ID, :PROBE, 0);
    IF(NOT(EXISTS(
        SELECT D.ID FROM TABL$R_COUNTRIESEX D
        WHERE  (D.COUNTRY_ID = 1000089)
          AND  (D.COUNTRIESTP_ID = :COUNTRIESTP_ID)
          AND  (D.NAME = :PROBE)
    )))THEN INSERT INTO TABL$R_COUNTRIESEX(COUNTRY_ID, COUNTRIESTP_ID, NAME, KURS)VALUES(1000089, :COUNTRIESTP_ID, :PROBE, 0);
    -- SELECTING VALUES
    SELECT FIRST 1 D.ID, D.KURS
    FROM   TABL$R_COUNTRIESEX D
    WHERE  (D.COUNTRY_ID = 1000086)
      AND  (D.COUNTRIESTP_ID = :COUNTRIESTP_ID)
      AND  (D.NAME = :PROBE)
    INTO   :ID1000086, :KURS1000086;
    SELECT FIRST 1 D.ID, D.KURS
    FROM   TABL$R_COUNTRIESEX D
    WHERE  (D.COUNTRY_ID = 1000087)
      AND  (D.COUNTRIESTP_ID = :COUNTRIESTP_ID)
      AND  (D.NAME = :PROBE)
    INTO   :ID1000087, :KURS1000087;
    SELECT FIRST 1 D.ID, D.KURS
    FROM   TABL$R_COUNTRIESEX D
    WHERE  (D.COUNTRY_ID = 1000088)
      AND  (D.COUNTRIESTP_ID = :COUNTRIESTP_ID)
      AND  (D.NAME = :PROBE)
    INTO   :ID1000088, :KURS1000088;
    SELECT FIRST 1 D.ID, D.KURS
    FROM   TABL$R_COUNTRIESEX D
    WHERE  (D.COUNTRY_ID = 1000089)
      AND  (D.COUNTRIESTP_ID = :COUNTRIESTP_ID)
      AND  (D.NAME = :PROBE)
    INTO   :ID1000089, :KURS1000089;
    SUSPEND;
    END
END
