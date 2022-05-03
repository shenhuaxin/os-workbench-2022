#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <ctype.h>

// struct procInf addPNode(struct node root, struct procInf info)
// {
//     struct node pnode;
//     if ((pnode = findPNode(root, info.ppid)) == NULL)
//     {
//         addPNode(root, info.ppid);
//     }
//     else
//     {
//         pnode.child[pnode.len].pid = info.pid;
//         pnode.child[pnode.len].name = info.name;
//     }
// };
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

struct node *findPNode(struct node *root, int pid)
{
    return root;
}

struct node *addNode(struct node *root, struct procInf info, struct procInf procArray[])
{
    struct node *pnode;
    if ((pnode = findPNode(root, info.ppid)) -> name == NULL)
    {
        addNode(root, procArray[info.ppid], procArray);
    }
    else
    {
        struct node newnode;
        newnode.pid = info.pid;
        newnode.name = info.name;
        newnode.len = 0;

        pnode -> child = malloc(sizeof(struct node *) * 1000);
        pnode -> child[pnode -> len++] = &newnode;
    }
    
}

int main(int argc, char const *argv[])
{
    struct procInf procArray[2];
    procArray[0].name = "root";
    procArray[0].pid = 0;
    procArray[0].ppid = 0;
    
    procArray[1].name = "systemd";
    procArray[1].pid = 1;
    procArray[1].ppid = 0;


    struct node root;
    root.pid = 0;
    root.name = "root";
    root.len = 0;

    addNode(&root, procArray[1], procArray);

    return 0;
}

// int main(int argc, char const *argv[])
// {
//     struct node root;
//     root.pid = 0;
//     root.name = "root";
//     root.len = 0;
//     struct node systemd;
//     systemd.pid = 2;
//     systemd.name = "xxx";
//     systemd.len = 0;

//     root.child = malloc(sizeof(struct node *) * 10);
//     root.child[root.len++] = &systemd;
//     printf("yyds");
//     return 0;
// }
