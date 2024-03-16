/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:16:04 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/16 10:22:55 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_env(char **env, char *var_name)
{
	int		i;
	char	*cut_str;

	i = 0;
	if (!env || !*env || !var_name)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], var_name, ft_strlen(var_name)))
		i++;
	if (!env || !env[i])
		return (NULL);
	cut_str = ft_strcut(env[i], var_name);
	return (cut_str);
}

void	edit_env(t_ms *ms)
{
	int	i;

	i = get_env_indice(ms, "PWD");
	free(ms->env[i]);
	ms->env[i] = ft_strjoin("PWD=", get_cwd(), NULL, 0b010);
}

void	old_pwd(t_ms *ms)
{
	int		i;

	i = get_env_indice(ms, "OLDPWD");
	free(ms->env[i]);
	ms->env[i] = \
		ft_strjoin("OLDPWD=", get_cwd(), NULL, 0b010);
}

void	handle_flag(t_ms *ms)
{
	char	*old_pwd;
	char	*tmp;
	int		i;

	old_pwd = ft_strjoin("OLDPWD=", get_cwd(), NULL, 0b010);
	tmp = ft_strcut(ms->env[get_env_indice(ms, "OLDPWD")], "OLDPWD=");
	chdir(tmp);
	free(tmp);
	i = get_env_indice(ms, "OLDPWD");
	free(ms->env[i]);
	ms->env[i] = old_pwd;
}

char	*get_cwd(void)
{
	char	cwd[65536];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (NULL);
}
