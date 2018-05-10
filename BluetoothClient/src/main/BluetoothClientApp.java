package main;

import java.util.Locale;

import controller.Controller;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import view.BluetoothClientView;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-21
 */
public class BluetoothClientApp extends Application
{
	public static void main(String[] args)
	{
		launch(args);
	}

	@Override
	public void start(Stage stage) throws Exception 
	{
		Locale.setDefault(new Locale("en", "US"));
		BluetoothClientView bluetoothClientView = new BluetoothClientView();
		
		Controller controller = new Controller(bluetoothClientView);
		controller.initializeView();

		stage.setTitle("");
		
		Scene scene = new Scene(bluetoothClientView, 1040, 718);
		scene.getStylesheets().add("files/stylesheet.css");
		
		stage.setScene(scene);
		
		try {
			stage.getIcons().add(new Image("/files/icon.png"));
		} 
		catch (IllegalArgumentException e) {
			// Do nothing if file path is invalid  	
		}

		stage.setResizable(false);
		stage.show();

		stage.setOnCloseRequest(e -> {
			System.exit(0);
		});
	}
}
