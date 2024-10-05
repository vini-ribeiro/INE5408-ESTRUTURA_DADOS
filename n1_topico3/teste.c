#include <stdio.h>

void primeira_funcao(void);
void segunda_funcao(void);
void terceira_funcao(void);

int main(void){
	primeira_funcao();
	segunda_funcao();
	terceira_funcao();

	return 0;
}

void primeira_funcao(void) {
	printf("%s", "primeira funcao");
}

void segunda_funcao(void) {
	printf("%s", "segunda funcao");
}

void terceira_funcao(void) {
	printf("%s", "terceira funcao");
}

