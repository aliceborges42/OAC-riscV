
#OAC - 2020/2 - Trabalho Simulador RISC-V
Alice da Costa Borges
18/0011855


##Problema: 
Este trabalho consiste na implementação de um simulador da arquitetura RV32I em
linguagem de alto nível (C++). As funções básicas de busca e decodificação de
instruções são fornecidas. Foi implementado a função de execução (execute()) das
instruções para o subconjunto de instruções indicado. O programa binário a ser
executado deve ser gerado a partir do montador RARS, juntamente com os
respectivos dados. O simulador deve ler arquivos binários contendo o segmento de
código e o segmento de dados para sua memória e executá-lo. 

##Descrição:

execute():
A partir da instrução decodificado no decode(), (instruction), é realizado a verificação através de um switch case, nele é verificado qual insrução está sendo tratada, e com base nisso é realizada a simulação de execução da instrução.

I_add    ->    add t1,t2,t3        Addition: set t1 to (t2 plus t3)
I_addi   ->    addi t1,t2,-100     Addition immediate: set t1 to (t2 plus signed 12-bit immediate)
I_and    ->    and t1,t2,t3        Bitwise AND : Set t1 to bitwise AND of t2 and t3
I_andi   ->    andi t1,t2,-100     Bitwise AND immediate : Set t1 to bitwise AND of t2 and sign-extended 12-bit immediate 
I_auipc  ->    auipc t1,100000     Add upper immediate to pc: set t1 to (pc plus an upper 20-bit immediate)
I_beq    ->    beq t1,t2,label     Branch if equal : Branch to statement at label's address if t1 and t2 are equal	
I_bge    ->    bge t1,t2,label     Branch if greater than or equal: Branch to statement at label's address if t1 is greater than or equal to t2
I_bgeu   ->    bgeu t1,t2,label    Branch if greater than or equal to (unsigned): Branch to statement at label's address if t1 is greater than or equal to t2 (with an unsigned interpretation) 
I_blt    ->    blt t1,t2,label     Branch if less than: Branch to statement at label's address if t1 is less than t2
I_bltu   ->    bltu t1,t2,label    Branch if less than (unsigned): Branch to statement at label's address if t1 is less than t2 (with an unsigned interpretation)
I_bne    ->    bne t1,t2,label     Branch if not equal : Branch to statement at label's address if t1 and t2 are not equal
I_jal    ->    jal t1, target      Jump and link : Set t1 to Program Counter (return address) then jump to statement at target address	
I_jalr   ->    jalr t1, t2, -100   Jump and link register: Set t1 to Program Counter (return address) then jump to statement at t2 + immediate 
I_lb     ->    lb t1, -100(t2)     Set t1 to sign-extended 8-bit value from effective memory byte address	
I_lbu    ->    lbu t1, -100(t2)    Set t1 to zero-extended 8-bit value from effective memory byte address
I_lw     ->    lw t1, -100(t2)     Set t1 to contents of effective memory word address   
I_lui    ->    lui t1,100000       Load upper immediate: set t1 to 20-bit followed by 12 0s
I_sb     ->    sb t1, -100(t2)     Store byte : Store the low-order 8 bits of t1 into the effective memory byte address
I_sw     ->    sw t1, -100(t2)     Store word : Store contents of t1 into effective memory word address  
I_sll    ->    sll t1,t2,t3        Shift left logical: Set t1 to result of shifting t2 left by number of bits specified by value in low-order 5 bits of t3
I_slt    ->    slt t1,t2,t3        Set less than : If t2 is less than t3, then set t1 to 1 else set t1 to 0
I_slli   ->    slli t1,t2,10       Shift left logical : Set t1 to result of shifting t2 left by number of bits specified by immediate
I_sub    ->    sub t1,t2,t3        Subtraction: set t1 to (t2 minus t3)
I_slti   ->    slti t1,t2,-100     Set less than immediate : If t2 is less than sign-extended 12-bit immediate, then set t1 to 1 else set t1 to 0
I_sltiu  ->    sltiu t1,t2,-100    Set less than immediate unsigned : If t2 is less than  sign-extended 16-bit immediate using unsigned comparison, then set t1 to 1 else set t1 to 0
I_xor    ->    xor t1,t2,t3        Bitwise XOR : Set t1 to bitwise XOR of t2 and t3
I_or     ->    or t1,t2,t3         Bitwise OR : Set t1 to bitwise OR of t2 and t3
I_srli   ->    srli t1,t2,10       Shift right logical : Set t1 to result of shifting t2 right by number of bits specified by immediate
I_srai   ->    srai t1,t2,10       Shift right arithmetic : Set t1 to result of sign-extended shifting t2 right by number of bits specified by immediate
I_sltu   ->    sltu t1,t2,t3       Set less than : If t2 is less than t3 using unsigned comparision, then set t1 to 1 else set t1 to 0
I_ori    ->    ori t1,t2,-100      Bitwise OR immediate : Set t1 to bitwise OR of t2 and sign-extended 12-bit immediate
I_ecall  ->    ecall               Issue a system call : Execute the system call specified by value in a7
I_xori   ->    xori t1,t2,-100     Bitwise XOR immediate : Set t1 to bitwise XOR of t2 and sign-extended 12-bit immediate
I_nop    ->    nop                 NO OPeration




