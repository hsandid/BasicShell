import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;

/*
|-----------------------------------|
|------------Basic Shell------------|
|-----------subtract.java-----------|
|-----------------------------------|
|>> Role : Performs a subtraction of|
| two provided integer values       |
|>> Shell Command : 'subtract'.     |
|>> Arguments : Two integer Values. |
|>> Pipe Support : Input Only       |
\-----------------------------------/
*/

class subtract {

    // Main Function

    public static void main(String args[]) {

        // Argument passed by the shell is either 'nopipe' or 'pipeout'
        // If 'nopipe' : No arguments needed when launching the program. The user inputs the two integer values when prompted by the program.
        // If 'pipein' : Arguments come from the output of another program. The two integer values are read from stdout.

        if (args[0].equals("nopipe")) {

            // Prompt the user to enter two integers, check the validity of the user input, and print out the result of their subtraction

            int v1 = 0;
            int v2 = 0;
            boolean v1_correct = false;
            boolean v2_correct = false;

            while (!v1_correct) {
                System.out.println("Input first Value");
                String val1 = System.console().readLine();

                if (val1.matches("^[+-]?\\d+$")) {
                    v1_correct = true;
                    v1 = Integer.valueOf(val1);

                } else {
                    System.out.println("Not a number!\n");
                }
            }

            while (!v2_correct) {
                System.out.println("Input second Value");
                String val2 = System.console().readLine();

                if (val2.matches("^[+-]?\\d+$")) {
                    v2_correct = true;
                    v2 = Integer.valueOf(val2);

                } else {
                    System.out.println("Not a number!\n");
                }
            }
			
            System.out.println(String.valueOf(v1) + " - " + String.valueOf(v2) + " = " + String.valueOf(v1 - v2));

        } else if (args[0].equals("pipein")) {

            // Read from stdout, convert strings to the corresponding integer values, and print out the result of their subtraction
            // !!! WARNING !! : It seems like this method only supports integer values which are in the 0-9 range. Any input taking more than one-digit will cause issues.

            try {
                BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
                String mvalue = in .readLine();
                int x = Integer.valueOf(mvalue.charAt(0)) - 48;
                int y = Integer.valueOf(mvalue.charAt(2)) - 48;
                System.out.println(String.valueOf(x) + " - " + String.valueOf(y) + " = " + String.valueOf(x - y));

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}