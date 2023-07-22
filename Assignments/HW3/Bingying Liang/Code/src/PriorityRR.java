import java.util.List;

public class PriorityRR implements Algorithm{
    private List<Task> queue;
    int quantum = 10;

    public PriorityRR(List<Task> queue){
        this.queue = queue;
    }
    @Override
    public void schedule() {
        System.out.println("Priority with round-robin: \n");
        while(queue.size() != 0){
            Task next = pickNetTask();
            queue.remove(next);
            if (next.getBurst() > quantum){
                CPU.run(next, quantum);
                next.setBurst(next.getBurst() - quantum);
                System.out.println(next.getName() + " has ran " + quantum + " and the remaining Burst is " + next.getBurst() + "\n");
                queue.add(next);
                System.out.println("----------------------------------------------------------------");
            } else {
                CPU.run(next, quantum);
                System.out.println(next.getName() + " has ran " + next.getBurst() + " and the remaining Burst is 0\n");
                next.setBurst(0);
                System.out.println("Task " + next.getName() + " finished\n");
                System.out.println("-----------------------------------------------------------------");
            }
        }


    }

    @Override
    public Task pickNetTask() {
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
