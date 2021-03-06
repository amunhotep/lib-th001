SELECT R0000.ID AS DS$ID 
      ,R0000.FLAG_DELETE
      ,R0000.FLAG_COMMIT
      ,R0000.FLAG_LOCK
      ,R0000.ID
      ,R0000.TYPE_ID
      ,(SELECT FIRST 1 T0001.NAME FROM TABL$_TB_DOCS T0001 WHERE (T0001.ID = R0000.TYPE_ID)) AS TYPE_ID_
      ,R0000.DOCNUMBER
      ,R0000.DOCNUMBERSTR
      ,R0000.DOCNUMBERIN
      ,R0001.WRK_ID
      ,(SELECT FIRST 1 T0002.NAME   FROM TABL$R_WRK T0002 WHERE (T0002.ID = R0001.WRK_ID)) AS WRK_ID_
      ,(SELECT FIRST 1 P0001.POINTS FROM PROC$P_WRK_ATPOINTS_GET(R0001.WRK_ID, R0000.DATE_COMMIT) P0001 ) AS WRK_POINTS
      ,R0001.DOC_ID_PASSPORT
      ,(SELECT FIRST 1 T0003.NAMEDISPLAY FROM TABL$R_DOC T0003 WHERE (T0003.ID = R0001.DOC_ID_PASSPORT)) AS DOC_ID_PASSPORT_
      ,R0001.DOC_ID_DRIVER
      ,(SELECT FIRST 1 T0004.NAMEDISPLAY FROM TABL$R_DOC T0004 WHERE (T0004.ID = R0001.DOC_ID_DRIVER)) AS DOC_ID_DRIVER_
      ,R0001.DOC_ID_LICENSE
      ,(SELECT FIRST 1 T0005.NAMEDISPLAY  FROM TABL$R_DOC T0005  WHERE (T0005.ID  = R0001.DOC_ID_LICENSE)) AS DOC_ID_LICENSE_
      ,(SELECT FIRST 1 T00051.DOC_DATEEND FROM TABL$R_DOC T00051 WHERE (T00051.ID = R0001.DOC_ID_LICENSE)) AS DOC_ID_LICENSE_DOC_DATEEND
      ,R0001.DOC_ID_MED
      ,(SELECT FIRST 1 T0006.NAMEDISPLAY FROM TABL$R_DOC T0006 WHERE (T0006.ID = R0001.DOC_ID_MED)) AS DOC_ID_MED_
      ,(SELECT FIRST 1 T0061.DOC_DATEEND FROM TABL$R_DOC T0061 WHERE (T0061.ID = R0001.DOC_ID_MED)) AS DOC_ID_MED_DOC_DATEEND
      ,R0001.DOC_ID_WAR
      ,(SELECT FIRST 1 T0007.NAMEDISPLAY FROM TABL$R_DOC T0007 WHERE (T0007.ID = R0001.DOC_ID_WAR)) AS DOC_ID_WAR_
      ,R0001.J_ID_WORK
      ,(SELECT FIRST 1 T0008.DOCNUMBERSTR||'  '||T0008.DATE_COMMIT FROM TABL$J_4 T0008 WHERE (T0008.ID = R0001.J_ID_WORK)) AS J_ID_WORK_
      ,R0001.J_ID_TMC
      ,(SELECT FIRST 1 T0009.DOCNUMBERSTR||'  '||T0009.DATE_COMMIT FROM TABL$J_4 T0009 WHERE (T0009.ID = R0001.J_ID_TMC)) AS J_ID_TMC_
      ,R0001.TMC_ID
      ,(SELECT FIRST 1 T0010.NAME FROM TABL$R_TMC T0010 WHERE (T0010.ID = R0001.TMC_ID)) AS TMC_ID_
      ,R0001.TMC_KM
      ,R0001.DOC_ID_TMC1
      ,(SELECT FIRST 1 T0011.NAMEDISPLAY FROM TABL$R_DOC T0011 WHERE (T0011.ID = R0001.DOC_ID_TMC1)) AS DOC_ID_TMC1_
      ,(SELECT FIRST 1 T00111.DOC_DATEEND FROM TABL$R_DOC T00111 WHERE (T00111.ID = R0001.DOC_ID_TMC1)) AS DOC_ID_TMC1_DOC_DATEEND
      ,R0001.DOC_ID_TMC2
      ,(SELECT FIRST 1 T0012.NAMEDISPLAY FROM TABL$R_DOC T0012 WHERE (T0012.ID = R0001.DOC_ID_TMC2)) AS DOC_ID_TMC2_
      ,(SELECT FIRST 1 T00121.DOC_DATEEND FROM TABL$R_DOC T00121 WHERE (T00121.ID = R0001.DOC_ID_TMC2)) AS DOC_ID_TMC2_DOC_DATEEND
      ,R0001.SALESPLAN
      ,R0001.REGIONSLEN_ID
      ,(SELECT FIRST 1 T0011.NAME FROM TABL$R_REGIONSLEN T0011 WHERE (T0011.ID = R0001.REGIONSLEN_ID)) AS REGIONSLEN_ID_
      ,R0001.SALESREGIONSLEN
      ,R0001.SUMTAX
      ,R0001.SUMTAXES
      ,R0001.SUMMED
      ,R0001.SUMWASH
      ,R0001.SUMCHECK
      ,R0001.SUMKRD
      ,R0001.SALESTOTAL
      ,R0001.SALESFACT
      ,R0001.SALESDIFF
      ,R0001.SALESDIFFPC
      ,R0001.ORDERS1
      ,R0001.ORDERS2
      ,R0001.ORDERSRET
      ,R0001.ORDERSTOTAL
      ,R0000.VALUTE_ID
      ,(SELECT FIRST 1 T0012.VALUTE_SHORT FROM TABL$R_COUNTRIES T0012 WHERE (T0012.ID = R0000.VALUTE_ID)) AS VALUTE_ID_
      ,R0000.DOCSUMVAL
      ,R0000.DOCSUM
      ,R0000.DOCNDP
      ,R0000.DOCSUMWONDP
      ,R0000.NAME
      ,R0000.DATE_COMMIT
      ,R0000.DATE_IN
      ,R0000.FIRM_ID
      ,(SELECT FIRST 1 T0013.NAME FROM TABL$R_FIRMS T0013 WHERE (T0013.ID = R0000.FIRM_ID)) AS FIRM_ID_
      ,R0000.FILIAL_ID
      ,(SELECT FIRST 1 T0014.NAME FROM TABL$R_FILIALS T0014 WHERE (T0014.ID = R0000.FILIAL_ID)) AS FILIAL_ID_
      ,R0000.USER_ID
      ,(SELECT FIRST 1 T0015.ID FROM TABL$_USERS T0015 WHERE (T0015.ID = R0000.USER_ID)) AS USER_ID_
      ,(SELECT FIRST 1 COALESCE(WZZ.NAME, R0000.USER_ID) FROM TABL$R_WRK WZZ WHERE (TRIM(WZZ.USER_NAME) = R0000.USER_ID) ) AS WRK_NAME
      ,R0000.DOCSTR
      ,(SELECT FIRST 1 TBD01.COLOR_FRG FROM TABL$_TB_DOCS TBD01 WHERE (TBD01.ID = R0000.TYPE_ID)) AS COLOR_FRG
      ,(SELECT FIRST 1 TBD01.COLOR_BGR FROM TABL$_TB_DOCS TBD01 WHERE (TBD01.ID = R0000.TYPE_ID)) AS COLOR_BGR 
FROM   TABL$J_4 R0000, TABL$J_1000156 R0001 
WHERE (R0000.ID   = ?J_ID) 
  AND (R0001.J_ID = R0000.ID)
ORDER BY DS$ID ASCENDING
