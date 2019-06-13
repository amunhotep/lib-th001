EXECUTE BLOCK (
  Q_PREFIX     TYPE OF COLUMN TABL$J_4.DOCSTR      = ?PREFIX
 ,Q_ROOT_ID    TYPE OF COLUMN TABL$R_TMC_CTGR.ID   = ?ROOT_ID
 ,Q_FIRM_IDS   TYPE OF COLUMN TABL$J_4.DOCSTR      = ?FIRM_IDS
 ,Q_PLACE_IDS  TYPE OF COLUMN TABL$J_4.DOCSTR      = ?PLACES_IDS
 ,Q_DATE       TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_FROM
)RETURNS(
  DATE_RPT  TYPE OF COLUMN TABL$J_4.DATE_COMMIT
 ,FLAG_DIFF TYPE OF COLUMN TABL$J_4.FLAG_COMMIT
 ,FIRM_IDS  TYPE OF COLUMN TABL$J_4.DOCSTR
 ,PLACE_IDS TYPE OF COLUMN TABL$J_4.DOCSTR
 ,ASQL001   TYPE OF COLUMN TABL$J_4.DOCSTR
 ,ASQL002   TYPE OF COLUMN TABL$J_4.DOCSTR
) AS
  DECLARE VARIABLE P_LANG_ID                TYPE OF COLUMN TABL$R_COUNTRIES.ID;
  DECLARE VARIABLE P_COUNTRY_ID             TYPE OF COLUMN TABL$R_COUNTRIES.ID;
  DECLARE VARIABLE P_NAME                   TYPE OF COLUMN TABL$_LOCAL.NAME;
  DECLARE VARIABLE P_TMC_CTGR_ID            TYPE OF COLUMN TABL$R_TMC_CTGR.ID;
  DECLARE VARIABLE P_TMC_CTGR_ID_L          TYPE OF COLUMN TABL$R_TMC_CTGR.ID;
  DECLARE VARIABLE P_TMC_CTGR_NAME          TYPE OF COLUMN TABL$R_TMC_CTGR.NAME;
  DECLARE VARIABLE P_TMC_CTGR_NAME_L        TYPE OF COLUMN TABL$R_TMC_CTGR.NAME;
  DECLARE VARIABLE P_TMC_GROUP_ID           TYPE OF COLUMN TABL$R_TMC_GROUP.ID;
  DECLARE VARIABLE P_TMC_GROUP_NAME         TYPE OF COLUMN TABL$R_TMC_GROUP.NAME;
  DECLARE VARIABLE P_TMC_ID                 TYPE OF COLUMN TABL$R_TMC.ID;
  DECLARE VARIABLE P_TMC_NAME               TYPE OF COLUMN TABL$R_TMC.NAME;
  DECLARE VARIABLE P_TMC_NAME_L             TYPE OF COLUMN TABL$R_TMC.NAME;
  DECLARE VARIABLE P_TMC_NAME_L2            TYPE OF COLUMN TABL$R_TMC.NAME;
  DECLARE VARIABLE P_TMC_NAME_L3            TYPE OF COLUMN TABL$R_TMC.NAME;
  DECLARE VARIABLE P_TMC_ARTICLE            TYPE OF COLUMN TABL$R_TMC.ARTICLE;
  DECLARE VARIABLE P_TMC_BARCODE            TYPE OF COLUMN TABL$R_TMC.BARCODE;
  DECLARE VARIABLE P_VALUTE                 TYPE OF COLUMN TABL$R_COUNTRIES.VALUTE;
  DECLARE VARIABLE P_TMC_PROBE              TYPE OF COLUMN TABL$R_TMC.PROBE;
  DECLARE VARIABLE P_TMC_MASSA              TYPE OF COLUMN TABL$R_TMC.MASSA;
  DECLARE VARIABLE P_TMC_MASSA_INS          TYPE OF COLUMN TABL$R_TMC.MASSA;
  DECLARE VARIABLE P_TMC_MASSA_NETTO        TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO;
  DECLARE VARIABLE P_TMC_LGTH               TYPE OF COLUMN TABL$R_TMC.LGTH;
  DECLARE VARIABLE P_TMC_DIAM               TYPE OF COLUMN TABL$R_TMC.DIAM;
  DECLARE VARIABLE P_TMC_VALUE_DATE         TYPE OF COLUMN TABL$R_TMC.VALUE_DATE;
  DECLARE VARIABLE P_PRICE                  TYPE OF COLUMN TABL$P_TMC_QUANT.QUANT;
  DECLARE VARIABLE P_QUANT                  TYPE OF COLUMN TABL$P_TMC_QUANT.QUANT;
