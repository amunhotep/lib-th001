EXECUTE BLOCK (
   Q_FIRM_IDS   TYPE OF COLUMN TABL$J_4.DOCSTR      = ?FIRM_IDS
  ,Q_PLACE_IDS  TYPE OF COLUMN TABL$J_4.DOCSTR      = ?PLACE_IDS
  ,Q_DATE       TYPE OF COLUMN TABL$J_4.DATE_COMMIT = ?DATE_FROM
  ,Q_PARTY      TYPE OF COLUMN TABL$J_4.FLAG_COMMIT = ?CHECK_PARTY
  ,Q_SUMM       TYPE OF COLUMN TABL$J_4.FLAG_COMMIT = ?CHECK_SUMM
  ,Q_ZERO       TYPE OF COLUMN TABL$J_4.FLAG_COMMIT = ?CHECK_ZERO
)RETURNS (
   DATE_RPT                  TYPE OF COLUMN TABL$J_4.DATE_COMMIT
  ,FLAG_PARTY                TYPE OF COLUMN TABL$J_4.FLAG_COMMIT
  ,FLAG_SUMM                 TYPE OF COLUMN TABL$J_4.FLAG_COMMIT
  ,FIRM_IDS                  TYPE OF COLUMN TABL$J_4.DOCSTR
  ,PLACE_IDS                 TYPE OF COLUMN TABL$J_4.DOCSTR
  ,FIRM_ID                   TYPE OF COLUMN TABL$R_FIRMS.ID
  ,FIRM_NAME                 TYPE OF COLUMN TABL$R_FIRMS.NAME
  ,PLACE_ID                  TYPE OF COLUMN TABL$R_PLACES.ID
  ,PLACE_NAME                TYPE OF COLUMN TABL$R_PLACES.NAME
  ,IN_CS_ID                  TYPE OF COLUMN TABL$R_CS.ID
  ,IN_CS_NAME                TYPE OF COLUMN TABL$R_CS.NAME
  ,IN_CS_INN                 TYPE OF COLUMN TABL$R_CS.INN
  ,TMC_GROUP_ID              TYPE OF COLUMN TABL$R_TMC_GROUP.ID
  ,TMC_GROUP_NAME            TYPE OF COLUMN TABL$R_TMC_GROUP.NAME
  ,TMC_CTGR_ID               TYPE OF COLUMN TABL$R_TMC.TMC_CTGR_ID
  ,TMC_CTGR_NAME             TYPE OF COLUMN TABL$R_TMC_CTGR.NAME
  ,TMC_CTGR_PATH             TYPE OF COLUMN TABL$R_TMC_CTGR.PATH
  ,TMC_ID                    TYPE OF COLUMN TABL$R_TMC.ID
  ,TMC_LIST_ID               TYPE OF COLUMN TABL$R_TMC.TMC_LIST_ID
  ,TMC_NAME                  TYPE OF COLUMN TABL$R_TMC.NAME
  ,TMC_ARTICLE               TYPE OF COLUMN TABL$R_TMC.ARTICLE
  ,TMC_BARCODE               TYPE OF COLUMN TABL$R_TMC.BARCODE
  ,TMC_NUMSHOW               TYPE OF COLUMN TABL$R_TMC.NUMSHOW
  ,TMC_VEDCODE               TYPE OF COLUMN TABL$R_TMC.VEDCODE
  ,COUNTRY_ID                TYPE OF COLUMN TABL$R_TMC.COUNTRY_ID
  ,VALUTE                    TYPE OF COLUMN TABL$R_COUNTRIES.VALUTE
  ,TMC_PROBE                 TYPE OF COLUMN TABL$R_TMC.PROBE
  ,TMC_MASSA                 TYPE OF COLUMN TABL$R_TMC.MASSA
  ,TMC_MASSA_INS             TYPE OF COLUMN TABL$R_TMC.MASSA
  ,TMC_MASSA_NETTO           TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO
  ,TMC_MASSA_                TYPE OF COLUMN TABL$R_TMC.MASSA
  ,TMC_MASSA_INS_            TYPE OF COLUMN TABL$R_TMC.MASSA
  ,TMC_MASSA_NETTO_          TYPE OF COLUMN TABL$R_TMC.MASSA_NETTO
  ,TMC_LGTH                  TYPE OF COLUMN TABL$R_TMC.LGTH
  ,TMC_DIAM                  TYPE OF COLUMN TABL$R_TMC.DIAM
  ,TMC_EDIZM_ID              TYPE OF COLUMN TABL$R_TMC.EDIZM_ID
  ,TMC_EDIZM_NAME            TYPE OF COLUMN TABL$R_EDIZM.NAME
  ,TMC_EDIZM_SHORT_NAME      TYPE OF COLUMN TABL$R_EDIZM.SHORT_NAME
  ,TMC_BRAND_ID              TYPE OF COLUMN TABL$R_TMC.TMC_BRAND_ID
  ,TMC_BRAND_NAME            TYPE OF COLUMN TABL$R_TMC_BRANDS.NAME
  ,TMC_DEV_BRAND_ID          TYPE OF COLUMN TABL$R_TMC.DEV_TMC_BRAND_ID
  ,TMC_DEV_BRAND_NAME        TYPE OF COLUMN TABL$R_TMC_BRANDS.NAME
  ,TMC_TYPE_ID               TYPE OF COLUMN TABL$R_TMC.TMC_TYPE_ID
  ,TMC_TYPE_NAME             TYPE OF COLUMN TABL$R_TMC_TYPES.NAME
  ,PRICE                     TYPE OF COLUMN TABL$P_TMCQUANT.PRICE
  ,QUANT                     TYPE OF COLUMN TABL$P_TMCQUANT.QUANT
  ,TOTAL                     TYPE OF COLUMN TABL$P_TMCQUANT.TOTAL
  ,PRICE_IN                  TYPE OF COLUMN TABL$P_TMCQUANT.PRICE_IN
  ,QUANT_IN                  TYPE OF COLUMN TABL$P_TMCQUANT.QUANT_IN
  ,TOTAL_IN                  TYPE OF COLUMN TABL$P_TMCQUANT.TOTAL_IN
  ,TOTAL_IN_CURR             TYPE OF COLUMN TABL$P_TMCQUANT.TOTAL_IN
  ,J_ID                      TYPE OF COLUMN TABL$J_4.ID
  ,D_ID                      TYPE OF COLUMN TABL$J_4.ID
  ,J_TYPE_ID                 TYPE OF COLUMN TABL$J_4.TYPE_ID
  ,J_TYPE_NAME               TYPE OF COLUMN TABL$_TB_DOCS.NAME
  ,J_TYPE_DOCNUMBERSTR       TYPE OF COLUMN TABL$J_4.DOCNUMBERSTR
  ,J_TYPE_DATE_COMMIT        TYPE OF COLUMN TABL$J_4.DATE_COMMIT
  ,COLOR_BGR                 TYPE OF COLUMN TABL$_TB_DOCS.COLOR_BGR
  ,COLOR_FRG                 TYPE OF COLUMN TABL$_TB_DOCS.COLOR_FRG
)
AS
BEGIN
  DATE_RPT   = :Q_DATE;
  FIRM_IDS   = :Q_FIRM_IDS;
  PLACE_IDS  = :Q_PLACE_IDS;
  FLAG_PARTY = :Q_PARTY;
  FLAG_SUMM  = :Q_SUMM;
  FOR
    SELECT T1.FIRM_ID, T1.PLACE_ID, T1.TMC_ID, T1.J_ID, T1.D_ID
          ,T1.PRICE, T1.PRICE_IN, COALESCE(SUM(T1.QUANT_IN),0)
          ,COALESCE(SUM(T1.QUANT_IN - T1.QUANT_K),0) AS QUANT
    FROM   (SELECT Q.FIRM_ID, Q.PLACE_ID, Q.TMC_ID, 0 AS J_ID, 0 AS D_ID
                  ,Q.PRICE, Q.PRICE_IN, Q.QUANT_IN
                  ,(SELECT COALESCE(SUM(K.QUANT),0)
                    FROM   TABL$P_TMCQUANT K
                    WHERE  (K.PARENT_ID = Q.ID)
                      AND  (K.FLAG_DEBET = 0)
                      AND  (K.DATE_COMMIT <= :DATE_RPT)
                    )AS QUANT_K
            FROM   TABL$P_TMCQUANT Q
            WHERE  (Q.FLAG_DEBET = 1)
              AND  (:FIRM_IDS  CONTAINING '~'||Q.FIRM_ID ||'~')
              AND  (:PLACE_IDS CONTAINING '~'||Q.PLACE_ID||'~')
              AND  (Q.DATE_COMMIT <= :DATE_RPT)
           )T1
    GROUP BY 1,2,3,4,5,6,7
    INTO    :FIRM_ID, :PLACE_ID, :TMC_ID, :J_ID, :D_ID
           ,:PRICE, :PRICE_IN, :QUANT_IN, :QUANT
  DO
    BEGIN
    TOTAL            = :PRICE    * :QUANT;
    TOTAL_IN         = :PRICE_IN * :QUANT_IN;
    TOTAL_IN_CURR    = :PRICE_IN * :QUANT;
    SELECT FIRST 1 F.NAME FROM TABL$R_FIRMS  F WHERE(F.ID = :FIRM_ID )INTO :FIRM_NAME;
    SELECT FIRST 1 P.NAME FROM TABL$R_PLACES P WHERE(P.ID = :PLACE_ID)INTO :PLACE_NAME;
    IN_CS_ID   = 0;
    IN_CS_NAME = '';
    IN_CS_INN  = '';
    SELECT FIRST 1 COALESCE(J14.CS_ID,0)
    FROM   TABL$J_1000014 J14
    WHERE  (J14.J_ID = :J_ID)
    INTO   :IN_CS_ID;
    IF(:IN_CS_ID = 0)THEN
      BEGIN
      SELECT FIRST 1 F.CS_ID, COALESCE(C.NAME,''), COALESCE(C.INN,'')
      FROM   TABL$R_FIRMS F, TABL$R_CS C
      WHERE  (F.ID = :FIRM_ID)
        AND  (C.ID = F.CS_ID)
      INTO   :IN_CS_ID, :IN_CS_NAME, :IN_CS_INN;
      END
     ELSE
      BEGIN
      SELECT FIRST 1 COALESCE(C.NAME,''), COALESCE(C.INN,'')
      FROM   TABL$R_CS C
      WHERE  (C.ID = :IN_CS_ID)
      INTO   :IN_CS_NAME, :IN_CS_INN;
      END
    SELECT FIRST 1 TMC.TMC_LIST_ID, TMC.NAME, TMC.ARTICLE, TMC.NUMSHOW, TMC.BARCODE, TMC.VEDCODE, TMC.COUNTRY_ID, TMC.PROBE
          ,(SELECT FIRST 1 C.VALUTE FROM TABL$R_COUNTRIES C WHERE (C.ID = TMC.COUNTRY_ID)) AS VALUTE
          ,TMC.MASSA, (TMC.MASSA - TMC.MASSA_NETTO) AS MASSA_INS, TMC.MASSA_NETTO, TMC.LGTH, TMC.DIAM
          ,TMC.TMC_GROUP_ID, TG.NAME AS TMC_GROUP_NAME
          ,TMC.TMC_CTGR_ID, CG.NAME, CG.PATH
          ,TMC.EDIZM_ID, ED.NAME, ED.SHORT_NAME
          ,TMC.TMC_BRAND_ID, B1.NAME, TMC.DEV_TMC_BRAND_ID, B2.NAME
          ,TMC.TMC_TYPE_ID, TT.NAME
    FROM   TABL$R_TMC TMC, TABL$R_TMC_TYPES TT, TABL$R_TMC_GROUP TG, TABL$R_TMC_CTGR CG
          ,TABL$R_EDIZM ED, TABL$R_TMC_BRANDS B1, TABL$R_TMC_BRANDS B2
    WHERE  (TMC.ID = :TMC_ID)
      AND  (TT.ID = TMC.TMC_TYPE_ID)
      AND  (TG.ID = TMC.TMC_GROUP_ID)
      AND  (CG.ID = TMC.TMC_CTGR_ID)
      AND  (ED.ID = TMC.EDIZM_ID)
      AND  (B1.ID = TMC.TMC_BRAND_ID)
      AND  (B2.ID = TMC.DEV_TMC_BRAND_ID)
    INTO   :TMC_LIST_ID, :TMC_NAME, :TMC_ARTICLE, :TMC_NUMSHOW, :TMC_BARCODE, :TMC_VEDCODE, :COUNTRY_ID, :TMC_PROBE
          ,:VALUTE, :TMC_MASSA, :TMC_MASSA_INS, :TMC_MASSA_NETTO, :TMC_LGTH, :TMC_DIAM
          ,:TMC_GROUP_ID, :TMC_GROUP_NAME
          ,:TMC_CTGR_ID, :TMC_CTGR_NAME, :TMC_CTGR_PATH
          ,:TMC_EDIZM_ID, :TMC_EDIZM_NAME, :TMC_EDIZM_SHORT_NAME
          ,:TMC_BRAND_ID, :TMC_BRAND_NAME, :TMC_DEV_BRAND_ID, :TMC_DEV_BRAND_NAME
          ,:TMC_TYPE_ID, :TMC_TYPE_NAME
          ;
    TMC_MASSA_       = :TMC_MASSA       * :QUANT;
    TMC_MASSA_INS_   = :TMC_MASSA_INS   * :QUANT;
    TMC_MASSA_NETTO_ = :TMC_MASSA_NETTO * :QUANT;

    J_TYPE_ID           = 0;
    J_TYPE_NAME         = '';
    J_TYPE_DOCNUMBERSTR = '';
    J_TYPE_DATE_COMMIT  = :DATE_RPT;
    COLOR_BGR           = 0XFFF0F0;
    COLOR_FRG           = 0X000000;
    IF(:J_ID <> 0)THEN
      BEGIN
      SELECT FIRST 1 J.TYPE_ID, DD.NAME, J.DOCNUMBERSTR
            ,J.DATE_COMMIT, DD.COLOR_FRG, DD.COLOR_BGR
      FROM   TABL$J_4 J, TABL$_TB_DOCS DD
      WHERE  (J.ID  = :J_ID)
        AND  (DD.ID = J.TYPE_ID)
      INTO   :J_TYPE_ID, :J_TYPE_NAME, :J_TYPE_DOCNUMBERSTR
            ,:J_TYPE_DATE_COMMIT, :COLOR_FRG, :COLOR_BGR;
      END

    IF(:Q_ZERO = 1)THEN
      BEGIN
      IF(:QUANT <> 0)THEN SUSPEND;
      END
     ELSE
      SUSPEND;
    END
END
