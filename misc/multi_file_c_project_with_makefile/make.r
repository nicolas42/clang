rebol []

{Rebol Make System
Takes all c files and compiles them into object files. Puts them in obj folder
Links all object files into executable
}

; === Helper Functions ===
foreach-file: func [
	{Deep read a directory given a dir d
	an output block o and a boolean function fn}
	d fn /local f
] [
	f: read d
	foreach f f [do :fn d/:f]
	foreach f f [if #"/" = last f [foreach-file d/:f :fn]]
]

remove-suffix: func [ file ] [
	file: copy file
	clear find/reverse tail file suffix? file
	head file
]

; === Main ===
target: {main}
object-dir: {obj/}
dir: what-dir
files: []
object-files: []
commands: []

; === Get Files ===
foreach-file dir func [ file ] [ 
	if find [%.c] suffix? file [ 
		append files remove-suffix second split-path file
	]
]

; === Make Object Paths ===
foreach file files [
	append object-files rejoin [ object-dir file {.o} ]
]

; === Make Commands ===
foreach file files [
	append commands rejoin [ {cc -c -g -std=c99 -Wall -Werror } file {.c -o } object-dir file {.o} ]
]
append commands rejoin [ {cc -o } target { } object-files ]
append commands {./main}


foreach command commands [
	;print command
	call/shell probe command
]


comment {
	 rm -rf main *.o
}
