# HD - Header Definitions

MakeFiles generated from `#include`s

# Help

includes and sources need to be in their own dirs

--config, -c   : set config file
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


# MakeFile

```Makefile
# flags
INC     = -I...
LIB     = -L...
LIBS    = -l...
CFLAGS += ...

# directories
OBJ     = ...
BIN     = ...

# binary info
NAME    = ...
VER     = ...

# presets
OUT = ${NAME}
# test out ${NAME}-${VER}_test
CC  = cc ${CFLAGS}


# build test
all: ${OUT}
	<<output message>>

# build release
build: clean ${OUT}
	strip -s ${OUT}
	<<output message>>

# clean
clean:
	rm ${BIN}/* ${OBJ}/* -f
	<<output message>>

# generate new makefile
gen: clean
	hd <options>
	<<output message>>


# body / files
${OUT}: <objects>
	${CC} -o ${OUT} ./<object path>/*.o ${LIBS}
	<<output message>>

<object>: <source / includes>
	${CC} -o <object> -c <source>
	<<output message>>
```
