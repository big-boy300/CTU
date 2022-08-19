package cz.cvut.fel.pjv;

import java.util.Arrays;
import java.util.Scanner;

public class Lab02 {

    Scanner scanner = new Scanner(System.in);

    /**
     * Calculate the statistics of a numerical sequence.
     */
    public void homework(String[] args) {
        int line_num = 0;
        String str;
        double[] input_arr = new double[10];

        int i = 0;
        double sum = 0;
        double arithmetic_average = 0;
        double arr_val = 0;
        double std_dev = 0;
        for (i = 0; i <= 10; ++i) {
            if (scanner.hasNext()) {
                str = scanner.next();
                line_num++;
                if (i == 10) {
                    i = 0;
                    Arrays.fill(input_arr, 0);
                }
                if (TextIO.isDouble(str)) {
                    input_arr[i] = Double.parseDouble(str);
                    sum += input_arr[i];
                    if (i == 9) {
                        arithmetic_average = sum / 10;
                        for (int j = 0; j < 10; ++j) {
                            arr_val += Math.pow((input_arr[j] - arithmetic_average), 2);
                        }
                        arr_val /= input_arr.length;
                        std_dev = Math.sqrt(arr_val);
                        System.out.printf("%2d %.3f %.3f\n", i + 1, arithmetic_average, std_dev);
                        sum = 0;
                        std_dev = 0;
                        arr_val = 0;
                    }
                } else {
                    System.err.printf("A number has not been parsed from line %d\n", line_num);
                    scanner.nextLine();
                    i--;
                }
            } else {
                System.err.println("End of input detected!");
                if (i > 1 && i < 10) {
                    arithmetic_average = sum / i;
                    for (int j = 0; j < i; ++j) {
                        arr_val += Math.pow((input_arr[j] - arithmetic_average), 2);
                    }
                    arr_val /= i;
                    std_dev = Math.sqrt(arr_val);
                    System.out.printf("%2d %.3f %.3f\n", i, arithmetic_average, std_dev);
                }
                break;
            }
        }
    }
}
