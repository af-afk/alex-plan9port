typedef struct Theme Theme;

enum {
	ThemeBack,
	ThemeHigh,
	ThemeBord,
	ThemeText,
	ThemeHText,
	ThemeNcol
};

struct Theme {
	ulong tag[ThemeNcol];
	ulong body[ThemeNcol];
	ulong rowback;
	ulong rowbord;
	ulong modbutton;
	ulong colbutton;
};

int themedark(void);
int themeiskey(Rune);
Theme *themeactive(void);
Theme *themetoggle(void);
