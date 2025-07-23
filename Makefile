CC := gcc
CFLAGS := -Wall -Wextra -O2
SHARED_FLAGS := -shared -fPIC
LIBS := -ldl

SRC_FILES := $(wildcard src/*.c)
LIB_TARGETS := $(patsubst src/%.c,lib/libfate-%.so,$(SRC_FILES))
TEST_TARGETS := $(patsubst src/%.c,test/test_%,$(SRC_FILES))

.PHONY: all build check clean install help
.DEFAULT_GOAL := build

build: $(LIB_TARGETS)

lib/libfate-%.so: src/%.c
	@mkdir -p lib
	$(CC) $(CFLAGS) $(SHARED_FLAGS) $(if $(findstring random,$*),$(LIBS)) $< -o $@

test/test_%: test/%.c
	$(CC) $(CFLAGS) $< -o $@

check: $(LIB_TARGETS) $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do \
		lib=$$(echo $$test | sed 's|test/test_|lib/libfate-|; s|$$|.so|'); \
		echo "Testing $$test with $$lib"; \
		LD_PRELOAD=$$lib $$test; \
	done

install: $(LIB_TARGETS)
	mkdir -p $(PREFIX)/lib
	install -m 755 $(LIB_TARGETS) $(PREFIX)/lib/

clean:
	rm -rf lib/ $(TEST_TARGETS)
