/*
Hier mal mein Ansatz, tut aber leider nicht das was es soll
*/

public class Sieve {

	public static void main  (String[] args) throws InterruptedException{
		SieveRunnable r=new SieveRunnable(2, null);
		Thread t=new Thread(r);
		r.setFirst(t);
		t.start();
		System.out.println("main");

		t.join();

	}


}
class SieveRunnable implements Runnable{
	static int curr=3;
	static int n=100;
	SieveRunnable sr;
	Thread first;
	Thread next;

	int z;
	public SieveRunnable (int i, Thread t){
		this.z=i;
		this.first=t;
	}
	public void setFirst(Thread t){
		this.first=t;
	}

	public synchronized void run(){
		while(true){
		System.out.println("run with z="+z);
		if(SieveRunnable.curr==n){
					System.out.println("if");
			return;
		}
		if(curr%z==0){
			System.out.println("ink");
			SieveRunnable.curr++;
			try{
				first.notify();
				this.wait();
				System.out.println("pause "+z);
			} catch (InterruptedException e){}

		}else {
			if(sr==null){
					SieveRunnable sr=new SieveRunnable(curr,first);
				System.out.println(curr);
				next=new Thread(sr);
				next.start();
				try{
					this.wait();
					System.out.println("pause "+z);

				} catch (InterruptedException e){}

			}
			try{
				next.notify();
				System.out.println("pause "+z);
				this.wait();

			} catch (InterruptedException e){}
		}
		}


	}
}
