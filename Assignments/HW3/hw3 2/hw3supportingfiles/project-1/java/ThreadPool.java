/**
 * A simple thread pool API.
 * 
 * Tasks that wish to get run by the thread pool must implement the
 * java.lang.Runnable interface.
 */
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
public class ThreadPool
private  ExecutorService Pool;
{
	/**
	 * Create a default size thread pool.
	Method                         Description
	newFixedThreadPool(int)           Creates a fixed size thread pool.
	newCachedThreadPool()             Creates a thread pool that creates new 
                                 	 	threads as needed, but will reuse previously 
                                 	 	constructed threads when they are available
	newSingleThreadExecutor()         Creates a single thread. 

 	 */
	public ThreadPool() {
ExecutorService Pool = Executors.newFixedThreadPool();
	
    }
	
	
	/**
	 * Create a thread pool with a specified size.
	 * 
	 * @param int size The number of threads in the pool.
	 */
	public ThreadPool(int size) {
ExecutorService Pool = Executors.newFixedThreadPool(size); 
	
    }
	
	
	/**
	 * shut down the pool.
	 */
	public void shutdown() {

pool.shutdown(); 
	}
	
	/**
	 * Add work to the queue.
       passes the Task objects to the pool to execute 
	 */
	public void add(Runnable task) {

pool.execute(task);

	}
	
}
