#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* максимальное число строк */
#define MAXLEN 1000 /* максимальная длина строки */
#define MAXBUFFERLEN 100000

char *line_ptr[MAXLINES]; /* указатели на строки */

int read_lines(char **line_ptr, int nlines, char *buffer);
void write_lines(char **line_ptr, int nlines);
void qsort(char **line_ptr, int left, int right);


int main()
{
    char buffer[MAXBUFFERLEN];

    int count = read_lines(line_ptr, MAXLINES, buffer);
    qsort(line_ptr, 0, count - 1);
    write_lines(line_ptr, count);

    return 0;
}


int get_line(char *, int);
void copy_str(char *from, char *to);

int read_lines(char **line_ptr, int max_lines, char *buffer)
{
    int len = 0;
    int nlines = 0;
    char line[MAXLEN];
    char *p;

    nlines = 0;

    int j = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
    {
        if (nlines >= max_lines)
        {
            return -1;
        }
        else 
        {
            copy_str(&buffer[j], line);
            line_ptr[nlines++] = &buffer[j];
            j += (len + 1);
        }
    }
    return nlines;
}


void swap(char **, int, int);

void qsort(char **v, int left, int right)
{
    int i, last;

    if (left >= right)
    {
        return;
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


int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
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

void copy_str(char *to, char *from)
{
    while(*to++ = *from++);
}