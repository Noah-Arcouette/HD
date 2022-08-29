# HD - Header Definitions

HD is a simple MakeFile generator that reads your source
file for `#include`s and generates a MakeFile.

HD tells you exactly what it's doing and what happened if
an error occurs.

# Requires

 - [(GNU) LibC](https://www.gnu.org/software/libc/)
 - [(MAKE) (GNU) CC](https://gcc.gnu.org/)
 - [(MAKE) LibMSAP](https://github.com/Noah-Arcouette/LibMSAP)
 - [(MAKE) LibMACSV](https://github.com/Noah-Arcouette/LibMACSV)
 - [(MAKE) (GNU) Make](https://www.gnu.org/software/make/)


# Help

includes and sources need to be in their own directories

--include, -i  : add include dir

--source, -s   : add source dir

--binary, -b   : set output dir

--object, -o   : set output for objects

--library, -l  : add lib

--path, -p     : add to lib path

--flag, -f     : add flag

--name, -n     : set name to project

--version, -v  : set release version

--makefile, -m : set make file name

--help, -h     : print help then exit

--config, -c   : use config file ***See ./config.acsv for example***

--test, -T     : add test file ***Will not be compiled into 
a library, if set.***

--dynamic, -D  : set HD to build a dynamic library

--static, -S   : set HD to build a static library

# Install

`$ ./install <Extra CFLAGS>`


# Uninstall

`$ ./uninstall`


# How to use

Just give HD some settings and it will read your sources and 
automatically generates a MakeFile from them.

If you create a new file or include a new local header you
must rebuild your MakeFile. But instead of rerunning the command
the HD MakeFile remembers your settings and rebuilds with 
`$ make gen`

If you change your settings sadly you must rerun the command with
the new settings.

To build a development build just run `$ make`.
This command will recompile the program using, well Make.

To build a release build just run `$ make build`.
This command will clean then build the program and 
remove unneeded symbols.

To clean the project just run `$ make clean`.

And that's it! It's handy to make a shell script to run
configurations before and after the building, and to run the 
program.
