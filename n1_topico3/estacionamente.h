// Copyright [2024] Vinicius Henrique Ribeiro

/*
    *** Importante ***

    O código de fila em vetor está disponível internamente (não precisa de implementação aqui)

*/



void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    // ... COLOQUE SEU CÓDIGO AQUI ...
    for (int i = 0; i < k - 1; i++) {
        f->enqueue(f->dequeue());
    }
    f->dequeue();
}


void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    // ... COLOQUE SEU CÓDIGO AQUI ...
    int size = static_cast<int>(f->size());
    for (int i = 0; i < size; i++) {
        if (i == k - 1) {
            f->enqueue(f->dequeue());
        } else {
            f->dequeue();
        }
    }
}



/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
