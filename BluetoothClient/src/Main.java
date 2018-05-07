import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

import javax.bluetooth.RemoteDevice;

public class Main
{
	public static void main(String[] args) throws IOException
	{
		BluetoothClient client = new BluetoothClient();
		System.out.println("Address: " + client.getBluetoothAddress());
		System.out.println("Name: " + client.getFriendlyName());

		ArrayList<RemoteDevice> devices = client.findDevices();

		int nbrOfDevices = devices.size();
		if (nbrOfDevices <= 0)
		{
			System.out.println("No Devices Found .");
			System.exit(0);
		}
		else
		{
			System.out.println("Bluetooth devices: ");
			for (int i = 0; i < nbrOfDevices; i++) 
			{
				RemoteDevice remoteDevice = (RemoteDevice) devices.get(i);
				System.out.println(i + ": " + remoteDevice.getBluetoothAddress() + " (" + remoteDevice.getFriendlyName(true) + ")");
			}
		}

		System.out.print("Choose device index: ");
		BufferedReader consoleReader = new BufferedReader(new InputStreamReader(System.in));
		
		String chosenIndex = consoleReader.readLine();
		int index = Integer.parseInt(chosenIndex.trim());
		
		RemoteDevice remoteDevice = (RemoteDevice) devices.get(index);	
		client.searchServices(remoteDevice);
		
		if (!client.pair(remoteDevice, "1234"))
		{
			System.out.println("Couldn't connect to device");
			System.exit(0);
		}
		else 
		{
			Thread thread = new Thread(client);
			thread.start();
		}	
	}
}
