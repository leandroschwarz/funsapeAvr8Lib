// Conteúdo de memory_stubs.cpp

#include <stddef.h> // Define size_t, que é o tipo subjacente de unsigned int para o size

void operator delete(void *ptr, unsigned int size)
{
    // Esta função é necessária pelo linker (ld) para resolver a chamada
    // do destrutor virtual.
    // Já que a alocação de memória dinâmica de heap não está sendo utilizada,
    // o corpo da função é deixado vazio.

    if (ptr) {
        // Em uma implementação completa com heap, a função free() seria chamada aqui.
        // A omissão intencional é para otimizar o uso de memória Flash/RAM.
    }
}
