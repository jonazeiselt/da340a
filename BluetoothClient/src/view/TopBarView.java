package view;

import javafx.scene.layout.HBox;

/**
 * 
 * @author Jonas Eiselt
 * @since 2018-04-21
 */
public class TopBarView extends HBox 
{
	public void initializeView() 
	{
		getStyleClass().add("bar");
		setPrefSize(1040, 60);
	}
}
