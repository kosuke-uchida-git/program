import java.util.ArrayList;
import java.util.Random;

public class QuickSort {
    protected double[] array;

    // constructor
    public QuickSort(double[] arg_array) {
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
            sortAscending(0, array.length - 1);
        } else {
            sortDescending(0, array.length - 1);
        }
    }

    public void sort() {// ascending order
        sort(true);
    }

    public void sortAscending(int firstIndex, int lastIndex) {
        if (firstIndex >= lastIndex || firstIndex < 0 || lastIndex >= array.length) {
            return;
        }
        Random rand = new Random();
        int num = rand.nextInt(lastIndex - firstIndex + 1) + firstIndex;
        double pivot = array[num];
        ArrayList<Double> smaller = new ArrayList<Double>();
        int middle = 0;
        ArrayList<Double> larger = new ArrayList<Double>();
        for (int i = firstIndex; i <= lastIndex; i++) {
            if (array[i] > pivot) {
                larger.add(array[i]);
            } else if (array[i] == pivot) {
                middle++;
            } else {
                smaller.add(array[i]);
            }
        }
        int i = firstIndex;
        for (int j = 0; j < smaller.size(); j++) {
            array[i] = smaller.get(j);
            i++;
        }
        int firstMiddle = i;
        for (int j = 0; j < middle; j++) {
            array[i] = pivot;
            i++;
        }
        int lastMiddle = i - 1;
        for (int j = 0; j < larger.size(); j++) {
            array[i] = larger.get(j);
            i++;
        }
        sortAscending(firstIndex, firstMiddle - 1);
        sortAscending(lastMiddle + 1, lastIndex);
    }

    public void sortDescending(int firstIndex, int lastIndex) {
        if (firstIndex >= lastIndex || firstIndex < 0 || lastIndex >= array.length) {
            return;
        }
        Random rand = new Random();
        int num = rand.nextInt(lastIndex - firstIndex + 1) + firstIndex;
        double pivot = array[num];
        ArrayList<Double> smaller = new ArrayList<Double>();
        int middle = 0;
        ArrayList<Double> larger = new ArrayList<Double>();
        for (int i = firstIndex; i <= lastIndex; i++) {
            if (array[i] > pivot) {
                larger.add(array[i]);
            } else if (array[i] == pivot) {
                middle++;
            } else {
                smaller.add(array[i]);
            }
        }
        int i = firstIndex;
        for (int j = 0; j < larger.size(); j++) {
            array[i] = larger.get(j);
            i++;
        }
        int firstMiddle = i;
        for (int j = 0; j < middle; j++) {
            array[i] = pivot;
            i++;
        }
        int lastMiddle = i - 1;
        for (int j = 0; j < smaller.size(); j++) {
            array[i] = smaller.get(j);
            i++;
        }
        sortDescending(firstIndex, firstMiddle - 1);
        sortDescending(lastMiddle + 1, lastIndex);
    }
}
