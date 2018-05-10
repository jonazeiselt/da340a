package model;

import java.util.Random;

import controller.Controller;

public class PositionGenerator implements Runnable 
{
	private Controller controller;
	private boolean isRunning;

	public PositionGenerator(Controller controller) 
	{
		this.controller = controller;
	}

	@Override
	public void run() 
	{
		isRunning = true;
		
		Random random = new Random();
		while (isRunning) 
		{			
			double planeMin = 0, planeMax = 4;
			double elevationMin = 0, elevationMax = 3;
			
			double x = planeMin + ((planeMax-planeMin)*random.nextDouble()); 
			double y = planeMin + ((planeMax-planeMin)*random.nextDouble()); 
			double z = elevationMin + ((elevationMax-elevationMin)*random.nextDouble()); 
			
			controller.setPosition(x, y, z);
			
			try {
				Thread.sleep(300);
			} 
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void terminate() 
	{
		isRunning = false;
	}
}
