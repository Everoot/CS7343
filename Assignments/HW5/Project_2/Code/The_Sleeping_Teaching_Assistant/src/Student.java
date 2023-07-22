import java.util.concurrent.Semaphore;

public class Student implements Runnable{

    private int studentNum;   //  Student number.
    private SignalSemaphore wakeup; // Semaphore used to wakeup TA.
    private Semaphore chairs; // Semaphore used to wait in chairs outside office. Three chairs. If not available
                              // Student will resume programming and will seek help at a later time.
    private Semaphore available; // Mutex lock (binary semaphore) used to determine if TA is available.

    // A reference to the current thread.
    // private Thread t;
    // Non-default constructor

    public Student(SignalSemaphore w, Semaphore c, Semaphore a, int num){
        wakeup = w;
        chairs = c;
        available = a;
        studentNum = num;
    }

    @Override
    public void run() {

        for (int i = 0; i < Main.TA_visit; i++) {
            try {
                // Program first
                System.out.println("Student " + studentNum + " has started programming");
                Thread.sleep(100); // Used to pause the execution of current thread for specified time in milliseconds

                // Check to see if TA
                System.out.println("Student " + studentNum + " is checking to see if TA is available.");
                if (available.tryAcquire()) { // checks if the TA is sleeping
                    try {
                        // wakeup the TA
                        wakeup.take(); //goes to the method take int class SignalSemphore
                        System.out.println("Student " + studentNum + " woke up the TA.");
                        System.out.println("Student " + studentNum + " has started working with the TA.");
                        Thread.sleep(100);
                        System.out.println("Student " + studentNum + " has stopped working with the TA,");
                    } catch (InterruptedException e) {
                        continue;
                    } finally {
                        available.release(); // return to semaphore
                    }

                } else {
                    // Check to see if any chairs are avaiable.
                    System.out.println("Student " + studentNum + " could not see the TA. Checking for available charis.");
                    if (chairs.tryAcquire()){
                        try{
                            // Wait for TA to finish with other student.
                            System.out.println("Student " + studentNum + " is siting outside the office. " + "He is #"
                            + ((Main.chair - chairs.availablePermits())) + " in line.");
                            available.acquire();
                            System.out.println("Student " + studentNum + " has started working with the TA.");
                            Thread.sleep(100);
                            System.out.println("Student " + studentNum + " has stopped with the TA.");
                            available.release();
                        }
                        catch (InterruptedException e){
                            continue;
                        }
                    }
                    else{
                        System.out.println("Student " + studentNum + " could not see the TA and all chairs were taken." +
                                "Back to programming!");
                    }
                }

            }
            catch (InterruptedException e){
                break;
            }
            if (i == Main.TA_visit){
                System.out.println("Studnet " + studentNum + " HAS COMPLETED THEIR PROGRAMMING ASSIGNMENT");
            }
        }
    }
}
