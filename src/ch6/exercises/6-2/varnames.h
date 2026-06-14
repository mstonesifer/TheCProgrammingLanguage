#define CMT  '/'
#define HYPC '-'
#define NL   '\n'
#define NULC '\0'
#define PPIC '#'
#define SPAC ' '
#define STR  '\"'
#define OPC  '('
#define PTRC '*'
#define TABC '\t'
#define UNSC '_'

#define DEF_MC		6
#define MAXWORDLEN	100
#define MAXWORDS	1000

#define num_val(c) c - '0'

struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
int getch(void);
int my_atoi(char *s);
char *strbsearch(char *, char **, int);
int strcomp(char *, char *);
void strcopy(char *, char *);
char *strdupe(char *);
int strlength(char *);
void treeprint(struct tnode *);
void ungetch(int);

