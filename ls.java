import java.util.Scanner;
import java.io.BufferedWriter;
import java.io.File;
import java.io.OutputStreamWriter;

/*
|-----------------------------------|
|------------Basic Shell------------|
|--------------ls.java--------------|
|-----------------------------------|
|>> Role : Lists all files and      |
|directories in the folder where    |
|this program is currently located  |
|>> Shell Command : 'ls'.           |
|>> Arguments : None.               |
|>> Pipe Support : Output Only      |
\-----------------------------------/
*/

class ls {

    // Main Function

    public static void main(String args[]) {

        // Argument passed by the shell is either 'nopipe' or 'pipeout'
        // If 'nopipe' : List of files and directories will be displayed by the shell
        // If 'pipeout' : List of files and directories will be passed as arguments to another command using pipes

        if (args[0].equals("nopipe")) {

            //Fetches the names of all files and directories in the folder where the program is located, and prints them to shell

            String[] pathnames;
            File f = new File(ls.class.getProtectionDomain().getCodeSource().getLocation().getPath());
            pathnames = f.list();
			
            for (String pathname: pathnames) {

                System.out.println(pathname);
            }
			
        } else if (args[0].equals("pipeout")) {

            //Fetches the names of all files and directories in the folder where the program is located, and passes then to stdout

            String[] pathnames;
            File f = new File(ls.class.getProtectionDomain().getCodeSource().getLocation().getPath());
            pathnames = f.list();

            try {
                BufferedWriter log = new BufferedWriter(new OutputStreamWriter(System.out));

                for (String pathname: pathnames) {

                    log.write(pathname);
                }
                log.flush();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}