#include "parent.h"

#include <stdio.h>

int main()
{
    ParentRoutine(getenv("PATH_TO_CHILD"), stdin);

    return 0;
}