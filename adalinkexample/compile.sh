gcc -c main.c
gnatmake api
gnatbind -n api
gnatlink api.ali main.o
