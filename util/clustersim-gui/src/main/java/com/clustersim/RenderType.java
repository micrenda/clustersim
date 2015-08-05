package com.clustersim;

public enum RenderType {
	RENDER_2D, RENDER_3D;

	public String toString() {
		return name().replace("RENDER_", "");
	};
}
