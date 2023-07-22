public class Philosopher implements Runnable{
    // private variables
    private int philosopherNumber;
    private DiningServerImp dTable;
    private String state;

    // constructor
    public Philosopher(){

    }

    public Philosopher(int philosopherNumber, DiningServerImp dTable){
        this.philosopherNumber = philosopherNumber;
        this.dTable = dTable;
        // if even phiNum then this Philosopher is thinking
        if (philosopherNumber % 1 == 0) {
            this.state = "Thinking";
        } else{ //
            this.state = "Eating";
        }
    }

    // Stalls so the Philosopher can do something.
    // @excpeton Throws an Exception if thread is interrupted.
    private void doSomething() throws InterruptedException{
        // generate random time between 1-3 seconds
        long time = (long)(Math.random() * 2000) + 1000;
        Thread.sleep(time);
    }

    @Override
    public void run() {
        while(true){
            try{
                // this Philosopher takes forsk off the table to eat
                dTable.takeForks(philosopherNumber);
                // stall
                doSomething();
                // this Philosopher returns forks to the table to think
                dTable.returnForks(philosopherNumber);
            }catch (Exception e){
                System.out.println("Exception Caught!");
            }
        }
    }

    // Gets this Philosopher's state:
    // @return The state that this Philosopher is in.
    public String getState() {
        return this.state;
    }

    // Sets this Philosopher's state
    // @param state The state the Philosopher is going to be.

    public void setState(String state){
        this.state = state;
    }
}
