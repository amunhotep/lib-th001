{$DEFINE PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC}
const //============== PEAKTOP:IDE/ERP/DBO/DBGRID/COL_PROTOCOL.INC =============
  ERP_COL_INDEX_TABLE             =  0;
  ERP_COL_INDEX_FIELD             =  1;
  ERP_COL_INDEX_REF_TABLE         =  2;
  ERP_COL_INDEX_REF_FIELD         =  3;
  ERP_COL_INDEX_REF_KEYFIELD      =  4;
  ERP_COL_INDEX_REF_BUFFERVAR     =  5;
  ERP_COL_INDEX_REF_SCRIPTDLG     =  6;
  ERP_COL_INDEX_VALUEDEFAULT      =  7;
  ERP_COL_INDEX_FIELDTYPE         =  8;
  ERP_COL_INDEX_PERIODICAL        =  9;
  ERP_COL_INDEX_VALUEEMPTY        = 10;
  ERP_COL_INDEX_REF_SCRIPTITEM    = 11;
  ERP_COL_INDEX_REF_SCRIPTITEMDLG = 12;
  ERP_COL_INDEX_TABLEMAIN         = 13;
  ERP_COL_INDEX_MAIN_BASETYPE     = 14;
  ERP_COL_INDEX_MAIN_BUFFERVAR    = 15;
  ERP_COL_INDEX_MAIN_SCRIPT       = 16;
  ERP_COL_INDEX_MAIN_SCRIPTDLG    = 17;
  ERP_COL_INDEX_MAIN_SCRIPTITEM   = 18;
  ERP_COL_INDEX_MAIN_SCRIPTITEMDLG= 19;
  ERP_COL_INDEX_SUBKONTO_FIELD    = 20;
  ERP_COL_INDEX__COUNT            = 21;
  //============================================================================
  function ERP_COL_INDEX__FIELDS(const aIndex:Integer):string;
  begin
    Result := 'TB_ID';
    case aIndex of
      ERP_COL_INDEX_TABLE             :Result := 'TB_ID';
      ERP_COL_INDEX_FIELD             :Result := 'ID';
      ERP_COL_INDEX_REF_TABLE         :Result := 'REF_TABLE';
      ERP_COL_INDEX_REF_FIELD         :Result := 'REF_FIELD';
      ERP_COL_INDEX_REF_KEYFIELD      :Result := 'REF_KEYFIELD';
      ERP_COL_INDEX_REF_BUFFERVAR     :Result := 'REF_BUFFER_VAR';
      ERP_COL_INDEX_REF_SCRIPTDLG     :Result := 'REF_SC_REF_DLG';
      ERP_COL_INDEX_VALUEDEFAULT      :Result := 'DEFAULT_VALUE';
      ERP_COL_INDEX_FIELDTYPE         :Result := 'FIELD_TYPE';
      ERP_COL_INDEX_PERIODICAL        :Result := 'FLAG_PERIODICAL';
      ERP_COL_INDEX_VALUEEMPTY        :Result := 'EMPTY_VALUE';
      ERP_COL_INDEX_REF_SCRIPTITEM    :Result := 'REF_SC_ITEM';
      ERP_COL_INDEX_REF_SCRIPTITEMDLG :Result := 'REF_SC_ITEM_DLG';
      ERP_COL_INDEX_TABLEMAIN         :Result := 'MAINTB_ID';
      ERP_COL_INDEX_MAIN_BASETYPE     :Result := 'MAIN_BASE_TYPE_ID';
      ERP_COL_INDEX_MAIN_BUFFERVAR    :Result := 'MAIN_BUFFER_VAR';
      ERP_COL_INDEX_MAIN_SCRIPT       :Result := 'MAIN_SC_REF';
      ERP_COL_INDEX_MAIN_SCRIPTDLG    :Result := 'MAIN_SC_REF_DLG';
      ERP_COL_INDEX_MAIN_SCRIPTITEM   :Result := 'MAIN_SC_ITEM';
      ERP_COL_INDEX_MAIN_SCRIPTITEMDLG:Result := 'MAIN_SC_ITEM_DLG';
      ERP_COL_INDEX_SUBKONTO_FIELD    :Result := 'SUBKONTO_FIELD';
    end;  
  end;
