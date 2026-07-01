package friend;

public class Friend {
    public static int friendLen;
    private String name;

    public Friend(String name) {
        this.name = name;
        friendLen++;
    }

    public String Name() {
        return name;
    }
}
