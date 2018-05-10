package view;

import java.util.LinkedList;

import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-21
 */
public class ElevationView extends Pane
{
	private LinkedList<Double> elevationValues;
	private double maxElevation;

	public void initializeView() 
	{
		elevationValues = new LinkedList<>();

		// Add vertical grids
		for (int i = 50; i <= 499; i += 50)
		{
			Line line = new Line(i, 1, i, 149);
			line.setStroke(Color.BLACK);
			line.getStrokeDashArray().addAll(2d);
			line.setStrokeWidth(0.3);

			getChildren().add(line);
		}

		// Add horizontal grids
		for (int i = 50; i <= 149; i += 50)
		{
			Line line = new Line(1, i, 499, i);
			line.setStroke(Color.BLACK);
			line.getStrokeDashArray().addAll(2d);
			line.setStrokeWidth(0.3);

			getChildren().add(line);
		}

		getStyleClass().add("bordered-box");
		setPrefSize(500, 150);
	}

	public void setElevation(double elevation)
	{
		// Remove existing lines from gui (there are 11 (dashed) lines from the beginning) 
		if (elevationValues != null)
			getChildren().remove(11, 11+elevationValues.size());

		double previousPixelValue;
		if (elevationValues.size() == 0)
			previousPixelValue = getPixelValue(0);
		else
			previousPixelValue = getPixelValue(elevationValues.getFirst());

		if (elevationValues.size() == 10)
			elevationValues.removeFirst();

		elevationValues.addLast(elevation);

		int i = 1;
		for (double meter : elevationValues) 
		{
			// Convert elevation to pixel value
			Line line = new Line(i, previousPixelValue, i+50, previousPixelValue = getPixelValue(meter));
			line.setStroke(Theme.getMainBrandColor());
			line.setStrokeWidth(2);

			getChildren().add(line);	
			
			i += 50;
		}
	}

	/** Convert meters to pixels */
	private double getPixelValue(double meters) 
	{
		double pixelsPerMeter = 150/maxElevation;
		return 150-(meters*pixelsPerMeter);
	}

	public void setMaxElevation(double d) 
	{
		maxElevation = d;
	}
}
