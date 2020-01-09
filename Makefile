make_hilbert: make_hilbert.c
	$(CC) -O2 -Wall -o "$@" $<

clean:
	rm -f make_hilbert

.PHONY: clean
