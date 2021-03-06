EXECUTE BLOCK (
   Q_OBJ_ID      TYPE OF COLUMN TABL$_TB.ID           = ?OBJ_ID
  ,Q_OBJ_TYPE    TYPE OF COLUMN TABL$_TB.BASE_TYPE_ID = ?OBJ_TYPE
  ,Q_TB_CHILD_ID TYPE OF COLUMN TABL$_TB.ID           = ?TB_CHILD_ID
)RETURNS (
   OBJ_ID             TYPE OF COLUMN TABL$_TB.ID
  ,OBJ_TYPE           TYPE OF COLUMN TABL$_TB.BASE_TYPE_ID
  ,TB_ID              TYPE OF COLUMN TABL$_TB_CHILDS.TB_ID
  ,TB_CHILD_ID        TYPE OF COLUMN TABL$_TB_CHILDS.TB_CHILD_ID
  ,TB_CHILD_NAME      TYPE OF COLUMN TABL$_TB.NAME
  ,TB_CHILD_TYPE_ID   TYPE OF COLUMN TABL$_TB.BASE_TYPE_ID
  ,TB_CHILD_TYPE_NAME TYPE OF COLUMN TABL$_TB_TYPES.NAME2
  ,INDEX_FIELDS       TYPE OF COLUMN TABL$_TB_CHILDS.INDEX_FIELDS
  ,KEY_FIELDS         TYPE OF COLUMN TABL$_TB_CHILDS.KEY_FIELDS
  ,CHILD_TYPE         TYPE OF COLUMN TABL$_TB_CHILDS.CHILD_TYPE
  ,FLAG_SHOW          TYPE OF COLUMN TABL$_TB_CHILDS.FLAG_SHOW
  ,TYPE_ID            TYPE OF COLUMN TABL$_TB_CHILDS.TYPE_ID
  ,TYPE_NAME          TYPE OF COLUMN TABL$_TB_TYPES.NAME
)
AS
BEGIN
  OBJ_ID   = :Q_OBJ_ID;
  OBJ_TYPE = :Q_OBJ_TYPE;
  SELECT FIRST 1 TC.TB_ID, TC.TB_CHILD_ID, TC.INDEX_FIELDS, TC.KEY_FIELDS, TC.CHILD_TYPE, TC.FLAG_SHOW, TC.TYPE_ID
  FROM     TABL$_TB_CHILDS TC
  WHERE    (TC.TB_ID = :OBJ_ID)
    AND    (TC.TB_CHILD_ID = :Q_TB_CHILD_ID)
  INTO     :TB_ID, :TB_CHILD_ID, :INDEX_FIELDS, :KEY_FIELDS, :CHILD_TYPE, :FLAG_SHOW, :TYPE_ID;

  TYPE_NAME = ''; TB_CHILD_NAME = ''; TB_CHILD_TYPE_NAME = '';
  SELECT FIRST 1 T2.NAME, T2.BASE_TYPE_ID
  FROM   TABL$_TB T2
  WHERE  (T2.ID = :TB_CHILD_ID)
  INTO   :TB_CHILD_NAME, :TB_CHILD_TYPE_ID;
  SELECT FIRST 1 T1.NAME  FROM TABL$_TB_TYPES T1 WHERE(T1.ID = :TYPE_ID         )INTO :TYPE_NAME;
  SELECT FIRST 1 T2.NAME2 FROM TABL$_TB_TYPES T2 WHERE(T2.ID = :TB_CHILD_TYPE_ID)INTO :TB_CHILD_TYPE_NAME;
  SUSPEND;
END
