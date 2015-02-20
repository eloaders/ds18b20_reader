#include "options.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_INTERVAL 5
#define SECONDS_A_DAY (24 * 60 * 60)

void init_options(opt_t *opt)
{
   opt->interval = DEFAULT_INTERVAL;
   opt->device = NULL;
   opt->action = ACTION_NONE; 
}

bool is_option(const char *s, const char *shortName, const char *longName)
{
   return (0 == strncmp(s, shortName, strlen(s))) ||
          (0 == strncmp(s, longName, strlen(s)));
}

int get_opt(int argc, char **argv, opt_t *opt)
{
   if (!opt) return OPTIONS_ERROR;

   init_options(opt);

   int pos = 1;
   while (pos < argc)
   {
      if (is_option(argv[pos], "-d", "--device"))
      {
         if (++pos < argc)
         {
            opt->action = ACTION_RUN;
            opt->device = argv[pos];
         }
         else
         {
            return OPTIONS_NO_DEVICE;
         }
      }

      if (is_option(argv[pos], "-i", "--interval"))
      {
         if (++pos < argc)
         {
            char *endptr = NULL;
            long interval = strtoul(argv[pos], &endptr, 10);

            if ((NULL == endptr) || ('\0' != *endptr))
            {
               return OPTIONS_INVALID_INTERVAL;
            }

            if (interval < 1)
            {
               return OPTIONS_INTERVAL_TOO_SMALL;
            }

            if (interval > SECONDS_A_DAY)
            {
               return OPTIONS_INTERVAL_TOO_BIG;
            }

            opt->interval = (unsigned) interval;
         }
      }

      if (is_option(argv[pos], "-h", "--help"))
      {
         opt->action = ACTION_HELP;
         return OPTIONS_OK;
      }

      if (is_option(argv[pos], "-v", "--version"))
      {
         opt->action = ACTION_VERSION;
         return OPTIONS_OK;
      }

      ++pos;
   }

   return OPTIONS_OK;
}

