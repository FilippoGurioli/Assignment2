package app;

import java.io.IOException;
import Communication.SerialCommChannel;
import Communication.ShowSerialPorts;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public final class MetalShot extends Application {

	@Override
	public void start(final Stage primaryStage) throws IOException {
		try {
			final FXMLLoader loader = new FXMLLoader(getClass().getResource("iot water check1.fxml"));
			Parent root = loader.load();
			primaryStage.setScene(new Scene(root));
			primaryStage.show();

			new Thread() {
				ShowSerialPorts ssp;
				
				public void run() {
					try {
						ssp = new ShowSerialPorts();
						SerialCommChannel channel = new SerialCommChannel(ssp.getPort(),9600);
						System.out.println("Waiting Arduino for rebooting...");		
						Thread.sleep(4000);
						System.out.println("Ready.");

						while (true){
							String msg = channel.receiveMsg();
							System.out.println(msg);
							GUIController guiController = (GUIController) loader.getController();

							Platform.runLater(new Runnable() {
								@Override
								public void run() {
									if (msg.equals("NORMAL")) {
										guiController.updateState(msg);
										guiController.disableSlider(true);
									} else if (msg.equals("PREALARM")) {
										guiController.updateState(msg);
										guiController.disableSlider(true);
									} else if (msg.equals("ALARM")) {
										guiController.updateState(msg);
										guiController.disableSlider(false);
									} else if (msg.equals("ON")) {
										guiController.updateLight(msg);
									} else if (msg.equals("OFF")) {
										guiController.updateLight(msg);
									} else {
										int raw = Integer.parseInt(msg);
										raw = raw > 200 ? 200 : raw;
										raw = raw < 0 ? 0 : raw;
										int conversion = 100 - (raw / 2);
										guiController.updateChart(conversion);
									}
								}
							});
							Thread.sleep(500);
						}

					} catch (Exception e) {
						System.err.println(e);
					}
				}
			}.start();

		} catch(Exception e) {
			e.printStackTrace();
		}
	}

}
