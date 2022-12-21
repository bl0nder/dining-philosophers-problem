all: 
	gcc philosophersA1.c -pthread -o philosophersA1
	gcc philosophersA2.c -pthread -o philosophersA2
	gcc philosophersB1.c -pthread -o philosophersB1
	gcc philosophersB2.c -pthread -o philosophersB2
	#Programs have been compiled successfully