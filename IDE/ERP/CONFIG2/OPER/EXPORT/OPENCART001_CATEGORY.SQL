EXECUTE BLOCK (
  Q_PREFIX   TYPE OF COLUMN TABL$J_4.DOCSTR    = ?PREFIX
 ,Q_ROOT_ID  TYPE OF COLUMN TABL$R_TMC_CTGR.ID = ?ROOT_ID
)RETURNS(
  ASQL001   TYPE OF COLUMN TABL$J_4.DOCSTR
 ,ASQL002   TYPE OF COLUMN TABL$J_4.DOCSTR
 ,ID        TYPE OF COLUMN TABL$R_TMC_CTGR.ID
 ,PARENT_ID TYPE OF COLUMN TABL$R_TMC_CTGR.PARENT_ID
 ,NAME      TYPE OF COLUMN TABL$R_TMC_CTGR.NAME
 ,PATH      TYPE OF COLUMN TABL$R_TMC_CTGR.NAME
) AS
  DECLARE VARIABLE P_PARENT_ID  TYPE OF COLUMN TABL$R_TMC_CTGR.PARENT_ID;
  DECLARE VARIABLE P_NAME_CTG   TYPE OF COLUMN TABL$R_TMC_CTGR.NAME;
  DECLARE VARIABLE P_LANG_ID    TYPE OF COLUMN TABL$R_COUNTRIES.ID;
  DECLARE VARIABLE P_COUNTRY_ID TYPE OF COLUMN TABL$R_COUNTRIES.ID;
  DECLARE VARIABLE P_NAME       TYPE OF COLUMN TABL$_LOCAL.NAME;
