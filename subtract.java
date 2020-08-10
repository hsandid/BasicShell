import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Scanner;


class subtract 
{ 

    public static void main(String args[]) 
    { 
        
        if(args[0].equals("nopipe") )
                {
        //CASE 1 :Add regular user input
        int v1=0;
        int v2=0;
        
        boolean v1_correct=false;
        boolean v2_correct=false;
        while(!v1_correct)
        {
            System.out.println("Input first Value");
            String val1 = System.console().readLine();
        
        if (val1.matches("^[+-]?\\d+$"))
        {
            v1_correct=true;
            v1=Integer.valueOf(val1);
            
        }
        else
        {
            System.out.println("Not a number!\n");
        }
        }

        while(!v2_correct)
        {
            System.out.println("Input second Value");
            String val2 = System.console().readLine();
        
        if (val2.matches("^[+-]?\\d+$"))
        {
            v2_correct=true;
            v2=Integer.valueOf(val2);
            
        }
        else
        {
            System.out.println("Not a number!\n");
        }
        }

        System.out.println(String.valueOf(v1)+" - "+String.valueOf(v2)+" = "+String.valueOf(v1-v2));

        
    }
    else if(args[0].equals("pipein"))
    {
        try {
            //Receive two integers
            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

            String mvalue =in.readLine(); 

            int x = Integer.valueOf(mvalue.charAt(0)) - 48;
            int y = Integer.valueOf(mvalue.charAt(2))- 48;

            // System.out.println("X is "+String.valueOf(x)+"\n");
            // System.out.println("Y is "+String.valueOf(y)+"\n");
            System.out.println(String.valueOf(x)+" - "+String.valueOf(y)+" = "+String.valueOf(x-y));
        
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
    } 
} 
