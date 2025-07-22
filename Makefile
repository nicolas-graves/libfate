.PHONY: build install check clean
.DEFAULT: build

build: libdet-random.so libdet-time.so libdet-sysinfo.so

libdet-random.so: deterministic-random.c
	gcc -shared -fPIC -ldl deterministic-random.c -o libdet-random.so

libdet-time.so: deterministic-time.c
	gcc -shared -fPIC deterministic-time.c -o libdet-time.so

libdet-sysinfo.so: deterministic-sysinfo.c
	gcc -shared -fPIC deterministic-sysinfo.c -o libdet-sysinfo.so

test/random: test/random.c
	gcc test/random.c -o test/random

test/time: test/time.c
	gcc test/time.c -o test/time

test/sysinfo: test/sysinfo.c
	gcc test/sysinfo.c -o test/sysinfo

check: libdet-random.so libdet-time.so libdet-sysinfo.so test/random test/time test/sysinfo
	@echo "Testing combined libraries..."
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so:./libdet-sysinfo.so ./test/random > combined1.out
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so:./libdet-sysinfo.so ./test/time >> combined1.out
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so:./libdet-sysinfo.so ./test/sysinfo >> combined1.out
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so:./libdet-sysinfo.so ./test/random > combined2.out
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so:./libdet-sysinfo.so ./test/time >> combined2.out
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so:./libdet-sysinfo.so ./test/sysinfo >> combined2.out
	@if diff -q combined1.out combined2.out > /dev/null; then \
		echo "✓ Combined libraries produce identical results"; \
	else \
		echo "ERROR: Combined libraries should produce identical results"; \
		exit 1; \
	fi
	@rm -f combined*.out
	@echo "Testing sysinfo separately..."
	@LD_PRELOAD=./libdet-sysinfo.so ./test/sysinfo > sysinfo1.out
	@LD_PRELOAD=./libdet-sysinfo.so ./test/sysinfo > sysinfo2.out
	@if diff -q sysinfo1.out sysinfo2.out > /dev/null; then \
		echo "✓ Sysinfo library produces identical results"; \
	else \
		echo "ERROR: Sysinfo library should produce identical results"; \
		exit 1; \
	fi
	@rm -f sysinfo*.out

clean:
	rm -f libdet-random.so libdet-time.so libdet-sysinfo.so test/random test/time test/sysinfo run*.out combined*.out sysinfo*.out

install: libdet-random.so libdet-time.so libdet-sysinfo.so
	mkdir -p $(PREFIX)/lib
	install libdet-random.so $(PREFIX)/lib
	install libdet-time.so $(PREFIX)/lib
	install libdet-sysinfo.so $(PREFIX)/lib
