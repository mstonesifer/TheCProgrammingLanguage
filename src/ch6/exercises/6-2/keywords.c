#define NAKEYS (sizeof(keytab) / sizeof(char *))	/* number of all clang keywords */
#define NVKEYS (sizeof varkeys / sizeof(char *))	/* num of clang keywords that preceed var name */

/* all clang keywords */
char *keytab[] = {
	"auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"extern",
	"float",
	"for",
	"goto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while"
};

/* subet of clang keywords which indicate a variable name */
char *varkeys[] = {
	"char",
	"double",
	"enum",
	"float",
	"int",
	"long",
	"register",
	"short"
};
