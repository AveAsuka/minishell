#include "minishell.h"

void export_alph_print(t_env *ex_l)
{
    t_env *head; // первый элемент
    head = ex_l;

    int j = ft_lstsize_mod(ex_l);
    int i = j;

// printf ("export_alph_print: \n");
printf("\n"); // ПОТОМ УДАЛИТЬ
    while(j > 0)
    {
        while (ex_l)
        {
            if (j == ex_l->num)
            {
                if (ex_l->value == NULL)
                    printf ("declare -x %s\n", ex_l->key);
                else
                    printf ("declare -x %s=\"%s\"\n", ex_l->key, ex_l->value);
                j--;
            }
            ex_l = ex_l->next;
        }

       
        ex_l = head;
    }

    if (ex_l->key)
        printf ("что-то есть = ");
    else
        printf ("ничего\n");

    if (ex_l->value)
        printf ("что-то есть_2\n");
    else   
         printf ("ничего_2\n");


printf("\nВсего = %d\n", i); // ПОТОМ УДАЛИТЬ
}

/* Настраиваем алфавит по key только - надо чтобы всё выкладывалось
поочередно, сначала: 
- английские большие, (с A - 65, по Z - 90);
- потом с "_", (95);
- потом английские маленькие (c a - 97, по z - 122).
Будем как-то применять таблицу ASCII, я полагаю. */
void export_alph_find(t_env *ex_l)
{
    int num; // текущий номер наибольшего
    num = 1;
    
    t_env *head; // первый элемент
    t_env *current;
    head = ex_l;
    current = ex_l;

    int j = ft_lstsize_mod(ex_l);

    while (ex_l)
    {
        ex_l->num = 0;
        ex_l = ex_l->next;
    }
    ex_l = head;

// Ебнем здесь двойной цикл, крутим до тех пор, пока всем не раздали номера
    while (j > 0)
    {
        while (ex_l)
        {
// printf("%c, %d and %c, %d\n", ex_l->key[0], ex_l->key[0] + '0', current->key[0], current->key[0] + '0');
            if (ex_l->key[0] > current->key[0] && ex_l->num == 0 && current->num == 0)
            {
                current = ex_l;
// printf("current = %c, %d\n", current->key[0], current->key[0] + '0');
            }
            ex_l = ex_l->next;
        }
        
        current->num = num;
// printf("current = %s, %d, num = %d\n", current->key, current->key[0] + '0', current->num);
        num++;
        j--;

        ex_l = head; // возращаемся к первому элементу
        while (ex_l)
        {
            if(ex_l->num == 0)
            {
                current = ex_l; // ?
                break;
            }
            ex_l = ex_l->next;
        }
    }
    ex_l = head;
    export_alph_print(ex_l); // тут уже будем распечатывать что получится
}
