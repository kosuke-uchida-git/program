package matrix;

import java.util.Random;

public class FactorizationMachine {
	private Matrix explain;
	private Matrix object;
	private int user;
	private int item;
	private double bias;
	private Matrix coefficient;
	private Matrix interaction;
	private int dimension;
	private double learningRate;

	public FactorizationMachine(Matrix combined, int user, int item) {
		this.user = user;
		this.item = item;
		this.dimension = 10;
		this.learningRate = 0.01;
		this.bias = 0.0;

		int n = combined.getRow();         // サンプル数
		int fullCol = combined.getColumn(); // 列数（説明 + 目的）

		int explainCol = fullCol - 1;

		// 説明変数行列（n × (col - 1)）
		this.explain = new Matrix(n, explainCol);
		// 目的変数列（n × 1）
		this.object = new Matrix(n, 1);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < explainCol; j++) {
				explain.set(i, j, combined.get(i, j));
			}
			object.set(i, 0, combined.get(i, explainCol)); // 最終列
		}
	}

	public void initialize() {
		Random random = new Random();

		int featureSize = explain.getColumn();

		// 線形係数ベクトルの初期化 (1 × featureSize)
		this.coefficient = new Matrix(1, featureSize);
		for (int j = 0; j < featureSize; j++) {
			coefficient.set(0, j, 0.0); // 初期値は0
		}

		// 交互作用項の初期化 (featureSize × dimension), 一様分布 U(0,1)
		this.interaction = new Matrix(featureSize, dimension);
		for (int i = 0; i < featureSize; i++) {
			for (int d = 0; d < dimension; d++) {
				double value = random.nextDouble(); // 0.0 <= value < 1.0
				interaction.set(i, d, value);
			}
		}
	}

	public void reviseBias() {
		int n = explain.getRow(); // サンプル数
		double gradientSum = 0.0;

		for (int i = 0; i < n; i++) {
			double yTrue = object.get(i, 0);
			double yPred = predict(i); // i番目のサンプルに対する予測値
			gradientSum += (yPred - yTrue);
		}

		double gradient = gradientSum / n;
		bias -= learningRate * gradient;
	}

	public double predict(int index) {
		double yPred = bias;

		int featureSize = explain.getColumn();

		// x_i: index番目の入力特徴行
		// 線形項: w^T x
		for (int j = 0; j < featureSize; j++) {
			double x = explain.get(index, j);
			double w = coefficient.get(0, j);
			yPred += w * x;
		}

		// 交互作用項
		for (int f = 0; f < dimension; f++) {
			double sumVx = 0.0;
			double sumVxSquared = 0.0;

			for (int j = 0; j < featureSize; j++) {
				double x = explain.get(index, j);
				double v = interaction.get(j, f);
				double vx = v * x;

				sumVx += vx;
				sumVxSquared += vx * vx;
			}

			yPred += 0.5 * (sumVx * sumVx - sumVxSquared);
		}

		return yPred;
	}

	public void reviseCoefficient() {
		int n = explain.getRow(); // サンプル数
		int featureSize = explain.getColumn(); // 特徴量数

		// 係数 w_j を1つずつ更新
		for (int j = 0; j < featureSize; j++) {
			double gradientSum = 0.0;

			for (int i = 0; i < n; i++) {
				double x_ij = explain.get(i, j);
				double yPred = predict(i);
				double yTrue = object.get(i, 0);
				gradientSum += (yPred - yTrue) * x_ij;
			}

			double gradient = gradientSum / n;
			double w = coefficient.get(0, j);
			coefficient.set(0, j, w - learningRate * gradient);
		}
	}
	
	public void reviseInteraction() {
		int n = explain.getRow();         // サンプル数
		int featureSize = explain.getColumn();  // 特徴量数

		for (int j = 0; j < featureSize; j++) {
			for (int f = 0; f < dimension; f++) {
				double gradientSum = 0.0;

				for (int i = 0; i < n; i++) {
					double x_ij = explain.get(i, j);
					double yPred = predict(i);
					double yTrue = object.get(i, 0);
					double error = yPred - yTrue;

					// sum_k v_{k,f} * x_{ik}
					double sumVx = 0.0;
					for (int k = 0; k < featureSize; k++) {
						sumVx += interaction.get(k, f) * explain.get(i, k);
					}

					// gradient term
					double v_jf = interaction.get(j, f);
					double gradComponent = x_ij * (sumVx - v_jf * x_ij);
					gradientSum += error * gradComponent;
				}

				double gradient = gradientSum / n;
				double current = interaction.get(j, f);
				interaction.set(j, f, current - learningRate * gradient);
			}
		}
	}
	
	public void train(int epoch) {
		int n = explain.getRow();

		for (int e = 0; e < epoch; e++) {
			// パラメータの更新
			reviseBias();
			reviseCoefficient();
			reviseInteraction();

			// 平均二乗誤差（MSE）の計算
			double loss = 0.0;
			for (int i = 0; i < n; i++) {
				double yTrue = object.get(i, 0);
				double yPred = predict(i);
				double error = yPred - yTrue;
				loss += error * error;
			}
			loss /= n;

			// エポックごとのログ出力
			System.out.printf("Epoch %d: MSE = %.6f%n", e + 1, loss);
		}
	}


}
