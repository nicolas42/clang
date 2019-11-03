gcc -Wall -pedantic multivector.c && ./a.out

Other Implementations
https://rosettacode.org/wiki/Geometric_algebra

Links
https://marctenbosch.com/quaternions/
https://www.euclideanspace.com/maths/algebra/clifford/d3/arithmetic/index.htm


=== Array Version ===
Multivectors are implemented as 8 element arrays of doubles
So if 'a' was a multivector then a[0] a[1:3] a[4:6] a[7] 
would be the scalar, vector3, bivector3, and pseudo-scalar parts respectively.

Multivector Product Implementation

typedef struct {
	double e0, e1, e2, e3, e23, e31, e12, e123;
} Multivector;

c->e0 	= a.e0*b.e0 + a.e1*b.e1 + a.e2*b.e2 + a.e3*b.e3 - a.e23*b.e23 - a.e31*b.e31 - a.e12*b.e12 - a.e123*b.e123;
c->e1 	= a.e0*b.e1 + a.e1*b.e0 - a.e2*b.e12 + a.e12*b.e2 + a.e3*b.e31 - a.e31*b.e3 + a.e123*b.e23 + a.e23*b.e123;
c->e2 	= a.e0*b.e2 + a.e2*b.e0 + a.e1*b.e12 - a.e12*b.e1 - a.e3*b.e23 + a.e23*b.e3 - a.e123*b.e31 - a.e31*b.e123;
c->e3 	= a.e0*b.e3 + a.e3*b.e0 - a.e1*b.e31 + a.e31*b.e1 + a.e2*b.e23 - a.e23*b.e2 + a.e123*b.e12 + a.e12*b.e123;
c->e23 	= a.e23*b.e0 + a.e0*b.e23 + a.e2*b.e3 - a.e3*b.e2 + a.e12*b.e31 - a.e31*b.e12 + a.e123*b.e1 + a.e1*b.e123;
c->e31 	= a.e31*b.e0 + a.e0*b.e31 + a.e3*b.e1 - a.e1*b.e3 + a.e23*b.e12 - a.e12*b.e23 + a.e123*b.e2 + a.e2*b.e123;
c->e12 	= a.e12*b.e0 + a.e0*b.e12 + a.e1*b.e2 - a.e2*b.e1 + a.e31*b.e23 - a.e23*b.e31 + a.e123*b.e3 + a.e3*b.e123;
c->e123	= a.e0*b.e123 + a.e123*b.e0 + a.e1*b.e23 + a.e23*b.e1 + a.e2*b.e31 + a.e31*b.e2 + a.e3*b.e12 + a.e12*b.e3;
