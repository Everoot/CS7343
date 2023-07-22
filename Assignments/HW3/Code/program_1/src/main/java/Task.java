public class Task implements Runnable
{
    private int a;
    private int b;

    public Task(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public void run() {
        System.out.println(Thread.currentThread().getName() + ". I am a task result = " + (a + b));
    }
}
