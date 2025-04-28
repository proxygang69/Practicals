import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class FractionalKnapsack {

    static class Item {
        int profit, weight;

        Item(int x, int y) {
            this.profit = x;
            this.weight = y;
        }
    }

    static class ComparatorByRatio implements Comparator<Item> {
        @Override
        public int compare(Item a, Item b) {
            double ratio1 = (double) a.profit / a.weight;
            double ratio2 = (double) b.profit / b.weight;
            if (ratio1 < ratio2) {
                return 1;  // Return 1 if ratio1 is smaller (for descending order)
            } else if (ratio1 > ratio2) {
                return -1; // Return -1 if ratio1 is greater (for descending order)
            } else {
                return 0;
            }
        }
    }

    static double fractionalKnapsack(int w, Item[] arr, int n) {
        Arrays.sort(arr, new ComparatorByRatio()); // Sort items by profit/weight ratio

        int currentWeight = 0;
        double finalProfit = 0.0;

        for (int i = 0; i < n; i++) {
            if (currentWeight + arr[i].weight <= w) {
                // Take the full item
                currentWeight += arr[i].weight;
                finalProfit += arr[i].profit;
                System.out.println("Taking full item " + (i+1) + " with profit: " + arr[i].profit + " and weight: " + arr[i].weight);
            } else {
                // Take the fraction of the remaining item
                int remainingCapacity = w - currentWeight;
                finalProfit += arr[i].profit * ((double) remainingCapacity / arr[i].weight);
                System.out.println("Taking fractional part of item " + (i+1) + " with profit: " + (arr[i].profit * ((double) remainingCapacity / arr[i].weight))) ;
                break;
            }
        }

        return finalProfit;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of items:");
        int n = sc.nextInt();
        Item[] arr = new Item[n];

        // Input the profit and weight of items
        for (int i = 0; i < n; i++) {
            System.out.println("Enter profit and weight for item " + (i + 1) + ": ");
            int profit = sc.nextInt();
            int weight = sc.nextInt();
            arr[i] = new Item(profit, weight);
        }

        System.out.println("Enter weight capacity: ");
        int w = sc.nextInt();

        FractionalKnapsack obj = new FractionalKnapsack();
        double ans = obj.fractionalKnapsack(w, arr, n);
        System.out.println("Maximum profit is: " + ans);

        sc.close();
    }
}
