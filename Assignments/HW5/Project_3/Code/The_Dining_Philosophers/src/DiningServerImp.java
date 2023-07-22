import java.util.Objects;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DiningServerImp implements DiningServer {
    // private variables
    Lock lock = new ReentrantLock(); // ?
    Condition[] forks = new Condition[5]; //?
    Philosopher[] philArr = new Philosopher[5];
    long[] timeRef = new long[5];


    // constructor
    public DiningServerImp(){
        // start threads
        for (int i = 0; i < 5; i++){
            forks[i] = lock.newCondition();
            Philosopher phil = new Philosopher(i, this);
            philArr[i] = phil;
            Thread philosophers_Thread = new Thread(philArr[i]);
            philosophers_Thread.start();
        }
    }

    // Philosopher philosopherNumber is taking available forks near him to eat.
    //@para philosopherNumber The corresponding Philosopher.
    @Override
    public void takeForks(int philosopherNumber) {
        // acquires the lock
        lock.lock();

        try{
            // philosoher philosopherNumber is checking if he can eat
            philArr[philosopherNumber].setState("WAITING");
            timeRef[philosopherNumber] = System.currentTimeMillis();
            System.out.println("Philosopher " + (philosopherNumber + 1) + " is waiting to eat.");
            // check if Philosophers next to Philosopher philosopher_Number is not eating and Philosopher
            // philosopherNuimber is waiting to eat
            // If Philosopher philosopherNuber can't eat then wait more
            checkFork(philosopherNumber);
            if (!Objects.equals(philArr[philosopherNumber].getState(), "EATING")){
                forks[philosopherNumber].await();
            }

        } catch (InterruptedException e){
            System.out.println("Exceptino Caught!");
        } finally{
            // releases lock
            lock.unlock();
        }

    }

    // Philosopher philosopherNumber is returning the forks to the table
    // The corresponding Philosopher

    @Override
    public void returnForks(int philosopherNumber) {
        // acquires the lock;
        lock.lock();
        try{
            // Philosopher philosopherNumber has finished eating and is now thinking.
            philArr[philosopherNumber].setState("THINKING");
            System.out.println("Philosopher " + (philosopherNumber + 1) + " has finished eating and is now thinking.");
            // If Philosopher PhilosopherNumber can't eat then wait more.
            checkFork((philosopherNumber+4)%5);
            // If Philosopher PhilosopherNumber can't eat then wait more.
            checkFork((philosopherNumber+1)%5);
            // releases lock
        }finally {
            lock.unlock();
        }

    }

    // check if fork on the table is available so philosopher can eat.
    // @param fork The corresponding fork

    private void checkFork(int fork){
        long ttemp = System.currentTimeMillis();
        if ((!Objects.equals(philArr[(fork + 4) % 5].getState(), "EATING"))
                && (Objects.equals(philArr[fork].getState(), "WAITING"))
                && (!Objects.equals(philArr[(fork + 1) % 5].getState(), "EATING"))){
            philArr[fork].setState("EATING");
            ttemp -= timeRef[fork];
            System.out.println("Philosopher " + (fork + 1) + " is now eating."
            + " ---- Waited " + ttemp + "ms");
            forks[fork].signal();

        }
    }
}
