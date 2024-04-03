/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:19:12 by escastel          #+#    #+#             */
/*   Updated: 2024/04/03 12:55:08 by escastel         ###   ########.fr       */
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

//ESTRUCTURA PARA GUARDAR LAS VARIABLES DE ENV SEPARANDO NOMBRES Y VALORES

typedef struct s_listenv
{
	char				*name;
	char				*value;
	int					index;
}	t_listenv;

//ESTRUCTURA PARA GUARDAR LOS COMANDOS

typedef struct s_cmds
{
	char	**full_cmd;
	char	**cmd_path;
	char	*exc_path;
	int		infile;
	int		outfile;
}	t_cmds;

//ESTRUCTURA GENERAL

typedef struct s_data
{
	t_list		*cmd;
	char		**env;
	char		*pwd;
	char		*oldpwd;
	t_list		*listenv;
}	t_data;

void	minishell_print(int flag);
int		init_struct(t_data *data, char **env);
void	lexer(t_data *data, char *line);
void	expander(t_data *data);
void	parser(t_data *data);

// BUILT-INS

void	builtins_control(t_data *data, char **full_cmd);
void	cd_built(t_data *data, char **cmd);
void	echo_built(char **cmd);
void	env_built(t_data *data, char **cmd);
int		env_initialize(t_data *data, char **new_env);
void	exit_built(void);
void	export_built(t_data *data, char **cmd);
void	export_var(t_data *data, char *str);
void	pwd_built(void);
void	unset_built(t_data *data, char **cmd);
void	unset_util(t_data *data, char *cmd);

// UTILS LISTAS

void	del_listenv(void *content);

#endif