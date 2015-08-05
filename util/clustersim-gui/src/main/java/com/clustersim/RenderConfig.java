package com.clustersim;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;

public class RenderConfig {
	
	String name;
	
	RenderType type = RenderType.RENDER_2D;
	
	Integer axis1;
	Integer axis2;
	Integer axis3;
	
	String cuts;
	
    ColorScheme colorScheme;
    ArrayList<Integer> colors;
    
	private PropertyChangeSupport pcs = new PropertyChangeSupport(this);

	public void addPropertyChangeListener(PropertyChangeListener pcl) {
		pcs.addPropertyChangeListener(pcl);
	}

	public void removePropertyChangeListener(PropertyChangeListener pcl) {
		pcs.removePropertyChangeListener(pcl);
	}
	
	
	public ColorScheme getColorScheme() {
		return colorScheme;
	}

	public void setColorScheme(ColorScheme colorScheme) {
		this.colorScheme = colorScheme;
	}

	

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}


	public Integer getAxis1() {
		return axis1;
	}

	public void setAxis1(Integer axis1) {
		this.axis1 = axis1;
	}

	public Integer getAxis2() {
		return axis2;
	}

	public void setAxis2(Integer axis2) {
		this.axis2 = axis2;
	}

	public Integer getAxis3() {
		return axis3;
	}

	public void setAxis3(Integer axis3) {
		if (axis3 == null)
			type = RenderType.RENDER_2D;
		else
			type = RenderType.RENDER_3D;
			
		this.axis3 = axis3;
		
		pcs.firePropertyChange("type", null, type);
	}

	public String getCuts() {
		return cuts;
	}

	public void setCuts(String cuts) {
		this.cuts = cuts;
	}

	
	public ArrayList<Integer> getColors() {
		return colors;
	}

	public void setColors(ArrayList<Integer> colors) {
		this.colors = colors;
	}
	
	@Override
	public String toString() {
		return name;
	}
	
	
	public void setType(RenderType type) {
		this.type = type;
		pcs.firePropertyChange("render3D", "", "?");
	}
	
	public RenderType getType() {
		return type;
	}
	
	public boolean isRender3D()
	{
		return type != null && type == RenderType.RENDER_3D;
	}

}
