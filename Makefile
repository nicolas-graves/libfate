BUILD_DIR := build

CC := gcc
CFLAGS := -Wall -Wextra -O2
SHARED_FLAGS := -shared -fPIC
LIBS := -ldl

SRC_FILES := $(wildcard src/*.c)
LIB_TARGETS := $(patsubst src/%.c,$(BUILD_DIR)/libfate-%.so,$(SRC_FILES))
TEST_TARGETS := $(patsubst src/%.c,$(BUILD_DIR)/test_%,$(SRC_FILES))

.PHONY: all build check clean install help
.DEFAULT_GOAL := build

build: $(LIB_TARGETS)

$(BUILD_DIR)/libfate-%.so: src/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SHARED_FLAGS) $(if $(findstring random,$*),$(LIBS)) $< -o $@

$(BUILD_DIR)/test_%: test/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

check: $(LIB_TARGETS) $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do \
		lib=$$(echo $$test | sed 's|$(BUILD_DIR)/test_|$(BUILD_DIR)/libfate-|; s|$$|.so|'); \
		echo "Testing $$test with $$lib"; \
		LD_PRELOAD=$$lib $$test; \
	done

install: $(LIB_TARGETS)
	mkdir -p $(PREFIX)/lib
	install -m 755 $(LIB_TARGETS) $(PREFIX)/lib/

clean:
	rm -rf $(BUILD_DIR)
