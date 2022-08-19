package cz.cvut.fel.pjv;

import java.util.Scanner;
import java.text.DecimalFormat;
import java.math.BigDecimal;

public class Lab01 {
    Scanner scanner = new Scanner(System.in);
    public void start(String[] args) {
       
        int operation = choose_operation();
        
        double operand1 = 0, operand2 = 0, result = 0;
        char operation_type = 0;
        
        if(operation == 1){
            operation_type = '+';
            operand1 = ask_for_operand1(operation_type);
            operand2 = ask_for_operand2(operation_type);
            result = compute_sum(operand1, operand2);
        } else if(operation == 2){
            operation_type = '-';
            operand1 = ask_for_operand1(operation_type);
            operand2 = ask_for_operand2(operation_type);
            result = compute_substr(operand1, operand2);
        } else if(operation == 3){
            operation_type = '*';
            operand1 = ask_for_operand1(operation_type);
            operand2 = ask_for_operand2(operation_type);
            result = compute_mult(operand1, operand2);
        } else if(operation == 4){
            operation_type = '/';
            operand1 = ask_for_operand1(operation_type);
            operand2 = ask_for_operand2(operation_type);
            if (operand2 == 0){
                System.err.println("Pokus o deleni nulou!");
                return;
            }
            result = compute_div(operand1, operand2);
        } else {
            System.err.println("Chybna volba!");
            return;
        }
        
        BigDecimal new_operand1 = turn_to_BigDecimal(operand1);
        BigDecimal new_operand2 = turn_to_BigDecimal(operand2);
        BigDecimal new_result = turn_to_BigDecimal(result);
        
        int fract_digits = fract_part_len();
        if(fract_digits < 0){
            System.err.println("Chyba - musi byt zadane kladne cislo!");
            return;
        }
        
        DecimalFormat dec_f = new DecimalFormat();
        dec_f.setMinimumFractionDigits(fract_digits);
        dec_f.setMaximumFractionDigits(fract_digits);
        dec_f.setGroupingUsed(false);
        
        System.out.printf("%s %c %s = %s\n", dec_f.format(new_operand1), operation_type, dec_f.format(new_operand2), dec_f.format(new_result));    
   }
   
    int choose_operation(){
       System.out.println("Vyber operaci (1-soucet, 2-rozdil, 3-soucin, 4-podil):");
       int operation = scanner.nextInt();
       return operation;
    }
    
    double ask_for_operand1(char operation_type){
        double operand1 = 0;
        if(operation_type == '+'){
            System.out.println("Zadej scitanec: ");
            operand1 = scanner.nextDouble();
        } else if(operation_type == '-'){
            System.out.println("Zadej mensenec: ");
            operand1 = scanner.nextDouble();
        } else if(operation_type == '*'){
            System.out.println("Zadej cinitel: ");
            operand1 = scanner.nextDouble();
        } else if(operation_type == '/'){
            System.out.println("Zadej delenec: ");
            operand1 = scanner.nextDouble();
        }
        return operand1;
    }
    
    double ask_for_operand2(char operation_type){
        double operand2 = 0;
        if(operation_type == '+'){
            System.out.println("Zadej scitanec: ");
            operand2 = scanner.nextDouble();
        } else if(operation_type == '-'){
            System.out.println("Zadej mensitel: ");
            operand2 = scanner.nextDouble();
        } else if(operation_type == '*'){
            System.out.println("Zadej cinitel: ");
            operand2 = scanner.nextDouble();
        } else if(operation_type == '/'){
            System.out.println("Zadej delitel: ");
            operand2 = scanner.nextDouble();
        }
        return operand2;
    }
    
    double compute_sum(double operand1, double operand2){
        double sum = operand1 + operand2;
        return sum;
    }
    
    double compute_substr(double operand1, double operand2){
        double difference = operand1 - operand2;
        return difference;
    }
    
    double compute_mult(double operand1, double operand2){
        double product = operand1 * operand2;
        return product;
    }
    
    double compute_div(double operand1, double operand2){
        double quotient = operand1 / operand2;
        return quotient;
    }
    
    int fract_part_len(){
        System.out.println("Zadej pocet desetinnych mist: ");
        int fract_digits = scanner.nextInt();
        return fract_digits;
    }
    
    BigDecimal turn_to_BigDecimal(double operand){
        BigDecimal tmp_var = new BigDecimal(operand);
        return tmp_var;
    }
}
