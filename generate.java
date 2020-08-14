import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.lang.Math;

/*
|-----------------------------------|
|------------Basic Shell------------|
|-----------generate.java-----------|
|-----------------------------------|
|>> Role : Generates two random     |
|integer values                     |
|>> Shell Command : 'generate'.     |
|>> Arguments : None.               |
|>> Pipe Support : Output Only      |
\-----------------------------------/
*/

class generate {

    // Main Function

    public static void main(String args[]) {

        // Argument passed by the shell is either 'nopipe' or 'pipeout'
        // If 'nopipe' : Generated values will be displayed by the shell
        // If 'pipeout' : Generated values will be passed as arguments to another command using pipes

        if (args[0].equals("nopipe")) {

            // Generate two random integers in the [0,9] range and print them on the shell

            double rd = Math.random();
            rd = rd * 10;
            int randomInt = (int) rd;
            System.out.println(randomInt);
            rd = Math.random();
            rd = rd * 10;
            randomInt = (int) rd;
            System.out.println(randomInt);

        } else if (args[0].equals("pipeout")) {

            // Generate two random integers in the [0,9] range, convert them to strings, and pass them to stdout

            double rd = Math.random();
            rd = rd * 10;
            int randomInt1 = (int) rd;
            rd = Math.random();
            rd = rd * 10;
            int randomInt2 = (int) rd;
            try {
                BufferedWriter log = new BufferedWriter(new OutputStreamWriter(System.out));
                log.write(String.valueOf(randomInt1) + " " + String.valueOf(randomInt2));
                log.flush();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

    }
}