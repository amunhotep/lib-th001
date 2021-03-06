SELECT MA.MON$ATTACHMENT_ID, MA.MON$SERVER_PID,
       (SELECT FIRST 1 TP.RDB$TYPE_NAME 
        FROM   RDB$TYPES TP 
        WHERE  (TP.RDB$FIELD_NAME = 'MON$STATE') 
          AND  (TP.RDB$TYPE = MA.MON$STATE) 
       ) AS MON$STATE, MA.MON$ATTACHMENT_NAME, 
       MA.MON$USER, MA.MON$ROLE, MA.MON$REMOTE_PROTOCOL, MA.MON$REMOTE_ADDRESS, 
       MA.MON$REMOTE_PID, MA.MON$CHARACTER_SET_ID, MA.MON$TIMESTAMP, 
       MA.MON$GARBAGE_COLLECTION, MA.MON$REMOTE_PROCESS, MA.MON$STAT_ID 
      ,(SELECT FIRST 1 MCA.MON$VARIABLE_VALUE 
        FROM   MON$CONTEXT_VARIABLES MCA 
        WHERE  (MCA.MON$ATTACHMENT_ID = MA.MON$ATTACHMENT_ID) 
          AND  (MCA.MON$VARIABLE_NAME = ?Q_USER_VAR)
      )AS DATABASE_USER 
      ,(SELECT FIRST 1 MCA.MON$VARIABLE_VALUE 
        FROM   MON$CONTEXT_VARIABLES MCA 
        WHERE  (MCA.MON$ATTACHMENT_ID = MA.MON$ATTACHMENT_ID) 
          AND  (MCA.MON$VARIABLE_NAME = ?Q_USER_VARLOCAL)
      )AS DATABASE_LOCAL 
      ,(SELECT FIRST 1 COALESCE(F.NAME, '')
        FROM   MON$CONTEXT_VARIABLES MCA1, TABL$R_FILIALS F 
        WHERE  (MCA1.MON$ATTACHMENT_ID = MA.MON$ATTACHMENT_ID) 
          AND  (MCA1.MON$VARIABLE_NAME = ?Q_USER_VARFILIAL)
          AND  (F.ID = MCA1.MON$VARIABLE_VALUE) 
      )AS FILIAL_NAME 
      ,(SELECT FIRST 1 COALESCE(WRK.NAME, '')
        FROM   MON$CONTEXT_VARIABLES MCA1, TABL$R_WRK WRK 
        WHERE  (MCA1.MON$ATTACHMENT_ID = MA.MON$ATTACHMENT_ID) 
          AND  (MCA1.MON$VARIABLE_NAME = ?Q_USER_VAR)
          AND  (TRIM(UPPER(WRK.USER_NAME)) = MCA1.MON$VARIABLE_VALUE) 
      )AS WRK_NAME 
      ,(SELECT FIRST 1 COALESCE(C.LANG_NAME, C.NAME)
        FROM   MON$CONTEXT_VARIABLES MCA1, TABL$R_COUNTRIES C 
        WHERE  (MCA1.MON$ATTACHMENT_ID = MA.MON$ATTACHMENT_ID) 
          AND  (MCA1.MON$VARIABLE_NAME = ?Q_USER_VARLOCAL)
          AND  (C.ID = MCA1.MON$VARIABLE_VALUE) 
      )AS COUNTRY_NAME 
      ,(SELECT FIRST 1 COALESCE(MCA.MON$VARIABLE_VALUE, '')
        FROM   MON$CONTEXT_VARIABLES MCA 
        WHERE  (MCA.MON$ATTACHMENT_ID = MA.MON$ATTACHMENT_ID) 
          AND  (MCA.MON$VARIABLE_NAME = ?Q_ERP_VERSION)
      )AS AMUNHOTEP_VERSION 
      ,(SELECT FIRST 1 CHS.RDB$CHARACTER_SET_NAME 
        FROM   RDB$CHARACTER_SETS CHS 
        WHERE  (CHS.RDB$CHARACTER_SET_ID = MA.MON$CHARACTER_SET_ID) 
      )AS RDB$CHARACTER_SET_NAME 
     ,(SELECT FIRST 1 '1' AS CONNECTION_FLAG FROM RDB$DATABASE DB WHERE (MA.MON$ATTACHMENT_ID = CURRENT_CONNECTION))
     ,(SELECT FIRST 1 RDB$GET_CONTEXT('SYSTEM','ENGINE_VERSION') AS ENGINE_VERSION FROM RDB$DATABASE) 
FROM MON$ATTACHMENTS MA 
