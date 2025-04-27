public class SelectionSort {
    protected double[] array;

    // constructor
    public SelectionSort(double[] arg_array) {
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
        // sort
        if (order) {
            for (int i = 0; i < array.length - 1; i++) {
                for (int j = i + 1; j < array.length; j++) {
                    if (array[i] > array[j]) {
                        double tmp = array[i];
                        array[i] = array[j];
                        array[j] = tmp;
                    }
                }
            }
        } else {
            for (int i = 0; i < array.length - 1; i++) {
                for (int j = i + 1; j < array.length; j++) {
                    if (array[i] < array[j]) {
                        double tmp = array[i];
                        array[i] = array[j];
                        array[j] = tmp;
                    }
                }
            }
        }
    }

    public void sort() {// ascending order
        sort(true);
    }
}