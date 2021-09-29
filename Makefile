Main: Build

Build:
	@cd libs && gcc -c ../lib/*.c
	@ar rs libs/libdict.a libs/*.o
