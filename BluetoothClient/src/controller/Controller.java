package controller;

import java.util.ArrayList;

import javax.bluetooth.BluetoothStateException;
import javax.bluetooth.RemoteDevice;

import javafx.application.Platform;
import javafx.scene.control.Alert.AlertType;
import model.BluetoothClient;
import other.ControlPanelViewListener;
import view.BluetoothClientView;
import view.DialogPresenter;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-21
 */
public class Controller 
{
	private BluetoothClientView bluetoothClientView;
	private boolean isRunning;

	private BluetoothClient client;
	private ArrayList<RemoteDevice> bluetoothDevices;

	private double MAX_X = 0.7;
	private double MAX_Y = 0.7;
	private double MAX_Z = 0.7;

	public Controller(BluetoothClientView bluetoothClientView)
	{
		this.bluetoothClientView = bluetoothClientView;
	}

	public void initializeView() 
	{
		ControlPanelViewListener controlPanelViewListener = getControlPanelViewListener();
		bluetoothClientView.initializeView();
		bluetoothClientView.setOnConnectClicked(controlPanelViewListener);
	}

	private ControlPanelViewListener getControlPanelViewListener() 
	{
		ControlPanelViewListener controlPanelViewListener = new ControlPanelViewListener() 
		{	
			@Override
			public void setOnConnectClicked(int selectedIndex) 
			{
				System.out.println("Selected index: " + selectedIndex);
				if (isRunning) 
				{
					isRunning = false;
					client.terminate();

					bluetoothClientView.startDisplaying(false);
				}
				else 
				{
					isRunning = true;
					RemoteDevice remoteDevice = (RemoteDevice) bluetoothDevices.get(selectedIndex);	
					client.searchServices(remoteDevice);

					if (!client.pair(remoteDevice, "1234"))
					{
						isRunning = false;
						bluetoothClientView.startDisplaying(false);
						bluetoothClientView.disableBluetoothInput(false);
						
						Platform.runLater(() -> {
							DialogPresenter.show(AlertType.ERROR, "Couldn't connect to device. Make "
									+ "sure the selected device is turned on..");
						});
					}
					else 
					{
						client.link(Controller.this);
						bluetoothClientView.startDisplaying(true);

						Thread thread = new Thread(client);
						thread.start();
					}
				}				
			}

			@Override
			public ArrayList<RemoteDevice> setOnSearchClicked() throws NullPointerException, BluetoothStateException
			{
				client = new BluetoothClient();

				System.out.println("Address: " + client.getBluetoothAddress());
				System.out.println("Name: " + client.getFriendlyName());

				bluetoothDevices = client.findDevices();
				return bluetoothDevices;
			}

			@Override
			public double[] getMaxValues() 
			{
				double[] values = { MAX_X, MAX_Y, MAX_Z };
				return values;
			}

			@Override
			public void setOnApplyClicked(double x, double y, double z) 
			{
				bluetoothClientView.setMaxValues(x, y, z);
			}
		};
		return controlPanelViewListener;
	}

	public void setPosition(double x, double y, double z) 
	{
		Platform.runLater(() -> {
			bluetoothClientView.setPosition(x, y, z);
		});
	}

	/* Format of received message is "coord: x y z" */
	public void processMessage(String message) 
	{
		Platform.runLater(() -> 
		{
			if (message.startsWith("coord:")) 
			{
				String[] fragmentedMessage = message.split(" ");
				double x = Double.parseDouble(fragmentedMessage[1].trim());
				double y = Double.parseDouble(fragmentedMessage[2].trim());
				double z = Double.parseDouble(fragmentedMessage[3].trim());

				bluetoothClientView.setPosition(x, y, z);
			}
		});
	}

	public void terminate() 
	{
		isRunning = false;
	}
}
