public class Main {
    public static void main(String[] args) {
        double[] array={8,6,2,8,5,3,7,8,3,0,87,35,225,-2};
        QuickSort test=new QuickSort(array);
        test.print();
        test.sort(false);
        test.print();
    }
}