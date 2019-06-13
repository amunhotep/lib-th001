{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/CONST.INC}
const
  INFINITE                            = $FFFFFFFF; // Infinite timeout    
// The following are masks for the predefined standard access types
  _DELETE                             = $00010000; // Renamed from DELETE for compability with pascal "procedure Delete()"
  READ_CONTROL                        = $00020000;
  WRITE_DAC                           = $00040000;
  WRITE_OWNER                         = $00080000;
  SYNCHRONIZE                         = $00100000;
  STANDARD_RIGHTS_REQUIRED            = $000F0000;
  STANDARD_RIGHTS_READ                = $00020000;
  STANDARD_RIGHTS_WRITE               = $00020000;
  STANDARD_RIGHTS_EXECUTE             = $00020000;
  STANDARD_RIGHTS_ALL                 = $001F0000;
  SPECIFIC_RIGHTS_ALL                 = $0000FFFF;
  ACCESS_SYSTEM_SECURITY              = $01000000;
  MAXIMUM_ALLOWED                     = $02000000;
  GENERIC_READ                        = $80000000;
  GENERIC_WRITE                       = $40000000;
  GENERIC_EXECUTE                     = $20000000;
  GENERIC_ALL                         = $10000000;
// process priority classes
  DEBUG_PROCESS                       = $00000001;
  DEBUG_ONLY_THIS_PROCESS             = $00000002;
  CREATE_SUSPENDED                    = $00000004;
  DETACHED_PROCESS                    = $00000008;
  CREATE_NEW_CONSOLE                  = $00000010;
  NORMAL_PRIORITY_CLASS               = $00000020;
  IDLE_PRIORITY_CLASS                 = $00000040;
  HIGH_PRIORITY_CLASS                 = $00000080;
  REALTIME_PRIORITY_CLASS             = $00000100;
// File access const
  FILE_SHARE_READ                     = $00000001;
  FILE_SHARE_WRITE                    = $00000002;
  FILE_SHARE_DELETE                   = $00000004;
  FILE_ATTRIBUTE_READONLY             = $00000001;
  FILE_ATTRIBUTE_HIDDEN               = $00000002;
  FILE_ATTRIBUTE_SYSTEM               = $00000004;
  FILE_ATTRIBUTE_DIRECTORY            = $00000010;
  FILE_ATTRIBUTE_ARCHIVE              = $00000020;
  FILE_ATTRIBUTE_NORMAL               = $00000080;
  FILE_ATTRIBUTE_TEMPORARY            = $00000100;
  FILE_ATTRIBUTE_COMPRESSED           = $00000800;
  FILE_ATTRIBUTE_OFFLINE              = $00001000;
  FILE_NOTIFY_CHANGE_FILE_NAME        = $00000001;
  FILE_NOTIFY_CHANGE_DIR_NAME         = $00000002;
  FILE_NOTIFY_CHANGE_ATTRIBUTES       = $00000004;
  FILE_NOTIFY_CHANGE_SIZE             = $00000008;
  FILE_NOTIFY_CHANGE_LAST_WRITE       = $00000010;
  FILE_NOTIFY_CHANGE_LAST_ACCESS      = $00000020;
  FILE_NOTIFY_CHANGE_CREATION         = $00000040;
  FILE_NOTIFY_CHANGE_SECURITY         = $00000100;
  FILE_ACTION_ADDED                   = $00000001;
  FILE_ACTION_REMOVED                 = $00000002;
  FILE_ACTION_MODIFIED                = $00000003;
  FILE_ACTION_RENAMED_OLD_NAME        = $00000004;
  FILE_ACTION_RENAMED_NEW_NAME        = $00000005;
  FILE_CASE_SENSITIVE_SEARCH          = $00000001;
  FILE_CASE_PRESERVED_NAMES           = $00000002;
  FILE_UNICODE_ON_DISK                = $00000004;
  FILE_PERSISTENT_ACLS                = $00000008;
  FILE_FILE_COMPRESSION               = $00000010;
  FILE_VOLUME_IS_COMPRESSED           = $00008000;
// File creation flags must start at the high end since they are combined with the attributes
  FILE_FLAG_WRITE_THROUGH             = $80000000;
  FILE_FLAG_OVERLAPPED                = $40000000;
  FILE_FLAG_NO_BUFFERING              = $20000000;
  FILE_FLAG_RANDOM_ACCESS             = $10000000;
  FILE_FLAG_SEQUENTIAL_SCAN           = $08000000;
  FILE_FLAG_DELETE_ON_CLOSE           = $04000000;
  FILE_FLAG_BACKUP_SEMANTICS          = $02000000;
  FILE_FLAG_POSIX_SEMANTICS           = $01000000;
  CREATE_NEW                          = 1;
  CREATE_ALWAYS                       = 2;
  OPEN_EXISTING                       = 3;
  OPEN_ALWAYS                         = 4;
  TRUNCATE_EXISTING                   = 5;
// Define possible return codes from the CopyFileEx callback routine
  PROGRESS_CONTINUE                   = 0;
  PROGRESS_CANCEL                     = 1;
  PROGRESS_STOP                       = 2;
  PROGRESS_QUIET                      = 3;
// Stream IDs
  BACKUP_INVALID                      = 0;
  BACKUP_DATA                         = 1;
  BACKUP_EA_DATA                      = 2;
  BACKUP_SECURITY_DATA                = 3;
  BACKUP_ALTERNATE_DATA               = 4;
  BACKUP_LINK                         = 5;
  BACKUP_PROPERTY_DATA                = 6;
// Stream Attributes
  STREAM_NORMAL_ATTRIBUTE             = 0;
  STREAM_MODIFIED_WHEN_READ           = 1;
  STREAM_CONTAINS_SECURITY            = 2;
  STREAM_CONTAINS_PROPERTIES          = 4;
// Dual Mode API below this line. Dual Mode Structures also included.
  STARTF_USESHOWWINDOW                = 1;
  STARTF_USESIZE                      = 2;
  STARTF_USEPOSITION                  = 4;
  STARTF_USECOUNTCHARS                = 8;
  STARTF_USEFILLATTRIBUTE             = $10;
  STARTF_RUNFULLSCREEN                = $20;  // ignored for non-x86 platforms
  STARTF_FORCEONFEEDBACK              = $40;
  STARTF_FORCEOFFFEEDBACK             = $80;
  STARTF_USESTDHANDLES                = $100;
  STARTF_USEHOTKEY                    = $200;
// ShowWindow() Commands
  SW_HIDE                             = 0;
  SW_SHOWNORMAL                       = 1;
  SW_NORMAL                           = 1;
  SW_SHOWMINIMIZED                    = 2;
  SW_SHOWMAXIMIZED                    = 3;
  SW_MAXIMIZE                         = 3;
  SW_SHOWNOACTIVATE                   = 4;
  SW_SHOW                             = 5;
  SW_MINIMIZE                         = 6;
  SW_SHOWMINNOACTIVE                  = 7;
  SW_SHOWNA                           = 8;
  SW_RESTORE                          = 9;
  SW_SHOWDEFAULT                      = 10;
  SW_MAX                              = 10;
// Old ShowWindow() Commands 
  HIDE_WINDOW                         = 0;
  SHOW_OPENWINDOW                     = 1;
  SHOW_ICONWINDOW                     = 2;
  SHOW_FULLSCREEN                     = 3;
  SHOW_OPENNOACTIVATE                 = 4;
