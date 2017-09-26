all: arvore matriz

arvore: arvore.o
	gcc -g arvore.o -o arvore -Wall -Wextra -Werror -std=c99 -pedantic -O2
matriz:  matriz.o
	gcc -g matriz.o -o matriz -Wall -Wextra -Werror -std=c99 -pedantic -O2
arvore.o: arvore.c arvore.h
	gcc -g arvore.c -c -Wall -Wextra -Werror -std=c99 -pedantic -O2
matriz.o: matriz.c matriz.h
	gcc -g matriz.c -c -Wall -Wextra -Werror -std=c99 -pedantic -O2
clean:
			$(RM) *.o arvore matriz
