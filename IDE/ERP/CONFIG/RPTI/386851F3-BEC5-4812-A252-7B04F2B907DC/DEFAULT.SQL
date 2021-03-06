SELECT TMP.BIRTHYEAR, (EXTRACT(YEAR FROM CURRENT_TIMESTAMP) - TMP.BIRTHYEAR) AS VOZRAST,
       COUNT(TMP.SUBKONTO_ID) AS CS_COUNT, SUM(TMP.SUMPC) AS SUMPC
FROM   (
          SELECT  J16.SUBKONTO_ID, EXTRACT(YEAR FROM CS.BIRTHDAY) AS BIRTHYEAR, SUM(J4.DOCSUM) AS SUMPC
          FROM    TABL$J_4 J4, TABL$J_1000016 J16, TABL$R_CS CS
          WHERE   (J4.TYPE_ID = 1000020)
            AND   (J4.FLAG_COMMIT = 1)
            AND   (J16.J_ID = J4.ID)
            AND   (J16.ACC_ID = 373)
            AND   (CS.ID = J16.SUBKONTO_ID)
          GROUP BY 1,2
       ) TMP
WHERE  (TMP.BIRTHYEAR >= 1900)
  AND  (TMP.BIRTHYEAR <= 2020)
GROUP BY 1,2;

