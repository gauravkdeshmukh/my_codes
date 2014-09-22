/*
*@author : Gaurav Deshmukh
*          The University of Texas at Tyler
*          Computer Science 
* Assignment No: 1 
* Operating Systems COSC 5330-01 
* Simulation of Producer - Consumer using Semaphores
*/
//List of various imports
import java.util.Random;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

//Main class
public class Semsp{

//Limit for Given Buffer
    private int LIMIT = 80; 
//Queue is used as buffer
    private static BlockingQueue<Integer> array = new ArrayBlockingQueue<>(80);
//producer thread loop count 
    int pc=0;
//consumer thread loop count
    int cc=0;
//randon class object for getting random values to insert in Queue
    Random random = new Random();
// mod is the integer which will decide when to print buffer 
    int mod;
// Flag for Availabilty of items 
    volatile boolean ITM_AVL = true; 
// Flag for Space Availability    
    volatile boolean SPC_AVL = true; 
// Flag for Buffer Availability
    volatile boolean BUF_AVL = true; 
//No of producing units
    int n;  
//No of consuming units
    int m; 
// wait signal for flags ; in binary S=S-1;
    public boolean waitSem(){ 
        return false;	
    }
 // Green signal for flags; in binary S=S+1; 
    public boolean signalSem(){
        return true;
    }

    
        
// Gets mod for printing the buffer at right time
    public int getMod(){
        if (n > m){
                    mod = n;
        }
        else{
                    mod = m;
        }
        return mod;
    }
// The method for producer thread        
    public void producer() throws InterruptedException{
        while(true){
//System.out.println("Producer ? Space Available :" + SPC_AVL);
//checks if space available is set
            if(SPC_AVL){
// repeat until buffer is full
                if (array.size()!=80){
                    BUF_AVL = waitSem();
//System.out.println("Producer -> Buffer Available :" + BUF_AVL);
                    ITM_AVL = waitSem(); 
//System.out.println("Producer -> Item Available :" + ITM_AVL);
//creatiton of value
                    int val = random.nextInt(1000);
// insert value into Queue
                    array.put(val);
                    //System.out.print(" " + val);
                    pc++;
                    if (pc % getMod() == 0){
                        System.out.println("\tBuffer Size:" + array.size()); 
                    }
// After insertion set item available                
                    ITM_AVL = signalSem(); 
                    try {
//set buffer available ; as producer threads finishes
                            if (pc % getMod() == 0)    
                                System.out.println("" + array);
                            BUF_AVL=signalSem();
                            Thread.sleep(100);
                        } 
                    catch (InterruptedException e) {
                                    e.printStackTrace();
                        }					
                    }       
//if buffer is full; Release buffer & wait producer thread
            BUF_AVL = signalSem();
            Thread.sleep(100);
// As the program runs infinitely to hold at some point
//so after 1000 iterations of threads 
// program will exit forcefully with exit code 1
            if(pc > 1000)
                System.exit(1);
            }
        }
    }
    
        public void consumer(){
            while(true){
//System.out.println("Consumer ? Item Available :" + ITM_AVL);
// checks if item available is set
                if(ITM_AVL){     
                    BUF_AVL=waitSem();
                    if(array.size()==0){
                        try {
                            BUF_AVL = signalSem();
                            System.out.println("After Consumption:" + array);
                            Thread.sleep(100);
                        } 
                        catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }     
//System.out.println("Consumer -> Buffer Available :" + BUF_AVL);
                    try{      
                        int val;
// Remove value from the buffer 
                        val = array.take();
                        System.out.println("Consume:" + val);
                      }
             catch (InterruptedException ex) {
              Logger.getLogger(Semsp.class.getName()).log(Level.SEVERE,null,ex);
                      }
                    SPC_AVL = signalSem();                              
// System.out.println("Consumer -> Space Available :" + SPC_AVL);
                    try {
                        BUF_AVL = signalSem();
                        Thread.sleep(100);
                      } 
                    catch (InterruptedException e){
                        e.printStackTrace();
                      }	
//if buffer is empty; Release buffer & wait consumer thread
                    BUF_AVL = signalSem();
                    try {
                            Thread.sleep(100);
// As the program runs infinitely to hold program at some point
// after 1000 iterations of threads 
// program will exit forcefully with exit code 1
                        if(cc > 1000)
                            System.exit(1);
                      } 
            catch (InterruptedException ex) {
              Logger.getLogger(Semsp.class.getName()).log(Level.SEVERE,null,ex);
                      }
                }      
            }
        }   
// Simualtion function for creating and calling threads        
    public synchronized void simulate(){
        Thread[] producerthreads = new Thread[n];
        for (int i = 0; i < producerthreads.length; i++) {
            producerthreads[i] = new Thread(new Runnable() {
            @Override
                public void run() {
                try {
                        // some code to run in parallel
                        producer();
                 }
              catch (InterruptedException ex) {
              Logger.getLogger(Semsp.class.getName()).log(Level.SEVERE,null,ex);
                 }
            }
          });
            producerthreads[i].start();
        }
        Thread[] consumerthreads = new Thread[m];
        for (int i = 0; i < consumerthreads.length; i++) {
            consumerthreads[i] = new Thread(new Runnable() {
            @Override
                public void run() {
                    // some code to run in parallel
                        consumer();
            }
          });
        consumerthreads[i].start();
        }
        try{
            for(int i=0 ; i<n ; i++){
                producerthreads[i].join();    
                }
            for(int i=0 ; i<m ; i++){
            consumerthreads[i].join();
            }
          }
        catch(InterruptedException e){
            e.printStackTrace();
        }		
    }
    
// Main function 
    public static void main(String args[]){
        Semsp obj;
        try (Scanner inp = new Scanner(System.in)){
            obj = new Semsp();
            System.out.println("Enter no of Producer Threads: ");
            obj.n = inp.nextInt();
            System.out.println("Enter no of Consumer Threads: ");
            obj.m = inp.nextInt();
            System.out.print("Simulation of " + obj.n +"Producers and");
            System.out.println( ""+ obj.m + "Consumers");
          }
        obj.simulate();
        System.out.println("");
        }
}

