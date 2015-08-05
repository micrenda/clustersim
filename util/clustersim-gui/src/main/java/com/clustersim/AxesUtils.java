package com.clustersim;

import org.apache.commons.lang3.StringUtils;

public class AxesUtils {

	public static Integer getAxisValue(int dimensions, String value) {
		if (dimensions <= 3) {
			switch (value) {
			case "x":
				return 0;
			case "y":
				return 1;
			case "z":
				return 2;
			default:
				return null;
			}
		} else {
			try {
				return Integer.parseInt(value.replace("r", "")) - 1;
			} catch (NumberFormatException e) {
				return null;
			}
		}
	}

	public static String getAxisSymbol(int dimensions, int value) {
		if (dimensions <= 3) {
			switch (value) {
			case 0:
				return "x";
			case 1:
				return "y";
			case 2:
				return "z";
			default:
				return null;
			}
		} else {
			return String.format("r%d", value + 1);
		}
	}

	public static String getAxisLabel(int dimensions, int value) {
		return StringUtils.join(getAxisSymbol(dimensions, value), "-axis");
	}

}
