import java.io.*;
import java.util.*;

class SieveThread extends Thread {

  private PipedWriter out;
  static PipedWriter outFirst= new PipedWriter();
  private int n=20;
  private int z;
  private PipedReader in;
	private int curr;
  
  public static void SetFirstWriter(PipedWriter first){
    outFirst=first;
  }
  public SieveThread(int z, PipedWriter sender){
    this.z=z;
    try {in=new PipedReader(sender);}
    catch (IOException e){};
  }
 
  
	public  void run(){
		while(true){
      try{
		curr=in.read();
      
		if(curr==n){// Itterations ende Ereicht
			return;
		}
		if(curr%z==0){//z ist vielfaches -> current um eins erhoehen
			outFirst.write(curr+1);

		}else {
			if(out==null){// Neuen Worker erzeugen
        out=new PipedWriter();
					SieveThread sr=new SieveThread(curr,out);
				System.out.println(curr);
				sr.start();
			}
			out.write(curr); // current an Worker weiter geben

		}
		} catch (IOException e){
        
      }
  }
}
}
		
	
 
  

public class Sieve {
  public static void main(String[] args) throws Exception {
    PipedWriter firstWriter= new PipedWriter(); 
    SieveThread startThread = new SieveThread(2,firstWriter);
    SieveThread.outFirst=firstWriter;
    startThread.start();
    firstWriter.write(3);
    startThread.join();
  }
} 