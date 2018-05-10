package view;

import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import other.PlaneViewListener;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-21
 */
public class PlaneMovementView extends Pane
{
	private static final double PIXELHEIGHT = 500;	
	private PositionMarker positionMarker;
	
	private PlaneViewListener planeViewListener;
	private double dimension;

	public PlaneMovementView(PlaneViewListener planeViewListener) 
	{
		this.planeViewListener = planeViewListener;
	}

	public void initializeView() 
	{			
		// Add vertical grids
		for (int i = 50; i <= 499; i += 50)
		{
			Line line = new Line(i, 1, i, 499);
			line.setStroke(Color.BLACK);
			line.getStrokeDashArray().addAll(2d);
			line.setStrokeWidth(0.3);

			getChildren().add(line);
		}

		// Add horizontal grids
		for (int i = 50; i <= 499; i += 50)
		{
			Line line = new Line(1, i, 499, i);
			line.setStroke(Color.BLACK);
			line.getStrokeDashArray().addAll(2d);
			line.setStrokeWidth(0.3);

			getChildren().add(line);
		}
		
		setOnMouseClicked(e -> 
		{
			double xMetres = getMeterValue(e.getX());
			double yMetres = getMeterValue(PIXELHEIGHT-e.getY());

			planeViewListener.setOnPlaneClicked(xMetres, yMetres);
		});
		
		setOnMouseExited(e -> {
			planeViewListener.setOnPlaneExited();
		});
		
		getStyleClass().add("bordered-box");
		setPrefSize(500, PIXELHEIGHT);
		setMinSize(500, PIXELHEIGHT);
	}

	public void setPosition(double x, double y) 
	{
		// Remove existing position marker
		if (positionMarker != null)
			getChildren().remove(positionMarker);

		positionMarker = new PositionMarker();
		getChildren().add(positionMarker);

		positionMarker.setLayoutX(getPixelValue(x)-positionMarker.getRadius());
		positionMarker.setLayoutY(PIXELHEIGHT-(getPixelValue(y)+positionMarker.getRadius()));
	}

	/** Convert meters to pixels */
	private double getPixelValue(double meters) 
	{
		double pixelsPerMeter = PIXELHEIGHT/dimension;
		return (meters*pixelsPerMeter);
	}
	
	/** Convert pixels to meters */
	private double getMeterValue(double pixels) 
	{
		double metersPerPixel = dimension/PIXELHEIGHT;
		return (pixels*metersPerPixel);
	}

	public void setMaxDimension(double d, double e) 
	{
		if (d >= e)
			dimension = d;
		else
			dimension = e;
	}
}
