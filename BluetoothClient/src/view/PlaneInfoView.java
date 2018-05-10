package view;

import java.text.DecimalFormat;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-21
 */
public class PlaneInfoView extends VBox
{
	private Label xValueLabel;
	private Label yValueLabel;
	
	private DecimalFormat decimalFormat = new DecimalFormat("#.#####");

	public void initializeView() 
	{
		Label unitLabel = new Label("Unit: meter");
		unitLabel.getStyleClass().add("smaller-heading");
		
		Label xStringLabel = new Label("x:");
		xValueLabel = new Label(Double.toString(0));

		HBox xBox = new HBox(3);
		xBox.getChildren().addAll(xStringLabel, xValueLabel);
		xBox.setPrefWidth(250);
		xBox.setAlignment(Pos.CENTER_LEFT);
		
		Label yStringLabel = new Label("y:");
		yValueLabel = new Label(Double.toString(0));

		HBox yBox = new HBox(3);
		yBox.getChildren().addAll(yStringLabel, yValueLabel);
		yBox.setPrefWidth(250);
		yBox.setAlignment(Pos.CENTER_LEFT);
		
		HBox xyBox = new HBox(10);
		xyBox.getChildren().addAll(xBox, yBox);
		
		getChildren().addAll(unitLabel, xyBox);
		
		getStyleClass().add("dark-card");
		setPadding(new Insets(10,20,10,20));
		setPrefSize(500, 60);
	}

	public void setPosition(double x, double y)
	{
		xValueLabel.setText(decimalFormat.format(x));
		yValueLabel.setText(decimalFormat.format(y));
	}
}
