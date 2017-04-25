
GCCFLAG	:= -w
GCCLIB	:= -lm

TESTDIR	:= test

INCLUDE := \
		-Iinclude

SRC_DIR := $(shell pwd)

COMM_PATH := $(SRC_DIR)/common
COMM_FILE := $(COMM_PATH)/*.c

SORT_PATH := $(SRC_DIR)/sort
SORT_FILE := \
		$(COMM_FILE) \
		$(SORT_PATH)/*.c

STRC_PATH := $(SRC_DIR)/structure
STRC_FILE := \
		$(COMM_FILE) \
		$(STRC_PATH)/tree/*.c \
		$(STRC_PATH)/list/*.c

PRQU_PATH := $(STRC_PATH)/queue
PRQU_FILE := \
		$(SORT_FILE) \
		$(STRC_FILE) \
		$(PRQU_PATH)/*.c

ALGO_PATH := $(SRC_DIR)/algorithm
RAND_PATH := $(ALGO_PATH)/random
RAND_FILE := \
		$(COMM_FILE) \
		$(RAND_PATH)/*.c


sorttest:$(SORT_FILE)
	@gcc $(GCCFLAG) $(INCLUDE) -o $@ $^ $(TESTDIR)/sorttest.c $(GCCLIB)
pqtest:$(PRQU_FILE)
	@gcc $(GCCFLAG) $(INCLUDE) -o $@ $^ $(TESTDIR)/pqtest.c $(GCCLIB)
treetest:$(STRC_FILE)
	@gcc $(GCCFLAG) $(INCLUDE) -o $@ $^ $(TESTDIR)/treetest.c $(GCCLIB)
randtest:$(RAND_FILE)
	@gcc $(GCCFLAG) $(INCLUDE) -o $@ $^ $(TESTDIR)/randtest.c $(GCCLIB)
clean:
	$(shell [ -e sorttest ] && rm sorttest)
	$(shell [ -e pqtest ] && rm pqtest)
	$(shell [ -e treetest ] && rm treetest)
	$(shell [ -e randtest ] && rm randtest)
