// stack.cpp
#include "stack.h"
#include <iostream>
#include <cmath>

// node class methods
node::node() : dado(""), prox(NULL) {}

node::node(tipo dado, node* ptr) : dado(dado), prox(ptr) {}

// lista class methods
lista::lista() : head(NULL), tail(NULL) {}

tipo lista::front() {
    return head->dado;
}

int lista::isEmpty() {
    return head == NULL;
}

void lista::addToHead(tipo dado) {
    head = new node(dado, head);
    if (isEmpty()) {
        tail = head;
    }
}

void lista::addToTail(tipo dado) {
    if (isEmpty()) {
        head = tail = new node(dado);
    } else {
        tail->prox = new node(dado);
        tail = tail->prox;
    }
}

void lista::printList() {
    for (node* tmp = head; tmp != NULL; tmp = tmp->prox) {
        if (tmp->prox) {
            std::cout << "[" << tmp->dado << "]->";
        } else {
            std::cout << "[" << tmp->dado << "]\n";
        }
    }
}

void lista::deleteFromHead() {
    if (isEmpty()) {
        std::cout << "Lista Vazia\n";
    } else {
        node* tmp = head;
        if (head == tail) {
            head = tail = NULL;
        } else {
            head = head->prox;
        }
        delete tmp;
    }
}

void lista::deleteFromTail() {
    if (isEmpty()) {
        std::cout << "Lista Vazia\n";
    } else {
        if (head == tail) {
            head = tail = NULL;
        } else {
            node* tmp = head;
            while (tmp->prox != tail) {
                tmp = tmp->prox;
            }
            tail = tmp;
            delete tail->prox;
            tail->prox = NULL;
        }
    }
}

// stack class methods
stack::stack() : pilha(), n(0) {}

int stack::size() {
    return n;
}

bool stack::empty() {
    return n == 0;
}

tipo stack::top() {
    if (empty()) {
        std::cout << "Pilha Vazia\n";
        return "";
    } else {
        return pilha.front();
    }
}

void stack::push(tipo dado) {
    ++n;
    pilha.addToHead(dado);
}

void stack::pop() {
    if (empty()) {
        std::cout << "Pilha já está vazia\n";
    } else {
        pilha.deleteFromHead();
        --n;
    }
}

void stack::imprime() {
    pilha.printList();
}
