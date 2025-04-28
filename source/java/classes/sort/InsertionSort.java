public class InsertionSort {
    protected double[] array;

    // constructor
    public InsertionSort(double[] arg_array) {
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
            for (int i = 1; i < array.length; i++) {// insert element #i
                for (int j = i; j > 0; j--) {// compare #j-1 and #j
                    if (array[j - 1] > array[j]) {
                        double tmp = array[j];
                        array[j] = array[j - 1];
                        array[j - 1] = tmp;
                    } else {
                        break;
                    }
                }
            }
        } else {
            for (int i = 1; i < array.length; i++) {// insert element #i
                for (int j = i; j > 0; j--) {// compare #i and #j
                    if (array[j - 1] < array[j]) {
                        double tmp = array[j];
                        array[j] = array[j - 1];
                        array[j - 1] = tmp;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    public void sort() {// ascending order
        sort(true);
    }
}