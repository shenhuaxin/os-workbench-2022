#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

struct node
{
    int pid;
    char *name;
    int len;
    struct node **child;
} Node;

struct procInf
{
    char *name;
    int pid;
    int ppid;
} ProcInf;

char *readline(FILE *flie)
{

    char *line = (char *)calloc(1, sizeof(char));
    char c;
    int len = 0;
    while ((c = fgetc(flie)) != EOF && c != '\n')
    {
        line = realloc(line, sizeof(char) * (len + 2));
        line[len++] = c;
        line[len] = '\0';
    }
    return line;
}

char *getName(char *name)
{
    char *realName = (char *)calloc(1, sizeof(char *));
    int meetFlag = 0;
    int i = 0;
    int len = 0;
    char c;
    while ((c = name[i++]) != '\0')
    {
        if (!meetFlag)
        {
            if (c == ':')
            {
                meetFlag = 1;
            }
            continue;
        }
        if (meetFlag && c == '\t')
        {
            continue;
        }
        realName = realloc(realName, sizeof(char) * (len + 2));
        realName[len++] = c;
        realName[len] = '\0';
    }
    return realName;
}

struct node *findPNode(struct node *root, int pid)
{
    if (root->pid == pid)
    {
        return root;
    }
    for (int i = 0; i < root->len; i++)
    {
        struct node *pnode = findPNode(root->child[i], pid);
        if (pnode != NULL)
        {
            return pnode;
        }
    }
    return NULL;
}

struct node *addNode(struct node *root, struct procInf info, struct procInf procArray[])
{
    struct node *pnode;
    if ((pnode = findPNode(root, info.ppid))->name == NULL)
    {
        addNode(root, procArray[info.ppid], procArray);
    }

    struct node *newnode = malloc(sizeof(struct node *));
    newnode->pid = info.pid;
    newnode->name = info.name;
    newnode->len = 0;

    if (pnode->len == 0)
    {
        pnode->child = malloc(sizeof(struct node *) * 1000);
    }

    pnode->child[pnode->len] = newnode;
    pnode->len = pnode->len + 1;
}

void printfTree(struct node *root, char *prefix, char* end)
{
    printf("%s%s%s(%d)\n", prefix, end ,root->name, root->pid);
    for (int i = 0; i < root->len; i++)
    {
        char *name = (char *) malloc(strlen(prefix) + strlen("   "));
        sprintf(name, "%s%s", "   ", prefix);

        printfTree(root->child[i], name, "+--");
    }
}

int main(int argc, char *argv[])
{
    FILE *stream = popen("ls /proc/", "r");

    char *line;
    int count = 0;

    int size = 100;
    char **array = malloc(sizeof(char *) * size);
    while (strcmp((line = readline(stream)), "") != 0)
    {
        if (!isdigit(*line))
        {
            continue;
        }
        if (count >= size)
        {
            size = size * 2;
            char **array_new = malloc(sizeof(char *) * size);
            for (int i = 0; i < count; i++)
            {
                array_new[i] = array[i];
            }
            array = array_new;
        }

        array[count++] = line;
    }

    char *name = malloc(sizeof(char *));
    char *ppid = malloc(sizeof(char *));
    struct procInf procArray[100000];
    for (int i = 0; i < 100000; i++)
    {
        procArray[i].name = NULL;
        procArray[i].ppid = 0;
        procArray[i].pid = 0;
    }
    for (int i = 0; i < count; i++)
    {
        char *path = malloc(sizeof(char *));
        sprintf(path, "/proc/%s/status", array[i]);

        FILE *fp = fopen(path, "r");
        if (!fp)
        {
            printf("文件不存在： %s \n", path);
            continue;
        }
        name = readline(fp);
        readline(fp);
        readline(fp);
        readline(fp);
        readline(fp);
        readline(fp);
        ppid = readline(fp);
        int pid_i = atoi(array[i]);
        int ppid_i = atoi(getName(ppid));

        procArray[pid_i].pid = pid_i;
        procArray[pid_i].ppid = ppid_i;
        procArray[pid_i].name = getName(name);
    }

    struct node *root = malloc(sizeof(struct node *));
    root->pid = 0;
    root->name = "root";
    root->len = 0;

    for (int i = 0; i < 65536; i++)
    {
        if (procArray[i].name == NULL)
        {
            continue;
        }
        addNode(root, procArray[i], procArray);
    }

    printfTree(root, "", "");
}