{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/IRPROPS_CPL.INC}
{$IFNDEF PEAKTOP:COM/MICROSOFT/WINDOWS/IRPROPS_CPL.STRUCT.INC}
  {$I ./IRPROPS_CPL.STRUCT.INC}
{$ENDIF}
function BluetoothFindFirstRadio(
           const pBTFRP :TBlueToothFindRadioParams; 
           var   phRadio:THandle
         ):TBlueToothRadioFind;    external 'BluetoothFindFirstRadio@irprops.cpl stdcall';

function BluetoothFindNextRadio(
                 hFind  :TBlueToothRadioFind; 
           var   phRadio:THandle
         ):Integer;                external 'BluetoothFindNextRadio@irprops.cpl stdcall';
         
function BluetoothFindRadioClose(
                 hFind  :TBlueToothRadioFind
         ):Integer;                external 'BluetoothFindRadioClose@irprops.cpl stdcall';
         
function BluetoothGetRadioInfo(
                 hRadio    :THandle; 
           var   pRadioInfo:TBlueToothRadioFind
         ):Integer;                external 'BluetoothGetRadioInfo@irprops.cpl stdcall';
         
function BluetoothFindFirstDevice(
           const pBTSP     :TBlueToothDeviceSearchParams; 
           var   pBTDI     :TBlueToothDeviceInfo
         ):TBlueToothDeviceFind;   external 'BluetoothFindFirstDevice@irprops.cpl stdcall';
         
function BluetoothFindNextDevice(
                 hFind     :TBlueToothDeviceFind; 
           var   pBTDI     :TBlueToothDeviceInfo
         ):Integer;                external 'BluetoothFindNextDevice@irprops.cpl stdcall';
         
function BluetoothFindDeviceClose(
                 hFind     :TBlueToothDeviceFind
         ):Integer;                external 'BluetoothFindDeviceClose@irprops.cpl stdcall';
         
function BluetoothGetDeviceInfo(
                 hRadio    :THandle; 
           var   pBTDI     :TBlueToothDeviceInfo
         ):DWORD;                  external 'BluetoothGetDeviceInfo@irprops.cpl stdcall';
         
function BluetoothUpdateDeviceRecord(
           var   pBTDI     :TBlueToothDeviceInfo
         ):DWORD;                  external 'BluetoothUpdateDeviceRecord@irprops.cpl stdcall';

function BluetoothRemoveDevice(
           var   pAddress  :TBlueToothAddress
         ):DWORD;                  external 'BluetoothRemoveDevice@irprops.cpl stdcall';
         
                                             
