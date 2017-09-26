all: arvore matriz

arvore: arvore.o
	gcc arvore.o -o arvore -Wall -Wextra -Werror -std=c99 -pedantic -O2
matriz:  matriz.o
	gcc matriz.o -o matriz -Wall -Wextra -Werror -std=c99 -pedantic -O2
arvore.o: arvore.c arvore.h
	gcc arvore.c -c -Wall -Wextra -Werror -std=c99 -pedantic -O2
matriz.o: matriz.c matriz.h
	gcc matriz.c -c -Wall -Wextra -Werror -std=c99 -pedantic -O2
clean:
			$(RM) *.o arvore matriz
