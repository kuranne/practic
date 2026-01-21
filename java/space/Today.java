public class Today {
    private enum Day {
        Monday,
        Tuesday,
        Wendesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    }

    public static void main(String[] args) {
        Day today = Day.Sunday;
        String print;
        switch (today) {
            case Day.Monday -> print = "Monday";
            case Day.Tuesday -> print = "Tuesday";
            case Day.Wendesday -> print = "Wendesday";
            case Day.Thursday -> print = "Thursday";
            case Day.Friday -> print = "Friday";
            case Day.Saturday -> print = "Saturday";
            case Day.Sunday -> print = "Sunday";
            default -> print = "Nusday";
        }

        System.out.printf("Today is %s\n", print);
    }
}
