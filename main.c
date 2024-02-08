#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

#define SVFMT "%.*s"
#define SVVARG(sv) sv.size, sv.data


typedef struct {
    char *data;
    int size;
} Sv;

typedef struct {
    char *data;
    int size;
    int position;
} Stream;

Sv nextCSVEntry(Stream *stream)
{
    Sv sv = {0};
    int start_pos = stream->position;
    sv.data = stream->data+stream->position;
    while(stream->data[stream->position++]!=','||stream->data[stream->position++]){
        if(stream->data[stream->position++]=='"'){
            while(stream->data[stream->position++]!=',');
        }
    }
    sv.size=stream->position-start_pos;
    return sv;
}

int main(void)
{
    const char *file_name = "./Text-Classification-Ag-News/data/test.csv";
    FILE *file = fopen(file_name, "r");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("Reading file '%s' of size %zd bytes...\n", file_name, file_size);
    char *text_data = malloc(file_size+1);
    fread(text_data, file_size, 1, file);
    printf("Done.\n");
    Stream text_data_stream = {.data=text_data, .size=file_size, .position=0};
    // Headers
    printf("--- Headers ---\n");
    for (int i = 1; i < 3; i++) {
        Sv sv = nextCSVEntry(&text_data_stream);
        printf(SVFMT" : ", SVVARG(sv));
    }
    puts("");
    // Content
    printf("--- Content ---\n");
    for (int i = 1; i < 1; i++) {
        Sv sv = nextCSVEntry(&text_data_stream);
        printf(SVFMT" : ", SVVARG(sv));
    }
    return 0;
}
