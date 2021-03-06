EXECUTE BLOCK (
   Q_TYPE_ID         TYPE OF COLUMN TABL$_TB.TYPE_ID = ?PQ_TYPE_ID 
  ,Q_USER_VAR        TYPE OF COLUMN TABL$_USERS.ID   = ?PQ_USER_VAR
)RETURNS ( 
   TYPE_ID           TYPE OF COLUMN TABL$_TB.TYPE_ID 
  ,MAINTB_ID         TYPE OF COLUMN TABL$_TB_COLS.TB_ID
  ,MAIN_BASE_TYPE_ID TYPE OF COLUMN TABL$_TB.BASE_TYPE_ID
  ,MAIN_BUFFER_VAR   TYPE OF COLUMN TABL$_TB.BUFFER_VAR
  ,MAIN_SC_REF       TYPE OF COLUMN TABL$_TB.SC_REF
  ,MAIN_SC_REF_DLG   TYPE OF COLUMN TABL$_TB.SC_REF_DLG
  ,MAIN_SC_ITEM      TYPE OF COLUMN TABL$_TB.SC_ITEM
  ,MAIN_SC_ITEM_DLG  TYPE OF COLUMN TABL$_TB.SC_ITEM_DLG
  ,TB_ID             TYPE OF COLUMN TABL$_TB_COLS.TB_ID 
  ,ID                TYPE OF COLUMN TABL$_TB_COLS.ID 
  ,NAME              TYPE OF COLUMN TABL$_TB_COLS.NAME 
  ,HINT              TYPE OF COLUMN TABL$_TB_COLS.HINT 
  ,FLAG_DELETE       TYPE OF COLUMN TABL$_TB_COLS.FLAG_DELETE 
  ,FIELD_TYPE        TYPE OF COLUMN TABL$_TB_COLS.FIELD_TYPE 
  ,ALIGNMENT         TYPE OF COLUMN TABL$_TB_COLS.ALIGNMENT 
  ,FORMAT            TYPE OF COLUMN TABL$_TB_COLS.FORMAT 
  ,WIDTH             TYPE OF COLUMN TABL$_TB_COLS.WIDTH 
  ,COLOR             TYPE OF COLUMN TABL$_TB_COLS.EDT_LEFT
  ,COL_INDEX         TYPE OF COLUMN TABL$_TB_COLS.COL_INDEX 
  ,ROW_INDEX         TYPE OF COLUMN TABL$_TB_COLS.ROW_INDEX
  ,ORIENTATION       TYPE OF COLUMN TABL$_TB_COLS.ORIENTATION 
  ,PICK_LIST         TYPE OF COLUMN TABL$_TB_COLS.PICK_LIST 
  ,KEY_LIST          TYPE OF COLUMN TABL$_TB_COLS.KEY_LIST 
  ,DEFAULT_VALUE     TYPE OF COLUMN TABL$_TB_COLS.DEFAULT_VALUE 
  ,CALC_SQL          TYPE OF COLUMN TABL$_TB_COLS.CALC_SQL       
  ,EDT_LEFT          TYPE OF COLUMN TABL$_TB_COLS.EDT_LEFT
  ,EDT_TOP           TYPE OF COLUMN TABL$_TB_COLS.EDT_TOP
  ,REF_TABLE         TYPE OF COLUMN TABL$_TB_COLS.REF_TABLE 
  ,REF_FIELD         TYPE OF COLUMN TABL$_TB_COLS.REF_FIELD 
  ,REF_KEYFIELD      TYPE OF COLUMN TABL$_TB_COLS.REF_KEYFIELD 
  ,REF_WHERE         TYPE OF COLUMN TABL$_TB_COLS.REF_WHERE 
  ,REF_WHEREEDIT     TYPE OF COLUMN TABL$_TB_COLS.REF_WHEREEDIT 
  ,REF_BUFFER_VAR    TYPE OF COLUMN TABL$_TB_COLS.REF_FIELD 
  ,REF_SC_REF_DLG    TYPE OF COLUMN TABL$_TB_COLS.REF_WHERE 
  ,REF_SC_ITEM       TYPE OF COLUMN TABL$_TB.SC_ITEM
  ,REF_SC_ITEM_DLG   TYPE OF COLUMN TABL$_TB.SC_ITEM_DLG
  ,SUBKONTO_FIELD    TYPE OF COLUMN TABL$_TB_COLS.SUBKONTO_FIELD
  ,FLAG_FOOTER       TYPE OF COLUMN TABL$_TB_COLS.FLAG_FOOTER
  ,FOOTER_COUNT      TYPE OF COLUMN TABL$_TB_COLS.COL_INDEX
  ,FLAG_ADDITIONAL   TYPE OF COLUMN TABL$_TB_COLS.FLAG_ADDITIONAL 
  ,FLAG_PERIODICAL   TYPE OF COLUMN TABL$_TB_COLS.FLAG_PERIODICAL
  ,FLAG_UPDNULL      TYPE OF COLUMN TABL$_TB_COLS.FLAG_PERIODICAL
  ,EMPTY_VALUE       TYPE OF COLUMN TABL$_TB_COLS.DEFAULT_VALUE
  ,FLAG_UPDDEFAULT   TYPE OF COLUMN TABL$_TB_COLS.FLAG_PERIODICAL
  ,FLAG_GROUPBY      TYPE OF COLUMN TABL$_TB_COLS.FLAG_GROUPBY 
  ,ACCS_FLAG_READ    TYPE OF COLUMN TABL$_TB_COLS.FLAG_DELETE 
  ,ACCS_FLAG_WRITE   TYPE OF COLUMN TABL$_TB_COLS.FLAG_DELETE 
)AS 
  DECLARE VARIABLE Q_TYPE_IDS DOMN$BLOB_TEXT; 
