import java.util.concurrent.Semaphore;

public class TA implements Runnable{
    private SignalSemaphore wakeup; // Semaphore used to wakeup TA.

    private Semaphore chairs; // Semaphore used to wait in chairs outside office.

    public TA(SignalSemaphore w, Semaphore c, Semaphore a){
        wakeup = w;
        chairs = c;
    }

    @Override
    public void run() {
        for(int i = 0; i < Main.TA_visit; i++){
            try {
                System.out.println("No students left. The TA is going to nap.");
                wakeup.release();
                System.out.println("The TA was woken up by a student.");
                Thread.sleep(1);

                // If there are other students waiting
                while (chairs.availablePermits() != Main.chair) {
                    Thread.sleep(1);
                    chairs.release();
                }
            }catch (InterruptedException e){
                continue;
            }
        }

    }
}
