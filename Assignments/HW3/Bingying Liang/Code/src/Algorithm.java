public interface Algorithm {
    // Implementation of scheduling algorithm, Invokes the scheduler
    public abstract void schedule();

    // Select the next task to be scheduled
    // Select the next task using the appropriate scheduling algorithm
    public abstract Task pickNetTask();
}
