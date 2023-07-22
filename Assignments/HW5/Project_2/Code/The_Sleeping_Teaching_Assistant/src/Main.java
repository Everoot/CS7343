import java.util.Scanner;
import java.util.concurrent.Semaphore;

public class Main {
    static Scanner in = new Scanner(System.in);
    static int chair, TA_visit;
    public static void main(String[] args){
        System.out.println("The TA is sleeping.");
        System.out.print("Enter the number of students in the lab:");
        int numberOfStudent = in.nextInt(); // Number of the students

        // Create semaphores.
        SignalSemaphore wakeup = new SignalSemaphore();
        System.out.print("Enter the number of chairs available: ");
        chair = in.nextInt();

        System.out.print("Enter the number of times students can visit the Assistant: ");
        TA_visit = in.nextInt();

        Semaphore chairs = new Semaphore(chair);
        Semaphore available = new Semaphore(1);

        // Create student thread and start them.
        for (int i = 0; i < numberOfStudent; i++){
            Thread student = new Thread(new Student(wakeup, chairs, available, i+1));
            student.start();
        }

        // Create and start TA Thread.
        Thread ta = new Thread(new TA(wakeup, chairs, available));
        ta.start();
    }
}
