#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

   // Make sure device exists
   char deviceName[50];
   snprintf(deviceName, sizeof(deviceName),
            "/sys/bus/w1/devices/28-%s/w1_slave", device);

   err = stat(deviceName, &s);
   if ((-1 == err) || !S_ISREG(s.st_mode)) return false;

   return true;
}

int ds18b20_read(const char *device, int *temperature)
{
   if ((NULL == device) || (NULL == temperature)) return DS18B20_ERROR;
   if (!ds18b20_is_present(device)) return DS18B20_NOT_PRESENT;

   size_t len = strlen(device);
   if ((0 == len) || (len > 12)) return DS18B20_INVALID_ID;

   char fullname[50];
   snprintf(fullname, sizeof(fullname), "/sys/bus/w1/devices/28-%s/w1_slave",
            device);

   char data[128];
   FILE *f = fopen(fullname, "rb");
   if (NULL == f)
   {
      return DS18B20_READ_ERROR;
   }
   size_t dataSize = fread(data, 1, sizeof(data), f);
   data[dataSize] = '\0';
   fclose(f);

   char *s = strstr(data, "t=");
   if (NULL == s) return DS18B20_ERROR;

   s += 2;
   *temperature = atoi(s);

   return DS18B20_OK;
}

