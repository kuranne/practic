// Black Jack by Kuramais
import java.util.*;

public class BlackJack {
    private static String winner = null;
    private static int turn = 1;
    private static Scanner scanner = new Scanner(System.in);
    private static Random random = new Random();

    static class Hand {
        private List<Integer> numbers;
        private boolean candidate;

        public Hand(int number) {
            this.numbers = new ArrayList<>();
            this.numbers.add(number);
            this.candidate = true;
        }

        public void draw() {
            int pick = random.nextInt(9) + 2;
            this.numbers.add(pick);
        }

        public boolean chkIfExceed() {
            int sum = getSum();
            this.candidate = sum <= 21;
            return sum > 21;
        }

        public boolean chkBot() {
            int sum = getSum();
            if (sum < 14) {
                return false;
            } else {
                return sum > 17;
            }
        }

        public int getSum() {
            return numbers.stream().mapToInt(Integer::intValue).sum();
        }

        public List<Integer> getNumbers() {
            return numbers;
        }

        public boolean isCandidate() {
            return candidate;
        }

        public int getLastCard() {
            return numbers.get(numbers.size() - 1);
        }
    }

    public static void main(String[] args) {
        Hand yourHand = new Hand(random.nextInt(9) + 2);
        Hand opHand = new Hand(random.nextInt(9) + 2);

        System.out.println("\n>>> d for draw, r for reveal <<<");

        while (true) {
            System.out.println("\nturn " + turn);
            System.out.println("yours: " + yourHand.getNumbers());
            System.out.print("sel :");
            String input = scanner.nextLine().trim().toLowerCase();

            switch (input) {
                case "d":
                    yourHand.draw();
                    System.out.println("U draw " + yourHand.getLastCard() + "!");
                    if (opHand.chkBot()) {
                        break;
                    } else {
                        opHand.draw();
                    }
                    break;
                case "r":
                    if (!opHand.chkBot()) {
                        opHand.draw();
                    }
                    break;
                default:
                    System.out.println("error, I will draw for you :)");
                    yourHand.draw();
                    System.out.println("U draw " + yourHand.getLastCard() + "!");
                    if (opHand.chkBot()) {
                        break;
                    } else {
                        opHand.draw();
                    }
                    break;
            }

            if (yourHand.chkIfExceed() || opHand.chkIfExceed()) {
                break;
            }
            turn++;
        }

        if (winner == null) {
            yourHand.chkIfExceed();
            opHand.chkIfExceed();

            if (!yourHand.isCandidate() || !opHand.isCandidate()) {
                if (yourHand.isCandidate()) {
                    winner = "You";
                } else {
                    winner = "Bot";
                }
            } else {
                if (yourHand.getSum() > opHand.getSum()) {
                    winner = "You";
                } else if (yourHand.getSum() < opHand.getSum()) {
                    winner = "Bot";
                } else {
                    winner = "Draw";
                }
            }
        }

        int winnerScore = winner.equals("Bot") ? opHand.getSum() : yourHand.getSum();
        int loserScore = winner.equals("Bot") ? yourHand.getSum() : opHand.getSum();
        
        System.out.println("winner is " + winner + ", with score " + winnerScore + " : " + loserScore);
        
        scanner.close();
    }
}