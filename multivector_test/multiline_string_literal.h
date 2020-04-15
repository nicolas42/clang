// example of how to include multiline string literals in c

static char multiline_string_literal[] = "#define T 6.28318530718 \n\
 \n\
arena = malloc(arena_capacity * sizeof(multivector_t)); \n\
 \n\
multivector_t v = vector(1,0,0); \n\
multivector_t a = vector(1,0,0); \n\
multivector_t b = vector(1/sqrt(2),1/sqrt(2),0); \n\
// multivector_t c; \n\
multivector_t r; \n\
multivector_t spinor; \n\
 \n\
// length \n\
a = vector(1,1,0); \n\
r = mul(2,a,a); \n\
print_scalar(r); \n\
 \n\
r = mul(2, vector_spherical(1, T/multivector_length, T/4),vector_spherical(1, T/multivector_length, T/4)); \n\
print_scalar(r); \n\
 \n\
// area \n\
r = mul(2, vector(1,0,0), vector(0,1,0)); \n\
print_bivector(r); \n\
 \n\
r = mul(2, vector_spherical(1,T/multivector_length, T/4), vector_spherical(1,3*T/multivector_length, T/4)); \n\
print_bivector(r); \n\
 \n\
// volume \n\
r = mul(3, vector(1,0,0), vector(0,1,0), vector(0,0,1)); \n\
print_trivector(r); \n\
 \n\
r = mul(3, vector_spherical(1, T/multivector_length, T/4), vector_spherical(1, 3*T/multivector_length, T/4), vector(0,0,1)); \n\
print_trivector(r); \n\
 \n\
// 2D rotation (complex numbers) \n\
r = mul(2, vector(1,0,0), bivector(1,0,0));  \n\
print(r); \n\
 \n\
spinor = mul(2, vector(1,0,0), vector_spherical(1, T/12, T/4)); \n\
r = mul(2, vector(1,0,0), spinor); \n\
print(r); \n\
 \n\
 \n\
// 3D rotation (multiply v by twice the angle between a and b) \n\
v = vector(1,0,0); \n\
a = vector_spherical(1, T/multivector_length, T/4); \n\
b = vector_spherical(1, T/multivector_length, T/multivector_length); \n\
r = mul(5, b,a,v,a,b); \n\
print(r); \n\
 \n\
// spinor1 = mul(2, vector(1,0,0), vector_spherical(1,T/multivector_length,T/4)) \n\
// spinor2 = mul(2, vector(1,0,0), vector_spherical(1,T/multivector_length,T/4)) \n\
// mul(3, vector(1,0,0), spinor1, spinor2); \n\
 \n\
// chirality??? \n\
mul(2, trivector(3), trivector(4)); \n\
 \n\
free(arena); \n\
";
