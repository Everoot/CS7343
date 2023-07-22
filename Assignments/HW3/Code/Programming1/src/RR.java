import java.util.List;

public class RR implements Algorithm{

    private List<Task> queue;
    int quantum = 10;

    public RR(List<Task> queue){
        this.queue = queue;
    }
    @Override
    public void schedule() {
        System.out.println("Round-robin (RR) scheduling: \n");
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
                CPU.run(next, next.getBurst());
                System.out.println(next.getName() + " has ran " + next.getBurst() + " and the remaining Burst is 0\n");
                next.setBurst(0);
                System.out.println("Task " + next.getName() + " finished\n");
                System.out.println("-----------------------------------------------------------------");
            }

        }
    }

    @Override
    public Task pickNetTask() {
        return queue.get(0);
    }
}