BEGIN 
  TYPE_ID = :Q_TYPE_ID; 
  WITH RECURSIVE TTT AS( 
    SELECT T1.ID, T1.PARENT_ID FROM TABL$_TB_TYPES T1 WHERE (T1.ID = :TYPE_ID) 
    UNION ALL 
    SELECT T2.ID, T2.PARENT_ID FROM TABL$_TB_TYPES T2, TTT T3 WHERE (T2.ID = T3.PARENT_ID) 
  )SELECT '~'||LIST(T.ID,'~')||'~' FROM TTT T INTO :Q_TYPE_IDS; 
  SELECT FIRST 1 TB.ID
  FROM   TABL$_TB TB
  WHERE  (TB.TYPE_ID = 4)
    AND  (TB.BASE_TYPE_ID = TB.TYPE_ID)
    AND  (TB.FLAG_MASTER = 1)
  INTO  :MAINTB_ID;

  SELECT FIRST 1 TBM.BASE_TYPE_ID, TBM.BUFFER_VAR
  FROM   TABL$_TB TBM 
  WHERE  (TBM.ID = :MAINTB_ID)
  INTO   :MAIN_BASE_TYPE_ID, :MAIN_BUFFER_VAR;
  MAIN_SC_REF     = 'DB:CONFIG/DOC/<%OBJECT_TYPE%>/DEFAULT.PS';
  MAIN_SC_REF_DLG = 'DB:CONFIG/DOC/<%OBJECT_TYPE%>/DEFAULT_DLG.PS';
  MAIN_SC_ITEM    = 'DB:CONFIG/DOC/<%OBJECT_TYPE%>/EDIT.PS';

  FOR 
    SELECT TC.TB_ID, TC.ID, TC.NAME, TC.HINT, TC.FLAG_DELETE, TC.FIELD_TYPE, TC.ALIGNMENT, 
           TC.FORMAT,TC.WIDTH,TC.COLOR,TC.COL_INDEX,TC.ROW_INDEX,TC.PICK_LIST,TC.KEY_LIST,TC.DEFAULT_VALUE,
           TC.REF_TABLE,TC.REF_FIELD,TC.REF_KEYFIELD,TC.REF_WHERE,TC.REF_WHEREEDIT,TC.FLAG_FOOTER, 
           TC.FLAG_ADDITIONAL, TC.FLAG_PERIODICAL, TC.DEFAULT_VALUE, TC.ORIENTATION,
           TC.CALC_SQL, TC.FLAG_GROUPBY, TC.EDT_LEFT, TC.EDT_TOP, TC.FLAG_UPDNULL, TC.EMPTY_VALUE, TC.FLAG_UPDDEFAULT, TC.SUBKONTO_FIELD 
    FROM   TABL$_TB TB, TABL$_TB_COLS TC 
    WHERE  (:Q_TYPE_IDS CONTAINING '~'||TB.TYPE_ID||'~')
      AND  (TB.FLAG_MASTER = 1) 
      AND  (TC.TB_ID = TB.ID) 
      AND  (NOT(EXISTS(
               SELECT E.OBJTYPE
               FROM   TABL$_TB_COLS_EXCLUDE E
               WHERE  (E.TB_ID   = TC.TB_ID)
                 AND  (E.TC_ID   = TC.ID)
                 AND  (E.OBJTYPE = 40)
                 AND  (E.TYPE_ID = :TYPE_ID)
            )))
    ORDER BY TC.FLAG_PERIODICAL, TC.COL_INDEX
    INTO   :TB_ID, :ID, :NAME, :HINT, :FLAG_DELETE, :FIELD_TYPE, :ALIGNMENT, 
           :FORMAT, :WIDTH, :COLOR, :COL_INDEX, :ROW_INDEX, :PICK_LIST, :KEY_LIST, :DEFAULT_VALUE,
           :REF_TABLE, :REF_FIELD, :REF_KEYFIELD, :REF_WHERE, :REF_WHEREEDIT, :FLAG_FOOTER, 
           :FLAG_ADDITIONAL, :FLAG_PERIODICAL, :DEFAULT_VALUE, :ORIENTATION,
           :CALC_SQL, :FLAG_GROUPBY, :EDT_LEFT, :EDT_TOP, :FLAG_UPDNULL, :EMPTY_VALUE, :FLAG_UPDDEFAULT, :SUBKONTO_FIELD 
  DO 
