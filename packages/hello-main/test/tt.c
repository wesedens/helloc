/**
 *  @file
 *  @author Wes Edens
 *  @date 11/05/2012
 *
 *  @brief test and time the triage functions
 *
 *  this file takes runs a triage test. the input is the name of a MATLAB .mat
 *  file containing variables called 'fpga2' and 'fpga3' these variables are
 *  structures defined in ../util/matlab_struct.h' they follow the PTSS
 *  prototyping environment there are options for the tests:
 *
 *<pre>
 *     -a, --all              run all the triage tests
 *     -b, --combine          run the combineLists test
 *     -c, --cluster          run the cluster test
 *     -d, --dualband         run the dualband-reject test
 *     -n, --num-loops        number of loops to run the timed tests
 *     -o, --output=file      optional output file name\n\
 *</pre>
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "compat-util.h"
#include "triage.h"

#include "debug.h"

#define HITLIST_SIZE  (1<<18)
#define NUM_LOOPS     (10)

static const char tt_usage[] =
"tt [--all] [--verbose] [--force] [--verbose] <remote> [<head>...]\n";

#define PROGRAM_NAME "opc-tt"

struct globalArgs_t {
    char       *in_file;        /* -o option */
    const char *out_file;       /* -o option */
    int         verbosity;      /* -v option */
    int         num_loops;
    int         do_clustertest;
    int         do_all;
} globalArgs = {0};

static struct option const longopts[] =
{
  {"verbose"       , no_argument      , &globalArgs.verbosity, 1    },
  {"all"           , no_argument      , NULL                 , 'a'  },
  {"cluster"       , no_argument      , NULL                 , 'c'  },
  {"output"        , required_argument, NULL                 , 'o'  },
  {"num-loops"     , required_argument, NULL                 , 'n'  },
  {NULL            , 0                , NULL                 , 0    }
};

int main( int argc, char *argv[] )
{
   char  cwd[1024];
   char  actualpath[PATH_MAX+1];
   char *realpath_ptr;
   int   option_idx           = 0;
   int   c;
   int   do_work              = 0;

   // set default number of loops to time
   globalArgs.num_loops = NUM_LOOPS;

   while ((c = getopt_long(argc, argv, "aco:n:", longopts, &option_idx)) != -1){
      switch (c)
      {
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
         globalArgs.do_clustertest  = 1;
         do_work                    = 1;
         break;

      default:
    	  usage(tt_usage);
         break;
      }
   }
   printf("%d\n", sane_istest('a', UT_ALPHA));

   /* Print any remaining command line arguments (not options). */
   if (optind < argc){
      globalArgs.in_file = argv[optind++];
   }else{
	   usage(tt_usage);
   }

   // Print the canonical path of the file, if it exists
   // helpful for debugging
   realpath_ptr = realpath(globalArgs.in_file, actualpath);
   if ( 0 != realpath_ptr ){
      printf("input file: %s\n", realpath_ptr);
   }else{
      perror("realpath");
   }

   // Print current working directory
   // helpful for debugging
   if ( getcwd(cwd, sizeof(cwd)) != NULL ){
       fprintf(stdout, "Current working dir: %s\n", cwd);
   }else{
       perror("getcwd() error");
   }

   if ( do_work ){
      printf("--- Test Completed ---\n");
   }

   return EXIT_SUCCESS;
}
