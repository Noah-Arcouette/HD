CFLAGS  =
CC      = cc -g -Wall -Wextra -O2 -std=gnu18 -I./inc ${CFLAGS}
OUT     = ./bin/hd
VER     = 1.0
LIBS    = -lmacsv -lmsap -lmcolor

all: ${OUT}
	${OUT} -c ./conf.acsv

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

${OUT}: ./inc/info.h ./obj/main.o ./obj/getFiles.o ./obj/getSettings.o
	${CC} -o ${OUT} ./obj/*.o ${LIBS}

./obj/main.o: ./src/main.c
	${CC} -o ./obj/main.o -c ./src/main.c

./obj/getFiles.o: ./src/getFiles.c
	${CC} -o ./obj/getFiles.o -c ./src/getFiles.c

./obj/getSettings.o: ./src/getSettings.c
	${CC} -o ./obj/getSettings.o -c ./src/getSettings.c

./inc/info.h: ./mkinfo
	./mkinfo ${VER}
