import java.util.ArrayList;
import java.util.Vector;

public class ArrayandList {
    protected int[] int_arr;
    protected Vector<Integer> int_vec;
    protected ArrayList<Integer> int_arrls;

    public ArrayandList() {
        int_arr = new int[1];
        int_vec = new Vector<>();
        int_arrls = new ArrayList<>();

        int_vec.add(1);
        int_arrls.add(2);
    }

    public void getSize() {
        System.out.printf("%d\n%d\n%d\n", int_arr.length, int_vec.size(), int_arrls.size());
    }
}
