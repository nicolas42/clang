#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
int main() { int cap = 1000000; /* 1mb */ char a[cap]; FILE *fp; fp = fopen("main.c", "r"); fread(a, 1000000, 1, fp); fclose(fp); char ca[cap]; strcpy(ca, a); /* ca[100] = '\0'; */ printf("%s", a); int la = strlen(a); int offsets[1000]; int length_offsets = 0; /* Convert spaces to null */ for (int i = 0; i < la; i++){ if (isspace(a[i])){ a[i] = '\0'; } } for (int i = 0; i < la - 1; i++){ if (i == 0 && a[i] != '\0') { offsets[length_offsets++] = i; } else if (a[i] == '\0' && a[i+1] != '\0') { offsets[length_offsets++] = i+1; } } for (int i = 0; i < length_offsets; i++){ printf("%s ", a + offsets[i]); } puts("\n"); return 0; } 
