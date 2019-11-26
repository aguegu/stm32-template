debug:
	mkdir -p $@
	cp debug.Makefile $@/makefile
	$(MAKE) -C $@ all

release:
	mkdir -p $@
	cp release.Makefile $@/makefile
	$(MAKE) -C $@ all

clean:
	rm -rf debug
	rm -rf release

.PHONY: debug release clean
