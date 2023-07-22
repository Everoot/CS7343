import java.util.List;

public class Priority implements Algorithm {
    private List<Task> queue;

    public Priority(List<Task> queue){
        this.queue = queue;

    }

    @Override
    public void schedule() {
        System.out.println("Priority scheling:");
        while (queue.size() != 0){
            Task next = pickNetTask();
            queue.remove(next);
            CPU.run(next, next.getBurst());
            System.out.println("Task " + next.getName() + " finished\n");
            System.out.println("---------------------------------------");
        }

    }

    @Override
    public Task pickNetTask() {
        // scheduling task based on priority
        // Priorities range from 1 to 10, where a higher numeric value indicates a higher relative priority.
        int Tid_index = -1;
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < queue.size(); i++){
            int currentPriority = queue.get(i).getPriority();
            if (currentPriority > max){
                max = currentPriority;
                Tid_index = i;
            }
        }
        return queue.get(Tid_index);
    }
}
