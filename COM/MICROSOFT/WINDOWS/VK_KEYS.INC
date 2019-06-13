{$DEFINE PEAKTOP:COM/MICROSOFT/WINDOWS/VK_KEYS.INC}
CONST  
  VK_LBUTTON        = $01; //Левая клавиша мыши
  VK_RBUTTON        = $02; //Правая клавиша мыши
  VK_CANCEL         = $03; //<Break>
  VK_MBUTTON        = $04; // Средняя кнопка для трехкнопочной мыши
  VK_XBUTTON1       = $05; //Windows 2000/XP: X1 mouse button
  VK_XBUTTON2       = $06; //Windows 2000/XP: X2 mouse button
  VK_BACK           = $08; //<Backspace>
  VK_TAB            = $09; //<Tab>
// $0A - $0B : reserved
  VK_CLEAR          = $0C; //Соответствует клавише <5> дополнительной клавиатуры при выключенном режиме <Num Lock>
  VK_RETURN         = $0D; //<Enter>
  VK_SHIFT          = $10; //<Shift>
  VK_CONTROL        = $11; //<Ctrl>
  VK_MENU           = $12; //<Alt>
  VK_PAUSE          = $13; //<Pause>
  VK_CAPITAL        = $14; //<Caps Lock>
  VK_KANA           = $15; //IME Kana mode
  VK_HANGEUL        = $15;  (* old name - should be here for compatibility *)
  VK_HANGUL         = $15; //IME Hangul mode
  VK_JUNJA          = $17; //IME Junja mode
  VK_FINAL          = $18; //IME final mode
  VK_HANJA          = $19; //IME Hanja mode
  VK_KANJI          = $19; //IME Kanji mode
  VK_ESCAPE         = $1B; //<Esc>
  VK_CONVERT        = $1C; //IME convert (Reserved for Kanji systems)
  VK_NONCONVERT     = $1D; //IME nonconvert (Reserved for Kanji systems)
  VK_ACCEPT         = $1E; //IME accept (Reserved for Kanji systems)
  VK_MODECHANGE     = $1F; //IME mode change request (Reserved for Kanji systems)
  VK_SPACE          = $20; //<Spacebar>
  VK_PRIOR          = $21; //<PgUp>
  VK_NEXT           = $22; //<PgDn>
  VK_END            = $23; //<End>
  VK_HOME           = $24; //<Home>
  VK_LEFT           = $25; //Клавиша перемещения курсора влево <Left>
  VK_UP             = $26; //Клавиша перемещения курсора вверх <Up>
  VK_RIGHT          = $27; //Клавиша перемещения курсора вправо <Right>
  VK_DOWN           = $28; //Клавиша перемещения курсора вниз <Down>
  VK_SELECT         = $29;
  VK_PRINT          = $2A;
  VK_EXECUTE        = $2B;
  VK_SNAPSHOT       = $2C; //<Print Screen>
  VK_INSERT         = $2D; //<Ins>
  VK_DELETE         = $2E; //<Delete>
  VK_HELP           = $2F;
(*
 *   VK_0 -   VK_9 are the same as ASCII '0' - '9' ($30 - $39)
 * $40 : unassigned
 *   VK_A -   VK_Z are the same as ASCII 'A' - 'Z' ($41 - $5A)
 *)
(*
 * Алфавитно-цифровые клавиши. Эти коды отсутствуют среди констант в файле windows.pas
 *   VK_0 -   VK_9 соответствуют клавишам на основной клавиатуре
 *)
  VK_0    = $30;
  VK_1    = $31;
  VK_2    = $32;
  VK_3    = $33;
  VK_4    = $34;
  VK_5    = $35;
  VK_6    = $36;
  VK_7    = $37;
  VK_8    = $38;
  VK_9    = $39;
  VK_A    = $41;
  VK_B    = $42;
  VK_C    = $43;
  VK_D    = $44;
  VK_E    = $45;
  VK_F    = $46;
  VK_G    = $47;
  VK_H    = $48;
  VK_I    = $49;
  VK_J    = $4A;
  VK_K    = $4B;
  VK_L    = $4C;
  VK_M    = $4D;
  VK_N    = $4E;
  VK_O    = $4F;
  VK_P    = $50;
  VK_Q    = $51;
  VK_R    = $52;
  VK_S    = $53;
  VK_T    = $54;
  VK_U    = $55;
  VK_V    = $56;
  VK_W    = $57;
  VK_X    = $58;
  VK_Y    = $59;
  VK_Z    = $5A;
  VK_LWIN = $5B; //Левая клавиша c логотипом Windows
  VK_RWIN = $5C; //Правая клавиша c логотипом Windows
  VK_APPS = $5D; //Клавиша вызова контекстного меню
