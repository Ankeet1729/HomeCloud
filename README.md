# Commands

- PING
- LIST
- UPLOAD
- DOWNLOAD
- DELETE

For each message sent by client, first the server has to identify what command is being issued. This would be figured out by the server by reading the bytes till the first "space/tab/newline"

After the server has recognised the protocol, it will hook into the specific protocol implementation

For this step, the files uploaded will only persist until the connection is active. We will handle login and session management in the next step

## PING

- Format -> PING
- The server simply replies to the CLIENT with "PONG"
- If any bytes are received after the separator of "PING", the SERVER will respond with "ERROR Invalid Arguments"

## LIST

- Format -> LIST
- returns "OK <number_of_files>", followed by the names of files uploaded separated by newlines
- client sees <number_of_files> and parses until that many newlines have been seen, and outputs the message finally
- If any bytes are recevied after "LIST", the SERVER will respond with "ERROR Invalid Arguments" 

## UPLOAD

- Format -> UPLOAD <filename> <number_of_bytes>\n<actual_bytes> (the arguments are space separated except after number of bytes)
- We maintain "directories" in the "disk" for every active client connection
- The filename along with its bytes gets stored in the respective directories
- Server responds with "SUCCESS" on successful upload

## DOWNLOAD

- Format -> DOWNLOAD <filename>
- Server first replies with "OK <number_of_bytes>" or "ERROR File Not Found" as required
- If server replied with OK, then client reads the required number of bytes and displays it in the terminal finally

## DELETE

- Format -> DELETE <filename>
- This deletes the <filename> from the client directory in the disk along with its contents
- Server responds with "SUCCESS" or "ERROR File Not Found" as required