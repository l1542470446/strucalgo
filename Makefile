
INCLUDE := \
	-Iinclude	
SRCFILE := \
	common/saprint.c \
	test.c \
	sort/*.c


test:$(SRCFILE)
	gcc $(INCLUDE) -o $@ $^
clean:
	rm test
