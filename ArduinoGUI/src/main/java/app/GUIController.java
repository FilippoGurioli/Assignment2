package app;

import java.net.URL;
import java.util.ResourceBundle;
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
    private int time = 0;
    
	@Override
    public void initialize(URL location, ResourceBundle resources) {
    	this.areaChart.getData().add(series);
    	this.xAxis.setForceZeroInRange(false);
    	this.areaChart.setCreateSymbols(false);
    	this.areaChart.getYAxis().setAutoRanging(false);
    	this.series.setName("Water level");
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
    	}
    	this.series.getData().add(new XYChart.Data<>(time, value));
    }
    
    void disableSlider(boolean state) {
    	this.sldServo.disableProperty().set(state);
    }
}
