import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.bluetooth.BluetoothStateException;
import javax.bluetooth.DataElement;
import javax.bluetooth.DeviceClass;
import javax.bluetooth.DiscoveryAgent;
import javax.bluetooth.DiscoveryListener;
import javax.bluetooth.LocalDevice;
import javax.bluetooth.RemoteDevice;
import javax.bluetooth.ServiceRecord;
import javax.bluetooth.UUID;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;

import com.intel.bluetooth.RemoteDeviceHelper;

/**
 * BluetoothClient
 * A bluetooth client that is able to find other bluetooth devices and 
 * obtain their bluetooth url address. The client can also pair with a 
 * selected device, send message, and receive message 
 * 
 * Copied and modified code from:
 * 1. Chapter B4. An Echoing Client/Server Application Using BlueCove 
 *    https://fivedots.coe.psu.ac.th/~ad/jg/blue4/blueCoveEcho.pdf
 * 2. SarahVeni, entry in javaprogrammingforums.com
 *    http://www.javaprogrammingforums.com/whats-wrong-my-code/10385-bluetooth-client-server.html
 * 
 * @author Jonas Eiselt
 * @date 2018-05-05
 */
public class BluetoothClient implements DiscoveryListener, Runnable
{
	private Object lock = new Object();
	private ArrayList<RemoteDevice> devices = new ArrayList<>();

	private String deviceBluetoothUrl;
	private StreamConnection streamConnection;

	private OutputStream out;
	private InputStream in;

	private boolean isRunning = true;
	private LocalDevice localDevice;
	private DiscoveryAgent discoveryAgent; 

	public BluetoothClient()
	{
		try {
			localDevice = LocalDevice.getLocalDevice();
		} 
		catch (BluetoothStateException e) {
			System.err.println("Check if Bluetooth is on: " + e.getMessage());
		}
	}

	public void deviceDiscovered(RemoteDevice remoteDevice, DeviceClass deviceClass) 
	{    
		if (!devices.contains(remoteDevice)) 
			devices.add(remoteDevice);   
	}

	public void servicesDiscovered(int transID, ServiceRecord[] servRecord) 
	{
		if (servRecord != null && servRecord.length > 0)
		{		
			System.out.println("Inside Service Discovered");
			deviceBluetoothUrl = servRecord[0].getConnectionURL(0, false);
			System.out.println(deviceBluetoothUrl);

			for (int i = 0; i < servRecord.length; i++) 
			{				
				try 
				{
					DataElement serviceName = servRecord[i].getAttributeValue(0x0100);
					System.out.println("Service " + serviceName.getValue() + " found ");
				} 
				catch (Exception e) {
					// Do nothing...
				}
			}
		}

		synchronized(lock) {
			lock.notify();
		}
	}

	public void serviceSearchCompleted(int transID, int respCode) 
	{
		synchronized(lock) {
			lock.notify();
		}
	}

	public void inquiryCompleted(int discType) 
	{
		synchronized(lock) {
			lock.notify();
		}
	}

	@Override
	public void run() 
	{
		sendMessage("i");
		while (isRunning) 
		{	
			String message = receiveMessage();
			if (message != null && !message.equals(""))
				System.out.println(message);
		}
	}

	public void sendMessage(String msg)
	{
		try 
		{
			PrintWriter writer = new PrintWriter(new OutputStreamWriter(out));
			writer.write(msg + "\n");
			writer.flush();
		}
		catch (Exception e) { 
			e.printStackTrace();
		}
	}

	private String receiveMessage()
	{
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(in));
			return reader.readLine();
		} 
		catch (IOException e) { 
			e.printStackTrace();
		}
		return null;
	}

	public StreamConnection getStreamConnection()
	{
		return streamConnection;
	}

	public String getBluetoothAddress() 
	{
		return localDevice.getBluetoothAddress();
	}

	public String getFriendlyName() 
	{			
		return localDevice.getFriendlyName();
	}

	public ArrayList<RemoteDevice> findDevices() 
	{
		try 
		{
			System.out.println("Starting device inquiry...");

			discoveryAgent = localDevice.getDiscoveryAgent();
			discoveryAgent.startInquiry(DiscoveryAgent.GIAC, this);

			try
			{
				synchronized(lock) {
					lock.wait();
				}
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}

			System.out.println("Device Inquiry Completed. ");
			return devices;
		} 
		catch (BluetoothStateException e1) {
			System.err.println("Check if Bluetooth is on: " + e1.getMessage());
		}
		return new ArrayList<>();
	}

	public void searchServices(RemoteDevice remoteDevice)
	{
		try 
		{
			System.out.println("\nSearching for service...");

			UUID[] uuidSet = new UUID[1];
			uuidSet[0] = new UUID("1101", true);
			int[] attrSet = { 
					0x1101 
			};

			discoveryAgent.searchServices(attrSet, uuidSet, remoteDevice, this);

			try 
			{
				synchronized(lock) {
					lock.wait();
				}
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
		} 
		catch (BluetoothStateException e1) {
			e1.printStackTrace();
		}
	}

	public boolean pair(RemoteDevice remoteDevice, String keyCode) 
	{
		try
		{
			if (keyCode != null) 
			{
				boolean authRes = RemoteDeviceHelper.authenticate(remoteDevice, keyCode);
				System.out.println("Pairing response: " + authRes); 
			}

			streamConnection = (StreamConnection) Connector.open(deviceBluetoothUrl);
			out = streamConnection.openOutputStream();
			in = streamConnection.openInputStream(); 

			return streamConnection != null;
		} 
		catch (Exception e) {
			e.printStackTrace();
		}
		return false;
	}
}