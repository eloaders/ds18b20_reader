#include <stdlib.h>
#include "ds18b20.h"

bool ds18b20_is_present(const char *device)
{
   return device != NULL;
}

int ds18b20_read(const char *device, int *temperature)
{
   if ((NULL == device) || (NULL == temperature)) return DS18B20_ERROR;

   *temperature = 17300;

   return DS18B20_OK;
}

