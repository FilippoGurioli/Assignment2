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

public class GUIController implements Initializable{

    @FXML
    private Label lblState;
    @FXML
    private Label lblLight;
    @FXML 
    private AreaChart<Integer, Integer> areaChart;
    @FXML
    private NumberAxis xAxis;
    
    private XYChart.Series<Integer, Integer> series = new Series<>();
    private int time = 0;
    
	@Override
    public void initialize(URL location, ResourceBundle resources) {
    	this.areaChart.setTitle("Water Level");
    	this.areaChart.getData().add(series);
    	this.xAxis.setForceZeroInRange(false);
    	this.areaChart.setCreateSymbols(false);
    }
    
    void updateState(String state) {
    	this.lblState.setText("State: " + state);
    }
    
    void updateLight(String light) {
    	this.lblLight.setText("Light: " + light);
    }
    
    void updateChart(final int value) {
    	time++;
    	/*if (time >= 10) {
    		for (var data : this.series.getData()) {
    			int tmp = this.series.getData().indexOf(data) + 1;
    			if (tmp < this.series.getData().size()) {
    				data.setXValue(this.series.getData().get(tmp).getXValue());
    				data.setYValue(this.series.getData().get(tmp).getYValue());
    			}
    		}
    		this.series.getData().get(this.series.getData().size() - 1).setXValue(time);
    		this.series.getData().get(this.series.getData().size() - 1).setYValue(value);
    	} else {
    		this.series.getData().add(new XYChart.Data<>(time, value));
    	}*/
    	if (time >= 10) {
    		this.series.getData().remove(0);
    	}
    	this.series.getData().add(new XYChart.Data<>(time, value));
    }    
}
