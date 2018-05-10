package view;

import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

public class DialogPresenter 
{
	public static void show(AlertType alertType, String message) 
	{
		String title = "";
		if (alertType == AlertType.INFORMATION)
			title = "Information Dialog";
		else if (alertType == AlertType.WARNING)
			title = "Warning Dialog";
		else if (alertType == AlertType.ERROR)
			title = "Error Dialog";
		
		Alert alert = new Alert(alertType);
		alert.setTitle(title);
		alert.setHeaderText(null);
		alert.setContentText(message);

		alert.showAndWait();
	}
}
