{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/ADVAPI32.DLL.INC}

type
  ACCESS_MASK = Integer;
  REGSAM      = ACCESS_MASK;  { Requested Key access mask type. }
  HKEY        = LongWord;

  TSecurityAttributes = record
    nLength             :LongWord;
    lpSecurityDescriptor:Pointer;
    bInheritHandle      :Boolean;
  end;

const
  HKEY_CLASSES_ROOT     = $80000000;
  HKEY_CURRENT_USER     = $80000001;
  HKEY_LOCAL_MACHINE    = $80000002;
  HKEY_USERS            = $80000003;
  HKEY_PERFORMANCE_DATA = $80000004;      
  HKEY_CURRENT_CONFIG   = $80000005;
  HKEY_DYN_DATA         = $80000006;
  PROVIDER_KEEPS_VALUE_LENGTH = 1;

function RegCloseKey(
           hKey: HKEY                 
           ): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegConnectRegistry (
               lpMachineName:PChar;     
               hKey         :HKEY;
           var phkResult    :HKEY
           ):LongInt; external 'RegConnectRegistry@advapi32.dll stdcall';
function RegConnectRegistryA(
               lpMachineName:PChar; 
               hKey         :HKEY;
           var phkResult    :HKEY
           ):LongInt; external 'RegConnectRegistryA@advapi32.dll stdcall';
function RegConnectRegistryW(
               lpMachineName:PChar; 
               hKey         :HKEY;
           var phkResult    :HKEY
           ):LongInt; external 'RegConnectRegistryW@advapi32.dll stdcall';
function RegCreateKey(
               hKey         :HKEY; 
               lpSubKey     :PChar; 
           var phkResult    :HKEY
           ): LongInt; external 'RegCreateKey@advapi32.dll stdcall';
function RegCreateKeyA(
               hKey         :HKEY; 
               lpSubKey     :PChar;
           var phkResult    :HKEY
           ): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegCreateKeyW(
               hKey         :HKEY; 
               lpSubKey     :PChar;
           var phkResult    :HKEY
           ): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegCreateKeyEx(
               hKey                :HKEY; 
               lpSubKey            :PChar; 
               Reserved            :LongWord; 
               lpClass             :PChar; 
               dwOptions           :LongWord; 
               samDesired          :REGSAM;
               lpSecurityAttributes:TSecurityAttributes; 
           var phkResult           :HKEY;
               lpdwDisposition     :LongWord
           ): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegCreateKeyExA(
               hKey: HKEY; 
               lpSubKey: PChar;
               Reserved: LongWord; 
               lpClass: PChar;
               dwOptions: LongWord;
               samDesired: REGSAM;
               lTSecurityAttributes: TSecurityAttributes; 
            var phkResult: HKEY;
  lpdwDisposition: PLongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegCreateKeyExW(hKey: HKEY; lpSubKey: PChar;
  Reserved: LongWord; lpClass: PChar; dwOptions: LongWord; samDesired: REGSAM;
  lTSecurityAttributes: TSecurityAttributes; var phkResult: HKEY;
  lpdwDisposition: PLongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegDeleteKey(hKey: HKEY; lpSubKey: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegDeleteKeyA(hKey: HKEY; lpSubKey: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegDeleteKeyW(hKey: HKEY; lpSubKey: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
function RegDeleteValue(hKey: HKEY; lpValueName: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegDeleteValueA}
function RegDeleteValueA(hKey: HKEY; lpValueName: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegDeleteValueW}
function RegDeleteValueW(hKey: HKEY; lpValueName: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumKey}
function RegEnumKey(hKey: HKEY; dwIndex: LongWord; lpName: PChar; cbName: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumKeyA}
function RegEnumKeyA(hKey: HKEY; dwIndex: LongWord; lpName: PChar; cbName: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumKeyW}
function RegEnumKeyW(hKey: HKEY; dwIndex: LongWord; lpName: PChar; cbName: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumKeyEx}
function RegEnumKeyEx(hKey: HKEY; dwIndex: LongWord; lpName: PChar;
  var lpcbName: LongWord; lpReserved: Pointer; lpClass: PChar;
  lpcbClass: PLongWord; lpftLastWriteTime: PFileTime): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumKeyExA}
function RegEnumKeyExA(hKey: HKEY; dwIndex: LongWord; lpName: PChar;
  var lpcbName: LongWord; lpReserved: Pointer; lpClass: PChar;
  lpcbClass: PLongWord; lpftLastWriteTime: PFileTime): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumKeyExW}
function RegEnumKeyExW(hKey: HKEY; dwIndex: LongWord; lpName: PChar;
  var lpcbName: LongWord; lpReserved: Pointer; lpClass: PChar;
  lpcbClass: PLongWord; lpftLastWriteTime: PFileTime): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumValue}
function RegEnumValue(hKey: HKEY; dwIndex: LongWord; lpValueName: PChar;
  var lpcbValueName: LongWord; lpReserved: Pointer; lpType: PLongWord;
  lpData: PByte; lpcbData: PLongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumValueA}
function RegEnumValueA(hKey: HKEY; dwIndex: LongWord; lpValueName: PChar;
  var lpcbValueName: LongWord; lpReserved: Pointer; lpType: PLongWord;
  lpData: PByte; lpcbData: PLongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegEnumValueW}
function RegEnumValueW(hKey: HKEY; dwIndex: LongWord; lpValueName: PChar;
  var lpcbValueName: LongWord; lpReserved: Pointer; lpType: PLongWord;
  lpData: PByte; lpcbData: PLongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegFlushKey}
function RegFlushKey(hKey: HKEY): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegGetKeySecurity}
function RegGetKeySecurity(hKey: HKEY; SecurityInformation: SECURITY_INFORMATION;
  pSecurityDescriptor: PSecurityDescriptor; var lpcbSecurityDescriptor: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegLoadKey}
function RegLoadKey(hKey: HKEY; lpSubKey, lpFile: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegLoadKeyA}
function RegLoadKeyA(hKey: HKEY; lpSubKey, lpFile: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegLoadKeyW}
function RegLoadKeyW(hKey: HKEY; lpSubKey, lpFile: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegNotifyChangeKeyValue}
function RegNotifyChangeKeyValue(hKey: HKEY; bWatchSubtree: BOOL;
  dwNotifyFilter: LongWord; hEvent: THandle; fAsynchronus: BOOL): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegOpenKey}
