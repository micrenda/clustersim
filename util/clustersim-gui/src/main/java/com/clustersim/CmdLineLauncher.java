package com.clustersim;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

import org.apache.commons.lang3.StringUtils;

public class CmdLineLauncher {

	private boolean enThreads = false;
	private boolean enRepeat = false;
	private boolean enDebug = false;
	private boolean enEncoder = false;
	private boolean enKeepPNG = false;
	private boolean enOutputDir = false;
	private boolean enShortArgs = false;

	private int threads = 1;
	private int repeat = 1;
	private boolean debug = false;
	private String encoder = "ffmpeg";
	private boolean keepPNG = false;
	private String outpudDir = "output/";

	private String configFile;

	private PropertyChangeSupport pcs = new PropertyChangeSupport(this);

	public void addPropertyChangeListener(PropertyChangeListener pcl) {
		pcs.addPropertyChangeListener(pcl);
	}

	public void removePropertyChangeListener(PropertyChangeListener pcl) {
		pcs.removePropertyChangeListener(pcl);
	}

	public boolean isEnThreads() {
		return enThreads;
	}

	public void setEnThreads(boolean enThreads) {
		this.enThreads = enThreads;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public boolean isEnRepeat() {
		return enRepeat;
	}

	public void setEnRepeat(boolean enRepeat) {
		this.enRepeat = enRepeat;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public boolean isEnDebug() {
		return enDebug;
	}

	public void setEnDebug(boolean enDebug) {
		this.enDebug = enDebug;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public boolean isEnEncoder() {
		return enEncoder;
	}

	public void setEnEncoder(boolean enEncoder) {
		this.enEncoder = enEncoder;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public boolean isEnKeepPNG() {
		return enKeepPNG;
	}

	public void setEnKeepPNG(boolean enKeepPNG) {
		this.enKeepPNG = enKeepPNG;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public boolean isEnOutputDir() {
		return enOutputDir;
	}

	public void setEnOutputDir(boolean enOutputDir) {
		this.enOutputDir = enOutputDir;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public boolean isEnShortArgs() {
		return enShortArgs;
	}

	public void setEnShortArgs(boolean enShortArgs) {
		this.enShortArgs = enShortArgs;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public int getThreads() {
		return threads;
	}

	public void setThreads(int theads) {
		this.threads = theads;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public int getRepeat() {
		return repeat;
	}

	public void setRepeat(int repeat) {
		this.repeat = repeat;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public boolean isDebug() {
		return debug;
	}

	public void setDebug(boolean debug) {
		this.debug = debug;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public String getEncoder() {
		return encoder;
	}

	public void setEncoder(String encoder) {
		this.encoder = encoder;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public boolean isKeepPNG() {
		return keepPNG;
	}

	public void setKeepPNG(boolean keepPNG) {
		this.keepPNG = keepPNG;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public String getOutpudDir() {
		return outpudDir;
	}

	public void setOutpudDir(String outpudDir) {
		this.outpudDir = outpudDir;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public String getConfigFile() {
		return configFile;
	}

	public void setConfigFile(String configFile) {
		this.configFile = configFile;
		pcs.firePropertyChange("commandLine", "", "?");
	}

	public String getCommandLine() {
		StringBuffer buffer = new StringBuffer();

		buffer.append("clustersim");

		if (enThreads && threads > 0) {
			buffer.append(" ");
			buffer.append(enShortArgs ? "-j" : "--threads");
			buffer.append(" ");
			buffer.append(threads);
		}

		if (enRepeat && repeat > 0) {
			buffer.append(" ");
			buffer.append(enShortArgs ? "-r" : "--repeat");
			buffer.append(" ");
			buffer.append(repeat);
		}

		if (enDebug) {
			buffer.append(" ");
			buffer.append(enShortArgs ? "-d" : "--debug");
		}

		if (enEncoder) {
			buffer.append(" ");
			buffer.append("--ffmpeg-encoder");
			buffer.append(" ");
			buffer.append(encoder);
		}

		if (enKeepPNG) {
			buffer.append(" ");
			buffer.append("--keep-png");
		}

		if (enOutputDir && !StringUtils.isBlank(outpudDir)) {
			buffer.append(" ");
			buffer.append(enShortArgs ? "-o" : "--output_dir");
			buffer.append(" ");
			buffer.append(outpudDir);
		}

		if (!StringUtils.isBlank(configFile)) {
			buffer.append(" ");
			buffer.append(configFile);
		}

		return buffer.toString();
	}

}
