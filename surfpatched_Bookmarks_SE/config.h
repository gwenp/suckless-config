/* modifier 0 means no modifier */
static char *useragent      = "Surf/"VERSION" (X11; U; Unix; en-US) AppleWebKit/531.2+ Compatible (Safari)";
static char *progress       = "#0066FF";
static char *progress_untrust = "#FF6600";
static char *progress_trust = "#00FF00";
static char *stylefile      = ".surf/style.css";
static char *scriptfile     = ".surf/script.js";
static char *cookiefile     = ".surf/cookies.txt";
static time_t sessiontime   = 3600;
static char *cafile         = "/etc/ssl/certs/ca-certificates.crt";
static char *strictssl      = FALSE; /* Refuse untrusted SSL connections */
#define HIDE_BACKGROUND FALSE
#define SPATIAL_BROWSING TRUE

#define SETPROP(p, q)     { .v = (char *[]){ "/bin/sh", "-c", \
	"prop=\"`xprop -id $2 $0 | cut -d '\"' -f 2 | dmenu`\" &&" \
	"xprop -id $2 -f $1 8s -set $1 \"$prop\"", \
	p, q, winid, NULL } }
#define DOWNLOAD(d) {			  \
	.v = (char *[]){ "/bin/sh", "-c", \
	"xterm -e \"wget '$0' \
--load-cookies ~/.surf/cookies.txt \
--user-agent '$1' ; sleep 5\"", d, useragent, NULL } }
#define MODKEY GDK_CONTROL_MASK

#define BM_PICK { .v = (char *[]){ "/bin/sh", "-c", \
"xprop -id $0 -f _SURF_GO 8s -set _SURF_GO \
`cat ~/.surf/bookmarks | dmenu -l 20 | awk '{print $1}' || exit 0`", \
winid, NULL } }

#define BM_ADD { .v = (char *[]){ "/bin/sh", "-c", \
"(echo `xprop -id $0 _SURF_URI | cut -d '\"' -f 2` | dmenu && \
cat ~/.surf/bookmarks) | sort -u > ~/.surf/bookmarks_new && \
mv ~/.surf/bookmarks_new ~/.surf/bookmarks", \
winid, NULL } }

static SearchEngine searchengines[] = {
	{ "g",	"http://www.google.com/search?q=%s" },
	{ "c",	"http://www.cnrtl.fr/lexicographie/%s"  },
	{ "d",	"https://duckduckgo.com/?q=%s"  },
	{ "i",	"http://www.imdb.com/find?s=tt&q=%s"  },
	{ "p",	"http://manual.pohape.ru/%s" },
	{ "o",	"http://goosh.org/?q=%s" },
	{ "e",	"http://seeks.fr/search?q=%s&action=expand&expansion=1" },
	{ "s",	"http://s.s/search?q=%s&action=expand&expansion=1" },
	{ "m",	"http://www.die.net/search/?q=%s" },
	{ "w",	"https://secure.wikimedia.org/wikipedia/en/w/index.php?search=%s" },
	{ "f",	"https://secure.wikimedia.org/wikipedia/fr/w/index.php?search=%s" },
	{ "y",	"http://www.youtube.com/results?search_query=%s"  },
	{ "t",	"http://thepiratebay.se/search/%s"  },
	{ "fr2en",	"http://www.wordreference.com/fren/%s" },
	{ "en2fr",	"http://www.wordreference.com/enfr/%s" },
};

static Key keys[] = {
    /* modifier	            keyval      function    arg             Focus */
    { MODKEY|GDK_SHIFT_MASK,GDK_r,      reload,     { .b = TRUE } },
    { MODKEY,               GDK_r,      reload,     { .b = FALSE } },
    { MODKEY|GDK_SHIFT_MASK,GDK_p,      print,      { 0 } },
    { MODKEY,               GDK_p,      clipboard,  { .b = TRUE } },
    { MODKEY,               GDK_y,      clipboard,  { .b = FALSE } },
    { MODKEY|GDK_SHIFT_MASK,GDK_j,      zoom,       { .i = -1 } },
    { MODKEY|GDK_SHIFT_MASK,GDK_k,      zoom,       { .i = +1 } },
    { MODKEY|GDK_SHIFT_MASK,GDK_i,      zoom,       { .i = 0  } },
    { MODKEY,               GDK_l,      navigate,   { .i = +1 } },
    { MODKEY,               GDK_h,      navigate,   { .i = -1 } },
    { MODKEY,               GDK_j,           scroll_v,   { .i = +1 } },
    { MODKEY,               GDK_k,           scroll_v,   { .i = -1 } },
    { MODKEY,               GDK_b,           scroll_v,   { .i = -10000 } },
    { MODKEY,               GDK_space,       scroll_v,   { .i = +10000 } },
    { MODKEY,               GDK_i,           scroll_h,   { .i = +1 } },
    { MODKEY,               GDK_u,           scroll_h,   { .i = -1 } },
    { 0,                    GDK_Escape, stop,       { 0 } },
    { MODKEY,               GDK_o,      source,     { 0 } },
    { MODKEY,               GDK_g,      spawn,      SETPROP("_SURF_URI", "_SURF_GO") },
    { MODKEY,               GDK_f,      spawn,      SETPROP("_SURF_FIND", "_SURF_FIND") },
    { MODKEY,               GDK_n,      find,       { .b = TRUE } },
    { MODKEY|GDK_SHIFT_MASK,GDK_n,      find,       { .b = FALSE } },


    { MODKEY,               GDK_a,      spawn,      BM_PICK },
    { MODKEY|GDK_SHIFT_MASK,GDK_b,      spawn,      BM_ADD },
};
