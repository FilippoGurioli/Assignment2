package Communication;

import app.GUIController;

public class CommController {
    
    GUIController guiC;
    
    public CommController(){
        //this.guiC = guiC;
    }

	public void communicate() throws Exception {	
	    SerialCommChannel channel = new SerialCommChannel("COM6",9600);
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");

		while (true){
			String msg = channel.receiveMsg();
			System.out.println(msg);
			Thread.sleep(500);
		}
	}
	
}
