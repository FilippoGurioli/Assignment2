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

public final class GUIMain extends Application {

    @Override
    public void start(final Stage primaryStage) throws IOException {
        try {
            final FXMLLoader loader = new FXMLLoader(getClass().getResource("Assignment2GUI.fxml"));
            Parent root = loader.load();
            primaryStage.setScene(new Scene(root));
            primaryStage.show();

            new Thread() {
                ShowSerialPorts ssp;
                String[] msgArray = {"","",""};

                public void run() {
                    try {
                        ssp = new ShowSerialPorts();
                        SerialCommChannel channel = new SerialCommChannel(ssp.getPort(),9600);
                        System.out.println("Waiting Arduino for rebooting...");		
                        Thread.sleep(4000);
                        System.out.println("Ready.");

                        while (true){

                            for (int i = 0; i < 3; i++) {
                                msgArray[i] = channel.receiveMsg();
                            }

                            GUIController guiController = (GUIController) loader.getController();

                            Platform.runLater(new Runnable() {
                                @Override
                                public void run() {

                                    //Update State
                                    guiController.updateState(msgArray[0]);
                                    //Update Light
                                    guiController.updateLight(msgArray[1]);
                                    //Update Chart
                                    int raw = Integer.parseInt(msgArray[2]);
                                    raw = raw > 200 ? 200 : raw;
                                    raw = raw < 0 ? 0 : raw;
                                    int conversion = 100 - (raw / 2);
                                    guiController.updateChart(conversion);
                                    
                                    if (msgArray[0].equals("ALARM")) {
                                        guiController.disableServoControls(false);
                                    } else {
                                        guiController.disableServoControls(true);
                                    }
                                }
                            });
                            Thread.sleep(300);
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
