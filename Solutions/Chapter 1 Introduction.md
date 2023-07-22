# Chapter 1 Introduction

1.1 What are the three main purposes of an operating system?

> My answer:
>
> 1. give user a convenient way to use the computer.
> 2. to control the hardware to run in different ways  
> 3. application program to execute environment

**Answer:**

The three main purposes are:

* To **<u>provide an environment</u>** **for a computer user** to execute programs on computer hardware in a convenient and efficient manner.

* To **<u>allocate the separate resources</u>** **of the computer** as needed to perform the required tasks. The allocation process should be as fair and efficient as possible.

* As **<u>a control program</u>**, it serves two major functions: 

  (1) **supervision of the execution of user programs** to prevent errors and improper use of the computer

  (2) **management** of the operation and control of I/O devices.





1.2 We have stressed the need for an operating system to make efficient use of the computing hardware. When is it appropriate for the operating system to forsake this principle and to "waste" resources? Why is such a system not really wasteful?

> My answer:
>
> For security, for some security use, we need to waste some resources for double checks. It might be waste some resource and save more data during the process. It is not really wasteful because in the situation, the reliable of the computer is much important than the efficient.

**Answer:**

Single-user systems should maximize use of the system for the user. A GUI might "waste" CPU cycles, but it optimizes the user's interaction with the system.



1.3 What is the main difficulty that a programmer must overcome in writing an operating system for a real-time environment?

>My answer:
>
>Balance every programs. The allocation of the resources and processes order and so on. 

**Answer:**

The main difficulty is **<u>keeping the operating system within the fixed time constraints of a real-time system.</u>** If the system does not complete a task in a certain time frame, it may cause a breakdown of the entire system. Therefore, when writing an operating system for a real-time system, the writer must be sure that his scheduling schemes don't allow response time to exceed the time constraint.



1.4 Keeping in mind the various definitions of operating system, consider whether the operating system should include applications such as web browsers and mail programs. Argue both that it should and that it should not, and support your answers.

> My answer:
>
> It should. But web browsers and mail programs need system to use the hardware to connect internet, it need the OS to do that, users are not convenient to connect the internet every time when they are wanting to search the website using web browsers. And some things like port should be control by the OS for some security reasons.
>
> It should not. Because the web browser it can be different styles, which means it actually kind like the applications which created by the users, like we can use chrome on different computer systems. It just the application of web browser. 

**Answer:**

An argument in favor of including popular applications in the operating system is that if the application is embedded within the operating system, it is likely to be better able to take advantage of features in the kernel and therefore have performance advantages over an application that runs outside of the kernel. 

Arguments against embedding applications within the operating system typically dominate, however: 

(1) the applications are applications -- not part of an operating system

(2) any performance benefits of running within the kernel are offset by security vulnerabilities

(3) inclusion of applications leads to a bloated operating system.



1.5 How does the distinction between kernel mode and user mode function as a rudimentary form of protection(security)?

> My answer:
>
> Kernel mode cannot be change, but the user mode can be modify by users. 

**Answer:**

The distinction between kernel mode and user mode provides a rudimentary form of protection in the following manner. Certain instructions can be executed only when the CPU is in kernel mode. Similarly, hardware devices can be accessed only when the program is in kernel mode, and interrupts can be enabled or disabled only when the CPU is in kernel mode. Consequently, the CPU has very limited capability when executing in user mode, thereby enforcing protection of critical resources. 



1.6 Which of the following instructions should be privileged?

a. Set value of timer.

b. Read the clock

c. Clear memory

d. Issue a trap instruction

e. Turn off interrupts

f. Modify entries in device-status table.

g. Switch from user to kernel mode.

h. Access I/O device.

> My Answer:
>
> e. f. h

**Answer:** 

The following operations need to be privileged: a. set value of timer, c.clear memory, e.turn off interrupts, f.modify entries in device-status table, h.access I/O device. The rest can be performed in user mode. 



1.7 Some early computers protected the operating system by placing it in a memory partition that could not be modified by either the user job or the operating system itself. Describe two difficulties that you think could arise with such a scheme.

