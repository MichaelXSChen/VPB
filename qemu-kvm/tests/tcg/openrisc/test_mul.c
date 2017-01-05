#include <stdio.h>

int main(void)
{
    int a, b, c;
    int result;

    b = 0x4;
    c = 0x1;
    result = 0x4;
    __asm
    ("l.mul    %0, %1, %2\n\t"
     : "=r"(a)
     : "r"(b), "r"(c)
    );
    if (a != result) {
        printf("mul error\n");
        return -1;
    }

    b = 0x1;
    c = 0x0;
    result = 0x0;
    __asm
    ("l.mul    %0, %1, %2\n\t"
     : "=r"(a)
     : "r"(b), "r"(c)
    );
    if (a != result) {
        printf("mul error\n");
        return -1;
    }

    b = 0x1;
    c = 0xff;
    result = 0xff;
    __asm
    ("l.mul    %0, %1, %2\n\t"
     : "=r"(a)
     : "r"(b), "r"(c)
    );
    if (a != result) {
        printf("mul error\n");
        return -1;
    }

    b = 0x7fffffff;
    c = 0x2;
    result = 0xfffffffe;
    __asm
    ("l.mul    %0, %1, %2\n\t"
     : "=r"(a)
     : "r"(b), "r"(c)
    );
    if (a != result) {
        printf("mul error\n");
        return -1;
    }

    return 0;
}
