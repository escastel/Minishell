/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:21:55 by escastel          #+#    #+#             */
/*   Updated: 2024/03/15 15:22:35 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_strncmp(char *s1, char *s2, int n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);
long int	ft_atoi(const char *str);
void		*ft_memmove(void *dst, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*get_next_line(int fd);
size_t		ft_strlen_gnl(const char *s);
int			ft_strchr_gnl(const char *s, int c);
void		*ft_calloc_gnl(size_t count, size_t size);
char		*ft_strjoin_gnl(char *s1, char *s2);
int			ft_printf(char const *str, ...);
int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_count_nb(int nb);
int			ft_putnbr(int nb);
int			ft_count_unsignb(unsigned int nb);
int			ft_putunsignbr(unsigned int nb);
int			ft_puthexa(unsigned long long nb, char c);
int			ft_putptr(unsigned long long ptr);
int			ft_abs(int nb);
int			ft_strcmp(char *s1, char *s2);
int			ft_strrlen(char **s);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;

}	t_stack;

t_stack		*ft_lstnew(int value);
void		ft_lstadd_front(t_stack **lst, t_stack *new);
int			ft_lstsize(t_stack *lst);
t_stack		*ft_lstlast(t_stack *lst);
void		ft_lstadd_back(t_stack **lst, t_stack *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
