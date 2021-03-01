CC=g++

OBJ = active_room.o active_student.o lazy_room.o lazy_student.o main.o message.o responsible_student.o Room.o Student.o ZoomSys.o

%.o: %.c
	$(CC) -c -o $@ $<

output: $(OBJ)
	$(CC) -o $@ $^
	
clean:
	rm *.o
