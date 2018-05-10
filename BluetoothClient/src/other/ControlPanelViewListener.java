package other;

import java.util.ArrayList;

import javax.bluetooth.BluetoothStateException;
import javax.bluetooth.RemoteDevice;

public interface ControlPanelViewListener 
{
	void setOnConnectClicked(int selectedIndex);
	ArrayList<RemoteDevice> setOnSearchClicked() throws NullPointerException, BluetoothStateException;
	double[] getMaxValues();
	void setOnApplyClicked(double x, double y, double z);
}
