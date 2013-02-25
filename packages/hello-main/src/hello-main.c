
#include <getopt.h>
#include <stdio.h>
#include <sys/types.h>

#include "system.h"
#include "error.h"
#include "quote.h"

/* The official name of this program (e.g., no 'g' prefix).  */
#define PROGRAM_NAME "hello"

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
  {GETOPT_HELP_OPTION_DECL},
  {GETOPT_VERSION_OPTION_DECL},
  {NULL, 0, NULL, 0}
};

void
usage (int status)
{
  if (status != EXIT_SUCCESS)
    emit_try_help ();
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

      emit_mandatory_arg_note ();

      fputs ("\
  -a, --multiple       support multiple arguments and treat each as a NAME\n\
  -v, --verbose        print detailed information\n\
", stdout);
      fputs (HELP_OPTION_DESCRIPTION, stdout);
      fputs (VERSION_OPTION_DESCRIPTION, stdout);
      printf ("\
\n\
Examples:\n\
  %s /usr/bin/sort          -> \"sort\"\n\
",
              program_name);
      emit_ancillary_info ();
    }
  exit (status);
}

int
main (int argc, char **argv)
{
    int c           = 1;
    int option_idx  = 0;

    initialize_main(&argc, &argv);
    set_program_name(argv[0]);

    atexit(close_stdout);

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

        case_GETOPT_HELP_CHAR;
        case_GETOPT_VERSION_CHAR (PROGRAM_NAME, AUTHORS);

        default:
        usage (EXIT_FAILURE);
    }
}

    /* Print any remaining command line arguments (not options). */
    if ( argc < optind ){
        error(0, 0, "missing operand");
        usage(EXIT_FAILURE);
    }

    if ( globalArgs.verbosity ){
        printf("verbose option selected: %d\n", globalArgs.verbosity);
    }

    printf("hello world\n");

    exit(EXIT_SUCCESS);
}
