#include "../suckless-themes/ocean_theme.h"
#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 25;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";


static const char *colors[][4]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_black, col_black, col_pink,	col_pink  },
	[SchemeSel]  = { col_black, col_black, col_black,	col_pink },
	//[2] 		 = { col_yellow, col_blue, col_green, col_pink },
	[2] 		 = { col_black, col_black, col_black, col_black },
};



//static const char *colors[][3]      = {
//	/*               fg         bg         border   */
//	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
//};

static const char *const autostart[] = {
	"feh", "--bg-fill", "/home/wint3rmute/Pictures/wallpapers/vera.png", NULL,
	"betterlockscreen", "-l", "dimblur", NULL,
	"picom", "--corner-radius", "10", NULL,
	"setxkbmap", "pl", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Flamehsot",     NULL,       NULL,       0,            1,           -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static int dmenu_color_counter = 0;
static char dmenu_current_color[] = "#82AAFF";
//static char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb",  dmenu_current_color, "-sf", col_gray1, NULL };
static char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
// rofi -show Dashboard -modi Dashboard:./dashboard.sh -lines 6 -width 30
static char *dashboard_cmd[] = { "rofi", "-show", "Dashboard", "-modi", "Dashboard:/home/wint3rmute/code/scripts/dashboard.sh", "-lines", "6", "-width", "30", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *thunar_cmd[]  = { "thunar", NULL };
static const char *flameshot_cmd[]  = { "flameshot", "gui", NULL };
static const char *lockscreen_cmd[] = { "betterlockscreen", "--lock", "dimblur", NULL };

static const char *brightness_up_cmd[] = { "/home/wint3rmute/code/scripts/brightness", "up", NULL };
static const char *brightness_down_cmd[] = { "/home/wint3rmute/code/scripts/brightness", "down", NULL };

static const char *kbd_brightness_up_cmd[] = { "/home/wint3rmute/code/scripts/keyboard", "3", NULL };
static const char *kbd_brightness_down_cmd[] = { "/home/wint3rmute/code/scripts/keyboard", "0", NULL };

static const char *volume_up_cmd[] = { "/home/wint3rmute/code/scripts/volume", "up", NULL };
static const char *volume_down_cmd[] = { "/home/wint3rmute/code/scripts/volume", "down", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          { .v = dmenucmd } },
	//{ MODKEY,                       XK_p,  spawn,          {.v = flameshot_cmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = thunar_cmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockscreen_cmd } },
	{ MODKEY,                       XK_space, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ 0,							XF86XK_MonBrightnessUp, spawn, { .v = brightness_up_cmd } },
	{ 0,							XF86XK_MonBrightnessDown, spawn, { .v = brightness_down_cmd } },
	{ 0,							XF86XK_KbdBrightnessUp, spawn, { .v = kbd_brightness_up_cmd } },
	{ 0,							XF86XK_KbdBrightnessDown, spawn, { .v = kbd_brightness_down_cmd } },
	{ 0,							XF86XK_AudioRaiseVolume, spawn, { .v = volume_up_cmd } },
	{ 0,							XF86XK_AudioLowerVolume, spawn, { .v = volume_down_cmd } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

