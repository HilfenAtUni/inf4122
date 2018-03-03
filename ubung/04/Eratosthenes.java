
public class Eratosthenes {

	static int LEN = 120 + 1;
	static int []ls = new int[LEN];

	public static void initArray(int size) {
		for (int i=0; i<size; i++) {
			ls[i] = i+1;
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
//					System.out.print("j:" + j + ",");
//					if(0 == j%11) System.out.println();
				}
			}
		}
	}

	public static void main(String[] args) {

		initArray(LEN);

		erathosthense();

		for(int i=1; i<LEN; i++) {
			if(0 != ls[i]){
				System.out.print(ls[i] + ", ");
			}
		}
		System.out.println();
	}
}