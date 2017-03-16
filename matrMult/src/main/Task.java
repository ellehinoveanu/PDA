package main;

import java.util.ArrayList;
import java.util.concurrent.Callable;

public class Task implements Runnable {

	int x ;
	ArrayList<ArrayList<Integer>> firstMatrix;
	ArrayList<ArrayList<Integer>> secondMatrix;
	ArrayList<ArrayList<Integer>> resultMatrix;
	
	
	public Task(int index, ArrayList<ArrayList<Integer>> firstMatrix, ArrayList<ArrayList<Integer>> secondMatrix, ArrayList<ArrayList<Integer>> resultMatrix){
		this.x = index;
		this.firstMatrix = firstMatrix;
		this.secondMatrix = secondMatrix;
		this.resultMatrix = resultMatrix;
	}



	@Override
	public void run() {
		// TODO Auto-generated method stub
		for(int i = 0; i < secondMatrix.get(0).size(); i++){
			for(int j = 0; j < firstMatrix.get(0).size(); j++){
				resultMatrix.get(x).set(i, resultMatrix.get(x).get(i) + firstMatrix.get(x).get(j) * secondMatrix.get(j).get(i));
			}
		}
	}
}
