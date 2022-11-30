package app;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.AreaChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Series;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;

public class GUIController implements Initializable{

    @FXML
    private Label lblState;
    @FXML
    private Label lblLight;
    @FXML 
    private AreaChart<Integer, Integer> areaChart;
    @FXML
    private NumberAxis xAxis;
    @FXML
    private Slider sldServo;

    private XYChart.Series<Integer, Integer> series = new Series<>();
    private XYChart.Series<Integer, Integer> WL1 = new Series<>();
    private XYChart.Series<Integer, Integer> WL2 = new Series<>();
    private int time = 0;
    private int degrees = 0;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        this.lblLight.setText("Light: OFF");
        this.WL1.setName("WL1");
        this.WL2.setName("WL2");
        this.areaChart.getData().add(series);
        this.areaChart.getData().add(WL1);
        this.areaChart.getData().add(WL2);
        this.xAxis.setForceZeroInRange(false);
        this.areaChart.setCreateSymbols(false);
        this.areaChart.getYAxis().setAutoRanging(false);
        this.series.setName("Water level");

        //Slider setup
        this.sldServo.valueProperty().addListener(new ChangeListener<Number>() {
            @Override
            public void changed(ObservableValue<? extends Number> observableValue, Number oldValue, Number newValue) {
                degrees = newValue.intValue();
            }
        });
        this.sldServo.disableProperty().set(true);
    }

    void updateState(String state) {
        this.lblState.setText("State: " + state);
    }

    void updateLight(String light) {
        this.lblLight.setText("Light: " + light);
    }

    void updateChart(final int value) {
        time++;
        if (time >= 25) {
            this.series.getData().remove(0);
            this.WL1.getData().remove(0);
            this.WL2.getData().remove(0);
        }
        this.series.getData().add(new XYChart.Data<>(time, value));
        this.WL1.getData().add(new XYChart.Data<>(time, 75));
        this.WL2.getData().add(new XYChart.Data<>(time, 92));
    }

    void disableSlider(boolean state) {
        this.sldServo.disableProperty().set(state);
    }

    int getSUpdate() {
        return this.degrees;
    }

    void setValues() {

    }


}
