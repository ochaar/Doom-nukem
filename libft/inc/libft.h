/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 18:18:57 by cglavieu          #+#    #+#             */
/*   Updated: 2019/07/25 05:58:06 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define BUFF_SIZE 9000

typedef struct		s_gnlu
{
	int			ret;
	char		*temp;
	char		*buff;
}					t_gnlu;

size_t				ft_strlen(char const *s);
size_t				ft_strlcat(char *dst, char const *src, size_t size);
void				ft_memdel(void **ap);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f) (unsigned int, char *));
void				ft_strdel(char **as);
void				ft_bzero(void *s, size_t n);
void				ft_strlclr(char *s);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putunsigned(unsigned int nb);
void				ft_putnbrendl(int nb);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_strclr(char *s);
void				ft_putnbr_fd(int n, int fd);
int					ft_atoi(char const *str);
unsigned int		ft_atou(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isfloat(char *str);
int					ft_isprint(int c);
int					ft_strisnone(char *str);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*str_to_upper(char *s);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					get_next_line_until(int const fd, char **line, int stop);
int					precise_get_next_line(int const fd, char **line, int size);
int					get_next_line(int const fd, char **line);
void				*ft_memalloc(size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strdup(char const *s1);
char				*ft_strstr(char const *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f) (char));
char				*ft_strmapi(char const *s, char (*f) (unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoinnfree(char *s1, char *s2, int fr);
char				*ft_strtrim(char const *s);
char				*ft_itoa(int n);
void				ft_light_itoa(int n, char *str);
char				*ft_strctrim(const char *s, char c);
char				**ft_strsplit(const char *s, char c);
char				*ft_epur_tabul(const char *src);
char				*ft_epur_str(const char *src);
double				ft_atof(const char *str);
void				ft_memreg(char **s);
void				ft_memreg3(char ***s);
unsigned int		ft_atoui_base(const char *str, int base);
char				*ft_uitoa_base(unsigned int n, int base);
char				*ft_ftoa(float fl, int precision);
int					ft_tab_len(char **tab);

#endif
