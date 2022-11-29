package Communication;

import jssc.*;

public class ShowSerialPorts {

	public String getPort() {
		String pn = "";
		String[] portNames = SerialPortList.getPortNames();
		for (int i = 0; i < portNames.length; i++){
		    if (!portNames[i].equals("")) {
		    	pn = portNames[i];
		    }
		}
		return pn;
	}

}
