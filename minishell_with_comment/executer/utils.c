#include "minishell.h"

// разбиение строки на ключ и добавление в лист
void find_key(char *content, t_env *d)
{
    int j;
    int l;
    
    j = 0;
    l = ft_strlen(content);
// printf("l = %d, k = %d, content[i] = %c\n", l, k, content[i]);
   
    d->key = (char *) malloc(l * sizeof(char));
    if (d->key == NULL)
        return ;
    d->value = NULL;
    while(l > j)
    {
        d->key[j] = content[j];
        j++;
    }
    d->key[j] = '\0';

    free(content); // ?
// printf("Проверка 0 | key: %s |\n", d->key);
}

// разбиение строки на ключ и значение и добавление в лист
void find_key_value(char *content, t_env *d)
{
    int i;
    int j;
    int l;
    int k;

    i = 0;
    j = 0;
    l = ft_strlen(content);
    while (content[i] != '=')
        i++;
    k = i;
    // d->equally = &content[i];
// printf("k = %d, content[i] = %c\n", k, content[i]);
    d->key = (char *) malloc(i * sizeof(char));
    if (d->key == NULL)
        return ;
    d->value = (char *) malloc((l - i - 1) * sizeof(char));
    if (d->value == NULL)
        return ;
    int r = 0;

// СТАРАЯ ВЕРСИЯ
    while(l > j)
    {
        if(i > j)
            d->key[j] = content[j];
        else
        {
            if(k != j)
            {
                d->value[r] = content[j];
                r++;
            }
        }
        j++;
    }

/* НОВАЯ ВЕРСИЯ, вроде как плохо работает
    while (i > j)
    {
        d->key[j] = content[j];
        j++;
    }
    d->key[j] = '\0';
    while(l > j)
    {
        if(k != j)
        {
            d->value[r] = content[j];
            r++;
        }
        j++;
    }
    d->value[r]= '\0';
*/

// printf("Проверка 0 | key: %s | value: %s |\n", d->key, d->value);
}

// добавление нового элемента в список - и ключа и значение
void add_new_elem_key_value(t_env *something, char *str)
{
    t_env *new;
    new = ft_lstnew_mod(str);
// printf("Проверка: key = %s value = %s\n", tmp->key, tmp->value);
    ft_lstadd_back_mod(something, new);
}

// добавление нового элемента в список - только key
void add_new_elem_key(t_env *ex_l_head, char *str)
{ 
/* СТАРАЯ ВЕРСИЯ
    t_env *new; // создаем новый
    char *b;
    b = copy_char(str);
    new = (t_env *)malloc(sizeof(t_env));
    new->key = b;
    new->value = NULL;
    new->num = 0; // её забыл, в ней могла быть вся проблема
    new->next = NULL;
    while (ex_l_head)
	{
		if (!ex_l_head->next)
			break;
		ex_l_head = ex_l_head->next;
	}
	ex_l_head->next = new;
*/

// НОВАЯ ВЕРСИЯ
    t_env *new;
    new = ft_lstnew_mod_two(str);
    ft_lstadd_back_mod(ex_l_head, new);
}

char *copy_char_two(char *a, int j)
{
    char *b;
    int i;

    if (j == 0)
        i = ft_strlen(a);
    else 
        i = j;
    b = malloc(sizeof(char) * (i + 1));
    if (b == NULL)
        return (NULL);

    j = 0;
    while(i > j)
    {
        b[j] = a[j];
        j++;
    }
    b[i] = '\0';
    return (b);
}

char *copy_char(char *a)
{
    char *b;
    int i;
    
    i = ft_strlen(a);
    b = malloc(sizeof(char) * (i + 1));
    if (b == NULL)
        return (NULL);
    i = 0;
    while(a[i])
    {
        b[i] = a[i];
        i++;
    }

// del
    // b[i] = '!';
    // i++;

    b[i]= '\0';
    return (b);
}

int	ft_strncmp_mod(const char *s1, const char *s2, size_t n) 
{
	size_t	i;

	i = 0;
// printf("%zu %zu\n", n, i);
	while (s1[i] && s2[i]) // && n > i
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (0);
		i++;
	}
// printf("%zu %zu\n", n, i);
    i = ft_strlen(s2);
	if (n != i)
		return (0);
	return (1);
}
