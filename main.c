#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
        char *src_file = NULL;
        char *out_file = NULL;

        for (int i = 1; i < argc; i += 2)
        {
                if (strcmp(argv[i], "-src") == 0)
                {
                        src_file = argv[i + 1];
                }
                else if (strcmp(argv[i], "-out") == 0)
                {
                        out_file = argv[i + 1];
                }
        }

        if (!src_file || !out_file)
        {
                printf("Usage: ./asm -src file.asm -out file.bin\n");
                return 1;
        }

        FILE *src = fopen(src_file, "r");
        FILE *out = fopen(out_file, "wb");

        if (!src || !out)
        {
                printf("Error opening files.\n");
                return 1;
        }

        char line[256];
        int line_number = 0;

        while (fgets(line, sizeof(line), src))
        {
                line_number++;

                if (strstr(line, "HALT"))
                {
                        unsigned char opcode = 0xF;
                        fwrite(&opcode, sizeof(opcode), 1, out);
                }
                else if (strstr(line, "ADD"))
                {
                        unsigned char opcode = 0x1;
                        fwrite(&opcode, sizeof(opcode), 1, out);
                }
                else
                {
                        printf("Error at line %d: %s\n", line_number, line);
                        return -1;
                }
        }

        fclose(src);
        fclose(out);
        return 0;
}
