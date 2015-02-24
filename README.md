# DS18B20_READER

DS18B20_Reader is a temperature logger using Linux's representation of a
DS18B20 temperature sensor in sysfs. It can be used on any Linux system with
such a sensor, but is primarily developed for Raspberry Pis.

## Requirements

The program has been tested with GNU Make 4.1, GCC 4.9.2 (and alternatively
Clang 3.5.1), but any recent version of the programs should do.

## How to compile?

Simply run the following command in the main directory of the project:

   `> make`

This will create the executable *ds18b20_reader*.

## How to use?

A simple help text is shown when the program is called with *-h*:

   `> ./ds18b20_reader -h`

You need to provide the ID of DS18B20 sensor to show its temperature. All
currently available sensor IDs can be found in Linux's sysfs directory
*/sys/bus/w1/devices*. Pass this information to the program with the *-d*
switch:

   `> ./ds18b20_reader -d 0000053da58f`

The program should immediately start to print the current temperature every
5 seconds. The output should look similar to this:

   2015-02-24T09:16:08.704495  18.750°C
   2015-02-24T09:16:13.534466  18.687°C
   2015-02-24T09:16:18.364459  18.750°C
   2015-02-24T09:16:23.194451  18.750°C

The time is always shown as UTC! The output can be stopped by pressing CTRL-C.

Use the *-i* switch to adjust the number of seconds between two measurements:

   `> ./ds18b20_reader -d 0000053ds58f -i 60`

The previous command prints one line every minute.

## How to store the output to a file?

To store output to a file, say *temp.log*, you start the program like this:

   `> ./ds18b20_reader -d 0000053ds58f -i 60 | tee -a temp.log`

# Questions, suggestions and bugs

Should you have questions about the program, suggestions for further
improvements or would like to report a bug, don't hesitate to send an email
to [me](mailto:jens@gutzeit.name).

# License

This program is released under a 3-clause BSD license. See the file
[LICENSE.md](LICENSE.md) for further details.

