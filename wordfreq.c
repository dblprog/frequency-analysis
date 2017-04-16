// wordfreq.c

// reads the next word from input,
// returning either a pointer to a buffer containing that word
// or NULL if there are no words to be read.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_word() {
	int size = 64;
	char b[size];
	bzero(b,size);

	if(scanf("%63[^ \t.\n]%*c",b)) {
		char* c = strdup(b); 
		c[size-1] = '\0';
		return c;
		free(b);
	} 

	return NULL;
}


typedef struct {
    char *word;
    int count;
} dict_entry_type;

typedef struct {
	int size; 
} dict_type;

void dict_initialize(dict_type *d);
void dict_increment(dict_type *d, char *word);

dict_entry_type **dict_get_entries(dict_type *d);

int main(int argc, char** argv) {
	printf("%s \n", get_word());
//	while(scanf(" %49[^ \t.\n]%*c", i)) {
//		}
//	printf("%s ", argv[1]);  // print input value
//	if
	exit(0);
}