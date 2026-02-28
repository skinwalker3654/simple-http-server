server = server.c
target = server
cc = gcc

runserver: $(server)
	@echo "compiling the server..."
	$(cc) $< -o $(target)
	@echo "starting the server..."
	./$(target)

clean:
	@echo "deleting the executables..."
	rm $(target)

.PHONY: serverrun clean
