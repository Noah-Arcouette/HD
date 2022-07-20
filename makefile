CFLAGS  =
CC      = cc -g -Wall -Wextra -O2 -std=gnu18 -I./inc ${CFLAGS}
OUT     = ./bin/hd
VER     = 1.0
LIBS    = -lmacsv -lmsap

all: ${OUT}
	${OUT} \
	-v 1.2 \
	-n hd \
	-o ./obj \
	-b ./bin \
	-f -g -f -Wall -f -Wextra -f -O2 -f -std=gnu18 \
	-l msap -l macsv \
	-s ./src \
	-i ./inc 

build: clean ${OUT}
	strip -s ${OUT}

clean:
	rm *.gz -f
	rm ./bin/* ./obj/* *.stack-dump -f

configure:
	mkdir -p ./bin/ ./obj/

# install: clean configure ${LIB}
# 	cp ${LIB} /lib/lib${OUT}.a
# 	cp ./inc/macsv.h /usr/include/macsv.h

# 	mkdir -p /etc/mimik/docs/LibMACSV
# 	cp ./doc/* /etc/mimik/docs/LibMACSV/

# uninstall:
# 	rm /lib/lib${OUT}.a -f
# 	rm /usr/include/macsv.h -f

# 	rm /etc/mimik/docs/LibMACSV/ -rf

${OUT}: ./obj/genHead.o ./obj/openFiles.o ./inc/info.h ./obj/main.o ./obj/getFiles.o ./obj/getSettings.o ./obj/runChecks.o
	${CC} -o ${OUT} ./obj/*.o ${LIBS}

./obj/main.o: ./src/main.c
	${CC} -o ./obj/main.o -c ./src/main.c

./obj/getFiles.o: ./src/getFiles.c
	${CC} -o ./obj/getFiles.o -c ./src/getFiles.c

./obj/getSettings.o: ./src/getSettings.c ./inc/movef.c
	${CC} -o ./obj/getSettings.o -c ./src/getSettings.c

./obj/runChecks.o: ./src/runChecks.c
	${CC} -o ./obj/runChecks.o -c ./src/runChecks.c

./obj/openFiles.o: ./src/openFiles.c
	${CC} -o ./obj/openFiles.o -c ./src/openFiles.c

./obj/genHead.o: ./src/genHead.c
	${CC} -o ./obj/genHead.o -c ./src/genHead.c

./inc/info.h: ./mkinfo
	./mkinfo ${VER}
