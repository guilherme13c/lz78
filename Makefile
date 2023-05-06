all:
	g++ main.cpp -o lz78-compress


clean:
	rm -f lz78-compress test/*_compressed.lz78 test/*_decompressed.txt
