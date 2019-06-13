{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/IRPROPS_CPL.STRUCT.INC}
const
  BLUETOOTH_MAX_NAME_SIZE            = 248;
  BLUETOOTH_MAX_PASSKEY_SIZE         = 16;
  BLUETOOTH_MAX_PASSKEY_BUFFER_SIZE  = BLUETOOTH_MAX_PASSKEY_SIZE + 1;
type
  SDP_LARGE_INTEGER_16 = record
    LowPart :Int64;
    HighPart:Int64;
  end;
  TSdpLargeInteger     = SDP_LARGE_INTEGER_16;
  SDP_ULARGE_INTEGER_16= record
    LowPart :Int64;
    HighPart:Int64;
  end;
  TSdpULargeInteger16  = SDP_ULARGE_INTEGER_16;
  NodeContainerType    = (
     NodeContainerTypeSequence
    ,NodeContainerTypeAlternative
  );
  TNodeContainerType   = NodeContainerType;
  SDP_ERROR            = Word;
  TSdpError            = SDP_ERROR;
  SDP_TYPE             = DWORD;
  TSdpType             = SDP_TYPE;
  SDP_SPECIFICTYPE     = DWORD;
  TSdpSpecificType     = SDP_SPECIFICTYPE;
  _SdpAttributeRange   = record
    minAttribute: Word;
    maxAttribute: Word;
  end;
  SdpAttributeRange    = _SdpAttributeRange;
  TSdpAttributeRange   = SdpAttributeRange;
{
  SdpQueryUuidUnion    = record
    case Integer of
      0: (uuid128 :TGUID);
      1: (uuid32  :ULONG);
      2: (uuid16  :Word);
    end;
  TSdpQueryUuidUnion   = SdpQueryUuidUnion;
  _SdpQueryUuid        = record
     u       :SdpQueryUuidUnion;
     uuidType:Word;
  end;
  SdpQueryUuid         = _SdpQueryUuid;
  TSdpQueryUuid        = SdpQueryUuid;
}
  BTH_ADDR             = Int64;
  _BLUETOOTH_ADDRESS   = record
    Addr: BTH_ADDR;
  end;
  BLUETOOTH_ADDRESS    = _BLUETOOTH_ADDRESS;
  TBlueToothAddress    = BLUETOOTH_ADDRESS;
  _BLUETOOTH_FIND_RADIO_PARAMS = record
    dwSize: DWORD;             //  IN  sizeof this structure
  end;
  BLUETOOTH_FIND_RADIO_PARAMS  = _BLUETOOTH_FIND_RADIO_PARAMS;
  TBlueToothFindRadioParams    = BLUETOOTH_FIND_RADIO_PARAMS;
  HBLUETOOTH_RADIO_FIND        = THandle;
  TBlueToothRadioFind          = HBLUETOOTH_RADIO_FIND;
  
  _BLUETOOTH_RADIO_INFO = record
    dwSize          :DWORD;                                              // Size, in bytes, of this entire data structure
    address         :BLUETOOTH_ADDRESS;                                  // Address of the local radio
    szName          :array [0..BLUETOOTH_MAX_NAME_SIZE - 1] of WideChar; // Name of the local radio
    ulClassofDevice :Integer;                                            // Class of device for the local radio
    lmpSubversion   :Word;                                               // lmpSubversion, manufacturer specifc.
    manufacturer    :Word;                                               // Manufacturer of the radio, BTH_MFG_Xxx value.  For the most up to date
                                                                         // list, goto the Bluetooth specification website and get the Bluetooth
                                                                         // assigned numbers document.
  end;
  BLUETOOTH_RADIO_INFO = _BLUETOOTH_RADIO_INFO;
  _BLUETOOTH_DEVICE_INFO = record
     dwSize         :DWORD;                             //  size, in bytes, of this structure - must be the sizeof(BLUETOOTH_DEVICE_INFO)
     Address        :BLUETOOTH_ADDRESS;                  //  Bluetooth address
     ulClassofDevice:Integer;                    //  Bluetooth "Class of Device"
     fConnected     :Integer;                         //  Device connected/in use
     fRemembered    :Integer;                        //  Device remembered
     fAuthenticated :Integer;                     //  Device authenticated/paired/bonded
     stLastSeen     :TDateTime;                     //  Last time the device was seen
     stLastUsed     :TDateTime;                     //  Last time the device was used for other than RNR, inquiry, or SDP
     szName         :array [0..BLUETOOTH_MAX_NAME_SIZE - 1] of WideChar;  //  Name of the device
  end;
  BLUETOOTH_DEVICE_INFO = _BLUETOOTH_DEVICE_INFO;
  TBlueToothDeviceInfo  = BLUETOOTH_DEVICE_INFO;
  _BLUETOOTH_DEVICE_SEARCH_PARAMS = record
     dwSize              :DWORD;                   //  IN  sizeof this structure
     fReturnAuthenticated:Integer;                 //  IN  return authenticated devices
     fReturnRemembered   :Integer;                 //  IN  return remembered devices
     fReturnUnknown      :Integer;                 //  IN  return unknown devices
     fReturnConnected    :Integer;                 //  IN  return connected devices
     fIssueInquiry       :Integer;                 //  IN  issue a new inquiry
     cTimeoutMultiplier  :CHAR;                    //  IN  timeout for the inquiry
     hRadio              :THandle;                 //  IN  handle to radio to enumerate - NULL == all radios will be searched
  end;
  BLUETOOTH_DEVICE_SEARCH_PARAMS = _BLUETOOTH_DEVICE_SEARCH_PARAMS;
  TBlueToothDeviceSearchParams = BLUETOOTH_DEVICE_SEARCH_PARAMS;
  HBLUETOOTH_DEVICE_FIND = THandle;
  TBlueToothDeviceFind   = HBLUETOOTH_DEVICE_FIND;

const
  SDP_TYPE_NIL         = $00;
  SDP_TYPE_UINT        = $01;
  SDP_TYPE_INT         = $02;
  SDP_TYPE_UUID        = $03;
  SDP_TYPE_STRING      = $04;
  SDP_TYPE_BOOLEAN     = $05;
  SDP_TYPE_SEQUENCE    = $06;
  SDP_TYPE_ALTERNATIVE = $07;
  SDP_TYPE_URL         = $08;
  // 9 - 31 are reserved
  SDP_TYPE_CONTAINER   = $20;

  SDP_ST_NONE          = $0000;
  SDP_ST_UINT8         = $0010;
  SDP_ST_UINT16        = $0110;
  SDP_ST_UINT32        = $0210;
  SDP_ST_UINT64        = $0310;
  SDP_ST_UINT128       = $0410;
  SDP_ST_INT8          = $0020;
  SDP_ST_INT16         = $0120;
  SDP_ST_INT32         = $0220;
  SDP_ST_INT64         = $0320;
  SDP_ST_INT128        = $0420;
  SDP_ST_UUID16        = $0130;
  SDP_ST_UUID32        = $0220;
  SDP_ST_UUID128       = $0430;
  
