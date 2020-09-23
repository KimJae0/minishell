/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonroy- <mmonroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 08:47:57 by aleon-ca          #+#    #+#             */
/*   Updated: 2020/09/22 13:37:20 by aleon-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			set_redirect(t_command_table *table, char *ptr, char *type)
{
	int			i;
	int			j;
	char		temp;

	i = 0;
	while ((ft_isspace_not_nl(ptr[++i])))
		;
	j = i;
	i--;
	while ((ptr[++i]) && !(ft_isspace_not_nl(ptr[i]))
		&& ((ft_isalnum(ptr[i])) || (ptr[i] == '.')))
		;
	temp = ptr[i];
	ptr[i] = '\0';
	if (ft_strcmp(type, "input"))
		table->input_file = ft_strdup(ptr + j);
	else if (ft_strcmp(type, "output"))
		table->output_file = ft_strdup(ptr + j);
	else if (ft_strcmp(type, "append"))
		table->append_file = ft_strdup(ptr + j);
	ptr[i] = temp;
}

char			*ft_add_char(char *str, char c)
{
	char	*rst;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	rst = ft_calloc(len + 2, sizeof(char));
	while (i < len)
	{
		rst[i] = str[i];
		i++;
	}
	rst[i] = c;
	free(str);
	return (rst);
}

/*
** Reads shell's stdin input one byte at a time until a '\n' is found
** If ctrl-D (EOF) is invoked, the shell is terminated.
*/

void			read_input(char *input)
{
	char	buff[1];
	int		bytes_read;

	while ((bytes_read = read(0, buff, 1)) && buff[0] != '\n')
		input = ft_add_char(input, buff[0]);
	input = ft_add_char(input, '\0');
	if (!bytes_read)
	{
		free(input);
		exit_minishell();
	}
}