BEGIN
/*
  ASQL001 = 
    'delete from `'||:Q_PREFIX||'category_description`; '||ASCII_CHAR(13)||ASCII_CHAR(10)||
    'delete from `'||:Q_PREFIX||'category_to_layout`; '||ASCII_CHAR(13)||ASCII_CHAR(10)||
    'delete from `'||:Q_PREFIX||'category_to_store`; '||ASCII_CHAR(13)||ASCII_CHAR(10);
  ASQL002 = 
    'delete from `'||:Q_PREFIX||'category`; '||ASCII_CHAR(13)||ASCII_CHAR(10);
  SUSPEND;
*/
  FOR
    SELECT T.ID, T.PARENT_ID, T.NAME, T.PATH
    FROM   (WITH RECURSIVE CGG AS(
              SELECT CG1.ID, CG1.PARENT_ID, CG1.NAME, CG1.NAME AS PATH
              FROM   TABL$R_TMC_CTGR CG1
              WHERE  (CG1.PARENT_ID = :Q_ROOT_ID)
                AND  (CG1.FLAG_DELETE <> 1)
              UNION ALL
              SELECT CG2.ID, CG2.PARENT_ID, CG2.NAME, (CG3.PATH||' / '||CG2.NAME) AS PATH
              FROM   TABL$R_TMC_CTGR CG2, CGG CG3
              WHERE  (CG2.PARENT_ID = CG3.ID)
                AND  (CG2.FLAG_DELETE <> 1)
            )SELECT C.ID, C.PARENT_ID, C.NAME, C.PATH
             FROM   CGG C
            )T
    INTO   :ID, :PARENT_ID, :NAME, :PATH
  DO
    BEGIN
    IF(:PARENT_ID = :Q_ROOT_ID)THEN PARENT_ID = 0;
    ASQL001 = 
      /* '---- '||:ID||'. '||:PATH||' '||ASCII_CHAR(13)||ASCII_CHAR(10)|| */
      'INSERT INTO `'||:Q_PREFIX||'category`(`category_id`,`image`,`parent_id`,`top`,`column`,`sort_order`,`status`,`date_added`,`date_modified`)'||
        'VALUES('||:ID||', NULL, '||:PARENT_ID||',1,2,'||:ID||',1,'''||
                 LPAD(EXTRACT(YEAR   FROM CURRENT_TIMESTAMP),4,'0')||'-'||
                 LPAD(EXTRACT(MONTH  FROM CURRENT_TIMESTAMP),2,'0')||'-'||
                 LPAD(EXTRACT(DAY    FROM CURRENT_TIMESTAMP),2,'0')||' '||
                 LPAD(EXTRACT(HOUR   FROM CURRENT_TIMESTAMP),2,'0')||':'||
                 LPAD(EXTRACT(MINUTE FROM CURRENT_TIMESTAMP),2,'0')||':'||
                 LPAD(EXTRACT(SECOND FROM CURRENT_TIMESTAMP),2,'0')||''','''||

                 LPAD(EXTRACT(YEAR   FROM CURRENT_TIMESTAMP),4,'0')||'-'||
                 LPAD(EXTRACT(MONTH  FROM CURRENT_TIMESTAMP),2,'0')||'-'||
                 LPAD(EXTRACT(DAY    FROM CURRENT_TIMESTAMP),2,'0')||' '||
                 LPAD(EXTRACT(HOUR   FROM CURRENT_TIMESTAMP),2,'0')||':'||
                 LPAD(EXTRACT(MINUTE FROM CURRENT_TIMESTAMP),2,'0')||':'||
                 LPAD(EXTRACT(SECOND FROM CURRENT_TIMESTAMP),2,'0')||''')'||
        'ON DUPLICATE KEY UPDATE `date_modified` = '''||
                 LPAD(EXTRACT(YEAR   FROM CURRENT_TIMESTAMP),4,'0')||'-'||
                 LPAD(EXTRACT(MONTH  FROM CURRENT_TIMESTAMP),2,'0')||'-'||
                 LPAD(EXTRACT(DAY    FROM CURRENT_TIMESTAMP),2,'0')||' '||
                 LPAD(EXTRACT(HOUR   FROM CURRENT_TIMESTAMP),2,'0')||':'||
                 LPAD(EXTRACT(MINUTE FROM CURRENT_TIMESTAMP),2,'0')||':'||
                 LPAD(EXTRACT(SECOND FROM CURRENT_TIMESTAMP),2,'0')||''' ; ';
    ASQL002 = '';
    FOR
      SELECT E.REC_ID, E.REC_ID_EXTERNAL
      FROM   TABL$_EXCHANGE E
      WHERE  (E.TB_ID = 'TABL$R_COUNTRIES')
        AND  (E.TB_ID_EXTERNAL = '_LANGUAGE')
      INTO   :P_COUNTRY_ID, :P_LANG_ID
    DO
      BEGIN
      P_NAME = :NAME;
      SELECT FIRST 1 COALESCE(L.NAME, :NAME)
      FROM   TABL$_LOCAL L
      WHERE  (L.OBJ_ID = 'TABL$R_TMC_CTGR')
        AND  (L.REC_ID = :ID)
        AND  ((L.COUNTRY_ID+0) = :P_COUNTRY_ID)
      INTO   :P_NAME;
      P_NAME = REPLACE(:P_NAME, '''', '''''');
      PATH = :P_NAME;
      P_PARENT_ID = :ID;
      WHILE(:P_PARENT_ID <> :Q_ROOT_ID)DO
        BEGIN
        SELECT FIRST 1 COALESCE(CC.PARENT_ID, :Q_ROOT_ID)
        FROM   TABL$R_TMC_CTGR CC
        WHERE  (CC.ID = :P_PARENT_ID)
        INTO   :P_PARENT_ID;
        P_NAME_CTG = '';
        SELECT FIRST 1 COALESCE(CC1.NAME, '')
        FROM   TABL$R_TMC_CTGR CC1
        WHERE  (CC1.ID = :P_PARENT_ID)
        INTO   :P_NAME_CTG;
        SELECT FIRST 1 COALESCE(L.NAME, :P_NAME_CTG)
        FROM   TABL$_LOCAL L
        WHERE  (L.OBJ_ID = 'TABL$R_TMC_CTGR')
          AND  (L.REC_ID = :P_PARENT_ID)
          AND  ((L.COUNTRY_ID+0) = :P_COUNTRY_ID)
        INTO   :P_NAME_CTG;
        PATH = :P_NAME_CTG||'&nbsp;/&nbsp;'||:PATH;
        END
      ASQL002 = :ASQL002||
        'INSERT INTO `'||:Q_PREFIX||'category_description`(`category_id`,`language_id`,`name`,`description`,`meta_description`,`meta_keyword`)'||
          'VALUES('||:ID||', '||:P_LANG_ID||','''||:P_NAME||''','''||:PATH||''','''||:PATH||''','''||REPLACE(:PATH,'->',', ')||''')'||
          'ON DUPLICATE KEY UPDATE `name`='''||:P_NAME||''',`description`='''||:PATH||''',`meta_description`='''||:PATH||'''; '||ASCII_CHAR(13)||ASCII_CHAR(10);
      END
    ASQL002 = :ASQL002||
      'INSERT INTO `'||:Q_PREFIX||'category_to_layout`(`category_id`,`store_id`,`layout_id`)'||
        'VALUES('||:ID||',0,1)ON DUPLICATE KEY UPDATE `layout_id` = 0;'||ASCII_CHAR(13)||ASCII_CHAR(10)||
      'INSERT INTO `'||:Q_PREFIX||'category_to_store`(`category_id`,`store_id`)'||
        'VALUES('||:ID||',0)ON DUPLICATE KEY UPDATE `store_id` = 0;'||ASCII_CHAR(13)||ASCII_CHAR(10);
    SUSPEND;
    END
END
