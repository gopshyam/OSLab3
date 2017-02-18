struct header{
    u32 ID_space; // 0x4100301:combined I&D|0x4200301:separate I&D
    u32 magic_number; // 0x00000020
    u32 tsize; // code section size in bytes
    u32 dsize; // initialized data section size in bytes
    u32 bsize; // bss section size in bytes
    u32 zero; // 0
    u32 total_size; // total memory size, including heap
    u32 symbolTable_size; // only if symbol table is present
}


int strtok(char *filename, char tok[20][20]) {
    //Tokenizes a filename, based on /
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



int load(char* filename, u16 segment) {

}
