
#include "minishell.h"
static void	skip_space(const char *nptr, int *i)
{
	while (nptr[*i] == 32 || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
}

static void	result_sign(const char *str, int *i, int *sign)
{
	if (str[*i] == '-')
	{
		*sign *= -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
}

int	ft_atoi(const char *nptr)
{
	int	x[2];
	int	result;
	int	temp;

	x[0] = 0;
	x[1] = 1;
	result = 0;
	skip_space(nptr, &x[0]);
	result_sign(nptr, &x[0], &x[1]);
	while ((nptr[x[0]] >= 48 && nptr[x[0]] <= 57))
	{
		temp = result;
		result = result * 10;
		if (result / 10 != temp && result)
		{
			if (x[1] == -1)
				return (0);
			return (-1);
		}
		result += nptr[x[0]] - 48;
		x[0]++;
	}
	return (result * x[1]);
}
int is_num(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        i++;
    }
    return 1;

}
void exit_function(char **av)
{
    int i = 1;
    while (av[i])
    {
        if (ft_strlen(av[i]) == ft_strlen("exit") && !ft_strncmp(av[i], "exit", ft_strlen("exit")))
        {   
            if (av[i + 1] && is_num(av[i + 1]) == 1)
            {
                exit(ft_atoi(av[i+1]));
            }
            if (av[i + 1] && !is_num(av[i+1]))
                perror(av[i + 1]);
        }
        i++;
    }

    
    
}

int main(int ac, char **av)
{
    exit_function(av);
}