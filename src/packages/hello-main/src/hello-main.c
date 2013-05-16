
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "version.h"
#include "config.h"

/* The official name of this program (e.g., no 'g' prefix).  */
#define PROGRAM_NAME "hello"
#define program_name PROGRAM_NAME

#define AUTHORS \
  proper_name ("Wes Edens")

static struct globalArgs_t {
    int         verbosity;      /* -v option */
    int         num_loops;
    int         do_all;
} globalArgs = {0};

static struct option const longopts[] =
{
  {"multiple", no_argument      , NULL, 'a'},
  {"verbose" , no_argument      , NULL, 'v'},
  {NULL, 0, NULL, 0}
};


void
usage (int status)
{
  if (status != 0)
    //emit_try_help ();
    fputs("error_try_help\n", stdout);
  else{
      printf ("\
Usage: %s NAME [SUFFIX]\n\
  or:  %s OPTION... NAME...\n\
",
              program_name, program_name);
      fputs ("\
Print NAME with any leading directory components removed.\n\
If specified, also remove a trailing SUFFIX.\n\
", stdout);

      fputs ("\
  -a, --multiple       support multiple arguments and treat each as a NAME\n\
  -v, --verbose        print detailed information\n\
", stdout);
      printf ("\
\n\
Examples:\n\
  %s /usr/bin/sort          -> \"sort\"\n\
",
              program_name);
    }
  exit (status);
}

int
main (int argc, char **argv)
{
    int c           = 1;
    int option_idx  = 0;

    while ( (c = getopt_long(argc, argv, "+av", longopts, &option_idx )) != -1 ){
        switch ( c ){
        case 0:
           /* If this option set a flag, do nothing else now. */
           if (longopts[option_idx].flag != 0)
              break;
           printf("option %s", longopts[option_idx].name);
           if (optarg)
              printf(" with arg %s", optarg);
           printf("\n");
           break;
        case 'a':
            break;
        case 'v':
            globalArgs.verbosity++;
            break;

        default:
        usage (-1);
    }
}

    /* Print any remaining command line arguments (not options). */
    if ( argc < optind ){
        usage(-1);
    }

    if ( globalArgs.verbosity ){
        printf("verbose option selected: %d\n", globalArgs.verbosity);
    }

    printf("hello world\n");
    printf("%s\n", PACKAGE_STRING);

    exit(0);
}
