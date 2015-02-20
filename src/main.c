#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "options.h"

#define VERSION "0.1.0"

void help()
{
   printf("Usage: ds18b20_reader [options]\n"
          "Repeatedly read the temperature from a DS18B20 sensor\n"
          "\n"
          "Options:\n"
          " -d, --device NAME\tSet the DS18B20 serial number\n"
          " -i, --interval SECONDS\tRead every SECONDS seconds (default: 5)\n"
          " -h, --help\t\tGive this help\n"
          " -v, --version\t\tDisplay version information\n"
          "\n");
}

void version()
{
   printf("Version %s\n", VERSION);
}

void error(int error)
{
   switch(error)
   {
   case OPTIONS_OK:
      break;
   case OPTIONS_NO_DEVICE:
      fprintf(stderr, "ERROR: No serial number specified\n"
                      "\n"
                      "You have to specify the serial number of your sensor,\n"
                      "e.g. like this:\n"
                      "\n"
                      "  ds18b20_reader --device 00053D87\n"
                      "\n");
      break;
   case OPTIONS_INVALID_INTERVAL:
      fprintf(stderr, "ERROR: Interval is not a number\n");
      break;
   case OPTIONS_INTERVAL_TOO_SMALL:
      fprintf(stderr, "ERROR: Interval has to be at least one second\n");
      break;
   case OPTIONS_INTERVAL_TOO_BIG:
      fprintf(stderr, "ERROR: One day or larger as interval is not supported\n");
      break;
   default:
      fprintf(stderr, "ERROR: Unknown error\n");
   }
}

void run(const char *device, unsigned interval)
{
   if (device != device) return;

   while(true)
   {
      printf("read data\n");
      sleep(interval);
   }
}

int main(int argc, char **argv)
{
   opt_t options;
   
   int result = get_opt(argc, argv, &options);

   if (OPTIONS_OK != result)
   {
      error(result);
      return EXIT_FAILURE;
   }

   switch (options.action)
   {
   case ACTION_NONE:
      break;
   case ACTION_HELP:
      help();
      break;
   case ACTION_VERSION:
      version();
      break;
   case ACTION_RUN:
      run(options.device, options.interval);
      break;
   default:
      fprintf(stderr, "ERROR: Internal error\n");
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

