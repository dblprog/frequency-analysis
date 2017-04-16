// freq.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

typedef struct {
    char *word;
    int count;
} dict_entry_type;

typedef struct dict_item {
    struct dict_item *next;
    dict_entry_type entry;
} dict_item;

typedef struct {
    dict_item *contents;
} dict_type;

char *get_word() {
    static char buf[257]; // shouldn't overflow!
	int c = '\0';
    while (!isalpha(c = getchar())) {
        if (c == EOF) {
            return NULL;
        }
    }        
    int i = 0;
    do {
        buf[i++] = tolower(c);
        assert (i < 256);
    } while (isalpha(c = getchar()) && c != EOF);

    buf[i] = '\0';
	    
    return buf;
}


void dict_initialize(dict_type *d) {
    d->contents = NULL;
}

void dict_increment(dict_type *dpt, char *word){
    dict_item **bpt = &dpt->contents;
    
    while(*bpt != NULL && strcmp((*bpt)->entry.word,word)) {
        bpt = &(*bpt)->next;
    }
    
    if (*bpt == NULL) {
        (*bpt) = (dict_item *) malloc (sizeof(dict_item));
        assert(*bpt != NULL);
    
        (*bpt)->next = NULL;
        (*bpt)->entry.word = strdup(word);
        (*bpt)->entry.count = 0;
    }
    
    (*bpt)->entry.count++;
    
    return;
}

static int dict_comp(const void *a, const void *b) {  
// static comparison function, as per qsort's arg req

	dict_entry_type *ap = * (dict_entry_type **)a;
	dict_entry_type *bp = * (dict_entry_type **)b;

	
	if (bp->count - ap->count != 0) {
	    return bp->count - ap->count;
	}

	return strcmp(ap->word,bp->word);
}

dict_entry_type **dict_get_entries(dict_type *d) {
	
	int count = 0;
	
	for (dict_item *cp = d->contents; cp != NULL; cp = cp->next) {
	    ++count;
	}
	
	dict_entry_type **result = (dict_entry_type **) calloc(count+1,sizeof(dict_entry_type *));
	assert(result != NULL);
    	
	int index = 0;

	for (dict_item *cp = d->contents; cp != NULL; cp = cp->next) {
        result[index++] = &cp->entry;
	}

	qsort((void*) result, count, sizeof(dict_entry_type *),dict_comp);	
	return result;
}

int main(int argc, char **argv) {
	
	dict_type d;
	dict_initialize(&d);
	
	char *word;
	while ((word = get_word())) {
		dict_increment(&d,word);
	}
	
	dict_entry_type **entries = dict_get_entries(&d);
	
	for (int i = 0; entries[i] != NULL; ++i) {
		printf("%-16s %d\n",entries[i]->word, entries[i]->count);
	}
	
	exit(0);
}