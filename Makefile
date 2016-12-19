
INCLUDE := \
	-Iinclude
SRCFILE := \
	common/*.c \
	sort/*.c

sorttest:$(SRCFILE)
	gcc $(INCLUDE) -o $@ $^ sorttest.c
clean:
	$(shell [ -e sorttest ] && rm sorttest)
