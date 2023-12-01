#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* максимальное число строк */
#define MAXLEN 1000 /* максимальная длина строки */

char *line_ptr[MAXLINES]; /* указатели на строки */

int read_lines(char **line_ptr, int nlines);
void write_lines(char **line_ptr, int nlines);
void qsort(char **line_ptr, int left, int right);

/* сортировка строк */
int main()
{
    int count = read_lines(line_ptr, MAXLINES);
    qsort(line_ptr, 0, count - 1);
    write_lines(line_ptr, count);

    return 0;
}


char *alloc(int);
int get_line(char *, int);

int read_lines(char **line_ptr, int max_lines)
{
    int len = 0;
    int nlines = 0;
    char *p;
    char line[MAXLEN];

    nlines = 0;

    while ((len = get_line(line, MAXLEN)) > 0)
    {
        p = alloc(len);
        if (nlines >= max_lines || p == NULL)
        {
            return -1;
        }
        else 
        {
            line[len-1] = '\0'; /* убираем символ \n */
            strcpy(p, line);
            line_ptr[nlines++] = p;
        }
    }
    return nlines;
}


void swap(char **, int, int);

void qsort(char **v, int left, int right)
{
    int i, last;

    if (left >= right) /* ничего не делается, если в массиве */
    {
        return; /* менее двух элементов */
    }

    swap(v, left, (left+ right)/2);
    last = left;

    for (i = left+1; i <= right; i++)
    {
        if (strcmp(v[i], v[left]) < 0)
        {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}


void write_lines(char **line_ptr, int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
    {
        printf("%s\n", line_ptr[i]);
    }
}


#define MAX_BUFF_LEN 10000
char alloc_buff[MAX_BUFF_LEN];
char *alloc_lasr_ptr = alloc_buff;

char *alloc(int n)
{
    if (alloc_buff + MAX_BUFF_LEN - alloc_lasr_ptr >= n)
    {
        alloc_lasr_ptr += n;
        return alloc_lasr_ptr - n;
    }
    else
    {
        return NULL;
    }
}

int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void swap(char **v, int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}