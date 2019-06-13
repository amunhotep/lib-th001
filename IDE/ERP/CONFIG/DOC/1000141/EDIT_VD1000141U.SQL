UPDATE TABL$D_1000141 SET
   J_ID           = ?J_ID
  ,NAME           = ?NAME
  ,FLAG_DELETE    = ?FLAG_DELETE
  ,TMC_GROUP_ID   = ?TMC_GROUP_ID
  ,TMC_CTGR_ID    = ?TMC_CTGR_ID
  ,DEV_COUNTRY_ID = ?DEV_COUNTRY_ID
  ,BRAND_ID       = ?BRAND_ID
  ,MODELNAME      = ?MODELNAME
  ,SERIAL         = ?SERIAL
  ,YEAR_ID        = ?YEAR_ID
  ,STATEFINE      = ?STATEFINE
  ,COMENT         = ?COMENT
  ,IMG            = ?IMG
  ,PRICE          = ?PRICE
  ,QUANT          = ?QUANT
  ,TOTAL          = ?TOTAL
WHERE (ID = ?ID);
