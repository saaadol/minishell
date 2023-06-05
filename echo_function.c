#include "minishell.h"


void echo_function(char **av, int fd)
{
    int i = 1;
    char *x = "echo";
    int new_line_flag = 0;
    int j = 0;

    while (av[i])
    {
        if (!av[i + 1])
            return;
        if (ft_strlen(av[i]) && !ft_strncmp(av[i], x, ft_strlen(x)))
        {
            i++;
            while (av[i][0] == '-' && av[i][1] == 'n')
            {
                j = 1;
                while (av[i][j] == 'n')
                {
                    j++;
                }
                if (av[i][j] && av[i][j] != 'n')
                    break;
                if (!av[i][j])
                {
                    new_line_flag = 1;
                }
                i++;
            }
            while (av[i])
            {
                if ((av[i][0] == '|' && !av[i][1]))
                {
                    return ;
                }
                if (fd == -99)
                    fd = 1;
                write(fd, av[i], ft_strlen(av[i]));
                if(av[i+1])
                    write(fd, " ", 1);
                i++;
            }
            if (!new_line_flag)
                write(fd, "\n", 1);
        }
        i++;
    }
}

// int main(int ac, char **av)
// {
//     echo_function(av, -99);
// }
