
/*************************************************************************
  usp  1   2   3   4   5   6   7   8   9  10   11   12    13  14  15  16
----------------------------------------------------------------------------
 |uds|ues|udi|usi|ubp|udx|ucx|ubx|uax|upc|ucs|uflag|retPC| a | b | c | d |
----------------------------------------------------------------------------
***************************************************************************/

/****************** syscall handler in C ***************************/
int put_word(u16 word, u16 segment, u16 offset)
{
    // uses put_byte to put a byte in memory
    u8 low_byte = word & 0x00FF;
    u8 high_byte = (word & 0xFF00) >> 8;
    //x86, little endian, put low byte first, then high byte
    put_byte(low_byte, segment, offset);
    put_byte(high_byte, segment, offset + 1);
}

u16 get_word(u16 segment, u16 offset) {
    //reads a word from memory and return it
    //x86, little endian, put low byte first, then high byte
    u8 low_byte = get_byte(segment, offset);
    u8 high_byte = put_byte(segment, offset + 1);
    u16 word = high_byte;
    word = (word << 8) + low_byte;
    return word;
}



int kcinth()
{
   int a,b,c,d, r;

    a = get_word(running->uss, running->usp + (13 * 2));
    b = get_word(running->uss, running->usp + (14 * 2));
    c = get_word(running->uss, running->usp + (15 * 2));
    d = get_word(running->uss, running->usp + (16 * 2));
    printf("Values found from the calling function: a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);

   switch(a){
       case 0 : r = kgetpid();        break;
       case 1 : r = kps();            break;
       case 2 : r = kchname(b);       break;
       case 3 : r = kkfork();         break;
       case 4 : r = ktswitch();       break;
       case 5 : r = kkwait(b);        break;
       case 6 : r = kkexit(b);        break;

       case 99: kkexit(b);            break;
       default: printf("invalid syscall # : %d\n", a); 
   }

    put_word(r, running->uss, running->usp + (8 * 2)); //Return value should be stored in ax of the running process' calling stack
}

//============= WRITE C CODE FOR syscall functions ======================

int kgetpid()
{
    return running->pid;
}

int kps()
{
    int i;
    int s;
    char status[32];
    printf("=======================================================\n");
    printf("name \t status \t pid \t ppid\n");
    printf("-------------------------------------------------------\n");
    
    for (i = 0; i < NPROC; i++) {
        s = proc[i].status;
        switch(s) {
            case FREE:
                strcpy(status, "FREE");
                break;
            case READY:
                strcpy(status, "READY");
                break;
            case RUNNING:
                strcpy(status, "RUNNING");
                break;
            case STOPPED:
                strcpy(status, "STOPPED");
                break;
            case SLEEP:
                strcpy(status, "SLEEP");
                break;
            case ZOMBIE:
                strcpy(status, "ZOMBIE");
                break;
        }
        printf("%s \t %s \t %d \t %d\n", proc[i].name, status, proc[i].pid, proc[i].ppid);
    }
}

int kchname(char *name)
{
    strcpy(running->name, name);
}

int kkfork()
{
  //use you kfork() in kernel;
  //return child pid or -1 to Umode!!!
    return kfork()->pid;
}

int ktswitch()
{
    return tswitch();
}

int kkwait(int *status)
{

  //use YOUR kwait() in LAB3;
  //return values to Umode!!!
    kwait(status);
    return 5;
}

int kkexit(int value)
{
    //use your kexit() in LAB3
    //do NOT let P1 die
    do_exit();
    return 8;
}
