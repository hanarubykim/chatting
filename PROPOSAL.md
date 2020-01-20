Project Name: chatting

Team Members and class period:
Christy Guan (4th pd)
Hana Kim (4th pd)

A statement of the problem you are solving and/or a high level description of the project:
A chatting app between two users, mimicking Messenger. Names of the users and chatrooms are customizable.

A description as to how the project will be used (describe the user interface):
- One user will create a chat and be the host. Other users are able to find the chat and join.
- Once a user has joined a chat, they are able to see the previously sent messages in reverse-chronological order (oldest messages at the top, the most recent messages are just above the prompt line).
- Each time a message is sent, it will display the name of the user who sent the message, followed by the message itself/
  - Ex) ilovedogs123: hello world
- Users are only able to send messages containing characters (cannot send photos or videos)



A description of your technical design. This should include:
How you will be using the topics covered in class in the project:
- Processes (fork, exec)
- Shared memory and semaphores
- Allocating memory
- Pipes

How you are breaking down the project and who is responsible for which parts:
- Making basic shell of chatroom: Hana
- : Christy
- Customizing the chatroom: Hana
- Networking: Christy

What algorithms and /or data structures you will be using, and how:
- Array to hold customizable aspects of the chatroom:
  * Original names set by users
  * Nicknames
  * Chatroom name



A timeline with expected completion dates of parts of the project:
- 1/4: User inputs message, program is able to store the message
- 1/8: User can customize nicknames
- 1/11: Figure out networking
- 1/13: User can create multiple chatrooms and navigate between them
- 1/15: Hopefully done, have two days to test and make sure everything works
