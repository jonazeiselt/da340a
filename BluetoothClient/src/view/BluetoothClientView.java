package view;

import java.util.ArrayList;

import javax.bluetooth.BluetoothStateException;
import javax.bluetooth.RemoteDevice;

import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import other.ControlPanelViewListener;
import other.PlaneViewListener;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-21
 */
public class BluetoothClientView extends VBox 
{
	private PlaneMovementView planeMovementView;
	private PlaneInfoView planeInfoView;

	private ElevationView elevationView;
	private ElevationInfoView elevationInfoView;

	private BottomBarView bottomBarView;
	private TopBarView topBarView;
	private ControlPanelViewListener controlPanelViewListener;
	private ControlPanelView controlPanelView;

	public void initializeView() 
	{
		int spacing = 10;

		topBarView = new TopBarView();
		topBarView.initializeView();

		planeMovementView = new PlaneMovementView(new PlaneViewListener() 
		{
			@Override
			public void setOnPlaneClicked(double xMetres, double yMetres) 
			{
				bottomBarView.setMouseValue(xMetres, yMetres);
			}

			@Override
			public void setOnPlaneExited() 
			{
				new Thread(() -> 
				{
					try {
						Thread.sleep(1000);
						Platform.runLater(() -> {
							bottomBarView.removeMouseValue();
						});
					} 
					catch (InterruptedException e) {
						e.printStackTrace();
					}

				}).start();
			}
		});
		planeMovementView.initializeView();

		planeInfoView = new PlaneInfoView();
		planeInfoView.initializeView();

		VBox planeBox = new VBox(spacing);
		planeBox.getChildren().addAll(planeMovementView, planeInfoView);

		elevationView = new ElevationView();
		elevationView.initializeView();

		elevationInfoView = new ElevationInfoView();
		elevationInfoView.initializeView();

		VBox heightBox = new VBox(spacing);
		heightBox.getChildren().addAll(elevationView, elevationInfoView);

		controlPanelView = new ControlPanelView(new ControlPanelViewListener()
		{	
			@Override
			public ArrayList<RemoteDevice> setOnSearchClicked() throws NullPointerException, BluetoothStateException {
				return controlPanelViewListener.setOnSearchClicked();
			}

			@Override
			public void setOnConnectClicked(int selectedIndex) {
				controlPanelViewListener.setOnConnectClicked(selectedIndex);	
			}

			@Override
			public double[] getMaxValues() {
				return controlPanelViewListener.getMaxValues();
			}

			@Override
			public void setOnApplyClicked(double x, double y, double z) {
				controlPanelViewListener.setOnApplyClicked(x, y, z);
			}
		});
		controlPanelView.initializeView();	
		setMaxValues(0.7, 0.7, 0.7);	

		VBox eastBox = new VBox(spacing+10);
		eastBox.getChildren().addAll(heightBox, controlPanelView);

		HBox mainBox = new HBox(spacing);
		mainBox.setPadding(new Insets(20));
		mainBox.getChildren().addAll(planeBox, eastBox);

		bottomBarView = new BottomBarView();
		bottomBarView.initializeView();

		getChildren().addAll(topBarView, mainBox, bottomBarView);
	}

	public void setMaxValues(double x, double y, double z) 
	{
		planeMovementView.setMaxDimension(x, y);
		elevationView.setMaxElevation(x);
		controlPanelView.setMaxValues(x, y, z);	
	}

	public void setPosition(double x, double y, double z) 
	{
		planeMovementView.setPosition(x, y);
		planeInfoView.setPosition(x, y);

		elevationView.setElevation(z);
		elevationInfoView.setElevation(z);
	}

	public void setOnConnectClicked(ControlPanelViewListener controlPanelViewListener) 
	{
		this.controlPanelViewListener = controlPanelViewListener;
	}

	public void startDisplaying(boolean display) 
	{
		Platform.runLater(() -> {
			controlPanelView.startDisplaying(display);	
		});
	}

	public void disableBluetoothInput(boolean disable) 
	{
		Platform.runLater(() -> {
			controlPanelView.disableBluetoothInput(disable);	
		});
	}
}
