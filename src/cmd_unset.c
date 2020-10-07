/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:13:01 by mmonroy-          #+#    #+#             */
/*   Updated: 2020/10/01 13:09:40 by mmonroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

static void     free_double(char **str)
{
    int i;

	i = 0;
	while(str[i])
		free(str[i++]);
	free(str);
    return;
}

static void     del_g_env(char *arg)
{
    char    **temp;
    char    **buff;
    int     i;
    int     j;

    i = -1;
    j = -1;
    temp = (char**)ft_calloc(envp_len(g_env), sizeof(char*));
    while (g_env[++i])
        if (ft_strncmp(arg, g_env[i], ft_find_char(g_env[i], '=')) != 0)
            if(!(temp[++j] = ft_strdup(g_env[i])))
                exit_minishell ();
    buff = g_env;
    g_env = temp;
    free_double(buff);
    return;
}

static int      ft_check(char *str)
{
    int i;
    int len;

    i = -1;
    len = ft_strlen(str);
    if (ft_find_char(str, '=') != -1)
    {  
        write(1, "unset: ", 7);
        write(1, str, len);
        write(1, ": invalid parameter name\n", 25);
        return (0);
    }
    i = -1;
    while (g_env[++i])
        if (ft_strncmp(str, g_env[i], len) == 0)
            return (1);
    return (0);
}

void            cmd_unset(char **arg)
{
    int i;

    i = 0;
    if (!arg[1])
        write(1, "unset: not enough arguments\n", 28);
    while (arg[++i])
        if (ft_check(arg[i]))
            del_g_env(arg[i]);
    return;
}