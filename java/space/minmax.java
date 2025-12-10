import java.util.Scanner;

public class minmax {
    public static void main(String[]arg){
        Scanner jvin = new Scanner(System.in);
        int lenge = jvin.nextInt();
        int thenumber, minni = 2000000000, maxi = -2000000000;
        for(int i=0;i<lenge;i++){
            thenumber = jvin.nextInt();
                if(i==0){
                    minni = thenumber;
                    maxi = thenumber;
                    continue;
                }
                if( maxi <thenumber ) {
                    maxi = thenumber;
                }
                if( minni >thenumber ) {
                    minni = thenumber;
                }
        }
        jvin.close();
        System.out.printf("%d\n%d\n", minni, maxi);
    }
}