(*
 * $5E : reserved
 *)
  VK_SLEEP          = $5F; //<Sleep>
  VK_NUMPAD0        = $60; //Коды для цифровых клавиш на дополнительной клавиатуре
  VK_NUMPAD1        = $61;
  VK_NUMPAD2        = $62;
  VK_NUMPAD3        = $63;
  VK_NUMPAD4        = $64;
  VK_NUMPAD5        = $65;
  VK_NUMPAD6        = $66;
  VK_NUMPAD7        = $67;
  VK_NUMPAD8        = $68;
  VK_NUMPAD9        = $69;
  VK_MULTIPLY       = $6A; //Клавиша 'умножить' (*) на дополнительной клавиатуре
  VK_ADD            = $6B; //Клавиша 'прибавить' (+) на дополнительной клавиатуре
  VK_SEPARATOR      = $6C; //Клавиша 'умножить' (*) на дополнительной клавиатуре
  VK_SUBTRACT       = $6D; //Separator key (не знаю, что за клавиша)
  VK_DECIMAL        = $6E; //Клавиша 'точка' (.) на дополнительной клавиатуре
  VK_DIVIDE         = $6F; //Клавиша 'разделить' (/) на дополнительной клавиатуре
  VK_F1             = $70; //Коды для функциональных клавиш
  VK_F2             = $71;
  VK_F3             = $72;
  VK_F4             = $73;
  VK_F5             = $74;
  VK_F6             = $75;
  VK_F7             = $76;
  VK_F8             = $77;
  VK_F9             = $78;
  VK_F10            = $79;
  VK_F11            = $7A;
  VK_F12            = $7B;
  VK_F13            = $7C;
  VK_F14            = $7D;
  VK_F15            = $7E;
  VK_F16            = $7F;
  VK_F17            = $80;
  VK_F18            = $81;
  VK_F19            = $82;
  VK_F20            = $83;
  VK_F21            = $84;
  VK_F22            = $85;
  VK_F23            = $86;
  VK_F24            = $87;
(*
 * $88 - $8F : unassigned
 *)
  VK_NUMLOCK        = $90; //<Num Lock>
  VK_SCROLL         = $91; //<Scroll Lock>
(*
 * NEC PC-9800 kbd definitions
 *)
  VK_OEM_NEC_EQUAL  = $92;   // '=' key on numpad
(*
 * Fujitsu/OASYS kbd definitions
 *)
  VK_OEM_FJ_JISHO   = $92;   // 'Dictionary' key
  VK_OEM_FJ_MASSHOU = $93;   // 'Unregister word' key
  VK_OEM_FJ_TOUROKU = $94;   // 'Register word' key
  VK_OEM_FJ_LOYA    = $95;   // 'Left OYAYUBI' key
  VK_OEM_FJ_ROYA    = $96;   // 'Right OYAYUBI' key
(*
 * $97 - $9F : unassigned
 *)
(*
 *   VK_L* &   VK_R* - коды левых и правых клавиш Shift, Control и Alt.
 * Используются только в функциях GetAsyncKeyState() и GetKeyState().
 * Никакие другие сообщения или функции их не используют.
 *)
  VK_LSHIFT         = $A0;
  VK_RSHIFT         = $A1;
  VK_LCONTROL       = $A2;
  VK_RCONTROL       = $A3;
  VK_LMENU          = $A4;
  VK_RMENU          = $A5;

