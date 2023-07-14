#include <stdio.h>
#include <stdlib.h>
#include "dataprocess.h"

/* read file data and return it */
char* get_data_content(void)
{  
    /* open file */
    FILE *fp = fopen("data/.plist.txt", "r");

    if (fp == NULL) {
        printf("failed to open file\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    char *buffer = (char*)malloc((file_size + 1) * sizeof(char));

    if (buffer == NULL) {
        printf("failed to allocate memory for the file\n");
        fclose(fp);
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, fp);
    buffer[bytes_read] = '\0';

    fclose(fp);
    return buffer;
}

int main(void)
{
    printf("hello world!\n");
    char *data = get_data_content();
    printf("data: %s\n", data);
    free(data);
    return 0;
}
