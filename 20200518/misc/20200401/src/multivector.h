#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include <stdio.h>
#include <math.h>

typedef struct {
	double e0, x, y, z, yz, zy, xy, xyz;
} MULTIVECTOR;

// void multivector_init(MULTIVECTOR *a);
// void multivector_product(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b);
// void multivector_rotate(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b);
// void multivector_print(MULTIVECTOR v);
// void multivector_printv(MULTIVECTOR v);
// char* multivector_str(char* buf, MULTIVECTOR v);

/* https://stackoverflow.com/questions/4396140/why-doesnt-ansi-c-have-namespaces */


typedef struct {
	void (*init)(MULTIVECTOR *a);
	void (*product)(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b);
	void (*rotate)(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b);
	void (*print)(MULTIVECTOR v);
	void (*printv)(MULTIVECTOR v);
	char* (*str)(char* buf, MULTIVECTOR v);
}  LIB_MULTIVECTOR;

// void lib_multivector_init(LIB_MULTIVECTOR *a);

// extern const LIB_MULTIVECTOR lib_multivector;
extern const LIB_MULTIVECTOR multivector;

static void init(MULTIVECTOR *a){
	a->e0 = 0; a->x = 0; a->y = 0; a->z = 0; a->yz = 0; a->zy = 0; a->xy = 0; a->xyz = 0; 
}

static void product(MULTIVECTOR *c, MULTIVECTOR a, MULTIVECTOR b){
	c->e0 	= a.e0*b.e0 	+ a.x*b.x 	+ a.y*b.y 	+ a.z*b.z 	- a.yz*b.yz 	- a.zy*b.zy 	- a.xy*b.xy 	- a.xyz*b.xyz;
	c->x 	= a.e0*b.x 	+ a.x*b.e0 	- a.y*b.xy 	+ a.xy*b.y 	+ a.z*b.zy 	- a.zy*b.z 	- a.xyz*b.yz 	+ a.yz*b.xyz;
	c->y 	= a.e0*b.y 	+ a.y*b.e0 	+ a.x*b.xy 	- a.xy*b.x 	- a.z*b.yz 	+ a.yz*b.z 	- a.xyz*b.zy 	- a.zy*b.xyz;
	c->z 	= a.e0*b.z 	+ a.z*b.e0 	- a.x*b.zy 	+ a.zy*b.x 	+ a.y*b.yz 	- a.yz*b.y 	- a.xyz*b.xy 	- a.xy*b.xyz;
	c->yz 	= a.yz*b.e0 	+ a.e0*b.yz 	+ a.y*b.z 	- a.z*b.y 	+ a.xy*b.zy 	- a.zy*b.xy 	+ a.xyz*b.x 	+ a.x*b.xyz;
	c->zy 	= a.zy*b.e0 	+ a.e0*b.zy 	+ a.z*b.x 	- a.x*b.z 	+ a.yz*b.xy 	- a.xy*b.yz 	+ a.xyz*b.y 	+ a.y*b.xyz;
	c->xy 	= a.xy*b.e0 	+ a.e0*b.xy 	+ a.x*b.y 	- a.y*b.x 	+ a.zy*b.yz 	- a.yz*b.zy 	+ a.xyz*b.z 	+ a.z*b.xyz;
	c->xyz	= a.e0*b.xyz 	+ a.xyz*b.e0 	+ a.x*b.yz 	+ a.yz*b.x 	+ a.y*b.zy 	+ a.zy*b.y 	+ a.z*b.xy 	+ a.xy*b.z;
}

static void rotate(MULTIVECTOR *Rab, MULTIVECTOR v, MULTIVECTOR a, MULTIVECTOR b){

	MULTIVECTOR ab, ba, v2;
	init(&ab); init(&ba); init(&v2);

	product(&ab, a, b);
	product(&ba, b, a);
	product(&v2, v, ab);
	product(Rab, ba, v2);
}

static void print(MULTIVECTOR v){
	printf("[%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]\r\n", 
			v.e0, v.x, v.y, v.z, v.yz, v.zy, v.xy, v.xyz);	
}

static void printv(MULTIVECTOR v){
	printf("[%.2f %.2f %.2f]\r\n", v.x, v.y, v.z);	
}

static char* str(char* buf, MULTIVECTOR v){
	sprintf(buf, "[%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]\r\n", 
			v.e0, v.x, v.y, v.z, v.yz, v.zy, v.xy, v.xyz);	
			
	return buf;
}


const LIB_MULTIVECTOR multivector = {
	.init = init,
	.product = product,
	.rotate = rotate,
	.print = print,
	.printv = printv,
	.str = str
};

#endif
