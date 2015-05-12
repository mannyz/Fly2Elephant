config:
	cd $(CONFIG) && make all

debug:
	make config CONFIG=Debug 

release:
	make config CONFIG=Release

.PHONY: debug release config

