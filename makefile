all: 
	gcc philosophersA.c -pthread -o philosophersA
	gcc philosophersB.c -pthread -o philosophersB
	#Programs have been compiled successfully