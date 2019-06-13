{$DEFINE PEAKTOP:OBJ/TSYNEDIT_KEYCOMMANDS.INC}
const //============== PEAKTOP:OBJ/TSYNEDIT_KEYCOMMANDS.INC ====================
  ecNone             =    0; // Nothing. Useful for user event to handle command
  ecViewCommandFirst =    0;
  ecViewCommandLast  =  500;
  ecEditCommandFirst =  501;
  ecEditCommandLast  = 1000;
  ecLeft             = 1;    // Move cursor left one char
  ecRight            = 2;    // Move cursor right one char
  ecUp               = 3;    // Move cursor up one line
  ecDown             = 4;    // Move cursor down one line
  ecWordLeft         = 5;    // Move cursor left one word
  ecWordRight        = 6;    // Move cursor right one word
  ecLineStart        = 7;    // Move cursor to beginning of line
  ecLineEnd          = 8;    // Move cursor to end of line
  ecPageUp           = 9;    // Move cursor up one page
  ecPageDown         = 10;   // Move cursor down one page
  ecPageLeft         = 11;   // Move cursor right one page
  ecPageRight        = 12;   // Move cursor left one page
  ecPageTop          = 13;   // Move cursor to top of page
  ecPageBottom       = 14;   // Move cursor to bottom of page
  ecEditorTop        = 15;   // Move cursor to absolute beginning
  ecEditorBottom     = 16;   // Move cursor to absolute end
  ecGotoXY           = 17;   // Move cursor to specific coordinates, Data = PPoint
  ecSelection        = 100;  // Add this to ecXXX command to get equivalent command, but with selection enabled. This is not a command itself.
  // Same as commands above, except they affect selection, too
  ecSelLeft          = ecLeft         + ecSelection;
  ecSelRight         = ecRight        + ecSelection;
  ecSelUp            = ecUp           + ecSelection;
  ecSelDown          = ecDown         + ecSelection;
  ecSelWordLeft      = ecWordLeft     + ecSelection;
  ecSelWordRight     = ecWordRight    + ecSelection;
  ecSelLineStart     = ecLineStart    + ecSelection;
  ecSelLineEnd       = ecLineEnd      + ecSelection;
  ecSelPageUp        = ecPageUp       + ecSelection;
  ecSelPageDown      = ecPageDown     + ecSelection;
  ecSelPageLeft      = ecPageLeft     + ecSelection;
  ecSelPageRight     = ecPageRight    + ecSelection;
  ecSelPageTop       = ecPageTop      + ecSelection;
  ecSelPageBottom    = ecPageBottom   + ecSelection;
  ecSelEditorTop     = ecEditorTop    + ecSelection;
  ecSelEditorBottom  = ecEditorBottom + ecSelection;
  ecSelGotoXY        = ecGotoXY       + ecSelection;  // Data = PPoint
  ecSelectAll        = 199;  // Select entire contents of editor, cursor to end
  ecCopy             = 201;  // Copy selection to clipboard
  ecScrollUp         = 211;  // Scroll up one line leaving cursor position unchanged.
  ecScrollDown       = 212;  // Scroll down one line leaving cursor position unchanged.
  ecScrollLeft       = 213;  // Scroll left one char leaving cursor position unchanged.
  ecScrollRight      = 214;  // Scroll right one char leaving cursor position unchanged.
  ecInsertMode       = 221;  // Set insert mode
  ecOverwriteMode    = 222;  // Set overwrite mode
  ecToggleMode       = 223;  // Toggle ins/ovr mode
  ecNormalSelect     = 231;  // Normal selection mode
  ecColumnSelect     = 232;  // Column selection mode
  ecLineSelect       = 233;  // Line selection mode
  ecMatchBracket     = 250;  // Go to matching bracket
  ecCommentBlock     = 251;  // Comment Block
  ecGotoMarker0      = 301;  // Goto marker
  ecGotoMarker1      = 302;  // Goto marker
  ecGotoMarker2      = 303;  // Goto marker
  ecGotoMarker3      = 304;  // Goto marker
  ecGotoMarker4      = 305;  // Goto marker
  ecGotoMarker5      = 306;  // Goto marker
  ecGotoMarker6      = 307;  // Goto marker
  ecGotoMarker7      = 308;  // Goto marker
  ecGotoMarker8      = 309;  // Goto marker
  ecGotoMarker9      = 310;  // Goto marker
  ecSetMarker0       = 351;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker1       = 352;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker2       = 353;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker3       = 354;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker4       = 355;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker5       = 356;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker6       = 357;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker7       = 358;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker8       = 359;  // Set marker, Data = PPoint - X, Y Pos
  ecSetMarker9       = 360;  // Set marker, Data = PPoint - X, Y Pos
  ecGotFocus         = 480;
  ecLostFocus        = 481;
  ecContextHelp      = 490;  // Help on Word, Data = Word
  ecDeleteLastChar   = 501;  // Delete last char (i.e. backspace key)
  ecDeleteChar       = 502;  // Delete char at cursor (i.e. delete key)
  ecDeleteWord       = 503;  // Delete from cursor to end of word
  ecDeleteLastWord   = 504;  // Delete from cursor to start of word
  ecDeleteBOL        = 505;  // Delete from cursor to beginning of line
  ecDeleteEOL        = 506;  // Delete from cursor to end of line
  ecDeleteLine       = 507;  // Delete current line
  ecClearAll         = 508;  // Delete everything
  ecLineBreak        = 509;  // Break line at current position, move caret to new line
  ecInsertLine       = 510;  // Break line at current position, leave caret
  ecChar             = 511;  // Insert a character at current position
  ecImeStr           = 550;  // Insert character(s) from IME
  ecUndo             = 601;  // Perform undo if available
  ecRedo             = 602;  // Perform redo if available
  ecCut              = 603;  // Cut selection to clipboard
  ecPaste            = 604;  // Paste clipboard to current position
  ecBlockIndent      = 610;  // Indent selection
  ecBlockUnindent    = 611;  // Unindent selection
  ecTab              = 612;  // Tab key
  ecShiftTab         = 613;  // Shift+Tab key
  ecAutoCompletion   = 650;
//  ecUpperCase        = 620; // apply to the current or previous word
//  ecLowerCase        = 621;
  ecToggleCase       = 622;
  ecTitleCase        = 623;
  ecUpperCaseBlock   = 625; // apply to current selection, or current char if no selection
  ecLowerCaseBlock   = 626;
  ecToggleCaseBlock  = 627;
  ecString           = 630;  //Insert a whole string
  ecUserFirst        = 1001; // Start of user-defined commands
