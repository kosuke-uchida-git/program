package matrix;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Matrix {
	private int row;
	private int column;
	private ArrayList<Double> elements;

	public Matrix() {
	}

	public Matrix(int row, int column) {
		this.row = row;
		this.column = column;
		elements = new ArrayList<>();
		int size = row * column;
		for (int i = 0; i < size; i++) {
			elements.add(0.0);
		}
	}
	
	public Matrix(String filename) throws IOException {
		this.elements = new ArrayList<>();

		ArrayList<String[]> lines = new ArrayList<>();

		try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
			String line;
			while ((line = reader.readLine()) != null) {
				line = line.trim();
				if (!line.isEmpty()) {
					lines.add(line.split("\\s+"));
				}
			}
		}

		// 行数と列数の決定
		this.row = lines.size();
		if (row == 0) {
			throw new IllegalArgumentException("File contains no data.");
		}
		this.column = lines.get(0).length;

		// 行ごとの列数が一致しているかチェックしながら格納
		for (int i = 0; i < row; i++) {
			String[] tokens = lines.get(i);
			if (tokens.length != column) {
				throw new IllegalArgumentException("Inconsistent number of columns at row " + i);
			}
			for (String token : tokens) {
				elements.add(Double.parseDouble(token));
			}
		}
	}

	public int getRow() {
		return row;
	}

	public void setRow(int row) {
		this.row = row;
	}

	public int getColumn() {
		return column;
	}

	public void setColumn(int column) {
		this.column = column;
	}

	public ArrayList<Double> getElements() {
		return elements;
	}

	public void setElements(ArrayList<Double> elements) {
		this.elements = elements;
	}

	public double get(int row, int column) {
		return elements.get(row * this.column + column);
	}

	public double set(int row, int column, double arg) {
		return elements.set(row * this.column + column, arg);
	}

	public void print() {
		System.out.print("(");
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				System.out.print(get(i, j) + " ");
			}
			if (i != row - 1) {
				System.out.println();
			}
		}
		System.out.println(")");
	}

	public void add(Matrix arg) {
		for (int i = 0; i < elements.size(); i++) {
			elements.set(i, elements.get(i) + arg.elements.get(i));
		}
	}

	public void subtract(Matrix arg) {
		for (int i = 0; i < elements.size(); i++) {
			elements.set(i, elements.get(i) - arg.elements.get(i));
		}
	}
	
	public Matrix multiply(Matrix arg) {
        // 行列の乗算が可能かチェック（この行列の列数 = 引数行列の行数）
        if (this.column != arg.row) {
            throw new IllegalArgumentException("Matrix multiplication not possible: " + 
                this.row + "x" + this.column + " * " + arg.row + "x" + arg.column);
        }
        
        // 結果の行列を作成（この行列の行数 x 引数行列の列数）
        Matrix result = new Matrix(this.row, arg.column);
        
        // 行列の乗算を実行
        for (int i = 0; i < this.row; i++) {
            for (int j = 0; j < arg.column; j++) {
                double sum = 0.0;
                for (int k = 0; k < this.column; k++) {
                    sum += this.get(i, k) * arg.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        
        return result;
    }

}
