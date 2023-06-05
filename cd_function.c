#include "minishell.h"
void cd_function(void)
{
    if (chdir("directory") != 0)
        perror("directory");
}


// int main()
// {
//     cd_function();
// }
