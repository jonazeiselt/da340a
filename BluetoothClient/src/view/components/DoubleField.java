package view.components;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.scene.control.TextField;

/**
 * A TextField that automatically prevents the user to enter 
 * information other than doubles or numbers
 * 
 * @author Jonas Eiselt
 * @since 2018-05-10
 * 
 * @see http://www.tutorialsface.com/2016/12/how-to-make-numeric-decimal-textfield-in-javafx-example-tutorial/
 */
public class DoubleField extends TextField
{
	public DoubleField(double value) 
	{
		super(Double.toString(value));
		textProperty().addListener(new ChangeListener<String>() 
		{
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue)
            {
                if (!newValue.matches("\\d{0,4}([\\.]\\d{0,6})?"))
                    setText(oldValue);
            }
        });
	}

	public double getDouble() 
	{
		return Double.parseDouble(getText());	
	}
}
