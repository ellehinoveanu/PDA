package main;


import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Scanner;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class RunMe {

	public static void main(String args[]) throws InterruptedException, ExecutionException, IOException {
		
		int rows = 0;
		
		ArrayList<ArrayList<Integer>> firstMatrix = new ArrayList<ArrayList<Integer>>();
		ArrayList<ArrayList<Integer>> secondMatrix = new ArrayList<ArrayList<Integer>>();
		ArrayList<ArrayList<Integer>> resultMatrix = new ArrayList<ArrayList<Integer>>();
		
		
		ArrayList<Task> collection = new ArrayList<Task>( );
		
		Scanner input = null;
		input = new Scanner(new File("file1.txt"));			
		while(input.hasNextLine()) {
			rows++;
		    Scanner colReader = new Scanner(input.nextLine());
		    ArrayList<Integer> element = new ArrayList<Integer>();
		    while(colReader.hasNextInt()) {
		        element.add(colReader.nextInt());	    
		    }
		    firstMatrix.add(element);
		}
		
		input = new Scanner(new File("file2.txt"));		
		while(input.hasNextLine()) {
		    Scanner colReader = new Scanner(input.nextLine());
		    ArrayList<Integer> element = new ArrayList<Integer>();
		    while(colReader.hasNextInt()) {
		        element.add(colReader.nextInt());	    
		    }
		    secondMatrix.add(element);
		}
		
		
		for(int i = 0; i < rows; i++){
			ArrayList<Integer> el = new ArrayList<Integer>();
			for(int j = 0; j < firstMatrix.get(0).size(); j++){
				el.add(0);
			}
			 resultMatrix.add(el);
		}
		
		
		for(int i = 0; i < rows ; i++){
			Task task = new Task(i, firstMatrix, secondMatrix, resultMatrix);
			collection.add(task);
		}
		
		for(int i=0; i < collection.size();i++)
		{
			collection.get(i).run();
		}

		
		Writer wr  = new FileWriter("file3.txt");
		for(ArrayList item: resultMatrix){
			for(Object item2: item){
				wr.write(item2.toString() + " ");
			}
			wr.write(" ");
		}
		System.out.print("Done!");
		wr.close();
	}
}

