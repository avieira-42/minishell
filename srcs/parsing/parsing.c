#include "parsing.h"
#include "../error/error.h"

void    parse_start(int argc, char *argv1)
{
    if (argc != 1)
        error_exit(argv1);
}
