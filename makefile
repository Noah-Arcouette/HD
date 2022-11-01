# Flags
INC      = -I./inc/ -I./snp/ 
LIB      = 
LIBS     = -lmsap -lmacsv 
DEFFLAGS = -g -Wall -Wextra -O2 -std=gnu18 -D_GNU_SOURCE  ${INC}

# directories
OBJ     = ./obj/
BIN     = ./bin/

#binary info
NAME    = hd
VERSION = 1.5
# presets
OUT = ${BIN}/${NAME}
# test out ${NAME}-${VER}_test
CC  = cc


# build test
all: message ${OUT}
	printf "\x1b[1;32m━━━SUCCESS━━━┛ Test Build\x1b[0m\n"

# build release
build: message clean_part ${OUT}
	strip -s ${OUT}
	printf "\x1b[1;32m━━━SUCCESS━━━┛ \x1b[39mRelease Build\x1b[0m\n"

# clean section
clean_part:
	rm ${BIN}/* ${OBJ}/* -f
	printf "\x1b[1;35m━━━CLEANED━━━┫\x1b[0m\n"

# clean
clean: message clean_part
	printf "\x1b[1;32m━━━SUCCESS━━━┛\x1b[0m\n"


# generate new makefile
gen: message clean_part
	printf "\x1b[1;39m━━━━━━━━━━━━━┛\x1b[0m\n\n"

	hd -n hd -v 1.5 -m makefile -b ./bin/ -o ./obj/ -s ./src/ -i ./inc/ -i ./snp/ -l msap -l macsv -f -g -f -Wall -f -Wextra -f -O2 -f -std=gnu18 -f -D_GNU_SOURCE
	printf "\x1b[1;32m\n━━━━━━━━━━━━━┓\nSUCCESS      ┃  \x1b[39mCreate new\x1b[35m MakeFile \x1b[32m\n━━━━━━━━━━━━━┛\x1b[0m\n"

# print settings
message:
	printf "\x1b[1;35m%s \x1b[39mV%s\n" ${NAME} ${VERSION}
	printf "\x1b[1;39mMakefile generated from \x1b[35mHD\x1b[39m\n"
	printf "\x1b[39m ━ \x1b[1;39mUnder the \x1b[32mMimik License 1.0\n"
	printf "\x1b[39m ━ \x1b[1;32mCopyright (c) 2022 Noah Arcouette\x1b[0m  ┃\n"
	printf "\x1b[39m━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┛\n"

ifndef VERBOSE
.SILENT:
endif

${OBJ}/gifnoCesu.o: ./src//useConfig.c ./inc//structures.h ./inc//functions.h 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//useConfig.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/gifnoCesu.o ./src//useConfig.c

${OBJ}/eliFedulcni.o: ./src//includeFile.c ./inc//structures.h ./inc//functions.h 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//includeFile.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/eliFedulcni.o ./src//includeFile.c

${OBJ}/ydoBneg.o: ./src//genBody.c ./inc//structures.h ./inc//functions.h 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//genBody.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/ydoBneg.o ./src//genBody.c

${OBJ}/seliFnepo.o: ./src//openFiles.c ./inc//structures.h ./inc//functions.h 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//openFiles.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/seliFnepo.o ./src//openFiles.c

${OBJ}/skcehCnur.o: ./src//runChecks.c ./inc//structures.h ./inc//functions.h 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//runChecks.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/skcehCnur.o ./src//runChecks.c

${OBJ}/niam.o: ./src//main.c ./inc//info.h ./inc//structures.h ./inc//functions.h 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//main.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/niam.o ./src//main.c

${OBJ}/sgnitteSteg.o: ./src//getSettings.c ./inc//structures.h ./inc//functions.h ./snp//movef.c 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//getSettings.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/sgnitteSteg.o ./src//getSettings.c

${OBJ}/daeHneg.o: ./src//genHead.c ./inc//structures.h ./inc//functions.h 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//genHead.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/daeHneg.o ./src//genHead.c

${OBJ}/seliFteg.o: ./src//getFiles.c ./inc//functions.h 
	printf "\x1b[1;39m━━━━━━━━━━━━━┫\n\x1b[35mFILE         \x1b[39m┃  \x1b[39m %s\x1b[39m\n━━━━━━━━━━━━━┫\x1b[0m\n" ./src//getFiles.c
	${CC} -c ${DEFFLAGS} ${CFLAGS} -o ${OBJ}/seliFteg.o ./src//getFiles.c

${OUT}: ${OBJ}/gifnoCesu.o ${OBJ}/eliFedulcni.o ${OBJ}/ydoBneg.o ${OBJ}/seliFnepo.o ${OBJ}/skcehCnur.o ${OBJ}/niam.o ${OBJ}/sgnitteSteg.o ${OBJ}/daeHneg.o ${OBJ}/seliFteg.o
	${CC} ${CFLAGS} ${DEFFLAGS} ${LIB} -o ${OUT} ${OBJ}/gifnoCesu.o ${OBJ}/eliFedulcni.o ${OBJ}/ydoBneg.o ${OBJ}/seliFnepo.o ${OBJ}/skcehCnur.o ${OBJ}/niam.o ${OBJ}/sgnitteSteg.o ${OBJ}/daeHneg.o ${OBJ}/seliFteg.o ${LIBS}
