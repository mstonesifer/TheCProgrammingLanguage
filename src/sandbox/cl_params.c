#include <stdio.h>
#include <string.h>

#define NUL '\0'
#define ADD_PARM 1 
#define SUB_PARM 1 << 1
#define DUB_PARM 1 << 2

#define ERR_PARAM_OOB 1		/* Parameter was out of bounds */

/* this program serves as a training ground to better
 * understand the input arguments passed into a c
 * program. it handles the params +a -b <number> --c.
 * each param is optional and the program will print
 * a message indicating which flags were set and if
 * the -b flag is set, what value was passed in with
 * it.
 */
int main(int argc, char *argv[])
{
	int i, c;
	int flags = 0;
	char *bvals;

	printf("Number of args: %i\n", argc);
	for (i = 0; i < argc; i++)
		printf("Arguemnt %i: %s\n", i, *(argv + i));

	while (--argc > 0) {
		if (*(*++argv) == '+')
			while (NUL != (c = *++argv[0]))
				switch (c) {
					case 'a':
						flags |= ADD_PARM;
						break;
					default:
						printf("cl_params: usage +a\n");
						return ERR_PARAM_OOB;
						break;
				}
	
		if(*(*argv) == '-') {
			if (*(*argv + 1) == '-') {
				*++argv[0];	/* advance over second - */
				while (NUL != (c = *++argv[0]))
					switch (c) {
						case 'c':
							flags |= DUB_PARM;
							break;
						default:
							printf("cl_params: usage --c\n");
							return ERR_PARAM_OOB;
							break;
					}
			} else {
				while (NUL != (c = *++argv[0])) {
					switch (c) {
						case 'b':
							flags |= SUB_PARM;
							if (NULL == (bvals = *(argv + 1)) ||
									*bvals == '+' ||
									*bvals == '-')
								bvals = "1000";
							printf("bvals = %c\n", *bvals);
							break;
						default:
							printf("cl_params: usage -b [number]\n");
							return ERR_PARAM_OOB;
							break;
					}
				}
			}
		}
	}

	printf("Flag set = %4b\n", flags);
	printf("ADD_PARM = %4b\n", ADD_PARM);
	printf("SUB_PARM = %4b\n", SUB_PARM);
	printf("DUB_PARM = %4b\n", DUB_PARM);
	if (flags & ADD_PARM)
		printf("You get extra parm!\n"); 
	if (flags & SUB_PARM)
		printf("Your dinner will be $%s\n", bvals);
	if (flags & DUB_PARM)
		printf("Your dinner is paid for!\n");

	return 0;
}
