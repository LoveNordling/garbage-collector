GC: gc
TEST: tests

all: gc test demo

gc:
	$(MAKE) -C src all

run: 	gc
	$(MAKE) -C src run

test:
	$(MAKE) -C test run

memtest: 
	$(MAKE) -C test valgrind

demo:	
	$(MAKE) -C demo run

memdemo: 
	$(MAKE) -C demo valgrind

debug: gc
	$(MAKE) -C src debug

debug_test: test
	$(MAKE) -C test debug

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	$(MAKE) -C demo clean

docs:
	$(MAKE) -C src docs

.PHONY : all test demo run memtest memdemo debug debug_test clean docs
