import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.lang.Math;


        class generate
        { 
        
            public static void main(String args[]) 
            { 
                
                if(args[0].equals("nopipe"))
                {
                double rd = Math.random();
	            rd = rd * 11 ;
                int randomInt = (int) rd;
                System.out.println(randomInt);

                rd = Math.random();
	            rd = rd * 10 ;
                randomInt = (int) rd;
                System.out.println(randomInt);
                }
                else if(args[0].equals("pipeout"))
                {
                double rd = Math.random();
	            rd = rd * 11 ;
                int randomInt1 = (int) rd;
               

                rd = Math.random();
	            rd = rd * 10 ;
                int randomInt2 = (int) rd;

                try {    
                    BufferedWriter log = new BufferedWriter(new OutputStreamWriter(System.out));
                    log.write(String.valueOf(randomInt1)+" "+String.valueOf(randomInt2));
                    log.flush();
                  }
                  catch (Exception e) {
                    e.printStackTrace();
                  }
                

                }
                
            } 
        } 
        