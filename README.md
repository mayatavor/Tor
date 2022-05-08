# OurTor

## Explanation of the project

TOR (The Onion Routing) is a network that keeps the users anonymous. Every package is encrypted and passed through several different servers. TOR helps the users keep their activity private and their IP addresses safe. TOR makes it difficult to trace the user's history and location.

## Our Project

Our project is a chatting app. Our project includes:
* Main Server: In charge of accepting new users and all of the requests. Deals with sending information throughout the network.
* Secondery Servers: In charge of sending requests between the Main server and the Users. every Secondery server has it's own encryption with a different private key, and only this server can decrypt the information.
* Users: The users can communicate with each other. Every package sent from any user gets to the Main server. The main server decides what to do with the package.

## RSA Encryption

In our project, we used the RSA encryption. We built it from 0 and used it in out communication with the Secondery servers. Every Secondery server has a different key.

[RSA](https://en.wikipedia.org/wiki/RSA_(cryptosystem)) (Rivest–Shamir–Adleman) is a public-key cryptosystem that is widely used for secure data transmission.

RSA is an asymmetrical encryption, and that means that the key to encrypt and the key to decrypt are not the same. After encrypting a message, only the ones with the decryption key can decrypt the message.
With this encryption, we were able to pass the packages through the Secondary Servers without the information being leaked. This Encryption keeps the users anonymous and their information private.

## About the code

In order to be able to accept packages from the Secondery Servers, the User had to have an option to receive packages from anyone. In order to be able to do that, the User had to become a server as well. The User now have a thread that runs in the back, accepting requests and dealing with them.

In order to be able to send packages to a spacific User, the Main Server is now a client as well. It has an option to send messages to a client.
