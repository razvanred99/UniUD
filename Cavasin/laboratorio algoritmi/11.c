#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct sHeap {
  int *v;
  unsigned int size, heapSize;
} Heap;

void printArray(int v[], unsigned int size) {
  printf("{");
  for(unsigned int i= 0; i < size; i++) {
    printf(" %d", v[i]);
  }
  puts(" }");
}

generateArray(int **v, unsigned int *size) {
  *size= rand() % 50 + 1;
  free(*v);
  *v= malloc(sizeof(int) * *size);
  for(unsigned int i= 0; i < *size; i++) {
    (*v)[i]= rand() % 201 - 100;
  }
}

int *copyArray(int **t, int v[], unsigned int size) {
  free(*t);
  *t= malloc(sizeof(int) * size);
  memcpy(*t, v, sizeof(int) * size);
  return *t;
}

void swap(int v[], unsigned int i, unsigned int j) {
  if(i != j) {
    v[i]^= v[j];
    v[j]= v[i] ^ v[j];
    v[i]^= v[j];
  }
}

unsigned int heapLeft(unsigned int i) {
  return 2 * (i + 1) - 1;
}

unsigned int heapRight(unsigned int i) {
  return 2 * (i + 1);
}

unsigned int heapParent(unsigned int i) {
  return i / 2;
}

unsigned int heapDepth(Heap h) {
  unsigned int i= 0;
  while(h.heapSize>>= 1)
    i++;
  return i;
}

void heapify(Heap h, unsigned int i) {
  unsigned int l= heapLeft(i), r= heapRight(i), n;
  if(l >= h.heapSize)
    l= i;
  if(r >= h.heapSize)
    r= i;
  if(h.v[l] > h.v[r])
    n= l;
  else
    n= r;
  if(h.v[i] > h.v[n])
    n= i;
  if(i != n) {
    swap(h.v, i, n);
    heapify(h, n);
  }
}

Heap generateHeap(int v[], unsigned int size) {
  Heap h;
  h.size= size;
  if(v) {
    h.heapSize= size;
    h.v= v;
    for(unsigned int i= h.heapSize / 2; i > 0; i--) {
      heapify(h, i - 1);
    }
  } else {
    h.heapSize= 0;
    h.v= malloc(size * sizeof(int));
  }
  return h;
}

int pop(Heap *h) {
  if(h->heapSize > 0) {
    h->heapSize--;
    swap(h->v, 0, h->heapSize);
    heapify(*h, 0);
    return h->v[h->heapSize];
  } else
    return 0;
}

void push(Heap *h, int n) {
  if(h->heapSize < h->size) {
    h->v[h->heapSize]= n;
    for(unsigned int i= h->heapSize; i > 0 && h->v[i] > h->v[heapParent(i)];) {
      swap(h->v, i, heapParent(i));
      i= heapParent(i);
    }
    h->heapSize++;
  }
}

void heapSort(int v[], unsigned int size) {
  Heap h= generateHeap(v, size);
  for(unsigned int i= size - 1; i > 0; i--) {
    v[i]= pop(&h);
  }
}

void printHeapRec(Heap h, unsigned int i, bool b[], unsigned int bSize) {
  unsigned int t;

  t= heapRight(i);
  if(t < h.heapSize) {
    for(unsigned int j= 0; j < bSize; j++) {
      b[j] ? printf("│   ") : printf("    ");
    }
    printf("├── %d\n", h.v[t]);
    b[bSize]= 1;
    printHeapRec(h, t, b, bSize + 1);
  }
  t= heapLeft(i);
  if(t < h.heapSize) {
    for(unsigned int j= 0; j < bSize; j++) {
      b[j] ? printf("│   ") : printf("    ");
    }
    printf("└── %d\n", h.v[t]);
    b[bSize]= 0;
    printHeapRec(h, t, b, bSize + 1);
  }
}

void printHeap(Heap h) {
  if(h.heapSize > 0) {
    unsigned int cp= GetConsoleCP();
    bool *b= calloc(heapDepth(h), sizeof(bool));
    printf("%d\n", h.v[0]);
    SetConsoleOutputCP(65001);
    printHeapRec(h, 0, b, 0);
    SetConsoleOutputCP(cp);
    free(b);
  }
}

void test1() {
  unsigned int size= rand() % 50 + 1;
  Heap h= generateHeap(NULL, size);

  puts("HEAP-BASED PRIORITY QUEUE");

  for(unsigned int i= 0; i < size; i++) {
    int n= rand() % 201 - 100;
    printf("add(%d)\n", n);
    push(&h, n);
    printHeap(h);
    putchar('\n');
  }
  for(unsigned int i= 0; i < size; i++) {
    printf("remove(): %d\n", pop(&h));
    printHeap(h);
    putchar('\n');
  }

  puts("\n---------------");
}

void test2() {
  int *a= NULL, *b= NULL;
  unsigned int size;

  puts("HEAP SORT");

  generateArray(&a, &size);
  printArray(a, size);

  copyArray(&b, a, size);
  heapSort(b, size);
  printArray(b, size);

  free(a);
  free(b);
  puts("\n---------------");
}

int main() {
  time_t vtime;
  srand((unsigned)time(&vtime));

  while(1) {
    test1();
    test2();

    getch();
  }

  return 0;
}