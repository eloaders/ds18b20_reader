#ifndef DS18B20_READER_OPTIONS_H
#define DS18B20_READER_OPTIONS_H

#include <stdbool.h>

enum
{
   OPTIONS_OK,
   OPTIONS_NO_DEVICE,
   OPTIONS_INVALID_INTERVAL,
   OPTIONS_INTERVAL_TOO_SMALL,
   OPTIONS_INTERVAL_TOO_BIG,
   OPTIONS_ERROR
};

enum
{
   ACTION_NONE,
   ACTION_HELP,
   ACTION_VERSION,
   ACTION_RUN
};

typedef struct
{
   unsigned interval;
   const char *device;
   int action;
} opt_t;

int get_opt(int argc, char **argv, opt_t *opt);

#endif // DS18B20_READER_OPTIONS_H

