
INCLUDE := \
	-Iinclude	
SRCFILE := \
	common/saprint.c \
	test.c


test:$(SRCFILE)
	gcc $(INCLUDE) -o $@ $^
clean:
	rm test
