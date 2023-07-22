public class SignalSemaphore {
    public boolean signal = false;
    // Send the signal
    public synchronized void take(){
        this.signal = true;
        this.notify();   // wake up the thread
    }

    // Will wait until it receives a singal before continuing.
    public synchronized void release() throws InterruptedException{
        while(!this.signal){
            wait(); // causes the current thread to wait indefinitely until another thread either invokes notify()
        }

        this.signal = false;
    }

}
