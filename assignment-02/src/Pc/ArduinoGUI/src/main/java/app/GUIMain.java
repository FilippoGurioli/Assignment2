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
            final FXMLLoader loader = new FXMLLoader(getClass().getResource("iot water check1.fxml"));
            Parent root = loader.load();
            primaryStage.setScene(new Scene(root));
            primaryStage.show();

            new Thread() {
                ShowSerialPorts ssp;
                boolean first = true;
                int WL1;
                int WL2;
                int WL3;
                int period = 0;

                String[] msgArray = {"","","",""};

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

                            if (first) {
                                //period = Integer.parseInt(msgArray[0]);
                                //WL1 = Integer.parseInt(msgArray[1]);
                                //WL2 = Integer.parseInt(msgArray[2]);
                                //WL3 = Integer.parseInt(msgArray[3]);
                                first = false;
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
                                    //Update Servo/Slider

                                    if (msgArray[0].equals("ALARM")) {
                                        guiController.disableSlider(false);
                                    } else {
                                        guiController.disableSlider(true);
                                    }

                                    //channel.sendMsg(String.valueOf(guiController.getSUpdate()));

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