/*  
    IF(EXISTS(
      SELECT R.RDB$FIELD_ID
      FROM   RDB$RELATION_FIELDS R
      WHERE  (TRIM(R.RDB$RELATION_NAME) = :TB_ID)
        AND  (TRIM(R.RDB$FIELD_NAME)    = :ID)
    ) OR (TRIM(:CALC_SQL) <> ''))THEN
*/
      BEGIN 
      ACCS_FLAG_READ  = 0; 
      ACCS_FLAG_WRITE = 0; 
      FOOTER_COUNT    = 0;
      REF_BUFFER_VAR  = '' ; 
      REF_SC_REF_DLG  = ''; 
      REF_SC_ITEM     = '';
      REF_SC_ITEM_DLG = '';
      IF(TRIM(:REF_TABLE) <> '')THEN 
        BEGIN 
        SELECT FIRST 1 TB1.BUFFER_VAR, TB1.SC_REF_DLG, TB1.SC_ITEM, TB1.SC_ITEM_DLG 
        FROM   TABL$_TB TB1 
        WHERE  (TB1.ID = :REF_TABLE) 
        INTO   :REF_BUFFER_VAR, :REF_SC_REF_DLG, :REF_SC_ITEM, :REF_SC_ITEM_DLG; 
        END 
      IF(:FLAG_FOOTER <> 0)THEN
        BEGIN
        SELECT COUNT(TF.ID)
        FROM   TABL$_TB_COLS_FOOTERS TF
        WHERE  (TF.TB_ID = :TB_ID)
          AND  (TF.TC_ID = :ID ) 
        INTO  :FOOTER_COUNT;
        END   
      ACCS_FLAG_READ  = 0;
      ACCS_FLAG_WRITE = 0;
      SELECT COALESCE(COUNT(TC.ID),0)
      FROM   TABL$_TB_COLS TC, TABL$_USERS_ACCS UA
      WHERE  (TC.TB_ID   = :TB_ID)
        AND  (TC.ID      = :ID)
        AND  (UA.USER_ID = RDB$GET_CONTEXT('USER_SESSION', :Q_USER_VAR))
        AND  (TC.ACCSS CONTAINING '~'||UA.ROLE_ID||'~')
      INTO   :ACCS_FLAG_READ;
      SELECT COALESCE(COUNT(TC.ID),0)
      FROM   TABL$_TB_COLS TC, TABL$_USERS_ACCS UA
      WHERE  (TC.TB_ID   = :TB_ID)
        AND  (TC.ID      = :ID)
        AND  (UA.USER_ID = RDB$GET_CONTEXT('USER_SESSION', :Q_USER_VAR))
        AND  (TC.ACCSSW CONTAINING '~'||UA.ROLE_ID||'~')
      INTO   :ACCS_FLAG_WRITE;
      SUSPEND; 
      END 
END
