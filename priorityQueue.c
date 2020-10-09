#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int *data;
    int last_index;
} heap_t;

///////////////////////////

void bfs();

heap_t *init_heap(int m) 
{
    heap_t *new_heap = (heap_t *)malloc(sizeof(heap_t));
    new_heap->data = (int *)malloc(sizeof(int)*(m+1));
    new_heap->last_index = 0;
    new_heap->data[0] = 1000000;
    return new_heap;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insert(heap_t *max_heap, int data)
{
    //printf("===INSERT===\n");
    int parent, input; 
    max_heap->data[max_heap->last_index+1] = data;
    max_heap->last_index += 1;
    //printf("max_heap: %d\n", max_heap->data[max_heap->last_index]);
    //printf("last index: %d\n", max_heap->last_index);
    input = max_heap->last_index;
    parent = input/2;
    //printf("input: %d parent: %d\n", input, parent);

    if (max_heap->last_index == 1)
        return ;
    while (max_heap->data[input] > max_heap->data[parent])
    {
        if (parent == 0)
            break;
        //printf("%d %d\n", max_heap->data[input], max_heap->data[parent]);
        swap(&max_heap->data[input], &max_heap->data[parent]);
        input = parent;
        parent = parent/2;
    }
    //bfs(max_heap);
}

void delete_max(heap_t *max_heap)
{
    //printf("===Delete_Max===\n");
    int delete, child;
    max_heap->data[1] = max_heap->data[max_heap->last_index];
    max_heap->data[max_heap->last_index] = 0;
    max_heap->last_index--;
    delete = 1;
    child = 2*delete;

    while (max_heap->data[delete] < max_heap->data[child] || max_heap->data[delete] < max_heap->data[child+1])
    {
        if (child > max_heap->last_index)
            break;
        if (max_heap->data[child] > max_heap->data[child+1])
        {
            //printf("del: %d chd: %d\n", max_heap->data[delete], max_heap->data[child]);
            swap(&max_heap->data[delete], &max_heap->data[child]);
            delete = child;
            child = 2*child;
        }
        else
        {
            printf("del: %d chd+1: %d\n", max_heap->data[delete], max_heap->data[child+1]);
            swap(&max_heap->data[delete], &max_heap->data[child+1]);
            delete = child+1;
            child = 2*(child+1);
        }
    }
    bfs(max_heap);
}

int find_max(heap_t *max_heap)
{
    if (max_heap->last_index == 0)
        return -1;
    else
        return max_heap->data[1];
}

void update_key(heap_t *max_heap, int old_key, int new_key) 
{
    int i, index, child, parent;
    for (i=1; i<max_heap->last_index+1; i++)
    {
        if (max_heap->data[i] == old_key)
        {
            max_heap->data[i] = new_key;
            index = i;
            break;
        }
    }
    parent = index/2;
    child = 2*index;


    while (max_heap->data[index] < max_heap->data[child] || max_heap->data[index]  < max_heap->data[child+1]) //chk both of child
    {
        if (child > max_heap->last_index)
            break;
        if (max_heap->data[child] > max_heap->data[child+1])
        {
            swap(&max_heap->data[index], &max_heap->data[child]);
            index = child;
            child = child*2;
        }
        else
        {
            swap(&max_heap->data[index], &max_heap->data[child+1]);
            index = child+1;
            child = (child+1)*2;
        }
    }

    while (max_heap->data[index] > max_heap->data[parent]) // chk parent
    {
        if (parent == 0)
            break;
        swap(&max_heap->data[index], &max_heap->data[parent]);
        index = parent;
        parent = parent/2;
    }
}

void bfs (heap_t *max_heap)
{
    int i;
    for (i=1; i<max_heap->last_index+1; i++)
    {
        printf("%d ", max_heap->data[i]);
    }
    printf("\n");
}
///////////////////////////

int main(void) {
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;

    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                insert(max_heap, data);
                break;
            case 2:
                delete_max(max_heap);
                break;
            case 3:
                printf("%d\n", find_max(max_heap));
                break;
            case 4:
                scanf("%d %d", &old_key, &new_key);
                update_key(max_heap, old_key, new_key);
                break;
            case 5:
                bfs(max_heap);
                break;
        }
    }
    return 0;
}
