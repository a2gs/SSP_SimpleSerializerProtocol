# Andre Augusto Giannotti Scota (https://sites.google.com/view/a2gs/)
# C flags:
CFLAGS_OPTIMIZATION = -g
#CFLAGS_OPTIMIZATION = -O3
CVERSION = c11
CFLAGS_VERSION = -std=$(CVERSION)
CFLAGS_WARNINGS = -Wall -Wextra -Wno-unused-parameter -Wno-unused-but-set-parameter
CFLAGS_DEFINES = -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -D_POSIX_SOURCE=1 -D_DEFAULT_SOURCE=1 -D_GNU_SOURCE=1
CFLAGS = $(CFLAGS_OPTIMIZATION) $(CFLAGS_VERSION) $(CFLAGS_WARNINGS) $(CFLAGS_DEFINES)

# System shell utilities
CC = gcc
RM = rm -fr
CP = cp
AR = ar
RANLIB = ranlib
CPPCHECK = cppcheck

INCLUDEPATH = -I./
LIBS = 
LIBPATH = -L./

all: clean exectag

exectag:
	@echo
	@echo "=== Code sanitizing =============="
	-ctags -R *
	-cscope -b -R
	-$(CPPCHECK) --enable=all --std=$(CVERSION) --platform=unix64 --language=c --check-config --suppress=missingIncludeSystem .

	@echo
	@echo "=== Compiling =============="
	$(CC) -o sample sample.c ssp.c $(CFLAGS) $(INCLUDEPATH) $(LIBPATH) $(LIBS)

clean:
	@echo
	@echo "=== clean_data =============="
	-$(RM) sample core tags cscope.out
