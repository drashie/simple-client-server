#include <stdio.h>
#include <stdlib.h>
#include "dataprocess.h"

#define FILE_PATH "data/.plist.txt"

/**
 * @brief get size of file
 * 
 * @return long file size in bytes + 1 for null terminated string
 */
long get_file_size(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    return (file_size + 1);
}

/**
 *  @brief read file data and return it
 * 
 *  @return buffer containing file contant as char *
 */
char* get_data_content(void)
{  
    /* open file */
    FILE *fp = fopen(FILE_PATH, "r");
    /* check for error while opening */
    if (fp == NULL) { printf("failed to open file\n"); return NULL; }

    /* get file size and create buffer with allocated file size */
    char *buffer = (char*)malloc((get_file_size(fp)) * sizeof(char));
    /* check if buffer could be allocated */
    if (buffer == NULL) { printf("failed to allocate memory for the file\n"); fclose(fp);}

    /* read file content into the buffer and return it */
    size_t bytes_read = fread(buffer, sizeof(char), (get_file_size(fp) - 1), fp);
    buffer[bytes_read] = '\0';

    fclose(fp);
    return buffer;
}

/**
 * @brief write given string at end of file (appending)
 * 
 * @param buffer String that will be appended to file
 * @return int error code 0 = OK
 */
int write_data_content(char* buffer)
{
    /* open file (appending mode)*/
    FILE *fp = fopen(FILE_PATH, "a");
    /* check for error while opening */
    if (fp == NULL) { printf("failed to open file\n"); return 1; }
    /* write given buffer to the file */
    if (fputs(buffer, fp) == EOF) { printf("failed to write\n"); fclose(fp); return 2; }

    fclose(fp);
    return 0;
}

int main(void)
{
    char *input_stream = "\nTHIS IS A NEW LINE\n";
    char *data;

    if (write_data_content(input_stream) != 0)
        return 1;

    data = get_data_content();

    printf("Written from file: %s", data);

    free(data);
    return 0;
}
