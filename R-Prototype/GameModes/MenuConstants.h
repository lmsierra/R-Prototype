#ifndef MENU_CONSTANTS_H
#define MENU_CONSTANTS_H

// Navigation Controls
#define MENU_KEY_UP     SYS_KEY_UP
#define MENU_KEY_DOWN   SYS_KEY_DOWN
#define MENU_KEY_ACCEPT SYS_KEY_SPACE

// Text size
#define SIZE_TITLE               50.f
#define SIZE_OPTION              16.f
#define SIZE_NOTE                12.f
#define SIZE_MARKER              16.f

// Margins
#define MARGIN_OPTIONS           11.f
#define MARGIN_OPTION_FROM_TITLE 32.f
#define MARGIN_MARKER             4.f
#define MARGIN_TOP_BOTTOM_SCR    16.f
#define MARGIN_LEFT_RIGHT_SCR    16.f

// Main menu texts
extern const char* ARRAY_DEVEL_NOTES[];
extern const char* ARRAY_HINTS [];

#define NUM_OPTIONS 4
#define NUM_NOTES   1 
#define NUM_HINTS   2

#define TEXT_TITLE                "R-PROTOTYPE"
#define TEXT_DEVELOPER_NOTE_2     "USING SWALIB BY JONBHO"
#define TEXT_MARKER_TOP_LEFT      "["
#define TEXT_MARKER_TOP_RIGHT     "]"
#define TEXT_MARKER_BOTTOM_LEFT   "{"
#define TEXT_MARKER_BOTTOM_RIGHT  "}"

// How to play menu texts
extern const char* ARRAY_INSTRUCTIONS[];
extern const char* ARRAY_INSTR_HINTS[];
#define NUM_INSTR       4
#define NUM_INSTR_HINTS 1

#define TEXT_INSTR_TITLE "HOW TO PLAY"


// Level selection menu texts
extern const char* ARRAY_LVL[];
#define TEXT_TITLE_LVL "LOAD LEVEL"
#define NUM_LEVELS 5


// Pause menu texts
extern const char* ARRAY_PAUSE_OPTIONS[];
#define NUM_PAUSE_OPTIONS 3
#define TEXT_TITLE_PAUSE "PAUSE"


#endif /* MENU_CONSTANTS_H */
