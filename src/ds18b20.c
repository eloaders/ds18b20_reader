#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ds18b20.h"

bool ds18b20_is_present(const char *device)
{
   // Make sure /sys/bus/w1/devices exists and is a directory
   struct stat s;
   int err = stat("/sys/bus/w1/devices", &s);
   if ((-1 == err) || !S_ISDIR(s.st_mode)) return false;

   return device == device;
}

int ds18b20_read(const char *device, int *temperature)
{
   if ((NULL == device) || (NULL == temperature)) return DS18B20_ERROR;
   if (!ds18b20_is_present(device)) return DS18B20_NOT_PRESENT;
   
   *temperature = 17300;

   return DS18B20_OK;
}

