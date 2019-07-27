/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 12:41:26 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/11 12:41:29 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

char		***assemble_cmd_args(char ***cmd, char **tmp, int cmd_count)
{
	int		j;
	int		i;
	int		i2;
	int		x;

	j = 0;
	i = 0;
	cmd = (char ***)malloc(sizeof(char **) * (cmd_count + 1));
	cmd[cmd_count] = NULL;
	while (j < cmd_count)
	{
		i2 = 1;
		while (ft_strncmp(tmp[i + i2], "-", 1) != 0)
			i2++;
		cmd[j] = (char **)malloc(sizeof(char *) * (i2 + 1));
		cmd[j][i2] = NULL;
		x = 0;
		while (x < i2)
		{
			cmd[j][x] = tmp[i++];
			x++;
		}
		j++;
	}
	return (cmd);
}

char		***do_parse_cmd(char ***cmd, int ac, char **av)
{
	int		i;
	int		cmd_count;
	char	**tmp;

	i = 0;
	cmd_count = 0;
	tmp = (char **)malloc(sizeof(char *) * (ac));
	tmp[ac - 1] = NULL;
	while (ac--)
		tmp[ac] = ft_strtrim(av[ac + 1]);
	if (ft_strncmp(tmp[0], "-", 1) == 0 && ft_strcmp(tmp[0], "-") != 0)
	{
		while (tmp[i])
		{
			if (ft_strncmp(tmp[i], "-", 1) == 0)
				cmd_count++;
			i++;
		}
		cmd = assemble_cmd_args(cmd, tmp, cmd_count);
	}
	free(tmp);
	return (cmd);
}

char		***parse_cmd(int ac, char **av)
{
	char	***cmd;

	cmd = NULL;
	if ((cmd = do_parse_cmd(cmd, ac, av)) == NULL)
		return (NULL);
	else
		return (cmd);
}
