import java.util.List;

public class FCFS implements Algorithm{
    private List<Task> queue;
    public FCFS(List<Task> queue){
        this.queue = queue;
    }

    @Override
    public void schedule() {
        System.out.println("First-come, first-served(FCFS): \n");
        while(queue.size() != 0){
            Task next = pickNetTask();
            queue.remove(next);
            CPU.run(next, next.getBurst());
            System.out.println("Task " + next.getName() + " finished.\n");
	    System.out.println("---------------------------------------");
        }
    }

    @Override
    public Task pickNetTask() {
        return queue.get(0);
    }
}
