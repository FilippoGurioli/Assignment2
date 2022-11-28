package app;

import java.io.IOException;
import Communication.SerialCommChannel;
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
			//Parent root = FXMLLoader.load(getClass().getResource("iot water check1.fxml"));
			final FXMLLoader loader = new FXMLLoader(getClass().getResource("iot water check1.fxml"));
			Parent root = loader.load();
			primaryStage.setScene(new Scene(root));
			primaryStage.show();

			new Thread() {
				public void run() {
					try {
						SerialCommChannel channel = new SerialCommChannel("COM6",9600);
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
										guiController.updateState("NORMAL");
									} else if (msg.equals("PREALARM")) {
										guiController.updateState("PREALARM");
									} else if (msg.equals("ALARM")) {
										guiController.updateState("ALARM");
									} else if (msg.equals("ON")) {
										guiController.updateLight("ON");
									} else if (msg.equals("OFF")) {
										guiController.updateLight("OFF");
									} else {
										guiController.updateChart(Integer.parseInt(msg));
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
