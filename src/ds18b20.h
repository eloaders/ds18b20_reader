#ifndef DS18B20_READER_H
#define DS18B20_READER_H

#include <stdbool.h>

enum
{
   DS18B20_OK,
   DS18B20_NOT_PRESENT,
   DS18B20_READ_ERROR,
   DS18B20_ERROR
};

bool ds18b20_is_present(const char *device);
int ds18b20_read(const char *device, int *temperature);

#endif // DS18B20_READER_H

