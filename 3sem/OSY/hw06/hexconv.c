#define EXIT_NUM 1
#define READ_NUM 3
#define WRITE_NUM 4

#define STDOUT 1
#define STDIN 0

int isnum(char ch);
int isspc(char ch);
void myExit(unsigned int retValue);
int myWrite(char buf[20], long unsigned length);
int myRead(char buf[20]);
static void print(unsigned num);

int isnum(char ch) {
    return ch >= '0' && ch <= '9';
}

int isspc(char ch) {
    return ch == ' ' || ch == '\n';
}

void myExit(unsigned int retValue) {
    asm volatile("int $0x80"
                 :
                 : "a"(EXIT_NUM), "b"(retValue));
}

int myWrite(char buf[20], long unsigned length) {
    int ret;
    asm volatile("int $0x80"
                 : "=a"(ret)
                 : "a"(WRITE_NUM), "b"(STDOUT), "c"(buf), "d"(length)
                 : "memory");
    return ret;
}

int myRead(char buf[20]) {
    int ret;
    asm volatile("int $0x80"
                 : "=a"(ret)
                 : "a"(READ_NUM), "b"(STDIN), "c"(buf), "d"(20)
                 : "memory");
    return ret;
}

static void print(unsigned num) {
    char buf[20];

    if (num == 0) {
        buf[0] = '0';
        buf[1] = 'x';
        buf[2] = '0';
        buf[3] = '\n';
        buf[4] = '\0';
        long unsigned length = sizeof(buf);

        int ret = myWrite(buf, length);
        if (ret == -1) {
            myExit(1);
        }
    } else {
        char hexNum[21];
        unsigned int remainder = 0, idx = 1;
        hexNum[0] = '\n';
        while (num != 0) {
            remainder = num % 16;
            if (remainder > 9) {
                if (remainder == 10) {
                    hexNum[idx] = 'a';
                } else if (remainder == 11) {
                    hexNum[idx] = 'b';
                } else if (remainder == 12) {
                    hexNum[idx] = 'c';
                } else if (remainder == 13) {
                    hexNum[idx] = 'd';
                } else if (remainder == 14) {
                    hexNum[idx] = 'e';
                } else if (remainder == 15) {
                    hexNum[idx] = 'f';
                }
            } else {
                hexNum[idx] = remainder + '0';
            }
            idx++;
            num /= 16;
        }
        hexNum[idx] = 'x';
        hexNum[idx + 1] = '0';
        hexNum[idx + 2] = '\0';

        int j = 0;
        for (int i = idx + 1; i >= 0; --i) {
            buf[j] = hexNum[i];
            j++;
        }
        buf[j] = '\0';

        long unsigned length = sizeof(buf);

        int ret = myWrite(buf, length);
        if (ret == -1) {
            myExit(1);
        }
    }
}

void _start() {
    char buf[20];
    unsigned num = 0;
    int i;
    int num_digits = 0;
    unsigned chars_in_buffer = 0;
    for (/* no init */; /* no end condition */; i++, chars_in_buffer--) {
        if (chars_in_buffer == 0) {
            int ret = myRead(buf);
            if (ret < 0) {
                myExit(1);
            }
            i = 0;
            chars_in_buffer = ret;
        }
        if (num_digits > 0 && (chars_in_buffer == 0 || !isnum(buf[i]))) {
            print(num);
            num_digits = 0;
            num = 0;
        }
        if (chars_in_buffer == 0 /* EOF */ || (!isspc(buf[i]) && !isnum(buf[i]))) {
            myExit(0);
        }
        if (isnum(buf[i])) {
            num = num * 10 + buf[i] - '0';
            num_digits++;
        }
    }
}
