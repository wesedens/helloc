/* Print --version and bug-reporting information in a consistent format.
   Copyright (C) 1999-2012 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* Written by Jim Meyering. */

#include <config.h>

/* Specification.  */
#include "version-etc.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* If you use AM_INIT_AUTOMAKE's no-define option,
   PACKAGE is not defined.  Use PACKAGE_TARNAME instead.  */
#if ! defined PACKAGE && defined PACKAGE_TARNAME
# define PACKAGE PACKAGE_TARNAME
#endif

enum { COPYRIGHT_YEAR = 2012 };

/* The three functions below display the --version information the
   standard way.

   If COMMAND_NAME is NULL, the PACKAGE is assumed to be the name of
   the program.  The formats are therefore:

   PACKAGE VERSION

   or

   COMMAND_NAME (PACKAGE) VERSION.

   The functions differ in the way they are passed author names. */

/* Display the --version information the standard way.

   Author names are given in the array AUTHORS. N_AUTHORS is the
   number of elements in the array. */
void
version_etc_arn (FILE *stream,
                 const char *command_name, const char *package,
                 const char *version,
                 const char * const * authors, size_t n_authors)
{
  if (command_name)
    fprintf (stream, "%s (%s) %s\n", command_name, package, version);
  else
    fprintf (stream, "%s %s\n", package, version);

#ifdef PACKAGE_PACKAGER
# ifdef PACKAGE_PACKAGER_VERSION
  fprintf (stream, "Packaged by %s (%s)\n", PACKAGE_PACKAGER,
           PACKAGE_PACKAGER_VERSION);
# else
  fprintf (stream, "Packaged by %s\n", PACKAGE_PACKAGER);
# endif
#endif

  fputs ("\
\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
\n\
",
         stream);

  switch (n_authors)
    {
    case 0:
      /* The caller must provide at least one author name.  */
      abort ();
    case 1:
      fprintf (stream, "Written by %s.\n", authors[0]);
      break;
    case 2:
      fprintf (stream, "Written by %s and %s.\n", authors[0], authors[1]);
      break;
    case 3:
      fprintf (stream, "Written by %s, %s, and %s.\n",
               authors[0], authors[1], authors[2]);
      break;
    case 4:
      fprintf (stream, "Written by %s, %s, %s,\nand %s.\n",
               authors[0], authors[1], authors[2], authors[3]);
      break;
    case 5:
      fprintf (stream, "Written by %s, %s, %s,\n%s, and %s.\n",
               authors[0], authors[1], authors[2], authors[3], authors[4]);
      break;
    case 6:
      fprintf (stream, "Written by %s, %s, %s,\n%s, %s, and %s.\n",
               authors[0], authors[1], authors[2], authors[3], authors[4],
               authors[5]);
      break;
    case 7:
      fprintf (stream, "Written by %s, %s, %s,\n%s, %s, %s, and %s.\n",
               authors[0], authors[1], authors[2], authors[3], authors[4],
               authors[5], authors[6]);
      break;
    case 8:
      fprintf (stream, "\
Written by %s, %s, %s,\n%s, %s, %s, %s,\nand %s.\n",
                authors[0], authors[1], authors[2], authors[3], authors[4],
                authors[5], authors[6], authors[7]);
      break;
    case 9:
      fprintf (stream, "\
Written by %s, %s, %s,\n%s, %s, %s, %s,\n%s, and %s.\n",
               authors[0], authors[1], authors[2], authors[3], authors[4],
               authors[5], authors[6], authors[7], authors[8]);
      break;
    default:
      fprintf (stream, "\
Written by %s, %s, %s,\n%s, %s, %s, %s,\n%s, %s, and others.\n",
                authors[0], authors[1], authors[2], authors[3], authors[4],
                authors[5], authors[6], authors[7], authors[8]);
      break;
    }
}

/* Display the --version information the standard way.  See the initial
   comment to this module, for more information.

   Author names are given in the NULL-terminated array AUTHORS. */
void
version_etc_ar (FILE *stream,
                const char *command_name, const char *package,
                const char *version, const char * const * authors)
{
  size_t n_authors;

  for (n_authors = 0; authors[n_authors]; n_authors++)
    ;
  version_etc_arn (stream, command_name, package, version, authors, n_authors);
}

/* Display the --version information the standard way.  See the initial
   comment to this module, for more information.

   Author names are given in the NULL-terminated va_list AUTHORS. */
void
version_etc_va (FILE *stream,
                const char *command_name, const char *package,
                const char *version, va_list authors)
{
  size_t n_authors;
  const char *authtab[10];

  for (n_authors = 0;
       n_authors < 10
         && (authtab[n_authors] = va_arg (authors, const char *)) != NULL;
       n_authors++)
    ;
  version_etc_arn (stream, command_name, package, version,
                   authtab, n_authors);
}


/* Display the --version information the standard way.

   If COMMAND_NAME is NULL, the PACKAGE is assumed to be the name of
   the program.  The formats are therefore:

   PACKAGE VERSION

   or

   COMMAND_NAME (PACKAGE) VERSION.

   The authors names are passed as separate arguments, with an additional
   NULL argument at the end.  */
void
version_etc (FILE *stream,
             const char *command_name, const char *package,
             const char *version, /* const char *author1, ...*/ ...)
{
  va_list authors;

  va_start (authors, version);
  version_etc_va (stream, command_name, package, version, authors);
  va_end (authors);
}

void
emit_bug_reporting_address (void)
{
  printf ("\nReport bugs to: %s\n", PACKAGE_BUGREPORT);
#ifdef PACKAGE_PACKAGER_BUG_REPORTS
  printf ("Report %s bugs to: %s\n", PACKAGE_PACKAGER,
          PACKAGE_PACKAGER_BUG_REPORTS);
#endif
#ifdef PACKAGE_URL
  printf ("%s home page: <%s>\n", PACKAGE_NAME, PACKAGE_URL);
#else
  printf ("%s home page: <http://www.gnu.org/software/%s/>\n",
          PACKAGE_NAME, PACKAGE);
#endif
  fputs ("General help using GNU software: <http://www.gnu.org/gethelp/>\n",
         stdout);
}
