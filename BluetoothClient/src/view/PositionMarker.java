package view;

import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class PositionMarker extends StackPane
{
	public PositionMarker() 
	{
		Color markerColor = Theme.getMainBrandColor();
		
		Circle outerCircle = new Circle();
		outerCircle.setFill(Theme.getWhiteColor());
		outerCircle.setRadius(13);
		outerCircle.setStroke(markerColor);
		outerCircle.setStrokeWidth(2);
		
		Circle innerCircle = new Circle();
		innerCircle.setRadius(9);
		innerCircle.setFill(markerColor);
		
		setPrefSize(30, 30);
		getChildren().addAll(outerCircle, innerCircle);
	
		setOnMouseEntered(e -> {
			outerCircle.setRadius(14);
			innerCircle.setRadius(10);
		});
		
		setOnMouseExited(e -> {
			outerCircle.setRadius(13);
			innerCircle.setRadius(9);
		});
	}

	public int getRadius() 
	{
		return 15;
	}
}
