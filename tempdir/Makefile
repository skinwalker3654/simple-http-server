target = test.file
wget = wget

sendrequest: $(target)
	@echo "sending request to the server to get the test.file..."
	$(wget) localhost:5050/$<

clean:
	@echo "deleting the test.file..."
	rm $(target)

.PHONY: sendrequest clean
