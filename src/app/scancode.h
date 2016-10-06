/*
Port of
Simple DirectMedia Layer PHI_scancode.h
From Sam Lantinga <slouken@libsdl.org>
*/

#pragma once

typedef enum
{
    PHI_SCANCODE_UNKNOWN = 0,

    PHI_SCANCODE_A = 4,
    PHI_SCANCODE_B = 5,
    PHI_SCANCODE_C = 6,
    PHI_SCANCODE_D = 7,
    PHI_SCANCODE_E = 8,
    PHI_SCANCODE_F = 9,
    PHI_SCANCODE_G = 10,
    PHI_SCANCODE_H = 11,
    PHI_SCANCODE_I = 12,
    PHI_SCANCODE_J = 13,
    PHI_SCANCODE_K = 14,
    PHI_SCANCODE_L = 15,
    PHI_SCANCODE_M = 16,
    PHI_SCANCODE_N = 17,
    PHI_SCANCODE_O = 18,
    PHI_SCANCODE_P = 19,
    PHI_SCANCODE_Q = 20,
    PHI_SCANCODE_R = 21,
    PHI_SCANCODE_S = 22,
    PHI_SCANCODE_T = 23,
    PHI_SCANCODE_U = 24,
    PHI_SCANCODE_V = 25,
    PHI_SCANCODE_W = 26,
    PHI_SCANCODE_X = 27,
    PHI_SCANCODE_Y = 28,
    PHI_SCANCODE_Z = 29,

    PHI_SCANCODE_1 = 30,
    PHI_SCANCODE_2 = 31,
    PHI_SCANCODE_3 = 32,
    PHI_SCANCODE_4 = 33,
    PHI_SCANCODE_5 = 34,
    PHI_SCANCODE_6 = 35,
    PHI_SCANCODE_7 = 36,
    PHI_SCANCODE_8 = 37,
    PHI_SCANCODE_9 = 38,
    PHI_SCANCODE_0 = 39,

    PHI_SCANCODE_RETURN = 40,
    PHI_SCANCODE_ESCAPE = 41,
    PHI_SCANCODE_BACKSPACE = 42,
    PHI_SCANCODE_TAB = 43,
    PHI_SCANCODE_SPACE = 44,

    PHI_SCANCODE_MINUS = 45,
    PHI_SCANCODE_EQUALS = 46,
    PHI_SCANCODE_LEFTBRACKET = 47,
    PHI_SCANCODE_RIGHTBRACKET = 48,
    PHI_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    PHI_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate PHI_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    PHI_SCANCODE_SEMICOLON = 51,
    PHI_SCANCODE_APOSTROPHE = 52,
    PHI_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    PHI_SCANCODE_COMMA = 54,
    PHI_SCANCODE_PERIOD = 55,
    PHI_SCANCODE_SLASH = 56,

    PHI_SCANCODE_CAPSLOCK = 57,

    PHI_SCANCODE_F1 = 58,
    PHI_SCANCODE_F2 = 59,
    PHI_SCANCODE_F3 = 60,
    PHI_SCANCODE_F4 = 61,
    PHI_SCANCODE_F5 = 62,
    PHI_SCANCODE_F6 = 63,
    PHI_SCANCODE_F7 = 64,
    PHI_SCANCODE_F8 = 65,
    PHI_SCANCODE_F9 = 66,
    PHI_SCANCODE_F10 = 67,
    PHI_SCANCODE_F11 = 68,
    PHI_SCANCODE_F12 = 69,

    PHI_SCANCODE_PRINTSCREEN = 70,
    PHI_SCANCODE_SCROLLLOCK = 71,
    PHI_SCANCODE_PAUSE = 72,
    PHI_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    PHI_SCANCODE_HOME = 74,
    PHI_SCANCODE_PAGEUP = 75,
    PHI_SCANCODE_DELETE = 76,
    PHI_SCANCODE_END = 77,
    PHI_SCANCODE_PAGEDOWN = 78,
    PHI_SCANCODE_RIGHT = 79,
    PHI_SCANCODE_LEFT = 80,
    PHI_SCANCODE_DOWN = 81,
    PHI_SCANCODE_UP = 82,

    PHI_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    PHI_SCANCODE_KP_DIVIDE = 84,
    PHI_SCANCODE_KP_MULTIPLY = 85,
    PHI_SCANCODE_KP_MINUS = 86,
    PHI_SCANCODE_KP_PLUS = 87,
    PHI_SCANCODE_KP_ENTER = 88,
    PHI_SCANCODE_KP_1 = 89,
    PHI_SCANCODE_KP_2 = 90,
    PHI_SCANCODE_KP_3 = 91,
    PHI_SCANCODE_KP_4 = 92,
    PHI_SCANCODE_KP_5 = 93,
    PHI_SCANCODE_KP_6 = 94,
    PHI_SCANCODE_KP_7 = 95,
    PHI_SCANCODE_KP_8 = 96,
    PHI_SCANCODE_KP_9 = 97,
    PHI_SCANCODE_KP_0 = 98,
    PHI_SCANCODE_KP_PERIOD = 99,

    PHI_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    PHI_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
    PHI_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    PHI_SCANCODE_KP_EQUALS = 103,
    PHI_SCANCODE_F13 = 104,
    PHI_SCANCODE_F14 = 105,
    PHI_SCANCODE_F15 = 106,
    PHI_SCANCODE_F16 = 107,
    PHI_SCANCODE_F17 = 108,
    PHI_SCANCODE_F18 = 109,
    PHI_SCANCODE_F19 = 110,
    PHI_SCANCODE_F20 = 111,
    PHI_SCANCODE_F21 = 112,
    PHI_SCANCODE_F22 = 113,
    PHI_SCANCODE_F23 = 114,
    PHI_SCANCODE_F24 = 115,
    PHI_SCANCODE_EXECUTE = 116,
    PHI_SCANCODE_HELP = 117,
    PHI_SCANCODE_MENU = 118,
    PHI_SCANCODE_SELECT = 119,
    PHI_SCANCODE_STOP = 120,
    PHI_SCANCODE_AGAIN = 121,   /**< redo */
    PHI_SCANCODE_UNDO = 122,
    PHI_SCANCODE_CUT = 123,
    PHI_SCANCODE_COPY = 124,
    PHI_SCANCODE_PASTE = 125,
    PHI_SCANCODE_FIND = 126,
    PHI_SCANCODE_MUTE = 127,
    PHI_SCANCODE_VOLUMEUP = 128,
    PHI_SCANCODE_VOLUMEDOWN = 129,
/* not sure whether there's a reason to enable these */
/*     PHI_SCANCODE_LOCKINGCAPSLOCK = 130,  */
/*     PHI_SCANCODE_LOCKINGNUMLOCK = 131, */
/*     PHI_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    PHI_SCANCODE_KP_COMMA = 133,
    PHI_SCANCODE_KP_EQUALSAS400 = 134,

    PHI_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    PHI_SCANCODE_INTERNATIONAL2 = 136,
    PHI_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
    PHI_SCANCODE_INTERNATIONAL4 = 138,
    PHI_SCANCODE_INTERNATIONAL5 = 139,
    PHI_SCANCODE_INTERNATIONAL6 = 140,
    PHI_SCANCODE_INTERNATIONAL7 = 141,
    PHI_SCANCODE_INTERNATIONAL8 = 142,
    PHI_SCANCODE_INTERNATIONAL9 = 143,
    PHI_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
    PHI_SCANCODE_LANG2 = 145, /**< Hanja conversion */
    PHI_SCANCODE_LANG3 = 146, /**< Katakana */
    PHI_SCANCODE_LANG4 = 147, /**< Hiragana */
    PHI_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    PHI_SCANCODE_LANG6 = 149, /**< reserved */
    PHI_SCANCODE_LANG7 = 150, /**< reserved */
    PHI_SCANCODE_LANG8 = 151, /**< reserved */
    PHI_SCANCODE_LANG9 = 152, /**< reserved */

    PHI_SCANCODE_ALTERASE = 153, /**< Erase-Eaze */
    PHI_SCANCODE_SYSREQ = 154,
    PHI_SCANCODE_CANCEL = 155,
    PHI_SCANCODE_CLEAR = 156,
    PHI_SCANCODE_PRIOR = 157,
    PHI_SCANCODE_RETURN2 = 158,
    PHI_SCANCODE_SEPARATOR = 159,
    PHI_SCANCODE_OUT = 160,
    PHI_SCANCODE_OPER = 161,
    PHI_SCANCODE_CLEARAGAIN = 162,
    PHI_SCANCODE_CRSEL = 163,
    PHI_SCANCODE_EXSEL = 164,

    PHI_SCANCODE_KP_00 = 176,
    PHI_SCANCODE_KP_000 = 177,
    PHI_SCANCODE_THOUSANDSSEPARATOR = 178,
    PHI_SCANCODE_DECIMALSEPARATOR = 179,
    PHI_SCANCODE_CURRENCYUNIT = 180,
    PHI_SCANCODE_CURRENCYSUBUNIT = 181,
    PHI_SCANCODE_KP_LEFTPAREN = 182,
    PHI_SCANCODE_KP_RIGHTPAREN = 183,
    PHI_SCANCODE_KP_LEFTBRACE = 184,
    PHI_SCANCODE_KP_RIGHTBRACE = 185,
    PHI_SCANCODE_KP_TAB = 186,
    PHI_SCANCODE_KP_BACKSPACE = 187,
    PHI_SCANCODE_KP_A = 188,
    PHI_SCANCODE_KP_B = 189,
    PHI_SCANCODE_KP_C = 190,
    PHI_SCANCODE_KP_D = 191,
    PHI_SCANCODE_KP_E = 192,
    PHI_SCANCODE_KP_F = 193,
    PHI_SCANCODE_KP_XOR = 194,
    PHI_SCANCODE_KP_POWER = 195,
    PHI_SCANCODE_KP_PERCENT = 196,
    PHI_SCANCODE_KP_LESS = 197,
    PHI_SCANCODE_KP_GREATER = 198,
    PHI_SCANCODE_KP_AMPERSAND = 199,
    PHI_SCANCODE_KP_DBLAMPERSAND = 200,
    PHI_SCANCODE_KP_VERTICALBAR = 201,
    PHI_SCANCODE_KP_DBLVERTICALBAR = 202,
    PHI_SCANCODE_KP_COLON = 203,
    PHI_SCANCODE_KP_HASH = 204,
    PHI_SCANCODE_KP_SPACE = 205,
    PHI_SCANCODE_KP_AT = 206,
    PHI_SCANCODE_KP_EXCLAM = 207,
    PHI_SCANCODE_KP_MEMSTORE = 208,
    PHI_SCANCODE_KP_MEMRECALL = 209,
    PHI_SCANCODE_KP_MEMCLEAR = 210,
    PHI_SCANCODE_KP_MEMADD = 211,
    PHI_SCANCODE_KP_MEMSUBTRACT = 212,
    PHI_SCANCODE_KP_MEMMULTIPLY = 213,
    PHI_SCANCODE_KP_MEMDIVIDE = 214,
    PHI_SCANCODE_KP_PLUSMINUS = 215,
    PHI_SCANCODE_KP_CLEAR = 216,
    PHI_SCANCODE_KP_CLEARENTRY = 217,
    PHI_SCANCODE_KP_BINARY = 218,
    PHI_SCANCODE_KP_OCTAL = 219,
    PHI_SCANCODE_KP_DECIMAL = 220,
    PHI_SCANCODE_KP_HEXADECIMAL = 221,

    PHI_SCANCODE_LCTRL = 224,
    PHI_SCANCODE_LSHIFT = 225,
    PHI_SCANCODE_LALT = 226, /**< alt, option */
    PHI_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    PHI_SCANCODE_RCTRL = 228,
    PHI_SCANCODE_RSHIFT = 229,
    PHI_SCANCODE_RALT = 230, /**< alt gr, option */
    PHI_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

    PHI_SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

    /* @} *//* Usage page 0x07 */

    /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
    /* @{ */

    PHI_SCANCODE_AUDIONEXT = 258,
    PHI_SCANCODE_AUDIOPREV = 259,
    PHI_SCANCODE_AUDIOSTOP = 260,
    PHI_SCANCODE_AUDIOPLAY = 261,
    PHI_SCANCODE_AUDIOMUTE = 262,
    PHI_SCANCODE_MEDIASELECT = 263,
    PHI_SCANCODE_WWW = 264,
    PHI_SCANCODE_MAIL = 265,
    PHI_SCANCODE_CALCULATOR = 266,
    PHI_SCANCODE_COMPUTER = 267,
    PHI_SCANCODE_AC_SEARCH = 268,
    PHI_SCANCODE_AC_HOME = 269,
    PHI_SCANCODE_AC_BACK = 270,
    PHI_SCANCODE_AC_FORWARD = 271,
    PHI_SCANCODE_AC_STOP = 272,
    PHI_SCANCODE_AC_REFRESH = 273,
    PHI_SCANCODE_AC_BOOKMARKS = 274,

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
    /* @{ */

    PHI_SCANCODE_BRIGHTNESSDOWN = 275,
    PHI_SCANCODE_BRIGHTNESSUP = 276,
    PHI_SCANCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    PHI_SCANCODE_KBDILLUMTOGGLE = 278,
    PHI_SCANCODE_KBDILLUMDOWN = 279,
    PHI_SCANCODE_KBDILLUMUP = 280,
    PHI_SCANCODE_EJECT = 281,
    PHI_SCANCODE_SLEEP = 282,

    PHI_SCANCODE_APP1 = 283,
    PHI_SCANCODE_APP2 = 284,

    /* @} *//* Walther keys */

    /* Add any other keys here. */

    PHI_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
} scancode;
