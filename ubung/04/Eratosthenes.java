
public class Eratosthenes implements Runnable {

	static int LEN = 120 + 1;
	static int []ls = new int[LEN];
	static int idx = 0;

	public static void initArray(int size) {
		for (int i=0; i<size; i++) {
			ls[i] = i;
//			System.out.print(ls[i] + ",");
//			if(0 == i%11) System.out.println();
		}
	}

	public static void erathosthense() {
		// delete 1
		ls[1] = 0;
		for(int i=2; i<LEN; i++) {
			for(int j=i; j<LEN; j++){
				if(0 == ls[j]){
					continue;
				}
				if(i!=j && 0 == ls[j]%i){
					ls[j] = 0;
				}
			}
		}
	}

	public static void erathosthense(int i) {
		// delete 1
		ls[1] = 0;
		for(int j=i; j<LEN; j++){
			if(0 == ls[j]){
				continue;
			}
			if(i!=j && 0 == ls[j]%i){
				ls[j] = 0;
			}
		}
	}

	public static void display() {
		for(int i=1; i<LEN; i++) {
			if(0 != ls[i]){
				System.out.print(ls[i] + ", ");
			}
		}
		System.out.println();
	}
	
	public static void main(String[] args) {

		initArray(LEN);

		erathosthense();
		display();

		for (int i=2; i<LEN; i++){
			Eratosthenes erat = new Eratosthenes();
			erat.idx = i;
			erat.run();
		}
		display();
	}

	public void run() {
		// TODO Auto-generated method stub
		// System.out.println("thread: " + this.idx);
		erathosthense(this.idx);
	}
}