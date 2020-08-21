#include <global.h>
#include <getopt.h>
#include "stream.h"

void cdecl(stream_t **result, const char *file, const char *filters);

int main(int argc, char **argv)
{
    char type = 0;
    int option = 0;

    while ((option = getopt(argc, argv, ":hc")) != -1)
    {
        switch (option)
        {
        case 'h':
            type = 'h';
            break;
        case 'c':
            type = 'c';
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
        }
    }

    if (type == 0)
    {
        puts("missing option: choose -c or -h");
    }

    int left = argc - optind;
    if (left < 2)
    {
        puts("usage: headsup (-h|-c) <output.h> <input.c> [<input.h>]\n");
        puts("options:");
        puts("  -h: generate declarations for header");
        puts("  -c: generate declarations for source");
        puts("arguments:");
        puts("  - output: generated file, e.g. `file.decl.c` or `file.decl.h`");
        puts("  - input.c: source file with the definitions, e.g. `file.c`");
        puts("  - input.h: header file with the definitions, e.g. `file.h` (optional)");
        return ~0;
    }

    char *content = null;
    const char *out_file = argv[optind];
    const char *in1_file = argv[optind + 1];
    const char *in2_file = left > 2 ? argv[optind + 2] : null;

    stream_t *out = stream_open_file(out_file, "w");
    fputs("#pragma once\n\n", out);

    if (type == 'h')
    {
        if (in2_file)
        {
            stream_t *in2 = null;
            cdecl(&in2, in2_file, "");
            while (stream_read_line(&content, in2))
            {
                fputs(content, out);
                memory_free(content);
            }
            stream_close_process(in2);
            fputs("\n", out);
        }

        stream_t *in1 = null;
        cdecl(&in1, in1_file, "variables functions");
        while (stream_read_line(&content, in1))
        {
            fputs(content, out);
            memory_free(content);
        }
        stream_close_process(in1);
    }
    else
    {
        stream_t *in1 = null;
        cdecl(&in1, in1_file, "enums unions structs static_variables static_functions");
        while (stream_read_line(&content, in1))
        {
            fputs(content, out);
            memory_free(content);
        }
        stream_close_process(in1);
    }

    stream_close_file(out);
    return 0;
}

void cdecl(stream_t **result, const char *file, const char *filters)
{
    char *command = null;
    asprintf(&command, "cdecl %s %s", file, filters);
    *result = stream_open_process(command, "r");
    memory_free(command);
}
