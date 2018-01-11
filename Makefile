GC: gc
TEST: tests

all: gc test

gc:
	$(MAKE) -C src gc

run: gc
	$(MAKE) -C src run

test:
	$(MAKE) -C test tests 


run_test: 
	$(MAKE) -C test run_test

demo:
	$(MAKE) -C demo all

debug: gc
	$(MAKE) -C src debug

debug_test: test
	$(MAKE) -C test debug

clean:
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	$(MAKE) -C demo clean

docs:
	doxygen Doxyfile

.PHONY = run run_test debug debug_test clean docs
