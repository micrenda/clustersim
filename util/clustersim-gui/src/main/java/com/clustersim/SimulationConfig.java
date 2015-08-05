package com.clustersim;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;

import org.apache.commons.lang3.StringUtils;

public class SimulationConfig {

	String basename;
	String dimensions;
	ArrayList<Integer> containerSize;
	int duration;
	
	double stopWhenVolumeIs;
	boolean periodicBoundaries;
	boolean unconstrainedGrow;
	double avramiFitMinVolume;
	double avramiFitMaxVolume;

	String clusterCreationFunc;
	String clusterGrowFunc;
	boolean genericPosition;
	ArrayList<String> clusterPositionFuncs;
	ArrayList<String> commonFuncs;
	
	ArrayList<RenderConfig> renders;
	
	private PropertyChangeSupport pcs = new PropertyChangeSupport(this);

	public void addPropertyChangeListener(PropertyChangeListener pcl) {
		pcs.addPropertyChangeListener(pcl);
	}

	public void removePropertyChangeListener(PropertyChangeListener pcl) {
		pcs.removePropertyChangeListener(pcl);
	}
	
	
	public String getBasename() {
		return basename;
	}
	public String getDimensions() {
		return dimensions;
	}
	public ArrayList<Integer> getContainerSize() {
		return containerSize;
	}
	public int getDuration() {
		return duration;
	}
	public double getStopWhenVolumeIs() {
		return stopWhenVolumeIs;
	}
	public boolean isPeriodicBoundaries() {
		return periodicBoundaries;
	}
	public boolean isUnconstrainedGrow() {
		return unconstrainedGrow;
	}
	public double getAvramiFitMinVolume() {
		return avramiFitMinVolume;
	}
	public double getAvramiFitMaxVolume() {
		return avramiFitMaxVolume;
	}
	public String getClusterCreationFunc() {
		return clusterCreationFunc;
	}
	public String getClusterGrowFunc() {
		return clusterGrowFunc;
	}
	public ArrayList<String> getClusterPositionFuncs() {
		return clusterPositionFuncs;
	}
	public ArrayList<String> getCommonFuncs() {
		return commonFuncs;
	}
	public void setBasename(String basename) {
		this.basename = basename;
	}
	public void setContainerSize(ArrayList<Integer> containerSize) {
		this.containerSize = containerSize;
		pcs.firePropertyChange("estimatedMemoryUsage", "", "?");
	}
	public void setDuration(int duration) {
		this.duration = duration;
	}
	public void setStopWhenVolumeIs(double stopWhenVolumeIs) {
		this.stopWhenVolumeIs = stopWhenVolumeIs;
	}
	public void setPeriodicBoundaries(boolean periodicBoundaries) {
		this.periodicBoundaries = periodicBoundaries;
	}
	public void setUnconstrainedGrow(boolean unconstrainedGrow) {
		this.unconstrainedGrow = unconstrainedGrow;
	}
	public void setAvramiFitMinVolume(double avramiFitMinVolume) {
		this.avramiFitMinVolume = avramiFitMinVolume;
	}
	public void setAvramiFitMaxVolume(double avramiFitMaxVolume) {
		this.avramiFitMaxVolume = avramiFitMaxVolume;
	}
	public void setClusterCreationFunc(String clusterCreationFunc) {
		this.clusterCreationFunc = clusterCreationFunc;
	}
	public void setClusterGrowFunc(String clusterGrowFunc) {
		this.clusterGrowFunc = clusterGrowFunc;
	}
	public void setDimensions(String dimensions) {
		this.dimensions = dimensions;
		updateDimensionalityRelatedFields();
	}
	
	public void setClusterPositionFuncs(ArrayList<String> clusterPositionFuncs) {
		this.clusterPositionFuncs = clusterPositionFuncs;
	}
	public void setCommonFuncs(ArrayList<String> commonFuncs) {
		this.commonFuncs = commonFuncs;
	}
	
	public boolean isGenericPosition() {
		return genericPosition;
	}
	public void setGenericPosition(boolean genericPosition) {
		this.genericPosition = genericPosition;
		updateDimensionalityRelatedFields();
		
	}
	
	public ArrayList<RenderConfig> getRenders() {
		return renders;
	}
	
	public void setRenders(ArrayList<RenderConfig> renders) {
		this.renders = renders;
	}

	public int getDimensionsValue()
	{
		return Integer.parseInt(dimensions.replace("D", ""));
	}
	
	
	String[] fileSizeUnits = {"bytes", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
	public String getEstimatedMemoryUsage(){
		
		double bytes = 16;
		
		if (getContainerSize() != null && ! getContainerSize().isEmpty())
		{
			for (int s: getContainerSize())
				bytes *= s;
		}
		else
			bytes = 0;
		
	    int i = 0;
	    for(i = 0; i < fileSizeUnits.length; i++){
	        if(Math.abs(bytes) < 1024){
	            break;
	        }
	        bytes = bytes / 1024;
	    }
	    
	    return String.format("%.2f %s", bytes, fileSizeUnits[i]);
	}
	
	void updateDimensionalityRelatedFields()
	{
		int d = getDimensionsValue();
		
		ArrayList<String> listPositionFuncs = getClusterPositionFuncs();
		
		if (listPositionFuncs != null)
		{
			if (isGenericPosition())
			{
			
				while (listPositionFuncs.size() < 1)
					listPositionFuncs.add("");
				
				while (listPositionFuncs.size() > 1)
					listPositionFuncs.remove(listPositionFuncs.size() - 1);
			}
			else
			{
				
				while (listPositionFuncs.size() < d)
					listPositionFuncs.add("");
				while (listPositionFuncs.size() > d)
					listPositionFuncs.remove(listPositionFuncs.size() - 1);
			}
		}
		
		
		//
		
		ArrayList<Integer> listContainerSize = getContainerSize();
		
		if (listContainerSize != null)
		{
			while (listContainerSize.size() < d)
				listContainerSize.add(1);
			while (listContainerSize.size() > d)
				listContainerSize.remove(listContainerSize.size() - 1);
			
		}
		
		
		pcs.firePropertyChange("containerSize", listContainerSize, null);
		pcs.firePropertyChange("containerSizeStr", "", "?");
		pcs.firePropertyChange("clusterPositionFuncs", listPositionFuncs, null);
	}
	
	
	public String getContainerSizeStr() {
		return StringUtils.join(this.containerSize, " x ");
	}
	
	public void setContainerSizeStr(String containerSize) {
		
		if (this.containerSize != null)
		{
			int i = 0;
			for (String s: StringUtils.split(containerSize, "x"))
			{
				if (i < this.containerSize.size())
				{
					try 
					{
						this.containerSize.set(i, Integer.parseInt(StringUtils.trim(s)));
					}
					catch (NumberFormatException e) {}
				}
				i++;
			}
		}
		
		pcs.firePropertyChange("estimatedMemoryUsage", "", "?");
	}
}
