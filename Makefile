.PHONY: build install test clean
.DEFAULT: build

build: libdet-random.so libdet-time.so

libdet-random.so: deterministic-random.c
	gcc -shared -fPIC -ldl deterministic-random.c -o libdet-random.so

libdet-time.so: deterministic-time.c
	gcc -shared -fPIC deterministic-time.c -o libdet-time.so

test-random: test-random.c
	gcc test-random.c -o test-random

test-time: test-time.c
	gcc test-time.c -o test-time

test: libdet-random.so libdet-time.so test-random test-time
	@echo "Testing combined libraries..."
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so ./test-random > combined1.out
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so ./test-time >> combined1.out
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so ./test-random > combined2.out
	@LD_PRELOAD=./libdet-random.so:./libdet-time.so ./test-time >> combined2.out
	@if diff -q combined1.out combined2.out > /dev/null; then \
		echo "✓ Combined libraries produce identical results"; \
	else \
		echo "ERROR: Combined libraries should produce identical results"; \
		exit 1; \
	fi
	@rm -f combined*.out

clean:
	rm -f libdet-random.so test-random run*.out

install: libdet-random.so
	mkdir -p $(PREFIX)/lib
	install libdet-random.so $(PREFIX)/lib

