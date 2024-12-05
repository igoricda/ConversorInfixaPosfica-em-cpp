// stack.h
#ifndef STACK_H
#define STACK_H

#include <string>

typedef std::string tipo;

class node {
public:
    node();
    node(tipo dado, node* ptr = NULL);
    tipo dado;
    node* prox;
};

class lista {
public:
    lista();
    int isEmpty();
    void addToHead(tipo dado);
    void addToTail(tipo dado);
    void printList();
    void deleteFromHead();
    void deleteFromTail();
    tipo front();
private:
    node* head;
    node* tail;
};

class stack {
public:
    stack();
    int size();
    bool empty();
    tipo top();
    void push(tipo dado);
    void pop();
    void imprime();
    void readstr();
    bool verifyinp();
    void conversao();
    bool checkprio(char a, char b);
    int avalposf();
private:
    lista pilha;
    int n;
    std::string infixa;
    std::string posfixa;
};

#endif // STACK_H
