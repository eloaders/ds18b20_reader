#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "options.h"
#include "ds18b20.h"

#define VERSION "0.2.0"

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
   if (!ds18b20_is_present(device))
   {
      fprintf(stderr, "ERROR: No sensor with ID '%s' found\n", device);
      exit(EXIT_FAILURE);
   }

   while(true)
   {
      int temperature = 0;
      int result = ds18b20_read(device, &temperature);
      double temp = temperature / 1000.0;

      struct timeval t;
      gettimeofday(&t, NULL);
      struct tm* tm_info = gmtime(&t.tv_sec);

      char buf[25];
      strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", tm_info);
      if (DS18B20_OK == result)
      {
         printf("%s.%06ld %7.3f°C\n", buf, t.tv_usec, temp);
         fflush(stdout);
      }

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

