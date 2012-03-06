/* See LICENSE file for copyright and license details. */

/* appearance */

static const char font[] = "-artwiz-cureextra-medium-r-normal--11-110-75-75-p-90-iso8859-1";
static const char colors[MAXCOLORS][ColLast][10] = {
	/* border     fg         bg       */
	{ "#111111", "#696969", "#020202" }, /* 1 = normal */
    { "#111111", "#DDDDDD", "#020202" }, /* 2 = selected */
	{ "#111111", "#66CD00", "#020202" }, /* 3 = green */
	{ "#111111", "#BF85CC", "#020202" }, /* 4 = yellow */
	{ "#111111", "#6096BF", "#020202" }, /* 5 = cyan */
	{ "#111111", "#7E62B3", "#020202" }, /* 6 = magenta */
	{ "#111111", "#899CA1", "#020202" }, /* 7 = grey */
    { "#111111", "#6633FF", "#020202" }, /* 8 = blue */
    { "#111111", "#CC0000", "#020202" }, /* 9 = red  */
};
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gap pixel between windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool clicktofocus      = True;     /* Change focus only on click */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const unsigned int statusmon = 0;        /* On which monitor should the status appear */

static const Rule rules[] = {
	/* class          instance     title             tags mask   floating     centred   monitor*/
	{ "Gimp",         NULL,        NULL,             0,          True,        False,      -1 },
	{ "MPlayer",      NULL,        NULL,             0,          True,        True,       -1 },
	{ "Vlc",          NULL,        NULL,             0,          True,        True,       -1 },
	{ "Chromium",     NULL,        NULL,             1 << 4,     False,       False,       0 },
	{ "Firefox",      NULL,        NULL,             1 << 4,     True,        True,        0 },
	{ "Firefox",      "Navigator", NULL,             1 << 4,     False,       False,       0 },
    { "URxvt",        NULL,        "ncmpcpp",        1 << 5,     False,       False,      -1 },
    { "URxvt",        NULL,        "weechat-curses", 1 << 3,     False,       False,      -1 },
};

/* layout(s) */
static const float mfact      = 0.5;   /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;     /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },        /* first entry is default */
	{ "[M]",      monocle },
	{ "[F]",      NULL },        /* no layout function means floating behavior */
	{ "[B]",      bstack },
	{ "[G]",      gaplessgrid },
	{ "[P]",      pidgin },
};

/* tagging */
static const Tag tags[2][6] = {
	/* name       layout           mfact    nmaster */
	{
	{ "Main",     &layouts[4],     -1,      -1 },
	{ "Term",     &layouts[4],     -1,      -1 },
	{ "Dev",      &layouts[0],     0.80,    -1 },
	{ "Chat",     &layouts[4],     -1,      -1 },
	{ "Web",      &layouts[1],     -1,      -1 },
	{ "Music",    &layouts[4],     -1,      -1 },
	},{
	{ "Main",     &layouts[4],     -1,      -1 },
	{ "Term",     &layouts[4],     -1,      -1 },
	{ "Chat",     &layouts[1],     -1,      -1 },
	{ "Web",      &layouts[1],     0.80,    -1 },
    { "Music",    &layouts[4],     -1,      -1 },
	{ "Misc",     &layouts[4],     -1,      -1 },
	}
};

