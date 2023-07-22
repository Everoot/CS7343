# Chapter 2 Operating-System Structures

2.12 The services and functions provided by an operating system can be divided into two main categories. Briefly describe the two categories, and discuss how they differ

(1) For users: Functions and services which are directly helpful to the user (networking, computer sharing, error detection, consistent computing)

(2) For system itself: Ensuring the efficient operation of the system. Systems with multiple processes can gain efficiency by sharing the computer resources among the different processes. Functions and resources which ensure efficient operation through resource sharing; resource allocation, user account tracking, and protection/security.



2.16 What are the two models of interprocess communication? What are the strengths and weaknesses of the two approaches?

(1) Message-passing model 

(2) Shared-memory model

Shared-memory strengths and weaknesses: it allows higher speed and convenience of communication. However, in the areas of protection and synchronization between the processes some problems exist.

Message-passing strengths and weaknesses: message can be exchanged between the processes either directly or indirectly through a common mailbox. It is useful for exchanging smaller amounts of data and easier to implement for inter-computer communication. However, its speed is slower than shared-memory model.