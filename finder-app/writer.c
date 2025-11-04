#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    openlog(NULL, 0, LOG_USER);

    if(argc != 3) {
        printf("Error: Invalid number of arguments.");
        printf("Usage: %s <filesdir> <searchstr>", argv[0]);

        syslog(LOG_ERR, "Invalid number of arguments: %d", argc - 1);

        closelog();
        return 1;
    }

    char *writefile = argv[1];
    char *writestr = argv[2];

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    FILE *fp = fopen(writefile, "w");
    if (fp == NULL) {
        printf("Error: fail to open the file %s", writefile);

        syslog(LOG_ERR, "Fail to open file %s: %m", writefile);

        closelog();

        return 1;
    }

    fprintf(fp, "%s", writestr);
    fprintf(fp, "\n");
    
    fclose(fp);

    closelog();
    return 0;
}