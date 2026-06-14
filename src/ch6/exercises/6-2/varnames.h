#define CMT  '/'
#define HYPC '-'
#define NL   '\n'
#define NULC '\0'
#define PPIC '#'
#define SPAC ' '
#define STR  '\"'
#define TABC '\t'

#define DEF_MC		6
#define MAXWORDLEN	100
#define MAXWORDS	1000

#define num_val(c) c - '0'

char *strbsearch(char *, char **, int);
int getword(char *, int);
int getch(void);
int my_atoi(char *s);
int strcomp(char *, char *);
void strcopy(char *, char *);
void ungetch(int);
