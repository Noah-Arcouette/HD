# HD - Header Definitions

HD is a simple MakeFile generator that reads you source
file for `#include`s and generates a MakeFile.

HD tells you exactly what it's doing and what happened if
an error occurs.

HD generates simple MakeFiles and sadly cant build libraries
or installation / uninstallation scripts, *yet*.


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

# Install

`$ ./install <Extra CFLAGS>`


# Uninstall

`$ ./uninstall`


# How to use

Just give HD some settings and it will read your sources and 
automatically generate a MakeFile from them.

If you create a new file or include and new local header you
must rebuild your MakeFile. But instead of rerunning the command
the HD MakeFile remembers your settings and rebuilds with 
`$ make gen`

If you change your settings sadly you must rerun the command with
the new settings.

To build a development build just run `$ make`.
This command will recompile the program using, well Make.

To build a release build just run `$ make build`.
This command will build the program and remove unneeded symbols.

To clean the project just run `$ make clean`.

And that's it! It's handy to make a shell script to run
configurations before and after the building, and to run the 
program.
