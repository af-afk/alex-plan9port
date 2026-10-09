#include <u.h>
#include <libc.h>
#include "theme.h"

static int dark;
static Theme night = {
	.tag = {
		0x242a30ff,
		0x3b5360ff,
		0x566b78ff,
		0xe8e6e3ff,
		0xffffffff,
	},
	.body = {
		0x1e1e1eff,
		0x5a4a16ff,
		0x74651bff,
		0xe8e6e3ff,
		0xffffffff,
	},
	.rowback = 0x111315ff,
	.rowbord = 0x000000ff,
	.modbutton = 0x3f6f8fff,
	.colbutton = 0x566b78ff,
};

int
themedark(void)
{
	return dark;
}

int
themeiskey(Rune r)
{
	return r == 0x1c;
}

Theme*
themeactive(void)
{
	if(dark)
		return &night;
	return nil;
}

Theme*
themetoggle(void)
{
	dark = !dark;
	return themeactive();
}
