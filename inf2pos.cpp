//Igor Correa Domingues de Almeida
//Linha de compilação:
// g++ -o polonia inf2pos.cpp stack.cpp; ./polonia
// Os metodos adicionados para a conversao estao neste arquivo

#include "stack.h"
#include <iostream>
#include <cmath>


void stack::readstr() {
    std::string str;
    getline(std::cin, str);
    infixa = "";

    for (char c : str) {
        if (c != ' ') {
            infixa += c;
        }
    }
}

bool stack::verifyinp() {
    short parent = 0;
    unsigned len = infixa.length();

    if (!(infixa[0] >= '0' && infixa[0] <= '9') && infixa[0] != '(') {
        std::cout << "String inválida, primeiro caractere inválido" << std::endl << "\nTECLE [ENTER]\n";
        std::cin.get();
        return false;
    }
    if (!(infixa[len - 1] >= '0' && infixa[len - 1] <= '9') && infixa[len - 1] != ')') {
        std::cout << "String inválida, último caractere inválido" << std::endl << "\nTECLE [ENTER]\n";
        std::cin.get();
        return false;
    }
    for (unsigned i = 0; i < len; ++i) {
        if (infixa[i] == '(') {
            parent++;
        } else if (infixa[i] == ')') {
            parent--;
        }
        if (parent < 0) {
            std::cout << "String inválida, parênteses fechados de forma errada" << std::endl << "\nTECLE [ENTER]\n";
            std::cin.get();
            return false;
        }

        if (infixa[i] == '*' || infixa[i] == '/' || infixa[i] == '+' || infixa[i] == '-' || infixa[i] == '^') {
            if (i + 1 < len && (infixa[i + 1] == '*' || infixa[i + 1] == '/' || infixa[i + 1] == '+' || infixa[i + 1] == '-' || infixa[i + 1] == '^' || infixa[i + 1] == ')')) {
                std::cout << "String inválida, sequência inválida de operandos" << std::endl;
                std::cout << "\nTECLE [ENTER]\n";
                std::cin.get();
                return false;
            }
        }

        if (infixa[i] == '(') {
            if (i + 1 < len && (infixa[i + 1] == '*' || infixa[i + 1] == '/' || infixa[i + 1] == '+' || infixa[i + 1] == '-' || infixa[i + 1] == '^')) {
                std::cout << "String inválida, sequência inválida de operandos" << std::endl;
                std::cout << "\nTECLE [ENTER]\n";
                std::cin.get();
                return false;
            }
        }
    }

    if (parent == 0) {
        return true;
    } else {
        std::cout << "String inválida, algum parêntese não foi fechado" << std::endl;
        std::cout << "\nTECLE [ENTER]\n";
        std::cin.get();
        return false;
    }
}

bool stack::checkprio(char a, char b) {
    int _a = 0, _b = 0;

    if (a == '-' || a == '+') {
        _a = 1;
    } else if (a == '*' || a == '/') {
        _a = 2;
    }

    if (b == '-' || b == '+') {
        _b = 1;
    } else if (b == '*' || b == '/') {
        _b = 2;
    }

    return (_a <= _b);
}

void stack::conversao() {
    std::string virtualstr;
    posfixa = "";

    for (unsigned i = 0; i < infixa.length(); ++i) {
        if (infixa[i] >= '0' && infixa[i] <= '9') {
            posfixa += infixa[i];
            if (i + 1 >= infixa.length() || !(infixa[i + 1] >= '0' && infixa[i + 1] <= '9')) {
                posfixa += ' ';
            }
        } else if (infixa[i] == '(' || infixa[i] == '^') {
            virtualstr = infixa[i];
            push(virtualstr);
        } else if (infixa[i] == ')') {
            while (!empty() && top()[0] != '(') {
                posfixa += top();
                posfixa += ' ';
                pop();
            }
            if (!empty()) {
                pop(); // Remove '('
            }
        } else {
            while (!empty() && checkprio(infixa[i], top()[0]) && top()[0] != '(') {
                posfixa += top();
                posfixa += ' ';
                pop();
            }
            virtualstr = infixa[i];
            push(virtualstr);
        }
    }
    while (!empty()) {
        posfixa += top();
        pop();
    }
    std::cout << posfixa << std::endl;
}

int stack::avalposf() {
    int aux1 = 0, aux2 = 0, result;

    for (unsigned i = 0; i < posfixa.length(); ++i) {
        if (posfixa[i] == ' ') {
            continue;
        } else if (posfixa[i] >= '0' && posfixa[i] <= '9') {
            std::string virtualstring = "";
            while (i < posfixa.length() && posfixa[i] != ' ') {
                virtualstring += posfixa[i];
                ++i;
            }
            push(virtualstring);
        } else {
            aux1 = std::stoi(top());
            pop();
            aux2 = std::stoi(top());
            pop();
            switch (posfixa[i]) {
                case '+':
                    result = aux2 + aux1;
                    break;
                case '-':
                    result = aux2 - aux1;
                    break;
                case '*':
                    result = aux2 * aux1;
                    break;
                case '/':
                    result = aux2 / aux1;
                    break;
                case '^':
                    result = std::pow(aux2, aux1);
                    break;
                default:
                    result = 0;
                    break;
            }
            push(std::to_string(result));
        }
    }
    return std::stoi(top());
}


int main() {
    stack p;
    p.readstr();
    if (p.verifyinp()) {
        p.conversao();
        std::cout << p.avalposf() << std::endl;
    }
    return 0;
}
