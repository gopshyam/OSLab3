#include<stdio.h>


int strtok(char *filename, char tok[20][20]) {
    int n = 1;
    int i = 0, j = 0;
    
    while(1) {
        
    printf("%c\n", filename[n]);
        if(filename[n] == '\0') {
            return i;
        }
        if(filename[n] == '/') {
            tok[i][j] = '\0';
            i++;
            j = 0;
            n++;
        } else {
            tok[i][j] = filename[n];
            j++;
            n++;
        }
    }
}

main() {

    char filename[] = "/bin/u1/u2/3";
    char tok[20][20];
    int len = strtok(filename, tok);

    printf("%d\n", len);
    int i;
    for (i=0; i<len; i++) {
        printf("%s\n", tok[i]);
    }
}
