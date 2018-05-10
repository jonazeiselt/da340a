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
public class ElevationInfoView extends VBox
{
	private Label elevationValueLabel;
	private DecimalFormat decimalFormat = new DecimalFormat("#.#####");

	public void initializeView()
	{		
		Label unitLabel = new Label("Unit: meter");
		unitLabel.getStyleClass().add("smaller-heading");
		
		Label heightStringLabel = new Label("Elevation:");
		elevationValueLabel = new Label(Double.toString(0));
		
		HBox elevationBox = new HBox(3);	
		elevationBox.getChildren().addAll(heightStringLabel, elevationValueLabel);
		
		getChildren().addAll(unitLabel, elevationBox);
		
		getStyleClass().add("dark-card");
		setAlignment(Pos.CENTER_LEFT);

		setPadding(new Insets(10,20,10,20));
		setPrefSize(500, 60);	
		setSpacing(3);
	}
	
	public void setElevation(double elevation)
	{
		elevationValueLabel.setText(decimalFormat.format(elevation));
	}
}
