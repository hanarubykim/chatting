Project Name: chatting

Team Members and class period:
Christy Guan (4th pd)
Hana Kim (4th pd)


Broad description of project:


List of any required libraries:
- N/A

Include apt-get instructions on how to install the libraries:
- N/A


Instructions on how to use your project:
1. `git clone` into the repository
2. Navigate to the correct directory
3. `make run`
4. Set up a server: `./server`
5. In separate terminal window(s), set up the clients by repeating steps 2 and 3
6. Set up a client: `./client`
7. Follow the instruction prompts
* NOTE: You can only enter a single word for your name, no spaces are allowed
* After you select a chatroom color, press `ENTER` twice
8. To quit the program, use `contrl c`

* To create a new chatroom, use `*CREATE [port number]` where port number is any number from 1025 to 65353
* To join the chatroom, use `*JOIN [port number]`
* NOTE: Please make sure there are no typos!


Other information you deem important (known bugs, work citation, etc.):
* There are small errors in the messages broadcasted between the clients when creating a chatroom or joining a chatroom
* User MUST make sure that there is no `server` command running in the background, or else they will receive an error: `error 48: Address already in use`
  * On mac, users can do `top` to find the process ID of the `server` command. Then, type `kill [process id]` in the terminal
