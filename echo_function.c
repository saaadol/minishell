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
            if (av[i + 1][0] == '-')
            {
                if (av[i + 1][1] == 'n')
                {
                    j = 1;
                    while (av[i + 1][j] == 'n')
                    {
                        j++;
                    }
                    if (!av[i + 1][j])
                    {
                        new_line_flag = 1;
                        i++;
                    }
                    else if (av[i + 1][j] == ' ')
                    {
                        new_line_flag = 0;
                        break;
                    }
                }
            }
            while (av[i])
            {
                if ((av[i][0] == '|' && !av[i][1]) || (av[i + 1][0] == '|' && !av[i + 1][1]))
                {
                    break;
                }

                if (fd == -99)
                    fd = 1;
                write(fd, av[i + 1], ft_strlen(av[i + 1]));
                if (!av[i + 2] || (av[i + 2][0] == '|' && !av[i + 2][1]))
                    break;
                write(fd, " ", 1);
                i++;
            }
            if (!new_line_flag)
                write(fd, "\n", 1);
        }
        i++;
    }
}





int main(int ac, char **av)
{
    echo_function(av, -99);
}
