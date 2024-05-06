/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:19:12 by escastel          #+#    #+#             */
/*   Updated: 2024/05/06 14:45:23 by lcuevas-         ###   ########.fr       */
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
	char		*pwd;
	char		*line;
	char		*oldpwd;
	char		**env;
	char		**prompt;
	char		**cmd_path;
	int			i;
	int			j;
	int			fdin;
	int			fdout;
	int			status;
	int			builtin;
	int			pipe[2];
	t_list		*cmd;
	t_list		*listenv;
}	t_data;

//		VARIABLE GLOBAL

int		g_signal;

//		EXPERIMENTOS CON GASEOSA
int		ft_path(t_data *data);

//		FUNCIONES GENERALES

void	minishell_print(int flag);
void	clean_cmd(t_data *data);
void	clean_program(t_data *data);
int		error_msg(char	*str);
void	ft_clean_path(t_data *data);

// 		INITIALIZE

int		init_struct(t_data *data, char **env);
int		env_initialize(t_data *data, char **new_env);

//		LEXER

int		lexer(t_data *data, char *line);

//	QUOTES AND BACKLASHES

int		ft_backlashes(t_data *data, char **line, char **str);
int		ft_singlequote(t_data *data, char **line, char **str);
int		ft_doublequote(t_data *data, char **line, char **str);
int		ft_quotes_and_lashes(t_data *data, char **line, char **str);

//	TOKENS

int		ft_tokens_pipe(t_data *data, char **line, char **tmp);
int		ft_tokens_minor(t_data *data, char **line, char **tmp);
int		ft_tokens_mayor(t_data *data, char **line, char **tmp);

//		EXPANDER

void	expander(t_data *data, int i);
void	fill_tmp(char **tmp, char *func);
char	*get_status(t_data *data);
char	*expand_var(t_data *data, char *str, int i, int j);
int		expand_tilde(t_data *data, char **tmp, char *str);
int		dollar(char **tmp, char *str, t_data *data);

//		PARSER

int		parser(t_data *data);
int		ft_redir(t_data *data, t_cmds *aux, int i);
void	heredoc(t_data *data, t_cmds *cmd, int i);

// CMD CREATE

t_cmds	*ft_new_cmd_node(void);
void	ft_new_cmd(t_data *data);
void	ft_next_node(t_data *data);
char	**ft_tmp_reservator(t_data *data);

//		EXECUTER

void	executer(t_data *data);

// EXECUTER UTILS

void	ft_no_cmd(t_data *data, char **full_cmd);
void	ft_file_or_directory(t_data *data, t_list *cmd);
int		ft_path(t_data *data);
int		ft_command_filter(t_data *data, t_list *cmd);
int		ft_command_filter_2(t_data *data, t_list *cmd,
			char **cmd_slash, char **tmp);

// EXECUTER PROCESSS

void	ft_parent(t_data *data, t_list	*cmd);
void	ft_xone_child(t_data *data, t_list *cmd);
void	ft_child_redir(t_data *data, t_list *cmd);
void	ft_child(t_data *data, t_list *cmd, int flag);

//		SIGNAL

void	handler(int signal);

// 		BUILT-INS

bool	builtins_control(t_data *data, char **full_cmd, int flag);

//  CD

void	cd_built(t_data *data, char **cmd);

//  ECHO

void	echo_built(char **cmd);

//  ENV

void	env_built(t_data *data, char **cmd);

//  EXIT

void	exit_built(t_data *data, char **cmd);

//  EXPORT

void	export_built(t_data *data, char **cmd);

// EXPORT UTILS
void	add_var_list(t_data *data, char *str);
void	add_var_env(t_data *data, char *str);
void	replace_var(t_data *data, char *str);
int		check_new_var(t_data *data, char *str, int *flag);

//  PWD

void	pwd_built(void);

//  UNSET

void	unset_built(t_data *data, char **cmd);

//  UTILS

void	reset_index(t_data *data);
void	clean_str(t_data *data);

// 		UTILS LISTAS

void	del_cmd(void	*content);
void	del_listenv(void *content);

#endif