GC: gc
TEST: tests

all: gc test demo

gc:
	$(MAKE) -C src all

run: 	gc
	$(MAKE) -C src run

test:
	$(MAKE) -C test all

run_test: test
	$(MAKE) -C test run

demo:	
	$(MAKE) -C demo all

run_demo: demo
	$(MAKE) -C demo run

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

.PHONY : all test demo run run_test debug debug_test clean docs
