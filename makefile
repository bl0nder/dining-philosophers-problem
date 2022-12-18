all: 
	gcc philosophersA1.c -pthread -o philosophersA1
	gcc philosophersA2.c -pthread -o philosophersA2
	gcc philosophersB.c -pthread -o philosophersB
	#Programs have been compiled successfully