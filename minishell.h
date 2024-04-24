/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:19:12 by escastel          #+#    #+#             */
/*   Updated: 2024/04/24 12:32:40 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*				LIBRERIAS 				*/

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
# include <stdbool.h>

/* 				COLORES					 */

# define BLUE    "\x1b[34m"
# define CYAN    "\x1b[36m"
# define GREEN   "\x1b[32m"
# define MAGENTA "\x1b[35m"
# define RED   	 "\x1b[31m"
# define RESET 	 "\x1b[0m"
# define YELLOW	 "\x1b[33m"


//		ESTRUCTURA PARA GUARDAR LAS VARIABLES DE ENV SEPARANDO NOMBRES Y VALORES

typedef struct s_listenv
{
	char				*name;
	char				*value;
	int					index;
}	t_listenv;

//		ESTRUCTURA PARA GUARDAR LOS COMANDOS

typedef struct s_cmds
{
	char	**full_cmd;
	char	*exc_path;
	int		infile;
	int		outfile;
	int		builtin;
}	t_cmds;

//		ESTRUCTURA GENERAL

typedef struct s_data
{
	char		**env;
	char		**prompt;
	char		*line;
	char		*pwd;
	char		*oldpwd;
	int			i;
	int			j;
	int			pipe[2];
	char		**cmd_path;
	t_list		*cmd;
	t_list		*listenv;
}	t_data;

//		VARIABLE GLOBAL

int		g_signal;

//		FUNCIONES GENERALES

void	minishell_print(int flag);
void	ft_liberator(t_data *data);
void	clean_program(t_data *data);

// 		INITIALIZE

int		init_struct(t_data *data, char **env);
int		env_initialize(t_data *data, char **new_env);

//		LEXER

int		lexer(t_data *data, char *line);

//		EXPANDER

void	expander(t_data *data);
void	fill_tmp(char **tmp, char *func);
void	dollar(char **tmp, char *str, int *i, int *j);
void	simple_quote(t_data *data, char **tmp, char *str);
char	*expand_var(t_data *data, char *str, int i, int j);
int		expand_tilde(t_data *data, char **tmp, char *str);

//		PARSER

int		parser(t_data *data);

//		SIGNAL

void	handler(int signal);

// 		BUILT-INS

bool	builtins_control(t_data *data, char **full_cmd, int flag);

// CD

void	cd_built(t_data *data, char **cmd);

// ECHO

void	echo_built(char **cmd);

// ENV

void	env_built(t_data *data, char **cmd);

// EXIT

void	exit_built(t_data *data);

// EXPORT

void	export_var(t_data *data, char *str);
void	export_built(t_data *data, char **cmd);

// PWD

void	pwd_built(void);

// UNSET

void	unset_util(t_data *data, char *cmd);
void	unset_built(t_data *data, char **cmd);

// 		UTILS LISTAS

void	del_cmd(void	*content);
void	del_listenv(void *content);

#endif