debug:
	mkdir -p Debug
	cp debug.Makefile Debug/makefile
	$(MAKE) -C Debug all

release:
	mkdir -p Release
	cp release.Makefile Release/makefile
	$(MAKE) -C Release all

clean:
	# $(MAKE) -C Debug clean
	rm -rf Debug
	# $(MAKE) -C Release clean
	rm -rf Release

.PHONY: debug release clean
