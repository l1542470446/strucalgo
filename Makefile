
INCLUDE := \
	-Iinclude	
SRCFILE := \
	common/*.c \
	test.c \
	sort/*.c


test:$(SRCFILE)
	gcc $(INCLUDE) -o $@ $^
clean:
	rm test
