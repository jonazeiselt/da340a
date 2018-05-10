package view;

import java.io.IOException;
import java.util.ArrayList;

import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import other.ControlPanelViewListener;
import view.components.DoubleField;

import javax.bluetooth.BluetoothStateException;
import javax.bluetooth.RemoteDevice;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-22
 */
public class ControlPanelView extends VBox
{
	private ControlPanelViewListener controlPanelViewListener;

	private Button connectButton;
	private Button applyButton;

	private ChoiceBox<String> choiceBox;

	private DoubleField xTextField;
	private DoubleField yTextField;
	private DoubleField zTextField;

	private Button searchDevicesButton;

	public ControlPanelView(ControlPanelViewListener controlPanelViewListener) 
	{
		this.controlPanelViewListener = controlPanelViewListener;
	}

	public void initializeView() 
	{
		Label unitLabel = new Label("Unit: meter");
		unitLabel.getStyleClass().addAll("smaller-heading", "dark-font");

		Label xLabel = new Label("Max x");	
		xLabel.getStyleClass().addAll("dark-font", "small-heading");

		xTextField = new DoubleField(0);
		xTextField.getStyleClass().add("dark-font");
		xTextField.setPrefWidth(250);

		VBox xBox = new VBox(3);
		xBox.getChildren().addAll(xLabel, xTextField);

		Label yLabel = new Label("Max y");
		yLabel.getStyleClass().addAll("dark-font", "small-heading");

		yTextField = new DoubleField(0);
		yTextField.getStyleClass().add("dark-font");
		yTextField.setPrefWidth(250);

		VBox yBox = new VBox(3);
		yBox.getChildren().addAll(yLabel, yTextField);

		Label zLabel = new Label("Max elevation");	
		zLabel.getStyleClass().addAll("dark-font", "small-heading");

		zTextField = new DoubleField(0);
		zTextField.getStyleClass().add("dark-font");
		zTextField.setPrefWidth(250);

		VBox zBox = new VBox(3);
		zBox.getChildren().addAll(zLabel, zTextField);

		HBox xyzBox = new HBox(10);
		xyzBox.getChildren().addAll(xBox, yBox, zBox);

		VBox xyzVBox = new VBox(3);
		xyzVBox.getChildren().addAll(unitLabel, xyzBox);

		applyButton = new Button("Apply");
		applyButton.setPrefSize(500, 50);
		applyButton.getStyleClass().add("apply");
		applyButton.setOnMouseClicked(e -> 
		{
			double x = xTextField.getDouble();
			double y = yTextField.getDouble();
			double z = zTextField.getDouble();

			controlPanelViewListener.setOnApplyClicked(x, y, z);
		});

		Label bluetoothLabel = new Label("Search Bluetooth devices");	
		bluetoothLabel.getStyleClass().addAll("dark-font", "small-heading");

		choiceBox = new ChoiceBox<>();
		choiceBox.setPrefWidth(250);

		searchDevicesButton = new Button("Search");
		configureSearchButton();

		HBox selectDeviceBox = new HBox(10);
		selectDeviceBox.getChildren().addAll(choiceBox, searchDevicesButton);

		VBox bluetoothBox = new VBox(3);
		bluetoothBox.getChildren().addAll(bluetoothLabel, selectDeviceBox);
		bluetoothBox.setPadding(new Insets(10,0,16,0));

		connectButton = new Button("Connect");
		configureConnectButton();

		getChildren().addAll(xyzVBox, applyButton, bluetoothBox, connectButton);
		setSpacing(10);
		setMaxWidth(500);
	}

	private void configureSearchButton() 
	{
		searchDevicesButton.setPrefSize(250, 50);
		searchDevicesButton.getStyleClass().add("search");
		searchDevicesButton.setOnMouseClicked(e -> 
		{	
			Thread thread = new Thread(() ->  
			{
				Platform.runLater(() -> 
				{
					if (choiceBox.getItems().size() > 0)
						choiceBox.getItems().clear();
				});

				choiceBox.setDisable(true);
				searchDevicesButton.setDisable(true);
				connectButton.setDisable(true);

				ArrayList<RemoteDevice> bluetoothDevices = new ArrayList<>();
				try {
					// Search for devices
					bluetoothDevices = controlPanelViewListener.setOnSearchClicked();
				} 
				catch (NullPointerException | BluetoothStateException npe) {
					Platform.runLater(() -> {
						DialogPresenter.show(AlertType.ERROR, "Something went wrong. Make sure "
								+ "your Bluetooth is turned on..");	
					});
				}	

				int nbrOfDevices = bluetoothDevices.size();
				if (nbrOfDevices > 0)
				{
					System.out.println("Bluetooth devices: ");
					for (int i = 0; i < nbrOfDevices; i++) 
					{
						RemoteDevice remoteDevice = (RemoteDevice) bluetoothDevices.get(i);
						try {
							String deviceName = remoteDevice.getFriendlyName(true);
							if (deviceName == null)
								deviceName = remoteDevice.getBluetoothAddress();

							System.out.println(i + ": " + remoteDevice.getBluetoothAddress() + " (" + remoteDevice.getFriendlyName(true) + ")");

							final String name = deviceName;
							Platform.runLater(() -> {
								choiceBox.getItems().add(name);
							});
						} catch (IOException e1) {
							e1.printStackTrace();
						}
					}
				}
				choiceBox.setDisable(false);
				searchDevicesButton.setDisable(false);
				connectButton.setDisable(false);
			});
			thread.start();
		});
	}

	private void configureConnectButton() 
	{
		connectButton.setPrefSize(500, 60);
		connectButton.getStyleClass().add("connect");

		connectButton.setOnMouseClicked(e ->
		{
			int selectedIndex = choiceBox.getSelectionModel().getSelectedIndex();
			if (selectedIndex != -1) 
			{
				Thread thread = new Thread(() ->  
				{
					Platform.runLater(() ->  
					{
						choiceBox.setDisable(true);
						searchDevicesButton.setDisable(true);

						connectButton.setDisable(true);
					});

					controlPanelViewListener.setOnConnectClicked(selectedIndex);
					connectButton.setDisable(false);

				});
				thread.start();
			}
			else 
			{
				DialogPresenter.show(AlertType.WARNING, "You must select a Bluetooth device..");
			}
		});
	}

	public void startDisplaying(boolean display)
	{
		if (display) 
		{ 
			connectButton.setText("Disconnect");
			applyButton.setDisable(true);
		}
		else 
		{
			connectButton.setText("Connect");
			applyButton.setDisable(false);
		}
	}

	public void setMaxValues(double x, double y, double z) 
	{
		xTextField.setText(Double.toString(x));
		yTextField.setText(Double.toString(y));
		zTextField.setText(Double.toString(z));
	}

	public void disableBluetoothInput(boolean disable) 
	{
		choiceBox.setDisable(disable);
		searchDevicesButton.setDisable(disable);
	}
}
