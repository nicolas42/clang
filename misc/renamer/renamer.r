rebol []

input-file: %multivector.c
output-file: %output.c

word-char: charset {ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_}

find-all: funct [ str1 str2 ] [
    o: copy []
    pos: str1
    while [ pos: find/case pos str2 ] [
        if not find word-char pos/-1 [
            append o index? pos
        ]
        pos: find/case/tail pos str2
    ]
    return o

]

str: read input-file

o: copy []
foreach word [
    "arena_allocate("
    "arena_reset("
    "init("
    "scalar("
    "vector("
    "bivector("
    "trivector("
    "geometric_product("
    "mul("
    "rotate("
   "rot("
    "vector_spherical("
    "print("
    "print_scalar("
    "print_vector("
    "print_bivector("
    "print_trivector("
;    "main("    
] [
    append o find-all str word
]



pos: sort o
o: copy []
append o copy/part str pos/1 - 1

forall pos [
 
    if any [ none? pos/1 none? pos/2 ] [ break ]

    append o copy "multivector_"
    append o copy/part at str pos/1 pos/2 - pos/1

]

append o copy/part at str pos/1 (1 + length? str) - pos/1


write output-file rejoin o