//begin of HIGH Version (2000 and XP) block
  VK_BROWSER_BACK        = $A6; //Windows 2000/XP: Browser Back key
  VK_BROWSER_FORWARD     = $A7; //Windows 2000/XP: Browser Forward key
  VK_BROWSER_REFRESH     = $A8; //Windows 2000/XP: Browser Refresh key
  VK_BROWSER_STOP        = $A9; //Windows 2000/XP: Browser Stop key
  VK_BROWSER_SEARCH      = $AA; //Windows 2000/XP: Browser Search key
  VK_BROWSER_FAVORITES   = $AB; //Windows 2000/XP: Browser Favorites key
  VK_BROWSER_HOME        = $AC; //Windows 2000/XP: Browser Start and Home key
  VK_VOLUME_MUTE         = $AD; //Windows 2000/XP: Volume Mute key
  VK_VOLUME_DOWN         = $AE; //Windows 2000/XP: Volume Down key
  VK_VOLUME_UP           = $AF; //Windows 2000/XP: Volume Up key
  VK_MEDIA_NEXT_TRACK    = $B0; //Windows 2000/XP: Next Track key
  VK_MEDIA_PREV_TRACK    = $B1; //Windows 2000/XP: Previous Track key
  VK_MEDIA_STOP          = $B2; //Windows 2000/XP: Stop Media key
  VK_MEDIA_PLAY_PAUSE    = $B3; //Windows 2000/XP: Play/Pause Media key
  VK_LAUNCH_MAIL         = $B4; //Windows 2000/XP: Start Mail key
  VK_LAUNCH_MEDIA_SELECT = $B5; //Windows 2000/XP: Select Media key
  VK_LAUNCH_APP1         = $B6; //Windows 2000/XP: Start Application 1 key
  VK_LAUNCH_APP2         = $B7; //Windows 2000/XP: Start Application 2 key
//end of HIGH Version block
(*
 * $B8 - $B9 : reserved
 *)
  VK_OEM_1          = $BA;   // Windows 2000/XP: For the US standard keyboard, the ';:' key
  VK_OEM_PLUS       = $BB;   // Windows 2000/XP: For any country/region, the '+' key
  VK_OEM_COMMA      = $BC;   // Windows 2000/XP: For any country/region, the ',' key
  VK_OEM_MINUS      = $BD;   // Windows 2000/XP: For any country/region, the '-' key
  VK_OEM_PERIOD     = $BE;   // Windows 2000/XP: For any country/region, the '.' key
  VK_OEM_2          = $BF;   // Used for miscellaneous characters; it can vary by keyboard.
                             // Windows 2000/XP: For the US standard keyboard, the '/?' key
  VK_OEM_3          = $C0;   // Used for miscellaneous characters; it can vary by keyboard.
                             // Windows 2000/XP: For the US standard keyboard, the '`~' key
(*
 * $C1 - $D7 : reserved
 *)
(*
 * $D8 - $DA : unassigned
 *)
    //Used for miscellaneous characters; it can vary by keyboard.
  VK_OEM_4          = $DB;  //  '[{' for US
  VK_OEM_5          = $DC;  //  '\|' for US
  VK_OEM_6          = $DD;  //  ']}' for US
  VK_OEM_7          = $DE;  //  ''"' for US
  VK_OEM_8          = $DF;
(*
 * $E0 : reserved
 *)
(*
 * Various extended or enhanced keyboards
 *)
  VK_OEM_AX         = $E1;  //  'AX' key on Japanese AX kbd
  VK_OEM_102        = $E2;  //  "<>" or "\|" on RT 102-key kbd.
  VK_ICO_HELP       = $E3;  //  Help key on ICO
  VK_ICO_00         = $E4;  //  00 key on ICO
  VK_PROCESSKEY     = $E5;  // Windows 95/98/Me, Windows NT 4.0, Windows 2000/XP: IME PROCESS key
  VK_ICO_CLEAR      = $E6;
  VK_PACKET         = $E7;  // Windows 2000/XP: Used to pass Unicode characters as if they were keystrokes. The
                            //  VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods.
(*
 * $E8 : unassigned
 *)
(*
 * Nokia/Ericsson definitions
 *)
  VK_OEM_RESET      = $E9;
  VK_OEM_JUMP       = $EA;
  VK_OEM_PA1        = $EB;
  VK_OEM_PA2        = $EC;
  VK_OEM_PA3        = $ED;
  VK_OEM_WSCTRL     = $EE;
  VK_OEM_CUSEL      = $EF;
  VK_OEM_ATTN       = $F0;
  VK_OEM_FINISH     = $F1;
  VK_OEM_COPY       = $F2;
  VK_OEM_AUTO       = $F3;
  VK_OEM_ENLW       = $F4;
  VK_OEM_BACKTAB    = $F5;
//Коды для 122-клавишной клавиатуры
  VK_ATTN           = $F6;
  VK_CRSEL          = $F7;
  VK_EXSEL          = $F8;
  VK_EREOF          = $F9;
  VK_PLAY           = $FA;
  VK_ZOOM           = $FB;
  VK_NONAME         = $FC;
  VK_PA1            = $FD;
  VK_OEM_CLEAR      = $FE;
(*
 * $FF : reserved
 *)
