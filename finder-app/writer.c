#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>
#include <syslog.h>


int main(int argc, char *argv[]) {
    // Open syslog with a program identifier
    openlog("writer", LOG_DEBUG, LOG_ERR);
    syslog(LOG_DEBUG, "Writing <%s> to <%s>", argv[1],argv[2]);
    if (argc != 3) {
        return 1;
    }

    char *filename = argv[1];
    char *text_to_write = argv[2];


    // Open the file for writing (creates new or truncates existing)
    FILE *file = fopen(filename, "w");
    if (!file) {
        syslog(LOG_ERR, "Failed to open file");
        return 1;
    }

    // Write the text string to the file
    if (fprintf(file, "%s", text_to_write) < 0) {
        syslog(LOG_ERR, "Failed to write to file");
        fclose(file);
        return 1;
    }

    // Close the file
    fclose(file);
    closelog(); // Close syslog connection
    return 0;
}

