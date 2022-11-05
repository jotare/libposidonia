# Makefile
# Author: jotare

headers := $(wildcard include/*/*.h)   # include/*/z.h
sources := $(wildcard src/*/*.c)       # src/*/z.c
tests   := $(wildcard test/*/test_*.c) # test/*/test_z.c

source_objects := $(subst .c,.o,$(sources)) # src/*/z.o
test_objects   := $(subst .c,.o,$(tests))   # test/*/test_z.o

test_targets := $(basename $(tests)) # test/*/test_z

includes  := include/ $(dir $(wildcard include/)) $(dir $(wildcard test/)) lib/libds/include/
library_paths := cunit lib/libds/
libraries := cunit ds

CC := gcc
CFLAGS := -Wall -g -std=c99
CPPFLAGS += $(addprefix -I,$(includes))

LDFLAGS += $(addprefix -L,$(library_paths))
LDLIBS += $(addprefix -l,$(libraries))


.PHONY: all
all: lib tests
	@echo ALL

# sources
lib: libposidonia.a
libposidonia.a: libds libposidonia.a($(source_objects))


# lib dependencies
libds:
	make -C lib/libds/ lib

# tests
run-tests: tests
	./test/test_libposidonia

tests: test/test_libposidonia
test/test_libposidonia: test/test_libposidonia.o $(test_objects) $(source_objects)


# formatting
format:
	indent -bad -bap -sc -br -ce -brs -psl -blf -nut -i4 -npcs $(headers) $(sources) $(tests)


# cleaning
.PHONY: clean veryclean
clean:
	$(RM) depend
	find . -type f -name "*~" -exec rm {} +

veryclean: clean
	$(RM) $(source_objects) $(test_objects) $(test_targets) test/test_libposidonia.o test/test_libposidonia libposidonia.a
	make -C lib/libds/ veryclean


# debug info
.PHONY: debug
debug:
	@echo HEADERS
	@echo $(headers)
	@echo
	@echo SOURCES
	@echo $(sources)
	@echo
	@echo TESTS
	@echo $(tests)
	@echo
	@echo SOURCE_OBJECTS
	@echo $(source_objects)
	@echo
	@echo TEST_OBJECTS
	@echo $(test_objects)
	@echo
	@echo TEST_TARGETS
	@echo $(test_targets)
	@echo
	@echo INCLUDES
	@echo $(includes)
	@echo
	@echo LIBRARIES
	@echo $(libraries)
