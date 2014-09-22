import java.util.Random;
/*
JAVA PROGRAM
*   @author :  Gaurav Deshmukh
*                       The University of Texas at Tyler
*                       Computer Science 
* Assignment No: 3 
* Operating Systems COSC 5330-01 
* Simulation of Memory Management 
* Virtual to Physical Address Translation
* A system has a 20 bit virtual address space, 16 bits of physical 
* address space, with a 4-KB page size. Write a program that that reads a 
* virtual address in decimal calculates the page number, and maps it to the 
* corresponding physical address.
 */

/**
 *
 * @author Gaurav
 */
public class VirtualtoPhysicalAdd {
    
    public static void main(String args[]){
 
     /*Physical Memory simulation as array having 16 rows ie. frames*/   
     int [] physicalmemory;
     int frame=0;
     /* 4 KB page size , so the 2^12 = 4096 = 4KB , each word = 12 bit*/
     int word_size =12;
     physicalmemory = new int[16];
 
     for (int i=0 ; i<100; i++)
     {
        /*Random number generator object */
        Random randnum = new Random();  
        
        /* Variable to store virtual address & physical address */
        int virtualadd;
        int physicaladd;
        /* Flag true => Address present in memory*/
        boolean flag=false;
   
        /*Since the virtual address is 20bit ie. 2^20 = 1048576*/
        virtualadd = randnum.nextInt(1048576);
        
        /* Each word in page is 12 bit  */
        int page_entry_size = 12; 
        
        System.out.println("Virtual Address :" + virtualadd);
        
        //System.out.println("Virtual Address in Hex :" + Integer.toHexString(virtualadd));
        
        /* To get higher 8 bits of virtual address masking with 0xFF000 and shifting by word size */
        int page_no = (virtualadd & 0xff000) >> page_entry_size;
        System.out.println("Page No:" + page_no);
        /* To get 12 bits of virtual address masking with 0x00FFF*/
        int word = (virtualadd & 0x00fff);
        System.out.println("Word No:" + word);
        
        /* Till the frames get filled up */
        if(frame!=16)
        {
            /* Checks for virtual address in memory*/
                for(int k=0 ; k<physicalmemory.length ;k++)
                {
                    if(physicalmemory[k]==virtualadd)
                    {
                        frame = k;
                        flag=true;
                    }
                }
                
                /*If found in memory prints the physical address*/
                if(flag==true)
                {
                    int frameno = (frame & 0x000ff) << word_size;
                    physicaladd = frameno + word;
                    System.out.println("Physical Address :" + physicaladd);
                    System.out.println("Frame No :" + frame);
                    System.out.println("Word No :" + word);
                    System.out.println("");   
                }
                /*If not in memory , stores it in memory and prints new physical address*/
                else
                {
                    flag=false;
                    physicalmemory[frame]= virtualadd;
                    int frameno = (frame & 0x000ff) << word_size;
                    physicaladd = frameno + word;
                    System.out.println("Physical Address :" + physicaladd);
                    System.out.println("Frame No :" + frame);
                    System.out.println("Word No :" + word);
                    System.out.println("Page Fault");
                    System.out.println("");
                    frame++;
                }
            }
           else
            {
                frame=0;
            }
        
     }
   }
}   
