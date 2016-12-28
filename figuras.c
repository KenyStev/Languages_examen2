#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RECTANGULO sizeof(int) + sizeof(int)
#define CIRCULO sizeof(int) + sizeof(int)

#define BASE_OFFSET sizeof(void*)
#define ALTURA_OFFSET BASE_OFFSET + sizeof(int)

#define RADIO_OFFSET sizeof(void*)

//vtables
char rectangulo_vtable[sizeof(void*)*3];
char circulo_vtable[sizeof(void*)*3];

//constructores
void rectangulo_ctor(char* this, int base, int altura) {
	*((void**)this) = rectangulo_vtable;
	*((int*)(this + BASE_OFFSET)) = base;
	*((int*)(this + ALTURA_OFFSET)) = altura;
}

void circulo_ctor(char* this, int radio) {
	*((void**)this) = circulo_vtable;
	*((int*)(this + RADIO_OFFSET)) = radio;
}

//perimetro
int rectangulo_getPerimetro(char *this) {
	int base = *((int*)(this + BASE_OFFSET));
	int altura = *((int*)(this + ALTURA_OFFSET));
	// printf("\tBase: %d Altura: %d ", base,altura);
	return 2*(base + altura);
}

int circulo_getPerimetro(char *this) {
	int radio = *((int*)(this + RADIO_OFFSET));
	// printf("\tRadio: %d ",radio);
	return 2*3.141692*radio;
}

//area
int rectangulo_getArea(char *this) {
	int base = *((int*)(this + BASE_OFFSET));
	int altura = *((int*)(this + ALTURA_OFFSET));
	// printf("\tBase: %d Altura: %d ", base,altura);
	return base*altura;
}

int circulo_getArea(char *this) {
	int radio = *((int*)(this + RADIO_OFFSET));
	// printf("\tRadio: %d ",radio);
	return 3.141692*radio*radio;
}

//prints
void rectangulo_print(char *this) {
	int base = *((int*)(this + BASE_OFFSET));
	int altura = *((int*)(this + ALTURA_OFFSET));
	printf("\tBase: %d Altura: %d ", base,altura);

	void* vtable = *((void**)this);
	int (*getArea)();
	int (*getPerimetro)();
	getArea = *((void**)vtable);
	getPerimetro = *((void**)(vtable + sizeof(void*)));

	printf("\tPerimetro: %d Area: %d ",getPerimetro(this) ,getArea(this));
}

void circulo_print(char *this) {
	int radio = *((int*)(this + RADIO_OFFSET));
	printf("\tRadio: %d ",radio);

	void* vtable = *((void**)this);
	int (*getArea)();
	int (*getPerimetro)();
	getArea = *((void**)vtable);
	getPerimetro = *((void**)(vtable + sizeof(void*)));

	printf("\tPerimetro: %d Area: %d ",getPerimetro(this) ,getArea(this));
}

void setup_vtable() {
	*((void**)rectangulo_vtable) = &rectangulo_getArea;
	*(((void**)rectangulo_vtable)+1) = &rectangulo_getPerimetro;
	*(((void**)rectangulo_vtable)+2) = &rectangulo_print;

	*((void**)circulo_vtable) = &circulo_getArea;
	*(((void**)circulo_vtable)+1) = &circulo_getPerimetro;
	*(((void**)circulo_vtable)+2) = &circulo_print;
}

void figura_print(char *figura) {
	void* vtable = *((void**)figura);
	void (*print)();
	print = *(((void**)vtable)+2);
	print(figura);
}

char r_data[sizeof(RECTANGULO)];

int main(int argc, char const *argv[])
{
	setup_vtable();

	char *figuras[3];

	rectangulo_ctor(&r_data, 10, 50);

	char* r_rect = malloc(RECTANGULO);
	rectangulo_ctor(r_rect, 5, 20);

	char c_circ[sizeof(CIRCULO)];
	circulo_ctor(&c_circ, 5);

	figuras[0] = &r_data;
	figuras[1] = r_rect;
	figuras[2] = &c_circ;

	int i;
	for(i = 0; i < 3; i++) {
		printf("%d ", i);
		figura_print(figuras[i]);
		printf("\n");
	}

	return 0;
}