EXECUTE BLOCK AS
  DECLARE VARIABLE P_PLACE_ID       TYPE OF COLUMN TABL$J_1000014.PLACE_ID;
  DECLARE VARIABLE P_FIRM_ID        TYPE OF COLUMN TABL$J_4.FIRM_ID;
  DECLARE VARIABLE P_CS_ID          TYPE OF COLUMN TABL$J_1000014.CS_ID;
  DECLARE VARIABLE P_J_ID           TYPE OF COLUMN TABL$J_4.ID;
  DECLARE VARIABLE P_J_1000064_ID   TYPE OF COLUMN TABL$J_4.ID;
  DECLARE VARIABLE P_J_1000024_ID   TYPE OF COLUMN TABL$J_4.ID;

  DECLARE VARIABLE P_TMC_ID         TYPE OF COLUMN TABL$R_TMC.ID;
  DECLARE VARIABLE P_PRICE          TYPE OF COLUMN TABL$D_1000062.PRICE;
  DECLARE VARIABLE P_QUANT          TYPE OF COLUMN TABL$D_1000062.QUANT;

  DECLARE VARIABLE P_CNT            TYPE OF COLUMN TABL$J_4.ID;
BEGIN
  FOR
    SELECT J.ID
    FROM   TABL$J_4 J, TABL$J_1000062 J62
    WHERE  (J.TYPE_ID = 1000062)
      AND  (J.FLAG_COMMIT = 1)
      AND  (J62.J_ID = J.ID)
      AND  ((J62.STATE_ID = 0) OR (J62.STATE_ID = 4))
      AND  (NOT(EXISTS(
              SELECT JTMP.DOCNUMBERSTR
              FROM   TABL$J_1000062_FCC7C1EDCFB2F1D4 JTMP
              WHERE  (JTMP.DOCNUMBERSTR = J.DOCNUMBERSTR)
            )))
    INTO   :P_J_ID
  DO
    BEGIN
    P_J_1000064_ID = 0;
    P_PLACE_ID     = 0;
    P_FIRM_ID      = 0;
    SELECT FIRST 1 J.ID, J.FIRM_ID, JB.PLACE_ID
    FROM   TABL$J_CHILDS JC, TABL$J_4 J, TABL$J_1000014 JB
    WHERE  (JC.J_ID = :P_J_ID)
      AND  (J.ID = JC.J_CHILD_ID)
      AND  (J.TYPE_ID = 1000064)
      AND  (J.FLAG_COMMIT = 1)
      AND  (JB.J_ID = J.ID)
    INTO   :P_J_1000064_ID, :P_FIRM_ID, :P_PLACE_ID;
    IF( (:P_J_1000064_ID<>0) AND (:P_J_1000064_ID IS NOT NULL) )THEN
      IF(NOT(EXISTS(
        SELECT FIRST 1 J.ID
        FROM   TABL$J_CHILDS JC, TABL$J_4 J
        WHERE  (JC.J_ID = :P_J_1000064_ID)
          AND  (J.ID = JC.J_CHILD_ID)
          AND  (J.TYPE_ID = 1000024)
--          AND  (J.FLAG_COMMIT = 1)
      )))THEN
      BEGIN
      SELECT FIRST 1 F.CS_ID
      FROM   TABL$R_FIRMS F
      WHERE  (F.ID = :P_FIRM_ID)
      INTO   :P_CS_ID;
      SELECT FIRST 1 P.J_ID FROM PROC$J_INS_4(:P_FIRM_ID, 1000024, :P_J_1000064_ID) P INTO :P_J_1000024_ID;
      UPDATE OR INSERT INTO TABL$J_1000014 (J_ID, CS_ID, CS_ADDR_ID, PLACE_ID, TAX_ID, TO_PLACE_ID, WRK_ID, TMC_GRID_ID)
        VALUES (:P_J_1000024_ID, :P_CS_ID, 0, :P_PLACE_ID, 1000008, 1000000, 0, 0)
        MATCHING(J_ID);
      --------
      P_CNT = 0;
      FOR
        SELECT DB.TMC_ID
              ,(SELECT FIRST 1 COALESCE(P.PRICE,0) FROM TABL$R_TMC_P P WHERE(P.TMC_ID = TMC.ID)
                AND (P.VALUE_DATE = TMC.VALUE_DATE)) AS PRICE
        FROM   TABL$D_1000014 DB, TABL$R_TMC TMC
        WHERE  (DB.J_ID  = :P_J_1000064_ID)
          AND  (TMC.ID   = DB.TMC_ID)
        INTO   :P_TMC_ID, :P_PRICE
      DO
        BEGIN
        SELECT SUM(P.QUANT)
        FROM   TABL$P_TMC_QUANT P
        WHERE  ((P.FIRM_ID+0) = :P_FIRM_ID)
          AND  (P.TMC_ID = :P_TMC_ID)
          AND  ((P.PLACE_ID+0) = :P_PLACE_ID)
        INTO   :P_QUANT;
    
        IF(:P_QUANT IS NULL)THEN P_QUANT = 0;
    
        IF(:P_QUANT > 0)THEN
          BEGIN
          INSERT INTO TABL$D_1000014 (J_ID, NAME, TMC_ID, PRICE, QUANT, J_BILLS_ID, PRICE_TMC)
          VALUES (:P_J_1000024_ID, '', :P_TMC_ID, :P_PRICE, :P_QUANT, :P_J_1000064_ID, :P_PRICE);
          P_CNT = :P_CNT + 1;
          END
        END
      IF(:P_CNT = 0)THEN
        BEGIN
        DELETE FROM TABL$J_4 J WHERE J.ID = :P_J_1000024_ID;
        P_J_1000024_ID = 0;
        END
      IF(:P_J_1000024_ID <> 0)THEN
        BEGIN
        UPDATE TABL$J_4 J SET
          J.FLAG_COMMIT = 1
        WHERE (J.ID = :P_J_1000024_ID);
        END
      END
    END
END
