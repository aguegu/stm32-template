debug:
	$(MAKE) -C Debug all

release:
	$(MAKE) -C Release all

clean:
	$(MAKE) -C Debug clean
	$(MAKE) -C Release clean

.PHONY: debug release clean
