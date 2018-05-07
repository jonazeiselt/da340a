/**
 * 
 * @author Jonas Eiselt
 * @since 2018-05-05
 * 
 * https://sourceforge.net/projects/bluecove/
 */

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;

public class Main2 
{
	boolean scanFinished = false;
	String hc06Url = "btspp://98D33380C769:1;authenticate=false;encrypt=false;master=false"; //Replace this with your bluetooth URL
	
	public static void main(String[] args) 
	{
		try {
			new Main2().go();
		} 
		catch (Exception ex) {
			ex.printStackTrace();
		}
	}
	
	private void go() throws Exception 
	{
		StreamConnection streamConnection = (StreamConnection) Connector.open(hc06Url);
		OutputStream os = streamConnection.openOutputStream();
		InputStream is = streamConnection.openInputStream();

		PrintWriter writer = new PrintWriter(new OutputStreamWriter(os));
		writer.write("Hi\n");
		writer.flush();
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(is));
		while (true) 
		{
			System.out.println("Hello?");
			System.out.println("Received: " + (char) reader.read());
		}
		// is.close();
		// streamConnection.close();
	}
}