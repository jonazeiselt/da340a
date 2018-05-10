package view;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.text.DecimalFormat;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-21
 */
public class BottomBarView extends HBox
{
	
	public void initializeView() 
	{
		ImageView imageView = new ImageView(new Image("/files/github.png"));
		imageView.setFitWidth(25);
		imageView.setPreserveRatio(true);
		
		Label label = new Label("Jonas Eiselt and Danial Mahmoud");
		label.getStyleClass().add("left-padding");
				
		setPadding(new Insets(17,40,0,40));
		getChildren().addAll(imageView, label);
		
		setOnMouseClicked(e -> {
			try {
				URI url = new URI("https://github.com/jonazeiselt/da340a");
		        java.awt.Desktop.getDesktop().browse(url);
			} 
			catch (URISyntaxException ioe) {
				ioe.printStackTrace();
			} catch (IOException ioe) {
				ioe.printStackTrace();
			}
		});
		
		getStyleClass().add("bar");
		setPrefSize(1040, 60);
	}

	public void setMouseValue(double xMetres, double yMetres) 
	{
		if (getChildren().size() > 2)
			getChildren().remove(2);
		
		DecimalFormat decimalFormat = new DecimalFormat("#.##");
		
		Label xLabel = new Label("x: " + decimalFormat.format(xMetres));
		Label yLabel = new Label("y: " + decimalFormat.format(yMetres));
		
		HBox labelBox = new HBox(10);
		labelBox.setPrefWidth(630);
		labelBox.setAlignment(Pos.BASELINE_RIGHT);
		labelBox.getChildren().addAll(xLabel, yLabel);
		
		getChildren().add(labelBox);
	}

	public void removeMouseValue() 
	{
		if (getChildren().size() > 2)
			getChildren().remove(2);
	}
}
