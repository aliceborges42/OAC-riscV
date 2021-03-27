/*
 *  main.cpp
 *  RISCV
 *
 *  Created by Ricardo Jacobi on 26/01/11.
 *  Copyright 2011 Universidade de Brasilia. All rights reserved.
 *
 */

#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

#include "globals.h"
#include "memoria.hpp"
#include "riscv.hpp"

int main (int argc, const char * argv[]) {

    int n;
    init();     // inicia parametros globais

    load_mem("text.bin", 0);
    load_mem("data.bin", 0x2000);

    cout << "Numero de instrucoes a imprimir: ";
    cin >> n;
    for (int i=0; i < n; i++) {
        fetch();
        decode();
        execute();
        cout << "Instr = " << instr_str[instruction]
             <<  " Imm = " << imm32_t
             << " rs1 = " << rs1
             << " rs2 = " << rs2
             << " rd = " << rd
             << " breg[rd] = " << breg[rd]
             << endl;
    }

    int address;

    cout << "\nNumero de palavras a imprimir: ";
    cin >> n;
    cout << "\n\nEndereco inicial: ";
    cin >> address;
    for (int i=0; i < n; i++) {
        int end = (address>>2) + i;
        printf("mem[%d] = %x\n", end, mem[end]);
    }

    return 0;
}
