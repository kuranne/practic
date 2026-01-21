import friend.Friend;
import java.util.ArrayList;

public class NumOfFriend {
    public static void main(String[] args) {
        String[] names = {"Maisa", "Kuranne", "Nrokariw"};
        ArrayList<Friend> friends = new ArrayList<>();

        for (String name: names) {
            friends.add(new Friend(name));
        }

        System.out.printf("friend: %d\narray: %d\n", Friend.friendLen , friends.size());
    }
}
