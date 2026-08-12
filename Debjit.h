#ifndef DEBJIT_H_
#define DEBJIT_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBJIT_UNIMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: %s is not implemented yet\n", \
                __FILE__, __LINE__, __func__); \
        abort(); \
    } while(0)

typedef size_t (*Debjit_Write)(const void *ptr, size_t size, size_t nmemb, void *stream);

typedef struct {
    void *sink;
    Debjit_Write write;
    size_t indent_level;
} Debjit;

/* Core Serializer Declarations */
void debjit_object_begin(Debjit *deb);
void debjit_object_end(Debjit *deb);
void debjit_member_key(Debjit *deb, const char *key);
void debjit_string_sized(Debjit *deb, const char *str, size_t len);
void debjit_null(Debjit *deb);

#ifdef DEBJIT_IMPLEMENTATION

static void debjit_pad(Debjit *deb) {
    for (size_t i = 0; i < deb->indent_level; ++i) {
        deb->write("  ", 1, 2, deb->sink);
    }
}

void debjit_object_begin(Debjit *deb) {
    deb->write("{\n", 1, 2, deb->sink);
    deb->indent_level++;
}

void debjit_object_end(Debjit *deb) {
    if (deb->indent_level > 0) deb->indent_level--;
    debjit_pad(deb);
    deb->write("}", 1, 1, deb->sink);
}

void debjit_member_key(Debjit *deb, const char *key) {
    debjit_pad(deb);
    deb->write("\"", 1, 1, deb->sink);
    deb->write(key, 1, strlen(key), deb->sink);
    deb->write("\": ", 1, 3, deb->sink);
}

void debjit_string_sized(Debjit *deb, const char *str, size_t len) {
    deb->write("\"", 1, 1, deb->sink);
    deb->write(str, 1, len, deb->sink);
    deb->write("\"\n", 1, 2, deb->sink);
}

void debjit_null(Debjit *deb) {
    deb->write("null\n", 1, 5, deb->sink);
}

#endif // DEBJIT_IMPLEMENTATION

#endif // DEBJIT_H_