/* key definitions */
#define ALTKEY Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char terminal[]       = "urxvt";
static const char scratchpadname[] = "scratchy";
static const char *dmenucmd[]      = { "dmenu_run", "-i", "-p", "Run command:", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]       = { terminal, NULL };
static const char *transterm[]     = { terminal, "-tr", "-sh", "35", NULL };
static const char *musiccmd[]      = { terminal, "-e", "ncmpcpp", NULL };
static const char *scratchpadcmd[] = { terminal, "-name", scratchpadname, "-geometry", "150x40", NULL };
static const char *filemancmd[]    = { "thunar", NULL };
static const char *browsercmd[]    = { "chromium", NULL };
/* static const char *altbrowsercmd[] = { "firefox", NULL }; */
static const char *editorcmd[]     = { terminal, "-e", "vim", NULL };
static const char *volmcmd[]       = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *voldcmd[]       = { "amixer", "-q", "sset", "Master", "1-", "unmute", NULL };
static const char *volucmd[]       = { "amixer", "-q", "sset", "Master", "1+", "unmute", NULL };
static const char *ncmpcppvoldcmd[]   = { "ncmpcpp", "volume", "-2", NULL };
static const char *ncmpcppvolucmd[]   = { "ncmpcpp", "volume", "+2", NULL };
static const char *ncmpcpptogglecmd[] = { "ncmpcpp", "toggle", NULL };
static const char *ncmpcppstopcmd[]   = { "ncmpcpp", "stop", NULL };
static const char *ncmpcppprevcmd[]   = { "ncmpcpp", "prev", NULL };
static const char *ncmpcppnextcmd[]   = { "ncmpcpp", "next", NULL };
static const char *screenshotcmd[] = { "printscreen", NULL };
static const char *lockcmd[]       = { "slock", NULL };
static const char *irccmd[]        = { terminal, "-e", "weechat-curses", NULL };

static Key keys[] = {
	/* modifier                     key         function        argument */
	{ ALTKEY,                       XK_p,       spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY|ControlMask,           XK_Return,  spawn,          {.v = transterm } },
	{ MODKEY|ShiftMask,             XK_n,       spawn,          {.v = musiccmd } },
    { MODKEY|ShiftMask,             XK_m,       spawn,          {.v = irccmd } },
	{ MODKEY,                       XK_x,       togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_t,       spawn,          {.v = filemancmd } },
	{ MODKEY,                       XK_f,       spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_e,       spawn,          {.v = editorcmd } },
	{ 0,                            0x1008ff12, spawn,          {.v = volmcmd } },
	{ 0,                            0x1008ff11, spawn,          {.v = voldcmd } },
	{ 0,                            0x1008ff13, spawn,          {.v = volucmd } },
	{ MODKEY,                       0x1008ff11, spawn,          {.v = ncmpcppvoldcmd } },
	{ MODKEY,                       0x1008ff13, spawn,          {.v = ncmpcppvolucmd } },
	{ 0,                            0x1008ff14, spawn,          {.v = ncmpcpptogglecmd } },
    { 0,                            0x1008ff15, spawn,          {.v = ncmpcppstopcmd } },
	{ 0,                            0x1008ff16, spawn,          {.v = ncmpcppprevcmd } },
	{ 0,                            0x1008ff17, spawn,          {.v = ncmpcppnextcmd } },
	{ 0,                            XK_Print,   spawn,          {.v = screenshotcmd } },
	{ MODKEY|ALTKEY,                XK_m,       togglemax,      {0} },
	{ MODKEY|ShiftMask,             XK_b,       togglebar,      {0} },
	{ MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,       pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,       pushup,         {0} },
	{ MODKEY,                       XK_a,       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_z,       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.01} },
	{ ALTKEY,                       XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,     view,           {0} },
	{ ALTKEY,                       XK_Tab,     focusurgent,    {0} },
	{ MODKEY,                       XK_Escape,  killclient,     {0} },
	{ MODKEY|ControlMask,           XK_n,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_m,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_f,       setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_b,       setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_g,       setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ControlMask,           XK_p,       setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },
	{ MODKEY,                       XK_0,       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Left,    cycle,          {.i = -1 } },
	{ MODKEY,                       XK_Right,   cycle,          {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,    tagcycle,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Right,   tagcycle,       {.i = +1 } },
	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	{ 0,                            XK_Pause,   spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_Escape,  quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = +1} },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        cycle,          {.i = -1} },
	{ ClkTagBar,            0,              Button5,        cycle,          {.i = +1} },
};

