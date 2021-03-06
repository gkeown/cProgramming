struct nlist { /* table entry */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined named */
    char *defn;         /* replacement text */
};


#define HASHSIZE 101

static struct nlist * hashtab[HASHSIZE]; /* point table */

/* hash: form hash value for string s */
unsigned
hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *
lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np; /* found */
        }
    }

    return NULL;
}

char *strdup2(char *);

/* install: put (name, defn) in hastab */
struct nlist *
install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));

        if (np == NULL || (np->name = strdup2(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np; 
    } else { /* already there */
        free((void *) np->defn); /* free previous defn */
    }

    if ((np->defn = strdup2(defn)) == NULL) {
        return NULL;
    }
    return np;
    }
}
