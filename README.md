# About the project
This is a very basic client server system I created for learning reasons. The client can send a String in form of "ADD sometext" to the server and the server will add the input to a .txt file and responds if the operation was successfull. The Client can also send "GET" in which the server will respond with the whole content of the file.

NOTE: The server can currently only handle one client at a time and will process multiple client requests one after another.

# server
server is running as C code using the socket library

To compile and run:

`gcc server.c dataprocess.c -o sv`

`./sv`

# client
client is running as a kotlin app for android (and also C for desktop)

UI:

<img src="https://github.com/drashie/simple-client-server/assets/106255805/2d2163e8-9df9-495f-822d-e84e422248ea" alt="Screenshot" width="300">


To compile and run the C client:

`gcc client.c -o cl`

`./cl GET`

`./cl ADD sometext`