BEGIN
  DATE_RPT  = :Q_DATE;
  FIRM_IDS  = :Q_FIRM_IDS;
  PLACE_IDS = :Q_PLACE_IDS;
/*
  ASQL001 = 
    'DELETE FROM `'||:Q_PREFIX||'product_description`; '||ASCII_CHAR(13)||ASCII_CHAR(10)||
    'DELETE FROM `'||:Q_PREFIX||'product_to_category`; '||ASCII_CHAR(13)||ASCII_CHAR(10)||
    'DELETE FROM `'||:Q_PREFIX||'product_to_layout`; '||ASCII_CHAR(13)||ASCII_CHAR(10)||
    'DELETE FROM `'||:Q_PREFIX||'product_to_store`; '||ASCII_CHAR(13)||ASCII_CHAR(10);
  ASQL002 = 
    'DELETE FROM `'||:Q_PREFIX||'product`; '||ASCII_CHAR(13)||ASCII_CHAR(10);
  SUSPEND;
*/
  FOR
    SELECT T.ID, T.NAME
    FROM   (WITH RECURSIVE CGG AS(
              SELECT CG1.ID, CG1.PARENT_ID, CG1.NAME, CG1.PATH
              FROM   TABL$R_TMC_CTGR CG1
              WHERE  (CG1.PARENT_ID = :Q_ROOT_ID)
                AND  (CG1.FLAG_DELETE <> 1)
              UNION ALL
              SELECT CG2.ID, CG2.PARENT_ID, CG2.NAME, CG2.PATH
              FROM   TABL$R_TMC_CTGR CG2, CGG CG3
              WHERE  (CG2.PARENT_ID = CG3.ID)
                AND  (CG2.FLAG_DELETE <> 1)
            )SELECT C.ID, C.PARENT_ID, C.NAME, C.PATH
             FROM   CGG C
            )T
    INTO   :P_TMC_CTGR_ID, :P_TMC_CTGR_NAME
  DO
    BEGIN
    P_TMC_CTGR_ID_L = :P_TMC_CTGR_ID;
    IF(:P_TMC_CTGR_ID_L = :Q_ROOT_ID)THEN P_TMC_CTGR_ID_L = 0;
    FOR
      SELECT Q.TMC_ID, SUM(Q.QUANT)
      FROM   (SELECT  TQ1.FIRM_ID, TQ1.PLACE_ID, TQ1.TMC_ID, TQ1.QUANT
              FROM    TABL$P_TMC_QUANT TQ1, TABL$R_TMC T1
              WHERE  (:FIRM_IDS  CONTAINING '~'||TQ1.FIRM_ID ||'~')
                AND  (:PLACE_IDS CONTAINING '~'||TQ1.PLACE_ID||'~')
                AND  (T1.ID = TQ1.TMC_ID)
                AND  (T1.TMC_CTGR_ID = :P_TMC_CTGR_ID)
              UNION ALL  -- DEBET
              SELECT  TQD.FIRM_ID, TQD.PLACE_ID, TQD.TMC_ID, ((-1) * TQD.QUANT) AS QUANT
              FROM    TABL$P_TMC_QUANT_MOVE TQD, TABL$R_TMC TD
              WHERE  (:FIRM_IDS  CONTAINING '~'||TQD.FIRM_ID ||'~')
                AND  (:PLACE_IDS CONTAINING '~'||TQD.PLACE_ID||'~')
                AND  (TQD.FLAG_DEBET = 1)
                AND  (TQD.DATE_COMMIT >= :DATE_RPT)
                AND  (TD.ID = TQD.TMC_ID)
                AND  (TD.TMC_CTGR_ID = :P_TMC_CTGR_ID)
              UNION ALL  -- KREDIT
              SELECT TQK.FIRM_ID, TQK.PLACE_ID, TQK.TMC_ID, TQK.QUANT
              FROM    TABL$P_TMC_QUANT_MOVE TQK, TABL$R_TMC TK
              WHERE  (:FIRM_IDS  CONTAINING '~'||TQK.FIRM_ID ||'~')
                AND  (:PLACE_IDS CONTAINING '~'||TQK.PLACE_ID||'~')
                AND  (TQK.FLAG_DEBET = 0)
                AND  (TQK.DATE_COMMIT >= :DATE_RPT)
                AND  (TK.ID = TQK.TMC_ID)
                AND  (TK.TMC_CTGR_ID = :P_TMC_CTGR_ID)
              )Q
      GROUP BY Q.TMC_ID
      INTO    :P_TMC_ID, :P_QUANT
    DO IF(:P_QUANT > 0)THEN
      BEGIN
      P_PRICE = 0;
      SELECT FIRST 1 TMC.NAME, COALESCE(TMC.ARTICLE,''), TMC.BARCODE, COALESCE(TMC.PROBE,'')
            ,(SELECT FIRST 1 COALESCE(C.VALUTE,'') FROM TABL$R_COUNTRIES C WHERE (C.ID = TMC.COUNTRY_ID)) AS VALUTE
            ,COALESCE(TMC.MASSA,0), (TMC.MASSA - TMC.MASSA_NETTO) AS MASSA_INS, TMC.MASSA_NETTO
            ,COALESCE(TMC.LGTH,0), COALESCE(TMC.DIAM,0), TMC.TMC_GROUP_ID, TG.NAME AS TMC_GROUP_NAME
      FROM   TABL$R_TMC TMC, TABL$R_TMC_GROUP TG
      WHERE  (TMC.ID = :P_TMC_ID)
        AND  (TG.ID = TMC.TMC_GROUP_ID)
      INTO   :P_TMC_NAME, :P_TMC_ARTICLE, :P_TMC_BARCODE, :P_TMC_PROBE, :P_VALUTE
            ,:P_TMC_MASSA, :P_TMC_MASSA_INS, :P_TMC_MASSA_NETTO, :P_TMC_LGTH, :P_TMC_DIAM
            ,:P_TMC_GROUP_ID, :P_TMC_GROUP_NAME;
      P_VALUTE      = COALESCE(:P_VALUTE,'');
      P_TMC_ARTICLE = COALESCE(:P_TMC_ARTICLE,'');
      P_TMC_PROBE   = COALESCE(:P_TMC_PROBE,'');
            
      SELECT MAX(P.VALUE_DATE)
      FROM   TABL$R_TMC_P P
      WHERE  (P.TMC_ID      = :P_TMC_ID)
        AND  (P.VALUE_DATE <= :DATE_RPT)
      INTO   :P_TMC_VALUE_DATE;
      SELECT FIRST 1 COALESCE(P.PRICE, 0)
      FROM   TABL$R_TMC_P P
      WHERE  (P.TMC_ID     = :P_TMC_ID)
        AND  (P.VALUE_DATE = :P_TMC_VALUE_DATE)
      INTO   :P_PRICE;

      ASQL001 =
        'INSERT INTO `'||:Q_PREFIX||'product`(`product_id`,`model`,`sku`,`upc`,`ean`,`jan`,`isbn`,`mpn`'||
        ',`location`,`quantity`,`stock_status_id`,`image`,`manufacturer_id`,`shipping`'||
        ',`price`,`points`,`tax_class_id`,`date_available`,`weight`,`weight_class_id`'||
        ',`length`,`width`,`height`,`length_class_id`,`subtract`,`minimum`,`sort_order`'||
        ',`status`,`date_added`,`date_modified`,`viewed`'||
        ')VALUES('||:P_TMC_ID||','''||:P_TMC_ARTICLE||''','''', '''','''','''','''','''''||
        ','''','||REPLACE(CAST(:P_QUANT AS VARCHAR(20)),',','.')||',7,NULL,1,1'||
        ','||REPLACE(CAST(:P_PRICE AS VARCHAR(20)),',','.')||',0,0,'''||
                 LPAD(EXTRACT(YEAR   FROM :DATE_RPT),4,'0')||'-'||
                 LPAD(EXTRACT(MONTH  FROM :DATE_RPT),2,'0')||'-'||
                 LPAD(EXTRACT(DAY    FROM :DATE_RPT),2,'0')||' '||
                 LPAD(EXTRACT(HOUR   FROM :DATE_RPT),2,'0')||':'||
                 LPAD(EXTRACT(MINUTE FROM :DATE_RPT),2,'0')||':'||
                 LPAD(EXTRACT(SECOND FROM :DATE_RPT),2,'0')||''','||REPLACE(CAST(:P_TMC_MASSA AS VARCHAR(20)),',','.')||',2'||
        ','||REPLACE(CAST(:P_TMC_LGTH AS VARCHAR(20)),',','.')||',0,0,2,1,0,'||:P_TMC_ID||
        ',1,'''||
                 LPAD(EXTRACT(YEAR   FROM :DATE_RPT),4,'0')||'-'||
                 LPAD(EXTRACT(MONTH  FROM :DATE_RPT),2,'0')||'-'||
                 LPAD(EXTRACT(DAY    FROM :DATE_RPT),2,'0')||' '||
                 LPAD(EXTRACT(HOUR   FROM :DATE_RPT),2,'0')||':'||
                 LPAD(EXTRACT(MINUTE FROM :DATE_RPT),2,'0')||':'||
                 LPAD(EXTRACT(SECOND FROM :DATE_RPT),2,'0')||''','''||

                 LPAD(EXTRACT(YEAR   FROM :DATE_RPT),4,'0')||'-'||
                 LPAD(EXTRACT(MONTH  FROM :DATE_RPT),2,'0')||'-'||
                 LPAD(EXTRACT(DAY    FROM :DATE_RPT),2,'0')||' '||
                 LPAD(EXTRACT(HOUR   FROM :DATE_RPT),2,'0')||':'||
                 LPAD(EXTRACT(MINUTE FROM :DATE_RPT),2,'0')||':'||
                 LPAD(EXTRACT(SECOND FROM :DATE_RPT),2,'0')||''',0'||
        ')ON DUPLICATE KEY UPDATE `status` = 1, `date_modified` = '''||
                 LPAD(EXTRACT(YEAR   FROM :DATE_RPT),4,'0')||'-'||
                 LPAD(EXTRACT(MONTH  FROM :DATE_RPT),2,'0')||'-'||
                 LPAD(EXTRACT(DAY    FROM :DATE_RPT),2,'0')||' '||
                 LPAD(EXTRACT(HOUR   FROM :DATE_RPT),2,'0')||':'||
                 LPAD(EXTRACT(MINUTE FROM :DATE_RPT),2,'0')||':'||
                 LPAD(EXTRACT(SECOND FROM :DATE_RPT),2,'0')||''' ; ';
      ASQL002 = '';
      FOR
        SELECT E.REC_ID, E.REC_ID_EXTERNAL
        FROM   TABL$_EXCHANGE E
        WHERE  (E.TB_ID = 'TABL$R_COUNTRIES')
          AND  (E.TB_ID_EXTERNAL = '_LANGUAGE')
        INTO   :P_COUNTRY_ID, :P_LANG_ID
      DO
        BEGIN
        P_TMC_CTGR_NAME_L = :P_TMC_CTGR_NAME;
        SELECT FIRST 1 COALESCE(L.NAME, :P_TMC_CTGR_NAME)
        FROM   TABL$_LOCAL L
        WHERE  (L.OBJ_ID = 'TABL$R_TMC_CTGR')
          AND  (L.REC_ID = :P_TMC_CTGR_ID)
          AND  ((L.COUNTRY_ID+0) = :P_COUNTRY_ID)
        INTO   :P_TMC_CTGR_NAME_L;
        P_TMC_CTGR_NAME_L = COALESCE(REPLACE(:P_TMC_CTGR_NAME_L, '''', ''''''),'');
        if(:P_TMC_CTGR_ID = 6)then
          BEGIN
          P_TMC_NAME_L  = :P_TMC_NAME;
          P_TMC_NAME_L2 = :P_TMC_NAME;
          END  
         ELSE
          BEGIN
          P_TMC_NAME_L  = :P_TMC_CTGR_NAME_L||' '||:P_TMC_ARTICLE||' '||:P_VALUTE||' '||:P_TMC_PROBE;
          P_TMC_NAME_L2 = :P_TMC_CTGR_NAME_L||' материал:"'||:P_VALUTE||'", проба:"'||:P_TMC_PROBE||
            '", артикул:"'||:P_TMC_ARTICLE||'" ';
          END
        P_TMC_NAME_L3 = :P_TMC_CTGR_NAME_L||' материал:"'||:P_VALUTE||'", проба:"'||:P_TMC_PROBE||
          '", артикул:"'||:P_TMC_ARTICLE||'" ';
        ASQL002 = :ASQL002||
          'INSERT INTO `'||:Q_PREFIX||'product_description`(`product_id`,`language_id`,`name`'||
          ',`description`,`meta_description`,`meta_keyword`,`tag`'||
          ')VALUES('||:P_TMC_ID||','||:P_LANG_ID||','''||:P_TMC_NAME_L||''''||
          ','''||:P_TMC_NAME_L2||''','''||:P_TMC_NAME_L3||''','''||:P_TMC_NAME_L||''','''' '||
          ')ON DUPLICATE KEY UPDATE '||
            '`name`='''||:P_TMC_NAME_L||''','||
            '`description`='''||:P_TMC_NAME_L2||''','||
            '`meta_description`='''||:P_TMC_NAME_L3||'''; '||ASCII_CHAR(13)||ASCII_CHAR(10);
        END
      ASQL002 = :ASQL002||
        'INSERT INTO `'||:Q_PREFIX||'product_to_category`(`product_id`,`category_id`)'||
          'VALUES('||:P_TMC_ID||','||:P_TMC_CTGR_ID||')ON DUPLICATE KEY UPDATE `category_id` = '||:P_TMC_CTGR_ID||'; '||ASCII_CHAR(13)||ASCII_CHAR(10)||
        'INSERT INTO `'||:Q_PREFIX||'product_to_store`(`product_id`,`store_id`)'||
          'VALUES('||:P_TMC_ID||',0)ON DUPLICATE KEY UPDATE `store_id` = 0;'||ASCII_CHAR(13)||ASCII_CHAR(10)||
        'INSERT INTO `'||:Q_PREFIX||'product_to_layout`(`product_id`,`store_id`,`layout_id`)'||
          'VALUES('||:P_TMC_ID||',0,1)ON DUPLICATE KEY UPDATE `layout_id` = 0; '||ASCII_CHAR(13)||ASCII_CHAR(10);
      SUSPEND;
      END
    END
END
