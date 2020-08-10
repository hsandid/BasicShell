import java.util.Scanner;
import java.io.BufferedWriter;
import java.io.File;
import java.io.OutputStreamWriter;


class ls {

    public static void main(String args[]) {
        if (args[0].equals("nopipe")) {
            String[] pathnames;
            File f = new File(ls.class.getProtectionDomain().getCodeSource().getLocation().getPath());
            pathnames = f.list();
			
            for (String pathname: pathnames) {

                System.out.println(pathname);
            }
			
        } else if (args[0].equals("pipeout")) {
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