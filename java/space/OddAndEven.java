import java.util.Scanner;

public class OddAndEven {
    public static void main(String[] args) {
        Scanner jvIn = new Scanner(System.in);

        int varA = jvIn.nextInt();
        boolean chkA, isZero = false;

        if( varA % 2 == 0 && varA != 0){
            chkA = true;
        }else if( varA % 2 != 0 && varA != 0){
            chkA = false;
        }else{
            chkA = false;
            isZero = true;
        }

        System.out.printf("number %d is %s" + "\n", varA, (chkA)?"Even":(isZero)?"Zero":"Odd");

        jvIn.close();
    }
}
