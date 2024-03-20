/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:19:12 by escastel          #+#    #+#             */
/*   Updated: 2024/03/19 16:38:09 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_listenv
{
	char			*name;
	char			*value;
	int				index;
	struct s_data	*data;
}	t_listenv;

typedef struct s_data
{
	char		**cmd;
	char		**env;
	char		*oldpwd;
	t_listenv	*listenv;
}	t_data;

void	minishell_print(int flag);

// BUILT-INS

void	builtins_control(t_data *data, char **env);
void	cd_built(t_data *data, char **cmd);
void	echo_built(char **cmd);
void	env_built(t_data *data, char **cmd);
void	env_initialize(t_data *data, char **old_env);
void	exit_built(void);
void	export_built(t_data *data, char **cmd);
void	pwd_built(void);
void	unset_built(t_data *data, char **cmd);

#endif