##memoria.cpp:
Foram implementadas as funções:

int32_t lb(uint32_t address, int32_t kte);
int32_t lw(uint32_t address, int32_t kte);
int32_t lbu(uint32_t address, int32_t kte);
void sb(uint32_t address, int32_t kte, int8_t dado);
void sw(uint32_t address, int32_t kte, int32_t dado); 


#Testes


##Teste 0:
arquivo de teste teste0.asm
--testa acesso a memoria

.data
w0:	.word 0x01F203F4
w1:	.word 0


.text
	li a7, 1
	la s0, w0
	lb a0, 0(s0)
	ecall			# imprime -12
	la s1, w1
	sb a0, 0(s1)
	lw a0, 0(s1)
	ecall			# imprime 244
	lbu a0, 0(s0)
	ecall			# imprime 244
	lb a0, 1(s0)
	ecall			# imprime 3
	lw a0, 0(s0)
	sw a0, 0(s1)
	lb a0, 3(s1)
	ecall			# imprime 1

##Resultado: 
Numero de instrucoes a imprimir: 20
Instr = ADDi Imm = 1 rs1 = 0 rs2 = 1 rd = 17 breg[rd] = 1
Instr = AUIPC Imm = 8192 rs1 = 0 rs2 = 0 rd = 8 breg[rd] = 8196
Instr = ADDi Imm = -4 rs1 = 8 rs2 = 28 rd = 8 breg[rd] = 8192
Instr = LB Imm = 0 rs1 = 8 rs2 = 0 rd = 10 breg[rd] = -12

-12
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = AUIPC Imm = 8192 rs1 = 0 rs2 = 0 rd = 9 breg[rd] = 8212
Instr = ADDi Imm = -16 rs1 = 9 rs2 = 16 rd = 9 breg[rd] = 8196
Instr = SB Imm = 0 rs1 = 9 rs2 = 10 rd = 0 breg[rd] = 0
Instr = LW Imm = 0 rs1 = 9 rs2 = 0 rd = 10 breg[rd] = 244

244
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = LBU Imm = 0 rs1 = 8 rs2 = 0 rd = 10 breg[rd] = 244

244
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = LB Imm = 1 rs1 = 8 rs2 = 1 rd = 10 breg[rd] = 3

3
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = LW Imm = 0 rs1 = 8 rs2 = 0 rd = 10 breg[rd] = 32637940
Instr = SW Imm = 0 rs1 = 9 rs2 = 10 rd = 0 breg[rd] = 0
Instr = LB Imm = 3 rs1 = 9 rs2 = 3 rd = 10 breg[rd] = 1

1
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instrucao Invalida (PC = 0000004c RI = 00000000)
Instr = NOP Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instrucao Invalida (PC = 00000050 RI = 00000000)
Instr = NOP Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0

Imprimiu o esperado, -12 244 244 3 1


##Teste 1:
arquivo de teste teste1.asm

Resultado:


Numero de instrucoes a imprimir: 20
Instr = ADDi Imm = 10 rs1 = 0 rs2 = 10 rd = 5 breg[rd] = 10
Instr = ADDi Imm = -5 rs1 = 0 rs2 = 27 rd = 6 breg[rd] = -5
Instr = ADDi Imm = 1 rs1 = 0 rs2 = 1 rd = 17 breg[rd] = 1
Instr = ADD Imm = 0 rs1 = 5 rs2 = 6 rd = 10 breg[rd] = 5

5
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = ADD Imm = 0 rs1 = 0 rs2 = 6 rd = 10 breg[rd] = -5

-5
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = ADD Imm = 0 rs1 = 5 rs2 = 6 rd = 6 breg[rd] = 5
Instr = AND Imm = 0 rs1 = 5 rs2 = 6 rd = 10 breg[rd] = 0

0
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = OR Imm = 0 rs1 = 5 rs2 = 6 rd = 10 breg[rd] = 15

15
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = ANDi Imm = 3 rs1 = 5 rs2 = 3 rd = 10 breg[rd] = 2

2
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = ORi Imm = 1 rs1 = 5 rs2 = 1 rd = 10 breg[rd] = 11

11
Instr = ECALL Imm = 0 rs1 = 0 rs2 = 0 rd = 0 breg[rd] = 0
Instr = SUB Imm = 0 rs1 = 5 rs2 = 6 rd = 10 breg[rd] = 5

Imprimiu o esperado, 5 -5 0 15 2 11.
