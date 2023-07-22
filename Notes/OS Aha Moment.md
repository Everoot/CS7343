# OS Aha Moment

Pthread: POSIX线程 (POSIX Threads, 常被缩写为Pthreads) 是POSIX的线程标准, 定义了创建和操纵线程的一套API.

Pthreads refers to the POSIX standard (IEEE 1003.1c) defining an API for thread creation and synchronization. This is a specification for thread behavior, not an implementation. Operating-system designers may implement the specification in any way they wish.



根据如果处理时钟中断(clock interrupts), 可以将调度算法分成两类: 非抢占式(nonpreemptive) 调度算法和抢占式(preemptive)调度算法.

nonpreemptive (非抢占式子):

* 挑选一个进程, 然后让该进程运行直至被阻塞(阻塞在IO或者等待另一个进程), 或者知道该进程自动释放CPU, 即使该进程运行了若干小时也不会被强迫(Suspend Process)挂起.

  > Suspend process: 挂起, 是电脑操作中的一种进程. 挂起进程在操作系统中可以定义为暂时被淘汰出内存的进程.

* 在适中中断发生不会进行调度, 在处理完时钟中断后, 如果没有更高级优先级的进程等待到时, 则被中断的进程会继续执行.



preemptive(抢占式):

* 挑选一个进程, 并且让该进程运行某个固定时段的最大值, 如果该时段结束, 进程仍在运行, 则它就被挂起, 而程序挑选另一个进程运行.
* 进行抢占式调度, 需要在时间间隔的末端发送时钟中断, 以便把CPU控制返回调度程序, 如果没有可用的时钟, 那么非抢占式调度就是唯一的选择了



调度算法中的分类

在不同的系统中, 调度程序的优化是不同的, 可以划分为三种环境:

* 批处理 Batch
* 交互式 Interactive
* 实时 Real Time





turnaround time = Time finish - Time arrival



Message passing:(信息传递) 

与Monitor(管程)和Semaphore(信号量)有关的一个问题是: 如果一个分布式系统有过个CPU, 并且每个CPU拥有自己的私有内存, 他们在同一个局域网相连, 那么这些原语将失效. 这里的结论是: 信号量太低级了, 而Monitor在少数几种编程语言之外又无法使用. 并且, 这些原语均为提供机器间的信息交换方法, 所以还需要其他的方法.

这个方法就是消息传递(Message passing) 这种进程间通信的方法使用两条原语send和receive, 他们是系统调用而不是语言成分, 因此可以很容易将他们加入到库过程中(library procedures)

> send(destination, &message);
>
> receive(source, &message)

