# simple http server

this project is a simple http server that 
only supports GET to server files


## run the server
```bash
make runserver
# then the program should say "Server is now listening on port 5050..."
```

## client request
```bash
# after you run the server now you open a new terminal and you go on the tempdir bc this is the clients place for our testing
cd tempdir

# and then run
make sendrequest
# this will send a request to the test.file witch is a file that we use it as an example of our server
```

## extens
```bash
# if you want more then just test.file the only thing you have to do is
# to create the files you want in the same directory with the server executable
# and then after you run the server, in a different director (clients directory) run
wget localhost:5050/filename # @filename is the name of the file you want the server to give you
```

im gonna add more in the future.
things like POST and other operations
safety from hacking techinques
hanlde multiple requests
and more!!
# simple-http-server
