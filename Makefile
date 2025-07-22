.PHONY: build install check clean
.DEFAULT: build

build: libdet-random.so libdet-time.so libdet-sysinfo.so

libdet-random.so: src/random.c
	gcc -shared -fPIC -ldl src/random.c -o libdet-random.so

libdet-time.so: src/time.c
	gcc -shared -fPIC src/time.c -o libdet-time.so

libdet-sysinfo.so: src/sysinfo.c
	gcc -shared -fPIC src/sysinfo.c -o libdet-sysinfo.so

test/random: test/random.c
	gcc test/random.c -o test/random

test/clock_gettime: test/clock_gettime.c
	gcc test/clock_gettime.c -o test/clock_gettime

test/sysinfo: test/sysinfo.c
	gcc test/sysinfo.c -o test/sysinfo


check: libdet-random.so libdet-time.so libdet-sysinfo.so test/random test/clock_gettime test/sysinfo
	LD_PRELOAD=./libdet-random.so ./test/random
	LD_PRELOAD=./libdet-time.so ./test/clock_gettime
	LD_PRELOAD=./libdet-sysinfo.so ./test/sysinfo

clean:
	rm -f libdet-random.so libdet-time.so libdet-sysinfo.so test/random test/clock_gettime test/sysinfo run*.out combined*.out sysinfo*.out

install: libdet-random.so libdet-time.so libdet-sysinfo.so
	mkdir -p $(PREFIX)/lib
	install libdet-random.so $(PREFIX)/lib
	install libdet-time.so $(PREFIX)/lib
	install libdet-sysinfo.so $(PREFIX)/lib
