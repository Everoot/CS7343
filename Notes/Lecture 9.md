# Lecture 9

March-30-2023

Dining Philosophers Problem

5 philosophers	{think, eat}.   

Eat: a round table is set to serve food. five plates, five forks, foo is spaghetti  and in order to eat. A philosopher must have two forks.



philosopher **<span style="color:red">$\rightarrow$ Processes</span>** 

five forks **<span style = "color:red">$\rightarrow$ Resources</span>**



<span style="color:red">**starvation**: write an algorithm in such a way that each philosopher</span> (i.e process)<span style= "color:red"> has a turn to pick two forks</span> (i.e resources)<span style = "color:red"> and eat</span> (i.e execute).

how?

There are two ways of doing it.

* Semaphores
* Monitor: Textbook present a solution using monitors. <span style= "color:red">The solution doesn't work</span>.
  *  In the lecture we use semaphores.



Exam:

