
GCCLIB	:= -lm

TESTDIR	:= test
INCLUDE := \
	-Iinclude
SRCFILE := \
	common/*.c \
	sort/*.c \
	structure/queue/*.c \
	structure/tree/*.c \
	structure/list/*.c

sorttest:$(SRCFILE)
	@gcc $(INCLUDE) -o $@ $^ $(TESTDIR)/sorttest.c $(GCCLIB)
pqtest:$(SRCFILE)
	@gcc $(INCLUDE) -o $@ $^ $(TESTDIR)/pqtest.c $(GCCLIB)
treetest:$(SRCFILE)
	@gcc $(INCLUDE) -o $@ $^ $(TESTDIR)/treetest.c $(GCCLIB)
clean:
	$(shell [ -e sorttest ] && rm sorttest)
	$(shell [ -e pqtest ] && rm pqtest)
	$(shell [ -e treetest ] && rm treetest)
