#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DEBUG 0

void check_file(const char *file)
{
    if (access(file, F_OK) == -1)
    {
        printf("[TEST FAILED] file access error: %s\n", file);
        exit(~0);
    }
}

void execute(char *cmd)
{
#if _WIN32
    int len = strlen(cmd);
    for (int i = 0; i < len; i++)
    {
        if (cmd[i] == '/')
        {
            cmd[i] = '\\';
        }
    }
#endif

    system(cmd);
}

void compare_files(const char *file1_name, const char *file2_name)
{
    FILE *file1 = fopen(file1_name, "r");
    FILE *file2 = fopen(file2_name, "r");

    while (1)
    {
        int a = fgetc(file1);
        int b = fgetc(file2);

        if (a == EOF && a == b)
        {
            break;
        }

        if (DEBUG)
        {
            putchar(a);
            putchar(b);
        }

        if (a != b)
        {
            printf("[TEST FAILED] files are different: %s %s", file1_name, file2_name);
            exit(~0);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 6)
    {
        printf("[TEST FAILED] argc should be at least 6. Got: %d\n", argc);
        return ~0;
    }

    const char *exp_file = argv[1];
    const char *headsup = argv[2];
    const char *type = argv[3];
    const char *out_file = argv[4];
    const char *in1_file = argv[5];
    const char *in2_file = argc > 6 ? argv[6] : NULL;

    check_file(exp_file);
    check_file(headsup);
    check_file(in1_file);
    if (in2_file)
    {
        check_file(in2_file);
    }

    char *cmd = NULL;
    if (!in2_file)
    {
        asprintf(&cmd, "%s %s %s %s", headsup, type, out_file, in1_file);
    }
    else
    {
        asprintf(&cmd, "%s %s %s %s %s", headsup, type, out_file, in1_file, in2_file);
    }

    if (DEBUG)
    {
        puts(cmd);
    }
    execute(cmd);

    check_file(out_file);
    compare_files(exp_file, out_file);

    puts("[TEST PASSED]");
    return 0;
}