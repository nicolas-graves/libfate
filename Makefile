.PHONY: install test clean
.DEFAULT: libdet-random.so

libdet-random.so: deterministic-random.c
	gcc -shared -fPIC -ldl deterministic-random.c -o libdet-random.so

test-random: test-random.c
	gcc test-random.c -o test-random

test: libdet-random.so test-random
	@echo "Testing without LD_PRELOAD (should differ)..."
	@./test-random > run1.out
	@./test-random > run2.out
	@if diff -q run1.out run2.out > /dev/null; then \
		echo "ERROR: Expected different results without LD_PRELOAD"; \
		exit 1; \
	else \
		echo "✓ Results differ without LD_PRELOAD"; \
	fi
	@echo "Testing with LD_PRELOAD (should match)..."
	@LD_PRELOAD=./libdet-random.so ./test-random > run3.out
	@LD_PRELOAD=./libdet-random.so ./test-random > run4.out
	@if diff -q run3.out run4.out > /dev/null; then \
		echo "✓ Results identical with LD_PRELOAD"; \
	else \
		echo "ERROR: Expected identical results with LD_PRELOAD"; \
		exit 1; \
	fi

clean:
	rm -f libdet-random.so test-random run*.out

install: libdet-random.so
	mkdir -p $(PREFIX)/lib
	install libdet-random.so $(PREFIX)/lib