> My answer: 
>
> First, the memory size is limited and it is very expensive, if in a memory partition that could not be modified, it may be not always be used, which means it might be wasted. And the performance of the computers will decreased. 
>
> Second, it is still hard to protect operating system. Because the operating system still have the memory where it can use. 

**Answer:**

The data required by the operating system (passwords, access controls, accounting information, and so on) would have to be stored in or passed through unprotected memory and thus be accessible to unauthorized users. 



1.8 Some CPUs provide for more than two modes of operation. What are two possible uses of these multiple modes?

> My answer:
>
> 1. Protection, more modes will have different access to do something.
> 2. Better performance, more modes can use different way to handle more specific ways, it will improve performance and make less waste.

**Answer:**

Although most systems only distinguish between user and kernel modes, some CPUs have supported multiple modes. Multiple modes could be used to provide a finer-gained security policy. For example, rather than distinguishing between types of user mode. Perhaps users belonging to the same group could execute each other's code. The machine would go into a specified mode when one of these users was running code. When the machine was in this mode, a member of the group could run code belonging to anyone else in the group.

Another possibility would be to provide different distinctions within kernel code. For example, a specific mode could allow USB device drivers to run. This would mean that USB devices could be serviced without having to switch to kernel mode, thereby essentially allowing USB device drivers to run in a quasi-user/kernel mode.



1.9 Timers could be used to compute the current time. Provide a short description of how this could be accomplished.

> My answer: 



1.10 Give two reasons why caches are useful. What problems do they solve? What problems do they cause? If a cache can be made as large as the device for which it is caching (for instance, a cache as large as a disk), why not make it that large and eliminate the device?

> My answer: Caching is an important principle of computer systems. Cache can improve the performance of the computer, however, It is cache is very expensive, and it is volatile storage, if the power is turned off ow otherwise lost it can not hold the program, it is not very reliable for some situation.
>
> Two reasons of why caches are useful:
>
>  (1) Fast access speed,  it can help system to hold the instructions expected to be executed next, and help CPU do not wait several cycles while an instruction was fetched from main memory and when two or more components need to exchange data, and the components perform transfers at differing speeds.
>
> (2) The performance improve without costing too much space: caches bring high speed so without taking up as much physical space as the lower elements of the memory hierarchy. 
>
> Problems they solve: 
>
> The transfer problem: Caches solve the transfer problem by providing a buffer of intermediate speed between the components. If the fast device finds the data it needs in the cache, it need not wait for the slower device. 
>
> The performance problem: Caches ameliorate the (performance critical) memory access time by leveraging spatial and temporal locality. 
>
> Problems they cause: Caches also introduce an additional level of complexity which are coherency and consistency assurance. And they will also incur an economic and space at the computer organization level penalty when add a cache. And Caches are volatile storage, if the power is turned off otherwise lost it cannot hold the program, it is not very reliable for some situation. The data in the cache must be kept consistent with the data in the components. If a component has a data value change, and the datum is also in the cache, the cache must also be updated. 
>
> Reasons of why not make it that large and eliminate the device:  
>
> Ineffective, because it would be too costly, the immense size would slow it down, and a cache is generally a volatile memory, while we want data on disks to be persistent.

**Answer:**

Caches are useful when two or more components need to exchange data, and the components perform transfers at differing speeds. Caches solve the transfer problem by providing a buffer of intermediate speed between the components. If the fast device finds the data it needs in the cache, it need not wait for the slower device. The data in the cache must be kept consistent with the data in the components. If a component has a data value change, and the datum is also in the cache, the cache must also be updated. This is especially a problem on multiprocessor systems, where more than one process may be accessing a datum. A component may be eliminated by an equal-sized cache, but only if:

(a) the cache and the component have equivalent state-saving capacity (that is, if the component retains its data when electricity is removed, the cache must retain data as well) 

(b) the cache is affordable, because faster storage tends to be more expensive.









1.11 Distinguish between the client – server and peer-to-peer models of distributed systems.



1.12 