function RegOpenKey(hKey: HKEY; lpSubKey: PChar; var phkResult: HKEY): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegOpenKeyA}
function RegOpenKeyA(hKey: HKEY; lpSubKey: PChar; var phkResult: HKEY): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegOpenKeyW}
function RegOpenKeyW(hKey: HKEY; lpSubKey: PChar; var phkResult: HKEY): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegOpenKeyEx}
function RegOpenKeyEx(hKey: HKEY; lpSubKey: PChar;
  ulOptions: LongWord; samDesired: REGSAM; var phkResult: HKEY): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegOpenKeyExA}
function RegOpenKeyExA(hKey: HKEY; lpSubKey: PChar;
  ulOptions: LongWord; samDesired: REGSAM; var phkResult: HKEY): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegOpenKeyExW}
function RegOpenKeyExW(hKey: HKEY; lpSubKey: PChar;
  ulOptions: LongWord; samDesired: REGSAM; var phkResult: HKEY): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryInfoKey}
function RegQueryInfoKey(hKey: HKEY; lpClass: PChar;
  lpcbClass: PLongWord; lpReserved: Pointer;
  lpcSubKeys, lpcbMaxSubKeyLen, lpcbMaxClassLen, lpcValues,
  lpcbMaxValueNameLen, lpcbMaxValueLen, lpcbSecurityDescriptor: PLongWord;
  lpftLastWriteTime: PFileTime): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryInfoKeyA}
function RegQueryInfoKeyA(hKey: HKEY; lpClass: PChar;
  lpcbClass: PLongWord; lpReserved: Pointer;
  lpcSubKeys, lpcbMaxSubKeyLen, lpcbMaxClassLen, lpcValues,
  lpcbMaxValueNameLen, lpcbMaxValueLen, lpcbSecurityDescriptor: PLongWord;
  lpftLastWriteTime: PFileTime): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryInfoKeyW}
function RegQueryInfoKeyW(hKey: HKEY; lpClass: PChar;
  lpcbClass: PLongWord; lpReserved: Pointer;
  lpcSubKeys, lpcbMaxSubKeyLen, lpcbMaxClassLen, lpcValues,
  lpcbMaxValueNameLen, lpcbMaxValueLen, lpcbSecurityDescriptor: PLongWord;
  lpftLastWriteTime: PFileTime): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryValue}
function RegQueryValue(hKey: HKEY; lpSubKey: PChar;
  lpValue: PChar; var lpcbValue: LongInt): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryValueA}
function RegQueryValueA(hKey: HKEY; lpSubKey: PChar;
  lpValue: PChar; var lpcbValue: LongInt): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryValueW}
function RegQueryValueW(hKey: HKEY; lpSubKey: PChar;
  lpValue: PChar; var lpcbValue: LongInt): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryMultipleValues}
function RegQueryMultipleValues(hKey: HKEY; var ValList;
  NumVals: LongWord; lpValueBuf: PChar; var ldwTotsize: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryMultipleValuesA}
function RegQueryMultipleValuesA(hKey: HKEY; var ValList;
  NumVals: LongWord; lpValueBuf: PChar; var ldwTotsize: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryMultipleValuesW}
function RegQueryMultipleValuesW(hKey: HKEY; var ValList;
  NumVals: LongWord; lpValueBuf: PChar; var ldwTotsize: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryValueEx}
function RegQueryValueEx(hKey: HKEY; lpValueName: PChar;
  lpReserved: Pointer; lpType: PLongWord; lpData: PByte; lpcbData: PLongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryValueExA}
function RegQueryValueExA(hKey: HKEY; lpValueName: PChar;
  lpReserved: Pointer; lpType: PLongWord; lpData: PByte; lpcbData: PLongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegQueryValueExW}
function RegQueryValueExW(hKey: HKEY; lpValueName: PChar;
  lpReserved: Pointer; lpType: PLongWord; lpData: PByte; lpcbData: PLongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegReplaceKey}
function RegReplaceKey(hKey: HKEY; lpSubKey: PChar;
   lpNewFile: PChar; lpOldFile: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegReplaceKeyA}
function RegReplaceKeyA(hKey: HKEY; lpSubKey: PChar;
   lpNewFile: PChar; lpOldFile: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegReplaceKeyW}
function RegReplaceKeyW(hKey: HKEY; lpSubKey: PChar;
   lpNewFile: PChar; lpOldFile: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegRestoreKey}
function RegRestoreKey(hKey: HKEY; lpFile: PChar; dwFlags: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegRestoreKeyA}
function RegRestoreKeyA(hKey: HKEY; lpFile: PChar; dwFlags: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegRestoreKeyW}
function RegRestoreKeyW(hKey: HKEY; lpFile: PChar; dwFlags: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSaveKey}
function RegSaveKey(hKey: HKEY; lpFile: PChar;
  lTSecurityAttributes: TSecurityAttributes): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSaveKeyA}
function RegSaveKeyA(hKey: HKEY; lpFile: PChar;
  lTSecurityAttributes: TSecurityAttributes): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSaveKeyW}
function RegSaveKeyW(hKey: HKEY; lpFile: PChar;
  lTSecurityAttributes: TSecurityAttributes): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSetKeySecurity}
function RegSetKeySecurity(hKey: HKEY; SecurityInformation: SECURITY_INFORMATION;
  pSecurityDescriptor: PSECURITY_DESCRIPTOR): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSetValue}
function RegSetValue(hKey: HKEY; lpSubKey: PChar;
  dwType: LongWord; lpData: PChar; cbData: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSetValueA}
function RegSetValueA(hKey: HKEY; lpSubKey: PChar;
  dwType: LongWord; lpData: PChar; cbData: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSetValueW}
function RegSetValueW(hKey: HKEY; lpSubKey: PChar;
  dwType: LongWord; lpData: PChar; cbData: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSetValueEx}
function RegSetValueEx(hKey: HKEY; lpValueName: PChar;
  Reserved: LongWord; dwType: LongWord; lpData: Pointer; cbData: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSetValueExA}
function RegSetValueExA(hKey: HKEY; lpValueName: PChar;
  Reserved: LongWord; dwType: LongWord; lpData: Pointer; cbData: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegSetValueExW}
function RegSetValueExW(hKey: HKEY; lpValueName: PChar;
  Reserved: LongWord; dwType: LongWord; lpData: Pointer; cbData: LongWord): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegUnLoadKey}
function RegUnLoadKey(hKey: HKEY; lpSubKey: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegUnLoadKeyA}
function RegUnLoadKeyA(hKey: HKEY; lpSubKey: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';
{ RegUnLoadKeyW}
function RegUnLoadKeyW(hKey: HKEY; lpSubKey: PChar): LongInt; external 'RegCloseKey@advapi32.dll stdcall';



begin
  
end.
