
GCCLIB	:= -lm

TESTDIR	:= test
INCLUDE := \
	-Iinclude
SRCFILE := \
	common/*.c \
	sort/*.c \
	structure/queue/*.c \
	structure/tree/*.c

sorttest:$(SRCFILE)
	@gcc $(INCLUDE) -o $@ $^ $(TESTDIR)/sorttest.c
pqtest:$(SRCFILE)
	@gcc $(INCLUDE) -o $@ $^ $(TESTDIR)/pqtest.c $(GCCLIB)
clean:
	$(shell [ -e sorttest ] && rm sorttest)
	$(shell [ -e pqtest ] && rm pqtest)
