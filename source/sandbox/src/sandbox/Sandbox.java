package sandbox;

import java.io.IOException;

import matrix.FactorizationMachine;
import matrix.Matrix;

public class Sandbox {

	public static void main(String[] args) {
		System.out.println("Hello, world!");
		Matrix m;
		try {
			m = new Matrix("/Users/kosuke/eclipse-workspace/sandbox/src/data.txt");
			m.print();
			FactorizationMachine  f =new FactorizationMachine(m,2,2);
			f.initialize();
			f.train(10000);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}
