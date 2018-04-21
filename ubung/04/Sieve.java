import java.io.*;
import java.util.concurrent.*;

public class Sieve {

	public static void main(String[] args) throws Exception {

		PipedOutputStream firstWriter = new PipedOutputStream();
		SieveThread startThread = new SieveThread(2, firstWriter);

		SieveThread.outFirst = firstWriter;

		System.out.println(2);
		startThread.start();
		firstWriter.write(3);
		startThread.join();
	}

	static class SieveThread extends Thread {

		private final static int N = 100;
		private int z;
		private int curr;
		// private PipedWriter out;
		// private PipedReader in;
		// static PipedWriter outFirst = new PipedWriter();
		private PipedOutputStream out;
		private PipedInputStream in;
		static PipedOutputStream outFirst = new PipedOutputStream();

		public static void SetFirstWriter(PipedOutputStream first) {
			outFirst = first;
		}

		public SieveThread(int z, PipedOutputStream sender) {
			this.z = z;
			try {
				in = new PipedInputStream(sender);
			} catch (IOException e) {
				//
			}
		}

		public void run() {
			while (true) {
				try {
					// Thread.sleep(500);
					curr = in.read();
					// System.out.println("curr: " + curr);

					if (curr == N) {// Itterations ende Ereicht
						System.out.println("finished.....");
						return;
					}
					if (curr % z == 0) {// z ist vielfaches -> current um eins
										// erhoehen

						// System.out.println("write curr: " + curr +
						// " to outFirst");
						outFirst.write(curr + 1);
						// Thread.sleep(100);
					} else {
						// System.out.println("curr%z != 0 -> " + curr);
						if (out == null) {// Neuen Worker erzeugen
							out = new PipedOutputStream();
							SieveThread sr = new SieveThread(curr, out);
							sr.start();
							System.out.println(curr);
							out.write(curr); // current an Worker weiter geben
						} else {
							System.out.println(curr);
							outFirst.write(curr + 1);
							// Thread.sleep(500);
						}
					}
				} catch (IOException e) {
					//
					// } catch (InterruptedException e) {
					// // TODO Auto-generated catch block
					// e.printStackTrace();
				}
			}
		}
	}

}
