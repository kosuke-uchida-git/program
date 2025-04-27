public class BubbleSort {
    protected double[] array;

    // constructor
    public BubbleSort(double[] arg_array) {
        array = new double[arg_array.length];
        for (int i = 0; i < array.length; i++) {
            array[i] = arg_array[i];
        }
    }

    // print
    public void print() {
        System.out.println(array.length);
        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i] + ", ");
        }
        System.out.println("");
    }

    // sort
    public void sort(boolean order) {// order=true : ascending order, order=false : descending order
        if (order) {
            for (int i = 0; i < array.length - 1; i++) {
                for (int j = array.length - 1; j > i; j--) {
                    if (array[j - 1] > array[j]) {
                        double tmp = array[j];
                        array[j] = array[j - 1];
                        array[j - 1] = tmp;
                    }
                }
            }
        } else {
            for (int i = 0; i < array.length - 1; i++) {
                for (int j = array.length - 1; j > i; j--) {
                    if (array[j - 1] < array[j]) {
                        double tmp = array[j];
                        array[j] = array[j - 1];
                        array[j - 1] = tmp;
                    }
                }
            }
        }
    }

    public void sort() {// ascending order
        sort(true);
    }
}