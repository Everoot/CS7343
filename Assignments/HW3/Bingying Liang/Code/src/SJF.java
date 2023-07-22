import java.util.List;

public class SJF implements Algorithm {
    private List<Task> queue;

    public SJF(List<Task> queue){
        this.queue = queue;
    }

    @Override
    public void schedule() {
        System.out.println("Shortest-job-first(SJF): \n");
        while(queue.size() != 0){
            Task next = pickNetTask();
            queue.remove(next);
            CPU.run(next, next.getBurst());
            System.out.println("Task " + next.getName() + " finished\n");
            System.out.println("---------------------------------------");
        }
    }

    @Override
    public Task pickNetTask() {
        // schedules tasks in order of the length of the tasks' next CPU burst.
        int Tid_index = -1;
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < queue.size(); i++){
            int currentBurst = queue.get(i).getBurst();
            if (currentBurst < min){
                min = currentBurst;
                Tid_index = i;
            }
        }
        return queue.get(Tid_index);
    }
}
