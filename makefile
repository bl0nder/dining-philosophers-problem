all: 
	gcc philosophersA.c -pthread -o philosophersA
	gcc philosophersB.c -pthread -o philosophersB
	echo "Programs have been compiled successfully"