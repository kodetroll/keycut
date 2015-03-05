/* keycut.c - A C Program that breaks an ASCII HEX string into smaller chunks with
 * configurable chunk size and separator.
 *
 * (C) 2015 KB4OID Labs - A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: March 2015
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define CHOPCHAR '|'
#define CHOPNUM 16
#define VER_MAJOR 0
#define VER_MINOR 99

/* Flag set by '--verbose'. */
static int verbose = 0;

/* Flag set by '--debug'. */
static int debug = 0;

void version(void);
void usage(unsigned char * name);

void version(void)
{
	printf("Version %d.%d\n",VER_MAJOR,VER_MINOR);
}

void usage(unsigned char * name)
{
	printf("%s <OPTIONS> <VALUE>\n",name);
	printf("where: <OPTIONS>\n");
	printf("    --help -h         Show Program Help (This info).\n");
	printf("    --version -v      Show version info and exit.\n");
	printf("    --chop -c <CHOP>  Set CHOP character.\n");
	printf("    --size -s <SIZE>  Set size to cut to.\n");
	printf("    --data -d <DATA>  Set VALUE to DATA.\n");
	printf("    <VALUE>        VALUE to be cut\n");
	printf("\n");
}

int main(int argc, char * argv[])
{
	int i=0;
	int j=0;
	int k=0;
	int gotin = 0;
	unsigned char chopchar = CHOPCHAR;
	int chopsize = CHOPNUM;
	unsigned char hexkey[130];
	unsigned char output[130];
	unsigned char * p;

	memset(hexkey,0x00,sizeof(hexkey));
	memset(output,0x00,sizeof(output));
	// ---------------

	int c;

	while (1)
	{
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"verbose", no_argument,       &verbose, 1},
			{"brief",   no_argument,       &verbose, 0},
			{"debug",   no_argument,         &debug, 1},
			{"nodebug", no_argument,         &debug, 0},
			/* These options don’t set a flag.
			   We distinguish them by their indices. */
			{"help",     no_argument,       0, 'h'},
			{"version",  no_argument,       0, 'v'},
			{"size",    required_argument,  0, 's'},
			{"chop",    required_argument,  0, 'c'},
			{"data",    required_argument,  0, 'd'},
			{"size",    required_argument,  0, 's'},
			{0, 0, 0, 0}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "hvc:d:s:",
			long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0)
					break;
				printf ("option %s", long_options[option_index].name);
				if (optarg)
					printf (" with arg %s", optarg);
				printf ("\n");
				break;

			case 'h':
				//puts ("option '-h' or '--help'\n");
				usage(argv[0]);
				exit(0);
				break;

			case 'v':
				//puts ("option '-v' or '--version'\n");
				version();
				exit(0);
				break;

			case 'c':
				//printf ("option '-c' or '--chop' with value '%s'\n", optarg);
				p = optarg;
				chopchar = *p;
				break;

			case 's':
				//printf ("option '-s' or '--size' with value '%s'\n", optarg);
				chopsize = atoi(optarg);
				break;

			case 'd':
				//printf ("option '-d' or '--data' with value '%s'\n", optarg);
				strcpy(hexkey,optarg);
				gotin = 1;
				break;

			case '?':
				/* getopt_long already printed an error message. */
				break;

			default:
				abort ();
		}
	}

	/* Instead of reporting '--verbose'
	   and '--brief' as they are encountered,
	   we report the final status resulting from them. */
	if (verbose)
		puts ("verbose is set");

	/* Print any remaining command line arguments (not options). */
	if (optind < argc)
	{
		//printf ("non-option ARGV-elements: ");
		while (optind < argc)
			strcat(hexkey,argv[optind++]);
		//	printf ("%s ", argv[optind++]);
		//putchar ('\n');

		gotin = 1;
	}


    // ---------------
	if (gotin != 1)
		i = scanf("%80s",hexkey);

	if (debug)
		printf("hexkey: '%s'\n",hexkey);

	i = j = k = 0;
	p = hexkey;
	do
	{
		output[i++] = *p++;
		j++;
		k++;
		if ((j == chopsize) && ((strlen(hexkey) - k) > 0)) {
			output[i++] = chopchar;
			j = 0;
		}
	} while(k<strlen(hexkey));

	if (verbose)
		printf("key: '%s'\n",output);
	else
		printf("%s\n",output);
	return(0);
}
