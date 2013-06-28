#include <stdio.h>
#include <stdlib.h>
#include "txc_term.h"

int main() 
{
    printf(TXC_AF(5,31,"Hello,LINE:%d\n"), __LINE__);
    printf("The Green is in " TXC_GREEN("%dth") " line\n", __LINE__);
    printf("The Error is in " TXC_ERROR("%dth") " line\n", __LINE__);
    printf("The Blue is in " TXC_BLUE("%dth") " line\n", __LINE__);
    printf("The Warn is in " TXC_WARN("%dth") " line\n", __LINE__);
    printf("The Notice is in " TXC_NOTICE("%dth") " line\n", __LINE__);
    return 0;
}
