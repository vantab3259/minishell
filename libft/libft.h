/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:24:29 by mudoh             #+#    #+#             */
/*   Updated: 2023/10/26 01:55:52 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include "ft_printf.h"
# include <stdbool.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
bool		ft_atoll_verif(const char *nptr);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *str);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strchr(const char *s, int c);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_itoa(int n);
void		ft_putnbr_fd(int n, int fd);
char		*get_next_line(int fd);
char		*gnl_join(char *str1, char *str2, int nb_read);
char		*gnl_trim(char *str);
char		*gnl_dub(char *str);

#endif
