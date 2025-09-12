# Sistema de Fila para Barbearia – Programa em C

O sistema simula a fila de espera de uma barbearia, permitindo gerenciar clientes e serviços de forma simples.

---

## Funcionalidades
- Inserir clientes na fila informando **nome** e **tipo de corte**.
- Atender o próximo cliente na ordem de chegada.
- Exibir a quantidade de clientes aguardando.
- Encerrar o programa liberando toda a memória.

---

## Tecnologias
- Linguagem: **C**
- Compilador sugerido: `gcc` (C99 ou superior)

---

## Como compilar e executar
```bash
# Compilar
gcc -std=c99 -Wall -Wextra main.c -o fila_barbearia

# Executar
./fila_barbearia
