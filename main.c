#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ft_strlen(char *s) {
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

char *ft_strdup(char *s1) {
    char *temp;
    int i = 0;
    temp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
    if (!temp)
        return NULL;
    while (s1[i]) {
        temp[i] = s1[i];
        i++;
    }
    temp[i] = '\0';
    return temp;
}

char *ft_strjoin(char *s1, char *s2) {
    size_t i = 0;
    size_t j = 0;
    char *p;
    if (!s2)
        return NULL;
    p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!p)
        return NULL;
    while (s1[i]) {
        p[i] = s1[i];
        i++;
    }
    while (s2[j]) {
        p[i + j] = s2[j];
        j++;
    }
    p[i + j] = '\0';
    free(s1);
    return p;
}

void checking_if_pipe_exists(int ac, char **av, char **envp, int **array) {
    char *command = NULL;
    char *joined = NULL;
    int i = 1;
    while (av[i]) {
        if (av[i][0] != '|' && ft_strlen(av[i]) != 1) {
            if (joined == NULL) {
                joined = ft_strdup(av[i]);
            } else {
                joined = ft_strjoin(joined, " ");
                joined = ft_strjoin(joined, av[i]);
            }
        } else if (av[i][0] == '|' && ft_strlen(av[i]) == 1) {
            command = ft_strdup(joined);
            if (joined != NULL) {
                free(joined);
                joined = NULL;
            }
            // execute func
            printf("%s\n", command);
            free(command);
            command = NULL;
            joined = NULL;
        }
        i++;
    }
}

int main(int ac, char **av, char *envp[]) {
    checking_if_pipe_exists(ac, av, envp, NULL);
    return 0;
}
