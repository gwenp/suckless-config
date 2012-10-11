/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbgcolor[] = "#222222";
static const char normfgcolor[] = "#bbbbbb";
static const char selbgcolor[]  = "#005577";
static const char selfgcolor[]  = "#eeeeee";
static const char before[]      = "<";
static const char after[]       = ">";
static const int  tabwidth      = 200;
static const Bool foreground    = False;

#define MODKEY ControlMask
static Key keys[] = { \
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, focusonce,      { 0 } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          { 0 } },
	{ MODKEY,                     XK_t, focusonce,      { 0 } },
	{ MODKEY,                     XK_t, spawn,          { 0 } },
	{ MODKEY,                     XK_s, focusonce,      { 0 } },
	{ MODKEY,                     XK_s, spawn,          { 0 } },
	{ MODKEY,                     XK_q,      rotate,         { .i = +1 } },
	{ MODKEY,                     XK_d,      rotate,         { .i = -1 } },
	{ MODKEY|Mod1Mask,                     XK_Left,      rotate,         { .i = +1 } },
	{ MODKEY|Mod1Mask,                     XK_Right,      rotate,         { .i = -1 } },
	{ MODKEY,                       XK_Tab,    rotate,         { .i = 0 } },
	{ MODKEY,                       XK_KP_1,      move,           { .i = 0 } },
	{ MODKEY,                       XK_KP_2,      move,           { .i = 1 } },
	{ MODKEY,                       XK_KP_3,      move,           { .i = 2 } },
	{ MODKEY,                       XK_KP_4,      move,           { .i = 3 } },
	{ MODKEY,                       XK_KP_5,      move,           { .i = 4 } },
	{ MODKEY,                       XK_KP_6,      move,           { .i = 5 } },
	{ MODKEY,                       XK_KP_7,      move,           { .i = 6 } },
	{ MODKEY,                       XK_KP_8,      move,           { .i = 7 } },
	{ MODKEY,                       XK_KP_9,      move,           { .i = 8 } },
	{ MODKEY,                       XK_KP_0,      move,           { .i = 9 } },
	{ MODKEY,                       XK_w,      killclient,     { 0 } },
};
